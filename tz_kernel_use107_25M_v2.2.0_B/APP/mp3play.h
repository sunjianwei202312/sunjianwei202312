#ifndef __MP3PLAY_H
#define	__MP3PLAY_H

#include "stm32f10x.h"
#include "usart1.h"
#include "SysTick.h"
#include "VS1003B.h"
#include "sdcard.h"
#include "ff.h"
#include "diskio.h"
#include <string.h>
#include <stdio.h>
//#include "led.h"

#include "lcd.h"
//#include "sd_fs_app.h"
//#include "Sd_bmp.h"

#define MIN(x, y)			((x) < (y)? (x) : (y))
#define READBUF_SIZE   ( 5 * 1024 )

#define TRUE 1
#define FALSE 0

/* music tag information structure */
struct tag_info
{
	char title[40];        // music title               
	char artist[40];        // music artist
	char album[40];         // album        
	char year[8];						// year

	int duration;           // music total duration (second)   
	int position;           // music current position (second) 

	uint8_t  length;        // bits PerSample			       
	uint32_t bit_rate;      // bit rate                       
	uint32_t sampling;      // sampling                     
	uint32_t data_start;    // start position of data        
};

/*
 * MP3�ļ������Ϊ3����:TAG_V2(ID3V2),Frame,TAG_V1(ID3V1)��Ҫע��
 * ��ЩMP3�ļ�β��û��ID3V1 tag�ģ��е���MP3�ļ�ͷ����ID3V2 tag��
 * ����ID3V1 �����MP3�ļ���ĩβ ����16���Ƶı༭����һ��MP3�ļ���
 * �鿴��ĩβ��128��˳�����ֽڣ����ݽṹ�������£�
 */

 /*
  *1��ÿ֡�Ĳ���ʱ�䣺����֡���Ƕ��٣�ÿ֡�Ĳ���ʱ����26ms��
	*2��FrameSize = ( (( MPEGVersion == MPEG1 ? 144 : 72 ) * Bitrate) / SampleRate ) + PaddingBit 
	*/
typedef struct tagID3V1
{
	char Header[3];	     // ��ǩͷ������"TAG"��������Ϊû�б�ǩͷ
	char Title[30];	     // ����
	char Artist[30];		 // ����
	char Album[30];			 // ר��
	char Year[4];				 // ��Ʒ���
	char Comment[28];		 // ��ע
	char reserve;				 // ����
	char track;					 // ����
	char Genre;					 // ���
}ID3V1, *pID3V1;

//void Read_ID3V1(FIL *FileObject, struct tag_info *info);
int Read_ID3V1(FIL *FileObject, struct tag_info *info);
void Read_ID3V2(FIL *FileObject, struct tag_info *info);
void MP3_Play(void);

#endif /* __MP3PLAY_H */

