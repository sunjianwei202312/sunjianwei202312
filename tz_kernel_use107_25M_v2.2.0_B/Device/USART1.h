

#ifndef __USART1_H
#define __USART1_H


#include "..\App\includes.h"
#define 	 USART1_RX_CNT 		     7  		  // ���廷�������С������ʵ�������Ӧ����

void unpack_usart(void);


void USART1_RXLoop(INT8U temp);     //   ��temp���뻷�����飬�����жϵ���
void USART1_Init(INT32U baud);      //   ��ʼ��USART1��baudΪ������
INT8U USART1_GetByte(INT8U *temp);  //   �ӻ�������ȡһ���ֽ�
void USART1_SendByte(INT8U temp);   //   ����һ���ֽ�
void USART1_Printf(INT8U *pch);     //   ��ӡ�ַ���

#endif


