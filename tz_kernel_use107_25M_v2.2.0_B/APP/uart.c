#include <string.h>
#include "stm32f10x.h"
#include "uart.h" 
#include "gps.h" 
//#include "tmcode.h"
//#include "led.h"
//#include "command.h"


/* uart1 */
#ifdef USING_UART1
volatile uint16_t com1_rx_len = 0;    //接收帧数据的长度
volatile INT8U com1_recv_end_flag = 0;//帧数据接收完成标志

INT8U 	com1_rx_buffer[400]={0};   //接收数据缓存
INT8U 	DMA_USART1_TX_BUF[400]={0};//DMA发送缓存
INT8U 	Uart1_Rx_Buf[UART1_RX_SIZE];	
INT8U 	Uart1_Tx_Buf[UART1_TX_SIZE];
INT8U 	Uart1_Tx_Idle = IDLE;
INT16U Usart1_Rx_Len = 0;
INT16U Uart1_Tx_Cnt = 0;
INT16U Uart1_Rx_Tmo_Cnt = 0; 
static INT8U 	Uart1_Rx_Idle = 0; 
static INT16U 	Uart1_Rx_Cnt = 0; 

#endif

/* uart2 */	
#ifdef USING_UART2
volatile uint16_t com2_rx_len = 0;    //接收帧数据的长度
INT16U Uart2_Rx_Len = 0;

INT8U 	Uart2_Rx_Buf[UART2_RX_SIZE];	
INT8U 	Uart2_Tx_Buf[UART2_TX_SIZE];
INT8U 	Uart2_Tx_Idle = IDLE;
INT16U 	Uart2_Tx_Cnt = 0;
INT16U 	Uart2_Rx_Tmo_Cnt = 0; 
static 		INT8U 	Uart2_Rx_Idle = 0; 
static 		INT16U 	Uart2_Rx_Cnt = 0; 
volatile 	INT8U com2_recv_end_flag = 0;//帧数据接收完成标志
INT16U uart2_rx_tmo_cnt = 0; 

#endif

/* uart3 */	
#ifdef USING_UART3
volatile uint16_t com3_rx_len = 0;    //接收帧数据的长度
INT16U Uart3_Rx_Len = 0;

INT8U 	Uart3_Rx_Buf[UART3_RX_SIZE];	
INT8U 	Uart3_Tx_Buf[UART3_TX_SIZE];
INT8U 	Uart3_Tx_Idle = IDLE;
INT16U 	Uart3_Tx_Cnt = 0;
INT16U 	Uart3_Rx_Tmo_Cnt = 0; 
static INT8U 	Uart3_Rx_Idle = 0; 
static INT16U 	Uart3_Rx_Cnt = 0; 
volatile INT8U com3_recv_end_flag = 0;//帧数据接收完成标志

#endif

/* uart4 */	
#ifdef USING_UART4
volatile uint16_t com4_rx_len = 0;    //接收帧数据的长度
INT16U Uart4_Rx_Len = 0;

INT8U 	Uart4_Rx_Buf[UART4_RX_SIZE];	
INT8U 	Uart4_Tx_Buf[UART4_TX_SIZE];
INT8U 	Uart4_Tx_Idle = IDLE;
INT16U  Uart4_Tx_Cnt = 0;
INT16U  Uart4_Rx_Tmo_Cnt = 0; 
static INT8U 	Uart4_Rx_Idle = 0; 
static INT16U 	Uart4_Rx_Cnt = 0; 
volatile INT8U com4_recv_end_flag = 0;//帧数据接收完成标志


#endif

/* uart5 */
#ifdef USING_UART5
INT8U 	Uart5_Tx_Tmo_Flag = 0;
INT16U 	Uart5_Tx_Cur_Cnt;
INT16U 	Uart5_Tx_Tmo_Cnt = 0; 
volatile uint16_t com5_rx_len = 0;    //接收帧数据的长度
INT16U Uart5_Rx_Len = 0;


INT8U 	Uart5_Rx_Buf[UART5_RX_SIZE];	
INT8U 	Uart5_Tx_Buf[UART5_TX_SIZE];
INT8U 	Uart5_Tx_Idle = IDLE;
INT16U 	Uart5_Tx_Cnt = 0;
INT16U 	Uart5_Rx_Tmo_Cnt = 0; 
static INT8U 	Uart5_Rx_Idle = 0; 
static INT16U 	Uart5_Rx_Cnt = 0; 
volatile INT8U com5_recv_end_flag = 0;//帧数据接收完成标志

#endif 


INT16U USART1_MODBUS_send_count;
static void uart1_rx(void);
static void DMA_Configuration(void);
static void UART_Configuration(void);


 INT8U 		uart1_rx_sig;
 INT8U 		uart1_tc_sig;
 
 INT8U 		uart2_rx_sig;
 INT8U 		uart3_rx_sig;
 INT8U 		uart4_rx_sig;
 
 INT8U 		uart5_rx_sig;
 INT8U 		uart5_tx_sig;

void uart2_tx(INT8U *data, INT16U len)
{
	/*
	if(len > UART2_TX_SIZE)
		Uart2_Tx_Cnt = UART2_TX_SIZE;
	else
		Uart2_Tx_Cnt = len;	 
	
//	while(uart2_Tx_Idle != IDLE);

	Uart2_Tx_Idle = BUSY;	  					 
	memcpy(Uart2_Tx_Buf, data, Uart2_Tx_Cnt);
	//DMA_SetCurrDataCounter(UART2_TX_DMA, Uart2_Tx_Cnt); 
	//DMA_Cmd(UART2_TX_DMA, ENABLE);
	*/
//drv_rs485_tx(data,len,2);

	
}








/*
1.//https://blog.csdn.net/m0_55409593/article/details/120874147
//stm32f407 usart1+dma接收固定长度数据 并在dma中断中进行解析

2.//严谨的做法需要做双buf，CPU和DMA各自一块内存交替访问，即是"乒乓缓存” ，处理流程步骤应该是这样：
//【1】第一步，DMA先将数据搬运到buf1，搬运完成通知CPU来拷贝buf1数据
//【2】第二步，DMA将数据搬运到buf2，与CPU拷贝buf1数据不会冲突
//【3】第三步，buf2数据搬运完成，通知CPU来拷贝buf2数据
//【4】执行完第三步，DMA返回执行第一步，一直循环
//https://baijiahao.baidu.com/s?id=1715820165842458402&wfr=spider&for=pc

3.STM32 407 USART+DMA接收(不用中断)
http://www.javashuo.com/article/p-kcktptdo-nt.html

*/









static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef USING_UART1
	GPIO_InitStructure.GPIO_Pin = UART1_GPIO_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART1_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = UART1_GPIO_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART1_GPIO, &GPIO_InitStructure);
#endif

#ifdef USING_UART2
	GPIO_InitStructure.GPIO_Pin = UART2_GPIO_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART2_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = UART2_GPIO_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART2_GPIO, &GPIO_InitStructure);
#endif

#ifdef USING_UART3
	GPIO_InitStructure.GPIO_Pin = UART3_GPIO_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART3_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = UART3_GPIO_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART3_GPIO, &GPIO_InitStructure);
#endif

#ifdef USING_UART4
   	GPIO_InitStructure.GPIO_Pin 	= UART4_GPIO_RX;
  	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
  	GPIO_Init(UART4_GPIO, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin 	= UART4_GPIO_TX;
  	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
  	GPIO_Init(UART4_GPIO, &GPIO_InitStructure);	
#endif

#ifdef USING_UART5
	GPIO_InitStructure.GPIO_Pin 	= UART5_GPIO_RX;
  	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
  	GPIO_Init(UART5_RXGPIO, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin 	= UART5_GPIO_TX;
  	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
  	GPIO_Init(UART5_TXGPIO, &GPIO_InitStructure);  
#endif
}


static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	 
  	
	/* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
  /* 2 bit for pre-emption priority, 2 bits for subpriority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     // 配置 NVIC 为优先级组 2
	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;  // 配置中断源：按键 1 

  
	
#ifdef USING_UART1
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef USING_UART2
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef USING_UART3
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef USING_UART4
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef USING_UART5
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	  
#endif



}










static void UART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;

	/* uart init */
#ifdef USING_UART1
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);	 	

	USART_DMACmd(USART1, USART_DMAReq_Tx , ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 			
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);

	USART_Cmd(USART1, ENABLE);
#endif

/*#ifdef USING_UART2
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_Init(USART2, &USART_InitStructure);
	USART_ClockInit(USART2, &USART_ClockInitStructure);	

	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);		

	USART_Cmd(USART2, ENABLE);
#endif

#ifdef USING_UART3
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_Init(USART3, &USART_InitStructure);
	USART_ClockInit(USART3, &USART_ClockInitStructure);	 

	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART3, ENABLE);
#endif

#ifdef USING_UART4
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure); 

	USART_DMACmd(UART4, USART_DMAReq_Tx , ENABLE);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	USART_Cmd(UART4, ENABLE);
#endif

#ifdef USING_UART5
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	USART_Init(UART5, &USART_InitStructure); 
	
	USART_ITConfig(UART5, USART_IT_TC, ENABLE);

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(UART5, ENABLE);
#endif

*/
}









#ifdef USING_UART1
void uart1_rx_isr(void)
{
	if(Uart1_Rx_Cnt >= UART1_RX_SIZE)     
		Uart1_Rx_Cnt = 0; 
		
	Uart1_Rx_Buf[Uart1_Rx_Cnt++] = USART_ReceiveData(USART1); 			
	
	Uart1_Rx_Tmo_Cnt = 0;
	Uart1_Rx_Idle = BUSY;
}



void uart1_rx_tmo(void)
{ 
	
	static INT8U cnt;
	
	if(Uart1_Rx_Tmo_Cnt != 0xFFFE)
		Uart1_Rx_Tmo_Cnt ++;	

	if(Uart1_Rx_Tmo_Cnt == 15)//由原来的2变为了15
		if(Uart1_Rx_Idle == BUSY)
		{
			Uart1_Rx_Idle = IDLE;	
			Usart1_Rx_Len = Uart1_Rx_Cnt; 			
			Uart1_Rx_Cnt = 0; 					
      uart1_rx();			
		}
}

void dma1_ch4_isr(void)
{     
	//DMA_ClearFlag(DMA1_IT_TC4);	    	
	//DMA_Cmd(UART1_TX_DMA, DISABLE);	
}  

void uart1_tc_isr(void)
{
	
	uart1_tc_sig = 1; 	
	Uart1_Tx_Idle = IDLE; 	
}



void uart1_tx(INT8U *data, INT16U len)
{
	if(len > UART1_TX_SIZE)
		Uart1_Tx_Cnt = UART1_TX_SIZE;
	else
		Uart1_Tx_Cnt = len;	 

//	while(uart1_Tx_Idle != IDLE); 	
	
	Uart1_Tx_Idle = BUSY;			 					 
	memcpy(Uart1_Tx_Buf, data, Uart1_Tx_Cnt);

	//DMA_SetCurrDataCounter(UART1_TX_DMA, Uart1_Tx_Cnt); 
	//DMA_Cmd(UART1_TX_DMA, ENABLE);   
}
#else
void uart1_tx(INT8U *data, INT16U len){}	
#endif

	

#ifdef USING_UART4
void uart4_rx_isr(void)
{	
	if(Uart4_Rx_Cnt >= UART4_RX_SIZE)     
		Uart4_Rx_Cnt = 0;  	
		
	Uart4_Rx_Buf[Uart4_Rx_Cnt++] = USART_ReceiveData(UART4);
	
	Uart4_Rx_Tmo_Cnt = 0;
	Uart4_Rx_Idle = BUSY;
}

static void uart4_rx(void)
{
	
	uart4_rx_sig = 1; 			 		  		
}

void uart4_rx_tmo(void)
{ 
	if(Uart4_Rx_Tmo_Cnt != 0xFFFE)
		Uart4_Rx_Tmo_Cnt ++;	
	
	if(Uart4_Rx_Tmo_Cnt == 2)		
		if(Uart4_Rx_Idle == BUSY)
		{
			Uart4_Rx_Idle = IDLE;	
			Uart4_Rx_Len = Uart4_Rx_Cnt; 			
			Uart4_Rx_Cnt = 0; 					
			uart4_rx();	 		
		}
}

void dma2_ch5_isr(void)
{ 
  //DMA_ClearFlag(DMA2_IT_TC5);   
	//DMA_Cmd(UART4_TX_DMA, DISABLE);		 		 
	Uart4_Tx_Idle = IDLE;	
}

void uart4_tx(INT8U *data, INT16U len)
{  	
	if(len > UART4_TX_SIZE)
		Uart4_Tx_Cnt = UART4_TX_SIZE;
	else
		Uart4_Tx_Cnt = len;	 
	
//	while(uart4_Tx_Idle != IDLE);

	Uart4_Tx_Idle = BUSY; 					 
	memcpy(Uart4_Tx_Buf, data, Uart4_Tx_Cnt);
	
	//DMA_SetCurrDataCounter(UART4_TX_DMA, Uart4_Tx_Cnt); 
	//DMA_Cmd(UART4_TX_DMA, ENABLE);   	
}
#else
void uart4_tx(INT8U *data, INT16U len){}
#endif

	


void uart_rx_tmo(void)
{		
#ifdef USING_UART1	
	uart1_rx_tmo();
#endif
}



static void uart1_rx(void)
{ 
	
		uart1_rx_sig = 1; 				
}
