
/* Includes ------------------------------------------------------------------*/

#include "hw_config.h"
#include "mass_mal.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "sdcard.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/********************************************************************
函数功能：系统初始化
入口参数：无。
返    回：无。
备    注：
            设置系统时钟
			初始化各外设时钟
			打开需要用的外设
			中断设置
			配制IO引脚，定义IO功能
			初始化存储器
			初始化USB
********************************************************************/
/*
void System_Init(void)
{

  // RCC configuration 
  RCC_Config();		             //与时钟相关的寄存器配制
  //IO配制 ------------------
  USB_Disconnect_Config();	   //USB软连接断开控制引脚
  SPI_Configuration();
    // nand configuration 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);	//使能
  //初始化NAND


	//2FSMC_NAND_Init();	// 初始化FSMC ,我在函数 已经有了，就不需要初始化了！added by sjw
				
	
  SD_Init();

  Set_USBClock();   //设置USB时钟
  
  USB_Interrupts_Config();	//USB中断配制
  //USB_Init();

  
}

*/



/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable.
                  软件连接断开USB电缆 
* Input          : None.
* Return         : Status
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    GPIO_SetBits(USB_CONNECT, USB_CONNECT_PIN);	  //连接USB
  }
  else
  {
    GPIO_ResetBits(USB_CONNECT, USB_CONNECT_PIN);	  //断开USB
  }
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
  /* USBCLK = PLLCLK */
 // RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);	 //USB时钟为PLL时钟除以1.5	为48MHz

  /* Enable USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/********************************************************************
函数功能：USB中断配制
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/

/*
void USB_Interrupts_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  // Set the Vector Table base location at 0x20000000 
//  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
  // Set the Vector Table base location at 0x08000000 
  //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);	   //中断向量表为FLASH

  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	//配置优先级组：优先级和子优先级.

	
	
  //NVIC_InitStructure.NVIC_IRQChannel =USB_LP_CAN_RX0_IRQChannel;  //USB低优先级中断
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQHandler; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	  //设置优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//设置从优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN_TX_IRQChannel;  //STM32F407
	 NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN_TX_IRQHandler;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQChannel;  //cancel by sjw
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	

}
*/


/********************************************************************
函数功能：USB软连接断开控制 IO引脚配制
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
void USB_Disconnect_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable USB_DISCONNECT GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CONNECT, ENABLE);

  /* USB_DISCONNECT_PIN used as USB pull-up */
  GPIO_InitStructure.GPIO_Pin = USB_CONNECT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//chaned by sjw from x_Out_OD to X_PP

  GPIO_Init(USB_CONNECT, &GPIO_InitStructure);
}



/********************************************************************
函数功能：LED IO引脚配制
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
void Led_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable USB_LED_PORT clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_LED, ENABLE);	  //LED所在IO口时钟使能
	
  /* Configure USB_LED_PORT pin6, pin7, pin8 and pin9 as output push-pull */
  //PF6：LED1   USB枚举成功
  //PF7：LED2
  //PF8：LED3	读写LED
  //PF9：LED4
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;	   //选中管脚6,7,8
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口输出最高频率为50MHz
  GPIO_Init(USB_LED_PORT, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }

}


/*******************************************************************************
* Function Name  : Led_RW_ON
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_RW_ON(void)
{
  GPIO_SetBits(USB_LED_PORT, USB_LED_PIN);	 //IO输出高电平，LED点亮
}

/*******************************************************************************
* Function Name  : Led_RW_OFF
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_RW_OFF(void)
{
  GPIO_ResetBits(USB_LED_PORT, USB_LED_PIN);
}
/*******************************************************************************
* Function Name  : USB_Configured_LED
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Configured_LED(void)
{
  GPIO_SetBits(USB_LED_PORT, USB_LED_PIN);	  
}

/*******************************************************************************
* Function Name  : USB_NotConfigured_LED
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_NotConfigured_LED(void)
{
  GPIO_ResetBits(USB_LED_PORT, USB_LED_PIN);
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  u32 Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(vu32*)(0x1FFFF7E8);	//96位的芯片身份证号码，只读
  Device_Serial1 = *(vu32*)(0x1FFFF7EC);
  Device_Serial2 = *(vu32*)(0x1FFFF7F0);

  if (Device_Serial0 != 0)
  {
    MASS_StringSerial[2] = (u8)(Device_Serial0 & 0x000000FF);
    MASS_StringSerial[4] = (u8)((Device_Serial0 & 0x0000FF00) >> 8);
    MASS_StringSerial[6] = (u8)((Device_Serial0 & 0x00FF0000) >> 16);
    MASS_StringSerial[8] = (u8)((Device_Serial0 & 0xFF000000) >> 24);

    MASS_StringSerial[10] = (u8)(Device_Serial1 & 0x000000FF);
    MASS_StringSerial[12] = (u8)((Device_Serial1 & 0x0000FF00) >> 8);
    MASS_StringSerial[14] = (u8)((Device_Serial1 & 0x00FF0000) >> 16);
    MASS_StringSerial[16] = (u8)((Device_Serial1 & 0xFF000000) >> 24);

    MASS_StringSerial[18] = (u8)(Device_Serial2 & 0x000000FF);
    MASS_StringSerial[20] = (u8)((Device_Serial2 & 0x0000FF00) >> 8);
    MASS_StringSerial[22] = (u8)((Device_Serial2 & 0x00FF0000) >> 16);
    MASS_StringSerial[24] = (u8)((Device_Serial2 & 0xFF000000) >> 24);
  }
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
