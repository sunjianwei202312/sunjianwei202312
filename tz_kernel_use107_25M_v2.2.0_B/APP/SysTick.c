/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名  ：SysTick.c
 * 描述    ：SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
 *           常用的有 1us 10us 1ms 中断。         
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |                 |
 *          |      无         |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.0.0
 *
 * 作者    ：fire  QQ: 313303034 
 * 博客    ：firestm32.blog.chinaunix.net
**********************************************************************************/


#include "SysTick.h"

static __IO u32 TimingDelay;

/*
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用 
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(72000000 / 100000))
  { 
    /* Capture error */ 
    while (1);
  }
}


/*
 * 函数名：Delay_us
 * 描述  ：us延时程序,10us为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  ：Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
 *       : Delay_us( 50000 ) 则实现的延时为 500ms
 *       ：外部调用 
 */

void Delay_us(__IO u32 nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


/*
 * 函数名：TimingDelay_Decrement
 * 描述  ：获取节拍程序
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在 SysTick 中断函数 SysTick_Handler()调用
 */  
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/******************* (C) COPYRIGHT 2011 野火嵌入式开发工作室 *****END OF FILE****/
