#ifndef _uart_h
#define _uart_h
	   
/*
	u1: disp
	u2: gps
	u3: bus
	u4: 422
	u5: 232/422
*/


#define USING_UART1
#define USING_UART2
#define USING_UART3
#define USING_UART4	 
#define USING_UART5


#define UART1_RX_SIZE 	150//76//64    added by sjw  
#define UART1_TX_SIZE 	256

#define UART2_RX_SIZE 	64 
#define UART2_TX_SIZE 	64  

#define UART3_RX_SIZE 	64  
#define UART3_TX_SIZE 	64

#define UART4_RX_SIZE 	256  
#define UART4_TX_SIZE 	76  //add by sjw

#define UART5_RX_SIZE 	64  
#define UART5_TX_SIZE 	64




/* USART1 */
#define UART1_GPIO_TX		    GPIO_Pin_9
#define UART1_GPIO_RX		    GPIO_Pin_10
#define UART1_GPIO			    GPIOA
#define RCC_APBPeriph_UART1	RCC_APB2Periph_USART1
#define UART1_TX_DMA		    DMA1_Channel4
#define UART1_RX_DMA		    DMA1_Channel5



/* USART2 */
#define UART2_GPIO_TX	      GPIO_Pin_5
#define UART2_GPIO_RX	      GPIO_Pin_6
#define UART2_GPIO	    	  GPIOD
#define RCC_APBPeriph_UART2	RCC_APB1Periph_USART2	 
#define UART2_TX_DMA		    DMA1_Channel7
#define UART2_RX_DMA		    DMA1_Channel6 //查表DMA，我发现通道搞反了。----sjw




/* USART3 */
#define UART3_GPIO_RX		    GPIO_Pin_9
#define UART3_GPIO_TX		    GPIO_Pin_8
#define UART3_GPIO			    GPIOD
#define RCC_APBPeriph_UART3	RCC_APB1Periph_USART3
#define UART3_TX_DMA		    DMA1_Channel2
#define UART3_RX_DMA		    DMA1_Channel3	




/* UART4 */
#define UART4_GPIO_TX		    GPIO_Pin_10	
#define UART4_GPIO_RX		    GPIO_Pin_11	
#define UART4_GPIO			    GPIOC
#define RCC_APBPeriph_UART4	RCC_APB1Periph_UART4 
#define UART4_TX_DMA		    DMA2_Channel5
#define UART4_RX_DMA		    DMA2_Channel3





/* UART5 */
#define UART5_GPIO_TX	      GPIO_Pin_12	
#define UART5_GPIO_RX	      GPIO_Pin_2	
#define UART5_TXGPIO	      GPIOC
#define UART5_RXGPIO	      GPIOD
#define RCC_APBPeriph_UART5	RCC_APB1Periph_UART5 	





void uart_init(void);



/* uart1 */
void uart1_rx_isr(void);
void dma1_ch4_isr(void);
void uart1_tx(u8*, u16);
void uart1_tc_isr(void);

/* uart2 */
void uart2_rx_isr(void);
void dma1_ch7_isr(void);
void uart2_tx(u8*, u16);

/* uart3 */
void uart3_rx_isr(void);
void dma1_ch2_isr(void);
void uart3_tx(u8*, u16);

/* uart4 */
void uart4_rx_isr(void);
void dma2_ch5_isr(void);
void uart4_tx(u8*, u16);
void uart4_rx_tmo(void);

/* uart5 */
void uart5_rx_isr(void);
void uart5_tx(u8*, u16);
void uart5_rx_tmo(void);

void Uart1_Init(u32 bound);
void uart1_init(u32 bound);


void uart_rx_tmo(void);

enum {BUSY = 1, IDLE};	

#endif
