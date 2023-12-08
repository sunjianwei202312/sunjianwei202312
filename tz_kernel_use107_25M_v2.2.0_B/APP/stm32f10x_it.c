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
#define   OVER_SYMBOL2     0x0a     //���ڻس��ͻ����޸�Ϊ 0xff+0x0a!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

INT8U  IntKeyActionValid;
extern INT8U ReadKey_Value;               //�����ļ�ֵ

extern  INT8U  MotorZZ_Flag,MotorFZ_Flag;
extern INT8U  Key_Time;

extern INT8U pps1_tim;

extern void pps_init(void);

extern enum   KeyRun_Order    Key_Subclock_State1;


extern  u16 Usart1_Rx_Len ;
extern INT8U   MotorActFlag;
extern INT8U     StartEraseNandFlag;
uint16_t USART_RX_STA=0;                  //����״̬���	
uint8_t  UsartRxBuf[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
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
	
extern		INT8U 		USART2_RX_FIFO[USART2_RX_CNT];  		// ���廷������
extern		mytime 		*p_timemu;
__IO     int32_t g_iRunTime ;
extern	OS_EVENT 	*Mutex_USART1; // ����USART1�������¼�	
	
extern		INT8U 	USART1_RX_FIFO[USART1_RX_CNT];  			// ���廷������
extern		INT8U 	*pPut_USART1_RX_FIFO ; 	// ���廷���������ָ��
extern		INT8U 	*pGet_USART1_RX_FIFO ; 	// ���廷������ȡ��ָ��

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



void SysTick_Handler(void){ //1����ϵͳ�ж�һ�Σ��ο�  OS_TICKS_PER_SEC   ����
	OS_CPU_SR  cpu_sr;	   
	static INT16U  jsrun,jsrun2;
	static	INT16U js_count;
	static	INT8U previous_actflag;
	static	INT8U  once_act_flag=0;
	static	INT16U  once_js_rseg=0;
	
	
	
	
		OSIntEnter(); //�����ж�   OSIntNesting++;    /* Increment ISR nesting level */
		jsrun++;
	  if(jsrun>300){//1000ms������ʾһ�Σ�����оƬ����ȫ��Ϩ�𣡣�added  by sjw
			jsrun=0;
			IntDisFlag=1;
      Key_Time=1;			
		}

	  jsrun2++;
	  if(jsrun2>999){//1000ms������ʾһ�Σ�����оƬ����ȫ��Ϩ�𣡣�added  by sjw
			jsrun2=0;
      ItWaitFlag=1;			
		}

		if(LightSlotFlag){
			 LightSlotValue++;	 
		}
		
		
		if(!PowerOnFLag){//�ϵ�׷ʱ��������ܿ�ʼ�߲������жϣ���added by sjw	
				if((p_timemu->second==30 || p_timemu->second==53)&&(!once_act_flag))//��֤�����ź���ֻ�ܷ�һ�Σ������Ҳ�����٣� added by sjw
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
			
		    #if 0  //���ж�����������״̬���ܵĴ�����
				switch ( Key_Subclock_State1){  //����״̬ 
						
					case NC:
				
					
					case WALK:
						/*
							//���û�д˱�־λ����Ϊ1ms�ж�һ�Σ���һֱ�����ź���1000�Σ���ʱ���һֱת����ȥ����added by sjw
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
							if((p_timemu->second==30 || p_timemu->second==53)&&(!once_flag))//��֤�����ź���ֻ�ܷ�һ�Σ������Ҳ�����٣� added by sjw
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
		
	
		
		OSTimeTick();//�ṩ��ʱ����ʱ���ܣ�����ucos��ʱ�ӷ������
		OSIntExit(); //�ж��˳��󴥷������л����ж� 
}



/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)//cpu����ָʾ��cpu�������>10hz���壩  <100ms
{
	static	INT16U js_count=0;
	static  INT16U jsrun;
  static  INT8U flag;
	 static  INT8U count;
	
	
	
	if (TIM_GetITStatus(TIM1 , TIM_IT_Update) != RESET )
	{ //�Ƿ����ж�
		TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
  /* Clear the TIM1 Update pending bit */		
		//if(MainBsJsValidFlag){
		count++;
		if(count<20)
			RUNLEDLOW;       //����ָʾ�Ƶ���
		else if(count<100){
			RUNLEDHIGH;	     //����ָʾ��Ϩ��
		}else if(count==100)
			count=0;
		
		
				/* ȫ������ʱ��ÿ1ms��1 */
		g_iRunTime++;
		if (g_iRunTime == 0x7FFFFFFF){	/* ��������� int32_t ���ͣ������Ϊ 0x7FFFFFFF */
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
				if(p_timemu->minute>57){  //����58���ӵ�ʱ��ʹ��vs1003bоƬһ�Σ���ʱ����ʹ����磡
					Vs1003bPowOnFlag=TRUE;//����������vs1003b��λ׼�����裡
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

��ס˳��
1.��ʹ��GPIOB��AFIO��
2.�ٵ���GPIO_PinRemapConfig������
3.Ȼ���ٳ�ʼ��gpio���ţ�
4.��ʹ��USART1��
5.�����ô��ڣ�
6.��Ҫ�жϵĻ��������жϣ��мǲ�Ҫ���
����ϵ��оƬ��˳��Ҳ��һ���ģ�����ӳ��ĺ����ǲ�һ���ģ����ѯ��ʹ�á�
*******************************************************************************/

void USART1_IRQHandler(void)//���Խӽ�1���죬�������Ӳ�������⣻��RXD�����Ͻ���һ��SN74LVC2T45DCT�������������Ÿ������ˣ�
//��˵�Ӹ���������Ҳ���У��������ŵ�ģʽ���ǲ��У��������ݶ���       ���ҵģ�������������SN74LVC2T45DCT��һ��ok��
{
	 INT16U num=0;
	 INT8U  start;
   OS_CPU_SR  cpu_sr;
	 static uint8_t count;
  u8 Clear = 0;
	
	
	
	
	
    OS_ENTER_CRITICAL();  //����ȫ���жϱ�־,�����ж�/* Tell uC/OS-II that we are starting an ISR*/
    OSIntNesting++;
    OS_EXIT_CRITICAL();	  //�ָ�ȫ���жϱ�־

	
         
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
			  //USART_ClearITPendingBit(USART1, USART_IT_IDLE);            // ��ָ���Ҫ����  added by sjw
				num = USART1->SR;
				num = USART1->DR;                                            //��USART_IT_IDLE��־ �����Ļ��� һֱ�����ж�  added by sjw
				DMA_Cmd(DMA1_Channel5,DISABLE);                              //�ر�DMA
				//DMA_GetCurrDataCounter����Ϊ���ص�ǰDMAyͨ��������ʣ������ݵ�Ԫ��
			  num = UART1_RX_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5); //�õ������������ݸ���
        Usart1_Rx_Len =num;
			 
			  DMA1_Channel5->CNDTR=UART1_RX_SIZE;                          //�������ý������ݸ��� DMA_Cmd(DMA1_Channel5,ENABLE); //����DMA
				DMA_Cmd(DMA1_Channel5,ENABLE);                               //����DMA
			  USART1_Recive_Flag = 1;                                      //���ݽ��ճɹ�  ������ɱ�־λ��1
			 uart1_rx_sig=1;
			  		 	
        //���ݴ���
		 
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

����˼·������ÿһ���ӵ�ʱ�������±������ݣ�
0xbb,ʱ+��+��+��music-1��+��Сʱ+1��+����ʱ�Ĵ�����+Ч���(0x0d+0x0a)	
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
	
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET ){// ����Ǵ���2�����ж�
		// USART_ClearITPendingBit(USART2, USART_IT_RXNE);//���жϱ�ʶ
		 //USART_ClearFlag(USART2, USART_FLAG_RXNE);
		 ch = USART1->SR;
		 ch = USART1->DR; 
		 StartSymble=USART_ReceiveData(USART2);//���յ�һ���ֽڣ������Ƿ�Ϊ��ʼ����0x24!
		
		
  	 USART2_RXLoop(StartSymble);	 // �����ݷ��뻷�ζ���
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
//				MainBsPayOrXms=USART2_RX_FIFO[4];		//0Ϊƽ��ҹ��ʱ��1Ϊ�����±�ʱ��
//				MainBsKnockCnt=USART2_RX_FIFO[5]%12;   //����������
//				if(USART2_RX_FIFO[6]==0){		 		//��ʱ�򿪻��߹���״̬��
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
//			MainBsPayOrXms=0;		//0Ϊƽ��ҹ��ʱ��1Ϊ�����±�ʱ��
//			MainBsKnockCnt=3;
//	
//		}
		
		//if(StartSymble==0xbb && !MainUsart2NoRxdFlag){//�ǵ�һ����ʼ���ţ���ô�ض����ж��н���ʣ�µ�8���ֽڣ�
		
			if(StartSymble==0xbb){			
				pRxdData=RxdData;
			    do{
					while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET){//����û���յ����ȴ���
						DelayMs_Usart2(1);
						timerinc++;
						if(timerinc>30000)	break;//��ʱ��ǿ���˳�ѭ����
					}
					//USART_ClearITPendingBit(USART2, USART_IT_RXNE);//���жϱ�ʶ	
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
					MainBsPayOrXms=RxdData[3];		//0Ϊƽ��ҹ��ʱ��1Ϊ�����±�ʱ��
					MainBsKnockCnt=RxdData[4]%12;   //����������
					if(RxdData[5]==0){		 		//��ʱ�򿪻��߹���״̬��
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
//			USART2_RXLoop(USART_ReceiveData(USART2));	 // �����ݷ��뻷�ζ���
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

    if(DMA_GetITStatus(DMA1_IT_TC5) != RESET)//��ΪDMA���ͽ�����Ҫ������жϣ���added by sjw
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

void uart1_rx_isr( void)//�˺�����BUG�������0x0d??�����ϲ�����ʱ�򣬻�������⣡������������������0x0d0a��������⣡��������������������
{
    if((USART_RX_STA & 0x8000)==0)          //����δ���
		{
			if(USART_RX_STA & 0x4000)             //�Ѿ����յ���OVER_SYMBOL1
			{
				if(Res!= OVER_SYMBOL2 ){
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA++;
					USART_RX_STA &=~(0x4000);
				}
				else{ 
					USART_RX_STA|=0x8000;         	//���������
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA=0;
					pMainProcess=UsartRxBuf; 
					ItWaitFlag=1;
					
				}
			}else{                             //��û�յ�OVER_SYMBOL1
				if(Res== OVER_SYMBOL1 ){
					USART_RX_STA|=0x4000;
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA++;
				}
				else
				{
					UsartRxBuf[USART_RX_STA & 0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>USART_REC_LEN-1)  USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
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
STM32-USBѧϰ�ʼǣ�һ�� USB����
https://www.doc88.com/p-505935487642.html

STM32 USB�����жϺ�����Ҫ����
https://blog.csdn.net/yxfabcdefg/article/details/52336070

https://www.pianshen.com/article/97651154818/

����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
https://blog.csdn.net/qq236106303/article/details/8177568


����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
https://blog.csdn.net/qq236106303/article/details/8179005


����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
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
** �������� �� void DelayMs(vu32 m)
** �������� �� ����ʱ����	 m=1,��ʱ1ms
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void DelayMs_Usart2(vu32 m){//��72Mϵͳ�У���������Ϊ0.0138ns�������ú�����ʱʱ��Ϊ13.8ns
  u32 i;					//Ҫ����ʣ�µ�8���ֽڣ���4800�������������Ļ���Լ��Ҫ10�������6���ֽ�
							//Ҫ����8���ֽڣ���Լ��Ҫ15���룡(15000/13.8)=1100�μ��������������ж���ѡ2000�Σ�
	 for(; m != 0; m--)	
       for (i=0; i<1000; i++);
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
