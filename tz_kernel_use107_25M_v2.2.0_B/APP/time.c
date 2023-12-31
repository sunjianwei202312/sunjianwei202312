#include <time.h>
#include "time.h" 
				   
const char *WeekDay[7]  = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const char *Month[12]   = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
							"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };	 

#define FEBRUARY			2
#define	STARTOFTIME			1970
#define SECDAY				(60*60*24UL)
#define SECYR				(SECDAY * 365) 
#define	days_in_year(x) 	(leapyear(x) ? 366 : 365)
#define	days_in_month(x) 	(month_days[(x) - 1])
static int month_days[12] = 
{
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static void GregorianDay(struct tm *tm) 
{
	int leapsToDate;
	int lastYear;
	int day;
	int MonthOffset[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	lastYear = tm->tm_year - 1;

	/*
	 * Number of leap corrections to apply up to end of last year
	 */
	leapsToDate = lastYear / 4 - lastYear / 100 + lastYear / 400;

	/*
	 * This year is a leap year if it is divisible by 4 except when it is
	 * divisible by 100 unless it is divisible by 400
	 *
	 * e.g. 1904 was a leap year, 1900 was not, 1996 is, and 2000 was
	 */
	day = tm->tm_mon > 2 && leapyear(tm->tm_year);

	day += lastYear*365 + leapsToDate + MonthOffset[tm->tm_mon-1] +
		   tm->tm_mday;

	tm->tm_wday = day % 7; 

	tm->tm_yday = MonthOffset[tm->tm_mon-1] + tm->tm_mday;
}

extern void to_tm(unsigned int tim, struct tm *tm) 
{
	register int    i;
	register long   hms, day;
	
	day = tim / SECDAY;
	hms = tim % SECDAY;

	/* Hours, minutes, seconds are easy */
	tm->tm_hour = hms / 3600;
	tm->tm_min = (hms % 3600) / 60;
	tm->tm_sec = (hms % 3600) % 60;

	/* Number of years in days */
	for (i = STARTOFTIME; day >= days_in_year(i); i++)
		day -= days_in_year(i);
	tm->tm_year = i;

	/* Number of months in days left */
	if (leapyear(tm->tm_year))
		days_in_month(FEBRUARY) = 29;
	for (i = 1; day >= days_in_month(i); i++)
		day -= days_in_month(i);
	days_in_month(FEBRUARY) = 28;
	tm->tm_mon = i;

	/* Days are what is left over (+1) from all that. */
	tm->tm_mday = day + 1;
	 
	GregorianDay(tm);
}

/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia before 1917,
 * Britain & colonies before 1752, anywhere else before 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * WARNING: this function will overflow on 2106-02-07 06:28:16 on
 * machines were long is 32-bit! (However, as time_t is signed, we
 * will already get problems at other places on 2038-01-19 03:14:08)
t */
unsigned int mktimev(struct tm *tm)
{
 	if (0 >= (int) (tm->tm_mon -= 2))  	/* 1..12 -> 11,12,1..10 */
  	{
		tm->tm_mon += 12;  				/* Puts Feb last since it has leap day */
  		tm->tm_year -= 1;
 	}

	return (((
	(unsigned int) (tm->tm_year/4 - tm->tm_year/100 + tm->tm_year/400 + 367*tm->tm_mon/12 + tm->tm_mday) +
	tm->tm_year*365 - 719499
 	)*24 + tm->tm_hour 		/* now have hours */
	)*60 + tm->tm_min 		/* now have minutes */
	)*60 + tm->tm_sec; 		/* finally seconds */
}


extern void make_yday_mday(struct tm *tm)
{ 	
  int n = tm->tm_yday;	
	int month = 0; 
	
	if (leapyear(tm->tm_year))
		days_in_month(FEBRUARY) = 29;	
	
	while(n > month_days[month])
  {
     n -= month_days[month];
     month++;
  }
		
	tm->tm_mday = n;
	tm->tm_mon 	= month;	
}
