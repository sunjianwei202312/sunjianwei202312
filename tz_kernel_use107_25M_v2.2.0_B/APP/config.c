#include <stm32f10x.h>
#include "config.h"
#include "tmcode.h"
#include "gps.h"



config board;
head header;

void id_init(void) 
{ 
    GPIO_InitTypeDef GPIO_InitStructure;   

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE); 

    GPIO_InitStructure.GPIO_Mode  	= GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz; 

		GPIO_InitStructure.GPIO_Pin   	= GPIO_Pin_11|GPIO_Pin_10;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin   	= GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
}

u8 get_bd_id(void) 
{
	uint8_t id0,id1,id2;
	id0 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	id1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
	id2 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15);

return(id2<<2 | id1 <<1 | id0);	
}

void is_tm_init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);								  
}

void Heartbeat_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_4;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void u5_dir_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_1;
  GPIO_Init(GPIOD, &GPIO_InitStructure);	
}

u8 is_tm_bd(u8 id) 
{
	u8 is_bd;

	if(id == 3)
		is_bd = 1;
	else	if(id == 4)
		is_bd = 1;
	else
		is_bd = 0;

return(is_bd);	
}



void configuration(void) 
{   
 	board.type	= GPS_TYPE;
	board.protocol = 10;   
	board.sw	= 10; 
	board.hw	= 14;	

	board.id	= get_bd_id(); 				 //得到板卡的ID号码！	
	board.is_bd = is_tm_bd(board.id);//是否是时源卡,在4/5号卡槽内。

	board.set_prio 	= GPS_USE;
	board.use_prio = GPS_USE;
	
	board.src_format= 1;

	board.max_colck = 10;

	board.gps	= 1;
	board.pps	= 0x03;
	board.xtal	= 0;
	board.adapt	= 0;
	board.u5	= 0;
	
	header.msg1 = 0;   
	header.msg2	= 0;	
	header.msg3 = 8;
	header.msg4 = 0; 
	
	board.offset[0] = 0;
	board.offset[1] = 0;			
}
