#ifndef __VS1003B_H
#define __VS1003B_H
#include "includes.h"

// VS1003控制引脚
#define VS1003B_RESET_PORT	 		GPIOC		  
#define VS1003B_RESET_BIT 	 		GPIO_Pin_8  


//以下用SPI2引脚来操作vs1003 PB12 PB13 PB14 PB15
#define VS1003B_CMD_CS_PORT  		GPIOB		     // 命令控制端口  控制命令   xCS
#define VS1003B_CMD_CS_BIT   		GPIO_Pin_1  // 命令控制引脚   GPIO_Pin_12          

#define VS1003B_DATA_CS_PORT		GPIOA		     // 数据控制端口            xDCS
#define VS1003B_DATA_CS_BIT 		GPIO_Pin_8   // 数据控制引脚

#define VS1003B_DREQ_PORT   		GPIOB		     // 数据控制端口    DREQ
#define VS1003B_DREQ_BIT    		GPIO_Pin_5   // 数据控制引脚

   

/* reset */
#define MP3_Reset(x)	  x ? (GPIO_SetBits(VS1003B_RESET_PORT,VS1003B_RESET_BIT))   : (GPIO_ResetBits(VS1003B_RESET_PORT,VS1003B_RESET_BIT))

/* 命令片选 */
#define MP3_xCS(x)	    x ? GPIO_SetBits(VS1003B_CMD_CS_PORT,VS1003B_CMD_CS_BIT)   : GPIO_ResetBits(VS1003B_CMD_CS_PORT,VS1003B_CMD_CS_BIT)

/* 数据片选 */ 
#define MP3_xDCS(x)	    x ? GPIO_SetBits(VS1003B_DATA_CS_PORT,VS1003B_DATA_CS_BIT) : GPIO_ResetBits(VS1003B_DATA_CS_PORT,VS1003B_DATA_CS_BIT)

#define	VS1003B_WAIT_DREQ( )			  (GPIO_ReadInputDataBit(VS1003B_DREQ_PORT, VS1003B_DREQ_BIT))






// VS1003控制命令
#define VS_WRITE_COMMAND 	0x02
#define VS_READ_COMMAND 	0x03

/*
 VS1003寄存器定义  VS1003 共有 16 个 16 位的寄存器， 地址分别为 0x0 – 0xF；
 除了模式寄存器 （MODE， 0x0） 和状态寄存器 （STATUS，0x1）
 在复位后的初始值分别为 0x800 和 0x3C 外，其余的寄存器在 VS1003 初始化后的值均为 0
 
 VS1003中的寄存器
 https://blog.csdn.net/cy941228/article/details/52700889
 此网页内的解释比较透切，值得一看
*/
#define SPI_MODE        	0x00   
#define SPI_STATUS      	0x01  //vs1003的状态 
#define SPI_BASS        	0x02  //内置高低音增强器 
#define SPI_CLOCKF      	0x03  //时钟频率+倍频数
#define SPI_DECODE_TIME 	0x04  //解码时间
#define SPI_AUDATA      	0x05   //各种音频数据
#define SPI_WRAM        	0x06   //RAM读、写
#define SPI_WRAMADDR    	0x07   //RAM读写地址
#define SPI_HDAT0       	0x08   //流头数据0
#define SPI_HDAT1       	0x09   //流头数据1



#define SPI_AIADDR      	0x0a  // 用户代码起始地址
#define SPI_VOL         	0x0b   //音量控制

#define SPI_AICTRL0     	0x0c   //应用控制器存器0
#define SPI_AICTRL1     	0x0d   //应用控制器存器1
#define SPI_AICTRL2     	0x0e   //应用控制器存器2
#define SPI_AICTRL3     	0x0f   //应用控制器存器3


/*
8．6．10 SCI_AIADDR (RW)
SCI_AIADDR指出了应用代码的开始地址，要在SCI_WRAMADDR和SCI_WARM之前写入。如果不使用应
用代码，此寄存器可以不初始化，也可初始化为0。详见VS10xx应用笔记。


8．6．12 SCI_AICTRL[x] (RW)
SCI_AICTRL[x]寄存器（x=[0..3]）可用作访问用户应用程序。

8．6．11 SCI_VOL (RW)
SCI_VOL可以控制播放器硬件音量。对每个声道，一个0 到254间的数被定义为从最大音量级别以0.5dB衰
减。左声道值乘256。因而，最大的音量是0，而静音为0xFEFE。
例如：若左声道为-2.0dB，右声道为-3.5dB：(4×256)+7=0x407。注意，在启动的时候被设置为满音量。软件
复位不会改变音量设定。
注意：设置SCI_VOL为0xFFFF将使芯片进入模拟掉电模式。



8．6．6 SCI_AUDATA (RW)
当解码正确的数据时，当前的采样率和通道数可以从SCI_AUDATA 的15：1 位和0 位中读取。15：1位域包
含了采样率除二后的值，位0为0 表示单声道，为1表示立体声。
写SCI_AUDATA 将直接改变采样率。
例如：44100Hz 立体声数据，读出来即为0xAC45(44101)。


SCI_HDAT0 和SCI_HDAT1 (R)
对于WAV文件，SCI_HDAT0 和SCI_HDAT1 读出值分别是0x7761 和0x7665。

对于WMA文件，SCI_HDAT1 的值为0x574D, SCI_HDAT0 包含了用字节每/秒描述的数据速度。若要获取文
件的比特率，将SCI_HDAT0 的值除8。

对于MIDI文件，SCI_HDAT1 的值为0x4D54，SCI_HDAT0 包含的值遵照下表。

对于MP3文件，SCI_HDAT[0…1]有以下的内容
当读的时候，SCI_HDAT0 和SCI_HDAT1 包含的头信息是从MP3 流开始解码时提取的。复位之后两个寄存器
都清零，指示没有数据被找到。
*/






#define SM_DIFF         	0x01   
#define SM_JUMP         	0x02   
#define SM_RESET        	0x04   
#define SM_OUTOFWAV     	0x08   
#define SM_PDOWN        	0x10   
#define SM_TESTS        	0x20   
#define SM_STREAM       	0x40   
#define SM_PLUSV        	0x80   
#define SM_DACT         	0x100   
#define SM_SDIORD       	0x200   
#define SM_SDISHARE     	0x400   
#define SM_SDINEW       	0x800   
#define SM_ADPCM        	0x1000   
#define SM_ADPCM_HP     	0x2000


// 函数声明
void  VS1003B_WriteData( uint8_t * buf);
void  VS1003BPin_Init(void);
void 	VS1003B_CMD_Write(INT8U address, INT16U data,INT8U device);
void 	VS1003B_SCI_Test(void);
void 	VS1003B_DetectSCIOk(void);
void 	VS1003B_SoftReset(void);
void 	SD_SPIDrive_Init(uint8_t device);
void 	VS1003B_HardReset(void);			    //硬复位
void 	VS1003B_SoftReset(void);  		    //软复位
void 	VS1003B_SineTest(INT8U fre);   		//正旋测试
void 	VS1003B_ResetDecodeTime(void);	  //复位解码时间
void 	VS1003B_LoadPatch(void);		      //加载频谱程序
void 	VS1003B_GetSpec(INT8U *p);		    //读取频谱
void 	InitRecordADPCM(void);			      //VS1003 IMA ADPCM录音初始化
void 	VS1003B_DATA_Write(unsigned char * buf, INT8U br); //VS1003写数据  br最大值为32


INT16U 	VS1003B_RAMTest(void);	 		    //RAM测试
INT16U 	VS1003B_GetDecodeTime(void);   	//读取解码时间 
INT16U 	VS1003B_REG_Read(INT8U address);//VS1003读寄存器

void TestReadFile(void);

void TestWriteFile(void);
void SD_SPIPin_Init(void);

extern	void DelayMs(vu32 m);
extern	void DelayUs(vu32 m);
#endif


