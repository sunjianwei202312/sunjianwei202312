/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : includes.h
* Version       : V1.10
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>

#include  "stm32f10x_conf.h"
//#include  "stm32f10x.h"

#include  "app_cfg.h"
#include  "os_cfg.h"
//#include  "..\uCOS-II\uC-CPU\cpu.h"
//#include  "..\uCOS-II\uC-CPU\cpu_def.h"
//#include  "..\uCOS-II\Ports\os_cpu.h"
//#include  "..\uCOS-II\Source\ucos_ii.h"

//#include  "..\BSP\bsp.h"

//#include  "..\Device\USART1.h"

//#include  "..\Device\USART2.h"

//#include  "..\Device\SD_driver.h"

//#include  "..\FatFs\src\ff.h"

//#include  "..\Device\VS1003B.h"

#include  "cpu.h"
#include  "cpu_def.h"
#include  "os_cpu.h"
#include  "bsp.h"

#include  "USART1.h"

#include  "USART2.h"

//#include  "SD_driver.h"

#include  "ff.h"

//#include  "VS1003B.h"

#include   "ucos_ii.h"


#define    USART_REC_LEN  			 (10)         //定义最大接收字节数 200

extern uint16_t USART_RX_STA;                
extern uint8_t  UsartRxBuf[USART_REC_LEN];    

#endif

