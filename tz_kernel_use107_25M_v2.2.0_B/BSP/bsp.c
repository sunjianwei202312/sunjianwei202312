
#include "bsp.h"
#include  "stm32f10x_rcc.h"
/***********************************************************************

	 ����ʱ��ʹ��

************************************************************************/
void RCC_Configuration(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | 
						             RCC_APB2Periph_GPIOD  | RCC_APB2Periph_GPIOE | 
	                       RCC_APB2Periph_GPIOF,ENABLE);//| RCC_APB2Periph_SPI1���Ե�ʱ�����Ƚ�SPI���ܹرգ�added by sjw
	
	 //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_SPI2, ENABLE);//| RCC_APB1Periph_SPI2���Ե�ʱ�����Ƚ�SPI���ܹرգ�added by sjw
}



/*******************************************************************************

        ȫ���ж��ڴ�����

*******************************************************************************/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef 	NVIC_InitStructure;
   
	/* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    //�����¼� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //��Ӧ���ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
	NVIC_Init(&NVIC_InitStructure);  
	  
	
	
	
	// Enable the USART1 Interrupt 
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //��Ӧ���ȼ�0 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//�����ж� 
	NVIC_Init(&NVIC_InitStructure);

		
	NVIC_InitStructure.NVIC_IRQChannel =  USART2_IRQn;    	//�����¼� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    	//��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       	//�����ж� 
	NVIC_Init(&NVIC_InitStructure);
	


  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_Init(&NVIC_InitStructure);
	*/
	//��ΪOS_TICKS_PER_SEC=40000��Ӧϵͳ25us�ж�һ�Σ�����̫�أ�ֻ�ܽ�������Ϊ��߼��жϣ�
	//ϵͳ����δ��ж�Ϊ��ͼ��жϣ��˳���ִ�������л�  
	//NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick,1,7);

}

/*******************************************************************************

       ��ʼ�� uCOS �δ�ʱ��

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
//    RCC_ClocksTypeDef  rcc_clocks; //RCC_ClocksTypeDef    rccʱ�����Ͷ���ṹ��
//    u32  cnts;
//	
//		//����ʹ���ⲿ������Ϊϵͳʱ�ӵ�ʱ�򣬶����ⲿ�����Ǳ�׼8MHz��ʱ������Ҫ����һ��STM32�Ĺ̼��⣬�����stm32f10x_rcc.c����ļ�
//    RCC_GetClocksFreq(&rcc_clocks);	//72m?
//    cnts = (u32)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;
// 
////������һ��Ҫע�⣬����ʹ�õ�ǰ�Ĵ�����ֵVAL����0��SysTick->VAL  = (0x00);ֻ�е�VALֵΪ0ʱ���������Զ�����RELOAD��
////�������Ϳ���ֱ�ӵ���Delay();���������ӳ��ˡ��ӳٺ�����ʵ���У�Ҫע����ǣ�ȫ�ֱ���TimingDelay����ʹ��volatile��������ܻᱻ�������Ż���
//    SysTick_SetReload(cnts);//����SysTick_SetReload()                                --����SysTick��װ��ֵ��
//    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//����SysTick_CLKSourceConfig()  --����SysTickʱ��Դ��
//    SysTick_CounterCmd(SysTick_Counter_Enable);//����SysTick_CounterCmd()            --ʹ��SysTick������
//	SysTick_ITConfig(ENABLE);	//����SysTick_ITConfig()                               --ʹ��SysTick�ж�
//}	 

		








/*
********************************************************************************
** �������� �� TIM1_Config(void)
** �������� �� ��ʱ��1��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/  



//ͨ�ö�ʱ��x�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz

void TIM1_Config(void){//���ж�1���μ��ж�3
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

   
	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		//1�����ȿ���TIM1��ʱ��	    
	
	TIM_DeInit(TIM1);																				//2��ʱ����Ԫ�ĳ�ʼ�� Time Base Config
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;							// 72��Ƶ��ÿ΢�����һ��,����ȡֵ������0x0000��0xFFFF֮��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;// ���ϼ���ģʽ
	
	TIM_TimeBaseStructure.TIM_Period =10000-1;                	// 10ms��ʱ���������ϼ�����10000����������¼�������ֵ����
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;			  	//�����˶�ʱ��ʱ�ӷָTIM_ClockDivision = 0x02  TIM_RepetitionCounter = 0x03  �Ͳ����붨ʱ��T1���ж����棡��
	
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			// ���������ڼ�����ֵ������ȡֵ������0x00��0xFF֮�䡣
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);	        // ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);               		//���жϣ�����һ�����жϺ����������ж�  //�������������ʱ������ĸ��±�־ 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);          		//ʹ��TIM1�ж�Դ 
	TIM_Cmd(TIM1, ENABLE); 		                          		//TIM1�ܿ��أ�����/ʹ�ܶ�ʱ��
	
	
	
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

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;          //�����¼� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //��Ӧ���ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
	NVIC_Init(&NVIC_InitStructure);  
}


/*******************************************************************************

        ��ʼ������

*******************************************************************************/
void BSP_Init(void)
{
//  GPIO_Configuration();	 // ��ʼ���������
//  NVIC_Configuration();	 // ��ʼ���ж�
//  USART1_Init(115200);	 // ��ʼ������1,9600������
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

