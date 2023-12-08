/*
*********************************************************************************************************
*
*	模块名称 : SD卡Fat文件系统演示模块。
*	文件名称 : demo_sdio_fatfs.c
*	版    本 : V1.0
*	说    明 : 该例程移植FatFS文件系统（版本 R0.09b），演示如何创建文件、读取文件、创建目录和删除文件
*			并测试了文件读写速度。
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2015-12-12 armfly  正式发布
*
*	Copyright (C), 2015-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include   "bsp.h"
#include   "ff.h"/* FatFS文件系统模块*/
#include   "demo_nand_fatfs.h"
#include   "bsp_nand_flash.h"
#include   "mp3play.h"

/* 用于测试读写速度 */
#define TEST_FILE_LEN		(2*1024*1024)	/* 用于测试的文件长度 我选择的nand为128K的存储容量，所以选择128*1024 added by sjw*/
#define BUF_SIZE				(4*1024)		/* 每次读写SD卡的最大数据长度 */




/* FatFs API的返回值 */
static const char * FR_Table[]= 
{
	"FR_OK：成功",				                             /* (0) Succeeded */
	"FR_DISK_ERR：底层硬件错误",			                 /* (1) A hard error occurred in the low level disk I/O layer */
	"FR_INT_ERR：断言失败",				                     /* (2) Assertion failed */
	"FR_NOT_READY：物理驱动没有工作",			             /* (3) The physical drive cannot work */
	"FR_NO_FILE：文件不存在",				                 /* (4) Could not find the file */
	"FR_NO_PATH：路径不存在",				                 /* (5) Could not find the path */
	"FR_INVALID_NAME：无效文件名",		                     /* (6) The path name format is invalid */
	"FR_DENIED：由于禁止访问或者目录已满访问被拒绝",         /* (7) Access denied due to prohibited access or directory full */
	"FR_EXIST：文件已经存在",			                     /* (8) Access denied due to prohibited access */
	"FR_INVALID_OBJECT：文件或者目录对象无效",		         /* (9) The file/directory object is invalid */
	"FR_WRITE_PROTECTED：物理驱动被写保护",		             /* (10) The physical drive is write protected */
	"FR_INVALID_DRIVE：逻辑驱动号无效",		                 /* (11) The logical drive number is invalid */
	"FR_NOT_ENABLED：卷中无工作区",			                 /* (12) The volume has no work area */
	"FR_NO_FILESYSTEM：没有有效的FAT卷",		             /* (13) There is no valid FAT volume */
	"FR_MKFS_ABORTED：由于参数错误f_mkfs()被终止",	         /* (14) The f_mkfs() aborted due to any parameter error */
	"FR_TIMEOUT：在规定的时间内无法获得访问卷的许可",		 /* (15) Could not get a grant to access the volume within defined period */
	"FR_LOCKED：由于文件共享策略操作被拒绝",				 /* (16) The operation is rejected according to the file sharing policy */
	"FR_NOT_ENOUGH_CORE：无法分配长文件名工作区",		     /* (17) LFN working buffer could not be allocated */
	"FR_TOO_MANY_OPEN_FILES：当前打开的文件数大于_FS_SHARE", /* (18) Number of open files > _FS_SHARE */
	"FR_INVALID_PARAMETER：参数无效"	                     /* (19) Given parameter is invalid */
};


u32  test_nandflash[250000] __attribute__ ((at(0x70000000)));//测试1M空间大小！
const uint8_t mytemp_array[]="Ahttps://blog.csdn.net/whw8007/article/details/18189365 Bhttps://blog.csdn.net/whw8007/article/details/18189365 Chttps://blog.csdn.net/whw8007/article/details/18189365 Dhttps://blog.csdn.net/whw8007/article/details/18189365 Ehttps://blog.csdn.net/whw8007/article/details/18189365 Fhttps://blog.csdn.net/whw8007/article/details/18189365 Ghttps://blog.csdn.net/whw8007/article/details/18189365 Hhttps://blog.csdn.net/whw8007/article/details/18189365 Ihttps://blog.csdn.net/whw8007/article/details/18189365 Jhttps://blog.csdn.net/whw8007/article/details/18189365 Khttps://blog.csdn.net/whw8007/article/details/18189365 Lhttps://blog.csdn.net/whw8007/article/details/18189365 Mhttps://blog.csdn.net/whw8007/article/details/18189365 Nhttps://blog.csdn.net/whw8007/article/details/18189365ils/18189365O";
static uint8_t TestWriteBuffer [NAND_PAGE_TOTAL_SIZE];
static uint8_t TestReadBuffer [2*NAND_PAGE_TOTAL_SIZE];

void TestPlayMp3(uint8_t music);
uint16_t TestCount;
uint8_t  TestCountHL[2];
uint8_t  *pTestCountHL=TestCountHL;
__IO int32_t g_iRunTime = 0;
uint8_t g_TestBuf[BUF_SIZE];



 FIL       fsrc,fdst;                /* 文件对象 */
extern u8 readBuf[READBUF_SIZE];
DIR       DirInf;
FILINFO   FileInf;

static uint8_t TestWriteBuf [NAND_PAGE_SIZE];
static uint8_t TestReadBuf [NAND_PAGE_SIZE];
extern uint16_t *p_s_usLUT;

void OutFileContent(INT8U *p_array);





void 	AppErase68BlockBeforeBlock(void);
void 	FatfsTest();
void 	CreateNewFileChinese(void);
extern void DemoDis512DataInNand(uint8_t *psector);
/* 仅允许本文件内调用的函数声明 */
static void DispMenu(void);
static void ViewRootDir(void);
static void CreateNewFile(void);
static void ReadFileData(void);
static void CreateDir(void);
static void DeleteDirFile(void);
static void WriteFileTest(void);
extern void NAND_WriteOrReadSmallPage(uint32_t cmd);
extern void AppEraseAllBlock(void);
extern	uint8_t NAND_Format(void);
extern	uint32_t NAND_FormatCapacity(void);

extern  void    SEE_FSMC_NAND_ID(void);
extern  INT8U	  ItFlag;
extern  INT8U   StartEraseNandFlag;
extern	INT32U  ms_1;
extern  uint8_t NAND_DetectPageOobOfBlock(uint32_t _ulBlockNo,uint8_t page);
extern  uint8_t NAND_CallAgainFun(void);
extern  void DemoTestBigOrSmall(uint8_t *psector);
extern  void  SumsungTestEcc(uint8_t offset,uint8_t bit,uint8_t ifchange);
extern  void FSMC_NAND_TestWriteSmallPage(uint8_t zone,uint8_t block,uint8_t page,uint8_t count);
extern  void NAND_OutIfUsedInfo(void);
extern  uint8_t NAND_ActCopyBackTrue(uint32_t _ulSrcBlock, uint32_t _ulTarBlock);
extern  uint8_t NAND_ChangedPageOobOfBlock(uint32_t _ulBlockNo,uint8_t page);
extern  void NAND_WriteMyData(uint32_t _ulBlockNo,uint8_t index,uint8_t cmd);
extern  void NAND_WriteOrReadInit(uint8_t zone,uint16_t block,uint8_t page);
extern  void NAND_WriteOrReadDetect(uint8_t zone,uint16_t block,uint8_t page);
extern  void NAND_WriteContinousTwoPage(uint8_t zone,uint16_t block,uint8_t page);
extern  void NAND_WriteContinous32Page(uint8_t zone,uint16_t block,uint8_t page);

	extern BYTE  		buffer[512];// file copy buffer 




/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: FatFS文件系统演示主程序
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void DemoFatFS(uint8_t *cmd)
{
	uint8_t  		*ptemp1,*ptemp2,*ptemp3,*ptemp4,*temp;
	OS_CPU_SR  	cpu_sr;	     

	/* 
	打印命令列表，用户可以通过串口操作指令 
	Eboot 中给nandflash分区实现
	https://blog.csdn.net/whw8007/article/details/18189365
	*/

	
	{		
		bsp_Idle();		/* 这个函数在bsp.c文件。用户可以修改这个函数实现CPU休眠和喂狗 */
		
		//cmd = getchar();	/* 从串口读入一个字符 (阻塞方式) */
		//if (comGetChar(COM1, &cmd))	/* 从串口读入一个字符(非阻塞方式) */
		
		{
			//printf("\r\n------------------------------------------------\r\n");
			
			temp=cmd;
			
			cmd++;
			ptemp1=cmd;
			cmd++;
			ptemp2=cmd;
			cmd++;
			ptemp3=cmd;
			cmd++;
			ptemp4=cmd;
			
			cmd=temp;
			
			
			switch (*cmd)
			{
				case '0':		
					//printf("【0 - PlayMp3的512个数据顺次如下：】\r\n");
	        TestPlayMp3(*ptemp1);				  
				break;
	 			
				
				case '1':
					printf("【1 - ViewRootDir】\r\n");
					ViewRootDir();		/* 显示根目录下的文件名 */					  
					break;

				case '2':
					printf("【2 - CreateNewFile】\r\n");
					CreateNewFile();		/* 创建一个新文件,写入一个字符串 */
					break;

				case '3':
					printf("【3 - ReadFileData】\r\n");
					ReadFileData();		/* 读取根目录下srcfile.txt的内容 */
					break;

				case '4':
					printf("【4 - CreateDir】\r\n");
					CreateDir();		/* 创建目录 */
					break;

				case '5':
					printf("【5 - DeleteDirFile】\r\n");
					DeleteDirFile();	/* 删除目录和文件 */
					break;

				case '6':
					printf("【6 - TestSpeed】\r\n");
					WriteFileTest();	/* 速度测试 */
					break;
				case '7':
					printf("【7 - CreateNewFileChinese】\r\n");
					CreateNewFileChinese();	/* 速度测试 */
					break;
											
				//此命令用来对vs进行正弦测试！38+频率+
				case '8':
					VS1003B_SineTest(*ptemp1);	
				break;
					
					//此命令读取1page的512字节的内容
					case '9'://此功能为在nandflash写入文件系统后，我查看nandflash写入的内容是否正确！！
						 	NAND_OutBadBlockInfo();
					    //DemoDis512DataInNand(0x460);//为什么全为0？？？？？？？？？？？？？？？？？？？
					    DemoDis512DataInNand(cmd);//指令执行的格式为：0x38 page的四个字节（小端格式）+0x0D+0x0A
					break;
					
				/*
				Nand Flash驱动(实现初始化以及读操作)    此文章写的非常棒，值得研究added by sjw
				https://www.cnblogs.com/lifexy/p/7097695.html
				
					46 00 00 fe 0f 0d 0a
					39 c0 ff 01 00 0d 0a
				
				*/
				//测试nandflash的ECC功能
				case 'A':	//0x41
					
					SumsungTestEcc(*ptemp1,*ptemp2,*ptemp3);	//测试nandflash的ECC功能！！
        break;
		


				default:
					DispMenu();
					break;
			}
		}
	}
	
}






void AppEraseAllBlock(void)
{
	    uint16_t i;
	
	
	
      StartEraseNandFlag=1;
			for(i=0;i<4096;i++)
			{
				if(do_erase_nandflash(i)==0x40)// 操作成功
				{	
					printf("擦除第%d个块成功 \r\n",i);
				}else
					printf("擦除第%d个块失败\r\n",i);
				
				
				#if 0
					if(do_erase_nandflash(2)==0x40)// 操作成功
					{	
						printf("擦除第2个块成功 \r\n");
					}else
						printf("擦除第2个块失败\r\n");
					
					if(do_erase_nandflash(3)==0x40)// 操作成功
					{	
						printf("擦除第3个块成功 \r\n");
					}else
						printf("擦除第3个块失败\r\n");		
				#endif
				
			}
			StartEraseNandFlag=0;
			printf("总共擦除时间为%d ms \r\n",ms_1);	
			ms_1=0;
		//经过上步计算，全片擦除需要11824ms，不到12秒钟！	
		//11829ms  11843ms	
}



void AppErase68BlockBeforeBlock(void)
{
	    uint16_t i;
	
	
	
      StartEraseNandFlag=1;
			for(i=0;i<70;i++)
			{
				if(do_erase_nandflash(i)==0x40)// 操作成功
				{	
					printf("擦除第%d个块成功 \r\n",i);
				}else
					printf("擦除第%d个块失败\r\n",i);
			}
			StartEraseNandFlag=0;
			printf("总共擦除时间为%d ms \r\n",ms_1);	
			ms_1=0;
		//经过上步计算，前35个块擦除需要  ms，不到  秒钟！	
		
}



void DemoTest(uint16_t block,uint8_t action,uint8_t force)
{
	 NAND_OutBadBlockInfo();
//	 FSMC_NAND_TestWriteoneSector(block,action,force);
	//FSMC_NAND_EraseBlock(block);
	//NAND_OutBadBlockInfo();	     // 向串口1打印NAND Flash坏块信息 (此函数开头初始FSMC) 			
	
		
}





/*
*********************************************************************************************************
*	函 数 名: DispMenu
*	功能说明: 显示操作提示菜单
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void DispMenu(void)
{
	printf("\r\n------------------------------------------------\r\n");
	printf("请选择操作命令:\r\n");
	printf("1 - 显示根目录下的文件列表\r\n");
	printf("2 - 创建一个新文件sjwmissbabamam.txt\r\n");
	printf("3 - 读armfly.txt文件的内容\r\n");
	printf("4 - 创建目录\r\n");
	printf("5 - 删除文件和目录\r\n");
	printf("6 - 读写文件速度测试\r\n");
	printf("0 - NAND Flash 低级格式化\r\n");
}

void TestPlayMp3(uint8_t music)
{
	FRESULT  		res;
	FATFS 	 		fs;
	FIL         file;               // file objects
  uint8_t  		Status;
	INT16U 	    count=0; 	
	UINT 		    br;             		// File R/W count  文件读计数器  
	
	

	res = f_mount(&fs, "0:", 0);			/* Mount a logical drive */
	switch(music){
				case 1:
					res=f_open(&file, "x01.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 2:
					res=f_open(&file, "x02.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 3:
					res=f_open(&file, "x03.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 4:
					res=f_open(&file, "x04.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 5:
					res=f_open(&file, "x05.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 6:
					res=f_open(&file, "x06.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 7:
					res=f_open(&file, "x07.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 8:
					res=f_open(&file, "x08.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 9:
					res=f_open(&file, "x09.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 10:
					res=f_open(&file, "x10.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				case 11:
					res=f_open(&file, "x11.mp3", FA_OPEN_EXISTING | FA_READ);	
				break;
				default:
					res=f_open(&file, "x12.mp3", FA_OPEN_EXISTING | FA_READ);	
		}
	
	
	VS1003B_ResetDecodeTime();	
	for (;;){
		 res = f_read(&file, buffer, sizeof(buffer), &br);  	//读取512字节	
     //OutFileContent(buffer);	
		 if(res==0){ 
				count=0;  		
				while(count<512){                                 //根据SD卡介质的原因，文件每次只能读出512字节                                                                                                                     
						  while(VS1003B_WAIT_DREQ( )==0 ); // 等待空闲 VS1003数据申请口线， 每次为高后，可以通过SPIx写入32字节的音频数据		                            				 
							VS1003B_DATA_Write(&buffer[count], 32);//写入音频数据,每次送32个数据 
							count+=32;      		  
						  if (res || br == 0) break;                      // 是否到文件尾  
				}			 		
		  }  
		  if (res || br == 0) break;                            // 是否到文件尾  		
	 }  	 
	 count=0;  //根据VS1003的特性，需要音乐文件的末尾发送一些个0，保证下一个音频文件的播放  
	 while(count<2048) {                   
			 while(VS1003B_WAIT_DREQ( )==0 );          // 等待空闲
			 VS1003B_DATA_Write(&buffer[count], 32);//写入音频数据,每次送32个数据                                                  
			 count+=32;				 	  
	 } 
	 DelayMs(100);
	 f_close(&file);	

	res = f_mount(NULL, "0:", 0);    /* 卸载文件系统 */
}





	
	
/*
*********************************************************************************************************
*	函 数 名: ViewRootDir
*	功能说明: 显示SD卡根目录下的文件名
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void ViewRootDir(void)
{
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	DIR       DirInf;
	FILINFO   FileInf;
	FRESULT   result;
	uint32_t  cnt = 0;
	char lfname[256];

 	/* 挂载文件系统 */
	//result = f_mount(&myFatFs, FS_VOLUME_NAND, 0);	/* Mount a logical drive */
	result = f_mount(&myFatFs, "0:", 0);
	
	
	if (result != FR_OK)
	{
		printf("挂载文件系统失败 (%d)\r\n", result);
	}else
			printf("挂载文件系统成功！！ (%d)\r\n", result);
	
	
	/* 打开根文件夹 */
	result = f_opendir(&DirInf, "0:/"); /* 1: 表示盘符 */
	if (result != FR_OK)
	{
		printf("打开根目录失败 马上退出该函数！(%d)\r\n", result);
		//return;
	}else
		  printf("打开根目录成功！！！\r\n");

	/* 读取当前文件夹下的文件和目录 */
	FileInf.lfname = lfname;
	FileInf.lfsize = 256;

	printf("属性        |  文件大小 | 短文件名 | 长文件名\r\n");
	for (cnt = 0; ;cnt++)
	{
		result = f_readdir(&DirInf,&FileInf); 		/* 读取目录项，索引会自动下移 */
		if (result != FR_OK || FileInf.fname[0] == 0)
		{
			break;
		}

		if (FileInf.fname[0] == '.')
		{
			continue;
		}

		/* 判断是文件还是子目录 */
		if (FileInf.fattrib & AM_DIR)
		{
			printf("(0x%02d)目录  ", FileInf.fattrib);
		}
		else
		{
			printf("(0x%02d)文件  ", FileInf.fattrib);
		}

		/* 打印文件大小, 最大4G */
		printf(" %10d", FileInf.fsize);

		printf("  %s |", FileInf.fname);	/* 短文件名 */

		printf("  %s\r\n", (char *)FileInf.lfname);	/* 长文件名 */
	}

	/* 卸载文件系统 */
	f_mount(NULL, "0:", 0);
}


static void CreateNewFile(void)
{
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;
	uint32_t bw;
	
 	/* 挂载文件系统 */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive */
	
	f_mount(NULL, "0:", 0);
	
	
	result = f_mount(&myFatFs, "0:", 0);
  if (result != FR_OK)
	{
		printf("挂载文件系统失败 马上退出该函数！(%d)\r\n", result);
		return;
	}else{
		printf("挂载文件系统成功！(%d)\r\n", result);
	}
	
	
	/* 打开文件 */
	result = f_open(&file, "0:/armfly.txt", FA_CREATE_ALWAYS | FA_WRITE);

	/* 写一串数据 */
	//result = f_write(&file, "FatFS Write Demo \r\n www.armfly.com1234567890 \r\n", 44, &bw);
	result = f_write(&file, "卫东永远怀念我的爸爸和妈妈，至死不渝。13184009859", 50, &bw);
	if (result == FR_OK)
	{
		printf("armfly.txt 文件写入成功\r\n");
	}
	else
	{
		printf("armfly.txt 文件写入失败\r\n");
	}

	/* 关闭文件*/
	f_close(&file);

	/* 卸载文件系统 */
	f_mount(NULL, "0:", 0);
}


 void CreateNewFileChinese(void)
{
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;
	uint32_t bw;
	
 	/* 挂载文件系统 */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive */
	
	f_mount(NULL, "0:", 0);
	
	
	result = f_mount(&myFatFs, "0:", 0);
  if (result != FR_OK)
	{
		printf("挂载文件系统失败 马上退出该函数！(%d)\r\n", result);
		return;
	}else{
		printf("挂载文件系统成功！(%d)\r\n", result);
	}
	
	
	/*
	result = f_mkfs("0:",0,512);	
	if (result == FR_OK)
	{
		printf("Start Format(Low Level) ......\r\n");
		printf("磁盘低级格式化已经完成！ f_mkfs Ok\r\n");
	}else
		printf("磁盘低级格式化失败！");
	*/
	
	
	
	/* 打开文件 */
	result = f_open(&file, "0:爸爸和妈妈.txt", FA_CREATE_ALWAYS | FA_WRITE);

	/* 写一串数据 */
	result = f_write(&file, "卫东爱爸爸和妈妈 \r\n", 44, &bw);
	if (result == FR_OK)
	{
		printf("armfly.txt 文件写入成功\r\n");
	}
	else
	{
		printf("armfly.txt 文件写入失败\r\n");
	}

	/* 关闭文件*/
	f_close(&file);

	/* 卸载文件系统 */
	f_mount(NULL, "0:", 0);
}


/*
*********************************************************************************************************
*	函 数 名: ReadFileData
*	功能说明: 读取文件srcfile.txt前128个字符，并打印到串口
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void ReadFileData(void)
{
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	FRESULT   result;
	DIR DirInf;
	uint32_t bw;
	

 	/* 挂载文件系统 */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive *///原来为&fs现在修改为&fsrc  added by sjw
	if (result != FR_OK)
	{
		printf("挂载文件系统失败(%d)\r\n", result);
	}else
		  printf("挂载文件系统成功！！！\r\n");

	/* 打开根文件夹 */
	result = f_opendir(&DirInf, "0:/"); /* 1: 表示盘符 */
	if (result != FR_OK)
	{
		printf("打开根目录失败(%d)\r\n", result);
		return;
	}else
	  printf("打开根目录成功！！！\r\n");

	
	/* 打开文件 */
	//result = f_open(&fsrc, "1:/srcfile.txt", FA_OPEN_EXISTING | FA_READ);
	result = f_open(&fsrc, "0:/armfly.txt", FA_OPEN_EXISTING | FA_READ);
	if (result !=  FR_OK)
	{
		printf("Don't Find File:  armfly.txt\r\n");
		return;
	}else
	    printf("打开文件armfly.txt成功！！！\r\n");
	

	/* 读取文件 */
	result = f_read(&fsrc, &readBuf, sizeof(readBuf) - 1, &bw);
	if (bw > 0)
	{
		readBuf[bw] = 0;
		printf("\r\n armfly.txt 文件内容 : \r\n %s\r\n", readBuf);
	}
	else
	{
		printf("\r\n armfly.txt.txt 文件内容 : \r\n");
	}

	/* 关闭文件*/
	f_close(&fsrc);

	/* 卸载文件系统 */
	f_mount(NULL, "0:", 0);
}

/*
*********************************************************************************************************
*	函 数 名: CreateDir
*	功能说明: 在SD卡根目录创建Dir1和Dir2目录，在Dir1目录下创建子目录Dir1_1
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void CreateDir(void)
{
	FRESULT   result;	
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
	

 	/* 挂载文件系统 */
	result = f_mount(&myFatFs,"0:", 0);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("挂载文件系统失败 (%d)\r\n", result);
	}
  //result =f_mkfs("1:/Dir",0,512);
	//if (f_opendir(&dirs, path) == FR_OK){                /* 打开根目录 */	

	/* 创建目录/Dir1 */
	result = f_mkdir("0:/Dir1");
	// 结果为PR_NO_FILESYSTEM  磁盘上没有有效的FAT卷。
	
	
	if (result == FR_OK)
	{
		printf("f_mkdir Dir1 Ok\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir1 目录已经存在(%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir1 失败 (%d)\r\n", result);
		return;
	}

	/* 创建目录/Dir2 */
	result = f_mkdir("0:/Dir2");
	if (result == FR_OK)
	{
		printf("f_mkdir Dir2 Ok\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir2 目录已经存在(%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir2 失败 (%d)\r\n", result);
		return;
	}

	/* 创建子目录 /Dir1/Dir1_1	   注意：创建子目录Dir1_1时，必须先创建好Dir1 */
	result = f_mkdir("0:/Dir1/Dir1_1"); /* */
	if (result == FR_OK)
	{
		printf("f_mkdir Dir1_1 成功\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir1_1 目录已经存在 (%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir1_1 失败 (%d)\r\n", result);
		return;
	}

	/* 卸载文件系统 */
	f_mount(NULL, "0:", 0);
}

/*
*********************************************************************************************************
*	函 数 名: DeleteDirFile
*	功能说明: 删除SD卡根目录下的 armfly.txt 文件和 Dir1，Dir2 目录
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void DeleteDirFile(void)
{
	FRESULT   result;
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
 FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	char FileName[13];
	uint8_t i;

 	/* 挂载文件系统 */
	result = f_mount(&myFatFs,"0:", 0);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("挂载文件系统失败 (%d)\r\n", result);
	}

	#if 0
	/* 打开根文件夹 */
	result = f_opendir(&DirInf, "0:/"); /* 如果不带参数，则从当前目录开始 */
	if (result != FR_OK)
	{
		printf("打开根目录失败(%d)\r\n", result);
		return;
	}
	#endif

	/* 删除目录/Dir1 【因为还存在目录非空（存在子目录)，所以这次删除会失败】*/
	result = f_unlink("0:/Dir1");
	if (result == FR_OK)
	{
		printf("删除目录Dir1成功\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("没有发现文件或目录 :%s\r\n", "/Dir1");
	}
	else
	{
		printf("删除Dir1失败(错误代码 = %d) 文件只读或目录非空\r\n", result);
	}

	/* 先删除目录/Dir1/Dir1_1 */
	result = f_unlink("0:/Dir1/Dir1_1");
	if (result == FR_OK)
	{
		printf("删除子目录/Dir1/Dir1_1成功\r\n");
	}
	else if ((result == FR_NO_FILE) || (result == FR_NO_PATH))
	{
		printf("没有发现文件或目录 :%s\r\n", "/Dir1/Dir1_1");
	}
	else
	{
		printf("删除子目录/Dir1/Dir1_1失败(错误代码 = %d) 文件只读或目录非空\r\n", result);
	}

	/* 先删除目录/Dir1 */
	result = f_unlink("0:/Dir1");
	if (result == FR_OK)
	{
		printf("删除目录Dir1成功\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("没有发现文件或目录 :%s\r\n", "/Dir1");
	}
	else
	{
		printf("删除Dir1失败(错误代码 = %d) 文件只读或目录非空\r\n", result);
	}

	/* 删除目录/Dir2 */
	result = f_unlink("0:/Dir2");
	if (result == FR_OK)
	{
		printf("删除目录 Dir2 成功\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("没有发现文件或目录 :%s\r\n", "/Dir2");
	}
	else
	{
		printf("删除Dir2 失败(错误代码 = %d) 文件只读或目录非空\r\n", result);
	}

	/* 删除文件 armfly.txt */
	result = f_unlink("0:/srcfile.txt");
	if (result == FR_OK)
	{
		printf("删除文件 srcfile.txt 成功\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("没有发现文件或目录 :%s\r\n", "srcfile.txt");
	}
	else
	{
		printf("删除srcfile.txt失败(错误代码 = %d) 文件只读或目录非空\r\n", result);
	}

	/* 删除文件 speed1.txt */
	for (i = 0; i < 20; i++)
	{
		sprintf(FileName, "0:/Speed%02d.txt", i);		/* 每写1次，序号递增 */
		result = f_unlink(FileName);
		if (result == FR_OK)
		{
			printf("删除文件%s成功\r\n", FileName);
		}
		else if (result == FR_NO_FILE)
		{
			printf("没有发现文件:%s\r\n", FileName);
		}
		else
		{
			printf("删除%s文件失败(错误代码 = %d) 文件只读或目录非空\r\n", FileName, result);
		}
	}

	/* 卸载文件系统 */
	f_mount(NULL, "0:", 0);
}

/*
*********************************************************************************************************
*	函 数 名: WriteFileTest
*	功能说明: 测试文件读写速度
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void WriteFileTest(void)
{
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	FRESULT   result;
	DIR       DirInf;
	uint32_t  bw;
	uint32_t  i,k;
	uint32_t  runtime1,runtime2,timelen;
	uint8_t   err = 0;
	char      TestFileName[13];
	static uint8_t s_ucTestSn = 0;

	for (i = 0; i < sizeof(g_TestBuf); i++)
	{
		g_TestBuf[i] = (i / 512) + '0';
	}

  	/* 挂载文件系统 */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("挂载文件系统失败 (%d)\r\n", result);
	}

	/* 打开根文件夹 */
	result = f_opendir(&DirInf, "0:/"); /* 如果不带参数，则从当前目录开始 */
	if (result != FR_OK)
	{
		printf("打开根目录失败 (%d)\r\n", result);
		return;
	}

	/* 打开文件 */
	sprintf(TestFileName, "0:/Speed%02d.txt", s_ucTestSn++);		/* 每写1次，序号递增 */
	result = f_open(&fsrc, TestFileName, FA_CREATE_ALWAYS | FA_WRITE);

	/* 写一串数据 */
	printf("开始写文件%s %dKB ...\r\n", TestFileName, TEST_FILE_LEN / 1024);
	runtime1 = bsp_GetRunTime();	/* 读取系统运行时间 */
	for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
	{
		result = f_write(&fsrc, g_TestBuf, sizeof(g_TestBuf), &bw);
		if (result == FR_OK)
		{
			if (((i + 1) % 8) == 0){		
				printf(".");
			}
		}else{
			err = 1;
			printf("%s文件写失败\r\n", TestFileName);
			break;
		}
	}
	runtime2 = bsp_GetRunTime();	/* 读取系统运行时间 */

	if (err == 0)
	{
		timelen = (runtime2 - runtime1);
		printf("\r\n  写耗时 : %dms   平均写速度 : %dB/S (%dKB/S)\r\n",
			 timelen,
			(TEST_FILE_LEN * 1000) / timelen,
			((TEST_FILE_LEN / 1024) * 1000) / timelen);
	}

	f_close(&fsrc);		/* 关闭文件*/


	/* 开始读文件测试 */
	result = f_open(&fsrc, TestFileName, FA_OPEN_EXISTING | FA_READ);
	if (result !=  FR_OK)
	{
		printf("没有找到文件: %s\r\n", TestFileName);
		return;
	}

	printf("开始读文件 %dKB ...\r\n", TEST_FILE_LEN / 1024);
	runtime1 = bsp_GetRunTime();	/* 读取系统运行时间 */
	for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
	{
		result = f_read(&fsrc, g_TestBuf, sizeof(g_TestBuf), &bw);
		if (result == FR_OK)
		{
			if (((i + 1) % 8) == 0)
			{
				printf(".");
			}

			/* 比较写入的数据是否正确，此语句会导致读卡速度结果降低到 3.5MBytes/S */
			for (k = 0; k < sizeof(g_TestBuf); k++)
			{
				if (g_TestBuf[k] != (k / 512) + '0')
				{
				  	err = 1;
					printf("Speed1.txt 文件读成功，但是数据出错\r\n");
					break;
				}
			}
			if (err == 1)
			{
				break;
			}
		}
		else
		{
			err = 1;
			printf("Speed1.txt 文件读失败\r\n");
			break;
		}
	}
	runtime2 = bsp_GetRunTime();	/* 读取系统运行时间 */

	if (err == 0)
	{
		timelen = (runtime2 - runtime1);
		printf("\r\n  读耗时 : %dms   平均读速度 : %dB/S (%dKB/S)\r\n", timelen,
			(TEST_FILE_LEN * 1000) / timelen, ((TEST_FILE_LEN / 1024) * 1000) / timelen);
	}

	/* 关闭文件*/
	f_close(&fsrc);

	/* 卸载文件系统 */
	f_mount(NULL, "0:", 0);
}




void bsp_Idle(void)
{
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
}



/*
*********************************************************************************************************
*	函 数 名: bsp_GetRunTime
*	功能说明: 获取CPU运行时间，单位1ms。最长可以表示 24.85天，如果你的产品连续运行时间超过这个数，则必须考虑溢出问题
*	形    参:  无
*	返 回 值: CPU运行时间，单位1ms
*********************************************************************************************************
*/
int32_t bsp_GetRunTime(void)
{
	int32_t runtime;

	DISABLE_INT();  	/* 关中断 */

	runtime = g_iRunTime;	/* 这个变量在Systick中断中被改写，因此需要关中断进行保护 */

	ENABLE_INT();  		/* 开中断 */

	return runtime;
}



/*
*********************************************************
* 函数介绍：本函数是ECC测试程序。				
* 输入参数：无
* 输出参数：无
* 返回值  ：无
*********************************************************
*/
int TestECC(void)
{
    int i;
    uint32_t  colECC=0,lowECC=0;
    uint32_t  col=0, low=0;

    //rNFCONF=(1<<15)|(1<<12);

    for(i=0;i<512;i++)
   // NF_WRDATA(0x0); /* Write one page*/
    
    //[0]=rNFECC0;
   // seBuf[1]=rNFECC1;
   // seBuf[2]=rNFECC2;

   // printf("Old: ECC0=0x%x, ECC1=0x%x, ECC2=0x%x\n",seBuf[0],seBuf[1], seBuf[2]);

   // rNFCONF=(1<<15)|(1<<12);
/*
    for(i=0;i<200;i++)
    NF_WRDATA(0x0); 	// Write 200 byte
    NF_WRDATA(0x20);    //Write one btte(col: 5th, line: 200th)
    for(i=0;i<311;i++)
    NF_WRDATA(0x0); 	// Write 311 byte
*/
   // seBuf[3]=rNFECC0;
   // seBuf[4]=rNFECC1;
   // seBuf[5]=rNFECC2;

    //printf("New: ECC0=0x%x, ECC1=0x%x, ECC2=0x%x\n",seBuf[3],seBuf[4],seBuf[5]);

    //seBuf[6]=seBuf[0]^seBuf[3];
   // seBuf[7]=seBuf[1]^seBuf[4];
   // seBuf[8]=seBuf[2]^seBuf[5];
    
   // printf("XOR: ECC0=0x%x, ECC1=0x%x, ECC2=0x%x\n",seBuf[6],seBuf[7],seBuf[8]);

    //colECC=seBuf[8]>>2;
    //lowECC=((seBuf[8]&0x3)<<16)|(seBuf[7]<<8)|(seBuf[6]<<0);
    //printf("Low ECC=0x%x, Col ECC=0x%x\n", lowECC, colECC);

    /* Column parity*/
    for(i=0;i<3;i++)
    //col |= (Check10(colECC, i) <<i);

    printf("col=%dth\n",col); 

    /* Line parity*/
    for(i=0;i<9;i++)
    //low |= (Check10(lowECC, i) <<i);
    printf("low=%dth\n",low); 
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/




FATFS Fatfs_test;
void FatfsTest()
{
	 //FATFS Fatfs_test;//定义成全局
	 FIL fil;
	 UINT nWriteLen = 0;
	 UINT nReadLen = 0;
	 unsigned char buf[64] = {0};
	 unsigned char buf_write[] = "1234567890";
	 int res = 0;


	 res = f_mount(&Fatfs_test, "0:", 0);//f_mount(0, &Fatfs_test);
	 
	// res = f_mkfs("1:",0,256*4096);// 1MB大小 第一次运行需要格式化扇区
	// return;
	 
	

	 res = f_open(&fil, "1:/testfile.txt", FA_CREATE_NEW | FA_WRITE);
	 if(res == FR_OK)
	 {
			res = f_write(&fil,buf_write,strlen(buf_write),&nWriteLen);
			f_close(&fil);
	 }else{
			if(res == FR_EXIST)
			{
			 printf("文件存在\r\n");
			}else{
			 printf("文件创建失败,res:%d\r\n",res);
			}
	 }
	 
	 res = f_open(&fil, "1:/testfile.txt", FA_OPEN_EXISTING | FA_READ);
	 printf("res:%d\r\n",res);
	 for(;;)
	 {
			res = f_read(&fil,buf,sizeof(buf),&nReadLen);
			printf("res:%d,nReadLen:%d\r\n",res,nReadLen);  
			if(res||nReadLen == 0)/*错误或者读到文件尾*/
			 break;
	 }
	 f_close(&fil);
	  f_mount(NULL,"0:", 0);
	 

}


void DemoDis512DataInNand(uint8_t *psector)
{
	OS_CPU_SR  cpu_sr;
	uint16_t i,j;
	uint32_t sector;//从0到131072页!!!
	
	
	//FSMC_NAND_ReadSmallPage(buff, sector, count);
	
	/*
	  通过仿真我得到如下结论：(特别重要，块的地址是从0开始到4095结束，相对的页是从0开始到31结束！！！）
	1.比如要写入第2013个块内的第31页数据，
	  那么绝对页的地址是：2013*32p+31
	
		要写入比如第2013个块内的第1页数据，那么会显示该块为badblock
	*/
	sector=(uint32_t)(psector[4]<<24)+(uint32_t)(psector[3]<<16)+(uint32_t)(psector[2]<<8)+psector[1];
	
	
	
	for(i=0;i<NAND_PAGE_SIZE;i++){
	   TestWriteBuf [i]=00;
		 TestReadBuf[i]=0x5a;
	}
	
	printf("***********************本页中的512字节的数据如下：**********************\r\n");
	
	
	
	
//	FSMC_NAND_ReadPage(TestReadBuf,sector,0,NAND_PAGE_SIZE,0);
	for(i = 0; i < NAND_PAGE_SIZE;  i++)
	{	
		if(i%32==0){
			printf("\r\n");
			printf("%#x ",TestReadBuf[i]);
		}else
			printf("%#x ",TestReadBuf[i]);
	}
	printf("******************************************************************\r\n");


	
	
	
	
	#if 0
	FSMC_NAND_ReadPage(TestReadBuf,0,0,512);
	for(i = 0; i < NAND_PAGE_TOTAL_SIZE;  i++)
	{	
		if(i%32==0){
			printf("\r\n");
			printf("%#x ",TestReadBuf[i]);
		}else
			printf("%#x ",TestReadBuf[i]);
	}
	printf("*********************************\r\n");	
	
	FSMC_NAND_ReadPage(TestReadBuf,2,0,512);
	
	for(i = 0; i < NAND_PAGE_TOTAL_SIZE;  i++)
	{	
		if(i%32==0){
			printf("\r\n");
			printf("%#x ",TestReadBuf[i]);
		}else
			printf("%#x ",TestReadBuf[i]);
	}
	printf("*********************************\r\n");
	
	FSMC_NAND_ReadPage(TestReadBuf,3,0,512);
	
	for(i = 0; i < NAND_PAGE_TOTAL_SIZE;  i++)
	{	
		if(i%32==0){
			printf("\r\n");
			printf("%#x ",TestReadBuf[i]);
		}else
			printf("%#x ",TestReadBuf[i]);
	}
	printf("*********************************\r\n");
	
 #endif
	
	
}




 uint8_t do_erase_nandflash(uint32_t _ulBlockNo)
{
	FSMC_NAND_EraseBlock(_ulBlockNo);
}



/*
————————————————
版权声明：本文为CSDN博主「hxl5955」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/hxl5955/article/details/53322944

*/


/*
*********************************************************************************************************
*	函 数 名: FileFormat
*	功能说明: 文件系统格式化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void FileFormat(void)
{
	/* 本函数使用的局部变量占用较多，请修改启动文件，保证堆栈空间够用 */
	FRESULT result;
	FATFS fs;

	/* 挂载文件系统 */
	result = f_mount(&fs, "0:", 0);	
	if (result != FR_OK)
	{
		printf("挂载文件系统失败 (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("挂载文件系统成功 (%s)\r\n", FR_Table[result]);
	}
	
	/* 第一次使用必须进行格式化 */
	result = f_mkfs("0:",0,0);
	if (result != FR_OK)
	{
		printf("格式化失败 (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("格式化成功 (%s)\r\n", FR_Table[result]);
	}

	/* 卸载文件系统 */
	result  = f_mount(NULL, "0:", 0);
	if (result != FR_OK)
	{
		printf("卸载文件系统失败 (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("卸载文件系统成功 (%s)\r\n", FR_Table[result]);
	}
}
void OutFileContent(INT8U *p_array)
{
	INT8U in,out;
	for(out=0;out<32;out++){
		for(in=0;in<16;in++){
			printf("0x%x",p_array[16*out+in]);
		}
		//printf("\r\n");
	}
	
}