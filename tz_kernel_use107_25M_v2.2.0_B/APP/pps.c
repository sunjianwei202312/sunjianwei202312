#include <stm32f10x.h>
//#include "tmcode.h"
#include "gps.h"
//#include "fsmc.h"
//#include "config.h"
//#include "led.h"
#include "ds3231.h"	
#include "uart.h"
//#include "pps.h"



/*
	PA11----------------------PPS
*/     
extern INT32U 		NTP;


extern INT8U pps1_rising_sig;
extern INT8U pps1_falling_sig;	
extern INT8U pps1_tim;
extern INT8U pps1_status;

static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void NVIC_Configuration(void);
static void EXTI_Configuration(void);





static void RCC_Configuration(void)
{			  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	
}

static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
   
    GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void EXTI_Configuration(void) 
{
	EXTI_InitTypeDef EXTI_InitStructure;  	
		 
    EXTI_InitStructure.EXTI_Line 	= EXTI_Line11;
    EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);	 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);

    EXTI_ClearITPendingBit(EXTI_Line11);	
}
	    
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void pps_init(void)
{
  RCC_Configuration();
	GPIO_Configuration();        
	EXTI_Configuration();
	NVIC_Configuration(); 	    
} 
	   
void pps_isr(void) 
{  	
	
	static u8 _pps_status; 	

	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11))	
		pps1_rising_sig = 1;	   
	else			   
		pps1_falling_sig = 1; 
		
	if(pps1_rising_sig)
	{
		if((98<pps1_tim) && (pps1_tim<102))
		{		
			if(_pps_status == 1)
			{  		
				if(pps1_status < 0xFF) 			
					pps1_status ++;
			}
			else
				pps1_status = 0;	
		}
		else
			pps1_status = 0;		

		pps1_tim = 0;  		
	}
	else	if(pps1_falling_sig)
	{
		if((8 < pps1_tim < 22))//if(8 < pps1_tim < 22) 使能此语句，有警告存在，采用下面的指令！！
		{			 		
			if(pps1_falling_sig)		
				_pps_status = 1;
			else 
			{			
				_pps_status = 0;
				pps1_status = 0;
			}	
		}
		else
		{
			_pps_status = 0;
			pps1_status = 0;
		}
			
		pps1_falling_sig = 0;	
	} 



   	if(pps1_rising_sig){//50ms干扰的滤除！
			NTP ++;		
	 	}
}


void set_pps1_sig(void)
{	
 // if(GPSStatus!=GPS_Valid)
	{
	
			if(pps1_tim > 101) 	  		
				if(pps1_rising_sig == 0)		
						pps1_status = 0; 	

				
			if(pps1_falling_sig)
				pps1_falling_sig = 0;
			
			if(pps1_rising_sig)
				pps1_rising_sig = 0;
	}
	
} 


