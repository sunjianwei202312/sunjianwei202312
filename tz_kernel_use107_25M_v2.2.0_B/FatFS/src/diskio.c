/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

/*
给stm32移植fatfs文件系统，今天终于取得阶段性胜利。只需要提供这样几个函数即可 
DSTATUS disk_initialize (BYTE); 
DSTATUS disk_status (BYTE); 
DRESULT disk_read (BYTE, BYTE*, DWORD, BYTE); 
DRESULT disk_write (BYTE, const BYTE*, DWORD, BYTE); // 如果实现只读的文件系统就不需要了。 
DRESULT disk_ioctl (BYTE, BYTE, void*); 
移植成功后，可以用如下方式读取SD卡了，实在太方便了，和PC机上编程差不了多少。 
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
LBA是非常单纯的一种寻址模式﹔从0开始编号来定位区块，第一区块LBA=0，第二区块LBA=1，依此类推。
这种寻址模式取代了原先操作系统必须面对存储设备硬件构造的方式。
最具代表性的首推CHS(cylinders-heads-sectors，磁柱-磁头-扇区)寻址模式，
区块必须以硬盘上某个磁柱、磁头、扇区的硬件位置所合成的地址来指定。
// 函数名：disk_read_sectors 


// 功  能：读扇区 
// 参  数：UINT32 start_sector 起始扇区地址 
// 参  数：BYTE sector_number  连续读出的扇区数，有效值1-255 
// 参  数：BYTE *buff读出数据缓存区
// 返回值：TRUE/FALSE    
*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) *///物理驱动器！
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) *///LBA(Logical Block Address),中文名称：逻辑区块地址。
	BYTE count		/* Number of sectors to read (1..255) *///读取扇区的数量   连续读出的扇区数，有效值1-255 
)
{
    //如果扇区数量为1个
	if(count == 1){	 // 读一个扇区
        SD_ReadSingleBlock(sector, buff);
    }else{			 // 读多个扇区
        SD_ReadMultiBlock(sector, buff, count);
    }
    return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s) 

// 函数名：disk_write_sectors 
// 功  能：写扇区 
// 参  数：UINT32 start_sector 起始扇区地址 
// 参  数：BYTE sector_number  连续写入的扇区数，有效值1-255 
// 参  数：BYTE *buff等待写入的数据
// 返回值：TRUE/FALSE

*/

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
    if(count == 1){	   //写多个扇区
        SD_WriteSingleBlock(sector, buff);
    }else{			   // 写多个扇区
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

