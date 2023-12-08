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



//****** HD7279A ָ�� ****************************


#define CMD_RESET 	0xa4        	//��λ
#define CMD_TEST 		0xbf         	//����
#define DECODE0 		0x80          // �������ݷ�ʽ0����
#define DECODE1 		0xc8           //�������ݷ�ʽ1����
#define CMD_READ 		0x15        	 // ������
#define UNDECODE 		0x90         	 //�������ݵ�������
#define RTL_CYCLE 	0xa3        	 // ѭ������   �����ݲ��䣩
#define RTR_CYCLE 	0xa2        	 //ѭ������
#define RTL_UNCYL 	0xa1        	 //����       ����λΪ0��
#define RTR_UNCYL 	0xa0        	 //����
#define ACTCTL 			0x98           //����
#define SEGON 			0xe0           //�ε���
#define SEGOFF 			0xc0           //�ιر�
#define BLINKCTL		0x88           //��˸����       ��0��/1������

#define TEST        0x55




 //7279A����������//


#define CS_7279  _RB12   //ʹ������λ
#define KEY_INT  _RB15   //


void 			Hd7279_Init(void);
void 			long_delay(void);    		      //      ����ʱ
void 			short_delay(void);    	      //     ����ʱ
void 			write7279(INT8U, INT8U);     	//д�뵽 HD7279
INT8U 		read_hd7279(INT8U);		        //�� HD7279����
void 			SendByteToHd7279(INT8U);  		  // ����һ���ֽ�
INT8U 		receive_byte(void); 		      // ����һ���ֽ�
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
