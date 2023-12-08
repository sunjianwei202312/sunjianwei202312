
/*****************************************************************
          USART1 驱动程序
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


#include 	"USART1.h"
#include 	"uart.h"

extern INT8U 	Uart1_Rx_Buf[UART1_RX_SIZE];

 
INT8U   receive_data[UART1_RX_SIZE]={0};
INT8U   RX_data[26] = {0};
INT8U 	USART1_RX_FIFO[USART1_RX_CNT];  			// 定义环形数据
INT8U 	*pPut_USART1_RX_FIFO = USART1_RX_FIFO; 	// 定义环形数组放数指针
INT8U 	*pGet_USART1_RX_FIFO = USART1_RX_FIFO; 	// 定义环形数组取数指针

/*****************************************************************

          USART1 接收数据入队，中断接收调用
          功能：将temp放入环形数组

*****************************************************************/
void USART1_RXLoop(INT8U temp)
{
    *pPut_USART1_RX_FIFO = temp;
    if(pPut_USART1_RX_FIFO == &USART1_RX_FIFO[USART1_RX_CNT - 1]){
        pPut_USART1_RX_FIFO = &USART1_RX_FIFO[0];	
    }else{
        pPut_USART1_RX_FIFO++;
    }
}

/*****************************************************************
我们的原理是DMA1的通道5为USART1的RX引脚
          USART1 初始化 baud 波特率

记住顺序，
1.先使能GPIOB和AFIO，
2.再调用GPIO_PinRemapConfig函数，
3.然后再初始化gpio引脚，
4.再使能USART1，
5.再配置串口，
6.需要中断的话再配置中断，切记不要搞错。
其它系列芯片的顺序也是一样的，但是映射的函数是不一样的，请查询后使用。

*****************************************************************/


void USART1_Init(INT32U baud)
{
    USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
	  DMA_InitTypeDef DMA_Initstructure;
    NVIC_InitTypeDef NVIC_InitStructure;
   
  
	
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//使能功能外设时钟;  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                       //然后是使能AFIO时钟：
		
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		/* 配置USART1-TX脚 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		  // TX1  推挽模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;   /* 配置USART1-RX脚 */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	     		// RX1  悬空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
		

    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
		
		

		// 初始化 中断优先级		
		NVIC_InitStructure.NVIC_IRQChannel                     = USART1_IRQn;  //串口1  中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority   = 1;            //抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority          = 0;            //响应优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd                  = ENABLE;       //使能	
		NVIC_Init(&NVIC_InitStructure);    //中断向量控制器初始化
		//开启中断并且初始化 NVIC，使能中断（如果需要开启串口中断才需要这个步骤）。
    #if 0
			//配置中断模式  有数据来即中断
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			USART_Cmd(USART1,ENABLE);//使能串口。
		#endif

				
				
				
		USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);//串口空闲中断+DMA接收数据  added  by sjw  //打开接收完毕中断
		USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
		USART_ClearFlag(USART1, USART_IT_IDLE); 			//清中断，以免一启用中断后立即产生中断
		









    DMA_DeInit(DMA1_Channel5);  //复位DMA1通道5！！added by sjw
    DMA_DeInit(UART1_RX_DMA);
		

		//STM32学习-DMA介绍及一般使用方法  此文将DMA1和DMA2的通道对应的片内外设进行了详细的介绍，不错！！(各个通道的DMAx请求)added by sjw
		//https://blog.csdn.net/m0_52850679/article/details/124506315
			//DMA配置
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//开启DMA时钟/
		DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USART1->DR);
		DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)receive_data;//Uart1_Rx_Buf;//
		DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_Initstructure.DMA_BufferSize =UART1_RX_SIZE;// 128; 数据传输量！ //DMA通道的DMA缓存的大小   added by sjw  
		DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
		DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_Initstructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;//工作在正常缓存模式
		DMA_Initstructure.DMA_Priority = DMA_Priority_High;//DMA通道x拥有高优先级 
		DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;       //DMA通道x没有设置为内存到内存传输
		DMA_Init(DMA1_Channel5, &DMA_Initstructure);
		 /* Enable USART1 DMA Rx request */
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    
		
			
			//配置中断优先级
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
		DMA_Cmd(DMA1_Channel5,ENABLE); //使能DMA1通道5  /* Enable DMA1 Channel5 */
			/*
————————————————
版权声明：本文为CSDN博主「Yahong.W」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/m0_52850679/article/details/124506315
*/
		
		
		
   
		
		USART_Cmd(USART1,ENABLE);//使能串口。
		
	
		
}

//解包主要程序：
void unpack_usart(void){

		INT16U i = 0;
		INT8U j = 0;
		for(i=0;i<1280;i++){
			if((receive_data[i]==0xAA) &&(receive_data[i+1]==0xBB)){	
				for(j=0;j<26;j++)
				{
					RX_data[j] = receive_data[i];
					i++;
				}
				return;
			}
		}

}


static	void USART1_Config(void){
	GPIO_InitTypeDef  		GPIO_InitStruct;
	USART_InitTypeDef 		USART_InitStruct;
	USART_ClockInitTypeDef  USART_ClockInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_TIM1 |RCC_APB2Periph_USART1, ENABLE  );
		// 串口1  TX1
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;				//	选中管脚PA.9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;// 最高输出速率50MHz
	GPIO_Init(GPIOA, &GPIO_InitStruct);				    // 选择A端口
	// 串口1  RX1
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;			  //选中管脚PA.10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStruct);				    //选择A端口
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE  );
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;			// 时钟低电平活动
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;				    // 时钟低电平
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;				  // 时钟第二个边沿进行数据捕获
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable;	// 最后一位数据的时钟脉冲不从SCLK输出
	
	/* Configure the USART1 synchronous paramters */
	USART_ClockInit(USART1, &USART_ClockInitStruct);					// 时钟参数初始化设置
	USART_InitStruct.USART_BaudRate = 115200;						      // 波特率为：115200
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;  // 8位数据
	USART_InitStruct.USART_StopBits = USART_StopBits_1;				// 在帧结尾传输1个停止位
	USART_InitStruct.USART_Parity = USART_Parity_No ;				  // 奇偶失能
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能
	
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
	/* Configure USART1 basic and asynchronous paramters */
	USART_Init(USART1, &USART_InitStruct);

	//清除标志位，否则第1位数据会丢失
  	USART_ClearFlag(USART1,USART_FLAG_TC);
	  /* Enable USART1 */
	USART_ClearFlag(USART1, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
	USART_ClearFlag(USART1, USART_IT_TC); 			  //清中断，以免一启用中断后立即产生中断
	//USART_ITConfig(USART1,USART_IT_TC, ENABLE);		//使能USART1发送中断源,系统瘫痪！
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);	//使能USART1接收中断源
	USART_Cmd(USART1, ENABLE);					    //USART1总开关：开启 
}






/*****************************************************************

          从 USART1 接收队列取字节 放入 temp
          有数据返回 1， 否则为 0

*****************************************************************/
INT8U USART1_GetByte(INT8U *temp)
{
    if(pGet_USART1_RX_FIFO == pPut_USART1_RX_FIFO){
        return(0);
    }

    *temp = *pGet_USART1_RX_FIFO;
    if(pGet_USART1_RX_FIFO == &USART1_RX_FIFO[USART1_RX_CNT - 1]){
        pGet_USART1_RX_FIFO = &USART1_RX_FIFO[0];
    }else{
        pGet_USART1_RX_FIFO++;
    }
    return(1);
}

/*****************************************************************

          从 USART1 发送temp数据

*****************************************************************/
void USART1_SendByte(INT8U temp)
{
    USART_SendData(USART1, temp);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*****************************************************************

          从 USART1 发送字符串

*****************************************************************/
void USART1_Printf(INT8U *pch)
{
    while(*pch != '\0'){
        USART1_SendByte(*pch);
        pch++;
    }
}


