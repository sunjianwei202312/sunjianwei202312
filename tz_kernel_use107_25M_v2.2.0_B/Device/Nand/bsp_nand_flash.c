/*

https://blog.csdn.net/ivy_reny/article/details/72190085
NandFlash ECC У���㷨ԭ����ʵ��


https://www.elecfans.com/emb/danpianji/20171201590963_a.html
����NAND Flash������ת������ - ȫ��    NFTL�������

*********************************************************************************************************
*
*	ģ������ : NAND Flash����ģ��
*	�ļ����� : bsp_nand.c
*	��    �� : V1.0
*	˵    �� : �ṩNAND Flash (HY27UF081G2A�� 8bit 128K�ֽ� ��ҳ)�ĵײ�ӿں�������������ԭ����
             �ṩNAND Flash (K9F1208U0B �� 8bit 16K�ֽ� Сҳ)�ĵײ�ӿں�����added by sjw
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2013-02-01  armfly  ��ʽ����
*		V1.1    2014-05-02  armfly  ����512MB�ͺ�: H27U4G8F2DTR,
*					(1) ���� NAND_ReadONFI() ����;
*					(2) ���� NAND_ReadParamPage() ����;
*					(3) ��� NAND_IsFreeBlock(uint32_t _ulBlockNo) ������BUG��
*					(4) ��� FSMC_NAND_PageCopyBack() �� FSMC_NAND_PageCopyBackEx()�� A18������ͬ��BUG
*					(5) �޸� NAND_FindFreeBlock(), �����βΣ�����������ż�����
*					(6) �޸� ��ӡ����ĺ��������ӱ�ʶ 1 ��ʾ���ÿ� 0 ��ʾ���п�
*					(7) NAND_MarkUsedBlock() ���õĵط������ββ��ԡ� ulPhyPageNo / NAND_BLOCK_SIZE
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/


/***************************************************************
ת�أ���ΪSTM32������̳�֮ʮ������NAND FLASH
http://t.zoukankan.com/wwjdwy-p-4664373.html




  added  by sjw     
    �� �� ����NAND FLASH����
    ��    ˾��
    ��    �ߣ�
	�� �� �ţ�
    �������ڣ�
    �޸����ڣ�  
    ���뻷���� KEIL FOR ARM
    Ӳ��ƽ̨��  K9F1G08U0A��ҳNAND  K9F1208СҳNAND 
    ���������� ������д������������    
***************************************************************/
#include "includes.h"
#include "bsp_nand_flash.h"
#include "hw_config.h"//������˺궨��ŵ���48�У���ôNAND_NWAIT_PORT��NAND_NWAIT_PIN��ʾû�ж��壬����Ų������40�У�������⣡��added by sjw

static NAND_IDTypeDef   *NAND_ID_SJW;
extern uint16_t  TestCount;

extern INT32U  BigOrSmallValue;
extern INT32U  *pBigOrSmallValue;

void DemoTestBigOrSmall(uint8_t *psector);

 void DemoTestDisFatfsHex(uint8_t *psector);

void FlashLoadBadBlockTable(void);

static uint32_t FlashBadBlockTable[2][FLASH_BAD_BLOCKS_REMAP+1]; //����������ı��

static uint32_t FlashBadBlocksCount;  //�ж��ٸ�����
static uint8_t FlashRemapBlockStatus[FLASH_BAD_BLOCKS_REMAP+1]; //������Ӱ���õĿ��״��
static uint32_t FlashLastAccessAddr; //���һ�η��ʹ��ĵ�ַ





//Ѫ�Ľ�ѵ��ԭ���������������ڡ�H�и������ˣ�
//���������ʱ����ʾ�������ļ�mass_mal.c bsp_nand_flash.c  demo_nand_fatfs.c���г�ͻ��������Ų��c�ļ��н�����⣡��
uint16_t s_usValidDataBlockCount;	/* ��Ч�����ݿ���� ԭ��Ϊstatic��������files�г���s_usValidDataBlockCount=0������������޸�Ϊȫ���������������⣡��*/
uint16_t s_usLUT[NAND_BLOCK_COUNT];/*ԭ��Ϊstatic��������files�г���s_usLUTԪ��Ϊ0�����*/
uint16_t usGoodBlockCount;
uint8_t s_ucTempBuf[NAND_PAGE_SIZE];	
	
	
//static uint8_t s_ucTempBuf[NAND_PAGE_SIZE];	/* �󻺳�����2112�ֽ�. ���ڶ����Ƚ�     С��������512+16�ֽ�.*/

/* Private variables ---------------------------------------------------------*/
uint32_t FlashCurrentWriteSectorAddr; //��ǰд��������ַ
uint32_t FlashCurrentReadSectorAddr;  //��ǰ����������ַ
uint32_t FlashNeedWriteBack;          //��Ҫ��д�ı�־
uint8_t PushSpearArea[512+16];

#define TEST_BLOCK  (3999)

uint32_t NAND_VALID_ADDRESS;

uint8_t OOBData[16];
uint32_t pageRawNo;
uint16_t addrInSpare,dataCount;


void   SEE_FSMC_NAND_ID(void);

void FSMC_NAND_ReadID(NAND_IDTypeDef* NAND_ID);

//#define WRITE_PAGE_VERIFY_EN	/* д page ����ʱУ�� ���ڵ��Խ׶���ʱ����Ҫ�򿨣�added by sjw */



/*
	�����IAR��KEIL�ı༭�����Ķ����뽫�༭������������Ϊ�����壨9��/��ţ���������TAB����Ϊ4��
	���򣬷��򴦳��ֲ���������⡣

	�������Ƶĵط���
	��1���ڲ���NAND Flashʱ�����������һ����ѭ�������Ӳ�������쳣���������������
 		while( GPIO_ReadInputDataBit(NAND_NWAIT_PORT, NAND_NWAIT_PIN) == 0 )

 	��2��û������ECCУ�鹦�ܡ�ECC���Լ��1����2��bit�������ֻ��1��bit����������޸����bit�����
 		����2��bit��������ܼ�ⲻ����

 	��3������д�ļ�����ʱ���ᵼ���ؽ�LUT��Ŀǰ���ؽ�LUT�Ĵ���ִ��Ч�ʻ������ߣ��д����ơ�

	��Ӳ��˵����
	���������������õ�NAND FlahsΪ����ʿ��HY27UF081G2A,  439�������Ϊ H27U4G8F2DTR
	��1��NAND Flash��Ƭѡ�ź����ӵ�CPU��FSMC_NCE2���������NAND Flash�ĵ�ַ�ռ�Ϊ 0x70000000����CPU������
		�ֲ��FSMC�½�)
	��2����FSMC�������ж�������豸����TFT��SRAM��CH374T��NOR������˱���ȷ�����������豸��Ƭѡ���ڽ�ֹ
		״̬�����򽫳������߳�ͻ���� ���μ����ļ���ʼ��FSMC GPIO�ĺ�����


	��NAND Flash �ṹ���塿
     ��������16x4�ֽڣ�ÿpage 2048�ֽڣ�ÿ512�ֽ�һ��������ÿ��������Ӧ16�Լ��ı�������

	 ÿ��PAGE���߼��ṹ��ǰ��512Bx4����������������16Bx4�Ǳ�����
	��������������������������������������������������������������������������������������������������������������������������������
	�� Main area  ���� Main area  ���� Main area  ����Main area   ���� Spare area ���� Spare area ���� Spare area ����Spare area  ��
	��            ����            ����            ����            ����            ����            ����            ����            ��
	��   512B     ����    512B    ����    512B    ����    512B    ����    16B     ����     16B    ����     16B    ����    16B     ��
	��������������������������������������������������������������������������������������������������������������������������������

	 ÿ16B�ı��������߼��ṹ����:(�����Ƽ���׼��
	������������������������������������������������������������������������������������������������������������������������������������������������������������
	��  BI  ����RESER ����LSN0����LSN1����LSN2����RESER ����RESER ����RESER ����ECC0����ECC1����ECC2����ECC0����S-ECC1����S-ECC0����RESER ����RESER ����RESER ��
	��      ���� VED  ����    ����    ����    ���� VED  ���� VED  ���� VED  ����    ����    ����    ����    ����      ����      ���� VED  ���� VED  ���� VED  ��
	������������������������������������������������������������������������������������������������������������������������������������������������������������

	K9F1G08U0A �� HY27UF081G2A �Ǽ��ݵġ�оƬ����ʱ�����̱�֤оƬ�ĵ�1�����Ǻÿ顣����ǻ��飬���ڸÿ�ĵ�1��PAGE�ĵ�1���ֽ�
	���ߵ�2��PAGE������1��PAGE�����޷����Ϊ0xFFʱ���ĵ�1���ֽ�д���0xFFֵ��������ֵ������ģ����ֱ���ж��Ƿ����0xFF���ɡ�

	ע�⣺������Щ����˵NAND Flash���̵�Ĭ�������ǽ������Ƕ��ڵ�1��PAGE�ĵ�6���ֽڴ������˵���Ǵ��󡣻������ڵ�6���ֽڽ���Բ���С������512�ֽڣ���NAND Flash
	���������е�NAND Flash���������׼������ڸ���NAND Flashʱ������ϸ�Ķ�оƬ�������ֲᡣ


	Ϊ�˱�����NAND Flash ����ֲFat�ļ�ϵͳ�����Ƕ�16B�ı������������·��䷽��:
	������������������������������������������������������������������������������������������������������������������������������������
	�� BI ����USED����LBN0����LBN1����ECC0����ECC1����ECC2����ECC3����ECC4����ECC5����S-ECC1����S-ECC0����RSVD����RSVD����RSVD����RSVD��
	��    ����    ����    ����    ����    ����    ����    ����    ����    ����    ����      ����      ����    ����    ����    ����    ��
	������������������������������������������������������������������������������������������������������������������������������������
    - BI : �����־(Bad Block Identifier)��ÿ��BLOCK�ĵ�1��PAGE���ߵ�2��PAGE�ĵ�1���ֽ�ָʾ�ÿ��Ƿ񻵿顣0xFF��ʾ�ÿ飬����0xFF��ʾ���顣
    - USED : �ÿ�ʹ�ñ�־��0xFF��ʾ���п飻0xF0��ʾ���ÿ顣
    - LBN0 LBN1 : �߼����(Logic Block No) ����0��ʼ���롣ֻ��ÿ��BLOCK�ĵ�1��PAGE��Ч������PAGE���ֶι̶�Ϊ0xFF FF
    - ECC0 ~ ECC5 : 512B����������ECCУ�� �����������ṩECC�㷨��256�ֽڶ�Ӧ3���ֽڵ�ECC)
    - S-ECC1 S-ECC0 : LSN0��LSN2��ECCУ��
    - RSVD : �����ֽڣ�Reserved

	��������� & ĥ��ƽ�⡿
	(1) �ڲ�ȫ������s_usLUT[]�����򱣴������š������������߼���ĵ�ַӳ�䡣
	(2) ��ʽ��ʱ����98%�ĺÿ����������ݴ洢��ʣ���2%���ڱ������������滻����
	(3) д������512B)ʱ�������������Ϊ�գ���ֱ��д�룬���ٲ���Ҫ�Ŀ������������Ч���NAND Flash�������Ͷ�д���ܡ�
	(4) д����ʱ������������ݲ�Ϊ�գ����ĩβ��ʼ����һ�����п��滻���ɿ飬�滻����д������ɺ󣬽��ɿ����������עΪ���У�֮���ؽ�LUT��
	(5) �鸴��ʱ���������NAND FlashӲ����Copy-Back���ܣ������Դҳ���ڴ���д��Ŀ��ҳ��������������߶�дЧ�ʡ�
	(6) ĥ��ƽ�⻹����ȱ�ݣ�Ч�����á�ECCУ����δʵ�֡�

*/

/* ����NAND Flash�������ַ���������Ӳ�������� */



/* �������NAND Flash�õ�3���� */
#define NAND_CMD_AREA		  *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA)
#define NAND_ADDR_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA)
#define NAND_DATA_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA)



typedef struct 
{
  uint16_t Zone;
  uint16_t Block;
  uint16_t Page;
} 
NAND_ADDRESS;

#define ROW_ADDRESS (Address.Page + (Address.Block + (Address.Zone * NAND_ZONE_SIZE)) * NAND_BLOCK_SIZE)


/* �߼����ӳ����ÿ�������2%���ڱ��������������ά������1024�� LUT = Look Up Table */


/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: ����FSMC��GPIO����NAND Flash�ӿڡ�������������ڶ�дnand flashǰ������һ�Ρ�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

static NAND_ADDRESS_T WriteReadAddr;//"static"is added by sjw for see...

 void FSMC_NAND_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NANDInitTypeDef  FSMC_NANDInitStructure;
	FSMC_NAND_PCCARDTimingInitTypeDef  p;
	


	/*--NAND Flash GPIOs ����  ------
		PD6/FSMC_INT2	(�������ò�ѯ��ʽ��æ���˿�����Ϊ��ͨGPIO���빦��ʹ��)
	 ʹ�� GPIO ʱ�� 
	 FSMC����ʹ�õ�GPIO��ʱ��ʹ��
	*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC  |
	                       RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |RCC_APB2Periph_AFIO , ENABLE);

	

	/* ʹ�� FSMC ʱ�� */
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	

	
	/*FSMC CLE, ALE, D0->D3, NOE, NWE and NCE2��ʼ�������츴�����*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14| GPIO_Pin_15|                //is D0   D1 
																GPIO_Pin_0 | GPIO_Pin_1 |                 //is D2   D3
																GPIO_Pin_11| GPIO_Pin_12|                 //is CLE, ALE 
                               	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;    //is NOE  NWR  NE_NCE2              
																                  
															    
	                              
                                                              
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//���ô�ָ���ô��ʾ����Ϊ4���������GPIO_Mode_Out_PP ����ʾ1024�����飡
  GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
	
	
	 /*FSMC������FSMC_D[4:7]��ʼ�������츴�����   ����GPIOE*/ 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7 | GPIO_Pin_8 |   //is  D4  D5
															 GPIO_Pin_9 | GPIO_Pin_10;   //is  D6  D7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
	
	
	/*FSMC NWAIT��ʼ������������  ����GPIOD, PD6��Ϊæ��Ϣ������Ϊ����*/ 
	//PD6/FSMC_INT2	(�������ò�ѯ��ʽ��æ���˿�����Ϊ��ͨGPIO���빦��ʹ��)
  GPIO_InitStructure.GPIO_Pin = NAND_NWAIT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	 /*--------------FSMC ���� �洢����������------------------------------*//* ���� FSMC ʱ�� 2014-06-29 ����ʱ�� */
  
	
	/*
		Defines the number of HCLK cycles to setup address before the command assertion for NAND-Flash
		read or write access  to common/Attribute or I/O memory space (depending on the memory space
		timing to be configured).This parameter can be a value between 0 and 0xFF.
	*/
  	//p.FSMC_SetupTime = 0x01;  ---- 01 err, 02 ok
  	p.FSMC_SetupTime = 0x2;//����ʱ��



	/*
		Defines the minimum number of HCLK cycles to assert the command for NAND-Flash read or write
		access to common/Attribute or I/O memory space (depending on the memory space timing to be
		configured). This parameter can be a number between 0x00 and 0xFF
	*/
	//p.FSMC_WaitSetupTime = 0x03; ---- 03 err;  05 ok
	 p.FSMC_WaitSetupTime = 0x5;//�ȴ�ʱ��



	/*
		Defines the number of HCLK clock cycles to hold address (and data for write access) after the
		command deassertion for NAND-Flash read or write access to common/Attribute or I/O memory space
		 (depending on the memory space timing to be configured).
		This parameter can be a number between 0x00 and 0xFF
	*/
	//p.FSMC_HoldSetupTime = 0x02;  --- 02 err  03 ok
	p.FSMC_HoldSetupTime = 0x3;//����ʱ��



	/*
		Defines the number of HCLK clock cycles during which the databus is kept in HiZ after the start
		of a NAND-Flash  write access to common/Attribute or I/O memory space (depending on the memory
		space timing to be configured). This parameter can be a number between 0x00 and 0xFF
	*/
	//p.FSMC_HiZSetupTime = 0x01;
	p.FSMC_HiZSetupTime = 0x1; //���轨��ʱ��
	
	
	
	
	FSMC_NANDInitStructure.FSMC_Bank = FSMC_Bank2_NAND;  					          /* ����FSMC NAND BANK �� */
	FSMC_NANDInitStructure.FSMC_Waitfeature = FSMC_Waitfeature_Enable;		  /* ����ȴ�ʱ��ʹ�� ʹ�ܻ����FSMC�ĵȴ�����*/
	FSMC_NANDInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;	/* ���ݿ�� 8bit */
	FSMC_NANDInitStructure.FSMC_ECC = FSMC_ECC_Enable; 						          /* ECC������;�������ʹ�� */
	FSMC_NANDInitStructure.FSMC_ECCPageSize = FSMC_ECCPageSize_512Bytes;    /* ECC ҳ���С */

	FSMC_NANDInitStructure.FSMC_TCLRSetupTime = 0x01;						            /* CLE�ͺ�RE��֮����ӳ٣�HCLK������ */	
	FSMC_NANDInitStructure.FSMC_TARSetupTime = 0x01;						            /* ALE�ͺ�RE��֮����ӳ٣�HCLK������ */

	FSMC_NANDInitStructure.FSMC_CommonSpaceTimingStruct = &p;				        /* FSMC Common Space Timing */
	FSMC_NANDInitStructure.FSMC_AttributeSpaceTimingStruct = &p;			      /* FSMC Attribute Space Timing */

	FSMC_NANDInit(&FSMC_NANDInitStructure);

	/* FSMC NAND Bank ʹ�� */
	FSMC_NANDCmd(FSMC_Bank2_NAND, ENABLE);	
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_ReadID
*	����˵��: ��NAND Flash��ID��ID�洢���β�ָ���Ľṹ������С�
*	��    ��:  ��
*	�� �� ֵ: 32bit��NAND Flash ID
*********************************************************************************************************
*/
uint32_t NAND_ReadID(void)//is OK!
{
	uint32_t data = 0;

	/* �������� Command to the command area */
	NAND_CMD_AREA = 0x90;/* �������������0x70010000 */   
	NAND_ADDR_AREA = 0x00;//�������ַ00H,Ȼ�����4���ֽڵ����ݼ���K9F1208��ID

	/* ˳���ȡNAND Flash��ID */
	data = *(__IO uint32_t *)(Bank_NAND_ADDR | DATA_AREA);
	data =  ((data << 24) & 0xFF000000) |
			((data << 8 ) & 0x00FF0000) |
			((data >> 8 ) & 0x0000FF00) |
			((data >> 24) & 0x000000FF) ;
	return data;
	
	
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_PageCopyBack
*	����˵��: ��һҳ���ݸ��Ƶ�����һ��ҳ��Դҳ��Ŀ��ҳ���ڵ�block����ͬΪż����ͬΪ��������A18������ͬ��
*	��    ��:  - _ulSrcPageNo: Դҳ��
*             - _ulTarPageNo: Ŀ��ҳ��
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*
*	˵    ���������ֲ��Ƽ�����ҳ����֮ǰ����У��Դҳ��λУ�飬������ܻ����λ���󡣱�����δʵ�֡�
*
*********************************************************************************************************
*/
static uint8_t FSMC_NAND_PageCopyBack(uint32_t _ulSrcPageNo, uint32_t _ulTarPageNo)
{
	uint8_t i;

	if ((_ulSrcPageNo & 0x40) != (_ulTarPageNo & 0x40))
	{
		printf("Error : FSMC_NAND_PageCopyBackEx(src=%d, tar=%d) \r\n", _ulSrcPageNo, _ulTarPageNo);
		return NAND_FAIL;
	}

	NAND_CMD_AREA = NAND_CMD_COPYBACK_A;

	/* ����Դҳ��ַ �� ���� HY27UF081G2A
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20
		��5�ֽڣ� A28  A29  A30  A31  0    0    0    0
	*/
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = _ulSrcPageNo;
	NAND_ADDR_AREA = (_ulSrcPageNo & 0xFF00) >> 8;

	#if NAND_ADDR_5 == 1
		NAND_ADDR_AREA = (_ulSrcPageNo & 0xFF0000) >> 16;
	#endif

	NAND_CMD_AREA = NAND_CMD_COPYBACK_B;

	/* ����ȴ���������������쳣, �˴�Ӧ���жϳ�ʱ */
	for (i = 0; i < 20; i++);
	while( GPIO_ReadInputDataBit(NAND_NWAIT_PORT, NAND_NWAIT_PIN) == 0 );

	NAND_CMD_AREA = NAND_CMD_COPYBACK_C;

	/* ����Ŀ��ҳ��ַ �� ���� HY27UF081G2A
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12    --- A18 ��plane��ַ
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20
		��5�ֽڣ� A28  A29  A30  A31  0    0    0    0

		Source and Destination page in the copy back program sequence must belong to the same device plane ��A18��
		Դ��ַ��Ŀ���ַ�� A18������ͬ
	*/
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = _ulTarPageNo;
	NAND_ADDR_AREA = (_ulTarPageNo & 0xFF00) >> 8;

	#if NAND_ADDR_5 == 1
		NAND_ADDR_AREA = (_ulTarPageNo & 0xFF0000) >> 16;
	#endif

	NAND_CMD_AREA = NAND_CMD_COPYBACK_D;

	/* ������״̬ */
	if (FSMC_NAND_GetStatus() == NAND_READY)
	{
		return NAND_OK;
	}

  printf("Error: FSMC_NAND_PageCopyBack(%d, %d)\r\n", _ulSrcPageNo, _ulTarPageNo);
	return NAND_FAIL;
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_PageCopyBackEx
*	����˵��: ��һҳ���ݸ��Ƶ�����һ��ҳ,������Ŀ��ҳ�еĲ������ݡ�Դҳ��Ŀ��ҳ���ڵ�BLOCK����ͬΪż����ͬΪ������
*	��    ��:  - _ulSrcPageNo: Դҳ��
*             - _ulTarPageNo: Ŀ��ҳ��
*			  - _usOffset: ҳ��ƫ�Ƶ�ַ��pBuf�����ݽ�д�������ַ��ʼ��Ԫ
*			  - _pBuf: ���ݻ�����
*			  - _usSize: ���ݴ�С
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*
*	˵    ���������ֲ��Ƽ�����ҳ����֮ǰ����У��Դҳ��λУ�飬������ܻ����λ���󡣱�����δʵ�֡�
*
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_PageCopyBackEx(uint32_t _ulSrcPageNo, uint32_t _ulTarPageNo, uint8_t *_pBuf, 
	uint16_t _usOffset, uint16_t _usSize)
{
	uint16_t i;

	if ((_ulSrcPageNo & 0x40) != (_ulTarPageNo & 0x40))
	{
		//printf_err("Error A18 not same:  FSMC_NAND_PageCopyBackEx(src=%d, tar=%d) \r\n", _ulSrcPageNo, _ulTarPageNo);
		return NAND_FAIL;
	}

	NAND_CMD_AREA = NAND_CMD_COPYBACK_A;

	/* ����Դҳ��ַ �� ���� HY27UF081G2A
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20
		��5�ֽڣ� A28  A29  A30  A31  0    0    0    0
	*/
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = _ulSrcPageNo;
	NAND_ADDR_AREA = (_ulSrcPageNo & 0xFF00) >> 8;

	#if NAND_ADDR_5 == 1
		NAND_ADDR_AREA = (_ulSrcPageNo & 0xFF0000) >> 16;
	#endif

	NAND_CMD_AREA = NAND_CMD_COPYBACK_B;

	/* ����ȴ���������������쳣, �˴�Ӧ���жϳ�ʱ */
	for (i = 0; i < 20; i++);
	while( GPIO_ReadInputDataBit(NAND_NWAIT_PORT, NAND_NWAIT_PIN) == 0 );

	NAND_CMD_AREA = NAND_CMD_COPYBACK_C;

	/* ����Ŀ��ҳ��ַ �� ���� HY27UF081G2A
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20
		��5�ֽڣ� A28  A29  A30  A31  0    0    0    0
	*/
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = 0;
	NAND_ADDR_AREA = _ulTarPageNo;
	NAND_ADDR_AREA = (_ulTarPageNo & 0xFF00) >> 8;

	#if NAND_ADDR_5 == 1
		NAND_ADDR_AREA = (_ulTarPageNo & 0xFF0000) >> 16;
	#endif

	/* �м����������, Ҳ����ȴ� */

	NAND_CMD_AREA = NAND_CMD_COPYBACK_C;

	NAND_ADDR_AREA = _usOffset;
	NAND_ADDR_AREA = _usOffset >> 8;

	/* �������� */
	for(i = 0; i < _usSize; i++)
	{
		NAND_DATA_AREA = _pBuf[i];
	}

	NAND_CMD_AREA = NAND_CMD_COPYBACK_D;

	/* ������״̬ */
	if (FSMC_NAND_GetStatus() == NAND_READY)
	{
		return NAND_OK;
	}

	printf("Error: FSMC_NAND_PageCopyBackEx(src=%d, tar=%d, offset=%d, size=%d)\r\n",_ulSrcPageNo, _ulTarPageNo, _usOffset, _usSize);
	return NAND_FAIL;
}


//void FSMC_NAND_TestNum100Block(uint16_t block)
//{
//	uint16_t index;
//	
//  uint16_t j;
//  static NAND_IDTypeDef NAND_ID;
//  
//  static uint32_t  ID;
//	uint32_t WriteReadStatus=0;
// 	
//	
//	//��3200ҳ
//	FSMC_NAND_EraseBlock(block);//��3072����(Ҳ���ǵ�98304ҳ��˳��32ҳ֮�������ȫ��������)
//	
//	// Write data to FSMC NOR memory 
//  // Fill the buffer to send 
////  for (index = 0; index < NAND_PAGE_TOTAL_SIZE; index++ )//����д�����ڵ�98304ҳ��д��ģ�
////  {
////     TxBuffer[index] = index;
////  }
////	

////  FSMC_NAND_WritePage(TxBuffer,98304,0, NAND_PAGE_SIZE);//NAND_PAGE_SIZE);
////	printf("%x  \r",TxBuffer[j]);

//	
//	FSMC_NAND_ReadPage(TestMyRxBuffer,block*32,0,  NAND_PAGE_TOTAL_SIZE);//��3072�����Ӧ���ǵ�98304ҳ������������������
//	printf("%x  \r",TestMyRxBuffer[j]);  
//	
//	
//	 
//	 
//	/* 
//	FSMC_NAND_EraseBlock(0);
//  //Write data to FSMC NOR memory  Fill the buffer to send 
//  for (index = 0; index <  NAND_PAGE_TOTAL_SIZE; index++ )
//  {
//     TxBuffer[index] = index;
//  }
//	FSMC_NAND_WritePage(TxBuffer,0,0, NAND_PAGE_TOTAL_SIZE);
//	
//	
//	// NAND memory address to write to 
//  // ��ʼ��Ҫд��NAND��ҳ��ַ  
//  WriteReadAddr.Zone = 0x00;
//  WriteReadAddr.Block = 0x00;
//  WriteReadAddr.Page = 0x00;//��0�����е�9ҳ��ȫ��������added by sjw
////��0�����е�9ҳ��ȫ��������added by sjw
//	
//	*/
//}

void FSMC_NAND_TestWriteoneBlock(uint16_t block,uint8_t action,uint8_t force)
{

  uint16_t j;
  static NAND_IDTypeDef NAND_ID;
  static NAND_ADDRESS_T WriteReadAddr;//"static"is added by sjw for see...
  static uint32_t  ID;
	uint32_t WriteReadStatus=0;
	uint16_t index;
	
	//���Ե��ɿ����ת��Ϊpage��ҳ����ע�ⷶΧ�������ڱ�Ϊuint32_t block2page��ԭ��Ϊuint16_t
	uint32_t block2page=block*32;
	
	
 	if(force)//ǿ�Ʋ��������ǲ�����д���ݣ���
	{
		FSMC_NAND_EraseBlock(block);
		
	}
	else if(action)
  {//ִ�в����������ڲ�ramд���ݣ�added by sjw
		FSMC_NAND_EraseBlock(block);
		
		for (index =0; index < 32; index++ )
		{
				for (j = 0; j < NAND_PAGE_SIZE; j++ )//���ò���OOA  added by sjw
				{
					TestMyTxBuffer[j] = index;
				}
				FSMC_NAND_WritePage(TestMyTxBuffer,block2page+index,0, NAND_PAGE_SIZE);//���ò���OOA  added by sjw
		}
	}
		
		
		
	

	for (index =0; index < 32; index++ )
	{
		for (j = 0; j < NAND_PAGE_TOTAL_SIZE; j++ )//��Ҫ����OOA  added by sjw
		{
			FSMC_NAND_ReadPage(TestMyRxBuffer,block2page+index,0,  NAND_PAGE_TOTAL_SIZE);//��Ҫ����OOA  added by sjw
			if(j%32==0){
				printf("\r\n");
			  printf("%x ",TestMyRxBuffer[j]);
			}else
			  printf("%x ",TestMyRxBuffer[j]);
		}
		printf("****************************  \r");
		
	}
	
	
	
	
}

void FSMC_NAND_TestWriteAndRead(void)//��������4��13�ղ��Գɹ�����added by sjw
{
	
	uint16_t index;
	
  uint16_t j;
	uint32_t WriteReadStatus=0;
 
	
	FSMC_NAND_EraseBlock(TEST_BLOCK);//��x����(Ҳ���ǵ�98304ҳ��˳��32ҳ֮�������ȫ��������)�Ȳ�����֮�����д�룡��
	
	// Write data to FSMC NOR memory  Fill the buffer to send 
  for (index = 0; index < NAND_PAGE_SIZE+16; index++ )//����д�����ڵ�98304ҳ��д��ģ�
  {
     TestMyTxBuffer[index] = index;
  }

	FSMC_NAND_WritePage(TestMyTxBuffer,TEST_BLOCK*32,0, NAND_PAGE_TOTAL_SIZE);//;//��ʾҪд���xҳ,ƫ�Ƶ�ַΪ0��д��528�����ݣ�

  // Read back the written data 
	FSMC_NAND_ReadPage(TestMyRxBuffer,TEST_BLOCK*32,0,  NAND_PAGE_TOTAL_SIZE);//��TEST_BLOCK�����Ӧ���ǵ�158000ҳ������������������
	
	 // Verify the written data 
	for(j = 0; j <  NAND_PAGE_TOTAL_SIZE; j++)
	{
		if(TestMyTxBuffer[j] != TestMyRxBuffer[j])
		{     
			WriteReadStatus++;
		} 
	}
	
	if (WriteReadStatus == 0)
	{     
		
		printf("OK,У��������ȷ��");
	}
	else
	{ 	
		printf("ERROR,У�����ݳ������ݲ����ţ�");   
	}
	
}


/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_WritePage
*	����˵��: дһ��������NandFlashָ��ҳ���ָ��λ�ã�д������ݳ��Ȳ�����һҳ�Ĵ�С��
*	��    ��:   - _pBuffer: ָ�������д���ݵĻ�����
*             - _ulPageNo: ҳ�ţ����е�ҳͳһ���룬��ΧΪ��0 - 131072
*			        - _usAddrInPage : ҳ�ڵ�ַ����ΧΪ��0-x
*             - _usByteCount: д����ֽڸ���
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t FSMC_NAND_WritePage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount)
{
	uint16_t i;

	/* ����ҳд���� */
	NAND_CMD_AREA = NAND_CMD_WRITE0;

	/* ����ҳ�ڵ�ַ �� ���� HY27UF081G2A
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20
		��5�ֽڣ� A28  A29  A30  A31  0    0    0    0
	*/
//	NAND_ADDR_AREA = _usAddrInPage;
//	NAND_ADDR_AREA = _usAddrInPage >> 8;
//	NAND_ADDR_AREA = _ulPageNo;
//	NAND_ADDR_AREA = (_ulPageNo & 0xFF00) >> 8;

//   NAND_ADDR_AREA = _usAddrInPage;
//	 NAND_ADDR_AREA = _ulPageNo;
//	 NAND_ADDR_AREA = (_ulPageNo>>8);
//	 NAND_ADDR_AREA = (_ulPageNo>>16);
	 
	  NAND_ADDR_AREA = _usAddrInPage;
	 	NAND_ADDR_AREA =ADDR_1st_CYCLE(_ulPageNo);
		NAND_ADDR_AREA =ADDR_2nd_CYCLE(_ulPageNo);
		NAND_ADDR_AREA =ADDR_3rd_CYCLE(_ulPageNo);




	#if NAND_ADDR_5 == 1
		NAND_ADDR_AREA = (_ulPageNo & 0xFF0000) >> 16;
	#endif

	/* tADL = 100ns,  Address to Data Loading */
	for (i = 0; i < 20; i++);	/* ��Ҫ���� 100ns */

	/* д���� */
	for(i = 0; i < _usByteCount; i++)
	{
		NAND_DATA_AREA = _pBuffer[i];
	}
	NAND_CMD_AREA = NAND_CMD_WRITE_TRUE1;

	/* WE High to Busy , 100ns */
	for (i = 0; i < 20; i++);	/* ��Ҫ���� 100ns */
	
	
	while( GPIO_ReadInputDataBit(NAND_NWAIT_PORT, NAND_NWAIT_PIN) ==Bit_RESET ); //�ȴ�д���  Ϊ�ͱ�ʾæ
	
	
	
	//������״̬ 
	if (FSMC_NAND_GetStatus() == NAND_READY)
	{
			// �������ݽ���У�� 
		#ifdef WRITE_PAGE_VERIFY_EN
			FSMC_NAND_ReadPage (s_ucTempBuf, _ulPageNo, _usAddrInPage, _usByteCount);
			if (memcmp(s_ucTempBuf,  _pBuffer, _usByteCount) != 0)
			{
    //		  printf_err("Error1: FSMC_NAND_WritePage(page=%d, addr=%d, count=%d)\r\n",
		//			_ulPageNo, _usAddrInPage, _usByteCount);				
				return NAND_FAIL;	
			}			
		#endif		
		return NAND_OK;
	}
	return NAND_FAIL;
}



/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_ReadPage
*	����˵��: ��NandFlashָ��ҳ���ָ��λ�ö�һ�����ݣ����������ݳ��Ȳ�����һҳ�Ĵ�С��
*	��    ��:   - _pBuffer: ָ�������д���ݵĻ�����
*             - _ulPageNo: ҳ�ţ����е�ҳͳһ���룬��ΧΪ��0 - 131072
*			        - _usAddrInPage : ҳ�ڵ�ַ����ΧΪ��0-527/2111           0-527
*             - _usByteCount: �ֽڸ�����  ����� 521+16/2048 + 64��     ����� 512 + 16��added by sjw
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_ReadPage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount)
{
	uint16_t i,index;

    /* ����ҳ������� ��ȡ�ϡ��°벿*/
    NAND_CMD_AREA =NAND_CMD_AREA_A;//0x50   read Spare Field   ������50h�����ڶ�ȡsparefield�����ݡ� NAND_CMD_AREA_A; SJW   is sjw

//	NAND_ADDR_AREA = _usAddrInPage;
//	NAND_ADDR_AREA = _usAddrInPage >> 8;
//	NAND_ADDR_AREA = _ulPageNo;
//	NAND_ADDR_AREA = (_ulPageNo & 0xFF00) >> 8;


   NAND_ADDR_AREA = _usAddrInPage;
	 NAND_ADDR_AREA = _ulPageNo;
	 NAND_ADDR_AREA = (_ulPageNo>>8);
	 NAND_ADDR_AREA = (_ulPageNo>>16);


	#if NAND_ADDR_5 == 1
		NAND_ADDR_AREA = (_ulPageNo & 0xFF0000) >> 16;
	#endif

	
	 /* ����ȴ���������������쳣, �˴�Ӧ���жϳ�ʱ */
	for (i = 0; i < 20; i++);

	while( GPIO_ReadInputDataBit(NAND_NWAIT_PORT, NAND_NWAIT_PIN) == 0);

	/* �����ݵ�������pBuffer */
	for(i = 0; i < _usByteCount; i++)
	{
		_pBuffer[i] = NAND_DATA_AREA;
		
	}
	
	

	return NAND_OK;
}



/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_CompPage
*	����˵��: �Ƚ�����
*	��    ��:  - _pBuffer: ָ��������Ƚϵ����ݻ�����
*            - _ulPageNo: ҳ�ţ����е�ҳͳһ���룬��ΧΪ��0 - x
*			       - _usAddrInPage : ҳ�ڵ�ַ����ΧΪ��0-y
*            - _usByteCount: �ֽڸ�����  ����� 512 + 16��
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ��� ���
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_CompPage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount)
{
	uint16_t i;

    /* ����ҳ������� */
    NAND_CMD_AREA = NAND_CMD_AREA_A;

	/* ����ҳ�ڵ�ַ �� ���� HY27UF081G2A  (128MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20
		��5�ֽڣ� A28  A29  A30  A31  0    0    0    0
	*/
//	NAND_ADDR_AREA = _usAddrInPage;
//	NAND_ADDR_AREA = _usAddrInPage >> 8;
//	NAND_ADDR_AREA = _ulPageNo;
//	NAND_ADDR_AREA = (_ulPageNo & 0xFF00) >> 8;

  
   NAND_ADDR_AREA = _usAddrInPage;
	 NAND_ADDR_AREA = _ulPageNo;
	 NAND_ADDR_AREA = (_ulPageNo>>8);
	 NAND_ADDR_AREA = (_ulPageNo>>16);


	#if NAND_ADDR_5 == 1
		NAND_ADDR_AREA = (_ulPageNo & 0xFF0000) >> 16;
	#endif

	
	
	
	
	
	
	
	
	
	//NAND_CMD_AREA = NAND_CMD_AREA_TRUE1;

	 /* ����ȴ���������������쳣, �˴�Ӧ���жϳ�ʱ */
	for (i = 0; i < 20; i++);//ԭ��Ϊfor (i = 0; i < 20; i++)
	while( GPIO_ReadInputDataBit(NAND_NWAIT_PORT, NAND_NWAIT_PIN) == 0);

	/* �����ݵ�������pBuffer */
	for(i = 0; i < _usByteCount; i++)
	{
		if (_pBuffer[i] != NAND_DATA_AREA)
		{
			return NAND_FAIL;
		}
	}

	return NAND_OK;
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_WriteSpare
*	����˵��: ��1��PAGE��Spare��д������
*	��    ��:   - _pBuffer: ָ�������д���ݵĻ�����
*             - _ulPageNo: ҳ�ţ����е�ҳͳһ���룬��ΧΪ��0 - 4095*32(131072)
*			        - _usAddrInSpare : ҳ�ڱ�������ƫ�Ƶ�ַ����ΧΪ��512-527
*             - _usByteCount: д����ֽڸ���
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_WriteSpare(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInSpare, uint16_t _usByteCount)
{
	if (_usByteCount > NAND_SPARE_AREA_SIZE)
	{
		printf("Error: FSMC_NAND_WriteSpare() length is larger 16 in OOB area! %d\r\n",_usByteCount);
		return NAND_FAIL;
	}

	return FSMC_NAND_WritePage(_pBuffer, _ulPageNo, NAND_PAGE_SIZE + _usAddrInSpare, _usByteCount);
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_ReadSpare
*	����˵��: ��1��PAGE��Spare��������
*	��    ��:   - _pBuffer:  ָ�������д���ݵĻ�����
*             - _ulPageNo: ҳ�ţ����е�ҳͳһ���룬��ΧΪ��
*			        - _usAddrInSpare : ҳ�ڱ�������ƫ�Ƶ�ַ����ΧΪ��0-15��byte  added by sjw
*             - _usByteCount: ������ֽڸ���
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t FSMC_NAND_ReadSpare(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInSpare, uint16_t _usByteCount)
{
	if (_usByteCount > NAND_SPARE_AREA_SIZE)
	{
		return NAND_FAIL;
	}

	return FSMC_NAND_ReadPage(_pBuffer, _ulPageNo, NAND_PAGE_SIZE + _usAddrInSpare, _usByteCount);
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_WriteData
*	����˵��: ��1��PAGE����������д������
*	��    ��:   - _pBuffer: ָ�������д���ݵĻ�����
*             - _ulPageNo: ҳ�ţ����е�ҳͳһ���룬��ΧΪ��0 - x
*			        - _usAddrInPage : ҳ����������ƫ�Ƶ�ַ����ΧΪ��0-y
*             - _usByteCount: д����ֽڸ���
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_WriteData(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount)
{
	if (_usByteCount > NAND_PAGE_SIZE)
	{
		printf("Error: FSMC_NAND_WriteData() %d\r\n",_usByteCount);
		return NAND_FAIL;
	}

	return FSMC_NAND_WritePage(_pBuffer, _ulPageNo, _usAddrInPage, _usByteCount);
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_ReadData
*	����˵��: ��1��PAGE�������ݵ�����
*	��    ��:  - _pBuffer: ָ������������ݵĻ�����
*            - _ulPageNo: ҳ�ţ����е�ҳͳһ���룬��ΧΪ��0 - 65535
*			       - _usAddrInPage : ҳ����������ƫ�Ƶ�ַ����ΧΪ��0-512����2047
*            - _usByteCount: д����ֽڸ���
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_ReadData(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount)
{
	if (_usByteCount > NAND_PAGE_SIZE)
	{
		return NAND_FAIL;
	}

	return FSMC_NAND_ReadPage(_pBuffer, _ulPageNo, _usAddrInPage, _usByteCount);
}









/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_EraseBlock
*	����˵��: ����NAND Flashһ���飨block��
*	��    ��:  - _ulBlockNo: ��ţ���ΧΪ�� 0-4095
*	�� �� ֵ: NAND����״̬�������¼���ֵ��
*             - NAND_TIMEOUT_ERROR  : ��ʱ����
*             - NAND_READY          : �����ɹ�
*********************************************************************************************************
*/

 uint8_t FSMC_NAND_EraseBlock(uint32_t _ulBlockNo)//is OK!!
{
	/* HY27UF081G2A  (128MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12    A18�����ǿ��
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		��1�ֽڣ� A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr ��bit7 - bit0)
		��2�ֽڣ� 0    0    0    0    A11  A10  A9   A8		(_usPageAddr ��bit11 - bit8, ��4bit������0)
		��3�ֽڣ� A19  A18  A17  A16  A15  A14  A13  A12    A18�����ǿ��
		��4�ֽڣ� A27  A26  A25  A24  A23  A22  A21  A20
		��5�ֽڣ� A28  A29  A30  A31  0    0    0    0
	*/
	
  //������������60H����������ַ��Ȼ�����D0H��
	//��70H����״̬���ȴ�������ɼ��� 
	
	
	/* ���Ͳ������� */
	NAND_CMD_AREA = NAND_CMD_ERASE0;
	_ulBlockNo <<= 5;	/* ���ת��Ϊҳ��� ����Ϊ��ÿ��������32ҳ��ɵģ���added by sjw*/


	#if NAND_ADDR_5 == 0	/* 64  MB�� */
		NAND_ADDR_AREA =ADDR_1st_CYCLE(_ulBlockNo);
		NAND_ADDR_AREA =ADDR_2nd_CYCLE(_ulBlockNo);
		NAND_ADDR_AREA =ADDR_3rd_CYCLE(_ulBlockNo);
		
	#else		             /* 512MB�� */
		NAND_ADDR_AREA = _ulBlockNo;
		NAND_ADDR_AREA = _ulBlockNo >> 8;
		NAND_ADDR_AREA = _ulBlockNo >> 16;
	#endif

	NAND_CMD_AREA = NAND_CMD_ERASE1;
	return (FSMC_NAND_GetStatus());
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_Reset
*	����˵��: ��λNAND Flash
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_Reset(void)
{
	NAND_CMD_AREA = NAND_CMD_RESET;

		/* ������״̬ */
	if (FSMC_NAND_GetStatus() == NAND_READY)
	{
		return NAND_OK;
	}

	return NAND_FAIL;
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_ReadStatus
*	����˵��: ʹ��Read statuc �����NAND Flash�ڲ�״̬
*	��    ��:  - Address: �������Ŀ��������ַ
*	�� �� ֵ: NAND����״̬�������¼���ֵ��
*             - NAND_BUSY: �ڲ���æ
*             - NAND_READY: �ڲ����У����Խ����²�����
*             - NAND_ERROR: ��ǰ������ִ��ʧ��
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_ReadStatus(void)
{
	uint8_t ucData;
	uint8_t ucStatus = NAND_BUSY;

	/* ��״̬���� */
	NAND_CMD_AREA = NAND_CMD_STATUS;
	ucData = *(__IO uint8_t *)(Bank_NAND_ADDR);

	if((ucData & NAND_ERROR) == NAND_ERROR)
	{
		ucStatus = NAND_ERROR;
	}
	else if((ucData & NAND_READY) == NAND_READY)
	{
		ucStatus = NAND_READY;
	}
	else
	{
		ucStatus = NAND_BUSY;
	}

	return (ucStatus);
}

/*
*********************************************************************************************************
*	�� �� ��: FSMC_NAND_GetStatus
*	����˵��: ��ȡNAND Flash����״̬
*	��    ��:  - Address: �������Ŀ��������ַ
*	�� �� ֵ: NAND����״̬�������¼���ֵ��
*             - NAND_TIMEOUT_ERROR  : ��ʱ����
*             - NAND_READY          : �����ɹ�
*********************************************************************************************************
*/
 uint8_t FSMC_NAND_GetStatus(void)
{
	uint32_t ulTimeout = 0x10000;
	uint8_t ucStatus = NAND_READY;

	ucStatus = FSMC_NAND_ReadStatus();

	/* �ȴ�NAND������������ʱ����˳� */
	while ((ucStatus != NAND_READY) &&( ulTimeout != 0x00))
	{
		ucStatus = FSMC_NAND_ReadStatus();
		ulTimeout--;
	}

	if(ulTimeout == 0x00)
	{
		ucStatus =  NAND_TIMEOUT_ERROR;
	}

	/* ���ز���״̬ */
	return (ucStatus);
}

/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: ��ʼ��NAND Flash�ӿ�
*	��    ��:  ��
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
Tips:NAND������ID�����Ĳ��֣�
1st Manufacturer Code 
2nd Device Identifier 
3rd Internal chip number, cell Type, Number of Simultaneously Programmed pages. 
4th Page size, spare size, Block size, Organization




STM32F103��FSMC��дNANDFlash��ѧϰ,���ĶԶ�д���ܵıȽϺã�
https://blog.csdn.net/YANXI_123/article/details/78934411?locationNum=8&fps=1



https://bbs.21ic.com/icview-2870710-1-1.html
*/



uint32_t nandsize=0;
uint8_t NAND_Init(void)
{
	uint8_t Status;

	//	FSMC_NAND_Init();	/* ��ʼ��FSMC */

	FSMC_NAND_Init();			    // ����FSMC��GPIO����NAND Flash�ӿ� 

	FSMC_NAND_Reset();			  //ͨ����λ���λNAND Flash����״̬ 
	
	
	//Status = NAND_BuildLUT();	// ���������� LUT = Look up table 
	Status= NAND_OK;
	
	return Status;
}




/*
*********************************************************************************************************
*	�� �� ��: NAND_WriteToNewBlock
*	����˵��: ���ɿ�����ݸ��Ƶ��¿飬�����µ����ݶ�д������¿�. 
*	��    ��:  	_ulPhyPageNo : Դҳ��
*				_pWriteBuf �� ���ݻ�����
*				_usOffset �� ҳ��ƫ�Ƶ�ַ
*				_usSize �����ݳ��ȣ�������4�ֽڵ�������
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t NAND_WriteToNewBlock(uint32_t _ulPhyPageNo, uint8_t *_pWriteBuf, uint16_t _usOffset, uint16_t _usSize)
{
	uint16_t n, i;
	uint16_t usNewBlock;
	uint16_t ulSrcBlock;
	uint16_t usOffsetPageNo;

	ulSrcBlock = _ulPhyPageNo / NAND_BLOCK_SIZE;		/* ��������ҳ�ŷ��ƿ�� */
	usOffsetPageNo = _ulPhyPageNo % NAND_BLOCK_SIZE;	/* ��������ҳ�ż�������ҳ���ڿ���ƫ��ҳ�� */
	/* ����ѭ����Ŀ���Ǵ���Ŀ���Ϊ�������� */
	for (n = 0; n < 10; n++)
	{
		/* �������ȫ0xFF�� ����ҪѰ��һ�����п��ÿ飬����ҳ�ڵ�����ȫ���Ƶ��¿��У�Ȼ���������� */
		usNewBlock = NAND_FindFreeBlock(_ulPhyPageNo);	/* �����һ��Block��ʼ����Ѱһ�����ÿ�.  */
		if (usNewBlock >= NAND_BLOCK_COUNT)
		{
			//printf_err("Error1: NAND_WriteToNewBlock() %d\r\n", usNewBlock);
			return NAND_FAIL;	/* ���ҿ��п�ʧ�� */
		}

		//printf_ok("NAND_WriteToNewBlock(%d -> %d)\r\n", ulSrcBlock, usNewBlock);
		
		/* ʹ��page-copy���ܣ�����ǰ�飨usPBN��������ȫ�����Ƶ��¿飨usNewBlock�� */
		for (i = 0; i < NAND_BLOCK_SIZE; i++)
		{
			if (i == usOffsetPageNo)
			{
				/* ���д��������ڵ�ǰҳ������Ҫʹ�ô�������ݵ�Copy-Back���� */
				if (FSMC_NAND_PageCopyBackEx(ulSrcBlock * NAND_BLOCK_SIZE + i, usNewBlock * NAND_BLOCK_SIZE + i,
					_pWriteBuf, _usOffset, _usSize) == NAND_FAIL)
				{
					//printf_err("Error2: NAND_WriteToNewBlock() %d\r\n", ulSrcBlock);
					NAND_MarkBadBlock(usNewBlock);	/* ���¿���Ϊ���� */
					NAND_BuildLUT();				/* �ؽ�LUT�� */
					break;
				}

			}
			else
			{
				/* ʹ��NAND Flash �ṩ����ҳCopy-Back���ܣ�����������߲���Ч�� */
				if (FSMC_NAND_PageCopyBack(ulSrcBlock * NAND_BLOCK_SIZE + i,usNewBlock * NAND_BLOCK_SIZE + i) == NAND_FAIL)
				{
					//printf_err("Error3: NAND_WriteToNewBlock() %d\r\n", ulSrcBlock);
					
					NAND_MarkBadBlock(usNewBlock);	/* ���¿���Ϊ���� */
					NAND_BuildLUT();				/* �ؽ�LUT�� */
					break;
				}
			}
		}
		/* Ŀ�����³ɹ� */
		if (i == NAND_BLOCK_SIZE)
		{
			/* ����¿�Ϊ���ÿ� */
			if (NAND_MarkUsedBlock(usNewBlock) == NAND_FAIL)
			{
				NAND_MarkBadBlock(usNewBlock);	/* ���¿���Ϊ���� */
				NAND_BuildLUT();				/* �ؽ�LUT�� */
				continue;
			}

			/* ����ԴBLOCK  (���Դ��дʧ�ܣ�������������) */
			if (FSMC_NAND_EraseBlock(ulSrcBlock) != NAND_READY)
			{
				//printf_err("Error4: FSMC_NAND_EraseBlock(), %d\r\n", ulSrcBlock);
				NAND_MarkBadBlock(ulSrcBlock);	/* ��Դ����Ϊ���� */
				NAND_BuildLUT();				/* �ؽ�LUT�� */
				continue;
			}
			NAND_BuildLUT();				/* �ؽ�LUT�� */
			break;
		}
	}
	if (n == 10)
	{
		//printf_err("Error5: FSMC_NAND_EraseBlock() n=%d\r\n", n);
		return NAND_FAIL;
	}

	return NAND_OK;	/* д��ɹ� */
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_WriteByteAbsoluteAddr
*	����˵��: дһ������
*	��    ��:  	_pWritebuff ����Ŵ�д���ݵĻ�������ָ��
              _ulMemAddr : �ڴ浥Ԫƫ�Ƶ�ַ(���ֽ�Ϊ��λ�����ֵΪ  131072*512=67108864
*				      _usSize �����ݳ��ȣ�������4�ֽڵ�������
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t NAND_WriteByteAbsoluteAddr(uint8_t *_pWriteBuf,uint32_t _ulMemAddr , uint16_t _usSize)
{
	static uint16_t usPBN;			     /* ������ */
	static uint32_t ulPhyPageNo;	   /* ����ҳ�� */
	static uint16_t usAddrInPage;	   /* ҳ��ƫ�Ƶ�ַ */
	static uint32_t ulTemp;

	/* ���ݳ��ȱ�����4�ֽ������� */
	if ((_usSize % 4) != 0)
	{
		printf("Error:1 NAND_WriteByteAbsoluteAddr()  %d\r\n",_usSize);
		return NAND_FAIL;
	}
	/* ���ݳ��Ȳ��ܳ���512�ֽ�(��ѭ Fat��ʽ) */
	if (_usSize > 512)
	{
		printf("Error:2 NAND_WriteByteAbsoluteAddr() length is larger 512byte/page  %d\r\n",_usSize);
		return NAND_FAIL;
	}

	usPBN = NAND_AddrToPhyBlockNo(_ulMemAddr);	/* ��ѯLUT���������� */

	ulTemp = _ulMemAddr % (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
	ulPhyPageNo = usPBN * NAND_BLOCK_SIZE + ulTemp / NAND_PAGE_SIZE;	/* ��������ҳ�� */
	usAddrInPage = ulTemp % NAND_PAGE_SIZE;	/* ����ҳ��ƫ�Ƶ�ַ */

	/* �������������ݣ��ж��Ƿ�ȫFF */
	if (FSMC_NAND_ReadData(s_ucTempBuf, ulPhyPageNo, usAddrInPage, _usSize) == NAND_FAIL)
	{
		return NAND_FAIL;	/* ��NAND Flashʧ�� */
	}
	/*�������ȫ0xFF, �����ֱ��д�룬������� */
	if (NAND_IsBufOk(s_ucTempBuf, _usSize, 0xFF) == 1)
	{
		if (FSMC_NAND_WriteData((uint8_t *)_pWriteBuf, ulPhyPageNo, usAddrInPage, _usSize) == NAND_FAIL)
		{
			/* ������д�뵽����һ���飨���п飩 */
			return NAND_WriteToNewBlock(ulPhyPageNo, (uint8_t *)_pWriteBuf, usAddrInPage, _usSize);
		}

		/* ��Ǹÿ����� */
		if (NAND_MarkUsedBlock(ulPhyPageNo / NAND_BLOCK_SIZE) == NAND_FAIL)
		{
			/* ���ʧ�ܣ�������д�뵽����һ���飨���п飩 */
			return NAND_WriteToNewBlock(ulPhyPageNo, (uint8_t *)_pWriteBuf, usAddrInPage, _usSize);
		}
		return NAND_OK;	/* д��ɹ� */
	}

	/* ������д�뵽����һ���飨���п飩 */
	return NAND_WriteToNewBlock(ulPhyPageNo, (uint8_t *)_pWriteBuf, usAddrInPage, _usSize);
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_ReadOneSector
*	����˵��: ��һ������
*	��    ��:  	_MemAddr : �ڴ浥Ԫƫ�Ƶ�ַ
*				      _pReadbuff ����Ŷ������ݵĻ�������ָ��
*				      _usSize �����ݳ��ȣ�������4�ֽڵ�������
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t NAND_ReadOneSector(uint8_t *_pReadBuf,uint32_t _ulMemAddr,  uint16_t _usSize)
{
	uint16_t usPBN;			/* ������ */
	uint32_t ulPhyPageNo;	/* ����ҳ�� */
	uint16_t usAddrInPage;	/* ҳ��ƫ�Ƶ�ַ */
	uint32_t ulTemp;

	/* ���ݳ��ȱ�����4�ֽ������� */
	if ((_usSize % 4) != 0)
	{
		printf("Error:1 NAND_ReadOneSector(_usSize)  %d\r\n",_usSize);
		return NAND_FAIL;
	}

	usPBN = NAND_AddrToPhyBlockNo(_ulMemAddr);	/* ��ѯLUT���������� */
	if (usPBN >= NAND_BLOCK_COUNT)
	{
		/* û�и�ʽ����usPBN = 0xFFFF */
		printf("Error:1 û�г�ʼ���� NAND_WriteByteAbsoluteAddr() usPBN %d\r\n",usPBN);
		return NAND_FAIL;
	}

	ulTemp = _ulMemAddr % (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
	ulPhyPageNo = usPBN * NAND_BLOCK_SIZE + ulTemp / NAND_PAGE_SIZE;	/* ��������ҳ�� */
	usAddrInPage = ulTemp % NAND_PAGE_SIZE;	/* ����ҳ��ƫ�Ƶ�ַ */

	if (FSMC_NAND_ReadData((uint8_t *)_pReadBuf, ulPhyPageNo, usAddrInPage, _usSize) == NAND_FAIL)
	{
		return NAND_FAIL;	/* ��NAND Flashʧ�� */
	}

	/* �ɹ� */
	return NAND_OK;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_WriteMultiSectors
*	����˵��: �ú��������ļ�ϵͳ������д����������ݡ�������С������512�ֽڻ�2048�ֽ�
*	��    ��:  	_pBuf : ������ݵĻ�������ָ��
*				     _SectorNo ��������
*				     _SectorSize ��ÿ�������Ĵ�С ��һ���� 512�ֽڣ�
*				_    _SectorCount : ��������
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t NAND_WriteMultiSectorsback(uint8_t *_pBuf, uint32_t _SectorNo, uint16_t _SectorSize, uint32_t _SectorCount)
{
	uint32_t i;
	uint32_t usLBN;			     /* �߼���� */
	uint32_t usPBN;			     /* ������ */
	uint32_t uiPhyPageNo;	   /* ����ҳ�� */
	uint16_t usAddrInPage;	 /* ҳ��ƫ�Ƶ�ַ */
	uint32_t ulTemp;
	uint8_t ucReturn;

	/*
	
		ÿ��PAGE���߼��Ͽ��Է�Ϊx��512�ֽ�������
		
	NAND_WriteMultiSectors
	K9F1208U0B=64M  �� 4096��BLOCK, ÿ��BLOCK����32��PAGE�� ÿ��PAGE����512+16�ֽ�
	*/

	for (i = 0; i < _SectorCount; i++)
	{
		//�����߼������ź�������С�����߼���� 
		//usLBN = (_SectorNo * _SectorSize) / (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		// (_SectorNo * _SectorSize) �˻����ܴ���32λ����˻���������д�� 
		usLBN = (_SectorNo + i) / (NAND_BLOCK_SIZE * (NAND_PAGE_SIZE / _SectorSize));
		usPBN = NAND_LBNtoPBN(usLBN);	//��ѯLUT���������� 
		if (usPBN >= NAND_BLOCK_COUNT)
		{
			printf("Error1: NAND_WriteMultiSectors(), no format. usLBN=%d, usPBN=%d\r\n", usLBN, usPBN);//û�и�ʽ����usPBN = 0xFFFF 		
			return NAND_FAIL;
		}

		//ulTemp = ((uint64_t)(_SectorNo + i) * _SectorSize) % (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		ulTemp = ((_SectorNo + i) % (NAND_BLOCK_SIZE * (NAND_PAGE_SIZE / _SectorSize))) *  _SectorSize;
		uiPhyPageNo = usPBN * NAND_BLOCK_SIZE + ulTemp / NAND_PAGE_SIZE;	//��������ҳ�� 
		usAddrInPage = ulTemp % NAND_PAGE_SIZE;	/* ����ҳ��ƫ�Ƶ�ַ */

		//��� _SectorCount > 0, ������ҳ���׵�ַ������Խ����Ż� 
		if (usAddrInPage == 0)
		{
			//��δ���� 
		}
		
		memset(s_ucTempBuf, 0xFF, _SectorSize);
		
		

		//�������ȫ0xFF, �����ֱ��д�룬������� 
		if (NAND_IsBufOk(s_ucTempBuf, _SectorSize, 0xFF) == 1){//added by sjw
			//if (FSMC_NAND_WriteData((&_pBuf[i * _SectorSize], uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_FAIL)
		  //{
			
		  //}
			FSMC_NAND_WriteData(&_pBuf[i * _SectorSize], uiPhyPageNo, usAddrInPage, _SectorSize);
		}
		
		
		
		
		
		
		
		
		
		
		/*
		if (FSMC_NAND_CompPage(s_ucTempBuf, uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_OK)
		{
			if (FSMC_NAND_WriteData(&_pBuf[i * _SectorSize], uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_FAIL)
			{
				//printf_err("Error3: NAND_WriteMultiSectors(), Write Faile\r\n");
				// ������д�뵽����һ���飨���п飩 
				ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
				if (ucReturn != NAND_OK)
				{
				//	printf_err("Error4: NAND_WriteMultiSectors(), Write Faile\r\n");
					return NAND_FAIL;	// ʧ�� 
				}
				
				// ���Դ��Ϊ���� 
				NAND_MarkBadBlock(uiPhyPageNo / NAND_BLOCK_SIZE);	//��Դ����Ϊ���� 
				continue;
			}

			//��Ǹÿ����� 
			if (NAND_MarkUsedBlock(uiPhyPageNo / NAND_BLOCK_SIZE) == NAND_FAIL)
			{
				//���ʧ�ܣ�������д�뵽����һ���飨���п飩 
				ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
				if (ucReturn != NAND_OK)
				{
					return NAND_FAIL;	// ʧ�� 
				}
				continue;
			}
		}
		else	// Ŀ�������Ѿ������ݣ�����ȫFF, ��ֱ�ӽ�����д������һ�����п� 
		{
			// ������д�뵽����һ���飨���п飩 
			ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
			if (ucReturn != NAND_OK)
			{
				//printf_err("Error5: NAND_WriteMultiSectors(), Write Faile\r\n");
				return NAND_FAIL;	// ʧ�� 
			}
			continue;
		}
		
		*/
	}
	return NAND_OK;		// �ɹ� 
}


/*
uint8_t NAND_WriteMultiSectors(uint8_t *_pBuf, uint32_t _SectorNo, uint16_t _SectorSize, uint32_t _SectorCount)
{
	uint32_t i;
	uint32_t usLBN;			    //�߼���� 
	uint32_t usPBN;			    //������ 
	uint32_t uiPhyPageNo;	  // ����ҳ�� 
	uint16_t usAddrInPage;	// ҳ��ƫ�Ƶ�ַ 
	uint32_t ulTemp;
	uint8_t ucReturn;

	
//		HY27UF081G2A = 128M Flash.  �� 1024��BLOCK, ÿ��BLOCK����64��PAGE�� ÿ��PAGE����2048+64�ֽڣ�
//		������С��λ��BLOCK�� �����С��λ���ֽڡ�

//		ÿ��PAGE���߼��Ͽ��Է�Ϊ4��512�ֽ�����������ΪоƬHY27UF081G2A = 128M Flash
//	 �����Ҫ��Сҳ��flash k9f1208UOx����ô��Ҫע�⣺
//	

	for (i = 0; i < _SectorCount; i++)
	{
		//�����߼������ź�������С�����߼���� 
		//usLBN = (_SectorNo * _SectorSize) / (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		// (_SectorNo * _SectorSize) �˻����ܴ���32λ����˻���������д�� 
		usLBN = (_SectorNo + i) / (NAND_BLOCK_SIZE * (NAND_PAGE_SIZE / _SectorSize));
		usPBN = NAND_LBNtoPBN(usLBN);	//��ѯLUT���������� 
		if (usPBN >= NAND_BLOCK_COUNT)
		{
			//printf_err("Error1: NAND_WriteMultiSectors(), no format. usLBN=%d, usPBN=%d\r\n", usLBN, usPBN);
			//û�и�ʽ����usPBN = 0xFFFF 
			return NAND_FAIL;
		}

		//ulTemp = ((uint64_t)(_SectorNo + i) * _SectorSize) % (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		ulTemp = ((_SectorNo + i) % (NAND_BLOCK_SIZE * (NAND_PAGE_SIZE / _SectorSize))) *  _SectorSize;
		uiPhyPageNo = usPBN * NAND_BLOCK_SIZE + ulTemp / NAND_PAGE_SIZE;	//��������ҳ�� 
		usAddrInPage = ulTemp % NAND_PAGE_SIZE;	// ����ҳ��ƫ�Ƶ�ַ 

		// ��� _SectorCount > 0, ������ҳ���׵�ַ������Խ����Ż� 
		if (usAddrInPage == 0)
		{
			// ��δ���� 
		}
		
		memset(s_ucTempBuf, 0xFF, _SectorSize);

		//�������ȫ0xFF, �����ֱ��д�룬������� 
		//if (NAND_IsBufOk(s_ucTempBuf, _SectorSize, 0xFF) == 1)
		if (FSMC_NAND_CompPage(s_ucTempBuf, uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_OK)
		{
			if (FSMC_NAND_WriteData(&_pBuf[i * _SectorSize], uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_FAIL)
			{
				//printf_err("Error3: NAND_WriteMultiSectors(), Write Faile\r\n");
				//������д�뵽����һ���飨���п飩 
				ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
				if (ucReturn != NAND_OK)
				{
				//	printf_err("Error4: NAND_WriteMultiSectors(), Write Faile\r\n");
					return NAND_FAIL;	// ʧ�� 
				}
				
				// ���Դ��Ϊ���� 
				NAND_MarkBadBlock(uiPhyPageNo / NAND_BLOCK_SIZE);	// ��Դ����Ϊ���� 
				continue;
			}

			// ��Ǹÿ����� 
			if (NAND_MarkUsedBlock(uiPhyPageNo / NAND_BLOCK_SIZE) == NAND_FAIL)
			{
				// ���ʧ�ܣ�������д�뵽����һ���飨���п飩 
				ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
				if (ucReturn != NAND_OK)
				{
					return NAND_FAIL;	// ʧ�� 
				}
				continue;
			}
		}
		else	//Ŀ�������Ѿ������ݣ�����ȫFF, ��ֱ�ӽ�����д������һ�����п� 
		{
			//������д�뵽����һ���飨���п飩 
			ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
			if (ucReturn != NAND_OK)
			{
				//printf_err("Error5: NAND_WriteMultiSectors(), Write Faile\r\n");
				return NAND_FAIL;	// ʧ�� 
			}
			continue;
		}
	}
	return NAND_OK;		//�ɹ� 
}

*/


/*
*********************************************************************************************************
*	�� �� ��: NAND_WriteMultiSectors
*	����˵��: �ú��������ļ�ϵͳ������д����������ݡ�������С������512�ֽڻ�2048�ֽ�
*	��    ��:  	_pBuf : ������ݵĻ�������ָ��
*				     _SectorNo ��������
*				     _SectorSize ��ÿ�������Ĵ�С ��һ���� 512�ֽڣ�
*				_    _SectorCount : ��������
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t NAND_WriteMultiSectors(uint8_t *_pBuf, uint32_t _SectorNo, uint16_t _SectorSize, uint32_t _SectorCount)
{
	uint32_t i;
	uint32_t usLBN;			     /* �߼���� */
	uint32_t usPBN;			     /* ������ */
	uint32_t uiPhyPageNo;	   /* ����ҳ�� */
	uint16_t usAddrInPage;	 /* ҳ��ƫ�Ƶ�ַ */
	uint32_t ulTemp;
	uint8_t ucReturn;

	

	for (i = 0; i < _SectorCount; i++)
	{
		//�����߼������ź�������С�����߼���� 
		//usLBN = (_SectorNo * _SectorSize) / (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		// (_SectorNo * _SectorSize) �˻����ܴ���32λ����˻���������д�� 
		
		
		usLBN = (_SectorNo + i) / (NAND_BLOCK_SIZE * (NAND_PAGE_SIZE / _SectorSize));
		usPBN = NAND_LBNtoPBN(usLBN);	//��ѯLUT���������� 
		if (usPBN >= NAND_BLOCK_COUNT)
		{
			printf("Error1:NAND����û�и�ʽ�� NAND_WriteMultiSectors(), no format. usLBN=%d, usPBN=%d\r\n", usLBN, usPBN);//û�и�ʽ����usPBN = 0xFFFF 		
			return NAND_FAIL;
		}

		//ulTemp = ((uint64_t)(_SectorNo + i) * _SectorSize) % (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		ulTemp = ((_SectorNo + i) % (NAND_BLOCK_SIZE * (NAND_PAGE_SIZE / _SectorSize))) *  _SectorSize;
		uiPhyPageNo = usPBN * NAND_BLOCK_SIZE + ulTemp / NAND_PAGE_SIZE;	//��������ҳ�� 
		usAddrInPage = ulTemp % NAND_PAGE_SIZE;	/* ����ҳ��ƫ�Ƶ�ַ */

		//��� _SectorCount > 0, ������ҳ���׵�ַ������Խ����Ż� 
		if (usAddrInPage == 0)
		{
			//��δ���� 
		}
		
		memset(s_ucTempBuf, 0xFF, _SectorSize);
		
		

		//�������ȫ0xFF, �����ֱ��д�룬������� 
		if (NAND_IsBufOk(s_ucTempBuf, _SectorSize, 0xFF) == 1){//added by sjw	
			FSMC_NAND_WriteData(&_pBuf[i * _SectorSize], uiPhyPageNo, usAddrInPage, _SectorSize);
		}
		
		
		
		
		
		
		
		
		
		
		/*
		if (FSMC_NAND_CompPage(s_ucTempBuf, uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_OK)
		{
			if (FSMC_NAND_WriteData(&_pBuf[i * _SectorSize], uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_FAIL)
			{
				//printf_err("Error3: NAND_WriteMultiSectors(), Write Faile\r\n");
				// ������д�뵽����һ���飨���п飩 
				ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
				if (ucReturn != NAND_OK)
				{
				//	printf_err("Error4: NAND_WriteMultiSectors(), Write Faile\r\n");
					return NAND_FAIL;	// ʧ�� 
				}
				
				// ���Դ��Ϊ���� 
				NAND_MarkBadBlock(uiPhyPageNo / NAND_BLOCK_SIZE);	//��Դ����Ϊ���� 
				continue;
			}

			//��Ǹÿ����� 
			if (NAND_MarkUsedBlock(uiPhyPageNo / NAND_BLOCK_SIZE) == NAND_FAIL)
			{
				//���ʧ�ܣ�������д�뵽����һ���飨���п飩 
				ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
				if (ucReturn != NAND_OK)
				{
					return NAND_FAIL;	// ʧ�� 
				}
				continue;
			}
		}
		else	// Ŀ�������Ѿ������ݣ�����ȫFF, ��ֱ�ӽ�����д������һ�����п� 
		{
			// ������д�뵽����һ���飨���п飩 
			ucReturn = NAND_WriteToNewBlock(uiPhyPageNo, &_pBuf[i * _SectorSize], usAddrInPage, _SectorSize);
			if (ucReturn != NAND_OK)
			{
				//printf_err("Error5: NAND_WriteMultiSectors(), Write Faile\r\n");
				return NAND_FAIL;	// ʧ�� 
			}
			continue;
		}
		
		*/
	}
	return NAND_OK;		// �ɹ� 
}




































/*
*********************************************************************************************************
*	�� �� ��: NAND_ReadMultiSectors
*	����˵��: �ú��������ļ�ϵͳ�������������ݡ���1������������������С������512�ֽڻ�2048�ֽ�
*	��    ��:  	_pBuf : ��Ŷ������ݵĻ�������ָ��
*				      _SectorNo ��������
*				      _SectorSize ��ÿ�������Ĵ�С
*				      _SectorCount : ��������
*	�� �� ֵ: ִ�н����
*				- NAND_FAIL ��ʾʧ��
*				- NAND_OK ��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t NAND_ReadMultiSectors(uint8_t *_pBuf, uint32_t _SectorNo, uint16_t _SectorSize, uint32_t _SectorCount)
{
	uint32_t i;
	uint32_t usLBN;			    /* �߼���� */
	uint32_t usPBN;			    /* ������ */
	uint32_t uiPhyPageNo;	  /* ����ҳ�� */
	uint16_t usAddrInPage;	/* ҳ��ƫ�Ƶ�ַ */
	uint32_t ulTemp;

	/*
		HY27UF081G2A = 128M Flash.  �� 1024��BLOCK, ÿ��BLOCK����64��PAGE�� ÿ��PAGE����2048+64�ֽڣ�
		������С��λ��BLOCK�� �����С��λ���ֽڡ�

		ÿ��PAGE���߼��Ͽ��Է�Ϊ4��512�ֽ�������
	������128M��flash����˳������
	�޸�Ϊ64M��flash����˳��
	*/

	for (i = 0; i < _SectorCount; i++)
	{
		/* �����߼������ź�������С�����߼���� */
		//usLBN = (_SectorNo * _SectorSize) / (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		/* (_SectorNo * _SectorSize) �˻����ܴ���32λ����˻���������д�� */
		usLBN = (_SectorNo + i) / (NAND_BLOCK_SIZE * (NAND_PAGE_SIZE / _SectorSize));
		usPBN = NAND_LBNtoPBN(usLBN);	/* ��ѯLUT���������� */
		if (usPBN >= NAND_BLOCK_COUNT)
		{
			//printf_err("Error: NAND_ReadMultiSectors(), not format, usPBN = %d\r\n", usPBN);
			/* û�и�ʽ����usPBN = 0xFFFF */
			return NAND_FAIL;
		}
		
		
//�������ǰ_SectorNo�������ҳ�е��ֽ���
		ulTemp = ((uint64_t)(_SectorNo + i) * _SectorSize) % (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
		uiPhyPageNo = usPBN * NAND_BLOCK_SIZE + ulTemp / NAND_PAGE_SIZE;	/* ��������ҳ�� */
		usAddrInPage = ulTemp % NAND_PAGE_SIZE;	/* ����ҳ��ƫ�Ƶ�ַ */

		if (FSMC_NAND_ReadData((uint8_t *)&_pBuf[i * _SectorSize], uiPhyPageNo, usAddrInPage, _SectorSize) == NAND_FAIL)
		{
			printf("Error: NAND_ReadMultiSectors(), ReadData(page = %d, addr = %d)\r\n", uiPhyPageNo, usAddrInPage);
			return NAND_FAIL;	/* ��NAND Flashʧ�� */
		}
	}

	/* �ɹ� */
	return NAND_OK;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_BuildLUT
*	����˵��: ���ڴ��д�����������
*	��    ��:  ZoneNbr ������
*	�� �� ֵ: NAND_OK�� �ɹ��� 	NAND_FAIL��ʧ��
*********************************************************************************************************
*/
	
 uint8_t NAND_BuildLUT(void)
{
	uint16_t i;
	uint8_t buf[VALID_SPARE_SIZE];
	uint16_t usLBN;	/* �߼���� */

	
	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
		s_usLUT[i] = 0xFFFF;	/* �����Чֵ�������ؽ�LUT���ж�LUT�Ƿ���� */
	}
	
	



	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
		/* ��ÿ����ĵ�1��PAGE��ƫ�Ƶ�ַΪLBN0_OFFSET������ */
		FSMC_NAND_ReadSpare(buf, i * NAND_BLOCK_SIZE, 0, VALID_SPARE_SIZE);//is wrong????????????????????
		/* ����Ǻÿ飬���¼LBN0 LBN1 */
		if (buf[BI_OFFSET] == 0xFF)
		{
			usLBN = buf[LBN0_OFFSET]+buf[LBN1_OFFSET] * 256 ;	/* ����������߼���� */
			if (usLBN < NAND_BLOCK_COUNT)
			{
				/* ����Ѿ��Ǽǹ��ˣ����ж�Ϊ�쳣 */
				if (s_usLUT[usLBN] != 0xFFFF)
				{
					return NAND_FAIL;
				}
				s_usLUT[usLBN] = i;	/* ����LUT�� */
			}
		}
	}
	
	
	

	/* LUT������ϣ�����Ƿ���� */
	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
		if (s_usLUT[i] >= NAND_BLOCK_COUNT)
		{
			s_usValidDataBlockCount = i;
			break;
		}
	}
	if (s_usValidDataBlockCount < 100)
	{
		/* ���� ������Ч�߼����С��100��������û�и�ʽ�� */
		return NAND_FAIL;
	}
	for (; i < s_usValidDataBlockCount; i++)
	{
		if (s_usLUT[i] != 0xFFFF)
		{
			return NAND_FAIL;	/* ����LUT���߼���Ŵ�����Ծ���󣬿�����û�и�ʽ�� */
		}
	}

	/* �ؽ�LUT���� */
	return NAND_OK;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_AddrToPhyBlockNo
*	����˵��: �߼��ڴ��ַת��Ϊ������
*	��    ��:  _ulMemAddr���߼��ڴ��ַ
*	�� �� ֵ: ����ҳ�ţ� ����� 0xFFFFFFFF ���ʾ����
*********************************************************************************************************
*/
uint16_t NAND_AddrToPhyBlockNo(uint32_t _ulMemAddr)
{
	uint16_t usLBN;		/* �߼���� */
	uint16_t usPBN;		/* ������ */

	usLBN = _ulMemAddr / (NAND_BLOCK_SIZE * NAND_PAGE_SIZE);	/* �����߼���� */
	/* ����߼���Ŵ�����Ч�����ݿ������̶�����0xFFFF, ���øú����Ĵ���Ӧ�ü������ִ��� */
	if (usLBN >= s_usValidDataBlockCount)
	{
		return 0xFFFF;
	}
	/* ��ѯLUT����������� */
	usPBN = s_usLUT[usLBN];
	return usPBN;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_LBNtoPBN
*	����˵��: �߼����ת��Ϊ������
*	��    ��: _uiLBN : �߼���� Logic Block No
*	�� �� ֵ: �����ţ� ����� 0xFFFFFFFF ���ʾ����
*********************************************************************************************************
*/
 uint16_t NAND_LBNtoPBN(uint32_t _uiLBN)
{
	uint16_t usPBN;		/* ������ */

//	/* ����߼���Ŵ�����Ч�����ݿ������̶�����0xFFFF, ���øú����Ĵ���Ӧ�ü������ִ��� */
//	if (_uiLBN >= s_usValidDataBlockCount)
//	{
//		return 0xFFFF;
//	}
	/* ��ѯLUT����������� */
	usPBN = s_usLUT[_uiLBN];
	return usPBN;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_FindFreeBlock
*	����˵��: �����һ���鿪ʼ������һ�����õĿ顣A18������ͬ
*	��    ��: _ulSrcPageNo : Դҳ��
*	�� �� ֵ: ��ţ������0xFFFF��ʾʧ��
*********************************************************************************************************
*/
 uint16_t NAND_FindFreeBlock (uint32_t _ulSrcPageNo)
{
	uint16_t n;

	n = NAND_BLOCK_COUNT - 1;
	if (_ulSrcPageNo & 0x40)	/* ��Ҫ������ */
	{
		if ((n & 0x01) == 0)
		{
			n--;
		}
	}
	else	/* ��Ҫż���� */
	{
		if (n & 0x01)
		{
			n--;
		}
	}

	while (1)
	{
		if (NAND_IsFreeBlock(n))	/* �ǿ��п� */
		{
			return n;
		}

		if (n < 2)
		{
			return 0xFFFF;	/* û���ҵ����еĿ� */
		}
		n -= 2;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_IsBufOk
*	����˵��: �ж��ڴ滺�����������Ƿ�ȫ��Ϊָ��ֵ
*	��    ��:  - _pBuf : ���뻺����
*			       - _ulLen : ����������
*			       - __ucValue : ������ÿ����Ԫ����ȷ��ֵ
*	�� �� ֵ: 1 ��ȫ����ȷ�� 0 ������ȷ
*********************************************************************************************************
*/
 uint8_t NAND_IsBufOk(uint8_t *_pBuf, uint32_t _ulLen, uint8_t _ucValue)
{
	uint32_t i;

	for (i = 0; i < _ulLen; i++)
	{
		if (_pBuf[i] != _ucValue)
		{
			return 0;
		}
	}

	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_IsBadBlock
*	����˵��: ���ݻ����Ǽ��NAND Flashָ���Ŀ��Ƿ񻵿�
*	��    ��: _ulBlockNo ����� 0 - 4095 ������64M�ֽڣ�512 Page��NAND Flash����4096���飩added by sjw

������64M�ֽڣ�ÿҳ512 Page��NAND Flash����4096����,ÿ������32ҳ��
*	�� �� ֵ:  0   ���ÿ���ã� 
             1  ���ÿ��ǻ���
*********************************************************************************************************
*/
 uint8_t NAND_IsBadBlock(uint32_t _ulBlockNo)
{
	uint8_t ucFlag;

	/* ���NAND Flash����ǰ�Ѿ���עΪ�����ˣ������Ϊ�ǻ��� */
	FSMC_NAND_ReadSpare(&ucFlag, _ulBlockNo * NAND_BLOCK_SIZE, BI_OFFSET, 1);
	if (ucFlag != 0xFF)
	{
		return 1;
	}
	
	return 0;	/* �Ǻÿ� */
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_IsFreeBlock
*	����˵��: ���ݻ����Ǻ�USED��־����Ƿ���ÿ�
*	��    ��: _ulBlockNo ����������޸�Ϊ0-4095������64M�ֽڣ�32 Page��NAND Flash����4096���飩


*	�� �� ֵ: 1 ���ÿ���ã� 
            0 ���ÿ��ǻ��������ռ��
*********************************************************************************************************
*/

static uint8_t NAND_IsFreeBlock(uint32_t _ulBlockNo)
{
	uint8_t ucFlag;

	// ���NAND Flash����ǰ�Ѿ���עΪ�����ˣ������Ϊ�ǻ��� 
	if (NAND_IsBadBlock(_ulBlockNo))
	{
		return 0;
	}


	FSMC_NAND_ReadSpare(&ucFlag, _ulBlockNo * NAND_BLOCK_SIZE, USED_OFFSET, 1);
	if (ucFlag == 0xFF)
	{
		return 1;
	}
	return 0;
}



/*
*********************************************************************************************************
*	�� �� ��: NAND_ScanBlock
*	����˵��: ɨ�����NAND Flashָ���Ŀ�
*			��ɨ������㷨��
*			1) ��1���飨�������������ͱ����������������������Ƿ�ȫ0xFF, ��ȷ�Ļ��������ԸĿ飬����ÿ�
				�ǻ���,��������
*			2) ��ǰ��д��ȫ 0x00��Ȼ���ȡ��⣬��ȷ�Ļ��������ԸĿ飬�����˳�
*			3) �ظ��ڣ�2���������ѭ��������50�ζ�û�з���������ô�ÿ�����,�������أ�����ÿ��ǻ��飬
*				��������
*			��ע�⡿
*			1) �ú���������Ϻ󣬻�ɾ�������������ݣ�����Ϊȫ0xFF;
*			2) �ú������˲������������⣬Ҳ�Ա������������в��ԡ�
*			3) ��д����ѭ���������Ժ�ָ����#define BAD_BALOK_TEST_CYCLE 50
*	��    ��:  _ulPageNo ��ҳ�� 0 - 65535 ������128M�ֽڣ�2K Page��NAND Flash����1024���飩

                        ҳ�� 0 - 131071������64M�ֽڣ�512 Page��NAND Flash����4096���飩
*	�� �� ֵ: NAND_OK ���ÿ���ã� NAND_FAIL ���ÿ��ǻ���
*********************************************************************************************************
*/
uint8_t NAND_ScanBlock(uint32_t _ulBlockNo)
{
	uint32_t i, k;
	uint32_t ulPageNo;

	#if 0
	/* ���NAND Flash����ǰ�Ѿ���עΪ�����ˣ������Ϊ�ǻ��� */
	if (NAND_IsBadBlock(_ulBlockNo))
	{
		return NAND_FAIL;
	}
	#endif

	/* ����Ĵ��뽫ͨ��������������̵ķ�ʽ������NAND Flashÿ����Ŀɿ��� */
	memset(s_ucTempBuf, 0x00, NAND_PAGE_TOTAL_SIZE);
	for (i = 0; i < BAD_BALOK_TEST_CYCLE; i++)
	{
		/* ��1������������� */
		if (FSMC_NAND_EraseBlock(_ulBlockNo) != NAND_READY)
		{
			return NAND_FAIL;
		}

		/* ��2������������ÿ��page�����ݣ����ж��Ƿ�ȫ0xFF */
		ulPageNo = _ulBlockNo * NAND_BLOCK_SIZE;	/* ����ÿ��1��ҳ��ҳ�� */
		for (k = 0; k < NAND_BLOCK_SIZE; k++)
		{
			/* ������ҳ���� */
			FSMC_NAND_ReadPage(s_ucTempBuf, ulPageNo, 0, NAND_PAGE_TOTAL_SIZE);

			/* �жϴ洢��Ԫ�ǲ���ȫ0xFF */
			if (NAND_IsBufOk(s_ucTempBuf, NAND_PAGE_TOTAL_SIZE, 0xFF) == 0)
			{
				return NAND_FAIL;
			}

			ulPageNo++;		/* ����д��һ��ҳ */
		}

		/* ��2����дȫ0���������ж��Ƿ�ȫ0 */
		ulPageNo = _ulBlockNo * NAND_BLOCK_SIZE;	/* ����ÿ��1��ҳ��ҳ�� */
		for (k = 0; k < NAND_BLOCK_SIZE; k++)
		{
			/* ���buf[]������Ϊȫ0,��д��NAND Flash */
			memset(s_ucTempBuf, 0x00, NAND_PAGE_TOTAL_SIZE);
			if (FSMC_NAND_WritePage(s_ucTempBuf, ulPageNo, 0, NAND_PAGE_TOTAL_SIZE) != NAND_OK)
			{
				return NAND_FAIL;
			}

			/* ������ҳ����, �жϴ洢��Ԫ�ǲ���ȫ0x00 */
			FSMC_NAND_ReadPage(s_ucTempBuf, ulPageNo, 0, NAND_PAGE_TOTAL_SIZE);
			if (NAND_IsBufOk(s_ucTempBuf, NAND_PAGE_TOTAL_SIZE, 0x00) == 0)
			{
				return NAND_FAIL;
			}

			ulPageNo++;		/* ����һ��ҳ */
		}
	}

	/* ���һ�������������� */
	if (FSMC_NAND_EraseBlock(_ulBlockNo) != NAND_READY)
	{
		return NAND_FAIL;
	}
	ulPageNo = _ulBlockNo * NAND_BLOCK_SIZE;	/* ����ÿ��1��ҳ��ҳ�� */
	for (k = 0; k < NAND_BLOCK_SIZE; k++)
	{
		/* ������ҳ���� */
		FSMC_NAND_ReadPage(s_ucTempBuf, ulPageNo, 0, NAND_PAGE_TOTAL_SIZE);

		/* �жϴ洢��Ԫ�ǲ���ȫ0xFF */
		if (NAND_IsBufOk(s_ucTempBuf, NAND_PAGE_TOTAL_SIZE, 0xFF) == 0)
		{
			return NAND_FAIL;
		}

		ulPageNo++;		/* ����д��һ��ҳ */
	}

	return NAND_OK;

}

/*
*********************************************************************************************************
*	�� �� ��: NAND_MarkUsedBlock
*	����˵��: ���NAND Flashָ���Ŀ�Ϊ���ÿ�
*	��    ��: _ulBlockNo ����� 0-4095 ������128M�ֽڣ�2K Page��NAND Flash����1024���飩
*	�� �� ֵ: NAND_OK:��ǳɹ��� NAND_FAIL�����ʧ�ܣ��ϼ����Ӧ�ý��л��鴦��
*********************************************************************************************************
*/
static uint8_t NAND_MarkUsedBlock(uint32_t _ulBlockNo)
{
	uint32_t ulPageNo;
	uint8_t ucFlag;

	/* �����ĵ�1��ҳ�� */
	ulPageNo = _ulBlockNo * NAND_BLOCK_SIZE;	/* ����ÿ��1��ҳ��ҳ�� */

	/* ���ڵ�1��page�������ĵ�USED_OFFSET���ֽ�д���0xFF���ݱ�ʾ���ÿ� */
	ucFlag = NAND_USED_BLOCK_FLAG;
	if (FSMC_NAND_WriteSpare(&ucFlag, ulPageNo, USED_OFFSET, 1) == NAND_FAIL)
	{
		/* ������ʧ�ܣ�����Ҫ��ע�����Ϊ���� */
		return NAND_FAIL;
	}
	return NAND_OK;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_MarkBadBlock
*	����˵��: ���NAND Flashָ���Ŀ�Ϊ����
*	��    ��: _ulBlockNo ����� 0 - 1023 ������128M�ֽڣ�2K Page��NAND Flash����1024���飩
*	�� �� ֵ: �̶�NAND_OK
*********************************************************************************************************
*/
static void NAND_MarkBadBlock(uint32_t _ulBlockNo)
{
	uint32_t ulPageNo;
	uint8_t ucFlag;

	///printf_err("NAND_MarkBadBlock(%d)\r\n", _ulBlockNo);

	/* �����ĵ�1��ҳ�� */
	ulPageNo = _ulBlockNo * NAND_BLOCK_SIZE;	/* ����ÿ��1��ҳ��ҳ�� */

	/* ���ڵ�1��page�������ĵ�BI_OFFSET���ֽ�д���0xFF���ݱ�ʾ���� */
	ucFlag = NAND_BAD_BLOCK_FLAG;
	if (FSMC_NAND_WriteSpare(&ucFlag, ulPageNo, BI_OFFSET, 1) == NAND_FAIL)
	{
		/* �����1��ҳ���ʧ�ܣ����ڵ�2��ҳ��� */
		FSMC_NAND_WriteSpare(&ucFlag, ulPageNo + 1, BI_OFFSET, 1);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_ScanAllBadBlock
*	����˵��: ɨ��������е�BLOCK, ����ǻ��飬����������
*	��    ��: _ulBlockNo ����� 0 - 1023 ������128M�ֽڣ�2K Page��NAND Flash����1024���飩
*	�� �� ֵ: �̶�NAND_OK
*********************************************************************************************************
*/
void NAND_ScanAllBadBlock(void)
{
	uint32_t i;
	
	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
		if (NAND_ScanBlock(i) == NAND_OK)
		{
			printf("Scan Block %d (%d%%), Ok\r\n", i, i * 100 / NAND_BLOCK_COUNT);
		}
		else
		{
			printf("Scan Block %d (%d%%), Err\r\n", i, i * 100 / NAND_BLOCK_COUNT);
			NAND_MarkBadBlock(i);
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_Format
*	����˵��: NAND Flash��ʽ�����������е����ݣ��ؽ�LUT
*	��    ��:  ��
*	�� �� ֵ: NAND_OK : �ɹ��� NAND_Fail ��ʧ�ܣ�һ���ǻ����������ർ�£�
*********************************************************************************************************
*/
uint8_t NAND_Format(void)
{
	uint16_t i, n;

		
	/* ����ÿ���� */
	usGoodBlockCount = 0;
	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{		
		/* ����Ǻÿ飬����� */
		if (!NAND_IsBadBlock(i))
		{
			FSMC_NAND_EraseBlock(i);
			usGoodBlockCount++;
		}
	}

	/* ����ÿ����������100����NAND Flash���� */
	if (usGoodBlockCount < 100)
	{
		return NAND_FAIL;
	}

	usGoodBlockCount = (usGoodBlockCount * 98) / 100;	/* 98%�ĺÿ����ڴ洢���� */

	/* ��������һ�� */
	n = 0; /* ͳ���ѱ�ע�ĺÿ� */
	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
		if (!NAND_IsBadBlock(i))
		{
			/* ����Ǻÿ飬���ڸÿ�ĵ�1��PAGE��LBN0 LBN1��д��nֵ (ǰ���Ѿ�ִ���˿������ */
			if (FSMC_NAND_WriteSpare((uint8_t *)&n, i * NAND_BLOCK_SIZE, LBN0_OFFSET, 2) != NAND_OK)
			{
				return NAND_FAIL;
			}
			n++;

			/* ���㲢д��ÿ��������ECCֵ ����ʱδ����*/
			if (n == usGoodBlockCount)
			{
				break;
			}
		}
	}

	NAND_BuildLUT();	/* ��ʼ��LUT�� */
	return NAND_OK;
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_FormatCapacity
*	����˵��: NAND Flash��ʽ�������Ч����. (���֧��4G)
*	��    ��:  ��
*	�� �� ֵ: NAND_OK : �ɹ��� NAND_Fail ��ʧ�ܣ�һ���ǻ����������ർ�£�
*********************************************************************************************************
*/
uint32_t NAND_FormatCapacity(void)
{
	uint16_t usCount;

	/* �������ڴ洢���ݵ����ݿ��������������Ч������98%������ */
	usCount = (s_usValidDataBlockCount * DATA_BLOCK_PERCENT) / 100;

	return (usCount * NAND_BLOCK_SIZE * NAND_PAGE_SIZE);
}

uint16_t See;

uint16_t bad_no[4096];//һ�������Ϊ16K  ���Ƕ��ڴ�K9F1208U0B��˵�ģ�added by sjw

/*
*********************************************************************************************************
*	�� �� ��: NAND_OutBadBlockInfo
*	����˵��: ͨ�����ڴ�ӡ��NAND Flash�Ļ�����Ϣ
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void NAND_OutBadBlockInfo(void)
{
	uint32_t id;
	uint32_t i;
	uint32_t n;
	uint32_t used = 0;
	uint8_t j,k,temp;
	uint32_t count=0;
	uint8_t buf[6];
		

//http://www.doc88.com/p-3814240407326.html
//http://www.doc88.com/p-3814240407326.html  �����ڴ泧���������ڴ�оƬ����added by sjw


	id = NAND_ReadID();
	
	printf("NAND Flash ID = 0x%04X, Type = ", id);
	if (id == HY27UF081G2A)
	{
		printf("HY27UF081G2A\r\n  1024 Blocks, 64 pages per block, 2048 + 64 bytes per page\r\n");
	}
	else if (id == K9F1G08U0A)
	{
		printf("K9F1G08U0A\r\n  1024 Blocks, 64 pages per block, 2048 + 64 bytes per page\r\n");
	}
	else if (id == K9F1G08U0B)
	{
		printf("K9F1G08U0B\r\n  1024 Blocks, 64 pages per block, 2048 + 64 bytes per page\r\n");
	}
	else if (id == H27U4G8F2DTR)
	{
		printf("H27U4G8F2DTR\r\n  4096 Blocks, 64 pages per block, 2048 + 64 bytes per page\r\n");
	}
	else if (id == DF2M8HM)
	{
		printf("DF2M8HM-T\r\n  4096 Blocks, 32 pages per block, 512 + 16 bytes per page\r\n");
	}
	else if (id == K9F1208U0B)
	{
		printf("K9F1208U0B\r\n  4096 Blocks, 32 pages per block, 512 + 16 bytes per page\r\n");
   }
	else if (id == K9F1208U0C)
	{
		printf("K9F1208U0C\r\n  4096 Blocks, 32 pages per block, 512 + 16 bytes per page\r\n");
   }

	else
	{
		printf("unkonow\r\n");
		return;
	}
	
	
	

	FSMC_NAND_Reset();
	n = 0;	  /* ����ͳ�� */
	used = 0; /* ���ÿ�ͳ�� */
	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
		if (NAND_IsBadBlock(i))
		{
			if (n < sizeof(bad_no) / 2)
			{
				bad_no[n] = i;	/* ��¼����� */
			}
			n++;
		}else{
			if (NAND_IsFreeBlock(i))
			{
				printf("0");	//���ÿ�
			}
			else
			{
				printf("-");	// ���ÿ� 
				used++;
			}
		}
		
		
		

		if (((i + 1) % 8) == 0)
		{	
			printf("* ");		
		}

		if (((i + 1) % 64) == 0)
		{	
			printf("\r\n");		
		}
	}
	
	
	
	if (id == K9F1G08U0B)//added by sjw for it!
	{
		
		printf("Bad Block Count = %d  ( < 80 is OK), Used = %d \r\n", n, used);
		
	}else if (id == K9F1208U0B)//added by sjw for it!
	{
		
		printf("Bad Block Count = %d  ( < 80 is OK), Used = %d \r\n", n, used);
		
	}
	else if (id == K9F1208U0C)//added by sjw for it!
	{
		
		printf("Bad Block Count = %d  ( < 80 is OK), Used = %d \r\n", n, used);
		
	}
	else
	{
		
		printf("Bad Block Count = %d\r\n", n);
	
	}
	
	
	
	
	
	
	
	printf("Bad Block Count = %d\r\n", n);	
	See=sizeof(bad_no);
	
	
	/* ��ӡ������� */
	if (n > 0)//��������Ŀ飬ͬʱ������
	{
		for (i = 0; i < n; i++)
		{		
			printf("%4d ",  bad_no[i]);
			
			/*
			if(do_erase_nandflash(bad_no[i])==0x40)// �����ɹ�
			{	
					printf("������%d����ɹ�! \r\n",bad_no[i]);
			}else
					printf("������%d����ʧ��!\r\n",bad_no[i]);
			*/
			
					
		}
		printf("\r\n\r\n");
		
	}
	
	
	printf("\r\n");
	
	
	
	
	
	#if 0	
  for (i = 0; i < NAND_BLOCK_COUNT; i++)//0---4095 �˶γ����ǲ��Կ�ĵ�0ҳ���Ƿ񱻳��Ҽ�¼���飡��
	{

				FSMC_NAND_ReadSpare(OOBData, i * NAND_BLOCK_SIZE, 0, VALID_SPARE_SIZE);		   			
				if(OOBData[BI_OFFSET]!=0xff)
				{			
					printf("ԭʼоƬ�л��飬�����ǹ�˾�����˱�ע���ڿ�%d��\r\n",i);
					for(k=0;k<NAND_SPARE_AREA_SIZE;k++)
						printf("%#x ",OOBData[k]);
					printf("\r\n");
				}					
				
	}
	
	
	
	for (i = 0; i < NAND_BLOCK_COUNT* NAND_BLOCK_SIZE; i++)//0---131072�˶γ����ǲ���ÿһ��ҳ���Ƿ񱻳��Ҽ�¼���飡��
	{

				FSMC_NAND_ReadSpare(OOBData, i, 0, NAND_SPARE_AREA_SIZE);   
				if(OOBData[5]!=0xff)
				{
					count++;
					printf("ԭʼоƬ�л��飬�����ǹ�˾�����˱�ע����ҳ��Ϊ%dҳ��\r\n",i);
					for(k=0;k<NAND_SPARE_AREA_SIZE;k++)
						printf("%#x ",OOBData[k]);
					printf("\r\n");
				}					
				
	}
	
	
	
	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
			FSMC_NAND_ReadSpare(buf, i * NAND_BLOCK_SIZE, 0, VALID_SPARE_SIZE);
		  for(j=0;j<VALID_SPARE_SIZE;j++)
				printf("%02x ",buf[j]);
		  printf("\r\n");
	}
	
	#endif
	
	
	
	
	
	
	
}





//�ҽ��в���һ��д����ж����ݣ������Ƿ�ɹ�������2007�����е�3��page��column=0ʱ��ʼд�����ݣ�д��512�����ݣ�֮���ٴӴ�page����ȡ���ݣ������Ƿ���ȷ��
//�˺����Ĺ���Ϊ���� ��xҳ���Ѽ��������ϵ������Ƕ��٣�ע�ⲻ�ǿ�����������������added by sjw
void DemoTestDisFatfsHex(uint8_t *psector)
{
	 //uint32_t select_page_addr;//�ӵ�0ҳ�ϵ���131072ҳ��!!!
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
	   TestMyTxBuffer[i]=i;
		 TestMyRxBuffer[i]=0x00;
	}
	
	
	//do_erase_nandflash(1060);
	
	/*
	
//	do_erase_nandflash(0);
//	do_erase_nandflash(2007);//������2007���飡�������������
//	do_erase_nandflash(2013);
//	do_erase_nandflash(2014);
//	do_erase_nandflash(2047);
//	do_erase_nandflash(4095);
//	
	
	//select_page_addr=(2007>>9)+3;
	//select_page_addr=(2007<<5)+0;  //0xfae3
	//select_page_addr=(2013<<5)+31; //������2013���飬�����page�ĵ�31��ҳ��д���ݣ�Ҳ���Ǿ���ҳ��0xFBC0+30=0xFBE0
	
	
	
	
	select_page_addr=(uint32_t)(3899<<5)+0;
	
	
	
	if (FSMC_NAND_WritePage(TestMyTxBuffer,sector, 0, NAND_PAGE_SIZE) != NAND_OK)
		printf("д����󣡣�\r\n");
	else
		printf("д����ȷ����\r\n");
	*/
	
	
	
	
	
	OS_ENTER_CRITICAL();
	printf("******************************************************************\r\n");
	//FSMC_NAND_ReadPage(TestMyRxBuffer,64224,0,NAND_PAGE_TOTAL_SIZE);//select_page_addr   64227//
	//FSMC_NAND_ReadPage(TestMyRxBuffer,64447,0,NAND_PAGE_TOTAL_SIZE);
	//FSMC_NAND_ReadPage(TestMyRxBuffer,64448,0,NAND_PAGE_TOTAL_SIZE);
	//FSMC_NAND_ReadPage(TestMyRxBuffer,64447,0,NAND_PAGE_TOTAL_SIZE);
	 // FSMC_NAND_ReadPage(TestMyRxBuffer,131072,0,NAND_PAGE_TOTAL_SIZE);
	//	FSMC_NAND_ReadPage(TestMyRxBuffer,131040,0,NAND_PAGE_TOTAL_SIZE);
	//FSMC_NAND_ReadPage(TestMyRxBuffer,0,0,NAND_PAGE_TOTAL_SIZE);
	//FSMC_NAND_ReadPage(TestMyRxBuffer,0,0,NAND_PAGE_TOTAL_SIZE);
	//FSMC_NAND_ReadPage(TestMyRxBuffer,124768,0,NAND_PAGE_TOTAL_SIZE);
	
	
	//for(j=0;j<21;j++)
	{
			//FSMC_NAND_ReadPage(TestMyRxBuffer,sector,0,NAND_PAGE_TOTAL_SIZE);
		  FSMC_NAND_ReadPage(TestMyRxBuffer,sector,0,NAND_PAGE_SIZE);
			
		  //for(i = 0; i < NAND_PAGE_TOTAL_SIZE;  i++)
			for(i = 0; i < NAND_PAGE_SIZE;  i++)
			{	
				if(i%32==0){
					printf("\r\n");
					printf("%#x ",TestMyRxBuffer[i]);
				}else
					printf("%#x ",TestMyRxBuffer[i]);
			}
			printf("******************************************************************\r\n");
	}
	OS_EXIT_CRITICAL();
	
	
	
	
	
	/*
	FSMC_NAND_ReadPage(TestMyRxBuffer,0,0,528);
	
	
	for(i = 0; i < NAND_PAGE_TOTAL_SIZE;  i++)
	{	
		if(i%32==0){
			printf("\r\n");
			printf("%#x ",TestMyRxBuffer[i]);
		}else
			printf("%#x ",TestMyRxBuffer[i]);
	}
	printf("*********************************\r\n");
	
	
	
	FSMC_NAND_ReadPage(TestMyRxBuffer,2,0,528);
	
	for(i = 0; i < NAND_PAGE_TOTAL_SIZE;  i++)
	{	
		if(i%32==0){
			printf("\r\n");
			printf("%#x ",TestMyRxBuffer[i]);
		}else
			printf("%#x ",TestMyRxBuffer[i]);
	}
	printf("*********************************\r\n");
	
	FSMC_NAND_ReadPage(TestMyRxBuffer,3,0,528);
	
	for(i = 0; i < NAND_PAGE_TOTAL_SIZE;  i++)
	{	
		if(i%32==0){
			printf("\r\n");
			printf("%#x ",TestMyRxBuffer[i]);
		}else
			printf("%#x ",TestMyRxBuffer[i]);
	}
	printf("*********************************\r\n");
*/


}





















/*�����ʽ���£�

��Ʒ�ڲ�Flash��СΪ��512K�ֽڣ� 	 www.armjishu.com

K9F1G08U0B
  1024 Blocks, 64 pages per block, 2048 + 64 bytes per page
0------- -------- -------- -------- -------- -------- -------- -------- 
------- -------- -------- -------- -------- -------- -------- -------- 
-------- -------- -------- -------- -------- ------- -------- -------- 
-------- -------- -------- -------- -------- -------- 0------- -------- 
--000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 0000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 -0-000-0 
Bad Block Count = 4  ( < 80 is OK), Used = 257 
  67  173  443  598 

Bad Block Count = 4


*/




/******************************************************************************
* Function Name  : FSMC_NAND_WriteSmallPage
* Description    : This routine is for writing one or several 512 Bytes Page size.
* Input          : - pBuffer: pointer on the Buffer containing data to be written   
*                  - Address: First page address
*                  - NumPageToWrite: Number of page to write  
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate 
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation 
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
* Attention		 : None
*******************************************************************************/
//ҳд������    ��Ϊÿ��ҳ��page���ɷ�ΪA��B��C������  ����ҳд��Ҳ��Ϊ���ַ�ʽ�� 
//����������õĵ�һ�ַ�ʽ������д��0~528byte�����ݡ�K9F1208����Сҳ��NAND��512byte+16byte���������ڴ�ҳ��NAND��2048byte+64byte�� 
uint32_t FSMC_NAND_WriteSmallPage(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite)
{
  uint32_t index = 0x00, numpagewritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
  uint32_t status = NAND_READY, size = 0x00;

  while((NumPageToWrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
  {
    /* Page write command and address */
    /* ҳд����͵�ַ */ 
    NAND_CMD_AREA = NAND_CMD_AREA_A;  //��������00H��������0x70010000����A����ʼд�� 
    NAND_CMD_AREA = NAND_CMD_WRITE0;  //��������80H��������0x70010000 
    NAND_ADDR_AREA = 0x00;  //���͵�ַA0~A7����ַ��0x70020000���ӵ�ַ0��ʼд��   
    NAND_ADDR_AREA = ADDR_1st_CYCLE(ROW_ADDRESS); //���͵�ַA9~A16����ַ��0x70020000   
    NAND_ADDR_AREA = ADDR_2nd_CYCLE(ROW_ADDRESS);  //���͵�ַA17~A24����ַ��0x70020000   
    NAND_ADDR_AREA = ADDR_3rd_CYCLE(ROW_ADDRESS);  //���͵�ַA25����ַ��0x70020000   
		
    /* Calculate the size */   /* ����д�����ݵĴ�С */ 
    size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpagewritten);
		
		/* д������ */ 
    for(; index < size; index++) 
    { 
      NAND_DATA_AREA = pBuffer[index];  //�������ݵ�������0x70000000 
			//NAND_CMD_AREA	;
			//NAND_ADDR_AREA;
    } 
		  /* ��æ�� */
    while( GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0 );
   
		/* ���״̬���Ƿ�����ɹ� */ 
    status = FSMC_NAND_GetStatus(); 
     
    if(status == NAND_READY)  //���������� 
    { 
      numpagewritten++;  //��д��ҳ����1 
      NumPageToWrite--;  //��д��ҳ����1 
      /* ����Ҫд�����һ��Сҳ�ĵ�ַ */ 
      //addressstatus = FSMC_NAND_AddressIncrement(&Address);     
    }
  }
  
  return (status | addressstatus);
}



   
  //ҳ�������������00H�������Ҫ�����ҳ��ַ��Ȼ��Ϳ��Զ������528byte�������ˡ�
u32 FSMC_NAND_ReadSmallPage(u8 *pBuffer, NAND_ADDRESS Address, u32 NumPageToRead) 
{ 
  u32 index = 0x00, numpageread = 0x00, addressstatus = NAND_VALID_ADDRESS; 
  u32 status = NAND_READY, size = 0x00; 
  
	while((NumPageToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS)) 
  {     
    /* ҳ�������ҳ��ַ*/ 
    NAND_CMD_AREA = NAND_CMD_AREA_A;   //��������00H��������0x70010000 
    
     NAND_ADDR_AREA = 0x00;  //���͵�ַA0~A7��00H������ַ��0x70020000 
     NAND_ADDR_AREA=  ADDR_1st_CYCLE(ROW_ADDRESS); //���͵�ַA9~A16����ַ��0x70020000  
     NAND_ADDR_AREA = ADDR_2nd_CYCLE(ROW_ADDRESS);  //���͵�ַA17~A24����ַ��0x70020000  
     NAND_ADDR_AREA = ADDR_3rd_CYCLE(ROW_ADDRESS);   //���͵�ַA25����ַ��0x70020000 
      
    /* ����Ҫ�������ݴ�С */ 
    size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpageread); 
     
    /* �����ݵ�pBuffer */     
    for(; index < size; index++) 
    { 
      pBuffer[index]= NAND_DATA_AREA;  //��������0x70000000�������� 
    } 
    numpageread++;  //�Ѷ���ҳ����1 
     
    NumPageToRead--;  //������ҳ����1 
    /* ������һ��Ҫ����ҳ��ַ */                
    //addressstatus = FSMC_NAND_AddressIncrement(&Address); 
  } 
  /* ���״̬���Ƿ�����ɹ� */ 
  status = FSMC_NAND_GetStatus(); 
   
  return (status | addressstatus); 
} 



/*

    // ��ʼ��Ҫд��NAND��ҳ��ַ  
    WriteReadAddr.Zone = 0x00; 
    WriteReadAddr.Block = 0x00; 
    WriteReadAddr.Page = 0x00;  
     
    status = FSMC_NAND_EraseBlock(WriteReadAddr); //����NAND FLASH�ĵ�һ���飨��1�͵�2ҳ���ڵĿ飩 
    //д���ݵ�NAND FLASH�ĵ�1�͵�2ҳ  
    // ���Ҫ���͵����ݵ�buffer  
    
 */    
   
	
   












































/*
*********************************************************************************************************
*	�� �� ��: NAND_DispPhyPageData
*	����˵��: ͨ�����ڴ�ӡ��ָ��ҳ�����ݣ�2048+64��
*	��    ��: _uiPhyPageNo �� ����ҳ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void NAND_DispPhyPageData(uint32_t _uiPhyPageNo)
{
	uint32_t i, n;
	uint32_t ulBlockNo;
	uint16_t usOffsetPageNo;

	ulBlockNo = _uiPhyPageNo / NAND_BLOCK_SIZE;		    /* ��������ҳ�ŷ��ƿ�� */
	usOffsetPageNo = _uiPhyPageNo % NAND_BLOCK_SIZE;	/* ��������ҳ�ż�������ҳ���ڿ���ƫ��ҳ�� */

	if (NAND_OK != FSMC_NAND_ReadPage(s_ucTempBuf, _uiPhyPageNo, 0, NAND_PAGE_TOTAL_SIZE))
	{
//		printf("FSMC_NAND_ReadPage Failed() \r\n");
		return;
	}

//	printf("Block = %d, Page = %d\r\n", ulBlockNo, usOffsetPageNo);

	/* ��ӡǰ�� 2048�ֽ����ݣ�ÿ512�ֽڿ�һ�� */
	for (n = 0; n < 4; n++)
	{
		for (i = 0; i < 512; i++)
		{
//			printf(" %02X", s_ucTempBuf[i + n * 512]);

			if ((i & 31) == 31)
			{
//				printf("\r\n");	/* ÿ����ʾ32�ֽ����� */
			}
			else if ((i & 31) == 15)
			{
//				printf(" - ");
			}
		}
//		printf("\r\n");
	}

	/* ��ӡǰ�� 2048�ֽ����ݣ�ÿ512�ֽڿ�һ�� */
	for (i = 0; i < 64; i++)
	{
//		printf(" %02X", s_ucTempBuf[i + 2048]);

		if ((i & 15) == 15)
		{
//			printf("\r\n");	/* ÿ����ʾ32�ֽ����� */
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_DispLogicPageData
*	����˵��: ͨ�����ڴ�ӡ��ָ��ҳ�����ݣ�512+16��
*	��    ��: _uiLogicPageNo �� �߼�ҳ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void NAND_DispLogicPageData(uint32_t _uiLogicPageNo)
{
	uint32_t uiPhyPageNo;
	uint16_t usLBN;	/* �߼���� */
	uint16_t usPBN;	/* ������ */
	static  uint8_t sjw;
	
	
	//sjw=_uiLogicPageNo % NAND_BLOCK_SIZE;(������������ȷ�ģ�����ҳ99741%32������Ϊ29����ʾ��3116�����ϵ�ƫ�Ƶ�29ҳ�Ͽ�ʼ��ʾ���ݣ�added by sjw)

	usLBN = _uiLogicPageNo / NAND_BLOCK_SIZE;
	usPBN = NAND_LBNtoPBN(usLBN);	/* ��ѯLUT���������� */
	if (usPBN >= NAND_BLOCK_COUNT)
	{
		/* û�и�ʽ����usPBN = 0xFFFF */
		return;
	}

//	printf("LogicBlock = %d, PhyBlock = %d\r\n", _uiLogicPageNo, usPBN);

	/* ��������ҳ�� */
	uiPhyPageNo = usPBN * NAND_BLOCK_SIZE + _uiLogicPageNo % NAND_BLOCK_SIZE;
	NAND_DispPhyPageData(uiPhyPageNo);	/* ��ʾָ��ҳ���� */
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_ReadONFI
*	����˵��: ��NAND Flash��ONFI��Ϣ,  ��� H27U4G8F2DTR
*	��    ��: _pBuf ��Ž���Ļ�����, ��С4�ֽڡ�Ӧ�ù̶����� "ONFI" �ַ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void NAND_ReadONFI(uint8_t *_pBuf)
{
	uint16_t i;

	/* �������� Command to the command area */
	NAND_CMD_AREA = 0x90;
	NAND_ADDR_AREA = 0x20;

	/* �����ݵ�������pBuffer */
	for(i = 0; i < 256; i++)
	{
		_pBuf[i] = NAND_DATA_AREA;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: NAND_ReadParamPage
*	����˵��: Read Parameter Page,  ��� H27U4G8F2DTR
*	��    ��: _pData ��Ž���Ļ�������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void NAND_ReadParamPage(PARAM_PAGE_T *_pData)
{
	uint16_t i;
	uint8_t *_pBuf = (uint8_t *)_pData;

	/* �������� Command to the command area */
	NAND_CMD_AREA = 0xEC;
	NAND_ADDR_AREA = 0x00;

	 /* ����ȴ���������������쳣, �˴�Ӧ���жϳ�ʱ */
	for (i = 0; i < 20; i++);
	while( GPIO_ReadInputDataBit(NAND_NWAIT_PORT, NAND_NWAIT_PIN) == 0);

	/* �����ݵ�������pBuffer */
	for(i = 0; i < 256; i++)
	{
		_pBuf[i] = NAND_DATA_AREA;
	}

}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

uint32_t FlashWriteOneSector(uint32_t Addr, uint8_t * pBuf, uint32_t Remain)
{
	return 0;
}

uint32_t FlashReadOneSector(uint32_t Addr, uint8_t * pBuf, uint32_t Remain)
{
	return 0;
}





/*
*********************************************************************************************************
*	�� �� ��: NAND_DispParamPage
*	����˵��: ͨ�����ڴ�ӡ Parameter Page Data Structure Definition (����ҳ���ݽṹ) ��� H27U4G8F2DTR
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void NAND_DispParamPage(void)
{
	PARAM_PAGE_T tPage;
	char buf[32];

	FSMC_NAND_Reset();

	NAND_ReadParamPage(&tPage);

#if 0
	uint8_t Sign[4];		/* = "ONFI" */
	uint16_t Revision; 		/* Bit1 = 1 ��ʾ֧�� ONFI Ver 1.0 */
	uint16_t Features;		/* */
	uint16_t OptionalCommands;
#endif

//	printf("\r\n");
//	printf("Read Parameter Page Data :\r\n");
//	printf("Sign = %c%c%c%c\r\n", tPage.Sign[0], tPage.Sign[1], tPage.Sign[2], tPage.Sign[3]);
//	printf("Revision = %04X\r\n", tPage.Revision);
//	printf("Features = %04X\r\n", tPage.Features);
//	printf("OptionalCommands = %04X\r\n", tPage.OptionalCommands);

	/* Manufacturer information block */
	memcpy(buf, tPage.Manufacturer, 12);
	buf[12] = 0;
//	printf("Manufacturer = %s\r\n", buf);	/* ������ */

	memcpy(buf, tPage.Model, 20);
	buf[20] = 0;
//	printf("Model = %s\r\n", buf);	/* �ͺ� */

//	printf("JEDEC_ID = %02X\r\n", tPage.JEDEC_ID);	/* AD */
///	printf("DateCode = %04X\r\n", tPage.DateCode);

#if 0
	/* Memory organization block */
	uint32_t PageDataSize;
	uint16_t PageSpareSize;
	uint32_t PartialPageDataSize;
	uint16_t PartialPageSpareSize;
	uint32_t BlockSize;
	uint32_t LogicalUnitSize;
	uint8_t LogicalUnitNumber;
	uint8_t AddressCycles;
	uint8_t CellBits;
	uint16_t BadBlockMax;
	uint16_t BlockEndurance;
	uint8_t ValidBlocksBegin;	/* ��ǰ�汣֤��Ч�Ŀ���� */
	uint16_t BlockEndurance2;	/* Block endurance for guaranteed valid blocks */
	uint8_t  ProgramsPerPage;	/* Number of programs per page */
	uint8_t PartialProgram;
	uint8_t ECCcorrectBits;
	uint8_t InterleavedAddrBits;	/* ����ĵ�ַλ */
	uint8_t InterleavedOperaton;
	uint8_t Rsv3[13];
#endif

////	printf("\r\n");

}


/********************************************************************
�������ܣ���FLASH���ض�λ�ü��ػ����
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void FlashLoadBadBlockTable(void)
{
 uint32_t i,j,k,Sum,Ok;
 uint8_t Data;

 Ok=0; //����Ϊ���ɹ�
	
	/*
 for(i=0;i<FLASH_BLOCKS_TABLE;i++) //����û��׼�������Ŀ�
 {
  //�Ӹÿ������һҳ���ص�һ�ֽڣ����Ƿ�Ϊ0xFF�����Ϊ0xFF����ʾ�ÿ�û��׼������
  FlashWriteCommand(0x00);
  FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*(i+1) - FLASH_PAGE_SIZE);
  FlashWriteCommand(0x30);
  FlashWait(); //�ȴ����ݶ���
  Data = FlashReadDataByte();
  if(Data==0xFF)  //��ʾ�ÿ����ݻ�δ׼������
  {
   //�Ӹÿ��е����ڶ�ҳ���ص�һ�ֽڣ����Ƿ�Ϊ0�����Ϊ0����ʾ�ÿ��Ѿ�д��������
   FlashWriteCommand(0x00);
   FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*(i+1) - 2*FLASH_PAGE_SIZE);
   FlashWriteCommand(0x30);
   FlashWait(); //�ȴ����ݶ���
   Data = FlashReadDataByte();
   if(Data==0) //��ʾ������Ч
   {
    Data = FlashReadDataByte(); //����У���
    Sum=Data;
    Data = FlashReadDataByte(); //����У���
    Sum=(Sum<<8)+Data;
    Data = FlashReadDataByte();//����У���
    Sum=(Sum<<8)+Data;
    Data = FlashReadDataByte();//����У���
    Sum=(Sum<<8)+Data;
    //�Ӹÿ鿪ʼλ�ö�
    FlashWriteCommand(0x00);
    FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*i);
    FlashWriteCommand(0x30);
    FlashWait(); //�ȴ����ݶ���
    //����1�ֽ��Ƿ�Ϊ0
    Data = FlashReadDataByte();
    if(Data!=0)continue;
    //����2�ֽ��Ƿ�Ϊ0x55
    Data = FlashReadDataByte();
    if(Data!=0x55)continue;
    //����3�ֽ��Ƿ�Ϊ0xAA
    Data = FlashReadDataByte();
    if(Data!=0xAA)continue;
    //����4�ֽ��Ƿ�Ϊ0xFF
    Data = FlashReadDataByte();
    if(Data!=0xFF)continue;
    Sum+=0x1FE;
    
    //����������
    Data = FlashReadDataByte();
    FlashBadBlocksCount=Data;
    Sum+=Data;
    Data = FlashReadDataByte();
    FlashBadBlocksCount=(FlashBadBlocksCount<<8)+Data;
    Sum+=Data;
    Data = FlashReadDataByte();
    FlashBadBlocksCount=(FlashBadBlocksCount<<8)+Data;
    Sum+=Data;
    Data = FlashReadDataByte();
    FlashBadBlocksCount=(FlashBadBlocksCount<<8)+Data;
    Sum+=Data;
    j=8;
    //���ػ����
    for(k=0;k<sizeof(FlashBadBlockTable[0][0])*FLASH_BAD_BLOCKS_REMAP*2;k++)
    {
     if(0==(j&(FLASH_PAGE_SIZE-1))) //���������ҳ������Ҫ���¶���ҳ
     {
      FlashWriteCommand(0x00);
      FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*i+j);
      FlashWriteCommand(0x30);
      FlashWait(); //�ȴ����ݶ���
     }
     Data = FlashReadDataByte();
     Sum+=Data; //��У���
     ((uint8_t *)FlashBadBlockTable)[k]=Data;  //����һ�ֽڵ��������
     j++;
    }
    //������Ӱ������״̬��
    for(k=0;k<sizeof(FlashRemapBlockStatus[0])*FLASH_BAD_BLOCKS_REMAP;k++)
    {
     if(0==(j&(FLASH_PAGE_SIZE-1))) //���������ҳ������Ҫ���¶���ҳ
     {
      FlashWriteCommand(0x00);
      FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*i+j);
      FlashWriteCommand(0x30);
      FlashWait(); //�ȴ����ݶ���
     }
     Data = FlashReadDataByte();
     Sum+=Data; //��У���
     ((uint8_t *)FlashRemapBlockStatus)[k]=Data;   //����һ�ֽڵ���Ӱ����״̬����
     j++;
    }
    if(Sum==0) //���У��ɹ�����˵��������ȷ
    {
     Ok=0xFF; //����Ϊ�ɹ�
     break;   //���˳�ѭ��
    }
   }
  }
 }
 
 if(Ok==0) //�������д��ı����Ҳ����õĻ������ȥ׼����������ȥ��
 {
  for(i=0;i<FLASH_BLOCKS_TABLE;i++) //����׼�������Ŀ�
  {
   //�Ӹÿ������һҳ���ص�һ�ֽڣ����Ƿ�Ϊ0�����Ϊ0����ʾ�ÿ��Ѿ�׼��������
   FlashWriteCommand(0x00);
   FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*(i+1) - FLASH_PAGE_SIZE);
   FlashWriteCommand(0x30);
   FlashWait(); //�ȴ����ݶ���
   Data = FlashReadDataByte();
   if(Data==0x00)  //��ʾ�ÿ�����׼������
   {
    //�Ӹÿ��е����ڶ�ҳ���ص�һ�ֽڣ����Ƿ�Ϊ0�����Ϊ0����ʾ�ÿ��Ѿ�д��������
    FlashWriteCommand(0x00);
    FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*(i+1) - 2*FLASH_PAGE_SIZE);
    FlashWriteCommand(0x30);
    FlashWait(); //�ȴ����ݶ���
    Data = FlashReadDataByte();
    if(Data==0) //��ʾ������Ч
    {
     Data = FlashReadDataByte(); //����У���
     Sum=Data;
     Data = FlashReadDataByte(); //����У���
     Sum=(Sum<<8)+Data;
     Data = FlashReadDataByte(); //����У���
     Sum=(Sum<<8)+Data;
     Data = FlashReadDataByte(); //����У���
     Sum=(Sum<<8)+Data;
     //�Ӹÿ鿪ʼλ�ö�
     FlashWriteCommand(0x00);
     FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*i);
     FlashWriteCommand(0x30);
     FlashWait(); //�ȴ����ݶ���
     //����1�ֽ��Ƿ�Ϊ0
     Data = FlashReadDataByte();
     if(Data!=0)continue;
     //����2�ֽ��Ƿ�Ϊ0x55
     Data = FlashReadDataByte();
     if(Data!=0x55)continue;
     //����3�ֽ��Ƿ�Ϊ0xAA
     Data = FlashReadDataByte();
     if(Data!=0xAA)continue;
     //����4�ֽ��Ƿ�Ϊ0xFF
     Data = FlashReadDataByte();
     if(Data!=0xFF)continue;
     Sum+=0x1FE;
     
     //����������
     Data = FlashReadDataByte();
     FlashBadBlocksCount=Data;
     Sum+=Data;
     Data = FlashReadDataByte();
     FlashBadBlocksCount=(FlashBadBlocksCount<<8)+Data;
     Sum+=Data;
     Data = FlashReadDataByte();
     FlashBadBlocksCount=(FlashBadBlocksCount<<8)+Data;
     Sum+=Data;
     Data = FlashReadDataByte();
     FlashBadBlocksCount=(FlashBadBlocksCount<<8)+Data;
     Sum+=Data;
     j=8;
     //���ػ����
     for(k=0;k<sizeof(FlashBadBlockTable[0][0])*FLASH_BAD_BLOCKS_REMAP*2;k++)
     {
      if(0==(j&(FLASH_PAGE_SIZE-1))) //���������ҳ������Ҫ���¶���ҳ
      {
       FlashWriteCommand(0x00);
       FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*i+j);
       FlashWriteCommand(0x30);
       FlashWait(); //�ȴ����ݶ���
      }
      Data = FlashReadDataByte();
      Sum+=Data; //��У���
      ((uint8_t *)FlashBadBlockTable)[k]=Data;  //����һ�ֽڵ��������
      j++;
     }
     //������Ӱ������״̬��
     for(k=0;k<sizeof(FlashRemapBlockStatus[0])*FLASH_BAD_BLOCKS_REMAP;k++)
     {
      if(0==(j&(FLASH_PAGE_SIZE-1))) //���������ҳ������Ҫ���¶���ҳ
      {
       FlashWriteCommand(0x00);
       FlashWriteAddr4Byte(FLASH_BLOCK_TABLE_ADDR + FLASH_BLOCK_SIZE*i+j);
       FlashWriteCommand(0x30);
       FlashWait(); //�ȴ����ݶ���
      }
      Data = FlashReadDataByte();
      Sum+=Data; //��У���
      ((uint8_t *)FlashRemapBlockStatus)[k]=Data;   //����һ�ֽڵ���Ӱ����״̬����
      j++;
     }
     if(Sum==0) //���У��ɹ�����˵��������ȷ
     {
      FlashSaveBadBlockTable(); //���䱣�浽FLASH��      
      Ok=0xFF; //����Ϊ�ɹ�
      break;   //���˳�ѭ��
     }
    }
   }
  }
 }
 
 if(Ok==0) //�������û�ҵ�����ôֻ�����³�ʼ����
 {
  FlashBadBlocksCount=0; //����������Ϊ0
  for(i=0;i<FLASH_BAD_BLOCKS_REMAP;i++)
  {
   //����Ӱ��鶼����Ϊ�ÿ�
   FlashRemapBlockStatus[i]=FLASH_BLOCK_OK;
   //����Ӱ���ϵ����Ϊ-1
   FlashBadBlockTable[0][i]=~0;
   FlashBadBlockTable[1][i]=~0;
  }
  //���ú�֮�󱣴�����
  FlashSaveBadBlockTable();
 }
 //���õ�ǰ���ʹ��ĵ�ַΪ��Чֵ
 FlashLastAccessAddr=~0;
 
 */
 
}
/////////////////////////End of function/////////////////////////////




/********************************************************************
�������ܣ�������õĽ������ַ��
��ڲ�����Op����Ӧ�Ĳ�����
��    �أ���һ�����õĽ�����ĵ�ַ��
��    ע���ޡ�
********************************************************************/
uint32_t FlashManageSwapBlock(uint32_t Op)
{
 static uint32_t Current;
 static uint8_t FlashSwapBlockStatus[FLASH_SWAP_BLOCKS];
 uint32_t i;
 
 switch(Op)
 {
  case 0:  //�������Ϊ1����ʾ��ʼ��
   Current=0;
   for(i=0;i<FLASH_SWAP_BLOCKS;i++)
   {
    FlashSwapBlockStatus[i]=0; //��ʼ�����н�����Ϊ�õ�
   }
  break;
  
  case 1: //�������Ϊ1����ʾ��ȡ��һ�����õĽ�����
   while(1)//һֱ���ԣ���������������꣨�����ˣ���ô����ѭ���ˣ�
   {
    Current++;
    if(Current>=FLASH_SWAP_BLOCKS)
    {
     Current=0;
    }
    if(FlashSwapBlockStatus[Current]==0)break; //����ÿ��־Ϊ0����˵��δ��
   }
  break;
  
  case 2: //�������Ϊ2��˵����ȡ��ǰ��������ַ
  break;
  
  case 3: //�������Ϊ3�����õ�ǰ������Ϊ����
   FlashSwapBlockStatus[Current]=FLASH_BLOCK_BAD;
  break;
  
  default:
  break;
 }
 return FLASH_SWAP_BLOCK_ADDR+Current*FLASH_BLOCK_SIZE; //���ؿ��õĽ������ַ
}






void FSMC_NAND_ReadID(NAND_IDTypeDef* NAND_ID)
{
  u32 data = 0;
  /* �������������0x70010000 */  
  *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = 0x90;
  *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
   /* ��K9F1208 NAND FLASH����ID���� */ 
   data = *(vu32 *)(Bank_NAND_ADDR | DATA_AREA);  //��������0x70000000��������
   NAND_ID->Maker_ID   = ADDR_1st_CYCLE (data);
   NAND_ID->Device_ID  = ADDR_2nd_CYCLE (data);
   NAND_ID->Third_ID   = ADDR_3rd_CYCLE (data);
   NAND_ID->Fourth_ID  = ADDR_4th_CYCLE (data);  
}





void   SEE_FSMC_NAND_ID(void)
{

	  FSMC_NAND_ReadID(NAND_ID_SJW);
}






/////////////////////////End of function/////////////////////////////


/***************************** ���������� www.armfly.com (END OF FILE) *********************************/








///*
// * NAND write
// */
//static int nand_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
//{
//	int i, page, col, cnt, status;
//	struct nand_chip *this = mtd->priv;

//	/* Do not allow write past end of page */
//	if ((to + len) > mtd->size) {
//		DEBUG(MTD_DEBUG_LEVEL0,
//			__FUNCTION__"(): Attempted write past end of device\n");
//		return -EINVAL;
//	}

//	/* Shift to get page */
//	page = ((int)to) >> this->page_shift;

//	/* Get the starting column */
//	col = to & (mtd->oobblock - 1);

//	/* Initialize return length value */
//	*retlen = 0;

//	/* Select the NAND device */
//	nand_select();

//	/* Check the WP bit */
//	nand_command(mtd, NAND_CMD_STATUS, -1, -1);

//	this->wait_for_ready();

//	if (!(this->read_data() & SMC_STAT_NOT_WP)) {
//		DEBUG(MTD_DEBUG_LEVEL0,
//			__FUNCTION__"(): Device is write protected!!!\n");
//		i = -EPERM;
//		goto nand_write_exit;
//	}

//	/* Loop until all data is written */
//	while (*retlen < len) {
//		/* Write data into buffer */
//		if ((col + len) >= mtd->oobblock)
//			for (i = col, cnt = 0; i < mtd->oobblock; i++, cnt++)
//				this->data_buf[i] = buf[(*retlen + cnt)];
//		else
//			for (i = col, cnt = 0; cnt < (len - *retlen); i++, cnt++)
//				this->data_buf[i] = buf[(*retlen + cnt)];
//		/* Write ones for partial page programming */
//		for (i = mtd->oobblock; i < (mtd->oobblock + mtd->oobsize); i++)
//			this->data_buf[i] = 0xff;
//		
//		/* Write pre-padding bytes into buffer */
//		for (i = 0; i < col; i++)
//			this->data_buf[i] = 0xff;

//		/* Write post-padding bytes into buffer */
//		if ((col + (len - *retlen)) < mtd->oobblock) {
//			for (i = (col + cnt); i < mtd->oobblock; i++)
//				this->data_buf[i] = 0xff;
//		}

//		/* Send command to begin auto page programming 
//		����ط���ʵ����д��ַ��Ҳ���ǵ�һ����һ��д����һҳ��
//������������������*/
//		nand_command(mtd, NAND_CMD_SEQIN, 0x00, page);

//		/* Write out complete page of data */
//		this->hwcontrol(NAND_CTL_DAT_OUT);
//		for (i = 0; i < (mtd->oobblock + mtd->oobsize); i++)
//			this->write_data(this->data_buf[i]);
//		this->hwcontrol(NAND_CTL_DAT_IN);

//		/* Send command to actually program the data */
//		nand_command(mtd, NAND_CMD_PAGEPROG, -1, -1);

//		this->wait_for_ready();

//		/*
//		 * Wait for program operation to complete. This could
//		 * take up to 3000us (3ms) on some devices. so we try
//		 * and exit as quickly as possible.
//		 */
//		status = 0;
//		for (i = 0; i < 24; i++) {
//			/* Delay for 125us */
//			udelay(125);

//			/* Check for status */
//			nand_command(mtd, NAND_CMD_STATUS, -1, -1);
//			status = (int)this->read_data();
//			if (status & SMC_STAT_READY)
//				break;
//		}

//		/* See if device thinks it succeeded */
//		if (status & SMC_STAT_WRITE_ERR) {
//			DEBUG(MTD_DEBUG_LEVEL0,
//				__FUNCTION__"(): Failed write, page 0x%08x, " \
//				"%6i bytes were sucesful\n", page, *retlen);
//			i = -EIO;
//			goto nand_write_exit;
//		}

//		if (col)
//			col = 0x00;

//		/* Update written bytes count */
//		*retlen += cnt;

//		/* Increment page address */
//		page++;
//		
//	}

//	/* Return happy */
//	*retlen = len;
//	i = 0;

//nand_write_exit:
//	/* De-select the NAND device */
//	nand_deselect();

//	return i;
//}


/*
uint8_t W25Q64Write(uint32_t Addr, uint32_t num, uint8_t * data)
{
uint32_t secpos;
uint16_t secoff;
uint16_t secremain;
uint16_t i; 
uint8_t Test_Reardata[512];

secpos=Addr/4096;//������ַ
secoff=Addr%4096;//�������ڵ�ƫ��
secremain=4096-secoff;//����ʣ��ռ��С

if(num<=secremain) secremain = num;//������4096���ֽ�

while(1)
{
		W25Q64Read(secpos*4096,4096,W25QXX_BUFFER);//������������������

		for(i=0;i<secremain;i++)//У������
		{
				if(W25QXX_BUFFER[secoff+i]!=0XFF) break;//��Ҫ���� 
		}
		if(i<secremain)//��Ҫ����
		{
				W25Q64SectorErase(secpos*4096);//������������
				for(i=0;i<secremain;i++) ? //����
				{
				W25QXX_BUFFER[i+secoff]=data[i];
				}
				// W25Q64Read(secpos*4096, 512, Test_Reardata);
				W25QXX_Write_NoCheck(W25QXX_BUFFER,secpos*4096,4096);//д����������
		}else{	
				W25QXX_Write_NoCheck(data,Addr,secremain);//д���������� ?
		}
		if(num==secremain)break;//д�����
		else  //д��δ����
		{
				secpos++;//������ַ��1
				secoff=0;//ƫ��λ��Ϊ0


				data+=secremain; //ָ��ƫ��
				Addr+=secremain; //д��ַƫ��
				num-=secremain; //�ֽ����ݼ�
				if(num>4096)secremain=4096; //��һ������д����
				else secremain=num; //дһ����������д��
		} 
}
		return 0;
}

-----------------------------------
?����Ȩ���������У�����51CTO��������wx60e325079f740��ԭ����Ʒ������ϵ���߻�ȡת����Ȩ������׷����������
FATFS��ֲ�����Թ��̣���STM32��ʹ��W25Q64��
https://blog.51cto.com/u_15294654/3112978
*/
