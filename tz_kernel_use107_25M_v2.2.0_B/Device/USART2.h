

#ifndef __USART2_H
#define __USART2_H


#include "..\App\includes.h"
#define 	USART2_RX_CNT 	      10	 						// ���廷�������С������ʵ�������Ӧ����10

void USART2_RXLoop(INT8U temp);     //   ��temp���뻷�����飬�����жϵ���
void USART2_Init(INT32U baud);      //   ��ʼ��USART2��baudΪ������
INT8U USART2_GetByte(INT8U *temp);  //   �ӻ�������ȡһ���ֽ�
void USART2_SendByte(INT8U temp);   //   ����һ���ֽ�
void USART2_Printf(INT8U *pch);     //   ��ӡ�ַ���

#endif


