/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

/*
��stm32��ֲfatfs�ļ�ϵͳ����������ȡ�ý׶���ʤ����ֻ��Ҫ�ṩ���������������� 
DSTATUS disk_initialize (BYTE); 
DSTATUS disk_status (BYTE); 
DRESULT disk_read (BYTE, BYTE*, DWORD, BYTE); 
DRESULT disk_write (BYTE, const BYTE*, DWORD, BYTE); // ���ʵ��ֻ�����ļ�ϵͳ�Ͳ���Ҫ�ˡ� 
DRESULT disk_ioctl (BYTE, BYTE, void*); 
��ֲ�ɹ��󣬿��������·�ʽ��ȡSD���ˣ�ʵ��̫�����ˣ���PC���ϱ�̲�˶��١� 
*/

#include "diskio.h"
#include  "..\Device\SD_driver.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define ATA		0
#define MMC		1
#define USB		2



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	return(0);
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return(0);
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*
LBA�Ƿǳ�������һ��Ѱַģʽ�r��0��ʼ�������λ���飬��һ����LBA=0���ڶ�����LBA=1���������ơ�
����Ѱַģʽȡ����ԭ�Ȳ���ϵͳ������Դ洢�豸Ӳ������ķ�ʽ��
��ߴ����Ե�����CHS(cylinders-heads-sectors������-��ͷ-����)Ѱַģʽ��
���������Ӳ����ĳ����������ͷ��������Ӳ��λ�����ϳɵĵ�ַ��ָ����
// ��������disk_read_sectors 


// ��  �ܣ������� 
// ��  ����UINT32 start_sector ��ʼ������ַ 
// ��  ����BYTE sector_number  ��������������������Чֵ1-255 
// ��  ����BYTE *buff�������ݻ�����
// ����ֵ��TRUE/FALSE    
*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) *///������������
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) *///LBA(Logical Block Address),�������ƣ��߼������ַ��
	BYTE count		/* Number of sectors to read (1..255) *///��ȡ����������   ��������������������Чֵ1-255 
)
{
    //�����������Ϊ1��
	if(count == 1){	 // ��һ������
        SD_ReadSingleBlock(sector, buff);
    }else{			 // ���������
        SD_ReadMultiBlock(sector, buff, count);
    }
    return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s) 

// ��������disk_write_sectors 
// ��  �ܣ�д���� 
// ��  ����UINT32 start_sector ��ʼ������ַ 
// ��  ����BYTE sector_number  ����д�������������Чֵ1-255 
// ��  ����BYTE *buff�ȴ�д�������
// ����ֵ��TRUE/FALSE

*/

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
    if(count == 1){	   //д�������
        SD_WriteSingleBlock(sector, buff);
    }else{			   // д�������
        SD_WriteMultiBlock(sector, buff, count);
    }        
    return RES_OK;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}

DWORD get_fattime(void){
    return 0;
}

