/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_it.c
* Author             : MCD Application Team
* Version            : V1.1
* Date               : 05/30/2008
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "motordrive.h"
#include "uart.h"
#include  "hd7279.h"
#include  "key.h"


#define   OVER_SYMBOL1     0xff
#define   OVER_SYMBOL2     0x0a     //现在回车和换行修改为 0xff+0x0a!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

INT8U  IntKeyActionValid;
extern INT8U ReadKey_Value;               //读到的键值

extern  INT8U  MotorZZ_Flag,MotorFZ_Flag;
extern INT8U  Key_Time;

extern INT8U pps1_tim;

extern void pps_init(void);

extern enum   KeyRun_Order    Key_Subclock_State1;


extern  u16 Usart1_Rx_Len ;
extern INT8U   MotorActFlag;
extern INT8U     StartEraseNandFlag;
uint16_t USART_RX_STA=0;                  //接收状态标记	
uint8_t  UsartRxBuf[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
uint8_t    ItWaitFlag;

	INT32U ms_1;

BOOLEAN		Vs1003bPowOnFlag;
INT8U 		RxdData[8];
INT8U		 *pRxdData=RxdData;
INT8U		  StartSymble;
INT8U		  ItFlag;
INT8U     USART1_Recive_Flag;

INT8U     IntDisFlag;

void 		DelayMs_Usart2(vu32 m);
extern    INT8U 		uart1_rx_sig;

extern  INT8U  LightSlotFlag;
extern  INT16U LightSlotValue;

extern		BOOLEAN		MainUsart2NoRxdFlag;
extern		BOOLEAN		MainBsJsValidFlag;
extern		BOOLEAN		MainBsOnOffStatusFlag;
extern		BOOLEAN		MainBsStartFlag;
extern		INT8U		MainBsPayOrXms;
extern		INT8U		MainBsKnockCnt;
	
extern		INT8U 		USART2_RX_FIFO[USART2_RX_CNT];  		// 定义环形数据
extern		mytime 		*p_timemu;
__IO     int32_t g_iRunTime ;
extern	OS_EVENT 	*Mutex_USART1; // 定义USART1互斥型事件	
	
extern		INT8U 	USART1_RX_FIFO[USART1_RX_CNT];  			// 定义环形数据
extern		INT8U 	*pPut_USART1_RX_FIFO ; 	// 定义环形数组放数指针
extern		INT8U 	*pGet_USART1_RX_FIFO ; 	// 定义环形数组取数指针

extern    OS_EVENT	 	*pMainMotorSemEve;

extern INT16U     TestCount;
extern INT8U      *pMainProcess;
extern uint8_t  TestCountHL[2];
extern uint8_t  *pTestCountHL;
void   uart1_rx_isr( void);
 uint8_t Res;

extern INT8U  PowerOnFLag;


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//static vu32 Index = 0;
//static vu32 AlarmStatus = 0;




/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void HardFaultException(void)
void HardFault_Handler(void)

{
	static	INT16U js_count=0;
	static INT16U jsrun;
  static  INT8U flag;
	
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
		js_count++;
  }
}



void SysTick_Handler(void){ //1毫秒系统中断一次！参考  OS_TICKS_PER_SEC   定义
	OS_CPU_SR  cpu_sr;	   
	static INT16U  jsrun,jsrun2;
	static	INT16U js_count;
	static	INT8U previous_actflag;
	static	INT8U  once_act_flag=0;
	static	INT16U  once_js_rseg=0;
	
	
	
	
		OSIntEnter(); //进入中断   OSIntNesting++;    /* Increment ISR nesting level */
		jsrun++;
	  if(jsrun>300){//1000ms可以显示一次，否则芯片保护全部熄灭！！added  by sjw
			jsrun=0;
			IntDisFlag=1;
      Key_Time=1;			
		}

	  jsrun2++;
	  if(jsrun2>999){//1000ms可以显示一次，否则芯片保护全部熄灭！！added  by sjw
			jsrun2=0;
      ItWaitFlag=1;			
		}

		if(LightSlotFlag){
			 LightSlotValue++;	 
		}
		
		
		if(!PowerOnFLag){//上电追时结束后才能开始走步进行判断！！added by sjw	
				if((p_timemu->second==30 || p_timemu->second==53)&&(!once_act_flag))//保证发出信号量只能发一次！不会多也不会少！ added by sjw
				{

					 once_act_flag=1;
					// OSSemPost(pMainMotorSemEve);
					 MotorActFlag=1;
				}
				
				if(once_act_flag){
						once_js_rseg++;
						if(once_js_rseg>1300){
							 once_act_flag=0;
							 once_js_rseg=0;
						}
				}
		}
		
		
		
		if(!PowerOnFLag){
			
		    #if 0  //在中断中屏蔽子钟状态功能的处理！！
				switch ( Key_Subclock_State1){  //子钟状态 
						
					case NC:
				
					
					case WALK:
						/*
							//如果没有此标志位，因为1ms中断一次，故一直发送信号量1000次，此时电机一直转动下去！！added by sjw
							if(p_timemu->second==29 || p_timemu->second==54){
									previous_actflag=1;
							}	
							if(previous_actflag){
									jsrun++;
									if(jsrun>1000){
										jsrun=0;
										previous_actflag=0;
										OSSemPost(pMainMotorSemEve);
									}
							}*/
							if((p_timemu->second==30 || p_timemu->second==53)&&(!once_flag))//保证发出信号量只能发一次！不会多也不会少！ added by sjw
							{
			
								 once_flag=1;
								// OSSemPost(pMainMotorSemEve);
								 MotorActFlag=1;
							}
							
							if(once_flag){
									once_js_rseg++;
								  if(once_js_rseg>1300){
										 once_js_rseg=0;
										 once_flag=0;
									}
							}
							
							
										
					break;
					
							
					case RUN_FORWARD:
							MotorFZ_Flag=0;
							MotorZZ_Flag=1;
					
					break;
					
					case STOP:
							 MotorZZ_Flag=0;
							 MotorFZ_Flag=0;
					
							 EAST_ZZ_IDLE;
							 EAST_FZ_IDLE;
							 Key_Subclock_State1=STOP;
					break;
					case RUN_REVERSE:
							MotorZZ_Flag=0;
							MotorFZ_Flag=1;
					break;
					case CALIB:
						
					break;
					
				}
				 
			 #endif
		}
		
	
		
		OSTimeTick();//提供延时及超时功能！调用ucos的时钟服务程序
		OSIntExit(); //中断退出后触发任务切换软中断 
}



/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)//cpu心跳指示（cpu输出）（>10hz脉冲）  <100ms
{
	static	INT16U js_count=0;
	static  INT16U jsrun;
  static  INT8U flag;
	 static  INT8U count;
	
	
	
	if (TIM_GetITStatus(TIM1 , TIM_IT_Update) != RESET )
	{ //是否发生中断
		TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
  /* Clear the TIM1 Update pending bit */		
		//if(MainBsJsValidFlag){
		count++;
		if(count<20)
			RUNLEDLOW;       //运行指示灯点亮
		else if(count<100){
			RUNLEDHIGH;	     //运行指示灯熄灭
		}else if(count==100)
			count=0;
		
		
				/* 全局运行时间每1ms增1 */
		g_iRunTime++;
		if (g_iRunTime == 0x7FFFFFFF){	/* 这个变量是 int32_t 类型，最大数为 0x7FFFFFFF */
			g_iRunTime = 0;
		}
			
		if(StartEraseNandFlag)
		  ms_1++;
		
			
		flag++;
		if(flag==2)flag=0;
		
		jsrun++;
		switch(jsrun){
			case 500:
							
			break;
			case 1000:
							
						
			  jsrun=0;
			break;
		}
		
		
		
			js_count++;
			if(js_count==100){			
				js_count=0;		
				p_timemu->second++;
				if(p_timemu->second==60){
					p_timemu->second=0x00;
					p_timemu->minute+=1;
					if(p_timemu->minute==60){
						p_timemu->minute=0x00;
						p_timemu->hour+=1;
						p_timemu->hour%=24;
					}
			   }
				if(p_timemu->minute>57){  //超过58分钟的时候，使能vs1003b芯片一次，报时结束使其掉电！
					Vs1003bPowOnFlag=TRUE;//在任务中让vs1003b复位准备唱歌！
				}
				if((p_timemu->minute==1)&&(p_timemu->second==5)){
					Vs1003bPowOnFlag=FALSE;
				}
			}
			
			
			
				
	  if(pps1_tim < 0xFF)
			pps1_tim++;		
	
	}
}







/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None

记住顺序，
1.先使能GPIOB和AFIO，
2.再调用GPIO_PinRemapConfig函数，
3.然后再初始化gpio引脚，
4.再使能USART1，
5.再配置串口，
6.需要中断的话再配置中断，切记不要搞错。
其它系列芯片的顺序也是一样的，但是映射的函数是不一样的，请查询后使用。
*******************************************************************************/

void USART1_IRQHandler(void)//调试接近1整天，最后发现是硬件的问题；在RXD引脚上接了一个SN74LVC2T45DCT驱动器，将引脚给拉低了！
//我说接个上拉电阻也不行，配置引脚的模式还是不行，接收数据都是       错乱的！！！！，吹掉SN74LVC2T45DCT，一切ok！
{
	 INT16U num=0;
	 INT8U  start;
   OS_CPU_SR  cpu_sr;
	 static uint8_t count;
  u8 Clear = 0;
	
	
	
	
	
    OS_ENTER_CRITICAL();  //保存全局中断标志,关总中断/* Tell uC/OS-II that we are starting an ISR*/
    OSIntNesting++;
    OS_EXIT_CRITICAL();	  //恢复全局中断标志

	
         
    /*
	
		
		 if (USART_GetFlagStatus(USART1, USART_FLAG_PE) != RESET){
				 USART_ReceiveData(USART1);
				 USART_ClearFlag(USART1, USART_FLAG_PE);
		 }
			
		 if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET){
					USART_ReceiveData(USART1);
					USART_ClearFlag(USART1, USART_FLAG_ORE);
		 }
			
		 if (USART_GetFlagStatus(USART1, USART_FLAG_FE) != RESET){ 
				 USART_ReceiveData(USART1);
				 USART_ClearFlag(USART1, USART_FLAG_FE);
		 }
			*/
			
			
			
		 
	
		 if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET){
			  //USART_ClearITPendingBit(USART1, USART_IT_IDLE);            // 此指令不需要！！  added by sjw
				num = USART1->SR;
				num = USART1->DR;                                            //清USART_IT_IDLE标志 不读的话会 一直进入中断  added by sjw
				DMA_Cmd(DMA1_Channel5,DISABLE);                              //关闭DMA
				//DMA_GetCurrDataCounter函数为返回当前DMAy通道传输中剩余的数据单元数
			  num = UART1_RX_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5); //得到真正接收数据个数
        Usart1_Rx_Len =num;
			 
			  DMA1_Channel5->CNDTR=UART1_RX_SIZE;                          //重新设置接收数据个数 DMA_Cmd(DMA1_Channel5,ENABLE); //开启DMA
				DMA_Cmd(DMA1_Channel5,ENABLE);                               //开启DMA
			  USART1_Recive_Flag = 1;                                      //数据接收成功  接受完成标志位置1
			 uart1_rx_sig=1;
			  		 	
        //数据处理
		 
		}
	
	
	 OS_ENTER_CRITICAL();
	 OSIntNesting--;
	 OS_EXIT_CRITICAL();
	
}




/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None

核心思路是主板每一分钟的时候发送以下报文数据：
0xbb,时+分+秒+（music-1）+（小时+1）+（报时寄存器）+效验和(0x0d+0x0a)	
*******************************************************************************/

void USART2_IRQHandler(void){
	OS_CPU_SR  	cpu_sr;
	INT16U		timerinc=0;
	INT8U 	  js=0,ch;
	


	static 		INT8U 	rxdjstemp=0;
	static  		INT8U 	temp1,temp2,temp3,temp4;
	static		INT8U 	temp;
	INT32U 		tempheader;
	INT32U 		tempid;
	INT32U 		tempflash;
	
	
	OS_ENTER_CRITICAL();
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET ){// 如果是串口2接收中断
		// USART_ClearITPendingBit(USART2, USART_IT_RXNE);//清中断标识
		 //USART_ClearFlag(USART2, USART_FLAG_RXNE);
		 ch = USART1->SR;
		 ch = USART1->DR; 
		 StartSymble=USART_ReceiveData(USART2);//接收第一个字节，看看是否为起始符号0x24!
		
		
  	 USART2_RXLoop(StartSymble);	 // 将数据放入环形队列
//		OSTaskResume(APP_TASK2_PRIO);
//		
		
		
//		
//		js++;
//		if(js==9){
//			js=0;
//			if((USART2_RX_FIFO[7]==0x0d)&&(USART2_RX_FIFO[8]==0x0a)){ 	
//				p_timemu->hour=USART2_RX_FIFO[1];
//				p_timemu->minute=USART2_RX_FIFO[2];
//				p_timemu->second=USART2_RX_FIFO[3];
//				MainBsPayOrXms=USART2_RX_FIFO[4];		//0为平安夜报时；1为西敏寺报时！
//				MainBsKnockCnt=USART2_RX_FIFO[5]%12;   //钟声次数！
//				if(USART2_RX_FIFO[6]==0){		 		//报时打开或者关死状态！
//					MainBsOnOffStatusFlag=FALSE;
//					MainBsJsValidFlag=FALSE;		
//				}else{
//					MainBsOnOffStatusFlag=TRUE;
//					MainBsJsValidFlag=TRUE;
//				}	
//			}
//		}

//		if(StartSymble==0xbb ){
//			p_timemu->hour=3;
//			p_timemu->minute=59;
//			p_timemu->second=30;
//			MainBsPayOrXms=0;		//0为平安夜报时；1为西敏寺报时！
//			MainBsKnockCnt=3;
//	
//		}
		
		//if(StartSymble==0xbb && !MainUsart2NoRxdFlag){//是第一个起始符号，那么必定在中断中接收剩下的8个字节！
		
			if(StartSymble==0xbb){			
				pRxdData=RxdData;
			    do{
					while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET){//数据没有收到，等待！
						DelayMs_Usart2(1);
						timerinc++;
						if(timerinc>30000)	break;//超时后强制退出循环！
					}
					//USART_ClearITPendingBit(USART2, USART_IT_RXNE);//清中断标识	
					//USART_ClearFlag(USART2, USART_FLAG_RXNE);
					*pRxdData=USART_ReceiveData(USART2);
					pRxdData++;
					js++;
				}while(js<8);
				
				if((RxdData[6]==0x0d)&&(RxdData[7]==0x0a)){ 
					//MainUsart2NoRxdFlag=TRUE;
					
					p_timemu->hour=RxdData[0];
					p_timemu->minute=RxdData[1];
					p_timemu->second=RxdData[2];
					MainBsPayOrXms=RxdData[3];		//0为平安夜报时；1为西敏寺报时！
					MainBsKnockCnt=RxdData[4]%12;   //钟声次数！
					if(RxdData[5]==0){		 		//报时打开或者关死状态！
						MainBsOnOffStatusFlag=FALSE;
						//MainBsJsValidFlag=FALSE;		
					}else{
						MainBsOnOffStatusFlag=TRUE;
						//MainBsJsValidFlag=TRUE;
					}	
				}
		 }


//				
//		if(!MainUsart2NoRxdFlag){
//			//USART_ClearFlag(USART2, USART_FLAG_RXNE);
//			USART2_RXLoop(USART_ReceiveData(USART2));	 // 将数据放入环形队列
//			OSTaskResume(APP_TASK2_PRIO);
//			//*pRxdData++=USART_ReceiveData(USART2);
//		}
	 }
	OS_ENTER_CRITICAL();
	OSIntNesting--;
	OS_EXIT_CRITICAL();
}
 

/*******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : This function handles DMA1 Channel 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel5_IRQHandler(void)
{
	 INT16U num=0;
	 INT8U  start;
   OS_CPU_SR  cpu_sr;
	 static uint8_t count;

    if(DMA_GetITStatus(DMA1_IT_TC5) != RESET)//此为DMA发送结束后要进入的中断！！added by sjw
    {
      //TestLive();
      DMA_ClearITPendingBit(DMA1_IT_TC5);
    }
	
	
}











/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
 if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{    
		EXTI_ClearITPendingBit(EXTI_Line11);
		pps_isr();
	} 
	
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{    
		Set7279CS(0);
	  ReadKey_Value=read_hd7279(CMD_READ);  
		EXTI_ClearITPendingBit(EXTI_Line10);
		Set7279CS(1);
		
		IntKeyActionValid=1;

	} 
	
	
}




















/*

void uart1_rx_isr( void)//此函数有BUG，如果在0x0d??个块上操作的时候，会出现问题！！！！！！！！比如0x0d0a个块出问题！！！！！！！！！！！
{
    if((USART_RX_STA & 0x8000)==0)          //接收未完成
		{
			if(USART_RX_STA & 0x4000)             //已经接收到了OVER_SYMBOL1
			{
				if(Res!= OVER_SYMBOL2 ){
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA++;
					USART_RX_STA &=~(0x4000);
				}
				else{ 
					USART_RX_STA|=0x8000;         	//接收完成了
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA=0;
					pMainProcess=UsartRxBuf; 
					ItWaitFlag=1;
					
				}
			}else{                             //还没收到OVER_SYMBOL1
				if(Res== OVER_SYMBOL1 ){
					USART_RX_STA|=0x4000;
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA++;
				}
				else
				{
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>USART_REC_LEN-1)  USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		} 
}	

*/





















/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
 
}


/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}





/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
    
}

/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
     
}

/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : This function handles DMA1 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : This function handles DMA1 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : This function handles DMA1 Channel 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel4_IRQHandler(void)
{
}


/*******************************************************************************
* Function Name  : DMA1_Channel6_IRQHandler
* Description    : This function handles DMA1 Channel 6 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel7_IRQHandler
* Description    : This function handles DMA1 Channel 7 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/




/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
STM32-USB学习笔记（一） USB基础
https://www.doc88.com/p-505935487642.html

STM32 USB部分中断函数简要分析
https://blog.csdn.net/yxfabcdefg/article/details/52336070

https://www.pianshen.com/article/97651154818/

基于STM32的USB枚举过程学习笔记(二)
https://blog.csdn.net/qq236106303/article/details/8177568


基于STM32的USB枚举过程学习笔记(三)
https://blog.csdn.net/qq236106303/article/details/8179005


基于STM32的USB枚举过程学习笔记(四)
https://blog.csdn.net/qq236106303/article/details/8181336?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&utm_relevant_index=2
*/


/*
void USB_LP_CAN_RX0_IRQHandler(void)
//void USB_LP_CAN1_RX0_IRQn(void)
{
	USB_Istr();
}

*/

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
 
}


/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : This function handles TIM8 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : This function handles TIM8 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : This function handles TIM8 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_CC_IRQHandler
* Description    : This function handles TIM8 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : This function handles ADC3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : FSMC_IRQHandler
* Description    : This function handles FSMC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : This function handles TIM5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : This function handles SPI3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles UART4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : This function handles UART5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM6_IRQHandler
* Description    : This function handles TIM6 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : This function handles TIM7 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : This function handles DMA2 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : This function handles DMA2 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel4_5_IRQHandler
* Description    : This function handles DMA2 Channel 4 and DMA2 Channel 5
*                  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{
}

/*
********************************************************************************
** 函数名称 ： void DelayMs(vu32 m)
** 函数功能 ： 长延时函数	 m=1,延时1ms
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void DelayMs_Usart2(vu32 m){//在72M系统中，机器周期为0.0138ns，这样该函数延时时间为13.8ns
  u32 i;					//要接收剩下的8个字节，在4800波特率下正常的话大约需要10毫秒接收6个字节
							//要接收8个字节，大约需要15毫秒！(15000/13.8)=1100次计数！这样我在中断中选2000次！
	 for(; m != 0; m--)	
       for (i=0; i<1000; i++);
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
