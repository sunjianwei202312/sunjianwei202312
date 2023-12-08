#include <string.h>
#include "stm32f10x.h"
#include "gps.h"
#include "check.h"
#include "time.h" 
#include "queue.h" 

//#include "tmcode.h" 
//#include "config.h" 
//#include "uart.h" 

#define QuSize 10//25//30 否则永远到达不了linear = 1;




#define YEAR 2000 
#define status_flag(flag) ((flag=='A') ? 1 : 0)
#define ascii2hex(ascii)  ((ascii)>='A' ? (ascii)-55 : (ascii)-'0')
#define hex2ascii(hex)    ((hex)>=10 ? (hex)+55 :(hex)+'0')

config 		board;
head 			header;



void    write_gps_status1(INT8U sta);

INT8U    last_status;
INT8U    GpsBdSaveFlag;
INT8U    GpsBdRunFlag;
INT16U     GpsBdRunRseg;


gps_info gps = {0};

//gps_info bd2_b1, gps_l1;
/*
exp:
40 40 48 62 0C 0E 
07 DC 07 2A 34 00 05 DA 3B 08 93 85 9B 18 EF 87 72 00 00 16 87 00 00 00 00 00 26 00 06 07 94 00 2F 08 05 E0 01 00 00 4A 59 39 38 34 38 76 0D 0A 
*/
//@@Hb 换页+不用切换
//响铃+



INT8U m12m_bin(INT8U *buf, INT16U len)
{  
	INT8U data[54] = {0};
	INT8U bcc1, bcc2;
	
	
	
	if(len != 54)
		return(0);
			
	memcpy(data, buf, 54);
	//memmove(data, buf, 54);

   	if((data[0]!='@') || (data[1]!='@') || (data[2]!='H') || (data[3]!='b') || (data[len-2]!='\r') ||(data[len-1]!='\n'))
		return(0);		

	bcc1 = checkbcc(data, 51);
	bcc2 = data[51];

	if(bcc1 != bcc2)
		return(0);		
			
	gps.year 	= data[6]<<8 | data[7]; 
	gps.mon 	= data[4]; 
	gps.day 	= data[5]; 
	gps.hour 	= data[8]; 
	gps.min 	= data[9]; 
	gps.sec 	= data[10]; 
	gps.hsec	= data[11]<<24 | data[12]<<16 | data[13]<<8 | data[14]; 
	gps.track	= data[40];			
					
	if(!gps.track)
	{
		gps.status = 0;
		return(0);
	}
	else
		gps.status = 1;
			
return(1);	
}




INT32U do_gps(void)
{ 	
	extern gps_info gps;  	 	
	struct tm now;

	now.tm_year	= gps.year;
	now.tm_mon 	= gps.mon;
	now.tm_mday	= gps.day;
	now.tm_hour	= gps.hour;
	now.tm_min	= gps.min;
	now.tm_sec	= gps.sec; 	

	return(mktimev(&now) + JAN_1970+28800);//我这里做了一个小技巧：将此GPS的时间往时钟芯片压入的时候，+8小时是北京时间，这样初始上电直接读取即可，不必转换！！added  by sjw
}

static INT8U ascii_check(INT8U *buf)
{
    INT8U len = 0;
    INT8U bcc1, bcc2;

    if(strchr(buf, '*'))
			//函数说明：strchr 查找字符串buf中首次出现 * 的位置。
		//返回首次出现 * 的位置的指针，返回的地址是被查找字符串开始的第一个与 * 相同字符的指针，如果字符串内无 * 返回NULL
		
		
		//函数说明：strcspn()从参数s 字符串的开头计算连续的字符，而这些字符都完全不在参数reject 所指的字符串中。
		//简单地说， 若strcspn()返回的数值为n，则代表字符串s 开头连续有n 个字符都不含字符串reject 内的字符。
		//返回值：返回字符串s 开头连续不含字符串reject 内的字符数目。
        len = strcspn(buf, "*");
	else
		return(0);	

    bcc1 = (ascii2hex(buf[len+1])<<4) | (ascii2hex(buf[len+2]));

	  bcc2 = checkbcc(&buf[1], len-1);

    if(bcc1 != bcc2)
        return(0);

    return(1);
}

static INT8U rmc(INT8U *rmc)
{
  INT8U i, comma = 0;
  if(ascii_check(rmc))
	{
    for(i=0; rmc[i]!='*'; i++)
		{
			if(rmc[i]==',')
			{
				comma++;
                if(comma==1)
                {
                    gps.hour= ascii2hex(rmc[i+1])*10 + ascii2hex(rmc[i+2]);
                    gps.min = ascii2hex(rmc[i+3])*10 + ascii2hex(rmc[i+4]);
                    gps.sec = ascii2hex(rmc[i+5])*10 + ascii2hex(rmc[i+6]);
                    gps.hsec= ascii2hex(rmc[i+8])*100+ ascii2hex(rmc[i+9])*10 + ascii2hex(rmc[i+10]);
                }
                else if(comma==2)
                    gps.status = status_flag((rmc[i+1]));
								
								
								
                else if(comma==9)
                {
                    gps.day = ascii2hex(rmc[i+1])*10 + ascii2hex(rmc[i+2]);
                    gps.mon = ascii2hex(rmc[i+3])*10 + ascii2hex(rmc[i+4]);
                    gps.year= ascii2hex(rmc[i+5])*10 + ascii2hex(rmc[i+6]) + YEAR;
                }
			}
		}
		return(1);
	}
    else
        return(0);

}

static INT8U gga(INT8U *gga)
{
    INT8U i, comma = 0;

  if(ascii_check(gga))
	{
    for(i=0; gga[i]!='*'; i++)
		{
			if(gga[i]==',')
			{
				comma++;

                if(comma==1)
                {
                    gps.hour= ascii2hex(gga[i+1])*10 + ascii2hex(gga[i+2]);
                    gps.min = ascii2hex(gga[i+3])*10 + ascii2hex(gga[i+4]);
                    gps.sec = ascii2hex(gga[i+5])*10 + ascii2hex(gga[i+6]);
                    gps.hsec= ascii2hex(gga[i+8])*100+ ascii2hex(gga[i+9])*10 + ascii2hex(gga[i+10]);
                }
                else
                if(comma==7){										
                    gps.track = ascii2hex(gga[i+1])*10 + ascii2hex(gga[i+2]);
								}
								
       }
		}
		return(1);
	}
    else
        return(0);
}

/* GPS + BD2 */
INT8U gps_bd2_ascii(INT8U *buf, INT16U len)
{  	
	
	char *p = NULL;

	if(len==0)
		return(0);
	

	if(p = strstr(buf, "$GBGGA")){  		
		if(gga(p)==1){	 			 
			board.use_prio = BD2_USE; 
      //bd2_b1.track  = gps.track;		
		}else  return(0);
	}else if(p = strstr(buf, "$GPGGA")){  		
		if(gga(p)==1){ 
			board.use_prio = GPS_USE; 
      //gps_l1.track  = gps.track;
		}else return(0);
	}else if(p = strstr(buf, "$GNGGA")){  		
		if(gga(p)==1){	 			 
			board.use_prio = BD2_GPS_USE; 
      //bd2_b1.track  = gps.track;
		}else
			return(0);
	}

	if(p = strstr(buf, "$GBRMC")){  		
		if(rmc(p)==1){  		
			board.use_prio = BD2_USE;  
      //bd2_b1.status = gps.status;
		}else
			return(0);
	}else	if(p = strstr(buf, "$GPRMC")){			
		if(rmc(p)==1){ 		
			board.use_prio = GPS_USE; 
      //gps_l1.status = gps.status;
		}else
			return(0);
	}else	if(p = strstr(buf, "$GNRMC")){			
		if(rmc(p)==1){ 		
			board.use_prio = BD2_GPS_USE; 
      //gps_l1.status = gps.status;
		}else
			return(0);
	}	
		

	if(gps.status==0){
		gps.track=0;//设置为固定0颗星，给辽化北斗。
		return(0);
	}

	return(1);	
}




//INT8U *gpsl1 = "$CFGSYS,h1\r\n";	
//INT8U *bd2b1 = "$CFGSYS,h10\r\n";这是原来模块对应的！




//model output only TWO sentence!! added by sjw in2021-11-12 11:00															 
//模块没有进行初始化之前，用x07来控制使其只输出两条语句：BD和GPS的RMC	,GGA														 
 INT8U gps1_sjw_set_double[28]={0x24, 0x50, 0x43, 0x41, 0x53, 0x30, 0x33, 0x2C, 0x31, 0x2C,
		                          0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x31, 0x2C, 0x30, 0x2C,
                           		0x30, 0x2C, 0x30, 0x2A, 0x30, 0x32, 0x0D, 0x0A };//此语句验证了GPS和BD都正确 added by sjw 		

//--only bd 14b
INT8U gps1_set_only_bd[14]  = {0x24,0x50,0x43,0x41,0x53,0x30,0x34,0x2C,0x32,0x2A,0x31,0x42,0x0D,0x0A};	//此语句验证了BD正确 												
						
//only  gps  14b
INT8U gps1_set_only_gps[14]={0x24, 0x50, 0x43, 0x41, 0x53, 0x30, 0x34, 0x2C, 0x31, 0x2A, 0x31, 0x38, 0x0D, 0x0A};
													 													 													 
INT8U gps_set_save[14]={0x24,0x50,0x43,0x41,0x53,0x30,0x34,0x2C,0x31,0x2A, 0x31,0x38,0x0D,0x0A};//使这GPS模块保存设置指令串！
INT8U bd_set_save[14]= {0x24,0x50,0x43,0x41,0x53,0x30,0x34,0x2C,0x32,0x2A, 0x31,0x42,0x0D,0x0A};//使这BD模块保存设置指令串！
INT8U gps_or_bd_set_save[14]= {0x24,0x50,0x43,0x41,0x53,0x30,0x34,0x2C,0x33,0x2A, 0x31,0x41,0x0D,0x0A};//使这BD模块保存设置指令串！
INT8U pps_set[28]={0xBA, 0xCE, 0x10, 0x00, 0x06, 0x03, 0x40, 0x42, 0x0F, 0x00, 0x40, 0x0D, 0x03, 0x00, 0x01, 
                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x4F, 0x18, 0x03,0x0D,0x0A};


	
	
  INT8U *bd2b1 =gps1_set_only_bd;
  INT8U *gpsl1 =gps1_set_only_gps;
  INT8U *gpsl2 =gps1_sjw_set_double;
  INT8U *pgps_save=gps_set_save;
  INT8U *pbd_save=bd_set_save;
  INT8U *pgps_or_bd_save=gps_or_bd_set_save;											
												
												

static INT16U sw_s = 0; 
static INT8U flag = 0; 	

void set_gps_prio(void)
{
	

	//below is added by sjw in order to time source priority
	//if(sw_s++ > 600)				
	{
		//if(board.set_prio ^ board.use_prio)
			
			if(board.use_prio==1){	
					switch(board.set_prio){
						case 1:					
						  write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
							board.set_prio=BD2_USE;
							board.use_prio=BD2_USE;
						break;
										
						case 2:
							write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						
						case 3:
							write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
							board.set_prio=BD2_USE;
							board.use_prio=BD2_USE;
						break;
						
						case 4:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						
						case 5:
							write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_GPS_USE;
						  board.use_prio=BD2_GPS_USE;
						break;
						
					}
			}else if(board.use_prio==2){ 						
				switch(board.set_prio){
					case 1:
						write_gps_status1(1); 
						uart4_tx(bd2b1, 14);
						uart1_tx(bd2b1, 14);
						GpsBdSaveFlag=1;
					  board.set_prio=BD2_USE;
						board.use_prio=BD2_USE;			
					break;
					
					case 2:
					  write_gps_status1(0); 
						uart4_tx(gpsl1, 14);
						uart1_tx(gpsl1, 14);
						GpsBdSaveFlag=1;
						board.set_prio=GPS_USE;
						board.use_prio=GPS_USE;
					break;
					
						case 3:
							write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
							board.set_prio=BD2_USE;
							board.use_prio=BD2_USE;
						break;
						
						case 4:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						
						case 5:
							write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_GPS_USE;
						  board.use_prio=BD2_GPS_USE;
						break;
				}				
			}else if(board.use_prio==3){
				  switch(board.set_prio){
						case 1:
							write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_USE;
						  board.use_prio=BD2_USE;
						break;
						case 2:
							write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						case 3:
						  write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
							board.set_prio=BD2_USE;
							board.use_prio=BD2_USE;
						break;
						
						case 4:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						
						case 5:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_GPS_USE;
						  board.use_prio=BD2_GPS_USE;
						break;
						
						
					}
			}else if(board.use_prio==4){
				 switch(board.set_prio){
						case 1:
							write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_USE;
						  board.use_prio=BD2_USE;
						break;
						case 2:
							write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						case 3:
							write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_USE;
						  board.use_prio=BD2_USE;
						break;
						
						case 4:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						
						case 5:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_GPS_USE;
						  board.use_prio=BD2_GPS_USE;
						break;
					}
						
				
			}else if(board.use_prio==5){
				 switch(board.set_prio){
						case 1:
							write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_USE;
						  board.use_prio=BD2_USE;
						break;
						case 2:
							write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						case 3:
							write_gps_status1(1); 
							uart4_tx(bd2b1, 14);
							uart1_tx(bd2b1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_USE;
						  board.use_prio=BD2_USE;
						break;
						
						case 4:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
						  GpsBdSaveFlag=1;
						  board.set_prio=GPS_USE;
						  board.use_prio=GPS_USE;
						break;
						
						case 5:
						  write_gps_status1(0); 
							uart4_tx(gpsl1, 14);
							uart1_tx(gpsl1, 14);
							GpsBdSaveFlag=1;
						  board.set_prio=BD2_GPS_USE;
						  board.use_prio=BD2_GPS_USE;
						break;
					}								
			}
		sw_s = 0;
	}
	
}








INT8U gps1_f1_info[8] = {0x40, 0x40, 0x48, 0x62, 0x01, 0x2B, 0x0D, 0x0A};		

void gps1_f1_tx(void)
{	
	uart1_tx(gps1_f1_info, 8);
}

void gps2_f1_tx(void)
{
		uart4_tx(gps1_f1_info, 8);
}


void write_gps_status1(u8 status)   
{	
	if(last_status ^ status)
	{
		//if(status)
			//fsmc_wr_bit1(1, 1, nCFG2); 	
		//else
			//fsmc_wr_bit1(1, 0, nCFG2); 

		last_status = status;
	}
} 



INT8U isLinear(INT32U data)
{ 	
	INT8U linear = 0;
	INT8U len;	 
	ElemType n;
	extern LinkQueue Qu;
	INT8U err;
	OS_CPU_SR  cpu_sr;
	
	
	
	//CPU_SR_ALLOC();
	// OS_ENTER_CRITICAL();
				
	EnQueue(&Qu, data);

	len = QueueLength(Qu);

	
	
	if(len == QuSize+1)
	{
		DeQueue(&Qu, &n);
		if(LineQueue(&Qu, QuSize))
			linear = 1;
	} 

   //OS_EXIT_CRITICAL();	
					  
return(linear);	 		
}

