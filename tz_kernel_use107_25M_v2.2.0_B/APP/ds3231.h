#ifndef _ds3231_h
#define _ds3231_h

#include <time.h> 

#define  I2C_SALVEID_DS3231 	0xD0  
 
/* Device registers */  
#define DS3231_REG_SECOND      	0x00  
#define DS3231_REG_MINUTE      	0x01  
#define DS3231_REG_HOUR        	0x02    /*x [12/24] 2 1 | 8 4 2 1 */  
#define DS3231_REG_DAY         	0x03  
#define DS3231_REG_DATE        	0x04  
#define DS3231_REG_MONTH       	0x05  
#define ds3231_REG_YEAR        	0x06     /* 8  4 2 1 | 8 4 2 1 */  
#define ds3231_REG_AL1_SECOND  	0x07    /* A1M1 4 2 1 | 8 4 2 1 */  
#define ds3231_REG_AL1_MIN     	0x08    /* A1M2 4 2 1 | 8 4 2 1 */  
#define ds3231_REG_AL1_HR      	0x09    /* A1M3 [12/24] 2 1 | 8 4 2 1 */  
#define ds3231_REG_AL1_DAY     	0x0a    /* A1M4 [DY/DT] 2 1 | 8 4 2 1 */  
#define ds3231_REG_AL2_MIN     	0x0b    /* A2M2 4 2 1 | 8 4 2 1 */  
#define ds3231_REG_AL2_HR      	0x0c    /* A2M3 [12/24] 2 1 | 8 4 2 1 */  
#define ds3231_REG_AL2_DAY     	0x0d    /* A2M4 [DY/DT] 2 1 | 8 4 2 1 */  
#define DS3231_REG_CONTROL     	0x0e    /*ESOC x x RS2 RS1 INTCN A2IE A1IE*/  
#define DS3231_REG_STATUS      	0x0f    /*OSF X X X X X A1F A2F*/  

#define DS3231_REG_TEMP_HI     	0x11  
#define DS3231_REG_TEMP_LO 		  0x12  

/* Control reg */  
#define ds3231_CTRL_A1IE       	(1<<0)  
#define ds3231_CTRL_A2IE       	(1<<1)  
#define ds3231_CTRL_INTCN      	(1<<2)  
#define ds3231_CTRL_RS         	(1<<3)  
#define ds3231_CTRL_EOSC       	(1<<7)  

/* Status reg */  
#define ds3231_STATUS_A1F      	(1<<0)  
#define ds3231_STATUS_A2F      	(1<<1)  
#define ds3231_STATUS_OSF      	(1<<7)  

/* CLKOUT frequencies , RS*/  
#define ds3231_FD_32768HZ      	(0x03)  
#define ds3231_FD_1024HZ       	(0x02)  
#define ds3231_FD_32           	(0x01)  
#define ds3231_FD_1HZ          	(0x00)  	

unsigned int ds3231_tm_rd(void);
void ds3231_tm_wr(unsigned int);
void ds3231_temp_rd(char*); 
extern void get_time(void);


#define bcd2dec(bcd) ((bcd>>4)*10 + (bcd&0x0F))	
#define dec2bcd(dec) ((dec/10)<<4 | (dec%10))	

#endif
