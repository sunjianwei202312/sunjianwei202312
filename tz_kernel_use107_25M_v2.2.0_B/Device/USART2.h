

#ifndef __USART2_H
#define __USART2_H


#include "..\App\includes.h"
#define 	USART2_RX_CNT 	      10	 						// 定义环形数组大小，根据实际情况相应增减10

void USART2_RXLoop(INT8U temp);     //   将temp放入环形数组，接收中断调用
void USART2_Init(INT32U baud);      //   初始化USART2，baud为波特率
INT8U USART2_GetByte(INT8U *temp);  //   从环形数组取一个字节
void USART2_SendByte(INT8U temp);   //   发送一个字节
void USART2_Printf(INT8U *pch);     //   打印字符串

#endif


