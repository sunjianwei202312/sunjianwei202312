
/*****************************************************************
          USART2 驱动程序
          创 建 人：LJ128
          创建时间：2008年6月3日
		  1 const char * ch 
const char * ch; const在*前面表示这是一个  字符串常量指针，它所指向的字符串不能被修改，
但是这个指针的指向可以改变，它和char const *ch是一样的，比如：const char *ch="123";
//指向常量字符串123,123的内容不能被修改，但可以改变ch的指向ch="Hello World!";//可以改变ch的指向 


如果const在*的后面，则表示这是一个指针常量，它的指向不能被修改，但可以修改批所指向的内容，比如：
1234 char c[] = "123";char * const ch=c;//ch的指向不能被修改，但它所指向的内容视情况可以被修改，
//比如由于c是个字符数组，所以，可以通过ch修改c数组的值ch[0]='4';//修改c[0]为4,c变成"423" 
*****************************************************************/

#include 	"USART2.h"
			
			INT8U 	USART2_RX_FIFO[USART2_RX_CNT];  		// 定义环形数据
			INT8U 	*pPut_USART2_RX_FIFO = USART2_RX_FIFO; 	// 定义环形数组放数指针
			INT8U 	*pGet_USART2_RX_FIFO = USART2_RX_FIFO; 	// 定义环形数组取数指针
			
			
			
	
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;   

//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	#if 0
	while((USART1->SR & 0x40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
	#endif
	
	
	#if 1
	while((USART2->SR & 0x40)==0);//循环发送,直到发送完毕   
	USART2->DR = (u8) ch;      
	return ch;
	#endif
	
	
}

_ttywrch(int ch) 
{ 
ch = ch; 
} 

#endif		
			

/*****************************************************************

          USART2 接收数据入队，中断接收调用
          功能：将temp放入环形数组

*****************************************************************/
void USART2_RXLoop(INT8U temp)
{
    *pPut_USART2_RX_FIFO = temp;
    if(pPut_USART2_RX_FIFO == &USART2_RX_FIFO[USART2_RX_CNT - 1]){
        pPut_USART2_RX_FIFO = &USART2_RX_FIFO[0];	
    }else{
        pPut_USART2_RX_FIFO++;
    }
}

/*****************************************************************

          USART2 初始化 baud 波特率


*****************************************************************/
void USART2_Init(INT32U baud)
{
   
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
	  DMA_InitTypeDef DMA_Initstructure;
    NVIC_InitTypeDef NVIC_InitStructure;
   

	  //USART,PD5-TX,PD6-RX
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);                      
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//使能功能外设时钟;  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);

	
	
	  
    //TX 
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed    = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD,&GPIO_InitStructure);    


    //RX 
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
		
		/*
————————————————
版权声明：本文为CSDN博主「quantum_520」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_52488303/article/details/120038667
*/

	
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
		USART_Init(USART2, &USART_InitStructure);
		
			

		// 初始化 中断优先级		
		NVIC_InitStructure.NVIC_IRQChannel                     = USART2_IRQn;  //串口2  中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority   = 1;            //抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority          = 2;            //响应优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd                  = ENABLE;       //使能	
		NVIC_Init(&NVIC_InitStructure);    //中断向量控制器初始化

    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断   /使能串口2接收中断
    USART_Cmd(USART2, ENABLE);                    //使能串口	
		USART_ClearFlag(USART2, USART_FLAG_TXE);	   /* 清发送完成标志，Transmission Complete flag */   
		
		
	 // USART_ClearFlag(USART2, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
	 // USART_ClearFlag(USART2, USART_IT_TC); 			  //清中断，以免一启用中断后立即产生中断
	
	
		
		
}

/*****************************************************************

          从 USART2 接收队列取字节 放入 temp
          有数据返回 1， 否则为 0

	
			信号板发送给报时板4个字节的数据 
			0xbb+(MUSIC-1)+(小时+1)+效验和


			信号板发送给报时板4个字节的数据 
			0xbb+MUSIC+小时+效验和;这是原来的，因为报时漏报，处理如下：
			
			在2012年4月30日早晨处理
			核心思路是主板每一分钟的时候发送以下报文数据：
			0xbb,时+分+秒+（music-1）+（小时+1）+（报时寄存器）+效验和	

*****************************************************************/
INT8U USART2_GetByte(INT8U *temp)
{
    if(pGet_USART2_RX_FIFO == pPut_USART2_RX_FIFO){
        return(0);
    }

    *temp = *pGet_USART2_RX_FIFO;
    if(pGet_USART2_RX_FIFO == &USART2_RX_FIFO[USART2_RX_CNT - 1]){
        pGet_USART2_RX_FIFO = &USART2_RX_FIFO[0];
    }else{
        pGet_USART2_RX_FIFO++;
    }
    return(1);
}

/*****************************************************************

          从 USART2 发送temp数据
借用com1观察！

*****************************************************************/
void USART2_SendByte(INT8U temp)
{
    USART_SendData(USART1, temp);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*****************************************************************

          从 USART2 发送字符串

*****************************************************************/
void USART2_Printf(INT8U *pch)
{
    while(*pch != '\0'){
        USART1_SendByte(*pch);
        pch++;
    }
}


