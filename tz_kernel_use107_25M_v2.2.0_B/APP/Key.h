
#ifndef _key_h
#define _key_h

#include  "OS_CPU.h"



#define USE_MOTOR_ONE

/*
#define USE_MOTOR_TWO   
#define USE_MOTOR_THREE
#define USE_MOTOR_FOUR
*/
 

enum   KeyRun_Order{NC,WALK,RUN_FORWARD,STOP,RUN_REVERSE,CALIB};
enum   _useKey{KEY_WAIT=0,KEY_MAS_TIME,KEY_SUB_STATE,KEY_SUB_TIME,KEY_REPORT,KEY_LIGHT,KEY_DATE,KEY_RESET}; 



struct Timdata_sub      //子钟   
 {
  INT16U  	hour;       //时
  INT16U  	minute;     //分
  INT16U  	second;     //秒
  INT16U  	step;       //步数
	 
	 
  INT8U 		state;      //子钟运行状态 
  INT8U 		pulse;      //子钟每秒标志
  INT8U 		timesource; //时源有效标志，有效时进行自动校时
  INT8U 		warning;    //故障警告标志
  INT8U 		dis_delay;  //驱动禁止使能等待时间
  INT8U 		en_delay;   //驱动开启使能等待时间
 }; 




void send_byte_7279( INT8U out_byte);         //向7279发送一字节数据
void write7279(INT8U cmd, INT8U dta); //7279写命令
INT8U read7279(INT8U command);        //7279度命令
void  set_clock_tm(INT8U *tm);
void SetAndGet_clock_tm(INT8U hour,INT8U min,INT8U sec);


#endif


