/*
*********************************************************************************************************
*	                                  
*	ģ������ : USB Mass������ص�Ӳ�����á�
*	�ļ����� : usb_hw.c
*	��    �� : V1.0
*	˵    �� : USBӲ���豸�����ӿ�
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		v1.0    2011-05-13 armfly  ST�̼���V3.5.0�汾��
*
*	Copyright (C), 2010-2011, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "usb_hw.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_lib.h"
#include "mass_mal.h"
#include "stm32f10x.h"


static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);


/*
*********************************************************************************************************
*	�� �� ��: MAL_Config
*	����˵��: MAL������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MAL_Config(void)
{
//	//MAL_Init(0);	/* ����SD�� */
//	MAL_Init(1);	/* ����NAND Flash */
	
	MAL_Init(1);//added by sjw
	
}

/*
*********************************************************************************************************
*	�� �� ��: InitUsbDev
*	����˵��: ��ʼ��USB��ص�Ӳ���豸
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void UsbDevInit(void)
{	
	USB_Disconnect_Config();/* ���ÿ���USB���ӺͶϿ���GPIO */

	MAL_Config();			      /* MAL configuration */

	Set_USBClock();			    /* ����USBʱ�� */
	USB_Interrupts_Config();/* ����USB�ж� */
	USB_Init();				      /* ��ʼ��USB�豸, �˺��������UsbConnect()����USB�豸��USB���� */
	
}



///*
//*********************************************************************************************************
//*	�� �� ��: Led_RW_ON
//*	����˵��: ������дָʾ��
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void Led_RW_ON(void)
//{
//	bsp_LedOn(3);
//}



///*
//*********************************************************************************************************
//*	�� �� ��: Led_RW_ON
//*	����˵��: �رն�дָʾ��
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void Led_RW_OFF(void)
//{
//	bsp_LedOff(3);
//}






///*
//*********************************************************************************************************
//*	�� �� ��: USB_Configured_LED
//*	����˵��: ����USB�豸���ӳɹ�ָʾ��
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void USB_Configured_LED(void)
//{
//	bsp_LedOn(1);
//}



///*
//*********************************************************************************************************
//*	�� �� ��: USB_NotConfigured_LED
//*	����˵��: �ر�USB�豸���ӳɹ�ָʾ��
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void USB_NotConfigured_LED(void)
//{
//	bsp_LedOff(1);
//}



///*
//*********************************************************************************************************
//*	�� �� ��: Get_SerialNum
//*	����˵��: �������ںź�������
//*	��    �Σ���
//*	�� �� ֵ: �������(���账��)
//*********************************************************************************************************
//*/
//void Get_SerialNum(void)
//{
//	uint32_t Device_Serial0, Device_Serial1, Device_Serial2;
//	
//	Device_Serial0 = *(__IO uint32_t*)(0x1FFFF7E8);
//	Device_Serial1 = *(__IO uint32_t*)(0x1FFFF7EC);
//	Device_Serial2 = *(__IO uint32_t*)(0x1FFFF7F0);
//	
//	Device_Serial0 += Device_Serial2;
//	
//	if (Device_Serial0 != 0)
//	{
//		IntToUnicode (Device_Serial0, &MASS_StringSerial[2] , 8);
//		IntToUnicode (Device_Serial1, &MASS_StringSerial[18], 4);
//	}
//}





///*
//*********************************************************************************************************
//*	�� �� ��: USB_Cable_Config
//*	����˵��: ��������USB�������ӻ�Ͽ�
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void USB_Cable_Config (uint8_t NewState)
//{
//	/* ������������ʹ��PB14����USB���������������衣PB14=0��USB�������ӵ����� */
//	if (NewState != DISABLE)
//	{
//		GPIO_ResetBits(GPIOB, GPIO_Pin_14);	
//	}
//	else
//	{
//		GPIO_SetBits(GPIOB, GPIO_Pin_14);
//	}
//}

///*
//*********************************************************************************************************
//*	�� �� ��: Enter_LowPowerMode
//*	����˵��: ���������ģʽʱ�ر�ϵͳʱ�Ӻ͵�Դ
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void Enter_LowPowerMode(void)
//{
//	/* �����豸״̬Ϊ������ */
//	bDeviceState = SUSPENDED;
//}




///*
//*********************************************************************************************************
//*	�� �� ��: Leave_LowPowerMode
//*	����˵��: ���˳�����ģʽʱ�ָ�ϵͳʱ�Ӻ͵�Դ
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void Leave_LowPowerMode(void)
//{	
//	DEVICE_INFO *pInfo = &Device_Info;
//	
//	/* �����豸״̬ */
//	if (pInfo->Current_Configuration != 0)
//	{
//		/* �豸���ӵ����������óɹ� */
//		bDeviceState = CONFIGURED;
//	}
//	else
//	{
//		bDeviceState = ATTACHED;
//	}
//}




/*
*********************************************************************************************************
*	�� �� ��: USB_Interrupts_Config
*	����˵��: ����USB�ж�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/



 void USB_Interrupts_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	
	
	//NVIC_InitStructure.NVIC_IRQChannel =USB_LP_CAN_RX0_IRQChannel;//CAN_RX1_IRQChannel ; //CAN�ж���Ƕ��������ж� 

	
	/*
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;//USB_LP_CAN_RX0_IRQHandler;//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;//USB_HP_CAN_TX_IRQHandler;//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	*/
	
//	
//		
//	NVIC_InitStructure.NVIC_IRQChannel =USBWakeUp_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	
	
	

//  	/* ����SDIO�ж� */
//  	{		  
//		NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//	}
//	
	
	
	
	
}







/*
*********************************************************************************************************
*	�� �� ��: IntToUnicode
*	����˵��: ��һ��32λ��HEXֵת��ΪUnicode�����ʽ���ַ���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
	uint8_t idx = 0;
	
	for( idx = 0 ; idx < len ; idx ++)
	{
		if( ((value >> 28)) < 0xA )
		{
			pbuf[ 2* idx] = (value >> 28) + '0';
		}
		else
		{
			pbuf[2* idx] = (value >> 28) + 'A' - 10; 
		}
		
		value = value << 4;
		
		pbuf[ 2* idx + 1] = 0;
	}
}
