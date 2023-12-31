/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_init.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Initialization routines & global variables
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*  The number of current endpoint, it will be used to specify an endpoint */
 u8	EPindex;
/*  The number of current device, it is an index to the Device_Table */
/* u8	Device_no; */
/*  Points to the DEVICE_INFO structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_INFO *pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_PROP *pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
u16	SaveState ;
u16  wInterrupt_Mask;
DEVICE_INFO	Device_Info;
USER_STANDARD_REQUESTS  *pUser_Standard_Requests;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : USB_Init
* Description    : USB system initialization
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
/*
从代码中可以看到，首先是注册了一个Device_Info结构体给USB，这个结构体保存着USB的各项信息，接着设置控制状态为IN_DATA，
USB初始化只有在这个状态才能接受主机发送过来的命令，接下去注册函数常用的一些函数及标准请求，最后执行注册过的初始化函数。
*/
void USB_Init(void)
{
  pInformation = &Device_Info;//注册设备信息结构体
  pInformation->ControlState = 2;//控制状态为IN_DATA
  pProperty = &Device_Property;//注册设备的常用一些函数结构体
  pUser_Standard_Requests = &User_Standard_Requests;
  /* Initialize devices one by one */
  pProperty->Init();//注册初始化函数
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
