#include "stm32f10x_lib.h"
#include "os_cpu.h"

#ifndef _HD7279_H_
#define _HD7279_H_


#define Set7279CS(x) 			(x ? GPIO_SetBits(GPIOE,GPIO_Pin_7):GPIO_ResetBits(GPIOE,GPIO_Pin_7))
 		

#define Set7279CLK(x)			(x ? GPIO_SetBits(GPIOE,GPIO_Pin_9):GPIO_ResetBits(GPIOE,GPIO_Pin_9))
	

#define Set7279DATA(x) 		(x ? GPIO_SetBits(GPIOE,GPIO_Pin_8):GPIO_ResetBits(GPIOE,GPIO_Pin_8))



#define Get7279DATA()  		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)
#define Get7279KEY()  		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)


//****************************************************************
//****************************************************************
//****************************************************************
//****************************************************************



//****** HD7279A 指令 ****************************


#define CMD_RESET 	0xa4        	//复位
#define CMD_TEST 		0xbf         	//测试
#define DECODE0 		0x80          // 下载数据方式0译码
#define DECODE1 		0xc8           //下载数据方式1译码
#define CMD_READ 		0x15        	 // 读键盘
#define UNDECODE 		0x90         	 //下载数据但不译码
#define RTL_CYCLE 	0xa3        	 // 循环左移   （数据不变）
#define RTR_CYCLE 	0xa2        	 //循环右移
#define RTL_UNCYL 	0xa1        	 //左移       （空位为0）
#define RTR_UNCYL 	0xa0        	 //右移
#define ACTCTL 			0x98           //消隐
#define SEGON 			0xe0           //段点亮
#define SEGOFF 			0xc0           //段关闭
#define BLINKCTL		0x88           //闪烁控制       （0闪/1不闪）

#define TEST        0x55




 //7279A控制命令字//


#define CS_7279  _RB12   //使能引脚位
#define KEY_INT  _RB15   //


void 			Hd7279_Init(void);
void 			long_delay(void);    		      //      长延时
void 			short_delay(void);    	      //     短延时
void 			write7279(INT8U, INT8U);     	//写入到 HD7279
INT8U 		read_hd7279(INT8U);		        //从 HD7279读出
void 			SendByteToHd7279(INT8U);  		  // 发送一个字节
INT8U 		receive_byte(void); 		      // 接收一个字节
void 			_nop_(void) ;
void      Menue_Mastertime(void);
void      Menue_Substate(void);
void      Menue_Subtime(void);
void      Menue_Report(void);
 void     Menue_Light(void);
 void     Menue_Date(void);


#define       USE_COMPANY_TZ_DIS



void 			Display(void);

#endif
