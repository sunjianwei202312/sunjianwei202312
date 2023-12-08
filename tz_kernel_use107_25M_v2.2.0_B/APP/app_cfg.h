
/*
*********************************************************************************************************
*
*             	主函数包含头文件

*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*               定义任务优先级
*********************************************************************************************************
*/

#define  FATFS_MUTEX_PRIO                                  3
#define  USART1_MUTEX_PRIO                                 4
#define  USART2_MUTEX_PRIO                                 5

#define  APP_TASK_START_PRIO                               9
#define  APP_TASK1_PRIO                                   10
#define  APP_TASK2_PRIO                                   11
#define  APP_TASK3_PRIO                                   12
#define  APP_TASK4_PRIO                                   13
#define  APP_TASK5_PRIO                                   14
#define  APP_TASK6_PRIO                                   15
#define  APP_TASK7_PRIO                                   16
#define  APP_TASK8_PRIO                                   17



/*
*********************************************************************************************************
*               定义任务堆栈大小
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE                         256
#define  APP_TASK1_STK_SIZE                              256
#define  APP_TASK2_STK_SIZE                              256


#define  APP_TASK3_STK_SIZE                              256
#define  APP_TASK4_STK_SIZE                              256
#define  APP_TASK5_STK_SIZE                              256
#define  APP_TASK6_STK_SIZE                              (256)
#define  APP_TASK7_STK_SIZE                              256
#define  APP_TASK8_STK_SIZE                              256



/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif
