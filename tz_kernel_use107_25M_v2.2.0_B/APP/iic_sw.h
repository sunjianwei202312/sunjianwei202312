#ifndef _iic_sw_h 
#define _iic_sw_h 
#include  "os_cpu.h"

#define eep_chip_ds3231	  0xD0	// 3231的器件地址 ---chip addr 
#define eep_chip_24cxx	  0xAE	// 24Cxx的器件地址 ---chip addr
	
/* 0x00-0x80 */
// #define iic_init	0x00	// 0xA5	
// #define iic_tst		0x01
// #define iic_gps		0x02
// #define iic_pps		0x03
// #define iic_xtal	0x04
// #define iic_adapt	0x05
// #define iic_u5		0x06
// #define iic_format	0x07
// #define iic_prio	0x08

#define iic_max1		0x0
#define iic_max2		0x1
#define iic_max3		0x2
#define iic_max4		0x3
#define iic_max5		0x4
#define iic_max6		0x5
#define iic_max7		0x6
#define iic_max8		0x7
#define iic_max9		0x8
#define iic_max10		0x9
#define iic_max255		0xFF


//AT24C02的容量足够，不必用位代替，用整个字节即可！！added by sjw
#define iic_eeprom_east							0x00
#define iic_eeprom_east_sta					0x07

/*
1u     小时
2u     分钟
3u     秒数
4u     校验
5u     状态  处于什么状态
6u
7u     
8u 
*/
#define iic_eeprom_south						0x08
#define iic_eeprom_west 						0x10
#define iic_eeprom_north						0x18
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************

#define iic_eeprom_bspower0_7				0x20
#define iic_eeprom_bspower8_15			0x28
#define iic_eeprom_bspower16_23			0x30

#define iic_eeprom_bsrythem   		  0x38
#define iic_eeprom_bsknock   		    0x39


//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************
//************************************************

#define iic_eeprom_zmpower_on   		0x68
#define iic_eeprom_zmpower_off		  0x69


#define iic_eeprom_15page           0x78
//************************************************


#define iic_eeprom_16page		0x80
#define iic_eeprom_17page		0x88
#define iic_eeprom_18page		0x90
#define iic_eeprom_19page		0x98
#define iic_eeprom_20page		0xa0
#define iic_eeprom_21page		0xa8
#define iic_eeprom_22page		0xb0
#define iic_eeprom_23page		0xb8

#define iic_eeprom_24page		0xc0
#define iic_eeprom_25page		0xc8
#define iic_eeprom_26page		0xd0
#define iic_eeprom_27page		0xd8
#define iic_eeprom_28page		0xe0
#define iic_eeprom_29page		0xe8
#define iic_eeprom_30page		0xf0
#define iic_eeprom_31page		0xf8


/*
#define	DEFAULT_SLAVE_EASTHOUR				iic_eeprom_east
#define	DEFAULT_SLAVE_EASTMIN			    iic_eeprom_east+1
#define	DEFAULT_SLAVE_EASTSEC			    iic_eeprom_east+2
#define	DEFAULT_SLAVE_EASTSTA			    iic_eeprom_east+3
#define	DEFAULT_SLAVE_EASTJY			    iic_eeprom_east+4

#define	DEFAULT_SLAVE_SOUTHHOUR				iic_eeprom_south+0
#define	DEFAULT_SLAVE_SOUTHMIN				iic_eeprom_south+1
#define	DEFAULT_SLAVE_SOUTHSEC				iic_eeprom_south+2
#define	DEFAULT_SLAVE_SOUTHSTA				iic_eeprom_south+3
#define	DEFAULT_SLAVE_SOUTHJY				  iic_eeprom_south+4

*/


#define	DEFAULT_EASTHOUR_VALUE				0
#define	DEFAULT_EASTMIN_VALUE		      0
#define	DEFAULT_EASTSEC_VALUE			    0
#define	DEFAULT_EASTJY_VALUE			    0
#define	DEFAULT_EASTSTA_VALUE		      0

#define	DEFAULT_ZMSTA00_VALUE         0
#define	DEFAULT_ZMSTA01_VALUE         0
#define	DEFAULT_ZMSTA02_VALUE         0
#define	DEFAULT_ZMSTA03_VALUE         0
#define	DEFAULT_ZMSTA04_VALUE         0
#define	DEFAULT_ZMSTA05_VALUE         0
#define	DEFAULT_ZMSTA06_VALUE         0
#define	DEFAULT_ZMSTA07_VALUE         1
#define	DEFAULT_ZMSTA08_VALUE         1
#define	DEFAULT_ZMSTA09_VALUE         1
#define	DEFAULT_ZMSTA10_VALUE         1
#define	DEFAULT_ZMSTA11_VALUE         1


#define	DEFAULT_ZMSTA12_VALUE         1
#define	DEFAULT_ZMSTA13_VALUE         0
#define	DEFAULT_ZMSTA14_VALUE         0
#define	DEFAULT_ZMSTA15_VALUE         1
#define	DEFAULT_ZMSTA16_VALUE         1
#define	DEFAULT_ZMSTA17_VALUE         1
#define	DEFAULT_ZMSTA18_VALUE         1
#define	DEFAULT_ZMSTA19_VALUE         1
#define	DEFAULT_ZMSTA20_VALUE         1
#define	DEFAULT_ZMSTA21_VALUE         0
#define	DEFAULT_ZMSTA22_VALUE         0
#define	DEFAULT_ZMSTA23_VALUE         0

INT8U HEX_to_BCD(INT8U data);

INT8U BCD_to_HEX(INT8U data);
 void iic_wr_byte(INT8U byte) ;

INT8U iic_sw_read (INT8U, INT8U, INT8U*, INT8U);
INT8U iic_sw_write(INT8U, INT8U, INT8U*, INT8U);
void iic_sw_init(void); 
void get_iic_setting(void);

#endif
