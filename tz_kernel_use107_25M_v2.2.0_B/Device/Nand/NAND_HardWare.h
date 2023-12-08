/*
Nand Flash����������Beta V2.0
�û���������Ϊ���NAND��������ʹ�ù����д��ڻ��鵼������
������ȷ���������⣬�ó������Զ���ʾ��ӳ�仵�飬ʹ�ϲ�
Ӧ�ò��ÿɿ������ݡ�

��Ȩ����@ δ��ͬ�ⲻ���Թ�����������ṩ�����˻����ҵ���� 
xin.rm@163.com
*/
#ifndef __NAND_HARDWARE_H
#define __NAND_HARDWARE_H

#define NAND_HARDWARE_VERSION 0x0102


/*
NAND ��������
*/
#define NAND_PAGEEXSIZE			16
#define NAND_PAGESIZE				512
#define NAND_BLOCKNUM				4096
#define NAND_BLOCKPAGENUM		32


/*
	NAND_BLOCKNUM_USEFORAPP should less than 3 to NAND_BLOCKNUM
	to recommend that above ten percent  less than NAND_BLOCKNUM
*/

#define NAND_BLOCKNUM_USEFORAPP		4000

#if((NAND_BLOCKNUM-NAND_BLOCKNUM_USEFORAPP)<2)
	#error NAND_BLOCKNUM-NAND_BLOCKNUM_USEFORAPP must >=2
#endif

#if((NAND_BLOCKNUM-NAND_BLOCKNUM_USEFORAPP)<3)
	#error no space for remap bad block
#endif


//ʹ�ù���ͬ��Ӧ�����룬���ʾ�ñ�ʾ��Ч

#define NANDHWSTATUS_SUCCESS 			0
#define NANDHWSTATUS_BUSY 				0x20
#define NANDHWSTATUS_WP 					0x80

#define NANDHWINIT_OK							 0
#define NANDHWINIT_FAIL 					1

#define NANDHWWRITER_OK 					0
#define NANDHWWRITER_NODISK 			2
#define NANDHWWRITER_TimeOut 			3
#define NANDHWWRITER_FAIL 				1
#define NANDHWWRITER_WP 					0x80

#define NANDHWREAD_OK 						0
#define NANDHWREAD_FAIL 					1

#define NANDHWERASEBLOCK_OK 			0x0
#define NANDHWERASEBLOCK_FAIL 		0x01
#define NANDHWERASEBLOCK_TimeOut 	0x03
#define NANDHWERASEBLOCK_WriteProtect 		0x80

#define NANDGETINFOR_OK 									0x0
#define NANDGETINFOR_NODISK 							0x01

#define NANDHWGETSTATUSR_Ready 						0x0
#define NANDHWGETSTATUSR_Fail 						0x01
#define NANDHWGETSTATUSR_TimeOut 					0x03
#define NANDHWGETSTATUSR_WriteProtect 		0x05

#define NANDVERIFY_OK 										0x00
#define NANDVERIFY_FAIL 									0x01



#define DEVICE_STATUS_NOPROTECT						0x80
#define DEVICE_STATUS_READY								0x40
#define DEVICE_STATUS_OPERFAIL						0x01

typedef NANDFTL_ADDR  NANDADDR;
typedef unsigned char NANDHWINIT;
typedef unsigned char NANDGETINFOR;
typedef unsigned char NANDHWERASEBLOCK;
typedef unsigned char NANDHWREAD;
typedef unsigned char NANDHWWRITER;
typedef unsigned char NANDHWGETSTATUSR;


extern NANDHWINIT NANDHW_Init(NANDSTRUCT* NandStruct);
extern NANDGETINFOR NANDHW_GetInfo(NANDSTRUCT* NandStruct);
extern NANDHWERASEBLOCK NANDHW_EraseBlock(NANDADDR addr);
extern NANDHWREAD NANDHW_ReadMainPage(U8* buff,NANDADDR addr);
extern NANDHWWRITER NANDHW_WriteMainPage(U8* buff,NANDADDR addr);


#endif
