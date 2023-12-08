/*
*********************************************************************************************************
*
*	ģ������ : SD��Fat�ļ�ϵͳ��ʾģ�顣
*	�ļ����� : demo_sdio_fatfs.c
*	��    �� : V1.0
*	˵    �� : ��������ֲFatFS�ļ�ϵͳ���汾 R0.09b������ʾ��δ����ļ�����ȡ�ļ�������Ŀ¼��ɾ���ļ�
*			���������ļ���д�ٶȡ�
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2015-12-12 armfly  ��ʽ����
*
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include   "bsp.h"
#include   "ff.h"/* FatFS�ļ�ϵͳģ��*/
#include   "demo_nand_fatfs.h"
#include   "bsp_nand_flash.h"
#include   "mp3play.h"

/* ���ڲ��Զ�д�ٶ� */
#define TEST_FILE_LEN		(2*1024*1024)	/* ���ڲ��Ե��ļ����� ��ѡ���nandΪ128K�Ĵ洢����������ѡ��128*1024 added by sjw*/
#define BUF_SIZE				(4*1024)		/* ÿ�ζ�дSD����������ݳ��� */




/* FatFs API�ķ���ֵ */
static const char * FR_Table[]= 
{
	"FR_OK���ɹ�",				                             /* (0) Succeeded */
	"FR_DISK_ERR���ײ�Ӳ������",			                 /* (1) A hard error occurred in the low level disk I/O layer */
	"FR_INT_ERR������ʧ��",				                     /* (2) Assertion failed */
	"FR_NOT_READY����������û�й���",			             /* (3) The physical drive cannot work */
	"FR_NO_FILE���ļ�������",				                 /* (4) Could not find the file */
	"FR_NO_PATH��·��������",				                 /* (5) Could not find the path */
	"FR_INVALID_NAME����Ч�ļ���",		                     /* (6) The path name format is invalid */
	"FR_DENIED�����ڽ�ֹ���ʻ���Ŀ¼�������ʱ��ܾ�",         /* (7) Access denied due to prohibited access or directory full */
	"FR_EXIST���ļ��Ѿ�����",			                     /* (8) Access denied due to prohibited access */
	"FR_INVALID_OBJECT���ļ�����Ŀ¼������Ч",		         /* (9) The file/directory object is invalid */
	"FR_WRITE_PROTECTED������������д����",		             /* (10) The physical drive is write protected */
	"FR_INVALID_DRIVE���߼���������Ч",		                 /* (11) The logical drive number is invalid */
	"FR_NOT_ENABLED�������޹�����",			                 /* (12) The volume has no work area */
	"FR_NO_FILESYSTEM��û����Ч��FAT��",		             /* (13) There is no valid FAT volume */
	"FR_MKFS_ABORTED�����ڲ�������f_mkfs()����ֹ",	         /* (14) The f_mkfs() aborted due to any parameter error */
	"FR_TIMEOUT���ڹ涨��ʱ�����޷���÷��ʾ�����",		 /* (15) Could not get a grant to access the volume within defined period */
	"FR_LOCKED�������ļ�������Բ������ܾ�",				 /* (16) The operation is rejected according to the file sharing policy */
	"FR_NOT_ENOUGH_CORE���޷����䳤�ļ���������",		     /* (17) LFN working buffer could not be allocated */
	"FR_TOO_MANY_OPEN_FILES����ǰ�򿪵��ļ�������_FS_SHARE", /* (18) Number of open files > _FS_SHARE */
	"FR_INVALID_PARAMETER��������Ч"	                     /* (19) Given parameter is invalid */
};


u32  test_nandflash[250000] __attribute__ ((at(0x70000000)));//����1M�ռ��С��
const uint8_t mytemp_array[]="Ahttps://blog.csdn.net/whw8007/article/details/18189365 Bhttps://blog.csdn.net/whw8007/article/details/18189365 Chttps://blog.csdn.net/whw8007/article/details/18189365 Dhttps://blog.csdn.net/whw8007/article/details/18189365 Ehttps://blog.csdn.net/whw8007/article/details/18189365 Fhttps://blog.csdn.net/whw8007/article/details/18189365 Ghttps://blog.csdn.net/whw8007/article/details/18189365 Hhttps://blog.csdn.net/whw8007/article/details/18189365 Ihttps://blog.csdn.net/whw8007/article/details/18189365 Jhttps://blog.csdn.net/whw8007/article/details/18189365 Khttps://blog.csdn.net/whw8007/article/details/18189365 Lhttps://blog.csdn.net/whw8007/article/details/18189365 Mhttps://blog.csdn.net/whw8007/article/details/18189365 Nhttps://blog.csdn.net/whw8007/article/details/18189365ils/18189365O";
static uint8_t TestWriteBuffer [NAND_PAGE_TOTAL_SIZE];
static uint8_t TestReadBuffer [2*NAND_PAGE_TOTAL_SIZE];

void TestPlayMp3(uint8_t music);
uint16_t TestCount;
uint8_t  TestCountHL[2];
uint8_t  *pTestCountHL=TestCountHL;
__IO int32_t g_iRunTime = 0;
uint8_t g_TestBuf[BUF_SIZE];



 FIL       fsrc,fdst;                /* �ļ����� */
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
/* �������ļ��ڵ��õĺ������� */
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
*	�� �� ��: 
*	����˵��: FatFS�ļ�ϵͳ��ʾ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void DemoFatFS(uint8_t *cmd)
{
	uint8_t  		*ptemp1,*ptemp2,*ptemp3,*ptemp4,*temp;
	OS_CPU_SR  	cpu_sr;	     

	/* 
	��ӡ�����б��û�����ͨ�����ڲ���ָ�� 
	Eboot �и�nandflash����ʵ��
	https://blog.csdn.net/whw8007/article/details/18189365
	*/

	
	{		
		bsp_Idle();		/* ���������bsp.c�ļ����û������޸��������ʵ��CPU���ߺ�ι�� */
		
		//cmd = getchar();	/* �Ӵ��ڶ���һ���ַ� (������ʽ) */
		//if (comGetChar(COM1, &cmd))	/* �Ӵ��ڶ���һ���ַ�(��������ʽ) */
		
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
					//printf("��0 - PlayMp3��512������˳�����£���\r\n");
	        TestPlayMp3(*ptemp1);				  
				break;
	 			
				
				case '1':
					printf("��1 - ViewRootDir��\r\n");
					ViewRootDir();		/* ��ʾ��Ŀ¼�µ��ļ��� */					  
					break;

				case '2':
					printf("��2 - CreateNewFile��\r\n");
					CreateNewFile();		/* ����һ�����ļ�,д��һ���ַ��� */
					break;

				case '3':
					printf("��3 - ReadFileData��\r\n");
					ReadFileData();		/* ��ȡ��Ŀ¼��srcfile.txt������ */
					break;

				case '4':
					printf("��4 - CreateDir��\r\n");
					CreateDir();		/* ����Ŀ¼ */
					break;

				case '5':
					printf("��5 - DeleteDirFile��\r\n");
					DeleteDirFile();	/* ɾ��Ŀ¼���ļ� */
					break;

				case '6':
					printf("��6 - TestSpeed��\r\n");
					WriteFileTest();	/* �ٶȲ��� */
					break;
				case '7':
					printf("��7 - CreateNewFileChinese��\r\n");
					CreateNewFileChinese();	/* �ٶȲ��� */
					break;
											
				//������������vs�������Ҳ��ԣ�38+Ƶ��+
				case '8':
					VS1003B_SineTest(*ptemp1);	
				break;
					
					//�������ȡ1page��512�ֽڵ�����
					case '9'://�˹���Ϊ��nandflashд���ļ�ϵͳ���Ҳ鿴nandflashд��������Ƿ���ȷ����
						 	NAND_OutBadBlockInfo();
					    //DemoDis512DataInNand(0x460);//ΪʲôȫΪ0��������������������������������������
					    DemoDis512DataInNand(cmd);//ָ��ִ�еĸ�ʽΪ��0x38 page���ĸ��ֽڣ�С�˸�ʽ��+0x0D+0x0A
					break;
					
				/*
				Nand Flash����(ʵ�ֳ�ʼ���Լ�������)    ������д�ķǳ�����ֵ���о�added by sjw
				https://www.cnblogs.com/lifexy/p/7097695.html
				
					46 00 00 fe 0f 0d 0a
					39 c0 ff 01 00 0d 0a
				
				*/
				//����nandflash��ECC����
				case 'A':	//0x41
					
					SumsungTestEcc(*ptemp1,*ptemp2,*ptemp3);	//����nandflash��ECC���ܣ���
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
				if(do_erase_nandflash(i)==0x40)// �����ɹ�
				{	
					printf("������%d����ɹ� \r\n",i);
				}else
					printf("������%d����ʧ��\r\n",i);
				
				
				#if 0
					if(do_erase_nandflash(2)==0x40)// �����ɹ�
					{	
						printf("������2����ɹ� \r\n");
					}else
						printf("������2����ʧ��\r\n");
					
					if(do_erase_nandflash(3)==0x40)// �����ɹ�
					{	
						printf("������3����ɹ� \r\n");
					}else
						printf("������3����ʧ��\r\n");		
				#endif
				
			}
			StartEraseNandFlag=0;
			printf("�ܹ�����ʱ��Ϊ%d ms \r\n",ms_1);	
			ms_1=0;
		//�����ϲ����㣬ȫƬ������Ҫ11824ms������12���ӣ�	
		//11829ms  11843ms	
}



void AppErase68BlockBeforeBlock(void)
{
	    uint16_t i;
	
	
	
      StartEraseNandFlag=1;
			for(i=0;i<70;i++)
			{
				if(do_erase_nandflash(i)==0x40)// �����ɹ�
				{	
					printf("������%d����ɹ� \r\n",i);
				}else
					printf("������%d����ʧ��\r\n",i);
			}
			StartEraseNandFlag=0;
			printf("�ܹ�����ʱ��Ϊ%d ms \r\n",ms_1);	
			ms_1=0;
		//�����ϲ����㣬ǰ35���������Ҫ  ms������  ���ӣ�	
		
}



void DemoTest(uint16_t block,uint8_t action,uint8_t force)
{
	 NAND_OutBadBlockInfo();
//	 FSMC_NAND_TestWriteoneSector(block,action,force);
	//FSMC_NAND_EraseBlock(block);
	//NAND_OutBadBlockInfo();	     // �򴮿�1��ӡNAND Flash������Ϣ (�˺�����ͷ��ʼFSMC) 			
	
		
}





/*
*********************************************************************************************************
*	�� �� ��: DispMenu
*	����˵��: ��ʾ������ʾ�˵�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DispMenu(void)
{
	printf("\r\n------------------------------------------------\r\n");
	printf("��ѡ���������:\r\n");
	printf("1 - ��ʾ��Ŀ¼�µ��ļ��б�\r\n");
	printf("2 - ����һ�����ļ�sjwmissbabamam.txt\r\n");
	printf("3 - ��armfly.txt�ļ�������\r\n");
	printf("4 - ����Ŀ¼\r\n");
	printf("5 - ɾ���ļ���Ŀ¼\r\n");
	printf("6 - ��д�ļ��ٶȲ���\r\n");
	printf("0 - NAND Flash �ͼ���ʽ��\r\n");
}

void TestPlayMp3(uint8_t music)
{
	FRESULT  		res;
	FATFS 	 		fs;
	FIL         file;               // file objects
  uint8_t  		Status;
	INT16U 	    count=0; 	
	UINT 		    br;             		// File R/W count  �ļ���������  
	
	

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
		 res = f_read(&file, buffer, sizeof(buffer), &br);  	//��ȡ512�ֽ�	
     //OutFileContent(buffer);	
		 if(res==0){ 
				count=0;  		
				while(count<512){                                 //����SD�����ʵ�ԭ���ļ�ÿ��ֻ�ܶ���512�ֽ�                                                                                                                     
						  while(VS1003B_WAIT_DREQ( )==0 ); // �ȴ����� VS1003����������ߣ� ÿ��Ϊ�ߺ󣬿���ͨ��SPIxд��32�ֽڵ���Ƶ����		                            				 
							VS1003B_DATA_Write(&buffer[count], 32);//д����Ƶ����,ÿ����32������ 
							count+=32;      		  
						  if (res || br == 0) break;                      // �Ƿ��ļ�β  
				}			 		
		  }  
		  if (res || br == 0) break;                            // �Ƿ��ļ�β  		
	 }  	 
	 count=0;  //����VS1003�����ԣ���Ҫ�����ļ���ĩβ����һЩ��0����֤��һ����Ƶ�ļ��Ĳ���  
	 while(count<2048) {                   
			 while(VS1003B_WAIT_DREQ( )==0 );          // �ȴ�����
			 VS1003B_DATA_Write(&buffer[count], 32);//д����Ƶ����,ÿ����32������                                                  
			 count+=32;				 	  
	 } 
	 DelayMs(100);
	 f_close(&file);	

	res = f_mount(NULL, "0:", 0);    /* ж���ļ�ϵͳ */
}





	
	
/*
*********************************************************************************************************
*	�� �� ��: ViewRootDir
*	����˵��: ��ʾSD����Ŀ¼�µ��ļ���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void ViewRootDir(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	DIR       DirInf;
	FILINFO   FileInf;
	FRESULT   result;
	uint32_t  cnt = 0;
	char lfname[256];

 	/* �����ļ�ϵͳ */
	//result = f_mount(&myFatFs, FS_VOLUME_NAND, 0);	/* Mount a logical drive */
	result = f_mount(&myFatFs, "0:", 0);
	
	
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}else
			printf("�����ļ�ϵͳ�ɹ����� (%d)\r\n", result);
	
	
	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "0:/"); /* 1: ��ʾ�̷� */
	if (result != FR_OK)
	{
		printf("�򿪸�Ŀ¼ʧ�� �����˳��ú�����(%d)\r\n", result);
		//return;
	}else
		  printf("�򿪸�Ŀ¼�ɹ�������\r\n");

	/* ��ȡ��ǰ�ļ����µ��ļ���Ŀ¼ */
	FileInf.lfname = lfname;
	FileInf.lfsize = 256;

	printf("����        |  �ļ���С | ���ļ��� | ���ļ���\r\n");
	for (cnt = 0; ;cnt++)
	{
		result = f_readdir(&DirInf,&FileInf); 		/* ��ȡĿ¼��������Զ����� */
		if (result != FR_OK || FileInf.fname[0] == 0)
		{
			break;
		}

		if (FileInf.fname[0] == '.')
		{
			continue;
		}

		/* �ж����ļ�������Ŀ¼ */
		if (FileInf.fattrib & AM_DIR)
		{
			printf("(0x%02d)Ŀ¼  ", FileInf.fattrib);
		}
		else
		{
			printf("(0x%02d)�ļ�  ", FileInf.fattrib);
		}

		/* ��ӡ�ļ���С, ���4G */
		printf(" %10d", FileInf.fsize);

		printf("  %s |", FileInf.fname);	/* ���ļ��� */

		printf("  %s\r\n", (char *)FileInf.lfname);	/* ���ļ��� */
	}

	/* ж���ļ�ϵͳ */
	f_mount(NULL, "0:", 0);
}


static void CreateNewFile(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;
	uint32_t bw;
	
 	/* �����ļ�ϵͳ */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive */
	
	f_mount(NULL, "0:", 0);
	
	
	result = f_mount(&myFatFs, "0:", 0);
  if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� �����˳��ú�����(%d)\r\n", result);
		return;
	}else{
		printf("�����ļ�ϵͳ�ɹ���(%d)\r\n", result);
	}
	
	
	/* ���ļ� */
	result = f_open(&file, "0:/armfly.txt", FA_CREATE_ALWAYS | FA_WRITE);

	/* дһ������ */
	//result = f_write(&file, "FatFS Write Demo \r\n www.armfly.com1234567890 \r\n", 44, &bw);
	result = f_write(&file, "������Զ�����ҵİְֺ����裬�������塣13184009859", 50, &bw);
	if (result == FR_OK)
	{
		printf("armfly.txt �ļ�д��ɹ�\r\n");
	}
	else
	{
		printf("armfly.txt �ļ�д��ʧ��\r\n");
	}

	/* �ر��ļ�*/
	f_close(&file);

	/* ж���ļ�ϵͳ */
	f_mount(NULL, "0:", 0);
}


 void CreateNewFileChinese(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	FRESULT result;
	FATFS fs;
	FIL file;
	DIR DirInf;
	uint32_t bw;
	
 	/* �����ļ�ϵͳ */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive */
	
	f_mount(NULL, "0:", 0);
	
	
	result = f_mount(&myFatFs, "0:", 0);
  if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� �����˳��ú�����(%d)\r\n", result);
		return;
	}else{
		printf("�����ļ�ϵͳ�ɹ���(%d)\r\n", result);
	}
	
	
	/*
	result = f_mkfs("0:",0,512);	
	if (result == FR_OK)
	{
		printf("Start Format(Low Level) ......\r\n");
		printf("���̵ͼ���ʽ���Ѿ���ɣ� f_mkfs Ok\r\n");
	}else
		printf("���̵ͼ���ʽ��ʧ�ܣ�");
	*/
	
	
	
	/* ���ļ� */
	result = f_open(&file, "0:�ְֺ�����.txt", FA_CREATE_ALWAYS | FA_WRITE);

	/* дһ������ */
	result = f_write(&file, "�������ְֺ����� \r\n", 44, &bw);
	if (result == FR_OK)
	{
		printf("armfly.txt �ļ�д��ɹ�\r\n");
	}
	else
	{
		printf("armfly.txt �ļ�д��ʧ��\r\n");
	}

	/* �ر��ļ�*/
	f_close(&file);

	/* ж���ļ�ϵͳ */
	f_mount(NULL, "0:", 0);
}


/*
*********************************************************************************************************
*	�� �� ��: ReadFileData
*	����˵��: ��ȡ�ļ�srcfile.txtǰ128���ַ�������ӡ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void ReadFileData(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	FRESULT   result;
	DIR DirInf;
	uint32_t bw;
	

 	/* �����ļ�ϵͳ */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive *///ԭ��Ϊ&fs�����޸�Ϊ&fsrc  added by sjw
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ��(%d)\r\n", result);
	}else
		  printf("�����ļ�ϵͳ�ɹ�������\r\n");

	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "0:/"); /* 1: ��ʾ�̷� */
	if (result != FR_OK)
	{
		printf("�򿪸�Ŀ¼ʧ��(%d)\r\n", result);
		return;
	}else
	  printf("�򿪸�Ŀ¼�ɹ�������\r\n");

	
	/* ���ļ� */
	//result = f_open(&fsrc, "1:/srcfile.txt", FA_OPEN_EXISTING | FA_READ);
	result = f_open(&fsrc, "0:/armfly.txt", FA_OPEN_EXISTING | FA_READ);
	if (result !=  FR_OK)
	{
		printf("Don't Find File:  armfly.txt\r\n");
		return;
	}else
	    printf("���ļ�armfly.txt�ɹ�������\r\n");
	

	/* ��ȡ�ļ� */
	result = f_read(&fsrc, &readBuf, sizeof(readBuf) - 1, &bw);
	if (bw > 0)
	{
		readBuf[bw] = 0;
		printf("\r\n armfly.txt �ļ����� : \r\n %s\r\n", readBuf);
	}
	else
	{
		printf("\r\n armfly.txt.txt �ļ����� : \r\n");
	}

	/* �ر��ļ�*/
	f_close(&fsrc);

	/* ж���ļ�ϵͳ */
	f_mount(NULL, "0:", 0);
}

/*
*********************************************************************************************************
*	�� �� ��: CreateDir
*	����˵��: ��SD����Ŀ¼����Dir1��Dir2Ŀ¼����Dir1Ŀ¼�´�����Ŀ¼Dir1_1
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void CreateDir(void)
{
	FRESULT   result;	
	FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	

 	/* �����ļ�ϵͳ */
	result = f_mount(&myFatFs,"0:", 0);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}
  //result =f_mkfs("1:/Dir",0,512);
	//if (f_opendir(&dirs, path) == FR_OK){                /* �򿪸�Ŀ¼ */	

	/* ����Ŀ¼/Dir1 */
	result = f_mkdir("0:/Dir1");
	// ���ΪPR_NO_FILESYSTEM  ������û����Ч��FAT��
	
	
	if (result == FR_OK)
	{
		printf("f_mkdir Dir1 Ok\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir1 Ŀ¼�Ѿ�����(%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir1 ʧ�� (%d)\r\n", result);
		return;
	}

	/* ����Ŀ¼/Dir2 */
	result = f_mkdir("0:/Dir2");
	if (result == FR_OK)
	{
		printf("f_mkdir Dir2 Ok\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir2 Ŀ¼�Ѿ�����(%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir2 ʧ�� (%d)\r\n", result);
		return;
	}

	/* ������Ŀ¼ /Dir1/Dir1_1	   ע�⣺������Ŀ¼Dir1_1ʱ�������ȴ�����Dir1 */
	result = f_mkdir("0:/Dir1/Dir1_1"); /* */
	if (result == FR_OK)
	{
		printf("f_mkdir Dir1_1 �ɹ�\r\n");
	}
	else if (result == FR_EXIST)
	{
		printf("Dir1_1 Ŀ¼�Ѿ����� (%d)\r\n", result);
	}
	else
	{
		printf("f_mkdir Dir1_1 ʧ�� (%d)\r\n", result);
		return;
	}

	/* ж���ļ�ϵͳ */
	f_mount(NULL, "0:", 0);
}

/*
*********************************************************************************************************
*	�� �� ��: DeleteDirFile
*	����˵��: ɾ��SD����Ŀ¼�µ� armfly.txt �ļ��� Dir1��Dir2 Ŀ¼
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DeleteDirFile(void)
{
	FRESULT   result;
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
 FATFS 		myFatFs;            			// Work area (file system object) for logical drive 
	char FileName[13];
	uint8_t i;

 	/* �����ļ�ϵͳ */
	result = f_mount(&myFatFs,"0:", 0);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	#if 0
	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "0:/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK)
	{
		printf("�򿪸�Ŀ¼ʧ��(%d)\r\n", result);
		return;
	}
	#endif

	/* ɾ��Ŀ¼/Dir1 ����Ϊ������Ŀ¼�ǿգ�������Ŀ¼)���������ɾ����ʧ�ܡ�*/
	result = f_unlink("0:/Dir1");
	if (result == FR_OK)
	{
		printf("ɾ��Ŀ¼Dir1�ɹ�\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("û�з����ļ���Ŀ¼ :%s\r\n", "/Dir1");
	}
	else
	{
		printf("ɾ��Dir1ʧ��(������� = %d) �ļ�ֻ����Ŀ¼�ǿ�\r\n", result);
	}

	/* ��ɾ��Ŀ¼/Dir1/Dir1_1 */
	result = f_unlink("0:/Dir1/Dir1_1");
	if (result == FR_OK)
	{
		printf("ɾ����Ŀ¼/Dir1/Dir1_1�ɹ�\r\n");
	}
	else if ((result == FR_NO_FILE) || (result == FR_NO_PATH))
	{
		printf("û�з����ļ���Ŀ¼ :%s\r\n", "/Dir1/Dir1_1");
	}
	else
	{
		printf("ɾ����Ŀ¼/Dir1/Dir1_1ʧ��(������� = %d) �ļ�ֻ����Ŀ¼�ǿ�\r\n", result);
	}

	/* ��ɾ��Ŀ¼/Dir1 */
	result = f_unlink("0:/Dir1");
	if (result == FR_OK)
	{
		printf("ɾ��Ŀ¼Dir1�ɹ�\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("û�з����ļ���Ŀ¼ :%s\r\n", "/Dir1");
	}
	else
	{
		printf("ɾ��Dir1ʧ��(������� = %d) �ļ�ֻ����Ŀ¼�ǿ�\r\n", result);
	}

	/* ɾ��Ŀ¼/Dir2 */
	result = f_unlink("0:/Dir2");
	if (result == FR_OK)
	{
		printf("ɾ��Ŀ¼ Dir2 �ɹ�\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("û�з����ļ���Ŀ¼ :%s\r\n", "/Dir2");
	}
	else
	{
		printf("ɾ��Dir2 ʧ��(������� = %d) �ļ�ֻ����Ŀ¼�ǿ�\r\n", result);
	}

	/* ɾ���ļ� armfly.txt */
	result = f_unlink("0:/srcfile.txt");
	if (result == FR_OK)
	{
		printf("ɾ���ļ� srcfile.txt �ɹ�\r\n");
	}
	else if (result == FR_NO_FILE)
	{
		printf("û�з����ļ���Ŀ¼ :%s\r\n", "srcfile.txt");
	}
	else
	{
		printf("ɾ��srcfile.txtʧ��(������� = %d) �ļ�ֻ����Ŀ¼�ǿ�\r\n", result);
	}

	/* ɾ���ļ� speed1.txt */
	for (i = 0; i < 20; i++)
	{
		sprintf(FileName, "0:/Speed%02d.txt", i);		/* ÿд1�Σ���ŵ��� */
		result = f_unlink(FileName);
		if (result == FR_OK)
		{
			printf("ɾ���ļ�%s�ɹ�\r\n", FileName);
		}
		else if (result == FR_NO_FILE)
		{
			printf("û�з����ļ�:%s\r\n", FileName);
		}
		else
		{
			printf("ɾ��%s�ļ�ʧ��(������� = %d) �ļ�ֻ����Ŀ¼�ǿ�\r\n", FileName, result);
		}
	}

	/* ж���ļ�ϵͳ */
	f_mount(NULL, "0:", 0);
}

/*
*********************************************************************************************************
*	�� �� ��: WriteFileTest
*	����˵��: �����ļ���д�ٶ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void WriteFileTest(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
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

  	/* �����ļ�ϵͳ */
	result = f_mount(&myFatFs, "0:", 0);			/* Mount a logical drive */
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%d)\r\n", result);
	}

	/* �򿪸��ļ��� */
	result = f_opendir(&DirInf, "0:/"); /* ���������������ӵ�ǰĿ¼��ʼ */
	if (result != FR_OK)
	{
		printf("�򿪸�Ŀ¼ʧ�� (%d)\r\n", result);
		return;
	}

	/* ���ļ� */
	sprintf(TestFileName, "0:/Speed%02d.txt", s_ucTestSn++);		/* ÿд1�Σ���ŵ��� */
	result = f_open(&fsrc, TestFileName, FA_CREATE_ALWAYS | FA_WRITE);

	/* дһ������ */
	printf("��ʼд�ļ�%s %dKB ...\r\n", TestFileName, TEST_FILE_LEN / 1024);
	runtime1 = bsp_GetRunTime();	/* ��ȡϵͳ����ʱ�� */
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
			printf("%s�ļ�дʧ��\r\n", TestFileName);
			break;
		}
	}
	runtime2 = bsp_GetRunTime();	/* ��ȡϵͳ����ʱ�� */

	if (err == 0)
	{
		timelen = (runtime2 - runtime1);
		printf("\r\n  д��ʱ : %dms   ƽ��д�ٶ� : %dB/S (%dKB/S)\r\n",
			 timelen,
			(TEST_FILE_LEN * 1000) / timelen,
			((TEST_FILE_LEN / 1024) * 1000) / timelen);
	}

	f_close(&fsrc);		/* �ر��ļ�*/


	/* ��ʼ���ļ����� */
	result = f_open(&fsrc, TestFileName, FA_OPEN_EXISTING | FA_READ);
	if (result !=  FR_OK)
	{
		printf("û���ҵ��ļ�: %s\r\n", TestFileName);
		return;
	}

	printf("��ʼ���ļ� %dKB ...\r\n", TEST_FILE_LEN / 1024);
	runtime1 = bsp_GetRunTime();	/* ��ȡϵͳ����ʱ�� */
	for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
	{
		result = f_read(&fsrc, g_TestBuf, sizeof(g_TestBuf), &bw);
		if (result == FR_OK)
		{
			if (((i + 1) % 8) == 0)
			{
				printf(".");
			}

			/* �Ƚ�д��������Ƿ���ȷ�������ᵼ�¶����ٶȽ�����͵� 3.5MBytes/S */
			for (k = 0; k < sizeof(g_TestBuf); k++)
			{
				if (g_TestBuf[k] != (k / 512) + '0')
				{
				  	err = 1;
					printf("Speed1.txt �ļ����ɹ����������ݳ���\r\n");
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
			printf("Speed1.txt �ļ���ʧ��\r\n");
			break;
		}
	}
	runtime2 = bsp_GetRunTime();	/* ��ȡϵͳ����ʱ�� */

	if (err == 0)
	{
		timelen = (runtime2 - runtime1);
		printf("\r\n  ����ʱ : %dms   ƽ�����ٶ� : %dB/S (%dKB/S)\r\n", timelen,
			(TEST_FILE_LEN * 1000) / timelen, ((TEST_FILE_LEN / 1024) * 1000) / timelen);
	}

	/* �ر��ļ�*/
	f_close(&fsrc);

	/* ж���ļ�ϵͳ */
	f_mount(NULL, "0:", 0);
}




void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
}



/*
*********************************************************************************************************
*	�� �� ��: bsp_GetRunTime
*	����˵��: ��ȡCPU����ʱ�䣬��λ1ms������Ա�ʾ 24.85�죬�����Ĳ�Ʒ��������ʱ�䳬�������������뿼���������
*	��    ��:  ��
*	�� �� ֵ: CPU����ʱ�䣬��λ1ms
*********************************************************************************************************
*/
int32_t bsp_GetRunTime(void)
{
	int32_t runtime;

	DISABLE_INT();  	/* ���ж� */

	runtime = g_iRunTime;	/* ���������Systick�ж��б���д�������Ҫ���жϽ��б��� */

	ENABLE_INT();  		/* ���ж� */

	return runtime;
}



/*
*********************************************************
* �������ܣ���������ECC���Գ���				
* �����������
* �����������
* ����ֵ  ����
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

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/




FATFS Fatfs_test;
void FatfsTest()
{
	 //FATFS Fatfs_test;//�����ȫ��
	 FIL fil;
	 UINT nWriteLen = 0;
	 UINT nReadLen = 0;
	 unsigned char buf[64] = {0};
	 unsigned char buf_write[] = "1234567890";
	 int res = 0;


	 res = f_mount(&Fatfs_test, "0:", 0);//f_mount(0, &Fatfs_test);
	 
	// res = f_mkfs("1:",0,256*4096);// 1MB��С ��һ��������Ҫ��ʽ������
	// return;
	 
	

	 res = f_open(&fil, "1:/testfile.txt", FA_CREATE_NEW | FA_WRITE);
	 if(res == FR_OK)
	 {
			res = f_write(&fil,buf_write,strlen(buf_write),&nWriteLen);
			f_close(&fil);
	 }else{
			if(res == FR_EXIST)
			{
			 printf("�ļ�����\r\n");
			}else{
			 printf("�ļ�����ʧ��,res:%d\r\n",res);
			}
	 }
	 
	 res = f_open(&fil, "1:/testfile.txt", FA_OPEN_EXISTING | FA_READ);
	 printf("res:%d\r\n",res);
	 for(;;)
	 {
			res = f_read(&fil,buf,sizeof(buf),&nReadLen);
			printf("res:%d,nReadLen:%d\r\n",res,nReadLen);  
			if(res||nReadLen == 0)/*������߶����ļ�β*/
			 break;
	 }
	 f_close(&fil);
	  f_mount(NULL,"0:", 0);
	 

}


void DemoDis512DataInNand(uint8_t *psector)
{
	OS_CPU_SR  cpu_sr;
	uint16_t i,j;
	uint32_t sector;//��0��131072ҳ!!!
	
	
	//FSMC_NAND_ReadSmallPage(buff, sector, count);
	
	/*
	  ͨ�������ҵõ����½��ۣ�(�ر���Ҫ����ĵ�ַ�Ǵ�0��ʼ��4095��������Ե�ҳ�Ǵ�0��ʼ��31������������
	1.����Ҫд���2013�����ڵĵ�31ҳ���ݣ�
	  ��ô����ҳ�ĵ�ַ�ǣ�2013*32p+31
	
		Ҫд������2013�����ڵĵ�1ҳ���ݣ���ô����ʾ�ÿ�Ϊbadblock
	*/
	sector=(uint32_t)(psector[4]<<24)+(uint32_t)(psector[3]<<16)+(uint32_t)(psector[2]<<8)+psector[1];
	
	
	
	for(i=0;i<NAND_PAGE_SIZE;i++){
	   TestWriteBuf [i]=00;
		 TestReadBuf[i]=0x5a;
	}
	
	printf("***********************��ҳ�е�512�ֽڵ��������£�**********************\r\n");
	
	
	
	
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
��������������������������������
��Ȩ����������ΪCSDN������hxl5955����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/hxl5955/article/details/53322944

*/


/*
*********************************************************************************************************
*	�� �� ��: FileFormat
*	����˵��: �ļ�ϵͳ��ʽ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void FileFormat(void)
{
	/* ������ʹ�õľֲ�����ռ�ý϶࣬���޸������ļ�����֤��ջ�ռ乻�� */
	FRESULT result;
	FATFS fs;

	/* �����ļ�ϵͳ */
	result = f_mount(&fs, "0:", 0);	
	if (result != FR_OK)
	{
		printf("�����ļ�ϵͳʧ�� (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("�����ļ�ϵͳ�ɹ� (%s)\r\n", FR_Table[result]);
	}
	
	/* ��һ��ʹ�ñ�����и�ʽ�� */
	result = f_mkfs("0:",0,0);
	if (result != FR_OK)
	{
		printf("��ʽ��ʧ�� (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("��ʽ���ɹ� (%s)\r\n", FR_Table[result]);
	}

	/* ж���ļ�ϵͳ */
	result  = f_mount(NULL, "0:", 0);
	if (result != FR_OK)
	{
		printf("ж���ļ�ϵͳʧ�� (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("ж���ļ�ϵͳ�ɹ� (%s)\r\n", FR_Table[result]);
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