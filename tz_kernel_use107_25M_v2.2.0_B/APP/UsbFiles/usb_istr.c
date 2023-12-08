/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_istr.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : ISTR events interrupt service routines
                       usb中断处理函数
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
//这里的mass storage 只用了三个端点  ：端点0，端点1、端点2
void (*pEpInt_IN[7])(void) =
  {
    EP1_IN_Callback,	  //端点1输入回调函数
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
    EP2_OUT_Callback,	   //端点2输出回调函数
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
  };


/*******************************************************************************
* Function Name  : USB_Istr
* Description    : ISTR events interrupt service routine
                   ISTR事件中断服务程序
                
				   USB中断事件分为如下几种：
				   void ISTR_CTR(void);    正确的传输
				   void ISTR_SOF(void);	   帧首标志
				   void ISTR_ESOF(void);   期望帧首标志
				   void ISTR_DOVR(void); 
				   void ISTR_ERROR(void);  出错
				   void ISTR_RESET(void);  USB复位请求
				   void ISTR_WAKEUP(void); 	唤醒
				   void ISTR_SUSPEND(void);	 挂起请求
				   这些处理函数使能由定义IMR_MSK决定
				   #define IMR_MSK (CNTR_CTRM  | CNTR_RESETM)

* Input          : None.
* Output         : None.
* Return         : None.

https://blog.csdn.net/pq113_6/article/details/106197926
added by sjw
基于STM32F103的USB学习笔记15 - USB中断处理
STM32F103的USB中断状态寄存器(USB_ISTR)有8个类型的中断，这8个中断都会让MCU产生一个USB_LP_CAN1_RX0_IRQHandler中断，
这8个中断源的标志位于ISTR寄存器的高8bit，定义如下：

15     14    13   12   11   10   9   8    7   6   5     4       3 2 1 0
CTR  pmaovr  ERR wkup susp  rst sot esof rcv           DIR     EP_ID[3:0]



*******************************************************************************/
void USB_Istr(void)
{

  wIstr = _GetISTR();		//获取中断状态（读USB中断状态寄存器） 读取中断状态寄存器(ISTR)的值

#if (IMR_MSK & ISTR_RESET)	//复位(RESET)中断标志
  if (wIstr & ISTR_RESET & wInterrupt_Mask)//读出的中断标志是RESET中断标志，且RESET中断使能了
  {
    _SetISTR((u16)CLR_RESET);	 //清除标志//清除RESET中断标志
    Device_Property.Reset();//调用复位函数
#ifdef RESET_CALLBACK      //当定义了RESET_CALLBACK，则调用RESET_CALLBACK,像钩子函数一样，在发生RESET中断时做点什么
    RESET_Callback();
#endif
  }
#endif
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_DOVR)
  if (wIstr & ISTR_DOVR & wInterrupt_Mask)//读出的中断标志是DOVR中断标志，且DOVR中断使能了
  {
    _SetISTR((u16)CLR_DOVR);//分组缓冲区溢出(DOVR)中断标志  //清除DOVR中断标志
#ifdef DOVR_CALLBACK//当定义了DOVR_CALLBACK，则调用DOVR_Callback,像钩子函数一样，在发生DOVR中断时做点什么
    DOVR_Callback();
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_ERR)//错误(ERR)中断标志
  if (wIstr & ISTR_ERR & wInterrupt_Mask)//读出的中断标志是ERR中断标志，且ERR中断使能了
  {
    _SetISTR((u16)CLR_ERR);//清除ERR中断标志
#ifdef ERR_CALLBACK
    ERR_Callback();/当定义了ERR_CALLBACK，则调用ERR_Callback,像钩子函数一样，在发生ERR中断时做点什么
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_WKUP)//唤醒(WKUP)中断标志
  if (wIstr & ISTR_WKUP & wInterrupt_Mask)//读出的中断标志是WKUP中断标志，且WKUP中断使能了
  {
    _SetISTR((u16)CLR_WKUP);//清除ERR中断标志
    Resume(RESUME_EXTERNAL);//调用唤醒函数
#ifdef WKUP_CALLBACK//当定义了WKUP_CALLBACK，则调用WKUP_Callback,像钩子函数一样，在发生WKUP中断时做点什么
    WKUP_Callback();
#endif
  }
#endif
	
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_SUSP)//挂起(SUSP)中断标志
  if (wIstr & ISTR_SUSP & wInterrupt_Mask)//读出的中断标志是SUSP中断标志，且SUSP中断使能了
  {

    /* check if SUSPEND is possible */
    if (fSuspendEnabled)//检查是否可以可以挂起
    {
      Suspend();//如果可以挂起，则调用挂起函数
    }
    else
    {
      /* if not possible then resume after xx ms */
      Resume(RESUME_LATER);//如果不可以挂起，则在xx ms后恢复
    }
    /* clear of the ISTR bit must be done after setting of CNTR_FSUSP */
    _SetISTR((u16)CLR_SUSP);//清除SUSP中断标志
#ifdef SUSP_CALLBACK//当定义了SUSP_CALLBACK，则调用SUSP_Callback,像钩子函数一样，在发生SUSP中断时做点什么
    SUSP_Callback();
#endif
  }
#endif
	
	
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_SOF)//帧首(SOF)中断标志
  if (wIstr & ISTR_SOF & wInterrupt_Mask)//读出的中断标志是SOF中断标志，且SOF中断使能了
  {
    _SetISTR((u16)CLR_SOF);//清除SOF中断标志
    bIntPackSOF++;//统计共接收到多少SOF

#ifdef SOF_CALLBACK//当定义了SOF_CALLBACK，则调用SOF_Callback,像钩子函数一样，在发生SOF中断时做点什么
    SOF_Callback();
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_ESOF)//期望帧首(ESOF)中断标志，当没有收到期望的SOF帧首是触发中断
  if (wIstr & ISTR_ESOF & wInterrupt_Mask)//读出的中断标志是ESOF中断标志，且ESOF中断使能了
  {
    _SetISTR((u16)CLR_ESOF);//清除ESOF中断标志
    /* resume handling timing is made with ESOFs */
    Resume(RESUME_ESOF); /* request without change of the machine state *///恢复ESOF的处理时间

#ifdef ESOF_CALLBACK
    ESOF_Callback();//当定义了ESOF_CALLBACK，则调用ESOF_Callback像钩子函数一样，在发生ESOF中断时做点什么
#endif
  }
#endif
	
	
	
	
	
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & ISTR_CTR)					//正确的传输  //正确传输中断CTR标志
  if (wIstr & ISTR_CTR & wInterrupt_Mask)
  {
    /* servicing of the endpoint correct transfer interrupt */
    /* clear of the CTR flag into the sub */
    CTR_LP();//调用正确传输中断服务程序
#ifdef CTR_CALLBACK
    CTR_Callback();//当定义了CTR_CALLBACK，则调用CTR_Callback,像钩子函数一样，在发生CRT中断时做点什么  adde by sjw
#endif
  }
#endif
} /* USB_Istr */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

