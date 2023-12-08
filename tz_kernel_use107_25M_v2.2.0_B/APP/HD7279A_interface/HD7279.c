#include <stm32f10x_lib.h>
#include "includes.h"
#include "hd7279.h"
#include  "bsp.h"
#include  "key.h"


//IO��������
#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ
//IO��������	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //����SDA 

extern void DelayMs(vu32 m);

#define  T1    (50US)  //cs�½��ص�clk�������
#define  T2    (8US)   //����ָ��ʱ���clk������
#define  T3    (8US)   //�ֽڴ�����clk����ʱ��
#define  T4    (25US)  //ָ��������ʱ����
#define  T5    (25US)  //������ָ��ʱ��ָ��������֮��ļ��
#define  T6    (8US)   //����������ݽ�����ʱ��
#define  T7    (8US)   //����������ʱCLK������
#define  T8_MAX  (5US)  //������������ɺ�DATAתΪ����״̬��ʱ�䣬���Ϊ5us



//**************** ������I/O�ڶ��� ******************

INT8U digit[5];
INT8U key_number, j, k;
INT16U tmr;
INT32U wait_cnter;
/*
�ͽṹ�塢������һ��������ö�����ͱ����ķ�ʽҲ�����֡�
1.��������ʱ�򣬶������
	enum Color{red,yellow,green}color
2.�ȶ������ͺ�������͵ı���
	enum Color{red,yellow,green};
  enum Color color;

3.��������
	enum {red,yellow,green}color;
	
	
	ͬ����û���������Ƶ�ö�٣���ʹ�� typedef �ؼ��֣�ֻ�������Ͷ����ʱ���������
*/
enum _useKey KeyState=KEY_WAIT;



extern  INT8U		  TimeDisValidFlag;
extern	mytime 		*p_timemu;


void long_delay(void);         //����ʱ
void short_delay(void);        //������ʱ
void delay10ms(unsigned char); //��ʱ10MS


//��һ������
void SendByteToHd7279(INT8U byte)
{
 	INT8U i,j,k;
	OS_CPU_SR  cpu_sr;
	
	
  //OS_ENTER_CRITICAL();
 
	_nop_();

	
			Set7279DATA(1);	
			for (i=0;i<40;i++){
				_nop_();
			}
			
			for(i=0;i<8;i++){	
				if(byte & 0x80){	
					Set7279DATA(1);			
				}else{
					Set7279DATA(0);
				}
					
				Set7279CLK(1);	
				for (j=0;j<8;j++){
					_nop_();
				}

				
				Set7279DATA(0);	
				for (k=0;k<8;k++){
					_nop_();
				}
				Set7279CLK(0);			//��ӵ�
				
				for (j=0;j<8;j++){
					_nop_();
				}
				byte<<=1;
			}
	
	
	//OS_EXIT_CRITICAL();	
}





/*********************************

#define  T1    (50US)  //cs�½��ص�clk�������
#define  T2    (8US)   //����ָ��ʱ���clk������
#define  T3    (8US)   //�ֽڴ�����clk����ʱ��
#define  T4    (25US)  //ָ��������ʱ����
#define  T5    (25US)  //������ָ��ʱ��ָ��������֮��ļ��
#define  T6    (8US)   //����������ݽ�����ʱ��
#define  T7    (8US)   //����������ʱCLK������
#define  T8_MAX  (5US)  //������������ɺ�DATAתΪ����״̬��ʱ�䣬���Ϊ5us


			���ذ���ֵ
**********************************/
INT8U RecvByteFromHd7279(void)
{
 	INT8U ret;
 	INT8U i,j,k;
	 GPIO_InitTypeDef GPIO_InitStructure;

	
	
	Set7279DATA(1);				  //������֮ǰҪ������P1��
 	for (i=0;i<40;i++){			 //T4,T5
		_nop_();
	}
	
	
	  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING ;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

	
	
	
 	for(i=0;i<8;i++){
  		Set7279CLK(1);
  		for (j=0;j<8;j++){		 //T6
				_nop_();
		  }
  		ret<<=1;
  		if(Get7279DATA())	ret|=0x01;
  		Set7279CLK(0);
  		for (k=0;k<8;k++){		   //T7
				_nop_();
		  }
 	}
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
 	Set7279DATA(0);
	
 	
	return ret;	
}

void write_hd7279(INT8U cmd, INT8U dat)
{
	SendByteToHd7279(cmd);
 	SendByteToHd7279(dat);
}

INT8U read_hd7279(INT8U cmd)
{
 	SendByteToHd7279(cmd);
 	return RecvByteFromHd7279();
}


/*************����ʱ******************************/
void long_delay(void)
{
  INT8U i;
 for (i=0;i<0x30;i++);
}
/*************����ʱ*******************************/
void short_delay(void)
{
  INT8U i;
 for (i=0;i<8;i++);
}
//*********************n*10ms**********************/


/*
void delay10ms(INT8U time)
{
  INT8U i;
  INT16U j;

 for (i=0;i<time;i++)
 {
  for(j=0;j<0x390;j++)
  {
   if (!Get7279KEY())
   {
    //key_int();
		 
   }
  }
 }
}						

*/

/*************************************************/

//΢��ʱ ���������� ����Ӧ7279
void _nop_() 
{
	int i;
	for(i=0;i<10;i++) ;
}

void Hd7279_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	Set7279CLK(1);
  DelayMs(100);	
	
	Set7279CS(0);
  SendByteToHd7279(CMD_RESET); 
  DelayMs(100);		
  Set7279CS(1);    
     
}



/*********************************
*���ܣ�ĸ��ʱ����ʾ
*
*********************************/
void Display(void)
{ 
   if(KeyState==KEY_WAIT){ 
			 #ifdef USE_COMPANY_TZ_DIS 
					 
					 if(TimeDisValidFlag==1){     //ĸ��ʱ����Ч ��ʾʱ��	 
						 write_hd7279(DECODE0+0,p_timemu->second%10);
						 write_hd7279(DECODE0+1,p_timemu->second/10);      
						 write_hd7279(DECODE0+3,p_timemu->minute%10);
						 write_hd7279(DECODE0+4,p_timemu->minute/10);       
						 write_hd7279(DECODE0+6,p_timemu->hour%10);
						 write_hd7279(DECODE0+7,p_timemu->hour/10);    
					 }else {                 //ĸ��ʱ����Ч ��ʾ��-�� 
						 write_hd7279(DECODE0+0,0x0a);
						 write_hd7279(DECODE0+1,0x0a);      
						 write_hd7279(DECODE0+3,0x0a);
						 write_hd7279(DECODE0+4,0x0a);        
						 write_hd7279(DECODE0+6,0x0a);
						 write_hd7279(DECODE0+7,0x0a);
						}
					 write_hd7279(DECODE0+2,0x0a); //
					 write_hd7279(DECODE0+5,0x0a); // 
					 
						DelayMs(10);
						
						
				#else
					 
					 if(TimeDisValidFlag==1){     //ĸ��ʱ����Ч ��ʾʱ��
						 write_hd7279(DECODE0+0,p_timemu->minute/10);       
						 write_hd7279(DECODE0+2,p_timemu->hour%10);
						 write_hd7279(DECODE0+3,p_timemu->hour/10); 
						 
						 write_hd7279(DECODE0+4,p_timemu->second%10); 
						 write_hd7279(DECODE0+5,p_timemu->second/10);
						 write_hd7279(DECODE0+7,p_timemu->minute%10);
					 }else {                 //ĸ��ʱ����Ч ��ʾ��-�� 
						 write_hd7279(DECODE0+0,0x0a);
						 write_hd7279(DECODE0+1,0x0a);      
						 write_hd7279(DECODE0+3,0x0a);
						 write_hd7279(DECODE0+4,0x0a);        
						 write_hd7279(DECODE0+6,0x0a);
						 write_hd7279(DECODE0+7,0x0a);
						}
						
						
					 write_hd7279(DECODE0+1,0x0a); //		
					 write_hd7279(DECODE0+6,0x0a); // 
					
           DelayMs(10);						
				#endif
   }  
 }
 
 				
