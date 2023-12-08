/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_istr.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : ISTR events interrupt service routines
                       usb�жϴ�����
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_type.h"
#include "usb_regs.h"
#include "usb_pwr.h"
#include "usb_istr.h"
#include "usb_init.h"
#include "usb_int.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile u16 wIstr;  /* ISTR register last read value */
volatile u8 bIntPackSOF = 0;  /* SOFs received between 2 consecutive packets */

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* function pointers to non-control endpoints service routines */
//�����mass storage ֻ���������˵�  ���˵�0���˵�1���˵�2
void (*pEpInt_IN[7])(void) =
  {
    EP1_IN_Callback,	  //�˵�1����ص�����
    EP2_IN_Callback,
    EP3_IN_Callback,
    EP4_IN_Callback,
    EP5_IN_Callback,
    EP6_IN_Callback,
    EP7_IN_Callback,
  };

void (*pEpInt_OUT[7])(void) =
  {
    EP1_OUT_Callback,
    EP2_OUT_Callback,	   //�˵�2����ص�����
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
  };


/*******************************************************************************
* Function Name  : USB_Istr
* Description    : ISTR events interrupt service routine
                   ISTR�¼��жϷ������
                
				   USB�ж��¼���Ϊ���¼��֣�
				   void ISTR_CTR(void);    ��ȷ�Ĵ���
				   void ISTR_SOF(void);	   ֡�ױ�־
				   void ISTR_ESOF(void);   ����֡�ױ�־
				   void ISTR_DOVR(void); 
				   void ISTR_ERROR(void);  ����
				   void ISTR_RESET(void);  USB��λ����
				   void ISTR_WAKEUP(void); 	����
				   void ISTR_SUSPEND(void);	 ��������
				   ��Щ������ʹ���ɶ���IMR_MSK����
				   #define IMR_MSK (CNTR_CTRM  | CNTR_RESETM)

* Input          : None.
* Output         : None.
* Return         : None.

https://blog.csdn.net/pq113_6/article/details/106197926
added by sjw
����STM32F103��USBѧϰ�ʼ�15 - USB�жϴ���
STM32F103��USB�ж�״̬�Ĵ���(USB_ISTR)��8�����͵��жϣ���8���ж϶�����MCU����һ��USB_LP_CAN1_RX0_IRQHandler�жϣ�
��8���ж�Դ�ı�־λ��ISTR�Ĵ����ĸ�8bit���������£�

15     14    13   12   11   10   9   8    7   6   5     4       3 2 1 0
CTR  pmaovr  ERR wkup susp  rst sot esof rcv           DIR     EP_ID[3:0]



*******************************************************************************/
void USB_Istr(void)
{

  wIstr = _GetISTR();		//��ȡ�ж�״̬����USB�ж�״̬�Ĵ����� ��ȡ�ж�״̬�Ĵ���(ISTR)��ֵ

#if (IMR_MSK & ISTR_RESET)	//��λ(RESET)�жϱ�־
  if (wIstr & ISTR_RESET & wInterrupt_Mask)//�������жϱ�־��RESET�жϱ�־����RESET�ж�ʹ����
  {
    _SetISTR((u16)CLR_RESET);	 //�����־//���RESET�жϱ�־
    Device_Property.Reset();//���ø�λ����
#ifdef RESET_CALLBACK      //��������RESET_CALLBACK�������RESET_CALLBACK,���Ӻ���һ�����ڷ���RESET�ж�ʱ����ʲô
    RESET_Callback();
#endif
  }
#endif
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_DOVR)
  if (wIstr & ISTR_DOVR & wInterrupt_Mask)//�������жϱ�־��DOVR�жϱ�־����DOVR�ж�ʹ����
  {
    _SetISTR((u16)CLR_DOVR);//���黺�������(DOVR)�жϱ�־  //���DOVR�жϱ�־
#ifdef DOVR_CALLBACK//��������DOVR_CALLBACK�������DOVR_Callback,���Ӻ���һ�����ڷ���DOVR�ж�ʱ����ʲô
    DOVR_Callback();
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_ERR)//����(ERR)�жϱ�־
  if (wIstr & ISTR_ERR & wInterrupt_Mask)//�������жϱ�־��ERR�жϱ�־����ERR�ж�ʹ����
  {
    _SetISTR((u16)CLR_ERR);//���ERR�жϱ�־
#ifdef ERR_CALLBACK
    ERR_Callback();/��������ERR_CALLBACK�������ERR_Callback,���Ӻ���һ�����ڷ���ERR�ж�ʱ����ʲô
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_WKUP)//����(WKUP)�жϱ�־
  if (wIstr & ISTR_WKUP & wInterrupt_Mask)//�������жϱ�־��WKUP�жϱ�־����WKUP�ж�ʹ����
  {
    _SetISTR((u16)CLR_WKUP);//���ERR�жϱ�־
    Resume(RESUME_EXTERNAL);//���û��Ѻ���
#ifdef WKUP_CALLBACK//��������WKUP_CALLBACK�������WKUP_Callback,���Ӻ���һ�����ڷ���WKUP�ж�ʱ����ʲô
    WKUP_Callback();
#endif
  }
#endif
	
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_SUSP)//����(SUSP)�жϱ�־
  if (wIstr & ISTR_SUSP & wInterrupt_Mask)//�������жϱ�־��SUSP�жϱ�־����SUSP�ж�ʹ����
  {

    /* check if SUSPEND is possible */
    if (fSuspendEnabled)//����Ƿ���Կ��Թ���
    {
      Suspend();//������Թ�������ù�����
    }
    else
    {
      /* if not possible then resume after xx ms */
      Resume(RESUME_LATER);//��������Թ�������xx ms��ָ�
    }
    /* clear of the ISTR bit must be done after setting of CNTR_FSUSP */
    _SetISTR((u16)CLR_SUSP);//���SUSP�жϱ�־
#ifdef SUSP_CALLBACK//��������SUSP_CALLBACK�������SUSP_Callback,���Ӻ���һ�����ڷ���SUSP�ж�ʱ����ʲô
    SUSP_Callback();
#endif
  }
#endif
	
	
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_SOF)//֡��(SOF)�жϱ�־
  if (wIstr & ISTR_SOF & wInterrupt_Mask)//�������жϱ�־��SOF�жϱ�־����SOF�ж�ʹ����
  {
    _SetISTR((u16)CLR_SOF);//���SOF�жϱ�־
    bIntPackSOF++;//ͳ�ƹ����յ�����SOF

#ifdef SOF_CALLBACK//��������SOF_CALLBACK�������SOF_Callback,���Ӻ���һ�����ڷ���SOF�ж�ʱ����ʲô
    SOF_Callback();
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_ESOF)//����֡��(ESOF)�жϱ�־����û���յ�������SOF֡���Ǵ����ж�
  if (wIstr & ISTR_ESOF & wInterrupt_Mask)//�������жϱ�־��ESOF�жϱ�־����ESOF�ж�ʹ����
  {
    _SetISTR((u16)CLR_ESOF);//���ESOF�жϱ�־
    /* resume handling timing is made with ESOFs */
    Resume(RESUME_ESOF); /* request without change of the machine state *///�ָ�ESOF�Ĵ���ʱ��

#ifdef ESOF_CALLBACK
    ESOF_Callback();//��������ESOF_CALLBACK�������ESOF_Callback���Ӻ���һ�����ڷ���ESOF�ж�ʱ����ʲô
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_CTR)					//��ȷ�Ĵ���  //��ȷ�����ж�CTR��־
  if (wIstr & ISTR_CTR & wInterrupt_Mask)
  {
    /* servicing of the endpoint correct transfer interrupt */
    /* clear of the CTR flag into the sub */
    CTR_LP();//������ȷ�����жϷ������
#ifdef CTR_CALLBACK
    CTR_Callback();//��������CTR_CALLBACK�������CTR_Callback,���Ӻ���һ�����ڷ���CRT�ж�ʱ����ʲô  adde by sjw
#endif
  }
#endif
} /* USB_Istr */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

