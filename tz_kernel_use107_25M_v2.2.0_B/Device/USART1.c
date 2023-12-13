
/*****************************************************************
          USART1 ��������
          �� �� �ˣ�LJ128
          ����ʱ�䣺2008��6��3��
		  1 const char * ch 
const char * ch; const��*ǰ���ʾ����һ��  �ַ�������ָ�룬����ָ����ַ������ܱ��޸ģ�
�������ָ���ָ����Ըı䣬����char const *ch��һ���ģ����磺const char *ch="123";
//ָ�����ַ���123,123�����ݲ��ܱ��޸ģ������Ըı�ch��ָ��ch="Hello World!";//���Ըı�ch��ָ�� 


���const��*�ĺ��棬���ʾ����һ��ָ�볣��������ָ���ܱ��޸ģ��������޸�����ָ������ݣ����磺
1234 char c[] = "123";char * const ch=c;//ch��ָ���ܱ��޸ģ�������ָ���������������Ա��޸ģ�
//��������c�Ǹ��ַ����飬���ԣ�����ͨ��ch�޸�c�����ֵch[0]='4';//�޸�c[0]Ϊ4,c���"423" 
*****************************************************************/


#include 	"USART1.h"
#include 	"uart.h"

extern INT8U 	Uart1_Rx_Buf[UART1_RX_SIZE];

 
INT8U   receive_data[UART1_RX_SIZE]={0};
INT8U   RX_data[26] = {0};
INT8U 	USART1_RX_FIFO[USART1_RX_CNT];  			// ���廷������
INT8U 	*pPut_USART1_RX_FIFO = USART1_RX_FIFO; 	// ���廷���������ָ��
INT8U 	*pGet_USART1_RX_FIFO = USART1_RX_FIFO; 	// ���廷������ȡ��ָ��

/*****************************************************************

          USART1 ����������ӣ��жϽ��յ���
          ���ܣ���temp���뻷������

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
���ǵ�ԭ����DMA1��ͨ��5ΪUSART1��RX����
          USART1 ��ʼ�� baud ������

��ס˳��
1.��ʹ��GPIOB��AFIO��
2.�ٵ���GPIO_PinRemapConfig������
3.Ȼ���ٳ�ʼ��gpio���ţ�
4.��ʹ��USART1��
5.�����ô��ڣ�
6.��Ҫ�жϵĻ��������жϣ��мǲ�Ҫ���
����ϵ��оƬ��˳��Ҳ��һ���ģ�����ӳ��ĺ����ǲ�һ���ģ����ѯ��ʹ�á�

*****************************************************************/


void USART1_Init(INT32U baud)
{
    USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
	  DMA_InitTypeDef DMA_Initstructure;
    NVIC_InitTypeDef NVIC_InitStructure;
   
  
	
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//ʹ�ܹ�������ʱ��;  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                       //Ȼ����ʹ��AFIOʱ�ӣ�
		
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		/* ����USART1-TX�� */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		  // TX1  ����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;   /* ����USART1-RX�� */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	     		// RX1  ��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
		

    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
		
		

		// ��ʼ�� �ж����ȼ�		
		NVIC_InitStructure.NVIC_IRQChannel                     = USART1_IRQn;  //����1  �ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority   = 1;            //��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority          = 0;            //��Ӧ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd                  = ENABLE;       //ʹ��	
		NVIC_Init(&NVIC_InitStructure);    //�ж�������������ʼ��
		//�����жϲ��ҳ�ʼ�� NVIC��ʹ���жϣ������Ҫ���������жϲ���Ҫ������裩��
    #if 0
			//�����ж�ģʽ  �����������ж�
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			USART_Cmd(USART1,ENABLE);//ʹ�ܴ��ڡ�
		#endif

				
				
				
		USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);//���ڿ����ж�+DMA��������  added  by sjw  //�򿪽�������ж�
		USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
		USART_ClearFlag(USART1, USART_IT_IDLE); 			//���жϣ�����һ�����жϺ����������ж�
		









    DMA_DeInit(DMA1_Channel5);  //��λDMA1ͨ��5����added by sjw
    DMA_DeInit(UART1_RX_DMA);
		

		//STM32ѧϰ-DMA���ܼ�һ��ʹ�÷���  ���Ľ�DMA1��DMA2��ͨ����Ӧ��Ƭ�������������ϸ�Ľ��ܣ�������(����ͨ����DMAx����)added by sjw
		//https://blog.csdn.net/m0_52850679/article/details/124506315
			//DMA����
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//����DMAʱ��/
		DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USART1->DR);
		DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)receive_data;//Uart1_Rx_Buf;//
		DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_Initstructure.DMA_BufferSize =UART1_RX_SIZE;// 128; ���ݴ������� //DMAͨ����DMA����Ĵ�С   added by sjw  
		DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
		DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_Initstructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;//��������������ģʽ
		DMA_Initstructure.DMA_Priority = DMA_Priority_High;//DMAͨ��xӵ�и����ȼ� 
		DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;       //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
		DMA_Init(DMA1_Channel5, &DMA_Initstructure);
		 /* Enable USART1 DMA Rx request */
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    
		
			
			//�����ж����ȼ�
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
		DMA_Cmd(DMA1_Channel5,ENABLE); //ʹ��DMA1ͨ��5  /* Enable DMA1 Channel5 */
			/*
��������������������������������
��Ȩ����������ΪCSDN������Yahong.W����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/m0_52850679/article/details/124506315
*/
		
		
		
   
		
		USART_Cmd(USART1,ENABLE);//ʹ�ܴ��ڡ�
		
	
		
}

//�����Ҫ����
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
		// ����1  TX1
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;				//	ѡ�йܽ�PA.9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	// �����������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;// ����������50MHz
	GPIO_Init(GPIOA, &GPIO_InitStruct);				    // ѡ��A�˿�
	// ����1  RX1
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;			  //ѡ�йܽ�PA.10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStruct);				    //ѡ��A�˿�
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE  );
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;			// ʱ�ӵ͵�ƽ�
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;				    // ʱ�ӵ͵�ƽ
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;				  // ʱ�ӵڶ������ؽ������ݲ���
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable;	// ���һλ���ݵ�ʱ�����岻��SCLK���
	
	/* Configure the USART1 synchronous paramters */
	USART_ClockInit(USART1, &USART_ClockInitStruct);					// ʱ�Ӳ�����ʼ������
	USART_InitStruct.USART_BaudRate = 115200;						      // ������Ϊ��115200
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;  // 8λ����
	USART_InitStruct.USART_StopBits = USART_StopBits_1;				// ��֡��β����1��ֹͣλ
	USART_InitStruct.USART_Parity = USART_Parity_No ;				  // ��żʧ��
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��
	
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
	/* Configure USART1 basic and asynchronous paramters */
	USART_Init(USART1, &USART_InitStruct);

	//�����־λ�������1λ���ݻᶪʧ
  	USART_ClearFlag(USART1,USART_FLAG_TC);
	  /* Enable USART1 */
	USART_ClearFlag(USART1, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
	USART_ClearFlag(USART1, USART_IT_TC); 			  //���жϣ�����һ�����жϺ����������ж�
	//USART_ITConfig(USART1,USART_IT_TC, ENABLE);		//ʹ��USART1�����ж�Դ,ϵͳ̱����
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);	//ʹ��USART1�����ж�Դ
	USART_Cmd(USART1, ENABLE);					    //USART1�ܿ��أ����� 
}






/*****************************************************************

          �� USART1 ���ն���ȡ�ֽ� ���� temp
          �����ݷ��� 1�� ����Ϊ 0

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

          �� USART1 ����temp����

*****************************************************************/
void USART1_SendByte(INT8U temp)
{
    USART_SendData(USART1, temp);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*****************************************************************

          �� USART1 �����ַ���

*****************************************************************/
void USART1_Printf(INT8U *pch)
{
    while(*pch != '\0'){
        USART1_SendByte(*pch);
        pch++;
    }
}


