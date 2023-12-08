
#include "bsp.h"
#include  "stm32f10x_rcc.h"
/***********************************************************************

	 外设时钟使能

************************************************************************/
void RCC_Configuration(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | 
						             RCC_APB2Periph_GPIOD  | RCC_APB2Periph_GPIOE | 
	                       RCC_APB2Periph_GPIOF,ENABLE);//| RCC_APB2Periph_SPI1调试的时候，我先将SPI功能关闭！added by sjw
	
	 //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_SPI2, ENABLE);//| RCC_APB1Periph_SPI2调试的时候，我先将SPI功能关闭！added by sjw
}



/*******************************************************************************

        全部中断在此配置

*******************************************************************************/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef 	NVIC_InitStructure;
   
	/* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    //更新事件 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //响应优先级2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断 
	NVIC_Init(&NVIC_InitStructure);  
	  
	
	
	
	// Enable the USART1 Interrupt 
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应优先级0 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//允许中断 
	NVIC_Init(&NVIC_InitStructure);

		
	NVIC_InitStructure.NVIC_IRQChannel =  USART2_IRQn;    	//更新事件 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    	//响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       	//允许中断 
	NVIC_Init(&NVIC_InitStructure);
	


  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_Init(&NVIC_InitStructure);
	*/
	//因为OS_TICKS_PER_SEC=40000对应系统25us中断一次！负荷太重，只能将其升级为最高级中断！
	//系统心脏滴答中断为最低级中断，退出后执行任务切换  
	//NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick,1,7);

}

/*******************************************************************************

       初始化 uCOS 滴答时钟

*******************************************************************************/
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;


    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

	  SysTick_Config(cnts);
}	  



////SystemFrequency 
// void SysTick_Config(void){
//    RCC_ClocksTypeDef  rcc_clocks; //RCC_ClocksTypeDef    rcc时钟类型定义结构！
//    u32  cnts;
//	
//		//当你使用外部晶振做为系统时钟的时候，而且外部晶振不是标准8MHz的时候，你需要留意一下STM32的固件库，里面的stm32f10x_rcc.c这个文件
//    RCC_GetClocksFreq(&rcc_clocks);	//72m?
//    cnts = (u32)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;
// 
////这里大家一定要注意，必须使得当前寄存器的值VAL等于0！SysTick->VAL  = (0x00);只有当VAL值为0时，计数器自动重载RELOAD。
////接下来就可以直接调用Delay();函数进行延迟了。延迟函数的实现中，要注意的是，全局变量TimingDelay必须使用volatile，否则可能会被编译器优化。
//    SysTick_SetReload(cnts);//调用SysTick_SetReload()                                --设置SysTick重装载值。
//    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//调用SysTick_CLKSourceConfig()  --设置SysTick时钟源。
//    SysTick_CounterCmd(SysTick_Counter_Enable);//调用SysTick_CounterCmd()            --使能SysTick计数器
//	SysTick_ITConfig(ENABLE);	//调用SysTick_ITConfig()                               --使能SysTick中断
//}	 

		








/*
********************************************************************************
** 函数名称 ： TIM1_Config(void)
** 函数功能 ： 定时器1初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/  



//通用定时器x中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz

void TIM1_Config(void){//主中断1，次级中断3
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

   
	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		//1、首先开启TIM1的时钟	    
	
	TIM_DeInit(TIM1);																				//2、时基单元的初始化 Time Base Config
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;							// 72分频，每微秒计数一次,它的取值必须在0x0000和0xFFFF之间
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;// 向上计数模式
	
	TIM_TimeBaseStructure.TIM_Period =10000-1;                	// 10ms定时计数器向上计数到10000后产生更新事件，计数值归零
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;			  	//设置了定时器时钟分割，TIM_ClockDivision = 0x02  TIM_RepetitionCounter = 0x03  就不进入定时器T1的中断里面！！
	
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			// 设置了周期计数器值，它的取值必须在0x00和0xFF之间。
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);	        // 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);               		//清中断，以免一启用中断后立即产生中断  //必须先清除配置时候产生的更新标志 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);          		//使能TIM1中断源 
	TIM_Cmd(TIM1, ENABLE); 		                          		//TIM1总开关：开启/使能定时器
	
	
	
	/*
	TIM_TimeBaseStructure.TIM_Period 			= 1000; 
	TIM_TimeBaseStructure.TIM_Prescaler 		= 72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision 	= 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	
	 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);   
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	 	
	TIM_Cmd(TIM1, ENABLE);		
	*/

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;          //更新事件 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应优先级2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断 
	NVIC_Init(&NVIC_InitStructure);  
}


/*******************************************************************************

        初始化外设

*******************************************************************************/
void BSP_Init(void)
{
//  GPIO_Configuration();	 // 初始化相关引脚
//  NVIC_Configuration();	 // 初始化中断
//  USART1_Init(115200);	 // 初始化串口1,9600波特率
  /*
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_64); 
  IWDG_SetReload(1875);
  IWDG_ReloadCounter();
  IWDG_Enable();
  */
}


#ifdef   USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	printf("\r\n file path is %s,error line is %d \r\n",file,line);
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

