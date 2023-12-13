/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_int.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Endpoint CTR (Low and High) interrupt's service routines

    STM32的USB模块可以产生三种中断：USB唤醒中断、USB高优先级中断和USB低优先级中断，
在STM32的参考手册中没有详细说明这三种中断对应哪些事件，现说明如下：

   1）USB唤醒中断：在中断向量表中的位置是42。这个中断在USB设备从暂停模式唤醒时产生，
      唤醒事件由USB_ISTR寄存器的WKUP位标识。

   2）USB高优先级中断：在中断向量表中的位置是19。这个中断仅由USB同步(Isochronous)
      模式传输或双缓冲块(Bulk)传输模式下的正确传输事件产生，正确传输事件由USB_ISTR
	  寄存器的CTR位标识。

   3）USB低优先级中断：在中断向量表中的位置是20。这个中断由所有其它的USB事件产生，
      例如正确传输(不包括同步模式和双缓冲块模式)、USB复位等，事件标志位在USB_ISTR寄存
	  器中。

usb_int.c一看就知道跟中断相关。在该文件中定义了两个函数，分别为低优先级的端点正确传输中断服务程序CTR_LP()和高优先级端点正确传输的中断服务程序CTR_HP()。
在我们的CUstomHID函数中，只用到CTR_LP()函数。该函数中在usb_istr.c中的USB_istr()函数中被调用。
CTR就是正确传输，只有检测到ISTR寄存器中的CTR位置位后，才会调用CTR_LP()函数。
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include ".\USBLIB\inc\usb_lib.h"
#include "usb_lib.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u16 SaveRState;
u16 SaveTState;

/* Extern variables ----------------------------------------------------------*/
extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void);   /*  Handles OUT interrupts   */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : CTR_LP.
* Description    : Low priority Endpoint Correct Transfer interrupt's service
*                  routine.
                   低优先级的正确传输端点中断服务程序
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
//主机在建立过程最后收到ACK以后，发送IN令牌包，从而进入到数据过程。
//在CTR_LP()函数中判断是IN0中断后，进入In0_Process()函数。在数据过程将之前填在USB缓冲器的设备描述符发给主机，并等待主机的应答。added by sjw

//void CTR_LP(void)此函数的解释观看此网站，不错写的！
//https://blog.csdn.net/u011318735/article/details/17424659

/*

主机进入控制传输的第一阶段：建立事务、发送setup令牌包、发送请求数据包、设备发送ACK包。
    主机对地址0、端点0发出SETUP令牌包，首先端点0寄存器的第11位SETUP位置位，表明收到了setup令牌包。
    由于此时端点0数据接收有效，所以接下来主机的请求数据包被SIE保存到端点0描述符表的RxADDR里面，收到的字节数保存到RxCount里面。
    端点0寄存器的CTR_RX被置位为1，ISTR的CTR置位为1，DIR=1，EP_ID=0，表示端点0
    接收到主机来的请求数据。此时设备已经ACK主机，将触发正确传输完成中断，
————————————————
版权声明：本文为CSDN博主「sz189981」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/sz189981/article/details/68962138
*/
void CTR_LP(void)//低优先级的端点正确传输中断服务程序
{
  u32 wEPVal = 0;
  /* stay in loop while pending ints */
  while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)//在等待中断时保持循环状态
  {
    _SetISTR((u16)CLR_CTR); /* clear CTR flag */
    /* extract highest priority endpoint number */
	//获取端点标识符
    EPindex = (u8)(wIstr & ISTR_EP_ID);//这句是读取端点号，下面分端点是否为0展开  获取指针传输针对的端点号
	//控制端点处理 ---------------------------------------
    if (EPindex == 0)	 //如果是端点0
    {
      /* Decode and service control endpoint interrupt */
      /* calling related service routine */
      /* (Setup0_Process, In0_Process, Out0_Process) */

      /* save RX & TX status */
      /* and set both to NAK */
      SaveRState = _GetEPRxStatus(ENDP0);//save RX & TX status and set both to NAK：保存端点0状态，原本是有效状态
      SaveTState = _GetEPTxStatus(ENDP0);
      _SetEPRxStatus(ENDP0, EP_RX_NAK);
      _SetEPTxStatus(ENDP0, EP_TX_NAK);/*在本次数据处理好之前，对主机发来的数据包以NAK回应*/


      /* DIR bit = origin of the interrupt */

      if ((wIstr & ISTR_DIR) == 0)		//端点0输入中断  //获取方向标志，如果是0表示主机要“IN”数据  如果是IN令牌包，数据被取走
      {
        /* DIR = 0 */

        /* DIR = 0      => IN  int */
        /* DIR = 0 implies that (EP_CTR_TX = 1) always  */
        _ClearEP_CTR_TX(ENDP0);		//清除端点0的输入完成中断标志   /*清除传输完成标志*/
        In0_Process();				    //发送剩余字节数
           /* before terminate set Tx & Rx status */
				_SetEPRxStatus(ENDP0, SaveRState);
				_SetEPTxStatus(ENDP0, SaveTState); /* before terminate set Tx & Rx status */
				return;
      }else	{					              //端点0输出中断  //方向标志为1，有两种情况，可能是主机要“OUT”也可能是在“SETUP”   
        /* DIR = 1 */

        /* DIR = 1 & CTR_RX       => SETUP or OUT int */
        /* DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending */

        wEPVal = _GetENDPOINT(ENDP0);	 //读端点寄存器    //获取端点0的状态
        if ((wEPVal & EP_CTR_TX) != 0)  
        {
          _ClearEP_CTR_TX(ENDP0);
          In0_Process();
          /* before terminate set Tx & Rx status */
          _SetEPRxStatus(ENDP0, SaveRState);
          _SetEPTxStatus(ENDP0, SaveTState);
          return;
        }
        else if ((wEPVal & EP_SETUP) != 0)	 //如果是建立包  //在被主机setup
        {
          _ClearEP_CTR_RX(ENDP0); /* SETUP bit kept frozen while CTR_RX = 1 */  /* SETUP bit kept frozen while CTR_RX = 1 ：*/
          Setup0_Process();			  //建立包处理   //主要是调用该程序来处理主机请求
          /* before terminate set Tx & Rx status */
          _SetEPRxStatus(ENDP0, SaveRState);
          _SetEPTxStatus(ENDP0, SaveTState);
          return;
        }

        else if ((wEPVal & EP_CTR_RX) != 0)		//普通数据输出  //主机在out
        {  
          _ClearEP_CTR_RX(ENDP0);           /* clear int flag：清除接收端点0标志 */
          Out0_Process();                   //调用此函数
          /* before terminate set Tx & Rx status */
          _SetEPRxStatus(ENDP0, SaveRState);
          _SetEPTxStatus(ENDP0, SaveTState);
          return;
        }
      }
    }/* if(EPindex == 0) */

	//非控制端点处理 -------------------------------
    else	 //否则就是是端点1～7   在mass storage中非控制端点只有EP1 and  EP2
    {
      /* Decode and service non control endpoints interrupt  */

      /* process related endpoint register */
      wEPVal = _GetENDPOINT(EPindex);
      if ((wEPVal & EP_CTR_RX) != 0)     //设备接收完成
      {
        /* clear int flag */
        _ClearEP_CTR_RX(EPindex);

        /* call OUT service function */
        (*pEpInt_OUT[EPindex-1])();		   //端点*(1~7)输出

      } /* if((wEPVal & EP_CTR_RX) */

      if ((wEPVal & EP_CTR_TX) != 0)    //设备发送完成
      {
        /* clear int flag */
        _ClearEP_CTR_TX(EPindex);

        /* call IN service function */
        (*pEpInt_IN[EPindex-1])();	      //端点*(1~7)输入
      } /* if((wEPVal & EP_CTR_TX) != 0) */

    }/* if(EPindex == 0) else */

  }/* while(...) */
}

/*******************************************************************************
* Function Name  : CTR_HP.
* Description    : High Priority Endpoint Correct Transfer interrupt's service 
*                  routine.
                   高优先级的正确传输端点中断服务例程
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CTR_HP(void)
{
  u32 wEPVal = 0;

  while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
  {
    _SetISTR((u16)CLR_CTR); /* clear CTR flag */
    /* extract highest priority endpoint number */
    EPindex = (u8)(wIstr & ISTR_EP_ID);
    /* process related endpoint register */
    wEPVal = _GetENDPOINT(EPindex);
    if ((wEPVal & EP_CTR_RX) != 0)
    {
      /* clear int flag */
      _ClearEP_CTR_RX(EPindex);

      /* call OUT service function */
      (*pEpInt_OUT[EPindex-1])();

    } /* if((wEPVal & EP_CTR_RX) */
    else if ((wEPVal & EP_CTR_TX) != 0)
    {
      /* clear int flag */
      _ClearEP_CTR_TX(EPindex);

      /* call IN service function */
      (*pEpInt_IN[EPindex-1])();


    } /* if((wEPVal & EP_CTR_TX) != 0) */

  }/* while(...) */
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
