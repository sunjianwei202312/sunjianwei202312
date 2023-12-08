#ifndef __VS1003B_H
#define __VS1003B_H
#include "includes.h"

// VS1003��������
#define VS1003B_RESET_PORT	 		GPIOC		  
#define VS1003B_RESET_BIT 	 		GPIO_Pin_8  


//������SPI2����������vs1003 PB12 PB13 PB14 PB15
#define VS1003B_CMD_CS_PORT  		GPIOB		     // ������ƶ˿�  ��������   xCS
#define VS1003B_CMD_CS_BIT   		GPIO_Pin_1  // �����������   GPIO_Pin_12          

#define VS1003B_DATA_CS_PORT		GPIOA		     // ���ݿ��ƶ˿�            xDCS
#define VS1003B_DATA_CS_BIT 		GPIO_Pin_8   // ���ݿ�������

#define VS1003B_DREQ_PORT   		GPIOB		     // ���ݿ��ƶ˿�    DREQ
#define VS1003B_DREQ_BIT    		GPIO_Pin_5   // ���ݿ�������

   

/* reset */
#define MP3_Reset(x)	  x ? (GPIO_SetBits(VS1003B_RESET_PORT,VS1003B_RESET_BIT))   : (GPIO_ResetBits(VS1003B_RESET_PORT,VS1003B_RESET_BIT))

/* ����Ƭѡ */
#define MP3_xCS(x)	    x ? GPIO_SetBits(VS1003B_CMD_CS_PORT,VS1003B_CMD_CS_BIT)   : GPIO_ResetBits(VS1003B_CMD_CS_PORT,VS1003B_CMD_CS_BIT)

/* ����Ƭѡ */ 
#define MP3_xDCS(x)	    x ? GPIO_SetBits(VS1003B_DATA_CS_PORT,VS1003B_DATA_CS_BIT) : GPIO_ResetBits(VS1003B_DATA_CS_PORT,VS1003B_DATA_CS_BIT)

#define	VS1003B_WAIT_DREQ( )			  (GPIO_ReadInputDataBit(VS1003B_DREQ_PORT, VS1003B_DREQ_BIT))






// VS1003��������
#define VS_WRITE_COMMAND 	0x02
#define VS_READ_COMMAND 	0x03

/*
 VS1003�Ĵ�������  VS1003 ���� 16 �� 16 λ�ļĴ����� ��ַ�ֱ�Ϊ 0x0 �C 0xF��
 ����ģʽ�Ĵ��� ��MODE�� 0x0�� ��״̬�Ĵ��� ��STATUS��0x1��
 �ڸ�λ��ĳ�ʼֵ�ֱ�Ϊ 0x800 �� 0x3C �⣬����ļĴ����� VS1003 ��ʼ�����ֵ��Ϊ 0
 
 VS1003�еļĴ���
 https://blog.csdn.net/cy941228/article/details/52700889
 ����ҳ�ڵĽ��ͱȽ�͸�У�ֵ��һ��
*/
#define SPI_MODE        	0x00   
#define SPI_STATUS      	0x01  //vs1003��״̬ 
#define SPI_BASS        	0x02  //���øߵ�����ǿ�� 
#define SPI_CLOCKF      	0x03  //ʱ��Ƶ��+��Ƶ��
#define SPI_DECODE_TIME 	0x04  //����ʱ��
#define SPI_AUDATA      	0x05   //������Ƶ����
#define SPI_WRAM        	0x06   //RAM����д
#define SPI_WRAMADDR    	0x07   //RAM��д��ַ
#define SPI_HDAT0       	0x08   //��ͷ����0
#define SPI_HDAT1       	0x09   //��ͷ����1



#define SPI_AIADDR      	0x0a  // �û�������ʼ��ַ
#define SPI_VOL         	0x0b   //��������

#define SPI_AICTRL0     	0x0c   //Ӧ�ÿ���������0
#define SPI_AICTRL1     	0x0d   //Ӧ�ÿ���������1
#define SPI_AICTRL2     	0x0e   //Ӧ�ÿ���������2
#define SPI_AICTRL3     	0x0f   //Ӧ�ÿ���������3


/*
8��6��10 SCI_AIADDR (RW)
SCI_AIADDRָ����Ӧ�ô���Ŀ�ʼ��ַ��Ҫ��SCI_WRAMADDR��SCI_WARM֮ǰд�롣�����ʹ��Ӧ
�ô��룬�˼Ĵ������Բ���ʼ����Ҳ�ɳ�ʼ��Ϊ0�����VS10xxӦ�ñʼǡ�


8��6��12 SCI_AICTRL[x] (RW)
SCI_AICTRL[x]�Ĵ�����x=[0..3]�������������û�Ӧ�ó���

8��6��11 SCI_VOL (RW)
SCI_VOL���Կ��Ʋ�����Ӳ����������ÿ��������һ��0 ��254�����������Ϊ���������������0.5dB˥
����������ֵ��256�����������������0��������Ϊ0xFEFE��
���磺��������Ϊ-2.0dB��������Ϊ-3.5dB��(4��256)+7=0x407��ע�⣬��������ʱ������Ϊ�����������
��λ����ı������趨��
ע�⣺����SCI_VOLΪ0xFFFF��ʹоƬ����ģ�����ģʽ��



8��6��6 SCI_AUDATA (RW)
��������ȷ������ʱ����ǰ�Ĳ����ʺ�ͨ�������Դ�SCI_AUDATA ��15��1 λ��0 λ�ж�ȡ��15��1λ���
���˲����ʳ������ֵ��λ0Ϊ0 ��ʾ��������Ϊ1��ʾ��������
дSCI_AUDATA ��ֱ�Ӹı�����ʡ�
���磺44100Hz ���������ݣ���������Ϊ0xAC45(44101)��


SCI_HDAT0 ��SCI_HDAT1 (R)
����WAV�ļ���SCI_HDAT0 ��SCI_HDAT1 ����ֵ�ֱ���0x7761 ��0x7665��

����WMA�ļ���SCI_HDAT1 ��ֵΪ0x574D, SCI_HDAT0 ���������ֽ�ÿ/�������������ٶȡ���Ҫ��ȡ��
���ı����ʣ���SCI_HDAT0 ��ֵ��8��

����MIDI�ļ���SCI_HDAT1 ��ֵΪ0x4D54��SCI_HDAT0 ������ֵ�����±�

����MP3�ļ���SCI_HDAT[0��1]�����µ�����
������ʱ��SCI_HDAT0 ��SCI_HDAT1 ������ͷ��Ϣ�Ǵ�MP3 ����ʼ����ʱ��ȡ�ġ���λ֮�������Ĵ���
�����㣬ָʾû�����ݱ��ҵ���
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


// ��������
void  VS1003B_WriteData( uint8_t * buf);
void  VS1003BPin_Init(void);
void 	VS1003B_CMD_Write(INT8U address, INT16U data,INT8U device);
void 	VS1003B_SCI_Test(void);
void 	VS1003B_DetectSCIOk(void);
void 	VS1003B_SoftReset(void);
void 	SD_SPIDrive_Init(uint8_t device);
void 	VS1003B_HardReset(void);			    //Ӳ��λ
void 	VS1003B_SoftReset(void);  		    //��λ
void 	VS1003B_SineTest(INT8U fre);   		//��������
void 	VS1003B_ResetDecodeTime(void);	  //��λ����ʱ��
void 	VS1003B_LoadPatch(void);		      //����Ƶ�׳���
void 	VS1003B_GetSpec(INT8U *p);		    //��ȡƵ��
void 	InitRecordADPCM(void);			      //VS1003 IMA ADPCM¼����ʼ��
void 	VS1003B_DATA_Write(unsigned char * buf, INT8U br); //VS1003д����  br���ֵΪ32


INT16U 	VS1003B_RAMTest(void);	 		    //RAM����
INT16U 	VS1003B_GetDecodeTime(void);   	//��ȡ����ʱ�� 
INT16U 	VS1003B_REG_Read(INT8U address);//VS1003���Ĵ���

void TestReadFile(void);

void TestWriteFile(void);
void SD_SPIPin_Init(void);

extern	void DelayMs(vu32 m);
extern	void DelayUs(vu32 m);
#endif


