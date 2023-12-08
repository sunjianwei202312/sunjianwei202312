
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



struct Timdata_sub      //����   
 {
  INT16U  	hour;       //ʱ
  INT16U  	minute;     //��
  INT16U  	second;     //��
  INT16U  	step;       //����
	 
	 
  INT8U 		state;      //��������״̬ 
  INT8U 		pulse;      //����ÿ���־
  INT8U 		timesource; //ʱԴ��Ч��־����Чʱ�����Զ�Уʱ
  INT8U 		warning;    //���Ͼ����־
  INT8U 		dis_delay;  //������ֹʹ�ܵȴ�ʱ��
  INT8U 		en_delay;   //��������ʹ�ܵȴ�ʱ��
 }; 




void send_byte_7279( INT8U out_byte);         //��7279����һ�ֽ�����
void write7279(INT8U cmd, INT8U dta); //7279д����
INT8U read7279(INT8U command);        //7279������
void  set_clock_tm(INT8U *tm);
void SetAndGet_clock_tm(INT8U hour,INT8U min,INT8U sec);


#endif


