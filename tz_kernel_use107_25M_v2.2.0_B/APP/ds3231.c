#include <stm32f10x.h>
#include "iic_sw.h"
#include "ds3231.h"
#include "time.h"
#include "bsp.h"


extern		mytime 		*p_timemu;


INT8U Hour,Min,Sec;
//#define JAN_1970 0x83AA7E80	
   
//#define	leapyear(year)	( (year)%4==0&&((year)%100!=0||(year)%400==0) )	 	 

	
u32 ds3231_tm_rd(void) 
{
	uint8_t rx[8];	
	struct tm now;

	iic_sw_read(I2C_SALVEID_DS3231, DS3231_REG_SECOND, rx, 7);	 

	now.tm_sec 	= bcd2dec(rx[0]);		  
	now.tm_min	= bcd2dec(rx[1]);		  
	now.tm_hour	= bcd2dec(rx[2]);
	now.tm_wday	= bcd2dec(rx[3]);
	now.tm_mday	= bcd2dec(rx[4]);
	now.tm_mon	= bcd2dec(rx[5]);
	now.tm_year	= bcd2dec(rx[6]) + 2000;   	

	
	
return(mktimev(&now) + JAN_1970);
}

void ds3231_tm_wr(u32 _ntp) 
{  
	uint8_t tx[8], init = 0x40;	 

	struct tm now;

	to_tm(_ntp - JAN_1970, &now); 

	tx[0] = dec2bcd(now.tm_sec);		  
	tx[1] = dec2bcd(now.tm_min);		  
	tx[2] = dec2bcd(now.tm_hour);
	tx[3] = dec2bcd(now.tm_wday);
	tx[4] = dec2bcd(now.tm_mday);
	tx[5] = dec2bcd(now.tm_mon);
	tx[6] = dec2bcd(now.tm_year%100);	 	
	
	iic_sw_write(I2C_SALVEID_DS3231, DS3231_REG_CONTROL, &init, 1); 
		 
	iic_sw_write(I2C_SALVEID_DS3231, DS3231_REG_SECOND, tx, 7);									 		
} 

void ds3231_temp_rd(char *temp) 
{ 
	u8 buf[2] = {0};	    		
	u16 t;
	iic_sw_read(I2C_SALVEID_DS3231, DS3231_REG_TEMP_HI, buf, 2);  
	
    t = buf[0]<<8 | buf[1];  
    t = t >> 6;  
    
    temp[0] = t>>2;

	switch(t%4)
	{
		case 0:
		 	temp[1]	= 0;
			break;
		case 1:
		 	temp[1]	= 25;
			break;
		case 2:
		 	temp[1]	= 50;
			break;
		case 3:
		 	temp[1]	= 75;
			break;
	} 

} 


void get_time(void)
{
	INT32U     _ntp = 0; 
  OS_CPU_SR  cpu_sr;
	struct tm  now;
	
  OS_ENTER_CRITICAL();
	_ntp=ds3231_tm_rd();
	to_tm(_ntp - JAN_1970, &now); 
	p_timemu->hour=now.tm_hour;
	p_timemu->minute=now.tm_min;
	p_timemu->second=now.tm_sec;
	p_timemu->day=now.tm_mday;
	p_timemu->month=now.tm_mon;
	p_timemu->year=now.tm_year-2000;
	OS_EXIT_CRITICAL();	
	
}


