
/*****************************************************************
          USART2 ��������
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

#include 	"USART2.h"
			
			INT8U 	USART2_RX_FIFO[USART2_RX_CNT];  		// ���廷������
			INT8U 	*pPut_USART2_RX_FIFO = USART2_RX_FIFO; 	// ���廷���������ָ��
			INT8U 	*pGet_USART2_RX_FIFO = USART2_RX_FIFO; 	// ���廷������ȡ��ָ��
			
			
			
	
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;   

//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	#if 0
	while((USART1->SR & 0x40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
	#endif
	
	
	#if 1
	while((USART2->SR & 0x40)==0);//ѭ������,ֱ���������   
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

          USART2 ����������ӣ��жϽ��յ���
          ���ܣ���temp���뻷������

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

          USART2 ��ʼ�� baud ������


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
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//ʹ�ܹ�������ʱ��;  
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
��������������������������������
��Ȩ����������ΪCSDN������quantum_520����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/weixin_52488303/article/details/120038667
*/

	
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
		USART_Init(USART2, &USART_InitStructure);
		
			

		// ��ʼ�� �ж����ȼ�		
		NVIC_InitStructure.NVIC_IRQChannel                     = USART2_IRQn;  //����2  �ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority   = 1;            //��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority          = 2;            //��Ӧ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd                  = ENABLE;       //ʹ��	
		NVIC_Init(&NVIC_InitStructure);    //�ж�������������ʼ��

    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�   /ʹ�ܴ���2�����ж�
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���	
		USART_ClearFlag(USART2, USART_FLAG_TXE);	   /* �巢����ɱ�־��Transmission Complete flag */   
		
		
	 // USART_ClearFlag(USART2, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
	 // USART_ClearFlag(USART2, USART_IT_TC); 			  //���жϣ�����һ�����жϺ����������ж�
	
	
		
		
}

/*****************************************************************

          �� USART2 ���ն���ȡ�ֽ� ���� temp
          �����ݷ��� 1�� ����Ϊ 0

	
			�źŰ巢�͸���ʱ��4���ֽڵ����� 
			0xbb+(MUSIC-1)+(Сʱ+1)+Ч���


			�źŰ巢�͸���ʱ��4���ֽڵ����� 
			0xbb+MUSIC+Сʱ+Ч���;����ԭ���ģ���Ϊ��ʱ©�����������£�
			
			��2012��4��30���糿����
			����˼·������ÿһ���ӵ�ʱ�������±������ݣ�
			0xbb,ʱ+��+��+��music-1��+��Сʱ+1��+����ʱ�Ĵ�����+Ч���	

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

          �� USART2 ����temp����
����com1�۲죡

*****************************************************************/
void USART2_SendByte(INT8U temp)
{
    USART_SendData(USART1, temp);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*****************************************************************

          �� USART2 �����ַ���

*****************************************************************/
void USART2_Printf(INT8U *pch)
{
    while(*pch != '\0'){
        USART1_SendByte(*pch);
        pch++;
    }
}


