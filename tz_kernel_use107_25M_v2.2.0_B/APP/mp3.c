#include <stm32f10x.h>
#include "gps.h"
#include "ds3231.h"	
#include "uart.h"
#include "mp3.h"




const INT8U   Volume[6]={0x24,0x03,0x0F,0x01,0x1F,0x12};                       //MP3音量设置


      INT8U   Mp3data[18]={0x24,0x0F,0x04,0x01,0x0C,0x4D,0x50,0x33,0x5F,       //播放MP3指定文件
                           0x30,0x30,0x30,0x32,
			                     0x2E,0x4D,0x50,0x33,0x74};

													 
													 
INT8U  Set_Time[4];
INT8U  Set_StrikeNumber[4];                    //报时音乐号、钟声号缓存		
													 
													 
extern INT8U  Rythem_Number,Strike_Number;     //报时音乐号，钟声号	


	
										 
const INT8U Rythem_Name[15]={62, 60, 61, 63, 69,  //已经将前奏65变为“平安夜”的mp3了    平安夜前奏
                            68, 67, 64, 65, 66,
                            121,122,123,124,125
                            };                    //MP3文件序列号

INT16U Strike_Head[8]={200,212,224,236,248,260,272,284};








INT8U  Rythem_Minite[15]=   { 0,  0,  0,  1,  1,  
                              1,  0,  0,  0,  0,
                              3,  3,  3,  3,  3
		                        };                  //MP3文件播放时间长度 分

														 
														 
INT8U  Rythem_Second[15]=   {51, 47, 46, 1,  49,  
                             21, 49, 28, 28, 26,   //平安夜第8个由25秒钟变为28秒钟,西敏寺由第9个25秒钟变为26秒钟   added by sjw
                             59, 59, 59, 59, 59
		                        };                   //MP3播放时间长度  秒




void mp3play(INT16U nummber){
  INT8U  i,num_store[4];
	OS_CPU_SR  	cpu_sr;
  
		
		if(nummber<10000){ //
			num_store[0]=nummber/1000;
			num_store[1]=(nummber-num_store[0]*1000)/100;
			num_store[2]=(nummber-num_store[0]*1000-num_store[1]*100)/10;
			num_store[3]=nummber%10;
			
		  if(num_store[0]<10&&num_store[1]<10&&num_store[2]<10&&num_store[3]<10){
						
						Mp3data[9]= num_store[0]+0x30;
						Mp3data[10]=num_store[1]+0x30; 
						Mp3data[11]=num_store[2]+0x30;  
						Mp3data[12]=num_store[3]+0x30;  

						Mp3data[17]=0x00;
						for(i=1;i<17;i++)
							Mp3data[17]=Mp3data[17]^Mp3data[i];
						
				    OS_ENTER_CRITICAL();
						for(i=0;i<18;i++){
							USART_SendData(USART2,Mp3data[i]); //连续发送三次
							while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );	
						}
						for(i=0;i<18;i++){
							USART_SendData(USART2,Mp3data[i]); //连续发送三次
							while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );	
						}
						for(i=0;i<18;i++){
							USART_SendData(USART2,Mp3data[i]); //连续发送三次
							while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );	
						}
						OS_EXIT_CRITICAL();
		}
	}
}


/*********************************
*功能：设置MP3模块音量为最大
*输入：无
*********************************/

void mp3_volume(void){
 
  INT8U i;   
  for(i=0;i<6;i++){
			USART_SendData(USART2,Volume[i]);
			while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );	
	}
 
}



