#ifndef _time_h
#define _time_h

#include <time.h>	
 
#define JAN_1970 0x83AA7E80	
   
#define	leapyear(year)	( (year)%4==0&&((year)%100!=0||(year)%400==0) )	 	 

extern void to_tm(unsigned int tim, struct tm*);
extern unsigned int mktimev(struct tm*);

#endif
