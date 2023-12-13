	//       打开iap.h代码如下：
	#ifndef __MOTORDRIVE_H__
	#define __MOTORDRIVE_H__

#define   SECOND_CYCLE             30      //多长时间走时一次 单位：秒 取值：1~59


//在驱动板子上添加了  9013和9012两种情况，此时用新版后，导通变为SSR_BS_STATUS(0) 
#define 		SSR_BS_STATUS(x)   	  (x ? GPIO_SetBits(GPIOB,GPIO_Pin_4) : GPIO_ResetBits(GPIOB,GPIO_Pin_4)) 
#define 		SSR_ZM_STATUS(x)   	  (x ? GPIO_SetBits(GPIOE,GPIO_Pin_2) : GPIO_ResetBits(GPIOE,GPIO_Pin_2)) 

#define     SPI_MOSI_GPIO_PORT     GPIOA
#define     SPI_MISO_GPIO_PORT		 GPIOA
#define     SPI_SCK_GPIO_PORT      GPIOA
#define     SPI_CS_PORT            GPIOA


#define     SPI_CS_PIN			       GPIO_Pin_4
#define     SPI_SCK_GPIO_PIN			 GPIO_Pin_5
#define     SPI_MISO_GPIO_PIN      GPIO_Pin_6
#define     SPI_MOSI_GPIO_PIN      GPIO_Pin_7

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************


//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

#define 		EAST_ZZ_IDLE     			(GPIO_ResetBits(GPIOB,GPIO_Pin_7))
#define 		EAST_FZ_IDLE     			(GPIO_ResetBits(GPIOB,GPIO_Pin_9)) 
#define 		EAST_ZZ   	     			(GPIO_SetBits(GPIOB,GPIO_Pin_7)) 
#define 		EAST_FZ   	     			(GPIO_SetBits(GPIOB,GPIO_Pin_9))
#define 		EAST_FK_PIN	     			(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12))



#define 		SOUTH_ZZ_IDLE     		(GPIO_ResetBits(GPIOE,GPIO_Pin_0))
#define 		SOUTH_FZ_IDLE     		(GPIO_ResetBits(GPIOE,GPIO_Pin_1)) 
#define 		SOUTH_ZZ   	          (GPIO_SetBits(GPIOE,GPIO_Pin_0))  
#define 		SOUTH_FZ   	          (GPIO_SetBits(GPIOE,GPIO_Pin_1))
#define 		SOUTH_FK_PIN	     		(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9))



#define 		WEST_ZZ_IDLE     			(GPIO_ResetBits(GPIOE,GPIO_Pin_4))
#define 		WEST_FZ_IDLE     			(GPIO_ResetBits(GPIOB,GPIO_Pin_6)) 
#define 		WEST_ZZ   	     			(GPIO_SetBits(GPIOE,GPIO_Pin_4))  
#define 		WEST_FZ   	     			(GPIO_SetBits(GPIOB,GPIO_Pin_6))  
#define 		WEST_FK_PIN	     			(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11))





#define 		NORTH_ZZ_IDLE     		(GPIO_ResetBits(GPIOE,GPIO_Pin_3))
#define 		NORTH_FZ_IDLE     		(GPIO_ResetBits(GPIOB,GPIO_Pin_8)) 
#define 		NORTH_ZZ   	     			(GPIO_SetBits(GPIOE,GPIO_Pin_3))  
#define 		NORTH_FZ   	     			(GPIO_SetBits(GPIOB,GPIO_Pin_8))  
#define 		NORTH_FK_PIN	     		(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10))



#define 		RUNLEDHIGH	     (GPIO_SetBits(GPIOA,GPIO_Pin_15))
#define 		RUNLEDLOW		     (GPIO_ResetBits(GPIOA,GPIO_Pin_15))


//#define 	SPEAKER_NOTICE 	   (GPIO_SetBits(GPIOD,GPIO_Pin_7)) //蜂鸣器动作指令	
//#define 	SPEAKER_SILENCE    (GPIO_ResetBits(GPIOD,GPIO_Pin_7)) 




	void MotorDriveOneStep(void);                             
	
	void normal_walk1(void);
  void run_reverse1(void);
	
	
	
	#endif


