#include  "motordrive.h"
#include 	"includes.h"
#include  "key.h"
#include  "gps.h"


#define    USE_ONE_STEMP

void normal_walk1(void);
void run_reverse1(void);

void MathEastSub_Qd220(mytime * ux);
void MathEastAdd_Qd220(mytime * ux);

INT8U  Reset_Set1=0xaa,Reset_Set2=0xaa,//������������־λ     
       Reset_Set3=0xaa,Reset_Set4=0xaa;


extern config 		board;
extern enum   KeyRun_Order Key_Subclock_State1;


extern void  EnterEastNormalRun(void);
extern void  EnterSouthNormalRun(void);
extern void  EnterWestNormalRun(void);
extern void  EnterNorthNormalRun(void);


extern void  EnterEastFzRun();
extern void  EnterSouthFzRun(void);
extern void  EnterWestFzRun(void);
extern void  EnterNorthFzRun(void);


extern void MainProcessTimeSub(config data,INT8U order);



typedef enum _motor_status{
	motor_stop,
	motor_zz,
	motor_fz,
	motor_pulse_low,
	motor_pulse_low_continual,
	motor_pulse_low_stop,
	motor_pulse_high,
	motor_pulse_high_continual,
	motor_pulse_high_stop
	
}Motor_Status;



 INT8U  MotorZZ_Flag,MotorFZ_Flag;


struct   Timdata_sub     Subclock1={0x0000,0x0000,0x0000,0x00,0xa0,0x00,0x00,0x00,0x00,0x00},
                         Subclock2={0x0000,0x0000,0x0000,0x00,0xa0,0x00,0x00,0x00,0x00,0x00},
                         Subclock3={0x0000,0x0000,0x0000,0x00,0xa0,0x00,0x00,0x00,0x00,0x00},
                         Subclock4={0x0000,0x0000,0x0000,0x00,0xa0,0x00,0x00,0x00,0x00,0x00};


       


/*********************************
*�� �ܣ�����1����
*�� �룺
*********************************/




/*********************************
*���ܣ�����1��ʱ
*
*********************************/

/*********************************
*���ܣ�����1��׷ 
* 
*********************************/

/*********************************
*���ܣ�����1��׷ 
*
*********************************/
/*
void run_reverse1(void)
{
	
	
		#ifdef USE_MOTOR_ONE	
			 EnterEastFzRun();
		#elif   USE_MOTOR_TWO
			 EnterSouthFzRun();
		#elif   USE_MOTOR_THREE
			 EnterWestFzRun();
		#else
			 EnterNorthFzRun();
		#endif
}
*/

/*********************************
*���ܣ� У׼����1
*
*********************************/


 
 
/*********************************
*���ܣ�����1�Զ�׷ʱ
*
*********************************/
 
 
 

/*********************************
*���ܣ������λ
*
*********************************/



void MathEastAdd_Qd220(mytime * ux){
	 ux->second+=30;
	 if(ux->second>=60){
	    ux->second=0;
		  ux->minute+=1;
			if(ux->minute>=60){
				ux->minute=0;
				ux->hour++;
				ux->hour%=12;
			}	
   }
}
void MathEastSub_Qd220(mytime * ux){
   ux->second-=30;
	 if(ux->second>=0xe2){
	    ux->second=30;
		  ux->minute-=1;
			if(ux->minute==0xff){
				ux->minute=59;
				ux->hour-=1;
				if(ux->hour==0xff)
				ux->hour=11;
				ux->hour%=12;
			}	
	}
}

  

//��������̵����������۵ĽǶ�Ϊ1�ȣ���ôԽ�������۵�ʱ����13.9���루���ת��180����Ҫ2.5���ӣ�
//����������������£�����ͬʱ�����ۣ�ִ��ʱ����Ǵ�Լ50*4=200�������ң����ᶪ�жϣ���
INT8U compare_zf(mytime *u,  mytime *v){ 
	static INT8U flag;
	
	if(u->hour%12==v->hour){/*��ʾĸ��Сʱ������Сʱ���*/	
		
		if(u->minute==v->minute){//��ʾĸ�ӷ��������ӷ������
			
			 switch(Key_Subclock_State1)
			 {
				// case  NC:
				 //case  WALK:
				 case  RUN_FORWARD:
						if(v->second==0){//���ӵ���ֻ��Ϊ0���30�룡added by sjw
							if(u->second>=30){
									Key_Subclock_State1=RUN_FORWARD; EnterEastNormalRun();return (0);
							}else if(u->second>=53){
									Key_Subclock_State1=RUN_FORWARD; EnterEastNormalRun();return (0);
							}else{
									EAST_ZZ_IDLE;
									EAST_FZ_IDLE;
									MotorZZ_Flag=0;
									MotorFZ_Flag=0;
									Key_Subclock_State1=WALK;
									return (1);
							} 
					 }else if(v->second==30){
									if (u->second>=53){
										Key_Subclock_State1=RUN_FORWARD; EnterEastNormalRun();return (0);
									}else{
										EAST_ZZ_IDLE;
										EAST_FZ_IDLE;
										MotorZZ_Flag=0;
										MotorFZ_Flag=0;
										Key_Subclock_State1=WALK;
										return (1);
									} 
					 }	
			 
				 break;
					 
					 
				 case  RUN_REVERSE:
							if(v->second==30){
									if (u->second<30){	
                    Key_Subclock_State1=RUN_REVERSE;
										 EnterEastFzRun();
										return (0);
									}else if(u->second>53){
										Key_Subclock_State1=RUN_FORWARD;
										EnterEastNormalRun();
										return (0);						
									}else{
										EAST_ZZ_IDLE;
										EAST_FZ_IDLE;
										MotorZZ_Flag=0;
										MotorFZ_Flag=0;
										Key_Subclock_State1=WALK;
										return (1);
									}
			        }
				 break;
							
				 //case CALIB:
				 //case STOP:
					 
				 break;
				 
			 }
			 
		}else if(u->minute>v->minute){
				 Key_Subclock_State1=RUN_FORWARD;//��ʾĸ�ӷ��� ���� ���ӷ���,������ת
			   EnterEastNormalRun();
			  return (0);
		}else if(u->minute<v->minute){
		     Key_Subclock_State1=RUN_REVERSE;//��ʾĸ�ӷ��� С�� ���ӷ���,���ӷ�ת
			   EnterEastFzRun();
			  return (0);
		}
		 
	}else if((u->hour%12)>v->hour && (u->hour%12)-v->hour<=6 ){
				Key_Subclock_State1=RUN_FORWARD;/*��ʾĸ��Сʱ ���� ����Сʱ,������ת*/
		    EnterEastNormalRun();
		    return (0);
	}else if((u->hour%12)>v->hour && (u->hour%12)-v->hour>6){
	      Key_Subclock_State1=RUN_REVERSE;/*��ʾĸ��Сʱ ���� ����Сʱ,���ӷ�ת*/
		    EnterEastFzRun();
		    return (0);
	}else if((u->hour%12)<v->hour &&  6>v->hour-(u->hour%12)){
	      Key_Subclock_State1=RUN_REVERSE;/*��ʾĸ��Сʱ С�� ����Сʱ,���ӷ�ת*/
		    EnterEastFzRun();
		    return (0);
	}else if((u->hour%12)<v->hour && v->hour-(u->hour%12)>=6){
	       Key_Subclock_State1=RUN_FORWARD;/*��ʾĸ��Сʱ С�ڵ��� ����Сʱ,������ת*/
		     EnterEastNormalRun();
		    return (0);
	}
	
}



