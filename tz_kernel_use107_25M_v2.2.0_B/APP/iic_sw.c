#include <stm32f10x_gpio.h>	 
#include "iic_sw.h"
//#include "config.h"
#include  "OS_CPU.h"
#include  "gps.h"






#define sw_clk		    RCC_APB2Periph_GPIOB 
#define sw_port 	    GPIOB 							
#define sw_scl  	    GPIO_Pin_14
#define sw_sda		    GPIO_Pin_15	




extern  mytime 		*p_timeslave;
extern  mytime 		hms_variant[5];
extern  INT8U  Light_Start,Light_End;         //����ʱ���
extern  INT8U  Rythem_Number,Strike_Number;   //��ʱ���ֺţ�������	
extern  INT8U  Report_Time[24];

extern void DelayMs(vu32 m);

extern  config 		board;
extern  INT32U 		NTP;
INT8U   BsPowerOnOff[24],ZmPowerOnOff[24];
INT8U   BsRythemAndKnock[24][9]={
  {9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},
	{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},
	{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},
	{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7},{9,7,7,7,7,7,7,7,7}
};

/*
	v3.0
*/

#define scl(x) 	(x)?(sw_port->BSRR=sw_scl):(sw_port->BRR=sw_scl) 	        
#define sda(x)  (x)?(sw_port->BSRR=sw_sda):(sw_port->BRR=sw_sda)        
#define issda	  (sw_port->IDR & sw_sda)
 
static void iic_delay(u16 j) 
{      
   u32 i = 0x10<<j;    			  
   while(i--);
}   
   
static char iic_start(void) 
{   
    sda(1);   
    scl(1);   
    iic_delay(1);   
    if(!issda)
		return(0); 
    sda(0);   
    iic_delay(1);   
    if(issda) 
		return(0);  
    sda(0);   
    iic_delay(1);   
return(1);   
}   
   
static void iic_stop(void) 
{   
    scl(0);   
    iic_delay(1);   
    sda(0);   
    iic_delay(1);   
    scl(1);   
    iic_delay(1);   
    sda(1);   
    iic_delay(1);   
}   
   
static void iic_ack(void) 
{      
    scl(0);   
    iic_delay(1);   
    sda(0);   
    iic_delay(1);   
    scl(1);   
    iic_delay(1);   
    scl(0);   
    iic_delay(1);   
}   
   
static void iic_nack(void) 
{      
    scl(0);   
    iic_delay(1);   
    sda(1);   
    iic_delay(1);   
    scl(1);   
    iic_delay(1);   
    scl(0);   
    iic_delay(1);   
}   
   
static char iic_wack(void) 
{  			
	scl(0);   
    iic_delay(1);   
    sda(1);             
    iic_delay(1);   
    scl(1);   
    iic_delay(1);   
    if(issda) 
	{   
      	scl(0);
		iic_delay(1);    
      	return(0);   
    }   
    scl(0);  
	iic_delay(1);  
return(1);   
}   
   
 void iic_wr_byte(u8 byte) 
{	   
    u8 i=8;   
    while(i--) 
	{   
        scl(0);   
        iic_delay(1);   
      	if(byte&0x80)   
        	sda(1);     
      	else    
        	sda(0);      
        byte <<= 1;   
        iic_delay(1);   
        scl(1);   
        iic_delay(1);   
    }   
    scl(0);  
	iic_delay(1);    
}   
   
static u8 iic_rd_byte(void) 
{ 	    
    u8 i = 8;   
    u8 byte = 0;      
    sda(1);                 
    while(i--) 
	{   
	    byte <<= 1;         
	    scl(0);   
	    iic_delay(1);   
	    scl(1);   
	    iic_delay(1);     
      	if(issda)   
         	byte |= 0x01;            
    }   
    scl(0);  
	iic_delay(1);     
return(byte);   
}   
  			
u8 iic_sw_write(u8 dev, u8 sub, u8* pbuf, u8 len) 
{ 
 	if(!iic_start())
		return(0);  		  
    iic_wr_byte(dev); 
  if(!iic_wack()) 
	{
		iic_stop(); 
		return(0);
	}	  	
	iic_wr_byte(sub);   			   
    iic_wack();  	
	while(len--)
	{
		iic_wr_byte(*pbuf++);		   
      	iic_wack();
	}		           
  iic_stop();
	iic_delay(100); 
	
  return(1);      
}   
       			   
u8 iic_sw_read(u8 dev, u8 sub, u8* pbuf, u8 len) 
{  
 	if(!iic_start())
		return(0); 
	
  iic_wr_byte(dev); 	 
	if(!iic_wack()) 
	{
		iic_stop(); 
		return(0);
	} 	  	  
	iic_wr_byte(sub);   			
	iic_wack();   
	iic_start();   
	iic_wr_byte(dev|0x01);   
	iic_wack();			 	 
	while(len--)
	{
		*pbuf++ = iic_rd_byte(); 
		if(len)
			iic_ack();   
      	else 
			iic_nack(); 
	} 	 	      
    iic_stop();
	iic_delay(100);    
return(1);  
}


void iic_sw_init(void) 
{
  	GPIO_InitTypeDef  GPIO_InitStructure;
	  
  	RCC_APB2PeriphClockCmd(sw_clk, ENABLE);  
	 
  	/* Configure I2C1 pins: SCL and SDA */   
  	GPIO_InitStructure.GPIO_Pin 	= sw_scl | sw_sda;   
  	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;   
  	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_OD;     
  	GPIO_Init(sw_port, &GPIO_InitStructure);
	

	//��ʼ��IIC���ߣ�ʹ���Ϊ����״̬��added by sjw
	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
    iic_stop();
			

	
} 

void get_iic_setting(void) 
{
	
	INT8U init,js,data[2],bspower_onoff[24];	
  INT8U rx[8] = {0};	
	
    
    p_timeslave=&hms_variant[1];	//ָ����������added by sjw	
		#if 0
    iic_sw_read(eep_chip_ds3231, iic_max1, board.max_colck, 8); //��3231��ʱ��		
	  DelayMs(100);
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	  #endif
	 	
	
	
		iic_sw_read(eep_chip_24cxx, iic_max255, &init, 1); 	//��EEPROM�ڵ����λ���ݣ��������Ƿ��һ�β�������added  by sjw

		if(init==0xFF)
		{	
				board.east_time[0]=DEFAULT_EASTHOUR_VALUE;
				board.east_time[1]=DEFAULT_EASTMIN_VALUE;
				board.east_time[2]=DEFAULT_EASTSEC_VALUE;
				board.east_time[3]=DEFAULT_EASTJY_VALUE;
				board.east_time[4]=DEFAULT_EASTSTA_VALUE;
				board.east_time[5]=0x5a;
				board.east_time[6]=0x5a;
				board.east_time[7]=0x5a;
				iic_sw_write(eep_chip_24cxx, iic_eeprom_east, &board.east_time[0], 8);
				DelayMs(100);
				data[0]=Light_Start;
				data[1]=Light_End;		
				iic_sw_write(eep_chip_24cxx, iic_eeprom_zmpower_on, data, 2);	//��ʼ��һ�ν�����Ĭ������ѹ��24cxx���棡      ��������19   ��������06
				DelayMs(100);
			  data[0]=Rythem_Number;                                        
				data[1]=Strike_Number;		
			  iic_sw_write(eep_chip_24cxx,  iic_eeprom_bsrythem, data, 2);	//��ʼ��һ�ν���ʱǰ�༰�����ļ�ѹ��24cxx���棡 ǰ��8       �õ�7
      

			//��ʼ��һ�ν�24����ı�ʱ����ѹ��24cxx���汣�棡
			  for(js=0;js<8;js++)
					 bspower_onoff[js]=Report_Time[js];
			  iic_sw_write(eep_chip_24cxx,  iic_eeprom_bspower0_7, bspower_onoff, 8);	//��ʼ��һ�ν���ʱ�����ֽ�����ѹ��24cxx���棡 
				
				
				DelayMs(100);
        for(js=8;js<16;js++)
					 bspower_onoff[js]=Report_Time[js];
			  iic_sw_write(eep_chip_24cxx,  iic_eeprom_bspower8_15, bspower_onoff, 8);
				
				
				
			  DelayMs(100);
				for(js=16;js<24;js++)
					 bspower_onoff[js]=Report_Time[js];
			  iic_sw_write(eep_chip_24cxx,  iic_eeprom_bspower16_23, bspower_onoff, 8);	
				
				
		    DelayMs(100);
				init=0x55;
				iic_sw_write(eep_chip_24cxx, iic_max255, &init, 1);//������ֽڽ����޸ģ��Ա��������������
				
			}else{
				//********************************************************************
				//********************************************************************
				//********************************************************************
				//********************************************************************
				//********************************************************************
				//********************************************************************
				//********************************************************************
				//ȡ����ʱ��
				iic_sw_read(eep_chip_24cxx, iic_eeprom_east, &board.east_time[0], 8);
				DelayMs(50);
				iic_sw_read(eep_chip_24cxx, iic_eeprom_east_sta, &board.east_time[7], 1);
				
				
				p_timeslave->hour  =board.east_time[0];
	      p_timeslave->minute=board.east_time[1];
	      p_timeslave->second=board.east_time[2];
				p_timeslave->sta   =board.east_time[7];
				
			
				#if 0
				iic_sw_read(eep_chip_24cxx, iic_eeprom_south, &board.south_time[0], 8);
				DelayMs(50);
				iic_sw_read(eep_chip_24cxx, iic_eeprom_west, &board.west_time[0], 8);
				DelayMs(50);
				iic_sw_read(eep_chip_24cxx, iic_eeprom_north, &board.north_time[0], 8);
				DelayMs(50);
				#endif
				
				//********************************************************************
				//ȡ��������ʱ�䣡
				DelayMs(50);
				iic_sw_read(eep_chip_24cxx, iic_eeprom_zmpower_on, data, 2);
				Light_Start=data[0];
				Light_End=data[1];
				

				//********************************************************************
			  //ȡ��ʱ24���㿪��ʱ��+ǰ��+�õ㣡�����������ÿ�������Ӧ��ǰ��ѡ�������������ѡ��򻯣���added by sjw��
				DelayMs(50);
				iic_sw_read(eep_chip_24cxx, iic_eeprom_bsrythem, data, 2);
				Rythem_Number=data[0];                                        
				Strike_Number=data[1];
				
				
				DelayMs(50);
        iic_sw_read(eep_chip_24cxx, iic_eeprom_bspower0_7, &bspower_onoff[0], 8);//ԭ������ָ���bspower_onoff�����Դ���7����Ǵ������ݣ���added by sjw
				for(js=0;js<8;js++)
					  Report_Time[js]=bspower_onoff[js];
				
        DelayMs(50);
        iic_sw_read(eep_chip_24cxx, iic_eeprom_bspower8_15, &bspower_onoff[8], 8);
				for(js=8;js<16;js++)
					  Report_Time[js]=bspower_onoff[js];
						
				DelayMs(50);
        iic_sw_read(eep_chip_24cxx, iic_eeprom_bspower16_23, &bspower_onoff[16], 8);
				for(js=16;js<24;js++)
					  Report_Time[js]=bspower_onoff[js];					
			
			}
}



/******************************
 *���ܣ�HEXת��ΪBCD
 *���룺��ת������
******************************/

INT8U HEX_to_BCD(INT8U data){

 INT8U i,k;
 i=data%10;
 k=data/10;
 k<<=4; 
 return (i+k);
}

/******************************
 *���ܣ�BCDת��ΪHEX
 *���룺��ת������
******************************/

INT8U BCD_to_HEX(INT8U data){

 INT8U i,k;
 i=data & 0x0f;
 k=data & 0xf0;
 k>>=4;  
 return (i+k*10);
}



