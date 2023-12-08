#ifndef _SD_DRIVER_H_
#define _SD_DRIVER_H_

#include "includes.h"
#include "sdcard.h"

// SD卡类型定义 
#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    4

// SPI总线速度设置
#define SPI_SPEED_LOW   0   // 低速
#define SPI_SPEED_HIGH  1   // 高速

// SD传输数据结束后是否释放总线宏定义 
#define NO_RELEASE      0   //不释放总线，在连续写字节时 
#define RELEASE         1   // 释放总线，   在写单字节时

// SD卡指令表 
#define CMD0    0       //卡复位
#define CMD9    9       //命令9 ，读CSD数据----读取卡特定数据寄存器！		
#define CMD10   10      //命令10，读CID数据----读取卡标志数据寄存器！
#define CMD12   12      //命令12，停止数据传输
#define CMD16   16      //命令16，设置SectorSize 应返回0x00---设置块大小(字节数）
#define CMD17   17      //命令17，读sector-----读取一个块的数据
#define CMD18   18      //命令18，读Multi sector
#define ACMD23  23      //命令23，设置多sector写入前预先擦除N个block
#define CMD24   24      //命令24，写sector-----写入一个块的数据
#define CMD25   25      //命令25，写Multi sector
#define ACMD41  41      //命令41，应返回0x00---引用命令的前命令
#define CMD55   55      //命令55，应返回0x01---开始卡的初始化
#define CMD58   58      //命令58，读OCR信息
#define CMD59   59      //命令59，使能/禁止CRC，应返回0x00--设置crc开启（1）或者关闭（0）
//其中R1的回应格式如下表所示：
/*
bit7   bit6        bit5        bit4         bit3          bit2      bit1      bit0

0	  参数错误    地址错误   连续擦除错误   命令crc错误    非法命令   擦除复位   idle状态

SD卡的典型初始化过程如下：  
1、初始化与SD卡连接的硬件条件（MCU的SPI配置，IO口配置）； 
2、上电延时（>74个CLK）；
3、复位卡（CMD0）； 
4、激活卡，内部初始化并获取卡类型（CMD1（用于MMC卡）、CMD55、CMD41）；
5.、查询OCR，获取供电状况（CMD58）；
6、是否使用CRC（CMD59）； 
7、设置读写块数据长度（CMD16）；  
8、读取CSD，获取存储卡的其他信息（CMD9）；
9、发送8CLK后，禁止片选； 
这样我们就完成了对SD卡的初始化，


SD卡读取数据，这里通过CMD17来实现，具体过程如下：
1、发送CMD17； 
2、接收卡响应R1；  
3、接收数据起始令牌0XFE； 
4、接收数据； 
5、接收2个字节的CRC，如果没有开启CRC，这两个字节在读取后可以丢掉。
6、8CLK之后禁止片选；  
以上就是一个典型的读取SD卡数据过程，SD卡的写于读数据差不多，写数据通过CMD24来实现。
*/

//相关控制引脚宏定义 
#define SD_CS_ENABLE()     GPIO_ResetBits(GPIOB,GPIO_Pin_10)        //选中SD卡
#define SD_CS_DISABLE()    GPIO_SetBits(GPIOB,GPIO_Pin_10)          //不选中SD卡
#define SD_PWR_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_3)         //SD卡上电
#define SD_PWR_OFF()       GPIO_SetBits(GPIOC,GPIO_Pin_8)           //SD卡断电
#define SD_CD()            GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) // 低电平有卡，高电平无卡




//#define SD_CS_ENABLE()     GPIOB->ODR &=~(1<<12)// GPIO_ResetBits(GPIOB,GPIO_Pin_6)   //选中SD卡
//#define SD_CS_DISABLE()    GPIOB->ODR |= (1<<12)  //GPIO_SetBits(GPIOB,GPIO_Pin_6)     //不选中SD卡
//#define SD_PWR_ON()       //  GPIOD->ODR &=~(1<<10) //GPIO_ResetBits(GPIOD,GPIO_Pin_10)  //SD卡上电
//#define SD_PWR_OFF()      //  GPIOD->ODR |= (1<<10)  //GPIO_SetBits(GPIOD,GPIO_Pin_10)    //SD卡断电
////#define SD_DET()           !GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) //检测有卡
//                                                                    //1-有 0-无



// 公共函数声明
void SPI1_SetSpeed(u8 SpeedSet);	  // 设置SIP的速度
void SPI2_SetSpeed(u8 SpeedSet);	  // 设置SIP的速度
u8 SPI1_ReadWriteByte(u8 TxData);   //SPI总线读写一个字节
u8 SD_GetCSD(u8 *csd_data);

u8 SD_ReadSingleBlock(u32 sector, u8 *buffer);  //读一个sector
u8 SD_WriteSingleBlock(u32 sector, const u8 *buffer); //写一个sector
u8 SD_ReadMultiBlock(u32 sector, u8 *buffer, u8 count); //读多个sector
u8 SD_WriteMultiBlock(u32 sector, const u8 *data, u8 count);  //写多个sector

#endif

