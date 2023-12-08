#ifndef _config_h
#define _config_h  

typedef struct 
{ 	
	u8 type;
	u8 id;	 	
	u8 err;		   // [0]pps, [1]gps
			
	u8 protocol;
	u8 hw;
   	u8 sw; 		
	u8 is_tm; 		// is tm src	
	u8 is_bd;  		// is tm src board 	
	u8 key;	 		 	
	u8 use_prio;
	
	u8 level;
	u8 box;

	u8 gps;
	u8 pps;
	u8 xtal;
	u8 adapt;
	u8 u5;	 
	u8 src_format;		
	u8 set_prio; 		
	u8 max_colck;
	u8 offset[2];

	u8 stratum; 
	s8 refeid[4];
	u8 refetimestamp[4]; 
u8 sjwtest;	
}config;

#define GPS_TYPE 0xC2  

#define is_tm() 	 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define u5_dir(x) ((x)?(GPIOD->BSRR=GPIO_Pin_1):(GPIOD->BRR=GPIO_Pin_1))

#define err_pps		(0x01)
#define err_bus		(0x02)
#define err_gps1	(0x04) 
#define err_gps2	(0x08) 
#define err_link	(0x10) 	

void configuration(void); 
void id_init(void);
u8 get_bd_id(void);
void host_init(void);
void Heartbeat_Init(void);
void is_tm_init(void); 
							
#endif
