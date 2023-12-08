

#ifndef __USART1_H
#define __USART1_H


#include "..\App\includes.h"
#define 	 USART1_RX_CNT 		     7  		  // 定义环形数组大小，根据实际情况相应增减

void unpack_usart(void);


void USART1_RXLoop(INT8U temp);     //   将temp放入环形数组，接收中断调用
void USART1_Init(INT32U baud);      //   初始化USART1，baud为波特率
INT8U USART1_GetByte(INT8U *temp);  //   从环形数组取一个字节
void USART1_SendByte(INT8U temp);   //   发送一个字节
void USART1_Printf(INT8U *pch);     //   打印字符串

#endif


