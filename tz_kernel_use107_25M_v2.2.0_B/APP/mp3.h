/*
 *DynaLnkQueue.h
 */

#ifndef _MP3_H
#define _MP3_H


#include    "os_cpu.h"


#define     MP3_KEY_PORT           GPIOA
#define     MP3_KEY_PIN			       GPIO_Pin_4
#define 		MP3_KEY_STATUS(x)      (x ? GPIO_SetBits(MP3_KEY_PORT, MP3_KEY_PIN) : GPIO_ResetBits(MP3_KEY_PORT,MP3_KEY_PIN)) 



#define     MP3_ACK_PORT           GPIOA
#define     MP3_ACK_PIN			       GPIO_Pin_6
#define     MP3_ACK_READ           GPIO_ReadInputDataBit(MP3_ACK_PORT, MP3_ACK_PIN)


#define     MP3_DECT_PORT          GPIOA
#define     MP3_DECT_PIN			     GPIO_Pin_5

	
#define     MP3_RESET_PORT         GPIOB
#define     MP3_RESET_PIN			     GPIO_Pin_12
#define 		MP3_RESET_STATUS(x)    (x ? GPIO_SetBits(MP3_RESET_PORT,MP3_RESET_PIN) : GPIO_ResetBits(MP3_RESET_PORT,MP3_RESET_PIN)) 




#define     MP3_DETECT(x)						( x ? (GPIO_SetBits(MP3_DECT_PORT,MP3_DECT_PIN )) : (GPIO_ResetBits(MP3_DECT_PORT,MP3_DECT_PIN )))

void mp3_volume(void);

void mp3play(INT16U nummber);

#endif /* _DYNALNKQUEUE_H */
