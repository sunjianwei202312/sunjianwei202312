#ifndef _SD_DRIVER_H_
#define _SD_DRIVER_H_

#include "includes.h"
#include "sdcard.h"

// SD�����Ͷ��� 
#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    4

// SPI�����ٶ�����
#define SPI_SPEED_LOW   0   // ����
#define SPI_SPEED_HIGH  1   // ����

// SD�������ݽ������Ƿ��ͷ����ߺ궨�� 
#define NO_RELEASE      0   //���ͷ����ߣ�������д�ֽ�ʱ 
#define RELEASE         1   // �ͷ����ߣ�   ��д���ֽ�ʱ

// SD��ָ��� 
#define CMD0    0       //����λ
#define CMD9    9       //����9 ����CSD����----��ȡ���ض����ݼĴ�����		
#define CMD10   10      //����10����CID����----��ȡ����־���ݼĴ�����
#define CMD12   12      //����12��ֹͣ���ݴ���
#define CMD16   16      //����16������SectorSize Ӧ����0x00---���ÿ��С(�ֽ�����
#define CMD17   17      //����17����sector-----��ȡһ���������
#define CMD18   18      //����18����Multi sector
#define ACMD23  23      //����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24��дsector-----д��һ���������
#define CMD25   25      //����25��дMulti sector
#define ACMD41  41      //����41��Ӧ����0x00---���������ǰ����
#define CMD55   55      //����55��Ӧ����0x01---��ʼ���ĳ�ʼ��
#define CMD58   58      //����58����OCR��Ϣ
#define CMD59   59      //����59��ʹ��/��ֹCRC��Ӧ����0x00--����crc������1�����߹رգ�0��
//����R1�Ļ�Ӧ��ʽ���±���ʾ��
/*
bit7   bit6        bit5        bit4         bit3          bit2      bit1      bit0

0	  ��������    ��ַ����   ������������   ����crc����    �Ƿ�����   ������λ   idle״̬

SD���ĵ��ͳ�ʼ���������£�  
1����ʼ����SD�����ӵ�Ӳ��������MCU��SPI���ã�IO�����ã��� 
2���ϵ���ʱ��>74��CLK����
3����λ����CMD0���� 
4��������ڲ���ʼ������ȡ�����ͣ�CMD1������MMC������CMD55��CMD41����
5.����ѯOCR����ȡ����״����CMD58����
6���Ƿ�ʹ��CRC��CMD59���� 
7�����ö�д�����ݳ��ȣ�CMD16����  
8����ȡCSD����ȡ�洢����������Ϣ��CMD9����
9������8CLK�󣬽�ֹƬѡ�� 
�������Ǿ�����˶�SD���ĳ�ʼ����


SD����ȡ���ݣ�����ͨ��CMD17��ʵ�֣�����������£�
1������CMD17�� 
2�����տ���ӦR1��  
3������������ʼ����0XFE�� 
4���������ݣ� 
5������2���ֽڵ�CRC�����û�п���CRC���������ֽ��ڶ�ȡ����Զ�����
6��8CLK֮���ֹƬѡ��  
���Ͼ���һ�����͵Ķ�ȡSD�����ݹ��̣�SD����д�ڶ����ݲ�࣬д����ͨ��CMD24��ʵ�֡�
*/

//��ؿ������ź궨�� 
#define SD_CS_ENABLE()     GPIO_ResetBits(GPIOB,GPIO_Pin_10)        //ѡ��SD��
#define SD_CS_DISABLE()    GPIO_SetBits(GPIOB,GPIO_Pin_10)          //��ѡ��SD��
#define SD_PWR_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_3)         //SD���ϵ�
#define SD_PWR_OFF()       GPIO_SetBits(GPIOC,GPIO_Pin_8)           //SD���ϵ�
#define SD_CD()            GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) // �͵�ƽ�п����ߵ�ƽ�޿�




//#define SD_CS_ENABLE()     GPIOB->ODR &=~(1<<12)// GPIO_ResetBits(GPIOB,GPIO_Pin_6)   //ѡ��SD��
//#define SD_CS_DISABLE()    GPIOB->ODR |= (1<<12)  //GPIO_SetBits(GPIOB,GPIO_Pin_6)     //��ѡ��SD��
//#define SD_PWR_ON()       //  GPIOD->ODR &=~(1<<10) //GPIO_ResetBits(GPIOD,GPIO_Pin_10)  //SD���ϵ�
//#define SD_PWR_OFF()      //  GPIOD->ODR |= (1<<10)  //GPIO_SetBits(GPIOD,GPIO_Pin_10)    //SD���ϵ�
////#define SD_DET()           !GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) //����п�
//                                                                    //1-�� 0-��



// ������������
void SPI1_SetSpeed(u8 SpeedSet);	  // ����SIP���ٶ�
void SPI2_SetSpeed(u8 SpeedSet);	  // ����SIP���ٶ�
u8 SPI1_ReadWriteByte(u8 TxData);   //SPI���߶�дһ���ֽ�
u8 SD_GetCSD(u8 *csd_data);

u8 SD_ReadSingleBlock(u32 sector, u8 *buffer);  //��һ��sector
u8 SD_WriteSingleBlock(u32 sector, const u8 *buffer); //дһ��sector
u8 SD_ReadMultiBlock(u32 sector, u8 *buffer, u8 count); //�����sector
u8 SD_WriteMultiBlock(u32 sector, const u8 *data, u8 count);  //д���sector

#endif

