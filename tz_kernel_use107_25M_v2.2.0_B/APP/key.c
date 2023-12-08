#include <key.h>
#include "includes.h"
#include "hd7279.h"
#include "gps.h"
#include "iic_sw.h"
#include "ds3231.h"
#include "time.h"

#define KEY_DELAY_LONG  30
#define KEY_DELAY_SHORT 15

#define HD7279_clk _RB13    //
#define HD7279_dat _RB14    //

 INT8U  Report_Hour; //报时时间段	
INT8U Report_Time[24]={0,0,0,0,0,0,0,            //系统默认报时开关状态！！added by sjw
	                     1,1,1,1,1,1,
											 0,0,1,1,1,1,1,1,
                       0,0,0};
extern  INT8U  IntKeyActionValid;
extern INT8U  PowerOnFLag;

extern INT8U Hour,Min,Sec;
extern u32 NTP;
extern		mytime 		*p_timemu;
extern	  mytime 		*p_SaveTime;
extern	 INT8U Set_Time[4]; 
extern	 INT8U Set_StrikeNumber[4]; 
extern		void 		  DelayMs(vu32 m);

INT8U     TimeStore[6];

				 
enum   KeyRun_Order  Key_Subclock_State1=WALK;//按键操作命令
  
												 
extern  INT8U  Rythem_Number,Strike_Number;											
extern   struct   Timdata_sub     Subclock1,Subclock2;
void     SetDs3231_Time(INT8U,INT8U,INT8U);


/*
这是对

1.状态键第1次 调整母钟时间
2.状态键第2次 准备调整子钟状态，使用位选键选择要调整的位置！
3.状态键第3次 准备调整子钟时间，使用位选键选择要调整的位置！ 
4.状态键第4次 准备调整照明开关时间，使用位选键选择要调整的位置！
5.状态键第5次 准备调整报时开关时间，使用位选键选择要调整的位置！

6.状态键第6次 恢复正常！

*/


INT8U Report_Order=1,Report_Number=1,Report_En=1;//Report_En变量默认代表报时关闭，为2的话代表报时打开！！added by sjw

extern  mytime 		*p_timeslave;

extern enum _useKey KeyState;
	INT8U  Blink_Number=0x3f;
INT8U  Subclock_State=0,Subclock_Number=1,Subclock_Order=1;//键盘设置暂存   Subclock_Number是子钟号！！  added by sjw
extern	INT8U  Time_Modify[6]; //母钟时间修改缓存
extern  INT8U  Mp3_Ok,Mp3_Error; 
														 
extern  INT8U  Rythem_Minite[15];
extern  INT8U Rythem_Second[15];
extern  config board; 

extern  INT8U  Light_En;                   //照明使能  
extern  INT8U  Light_Start,Light_End;   //照明时间段
extern  INT8U  ReadKey_Value;
//https://wenku.baidu.com/view/802faed3a88271fe910ef12d2af90242a895abb0.html?_wkts_=1694764925358&bdQuery=stm32f103%E5%88%9D%E5%A7%8B%E5%8C%967279
//stm32f10x各部分常用的初始化步骤
extern  void write_hd7279(INT8U cmd, INT8U dat);
	 extern unsigned int ds3231_tm_rd(void);
INT8U Count_State;


/*
void Init_MAX7219(void)
{max7219_send(0x09, 0xff);       //译码方式：BCD译码
	max7219_send(0x0a, 0x05);       //亮度
	max7219_send(0x0b, 0x07);       //显示数码管数量
	max7219_send(0x0c, 0x01);     	 //断电模式0，显示模式1
	max7219_send(0x0f, 0x00);       //开始显示，1为测试，0为显示
}
*/

/************************************
*功能：向7279发送一字节
*输入：待发送数据
************************************/
void send_byte_7279( INT8U out_byte)
{
  volatile INT32U i,j;
 
	
	/*
  for(j=0;j<KEY_DELAY_LONG;j++) Nop();

  for(i=0;i<8;i++)
   {
    if(out_byte&0x80)  HD7279_dat=1;      
    else HD7279_dat=0;
    Nop();Nop();
    Nop();Nop(); 
    HD7279_clk=1;   
    for(j=0;j<KEY_DELAY_SHORT;j++) Nop();

    HD7279_clk=0;   
    for(j=0;j<KEY_DELAY_SHORT;j++) Nop();

    out_byte<<=1;
   }
 //dat=0;
	 
	 */
	 
}

/************************************
*功能：读取7279中的一字节
*返回：读取到的数据
************************************/
INT8U receive_byte_7279(void)
{
  volatile INT32U  i,j;
           INT8U  in_byte=0xff;  
 
	/*
  TRISB|=0x4000;   //设为输入状态

  for(j=0;j<KEY_DELAY_LONG;j++) Nop();

  for(i=0;i<8;i++)
   {
     HD7279_clk=1;    
     for(j=0;j<KEY_DELAY_SHORT;j++) Nop();

     in_byte<<=1;
     HD7279_clk=0;

     if(HD7279_dat==1)
      {
      in_byte=in_byte|0x01;
      } 
     else  in_byte=in_byte&0xfe;   
    
     for(j=0;j<KEY_DELAY_SHORT;j++) Nop();
   }
  TRISB&=0xbfff; //设为输出状态   
	 
	 */
	 
  return(in_byte);
}


/************************************
*功能：向7279发送命令
*输入：命令、设置参数
************************************/
void write7279(INT8U cmd, INT8U data)
{
  send_byte_7279(cmd);
  send_byte_7279(data);
}


/************************************
*功能：读取7279
*输入：
*返回：读取到的数据
************************************/
INT8U read7279(INT8U command)
{  
  send_byte_7279(command);   
  return(receive_byte_7279());  
}

 
 
/*********************************
*功能：按键功能处理
*
*********************************/
void  Key_Operation(void){//典型的状态机函数！！added by sjw
  
  
	
	/*
	if(ReadKey_Value==15)  母钟时间   S1
	if(ReadKey_Value==7)    位选      S2
  if(ReadKey_Value==14) 	 +        S3	
  if(ReadKey_Value==6)     -        S4 
  if(ReadKey_Value==13)  取消功能   S5  
  if(ReadKey_Value==5){  功能确定   S6 	
	
	*/
	
	
	
	
	  if(ReadKey_Value==15){   //状态按键按动有效！ 
				switch(Count_State){
						case 0:
								Time_Modify[0]=p_timemu->second%10;
								Time_Modify[1]=p_timemu->second/10; 
								 
								Time_Modify[2]=p_timemu->minute%10;
								Time_Modify[3]=p_timemu->minute/10; 
								 
								Time_Modify[4]=p_timemu->hour%10;
								Time_Modify[5]=p_timemu->hour/10;						
								KeyState=KEY_MAS_TIME;
						break;
						
						case 1:	
								KeyState=KEY_SUB_STATE;
						break;
					
						case 2:
							/*
								Time_Modify[0]=board.east_time[2]%10;
								Time_Modify[1]=board.east_time[2]/10; 
								 
								Time_Modify[2]=board.east_time[1]%10;
								Time_Modify[3]=board.east_time[1]/10; 
								 
								Time_Modify[4]=board.east_time[0]%10;
								Time_Modify[5]=board.east_time[0]/10;	
						*/
             	
                Time_Modify[0]=p_timeslave->second%10;
								Time_Modify[1]=p_timeslave->second/10; 
								 
								Time_Modify[2]=p_timeslave->minute%10;
								Time_Modify[3]=p_timeslave->minute/10; 
								 
								Time_Modify[4]=p_timeslave->hour%10;
								Time_Modify[5]=p_timeslave->hour/10;	
                
                						
								KeyState=KEY_SUB_TIME;
						break;
						
						case 3:
							  //Report_Hour=Set_Time[0]+Set_Time[1]*10; 
								KeyState=KEY_REPORT;
						    
						break;
						
						case 4:
							  Subclock_Order=Light_En+1; 
								Set_Time[0]=Light_End%10;
								Set_Time[1]=Light_End/10;        
								Set_Time[2]=Light_Start%10;
								Set_Time[3]=Light_Start/10;    
							  KeyState=KEY_LIGHT;
						break;
						
						case 5:
							   KeyState=KEY_DATE;
						break;
						
						default:
								KeyState=KEY_WAIT;        
						
				}	
				
				Count_State++;
				if(Count_State==6)
						Count_State=0;
				
			}
		
			/*
			else if(ReadKey_Value!=0xff)//
       {
        ir_state=KEY_WAIT;        
       }
     Key_value=0xff;
			 */
				  
					switch(KeyState){
							case KEY_WAIT :	
								
							break;
							 
							case KEY_MAS_TIME :		
									Menue_Mastertime();            						
							break;

						
							case KEY_SUB_STATE :					 
									Menue_Substate(); 								
							break;
							case KEY_SUB_TIME :	                  						
									 Menue_Subtime();                  						
							break;
							
							
							case KEY_REPORT :           					
									Menue_Report();				    
							break;
							
							case KEY_LIGHT :				 
									Menue_Light();			    
							break;
							
							
							case KEY_DATE :	         						
									Menue_Date();			    			
							break;
							
							case KEY_RESET :
								   
											 
							break;
							/*
							case KEY_GPS :
									menue_time();
							break;
							case KEY_RESET :
									menue_rest();      
							break;
							default: KeyState=KEY_WAIT; 
							break; 
							*/					
					 }
					
		 
	 }
	 


 /*********************************
*功能:日期    显示“年月日”
*
*********************************/
void  Menue_Date(void)
 {  
    write_hd7279(DECODE0+0,p_timemu->day%10);
    write_hd7279(DECODE0+1,p_timemu->day/10);
    write_hd7279(DECODE0+2,p_timemu->month%10);
    write_hd7279(DECODE0+3,p_timemu->month/10);
    write_hd7279(DECODE0+4,p_timemu->year%10); 
    write_hd7279(DECODE0+5,p_timemu->year/10);
    write_hd7279(DECODE1+6,0x0d);
    write_hd7279(DECODE1+7,0x0d);
    if(ReadKey_Value==5 || ReadKey_Value==13){                   
        KeyState=KEY_WAIT; 
        Count_State=0;			
    }   
    ReadKey_Value=0xff;
 }
 
 
/*********************************
*功能:修改母钟时间
*
*********************************/
 void Menue_Mastertime(void){
	 
	 static INT8U circle;
	 INT8U   write[8],i;
   INT8U   temp_sec,temp_min,temp_hour;
	 INT32U     _ntp = 0; 
  OS_CPU_SR  cpu_sr;
	struct tm  now;
	
	 

	
	 
	 
	/*
	if(ReadKey_Value==15)  母钟时间   S1
	if(ReadKey_Value==7)    位选      S2
  if(ReadKey_Value==14) 	 +        S3	
  if(ReadKey_Value==6)     -        S4 
  if(ReadKey_Value==13)  取消功能   S5  
  if(ReadKey_Value==5){  功能确定   S6 	
	
	*/
   if(ReadKey_Value==7){  // 往右边移动，值以此为：0x3f  0xcf  0xf3   0xfc
					 if(Blink_Number<0xfc){//right
							Blink_Number>>=2;
							Blink_Number|=0xc0; 
					 }else 
							Blink_Number=0x3f;
   }else if(ReadKey_Value==14){      //+键
			 if(Blink_Number==0xfc){        //second       
				 Time_Modify[0]++; 
				 if(Time_Modify[0]>=10){   
					 Time_Modify[0]=0;
					 Time_Modify[1]++;
					 if(Time_Modify[1]>=6)
						 Time_Modify[1]=0;
					} 
      }else if(Blink_Number==0xf3){  //minute    
				 Time_Modify[2]++; 
				 if(Time_Modify[2]>=10){			
					 Time_Modify[2]=0;         
					 Time_Modify[3]++;
					 if(Time_Modify[3]>=6)
						Time_Modify[3]=0;
					} 
      }else if(Blink_Number==0xcf){    //hour       
				 if(Time_Modify[5]<2){		
					 Time_Modify[4]++;
					 if(Time_Modify[4]>9){
						 Time_Modify[4]=0;         
						 Time_Modify[5]++;           
					 }        
				 }else{       
					 Time_Modify[4]++;
					 if(Time_Modify[4]>3){			
						 Time_Modify[4]=0;         
						 Time_Modify[5]=0;           
					 }                
         } 
      }     
    }else if(ReadKey_Value==6){   //-键
			 if(Blink_Number==0xfc){       
				 Time_Modify[0]--; 
				 if(Time_Modify[0]>=10){  
					 Time_Modify[0]=9;         
					 Time_Modify[1]--;
					 if(Time_Modify[1]>=6)
						Time_Modify[1]=5;
					} 
      }else  if(Blink_Number==0xf3){      
				 Time_Modify[2]--; 
				 if(Time_Modify[2]>=10){		
					 Time_Modify[2]=9;         
					 Time_Modify[3]--;
					 if(Time_Modify[3]>=6)
						Time_Modify[3]=5;
					} 
      }else if(Blink_Number==0xcf){     
					 Time_Modify[4]--;
					 if(Time_Modify[4]>=10){	
						 Time_Modify[4]=9;         
						 Time_Modify[5]--;
						 if(Time_Modify[5]>=3){ 	
							 Time_Modify[5]=2;
							 Time_Modify[4]=3;
							}                  
						}      
			}      
    } 


	  write_hd7279(DECODE0+0,Time_Modify[0]);
    write_hd7279(DECODE0+1,Time_Modify[1]);   
    write_hd7279(DECODE0+2,Time_Modify[2]);
    write_hd7279(DECODE0+3,Time_Modify[3]);   
    write_hd7279(DECODE0+4,Time_Modify[4]);
    write_hd7279(DECODE0+5,Time_Modify[5]); 
    write_hd7279(DECODE1+6,0x0a);
    write_hd7279(DECODE1+7,0x0a);
    write_hd7279(BLINKCTL,Blink_Number); 
		 
		
		 
   
    if(ReadKey_Value==5){
				temp_sec=Time_Modify[0]+Time_Modify[1]*10;
				temp_min=Time_Modify[2]+Time_Modify[3]*10;
				temp_hour=Time_Modify[4]+Time_Modify[5]*10; 
				write[0]= temp_hour;write[1]=temp_min;write[2]=temp_sec;   
				
				//iic_sw_write(eep_chip_24cxx,iic_eeprom_east, &write[0], 3);  
			  //ds3231_tm_wr(_ntp);   //往DS3231里压入保存设置的时间！);	
			  //SetDs3231_Time(temp_hour,temp_min,temp_sec);
			
			  SetAndGet_clock_tm(write[0],write[1],write[2]);//都是  UTC   的时间，不必非要转换为北京时间，added by sjw
			
			
			  DelayMs(100);  
   			OS_ENTER_CRITICAL();		
			
			 	_ntp=ds3231_tm_rd();
			  to_tm(_ntp - JAN_1970, &now);
				p_timemu->hour=now.tm_hour;
				p_timemu->minute=now.tm_min;
				p_timemu->second=now.tm_sec;
				p_timemu->day=now.tm_mday;
				p_timemu->month=now.tm_mon;
				p_timemu->year=now.tm_year-2000;
				
			
			
				OS_EXIT_CRITICAL();	
				write_hd7279(BLINKCTL,0xff);//    
				Blink_Number=0x3f;     
				KeyState=KEY_WAIT; 
				Count_State=0;
        				
     }else if(ReadKey_Value==13){  
				write_hd7279(BLINKCTL,0xff);//
				Blink_Number=0x3f;
				KeyState=KEY_WAIT;
			  Count_State=0;
     }
     ReadKey_Value=0xff;
 }
 
 
 
 
 
//通过上位机发送  全日历时间(依照UTC格式保存！)  added by sjw
void  set_clock_tm(INT8U *tm)
{					
	
	 
	/*
	if(ReadKey_Value==15)  母钟时间   S1
	if(ReadKey_Value==7)    位选      S2
  if(ReadKey_Value==14) 	 +        S3	
  if(ReadKey_Value==6)     -        S4 
  if(ReadKey_Value==13)  取消功能   S5  
  if(ReadKey_Value==5){  功能确定   S6 	
	
	*/
	struct tm now;		 

 	now.tm_year	= tm[1]<<8 | tm[2];
	now.tm_mon 	= tm[3];
	now.tm_mday	= tm[4];	
	now.tm_hour	= tm[5];
	now.tm_min	= tm[6];  
	now.tm_sec 	= tm[7]; 	
	now.tm_wday	= tm[10];

   	NTP = mktimev(&now) + JAN_1970 - 3600*8;
	
	ds3231_tm_wr(NTP);
}

 
 
 
 
 /*********************************
*功能:子钟状态
*
*********************************/
 void  Menue_Substate(void){
 
	 config data;
	 
	/*
	if(ReadKey_Value==15)  母钟时间   S1
	if(ReadKey_Value==7)    位选      S2
  if(ReadKey_Value==14) 	 +        S3	
  if(ReadKey_Value==6)     -        S4 
  if(ReadKey_Value==13)  取消功能   S5  
  if(ReadKey_Value==5){  功能确定   S6 	
	
	*/
	 if(ReadKey_Value==7){  // 往右边移动，值以此为：0x3f  0xcf  0xf3   0xfc
					 if(Blink_Number<0xfc){//right
							Blink_Number>>=3;
							Blink_Number|=0xe0; 
					 }else 
							Blink_Number=0x3f;
					 
   }else if(ReadKey_Value==14){   //     +键
			 if(Blink_Number==0xfc){    //显示某一面子钟的状态！！added by sjw
					 
					 Subclock_State++;
					 if(Subclock_State>=5)      
							Subclock_State=0;
           				 
				}else if(Blink_Number==0xe7){ //子钟号   简单起见，操作一面子钟！！added by sjw   
					 #ifdef USE_MOTOR_ONE
						 Subclock_Number++;
						 if(Subclock_Number>=2) Subclock_Number=1;
					 #elif  defined  USE_MOTOR_TWO
						 Subclock_Number++;
						 if(Subclock_Number>=3) Subclock_Number=1;
					 #elif  defined USE_MOTOR_THREE
						 Subclock_Number++;
						 if(Subclock_Number>=4) Subclock_Number=1;
					 #else  
						 Subclock_Number++;
						 if(Subclock_Number>=5) Subclock_Number=1;
					 #endif
				}
		}else if(ReadKey_Value==6){   //   -键 
			 if(Blink_Number==0xfc){     
					 Subclock_State--;
					 if(Subclock_State>4)       
							Subclock_State=4;        
				}else if(Blink_Number==0xe7){ //子钟号
					 #ifdef USE_MOTOR_ONE
						 Subclock_Number--;
						 if(Subclock_Number<1 || Subclock_Number>1) Subclock_Number=1; 
					 #elif   USE_MOTOR_TWO
						 Subclock_Number--;
						 if(Subclock_Number<1 || Subclock_Number>2) Subclock_Number=2;
					 #elif   USE_MOTOR_THREE	 
						 Subclock_Number--;
						 if(Subclock_Number<1 || Subclock_Number>3) Subclock_Number=3; 
					 #else
					   Subclock_Number--;
						 if(Subclock_Number<1 || Subclock_Number>4) Subclock_Number=4;
           #endif					
				}       
    }
	 
		/*
    #ifdef USE_MOTOR_ONE
					 if(Blink_Number!=0xfc  &&  Subclock_Number==1) {//Subclock_Number是子钟号！！added by sjw
							 Subclock_State=Motor_State1;
					 }					 
    #elif   USE_MOTOR_TWO					 
					 if(Blink_Number!=0xfc&&Subclock_Number==2){
						 Subclock_State=Motor_State2;         
					 }
		#elif   USE_MOTOR_THREE			 		
					if(Blink_Number!=0xfc&&Subclock_Number==3){ 
						 Subclock_State=Motor_State3;          
					}
		#else	
					if(Blink_Number!=0xfc&&Subclock_Number==4){
						 Subclock_State=Motor_State4;       
					}
		#endif

*/





		
     
   write_hd7279(DECODE0+0,Subclock_State);
   write_hd7279(DECODE0+1,0x00);
   write_hd7279(DECODE0+2,0x0a); //
   write_hd7279(DECODE0+3,Subclock_Number);  
   write_hd7279(DECODE1+4,0x0f);  
   write_hd7279(DECODE0+5,0x0a);   
   write_hd7279(DECODE0+6,0x0b);  
   write_hd7279(DECODE0+7,0x0c); //   
   write_hd7279(BLINKCTL,Blink_Number);

   if(ReadKey_Value==5){ 
//SubclockChangeSta();	
		 
          #ifdef USE_MOTOR_ONE		 
					if(Subclock_Number==1 && Subclock1.warning==0){  
						 switch (Subclock_State){   
								 case 0 :
									  PowerOnFLag=0;
									  Key_Subclock_State1=WALK;        //正常1
								 break;
								 case 1 :
									  PowerOnFLag=1;
									  Key_Subclock_State1=RUN_FORWARD; //正追1面          
								 break;
								 case 2 :
									  PowerOnFLag=1;
									  Key_Subclock_State1=STOP;         //停1面
								 break;
								 case 3 :
									 PowerOnFLag=1;
									 Key_Subclock_State1=RUN_REVERSE; //倒追1面         
								 break;
								 case 4 :
									 Key_Subclock_State1=CALIB;       //1面校准针        
								 break;
								 
						}
						data.east_time[7]= Key_Subclock_State1;
						iic_sw_write(eep_chip_24cxx, iic_eeprom_east_sta, &data.east_time[7], 1);
            DelayMs(100);
						iic_sw_read(eep_chip_24cxx, iic_eeprom_east_sta, &board.east_time[7], 1);
						Key_Subclock_State1=board.east_time[7];
    						
						
					}
					
				  #elif  defined(USE_MOTOR_TWO)//此预定义下的指令不能执行，需要查找问题，已经将USE_MOTOR_TWO在Key.h中打开了！！added by sjw
					if(Subclock_Number==2 && Subclock2.warning==0){
							 switch (Subclock_State)
							 {
								 case 0 :
									 Key_Subclock_Order2=WALK;        //正常2
								 break;
								 case 1 :
									 Subclock_Order2=RUN_FORWARD; //正追2面          
								 break;
								 case 2 :
									 Subclock_Order2=STOP;        //停2面
								 break;
								 case 3 :
									 Subclock_Order2=RUN_REVERSE; //倒追2面          
								 break;
								 case 4 :
									Subclock_Order2=CALIB;        //2面校准针         
								 break;
								
								}
					} 
				  #elif   USE_MOTOR_THREE
					if(Subclock_Number==3 && Subclock2.warning==0){
						 switch (Subclock_State)
						 {
							 case 0 :
								 Subclock_Order3=WALK;        //正常3
							 break;
							 case 1 :
								 Subclock_Order3=RUN_FORWARD; //正追3面          
							 break;
							 case 2 :
								 Subclock_Order3=STOP;        //停3面
							 break;
							 case 3 :
								 Subclock_Order3=RUN_REVERSE; //倒追3面          
							 break;
							 case 4 :
								Subclock_Order3=CALIB;        //3面校准针         
							 break;
							  
							}
				} 
				#else
				if(Subclock_Number==4 && Subclock2.warning==0){
						 switch (Subclock_State)
						 {
							 case 0 :
								 Subclock_Order4=WALK;        //正常4
							 break;
							 case 1 :
								 Subclock_Order4=RUN_FORWARD; //正追4面          
							 break;
							 case 2 :
								 Subclock_Order4=STOP;        //停4面
							 break;
							 case 3 :
								 Subclock_Order4=RUN_REVERSE; //倒追4面          
							 break;
							 case 4 :
								Subclock_Order4=CALIB;        //4面校准针         
							 break;
							 
							}
				} 
				#endif
				
				
				
				write_hd7279(BLINKCTL,0xff);
				Blink_Number=0x3f;    
				KeyState=KEY_WAIT;
				Count_State=0;
    }else if(ReadKey_Value==13){
      write_hd7279(BLINKCTL,0xff);//
      Blink_Number=0x3f;
      KeyState=KEY_WAIT;
			Count_State=0;
    }
		ReadKey_Value=0xff;
 }

 
 
 /*********************************
*功能:设置子钟时间
*
*********************************/
void  Menue_Subtime(void){
 
  INT8U  i;
	
	
	 
	 
	/*
	if(ReadKey_Value==15)  母钟时间   S1
	if(ReadKey_Value==7)    位选      S2
  if(ReadKey_Value==14) 	 +        S3	
  if(ReadKey_Value==6)     -        S4 
  if(ReadKey_Value==13)  取消功能   S5  
  if(ReadKey_Value==5){  功能确定   S6 	
	
	*/
	 if(ReadKey_Value==7){  // 往右边移动，值以此为：0x3f  0xcf  0xf3   0xfc
					 if(Blink_Number<0xfc){//right
							Blink_Number>>=2;
							Blink_Number|=0xc0; 
					 }else 
							Blink_Number=0x3f;
					 
   }else if(ReadKey_Value==14){   //  +键
    
				 if(Blink_Number==0x3f){  //子钟号    
            #ifdef USE_MOTOR_ONE						 
							 Subclock_Number++;
							 if(Subclock_Number>1) Subclock_Number=1; 
					  #elif   USE_MOTOR_TWO
								Subclock_Number++;
							 if(Subclock_Number>2) Subclock_Number=1; 
					  #elif   USE_MOTOR_THREE
					      Subclock_Number++;
							 if(Subclock_Number>3) Subclock_Number=1; 
						#else
								Subclock_Number++;
							 if(Subclock_Number>4) Subclock_Number=1; 
					  #endif
					 
				 }else if(Blink_Number==0xcf){ //子钟 时				
						 if(Time_Modify[5]<1){
							 Time_Modify[4]++;
							 if(Time_Modify[4]>9){
								 Time_Modify[4]=0;         
								 Time_Modify[5]++;           
							 }        
						 }else{         
								 Time_Modify[4]++;
								 if(Time_Modify[4]>=2){   
									 Time_Modify[4]=0;         
									 Time_Modify[5]=0;           
								 }                
						 } 
				 }else if(Blink_Number==0xf3){ //子钟 分         
							 Time_Modify[2]++; 
							 if(Time_Modify[2]>=10){  
								 Time_Modify[2]=0;         
								 Time_Modify[3]++;
								 if(Time_Modify[3]>=6)
									Time_Modify[3]=0;
							 } 
				 }else if(Blink_Number==0xfc){ //子钟 秒        
							 Time_Modify[0]++; 
							 if(Time_Modify[0]>=10){	
								 Time_Modify[0]=0;         
								 Time_Modify[1]++;
								 if(Time_Modify[1]>=6)
									 Time_Modify[1]=0;
							 }
        }      
    }else if(ReadKey_Value==6){   //  -键
			 if(Blink_Number==0x3f){  //子钟号		
				    #ifdef USE_MOTOR_ONE	
						 
							 Subclock_Number--;
							 if(Subclock_Number<1 || Subclock_Number>1) Subclock_Number=1;  

						#elif   USE_MOTOR_TWO
							 Subclock_Number--;
							 if(Subclock_Number<1 || Subclock_Number>2) Subclock_Number=2;  
	 
				    #elif   USE_MOTOR_THREE
				       Subclock_Number--;
							 if(Subclock_Number<1 || Subclock_Number>3) Subclock_Number=3;  

			
				    #else
							 Subclock_Number--;
							 if(Subclock_Number<1 || Subclock_Number>4) Subclock_Number=4;  

				    #endif
				 
				 
				}else if(Blink_Number==0xcf){ //子钟 时
						 Time_Modify[4]--;
						 if(Time_Modify[4]>=10){
								Time_Modify[4]=9;         
								Time_Modify[5]--;
								if( Time_Modify[5]>=2){  
									Time_Modify[5]=1;
									Time_Modify[4]=1;
								 }                  
						 }         
				}else if(Blink_Number==0xf3){ //子钟 分         
						 Time_Modify[2]--; 
						 if(Time_Modify[2]>=10){
							 Time_Modify[2]=9;         
							 Time_Modify[3]--;
							 if(Time_Modify[3]>=6)
								Time_Modify[3]=5;
						 }        
        }else if(Blink_Number==0xfc){ //子钟 秒					
						 Time_Modify[0]--; 
						 if(Time_Modify[0]>=10){	
							 Time_Modify[0]=9;         
							 Time_Modify[1]--;
							 if(Time_Modify[1]>=6)
								 Time_Modify[1]=5;
						 }        
			  }     
    }
		
		
		
		
	
		

   if(Blink_Number==0x3f){  
		  
		  #ifdef USE_MOTOR_ONE	
      if(Subclock_Number==1){ 
/*				
          TimeStore[0]=board.east_time[2];
          TimeStore[1]=board.east_time[1];
          TimeStore[2]=board.east_time[0];
				*/
				 TimeStore[0]=p_timeslave->second;
				 TimeStore[1]=p_timeslave->minute;
				 TimeStore[2]=p_timeslave->hour;
      }
      #elif   USE_MOTOR_TWO
			if(Subclock_Number==2){    
          TimeStore[0]=board.south_time[2];
          TimeStore[1]=board.south_time[1];
          TimeStore[2]=board.south_time[0];
      }
      #elif   USE_MOTOR_THREE
			if(Subclock_Number==3){    
          TimeStore[0]=board.west_time[2];
          TimeStore[1]=board.west_time[1];
          TimeStore[2]=board.west_time[0];
      }
			#else
			if(Subclock_Number==4){    
          TimeStore[0]=board.north_time[2];
          TimeStore[1]=board.north_time[1];
          TimeStore[2]=board.north_time[0];
      }
      #endif			
      Time_Modify[0]=TimeStore[0]%10;
      Time_Modify[1]=TimeStore[0]/10;        
      Time_Modify[2]=TimeStore[1]%10;
      Time_Modify[3]=TimeStore[1]/10;        
      Time_Modify[4]=TimeStore[2]%10;
      Time_Modify[5]=TimeStore[2]/10;
   }else{
      TimeStore[0]=Time_Modify[0]+Time_Modify[1]*10;
      TimeStore[1]=Time_Modify[2]+Time_Modify[3]*10;
      TimeStore[2]=Time_Modify[4]+Time_Modify[5]*10;
   }
  
   for(i=0;i<6;i++)
     write_hd7279(DECODE0+i,Time_Modify[i]);   

   write_hd7279(DECODE0+6,Subclock_Number);  
   write_hd7279(DECODE1+7,0x0f);          
   write_hd7279(BLINKCTL,Blink_Number);

   if(ReadKey_Value==5){ 
		 #ifdef USE_MOTOR_ONE	
     if(Subclock_Number==1){  
         board.east_time[2]=Time_Modify[0]+Time_Modify[1]*10;
         board.east_time[1]=Time_Modify[2]+Time_Modify[3]*10;
         board.east_time[0]=Time_Modify[4]+Time_Modify[5]*10; 
			   iic_sw_write(eep_chip_24cxx, iic_eeprom_east, &board.east_time[0], 3);
			   DelayMs(100);
			   iic_sw_read(eep_chip_24cxx, iic_eeprom_east, &board.east_time[0], 8);
				 p_timeslave->hour=board.east_time[0];
			   p_timeslave->minute=board.east_time[1];
			   p_timeslave->second=board.east_time[2];
				
			 
      }
		 #elif   USE_MOTOR_TWO
  		if(Subclock_Number==2){
				 board.south_time[2]=Time_Modify[0]+Time_Modify[1]*10;
         board.south_time[1]=Time_Modify[2]+Time_Modify[3]*10;
         board.south_time[0]=Time_Modify[4]+Time_Modify[5]*10;
				 iic_sw_write(eep_chip_24cxx, iic_eeprom_south, &board.south_time[0], 3);
				  DelayMs(100);
			   iic_sw_read(eep_chip_24cxx, iic_eeprom_south, &board.south_time[0], 8);
			}
			#elif   USE_MOTOR_THREE
			if(Subclock_Number==3){
				 board.west_time[2]=Time_Modify[0]+Time_Modify[1]*10;
         board.west_time[1]=Time_Modify[2]+Time_Modify[3]*10;
         board.west_time[0]=Time_Modify[4]+Time_Modify[5]*10;	
				 iic_sw_write(eep_chip_24cxx, iic_eeprom_west, &board.west_time[0], 3);
				  DelayMs(100);
			   iic_sw_read(eep_chip_24cxx, iic_eeprom_west, &board.west_time[0], 8);
			}
			#elif   USE_MOTOR_FOUR
			if(Subclock_Number==4){
				 board.north_time[2]=Time_Modify[0]+Time_Modify[1]*10;
         board.north_time[1]=Time_Modify[2]+Time_Modify[3]*10;
         board.north_time[0]=Time_Modify[4]+Time_Modify[5]*10;
         iic_sw_write(eep_chip_24cxx, iic_eeprom_north, &board.north_time[0], 3);
          DelayMs(100);
			   iic_sw_read(eep_chip_24cxx, iic_eeprom_north, &board.north_time[0], 8);				
			}
			#endif
    
     write_hd7279(BLINKCTL,0xff);
     Blink_Number=0x3f;     
     KeyState=KEY_WAIT; 
     Count_State=0;			
   }else if(ReadKey_Value==13){ 
      write_hd7279(BLINKCTL,0xff);//
      Blink_Number=0x3f;
      KeyState=KEY_WAIT;
		  Count_State=0;
    }
    ReadKey_Value=0xff; 
 }


 /*********************************
*功能:报时时间
*
*********************************/
 
 
 void  Menue_Report(void){
	  OS_CPU_SR  cpu_sr;
	 INT8U temp,bs[2];
	 config data;
	/*
	if(ReadKey_Value==15)  母钟时间   S1
	if(ReadKey_Value==7)    位选      S2
  if(ReadKey_Value==14) 	 +        S3	
  if(ReadKey_Value==6)     -        S4 
  if(ReadKey_Value==13)  取消功能   S5  
  if(ReadKey_Value==5){  功能确定   S6 	
	
	*/
	 if(ReadKey_Value==7){  // 往右边移动，值以此为：0x3f  0xcf  0xf3   0xfc
					 if(Blink_Number<0xfc){//right
							Blink_Number>>=2;
							Blink_Number|=0xc0; 
					 }else 
							Blink_Number=0x3f;
					 
   }else if(ReadKey_Value==14){  // +   加按键      
    
     if(Blink_Number==0x3f){ //设置报时点的开关+每个点对应的前奏和钟声+特殊长时间的MP3文件！！added by sjw  
        Report_Order++;     //报时3端，开关+选择前奏及钟声+特殊MP3音乐长时段  added  by sjw
        if(Report_Order>3) 
					 Report_Order=1;
     }else if(Blink_Number==0xcf){ //特殊的长时间mp3歌曲！！added by  sjw
				if(Report_Order==3){  
						Report_Number++;       //共有5个自定义特殊报时的文件存在，added by sjw
						if(Report_Number>5) Report_Number=1;//此变量从1-------5共5个自定义的文件！！
				}					
     }else if(Blink_Number==0xf3){  //
        switch(Report_Order)
				{
					case 1:                   //报时开或者关！  added by sjw
						 if(Set_Time[1]<2){	 
								Set_Time[0]++;
								if(Set_Time[0]>9){					
								 Set_Time[0]=0;         
								 Set_Time[1]++;           
								}        
						 }else{	         
								Set_Time[0]++;
								if(Set_Time[0]>3){		
								 Set_Time[0]=0;         
								 Set_Time[1]=0;           
								}                
						 }
						 Report_Hour=Set_Time[0]+Set_Time[1]*10; 
						 Report_En=Report_Time[Report_Hour]+1; 
					break;
						 
					case 2://前奏可选择15个前奏和8个敲点声音！！added by sjw
							 if(Set_StrikeNumber[3]<1){
									Set_StrikeNumber[2]++;
									if(Set_StrikeNumber[2]>9){
										Set_StrikeNumber[2]=0;         
										Set_StrikeNumber[3]++;           
									}        
						   }else{        
									Set_StrikeNumber[2]++;
									if(Set_StrikeNumber[2]>=5){	
									  Set_StrikeNumber[2]=0;         
									  Set_StrikeNumber[3]=0;           
									}                
							 }
					break;
							 
					case  3://显示  PH 10 00 00  到   PH 14 00 00   added  by sjw
								Time_Modify[2]++; 
							  if(Time_Modify[2]>=10){
									 Time_Modify[2]=0;         
									 Time_Modify[3]++;
									 if(Time_Modify[3]>=6)
										Time_Modify[3]=0;
								}     
					break;
					
				}
			}else if(Blink_Number==0xfc){ //
				switch(Report_Order)
				{
						case  1:
							 if(Report_Order==1){  
									 Report_En++;
									 if(Report_En>2) 
											Report_En=1;
						   }
						break;
						
						case  2:		            //敲钟可选择  00-07共8钟钟声！！added by sjw
							  Set_StrikeNumber[0]++;
								if(Set_StrikeNumber[0]>7){		
										Set_StrikeNumber[0]=0;                  
								}        
								Set_StrikeNumber[1]=0;    
						break;
						
						
						case  3:
								Time_Modify[0]++; 
						    if(Time_Modify[0]>=10){
									 Time_Modify[0]=0;         
									 Time_Modify[1]++;
									 if(Time_Modify[1]>=6)
										Time_Modify[1]=0;
							  }
						break;
				}
				
			}
	}else if(ReadKey_Value==6){    //- 减按键 
			if(Blink_Number==0x3f){      
					 Report_Order--;       //报时3端，开关+选择前奏及钟声+特殊MP3音乐长时段  added  by sjw
					 if(Report_Order<1||Report_Order>3) 
						 Report_Order=3;
      }else if(Blink_Number==0xcf){
					if(Report_Order==3){ 
							Report_Number--;
							if(Report_Number<1 || Report_Number>5)//此变量从1-------5共5个自定义的文件！！ 
								Report_Number=5; //特殊时长的mp3   added  by sjw
					}							  
      }else if(Blink_Number==0xf3){  
					switch(Report_Order)
					{
						case 1:
								Set_Time[0]--;
								if(Set_Time[0]>=10){ 
										Set_Time[0]=9;         
										Set_Time[1]--;
										if(Set_Time[1]>=3){ 
											 Set_Time[1]=2;
											 Set_Time[0]=3;
									  }                  
								 }    
								 Report_Hour=Set_Time[0]+Set_Time[1]*10; 
								 Report_En=Report_Time[Report_Hour]+1;      						 
						break;
						case 2:
								 Set_StrikeNumber[2]--;
								 if(Set_StrikeNumber[2]>=10){	
										 Set_StrikeNumber[2]=9;         
										 Set_StrikeNumber[3]--;
										 if( Set_StrikeNumber[3]>=2){ 		 
												Set_StrikeNumber[3]=1;
												Set_StrikeNumber[2]=4;
										 }                  
								 }      
						break;
						case 3:
									 Time_Modify[2]--; 
									 if(Time_Modify[2]>=10){				
											Time_Modify[2]=9;         
											Time_Modify[3]--;
											if(Time_Modify[3]>=6)
													Time_Modify[3]=5;
									 }
						break;
						
					}
      }else if(Blink_Number==0xfc){  
					switch(Report_Order)       //报时功能键盘里面还有三个子菜单，对应 报时开关，报时前奏和敲点，外加自定义的音乐文件！！added by sjw
					{
						case 1:
									if(Report_Order==1){
											Report_En--;
											if(Report_En<1||Report_En>2) 
													Report_En=2;  
									}
						break;
						case 2:
									Set_StrikeNumber[0]--;
								  if(Set_StrikeNumber[0]>7){	
									 Set_StrikeNumber[0]=7;                                 
									} 
								  Set_StrikeNumber[1]=0;   
						break;
			
						case 3:
								 Time_Modify[0]--; 
								 if(Time_Modify[0]>=10){		
										Time_Modify[0]=9;         
										Time_Modify[1]--;
										if(Time_Modify[1]>=6)
											Time_Modify[1]=5;
								 }
						break;
						
				}
		}	
	}			
						 
    if(Blink_Number==0x3f){       
				if(Report_Order==2){   
							Set_StrikeNumber[0]=Strike_Number%10;
							Set_StrikeNumber[1]=Strike_Number/10;        
							Set_StrikeNumber[2]=Rythem_Number%10;
							Set_StrikeNumber[3]=Rythem_Number/10;
				 }else if(Report_Order==3){ 
							Time_Modify[0]=0;
							Time_Modify[1]=0;        
							Time_Modify[2]=0;
							Time_Modify[3]=0;   
				 }
     }
		
		 switch(Report_Order)		 
		 {
			 case 1:
					 if(Report_En==2){  
							write_hd7279(DECODE1+0,0x0e); //使能
							write_hd7279(DECODE1+1,0x0e);  
					 }else if(Report_En==1){ 
							write_hd7279(DECODE1+0,0x05);
							write_hd7279(DECODE1+1,0x0d); 
					 }   
					write_hd7279(DECODE0+2,Set_Time[0]);
					write_hd7279(DECODE0+3,Set_Time[1]);   
					write_hd7279(DECODE0+4,0x0a); 
					write_hd7279(DECODE0+5,0x0a);
					write_hd7279(DECODE0+6,0x0e);
					write_hd7279(DECODE0+7,0x0e);
			 break;
			 case 2:
					write_hd7279(DECODE0+0,Set_StrikeNumber[0]);
					write_hd7279(DECODE0+1,Set_StrikeNumber[1]);     
					write_hd7279(DECODE0+2,Set_StrikeNumber[2]);
					write_hd7279(DECODE0+3,Set_StrikeNumber[3]);
					write_hd7279(DECODE0+4,0x0a); 
					write_hd7279(DECODE0+5,0x0a);
					write_hd7279(DECODE1+6,0x0a);
					write_hd7279(DECODE0+7,0x0e);
			 break;
			 case 3:
					write_hd7279(DECODE0+0,Time_Modify[0]);
					write_hd7279(DECODE0+1,Time_Modify[1]);     
					write_hd7279(DECODE0+2,Time_Modify[2]);
					write_hd7279(DECODE0+3,Time_Modify[3]);
					write_hd7279(DECODE0+4,Report_Number-1); //此变量从1-------5共5个自定义的文件！！ 
					write_hd7279(DECODE0+5,0x01);
					write_hd7279(DECODE0+6,0x0c);
					write_hd7279(DECODE0+7,0x0e);
			 break;
		 }             
    write_hd7279(BLINKCTL,Blink_Number); 
		 
		 
		 
    if(ReadKey_Value==5){ 
			 switch(Report_Order)
			 {
				 case 1://报时时间点存储起始地址，24个字节!!
							  //写入24个小时报时开关与否   于AT24C02
							Report_Hour=Set_Time[0]+Set_Time[1]*10;           
							if(Report_Hour<24){ 
								 if(Report_En==2)      
										Report_Time[Report_Hour]=1;
								 else if(Report_En==1) 
										Report_Time[Report_Hour]=0; 

								 
								 temp=Report_Time[Report_Hour];
								 // Eeprom_WriteWord(DATA_START+REPORT_ADDR+Report_hour*2,(unsigned int)Report_time[Report_hour]);//
							
								 OS_ENTER_CRITICAL();
                 iic_sw_write(eep_chip_24cxx,  iic_eeprom_bspower0_7+Report_Hour, &temp, 1);
								 OS_EXIT_CRITICAL();	
                 DelayMs(100);
								
								 OS_ENTER_CRITICAL();
								 iic_sw_read(eep_chip_24cxx,  iic_eeprom_bspower0_7+Report_Hour, &temp, 1);
								 OS_EXIT_CRITICAL();
                 Report_Time[Report_Hour]=temp;								 
              }     
       
				 break;
				 
				 case 2:
							//报时音乐、钟声号 
							if((Set_StrikeNumber[2]+Set_StrikeNumber[3]*10)<15)       //前奏有15个文件可以选择！  added by sjw
								Rythem_Number=Set_StrikeNumber[2]+Set_StrikeNumber[3]*10;
							if((Set_StrikeNumber[0]+Set_StrikeNumber[1]*10)<8)        //敲点有8个文件可以选择！   added by sjw
								Strike_Number=Set_StrikeNumber[0]+Set_StrikeNumber[1]*10;
							 
							bs[0]=Rythem_Number;
							bs[1]=Strike_Number;
              iic_sw_write(eep_chip_24cxx,  iic_eeprom_bsrythem, bs, 2);//iic_eeprom_bsrythem 和 iic_eeprom_bsknock两个字节里保存！added by sjw
							DelayMs(100);
							iic_sw_read(eep_chip_24cxx, iic_eeprom_bsrythem, bs, 2);
              Rythem_Number=bs[0];
							Strike_Number=bs[1];
							
							//Eeprom_WriteWord(DATA_START+SONG_ADDR,(unsigned int) (Songs_nummber));
							//Eeprom_WriteWord(DATA_START+STRIKE_ADDR,(unsigned int) (Strike_nummmber));        
						
				 break;
				 
				 
				 case 3:
							 //报时音乐长度         此功能以备将来使用，added by sjw
							if((Time_Modify[2]+Time_Modify[3]*10)<5){ 
								Rythem_Minite[Report_Number+9]=Time_Modify[2]+Time_Modify[3]*10;
								Rythem_Second[Report_Number+9]=Time_Modify[0]+Time_Modify[1]*10;
								//Eeprom_WriteWord(DATA_START+LONG_ADDR+(Report_nummber-1)*2,(unsigned int) (Songs_minite[Report_nummber+9]));
								//Eeprom_WriteWord(DATA_START+LONG_ADDR+0x10+(Report_nummber-1)*2,(unsigned int) (Songs_second[Report_nummber+9]));   
							}        					 
				 break;
			}   
      write_hd7279(BLINKCTL,0xff);  
      Blink_Number=0x3f;     
      KeyState=KEY_WAIT; 
      Count_State=0;			 
     }else if(ReadKey_Value==13){ 
				write_hd7279(BLINKCTL,0xff);
				Blink_Number=0x3f;
				KeyState=KEY_WAIT;
			  Count_State=0;
     }
		 ReadKey_Value=0xff;
 }

 
/*********************************
*功能:照明
*
*********************************/
 
 
 	
 void  Menue_Light(void){
	 INT8U data[2];
 
//Set_Time[4]
		 
	/*
	if(ReadKey_Value==15)  母钟时间   S1
	if(ReadKey_Value==7)    位选      S2
  if(ReadKey_Value==14) 	 +        S3	
  if(ReadKey_Value==6)     -        S4 
  if(ReadKey_Value==13)  取消功能   S5  
  if(ReadKey_Value==5){  功能确定   S6 	
	
	*/
	 if(ReadKey_Value==7){  // 往右边移动，依此为：0x3f  0xcf  0xf3   0xfc
					 if(Blink_Number<0xfc){//right
							Blink_Number>>=2;
							Blink_Number|=0xc0; 
					 }else 
							Blink_Number=0x3f;
					 
   }else if(ReadKey_Value==14){  //+  加按键            
     if(Blink_Number==0xcf){
       Subclock_Order++;
       if(Subclock_Order>=3) Subclock_Order=1;
     }
     if(Blink_Number==0xf3){  //照明起始时间
      
       if(Set_Time[3]<2){  
         Set_Time[2]++;
         if(Set_Time[2]>9){  
           Set_Time[2]=0;         
           Set_Time[3]++;           
         }        
       }else{        
         Set_Time[2]++;
         if(Set_Time[2]>3){  
           Set_Time[2]=0;         
           Set_Time[3]=0;           
         }                
       } 
     }else if(Blink_Number==0xfc){ //照明结束时间    
       if(Set_Time[1]<2){ 
         Set_Time[0]++;
         if(Set_Time[0]>9)
          {
           Set_Time[0]=0;         
           Set_Time[1]++;           
          }        
       }else{         
         Set_Time[0]++;
         if(Set_Time[0]>3){  
           Set_Time[0]=0;         
           Set_Time[1]=0;           
         }                
       } 
     }     
   }else if(ReadKey_Value==6){    //- 减按键 
        
     if(Blink_Number==0xcf){ 
       Subclock_Order--;
       if(Subclock_Order<1||Subclock_Order>2) Subclock_Order=2;
     }else if(Blink_Number==0xf3){  //照明起始时间
				 Set_Time[2]--;
				 if(Set_Time[2]>=10){
					 Set_Time[2]=9;         
					 Set_Time[3]--;
					 if( Set_Time[3]>=10){ 	
						 Set_Time[3]=2;
						 Set_Time[2]=3;
					 }                  
				 } 
     }else if(Blink_Number==0xfc){//照明结束时间
				 Set_Time[0]--;
				 if(Set_Time[0]>=10){
					 Set_Time[0]=9;         
					 Set_Time[1]--;
					 if( Set_Time[1]>=3){ 
						
						 Set_Time[1]=2;
						 Set_Time[0]=3;
					 }                  
				 }
		 }         
   }   
   write_hd7279(DECODE0+0,Set_Time[0]);
   write_hd7279(DECODE0+1,Set_Time[1]);    
   write_hd7279(DECODE0+2,Set_Time[2]);
   write_hd7279(DECODE0+3,Set_Time[3]);     
   if(Subclock_Order==2){
     write_hd7279(DECODE1+4,0x0e); //使能
     write_hd7279(DECODE1+5,0x0e);  
   }else if(Subclock_Order==1){
     write_hd7279(DECODE1+4,0x05); //禁止
     write_hd7279(DECODE1+5,0x0d); 
    } 
    write_hd7279(DECODE0+6,0x0d);
    write_hd7279(DECODE0+7,0x0d);       
    write_hd7279(BLINKCTL,Blink_Number); 
		
		
		
    if(ReadKey_Value==5){      
				Light_End=Set_Time[0]+Set_Time[1]*10;
				Light_Start=Set_Time[2]+Set_Time[3]*10;
			
				if(Subclock_Order==2)      
						Light_En=1;
				else if(Subclock_Order==1) 
						Light_En=0;  
				//Eeprom_WriteWord(DATA_START+LIGHT_ADDR,(unsigned int) (Light_start));  
				//Eeprom_WriteWord(DATA_START+LIGHT_ADDR+0x02,(unsigned int) (Light_end));
				//Eeprom_WriteWord(DATA_START+LIGHT_ADDR+0x04,(unsigned int) (Light_en)); 
        data[0]=Light_Start;
				data[1]=Light_End;
				
			  iic_sw_write(eep_chip_24cxx, iic_eeprom_zmpower_on, data, 2);
				DelayMs(50);
				iic_sw_read(eep_chip_24cxx, iic_eeprom_zmpower_on, data, 2);
				Light_Start=data[0];
				Light_End=data[1];

				write_hd7279(BLINKCTL,0xff);    
				Blink_Number=0x3f;       
				KeyState=KEY_WAIT;
				Count_State=0;
    }else if(ReadKey_Value==13){ 
      write_hd7279(BLINKCTL,0xff);//
      Blink_Number=0x3f;
      KeyState=KEY_WAIT;
			Count_State=0;
    }
    ReadKey_Value=0xff;
 }

 
 /***********************************
*功能：向寄存器写入一字节
*输入：寄存器地址、待写数据     功能：将时间写入RTC
***********************************/
void SetDs3231_Time(INT8U hour,INT8U min,INT8U sec)
 {
	 INT8U data=8,temp;
	 
	 
	 
	 
	temp= HEX_to_BCD(sec);
  iic_sw_write(eep_chip_ds3231,0x00,&temp,1);
	DelayMs(100); 
	
	temp=HEX_to_BCD(min);
  iic_sw_write(eep_chip_ds3231,0x01,&temp,1);
	DelayMs(100);  
	 
	 
	temp=HEX_to_BCD(hour); 
  iic_sw_write(eep_chip_ds3231,0x02,&temp,1);
	DelayMs(100);  
	 
  
	 temp=HEX_to_BCD(p_timemu->day);
	 iic_sw_write(eep_chip_ds3231,0x04,&temp,1);
	 DelayMs(100); 
	 
	 
	 
	 temp=HEX_to_BCD(p_timemu->month);
   iic_sw_write(eep_chip_ds3231,0x05,&temp,1);
	 DelayMs(100); 
	
	
	 temp=HEX_to_BCD(p_timemu->year);
   iic_sw_write(eep_chip_ds3231,0x06,&temp,1);
	 DelayMs(100); 
	
	
   iic_sw_write(eep_chip_ds3231,0x0f,&data,1);
   DelayMs(100);   
 }


 
 
void SetAndGet_clock_tm(INT8U hour,INT8U min,INT8U sec)
{
 	
  mytime 		*p_data;
  uint8_t tx[8],temp1,temp2,temp3,data1,data2,data3, init = 0x40;	 
	INT32U     _ntp = 0; 

	struct tm after,before;

	
	
	
	_ntp=ds3231_tm_rd();
	to_tm(_ntp - JAN_1970, &before); 
	
	data1=before.tm_mday;
	data2=before.tm_mon;
	data3=before.tm_year-2000;
	
	
	

	to_tm(NTP - JAN_1970, &after);//NTP转换为当前UTC的时间！！added by sjw

	tx[0] = dec2bcd(sec);		  
	tx[1] = dec2bcd(min);		  
	tx[2] = dec2bcd(hour);
	tx[3] = dec2bcd(after.tm_wday);
	//tx[4] = dec2bcd(after.tm_mday);
	//tx[5] = dec2bcd(after.tm_mon);
	//tx[6] = dec2bcd(after.tm_year%100);	
  tx[4] = dec2bcd(data1);
	tx[5] = dec2bcd(data2);
	tx[6] = dec2bcd(data3);


	
	iic_sw_write(I2C_SALVEID_DS3231, DS3231_REG_CONTROL, &init, 1); 
		 
	iic_sw_write(I2C_SALVEID_DS3231, DS3231_REG_SECOND, tx, 7);
	
	
	
	
}			  
 
 
 

