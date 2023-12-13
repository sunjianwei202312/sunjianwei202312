#ifndef _gps_h
#define _gps_h

#include "includes.h"


#define err_pps		(0x01)
#define err_bus		(0x02)
#define err_gps1	(0x04) 
#define err_gps2	(0x08) 
#define err_link	(0x10) 	


typedef struct 
{
	u8 msg1;
	u8 msg2; 	
	u8 msg3;
	u8 msg4; 
	u8 msg5; // src
	u8 msg6; //
	u8 msg7; // struct	 
}head;


typedef struct _gps_info_
{  
    INT16U 	year;      
    INT8U  	mon;        
    INT8U	 	day;           
	  INT8U  	hour;      
    INT8U  	min;        
    INT8U  	sec;        
    INT32U	hsec;       
		INT8U 	track;
		INT8U 	status;
}gps_info;




typedef struct 
{ 
	INT8U  	type;
	INT8U  	id;	 	
	INT8U  	err;		   // [0]pps, [1]gps
			
	INT8U 	protocol;
	INT8U 	hw;
	
  INT8U 	sw; 		
	INT8U 	is_tm; 		// is tm src	
	INT8U 	is_bd;  	// is tm src board 	
	INT8U 	key;	 		 	
	INT8U 	use_prio;
	
	
	INT8U 	level;
	INT8U 	box;

	INT8U 	gps;
	INT8U 	pps;
	INT8U 	xtal;
	INT8U 	adapt;
	INT8U 	u5;	 
	INT8U 	src_format;		
	INT8U 	set_prio; 		
	INT8U 	max_colck[32];
	INT8U   hms_ms[16];
	INT8U 	offset[2];
	
	
	INT8U  	ntp_auth_key[3][9];
	INT8U  (*pntp_auth_key)[9];
	

	INT8U 	stratum; 
	INT8U 	refeid[4];
	INT8U 	refetimestamp[4]; 	
	
	
	INT8U 	start_ip[4]; 
	INT8U 	end_ip[4];
	INT8U 	start_mask[4]; 
	INT8U 	start_net[4];
	
	
	INT8U   east_time[8];
	INT8U   south_time[8];
	INT8U   west_time[8];
	INT8U   north_time[8];
	
	
}config;





INT32U	  do_gps(void); 
INT8U 		m12m_bin(INT8U*, u16);
INT8U     gps_bd2_ascii(INT8U*, u16);	
void      set_gps_prio(void);   

#define BD2_USE 1
#define GPS_USE	2
#define BD2_GPS_USE 3

#endif
