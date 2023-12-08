/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���  ��mp3play.c
 * ����    ��mp3Ӧ�ú�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�-----------------
 *          |                 |
 *          |       ��        |
 *          |                 |
 *           -----------------
 * ��汾  ��ST3.0.0
 *
 * ����    ��fire  QQ: 313303034 
 * ����    ��firestm32.blog.chinaunix.net
**********************************************************************************/
#include   "mp3play.h"

u8 readBuf[READBUF_SIZE];		     /* ���ڴ洢MP3֡ͷ��Ϣ */
struct tag_info id3v1;					 /* ID3V1�ṹ����������ڴ�����ĸ�����Ϣ */
struct tag_info id3v2;					 /* ID3V2�ṹ����������ڴ�����ĸ�����Ϣ */

/* ----------�ļ�ϵͳ����------------- */
FATFS fs;                  // Work area (file system object) for logical drive
static FIL fsrc;            // file objects
static BYTE buffer[512];          // file copy buffer
static FRESULT res;               // FatFs function common result code
static UINT br, bw;               // File R/W count
UINT n_Read;

extern void VS1003B_WriteData( uint8_t * buf);


/*
 * ��������MP3_Play
 * ����  ����ȡSD���������Ƶ�ļ�����ͨ���������ų���
 *         ֧�ֵĸ�ʽ��mp3,mid,wav,wma
 * ����  ����
 * ���  ����
 * ˵��  ���ݲ�֧�ֳ��ļ�������֧�����ġ�
 */
void MP3_Play(void)
{ 
  FRESULT res;
  FILINFO finfo;
  DIR dirs;	
	
	FATFS 	 		fs;
	FIL         file;               // file objects
  uint8_t  		Status;
	INT16U 	    count=0; 	
	UINT 		    br;             		// File R/W count  �ļ���������  
	
	
	
	
	
	
	
	
	
	
	
	char j = 0;
  char path[50] = {""}; /* MicroSD����Ŀ¼ */	
  char *result1, *result2, *result3, *result4;

  f_mount(&fs, "0:", 0);			                    /* �����ļ�ϵͳ��0�� */

 	if (f_opendir(&dirs, path) == FR_OK) 	          /* �򿪸�Ŀ¼ */
  {
    while (f_readdir(&dirs, &finfo) == FR_OK)    	/* ���ζ�ȡ�ļ��� */
    {
      if ( finfo.fattrib & AM_ARC )               /* �ж��Ƿ�Ϊ�浵���ĵ� */
      {
        if( !finfo.fname[0] )				              /* �ļ���Ϊ�ռ�������Ŀ¼��ĩβ���˳� */
          break;         
        printf( " \r\n �ļ���Ϊ: %s \r\n", finfo.fname );

				result1 = strstr( finfo.fname, ".mp3" );	/* �ж��Ƿ�Ϊ��Ƶ�ļ� */
				result2 = strstr( finfo.fname, ".mid" );
				result3 = strstr( finfo.fname, ".wav" );
				result4 = strstr( finfo.fname, ".wma" );				
					     
				if ( result1!=NULL || result2!=NULL || result3!=NULL || result4!=NULL )
				{
					Put_ascii_chinese_string(30,250,"����һ��MP3���Գ���......",0xf800,1);
					PutChinese_strings22(30, 200, "��ʼ����", 0, 1);

        	res = f_open( &fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ ); /* ��ֻ����ʽ�� */					

					/* ��ȡ������Ϣ(ID3V1 tag / ID3V2 tag) */					
					if ( Read_ID3V1(&fsrc, &id3v1) == TRUE )
					{// ID3V1 tag
							printf( "\r\n ��Ŀ    ��%s \r\n", id3v1.title );
							printf( "\r\n ������  ��%s \r\n", id3v1.artist );														
							printf( "\r\n ר��    ��%s \r\n", id3v1.album );

              Put_ascii_chinese_string(10,180,"��Ŀ:",0,1);
							Put_ascii_chinese_string(80,180,id3v1.title,0,1);

							Put_ascii_chinese_string(10,160,"������:",0,1);
							Put_ascii_chinese_string(80,160,id3v1.artist,0,1);

              Put_ascii_chinese_string(10,140,"ר��:",0,1);
							Put_ascii_chinese_string(80,140,id3v1.album,0,1);
					}
					else
					{// ��ЩMP3�ļ�û��ID3V1 tag,ֻ��ID3V2 tag						
							res = f_lseek(&fsrc, 0);
							Read_ID3V2(&fsrc, &id3v2);

							printf( "\r\n ��Ŀ    ��%s \r\n", id3v2.title );
							printf( "\r\n ������  ��%s \r\n", id3v2.artist );

              Put_ascii_chinese_string(10,200,"��Ŀ:",0,1);
							Put_ascii_chinese_string(80,200,id3v2.title,0,1);

							Put_ascii_chinese_string(10,180,"������:",0,1);
							Put_ascii_chinese_string(80,180,id3v2.artist,0,1);	
					}
//					Screen_shot(0, 0, 320, 240, "/myScreen"); closed by sjw for compiler pass
					/* ʹ�ļ�ָ�� fsrc ����ָ���ļ�ͷ����Ϊ�ڵ���Read_ID3V1/Read_ID3V2ʱ��
					   fsrc ��λ�øı��� */
					res = f_open( &fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ );
					//res = f_lseek(&fsrc, 0);
										 										
        	br = 1;				  			     /* br Ϊȫ�ֱ��� */
//					TXDCS_SET( 0 );            /* ѡ��VS1003�����ݽӿ�	closed by sjw for compiler pass*/  
/* ------------------- һ����ʼ --------------------*/
         printf(  " \r\n ��ʼ���� \r\n" ); 
					for (;;) 
					{			
    	    	res = f_read( &fsrc, buffer, sizeof(buffer), &br );
          	if ( res == 0 )
						{				
								count = 0;								/* 512�ֽ������¼��� */
								GPIO_WriteBit(GPIOC, GPIO_Pin_5, 
		                         (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_5))));

								Delay_us( 1000 );         /* 10ms ��ʱ */ 
								while ( count < 512)		  /* SD����ȡһ��sector��һ��sectorΪ512�ֽ� */	
								{ 						
			           	if ( VS1003B_DREQ_BIT != 0 )	      /* �ȴ�DREQΪ�ߣ������������� */
								 	{
				 						for (j=0; j<32; j++ ) /* VS1003��FIFOֻ��32���ֽڵĻ��� */
										{										
											VS1003B_WriteData( &buffer[count] );			//closed by sjw for compiler pass!	?????????????????????						
											count++;
										}
								  }		    	      	
							  }
       		   }
					   if (res || br == 0) break;   /* ������ߵ���MP3�ļ�β */		   
           }
					 printf( " \r\n ���Ž��� \r\n" );
/* ------------------- һ������ --------------------*/ 
				   count = 0;
					 /* ����VS1003��Ҫ����һ���������跢��2048��0��ȷ����һ�׵��������� */
				   while ( count < 2048 )	
				   {	
            	if ( VS1003B_DREQ_BIT != 0 )
							{
 								for ( j=0; j<32; j++ )
				      	{					   			
									VS1003B_WriteData( 0 );	//closed by sjw for compiler pass!							
									count++;
				      	}
			     		}
		       }
					 count = 0;
					// TXDCS_SET( 1 );   /* �ر�VS1003���ݶ˿� closed by sjw for compiler pass*/ 
				   f_close(&fsrc);	 /* �رմ򿪵��ļ� */
					 PutChinese_strings22(10, 160, "���Ž���", 0, 1);
				}   		                      
      }
    } /* while (f_readdir(&dirs, &finfo) == FR_OK) */  
  } /* if (f_opendir(&dirs, path) == FR_OK)  */	  
} /* end of MP3_Play */

/*
 * ��������Read_ID3V1
 * ����  ����MP3�ļ�β��ȡID3V1����Ϣ��������Щ��Ϣ������һ��ȫ��������        
 * ����  ��- FileObject: file system
 *         - info: struct tag_info
 * ���  ����
 * ˵��  �����ڵ�mp3�����϶�û��ID3V1 tag(���ļ�β��)���е���ID3V2 tag(���ļ�ͷ��)��
 */
int Read_ID3V1(FIL *FileObject, struct tag_info *info)
{
    res = f_lseek(FileObject,FileObject->fsize - 128 ); /* ID3V1����Ϣ�������ļ�ĩβ��128��byte�� */
    res = f_read(FileObject, &readBuf, 128 , &n_Read);	/* ��ID3V1�е�128��byte����Ϣ���������� */    

    if (strncmp("TAG", (char *) readBuf, 3) == 0)	      /* ID3V1�ı�ǩͷ�����ǡ�TAG����������Ϊû�б�ǩ */
    {				
        strncpy(info->title, (char *) readBuf + 3, MIN(30, sizeof(info->title) - 1)); 	    /* ���� */
        strncpy(info->artist,(char *) readBuf + 3 + 30, MIN(30, sizeof(info->artist) - 1));	/* ���� */
				strncpy(info->album,(char *) readBuf + 3 + 30 + 30, MIN(30, sizeof(info->album) - 1));	/* ר�� */
				strncpy(info->year,(char *) readBuf + 3 + 30 + 30 + 30, MIN(4, sizeof(info->year) - 1));	/* ʱ�� */
				return TRUE;
    }
		else 
		{ 
			return FALSE; 
		}		
}

/*
 * ��������Read_ID3V2
 * ����  ����MP3�ļ�ͷ����ȡID3V2����Ϣ��������Щ��Ϣ������һ��ȫ��������
 * ����  ��- FileObject: file system
 *         - info: struct tag_info
 * ���  ����
 * ˵��  ��MP3�ļ�����ID3V2�����������ߣ���Ŀ��ר������Ϣ�����Ȳ��̶�����չ��ID3V1����Ϣ����
 */
void Read_ID3V2(FIL *FileObject, struct tag_info *info)
{
    uint32_t p = 0;
    
    res = f_lseek(FileObject,0); /* ��λ���ļ���ͷ�� */
    res = f_read(FileObject, &readBuf, READBUF_SIZE , &n_Read); /* ���ļ�ͷ����ʼ��ȡREADBUF_SIZE���ֽ� */
    
    if (strncmp("ID3", (char *) readBuf, 3) == 0)	/* ID3V3��ͷ����ǩ����Ϊ��ID3�� */
    {
        uint32_t tag_size, frame_size, i;
        uint8_t version_major;
        int frame_header_size;

        /* ��ǩ��С��������ǩͷ��10���ֽں����б�ǩ֡�Ĵ�С */
        tag_size = ((uint32_t) readBuf[6] << 21) | ((uint32_t) readBuf[7] << 14) | ((uint16_t) readBuf[8] << 7) | readBuf[9];
        
        info->data_start = tag_size;
        version_major = readBuf[3];   /* �汾��ΪID3V2.3ʱ�ͼ�¼Ϊ3 */

        if (version_major >= 3)
        {
            frame_header_size = 10;		/* ID3V2.3�ı�ǩͷΪ10���ֽ� */
        }
        else
        {
            frame_header_size = 6;
        }
        i = p = 10;
        
        /* iterate through frames */
        while (p < tag_size)				 /* �ӱ�ǩͷ��ʼ���� */
        {
            if (version_major >= 3)
            {
                frame_size = ((uint32_t) readBuf[i + 4] << 24) | ((uint32_t) readBuf[i + 5] << 16) | ((uint16_t) readBuf[i + 6] << 8) | readBuf[i + 7];
            }
            else
            {
                frame_size = ((uint32_t) readBuf[i + 3] << 14) | ((uint16_t) readBuf[i + 4] << 7) | readBuf[i + 5];
            }
            if (i + frame_size + frame_header_size + frame_header_size >= sizeof(readBuf))
            {
                if (frame_size + frame_header_size > sizeof(readBuf))
                {
                    res = f_lseek(FileObject,FileObject->fptr + p + frame_size + frame_header_size); 
                    res = f_read(FileObject, &readBuf, READBUF_SIZE , &n_Read);
                    p += frame_size + frame_header_size;
                    i = 0;
                    continue;
                }
                else
                {
                    int r = sizeof(readBuf) - i;
                    memmove(readBuf, readBuf + i, r);
                    res = f_read(FileObject, (char *) readBuf + r, i , &n_Read);
                    i = 0;
                }
            }

            /* ֡��ʶ"TT2"/"TIT2"��ʾ����Ϊ���׸�� ���� */
            if (strncmp("TT2", (char *) readBuf + i, 3) == 0 || strncmp("TIT2", (char *) readBuf + i, 4) == 0)
            {
                strncpy(info->title, (char *) readBuf + i + frame_header_size + 1, MIN(frame_size - 1, sizeof(info->title) - 1));
                if( ( info->title[0] == 0xFE && info->title[1] == 0xFF ) || ( info->title[0] == 0xFF && info->title[1] == 0xFE ) )
                {
                    /* unicode ��ʽ*/
                    memset(info->title,0,sizeof(info->title));
                    printf( "-- MP3 title no support unicode \r\n");			
                }       
            }

						/* ֡��ʶ"TP1"/"TPE1"��ʾ����Ϊ���׸�� ���� */
            else if (strncmp("TP1", (char *) readBuf + i, 3) == 0 || strncmp("TPE1", (char *) readBuf + i, 4) == 0)
            {
                strncpy(info->artist, (char *) readBuf + i + frame_header_size + 1, MIN(frame_size - 1, sizeof(info->artist) - 1));
                
                if( ( info->artist[0] == 0xFE && info->artist[1] == 0xFF ) || ( info->artist[0] == 0xFF && info->artist[1] == 0xFE ) )
                {
                    /* unicode ��ʽ*/
                    memset(info->artist,0,sizeof(info->artist));
                    printf( "-- MP3 artist no support unicode \r\n");
                }
            }
            
            p += frame_size + frame_header_size;
            i += frame_size + frame_header_size;
        }
    }
}

/******************* (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� *****END OF FILE****/
