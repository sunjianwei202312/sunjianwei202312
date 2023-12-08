/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名  ：mp3play.c
 * 描述    ：mp3应用函数库         
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |                 |
 *          |       无        |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.0.0
 *
 * 作者    ：fire  QQ: 313303034 
 * 博客    ：firestm32.blog.chinaunix.net
**********************************************************************************/
#include   "mp3play.h"

u8 readBuf[READBUF_SIZE];		     /* 用于存储MP3帧头信息 */
struct tag_info id3v1;					 /* ID3V1结构体变量，用于存歌曲的附加信息 */
struct tag_info id3v2;					 /* ID3V2结构体变量，用于存歌曲的附加信息 */

/* ----------文件系统变量------------- */
FATFS fs;                  // Work area (file system object) for logical drive
static FIL fsrc;            // file objects
static BYTE buffer[512];          // file copy buffer
static FRESULT res;               // FatFs function common result code
static UINT br, bw;               // File R/W count
UINT n_Read;

extern void VS1003B_WriteData( uint8_t * buf);


/*
 * 函数名：MP3_Play
 * 描述  ：读取SD卡里面的音频文件，并通过耳机播放出来
 *         支持的格式：mp3,mid,wav,wma
 * 输入  ：无
 * 输出  ：无
 * 说明  ：暂不支持长文件名，不支持中文。
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
	UINT 		    br;             		// File R/W count  文件读计数器  
	
	
	
	
	
	
	
	
	
	
	
	char j = 0;
  char path[50] = {""}; /* MicroSD卡根目录 */	
  char *result1, *result2, *result3, *result4;

  f_mount(&fs, "0:", 0);			                    /* 挂载文件系统到0区 */

 	if (f_opendir(&dirs, path) == FR_OK) 	          /* 打开根目录 */
  {
    while (f_readdir(&dirs, &finfo) == FR_OK)    	/* 依次读取文件名 */
    {
      if ( finfo.fattrib & AM_ARC )               /* 判断是否为存档型文档 */
      {
        if( !finfo.fname[0] )				              /* 文件名为空即到达了目录的末尾，退出 */
          break;         
        printf( " \r\n 文件名为: %s \r\n", finfo.fname );

				result1 = strstr( finfo.fname, ".mp3" );	/* 判断是否为音频文件 */
				result2 = strstr( finfo.fname, ".mid" );
				result3 = strstr( finfo.fname, ".wav" );
				result4 = strstr( finfo.fname, ".wma" );				
					     
				if ( result1!=NULL || result2!=NULL || result3!=NULL || result4!=NULL )
				{
					Put_ascii_chinese_string(30,250,"这是一个MP3测试程序......",0xf800,1);
					PutChinese_strings22(30, 200, "开始播放", 0, 1);

        	res = f_open( &fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ ); /* 以只读方式打开 */					

					/* 获取歌曲信息(ID3V1 tag / ID3V2 tag) */					
					if ( Read_ID3V1(&fsrc, &id3v1) == TRUE )
					{// ID3V1 tag
							printf( "\r\n 曲目    ：%s \r\n", id3v1.title );
							printf( "\r\n 艺术家  ：%s \r\n", id3v1.artist );														
							printf( "\r\n 专辑    ：%s \r\n", id3v1.album );

              Put_ascii_chinese_string(10,180,"曲目:",0,1);
							Put_ascii_chinese_string(80,180,id3v1.title,0,1);

							Put_ascii_chinese_string(10,160,"艺术家:",0,1);
							Put_ascii_chinese_string(80,160,id3v1.artist,0,1);

              Put_ascii_chinese_string(10,140,"专辑:",0,1);
							Put_ascii_chinese_string(80,140,id3v1.album,0,1);
					}
					else
					{// 有些MP3文件没有ID3V1 tag,只有ID3V2 tag						
							res = f_lseek(&fsrc, 0);
							Read_ID3V2(&fsrc, &id3v2);

							printf( "\r\n 曲目    ：%s \r\n", id3v2.title );
							printf( "\r\n 艺术家  ：%s \r\n", id3v2.artist );

              Put_ascii_chinese_string(10,200,"曲目:",0,1);
							Put_ascii_chinese_string(80,200,id3v2.title,0,1);

							Put_ascii_chinese_string(10,180,"艺术家:",0,1);
							Put_ascii_chinese_string(80,180,id3v2.artist,0,1);	
					}
//					Screen_shot(0, 0, 320, 240, "/myScreen"); closed by sjw for compiler pass
					/* 使文件指针 fsrc 重新指向文件头，因为在调用Read_ID3V1/Read_ID3V2时，
					   fsrc 的位置改变了 */
					res = f_open( &fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ );
					//res = f_lseek(&fsrc, 0);
										 										
        	br = 1;				  			     /* br 为全局变量 */
//					TXDCS_SET( 0 );            /* 选择VS1003的数据接口	closed by sjw for compiler pass*/  
/* ------------------- 一曲开始 --------------------*/
         printf(  " \r\n 开始播放 \r\n" ); 
					for (;;) 
					{			
    	    	res = f_read( &fsrc, buffer, sizeof(buffer), &br );
          	if ( res == 0 )
						{				
								count = 0;								/* 512字节完重新计数 */
								GPIO_WriteBit(GPIOC, GPIO_Pin_5, 
		                         (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_5))));

								Delay_us( 1000 );         /* 10ms 延时 */ 
								while ( count < 512)		  /* SD卡读取一个sector，一个sector为512字节 */	
								{ 						
			           	if ( VS1003B_DREQ_BIT != 0 )	      /* 等待DREQ为高，请求数据输入 */
								 	{
				 						for (j=0; j<32; j++ ) /* VS1003的FIFO只有32个字节的缓冲 */
										{										
											VS1003B_WriteData( &buffer[count] );			//closed by sjw for compiler pass!	?????????????????????						
											count++;
										}
								  }		    	      	
							  }
       		   }
					   if (res || br == 0) break;   /* 出错或者到了MP3文件尾 */		   
           }
					 printf( " \r\n 播放结束 \r\n" );
/* ------------------- 一曲结束 --------------------*/ 
				   count = 0;
					 /* 根据VS1003的要求，在一曲结束后需发送2048个0来确保下一首的正常播放 */
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
					// TXDCS_SET( 1 );   /* 关闭VS1003数据端口 closed by sjw for compiler pass*/ 
				   f_close(&fsrc);	 /* 关闭打开的文件 */
					 PutChinese_strings22(10, 160, "播放结束", 0, 1);
				}   		                      
      }
    } /* while (f_readdir(&dirs, &finfo) == FR_OK) */  
  } /* if (f_opendir(&dirs, path) == FR_OK)  */	  
} /* end of MP3_Play */

/*
 * 函数名：Read_ID3V1
 * 描述  ：从MP3文件尾读取ID3V1的信息，并将这些信息保存在一个全局数组中        
 * 输入  ：- FileObject: file system
 *         - info: struct tag_info
 * 输出  ：无
 * 说明  ：现在的mp3基本上都没有ID3V1 tag(在文件尾部)，有的是ID3V2 tag(在文件头部)。
 */
int Read_ID3V1(FIL *FileObject, struct tag_info *info)
{
    res = f_lseek(FileObject,FileObject->fsize - 128 ); /* ID3V1的信息包含在文件末尾的128个byte中 */
    res = f_read(FileObject, &readBuf, 128 , &n_Read);	/* 将ID3V1中的128个byte的信息读到缓冲区 */    

    if (strncmp("TAG", (char *) readBuf, 3) == 0)	      /* ID3V1的标签头必须是“TAG”，否则认为没有标签 */
    {				
        strncpy(info->title, (char *) readBuf + 3, MIN(30, sizeof(info->title) - 1)); 	    /* 标题 */
        strncpy(info->artist,(char *) readBuf + 3 + 30, MIN(30, sizeof(info->artist) - 1));	/* 作者 */
				strncpy(info->album,(char *) readBuf + 3 + 30 + 30, MIN(30, sizeof(info->album) - 1));	/* 专辑 */
				strncpy(info->year,(char *) readBuf + 3 + 30 + 30 + 30, MIN(4, sizeof(info->year) - 1));	/* 时间 */
				return TRUE;
    }
		else 
		{ 
			return FALSE; 
		}		
}

/*
 * 函数名：Read_ID3V2
 * 描述  ：从MP3文件头部读取ID3V2的信息，并将这些信息保存在一个全局数组中
 * 输入  ：- FileObject: file system
 *         - info: struct tag_info
 * 输出  ：无
 * 说明  ：MP3文件都有ID3V2，包含了作者，曲目，专辑等信息，长度不固定，扩展了ID3V1的信息量。
 */
void Read_ID3V2(FIL *FileObject, struct tag_info *info)
{
    uint32_t p = 0;
    
    res = f_lseek(FileObject,0); /* 定位到文件的头部 */
    res = f_read(FileObject, &readBuf, READBUF_SIZE , &n_Read); /* 从文件头部开始读取READBUF_SIZE个字节 */
    
    if (strncmp("ID3", (char *) readBuf, 3) == 0)	/* ID3V3的头部标签必须为“ID3” */
    {
        uint32_t tag_size, frame_size, i;
        uint8_t version_major;
        int frame_header_size;

        /* 标签大小，包括标签头的10个字节和所有标签帧的大小 */
        tag_size = ((uint32_t) readBuf[6] << 21) | ((uint32_t) readBuf[7] << 14) | ((uint16_t) readBuf[8] << 7) | readBuf[9];
        
        info->data_start = tag_size;
        version_major = readBuf[3];   /* 版本号为ID3V2.3时就记录为3 */

        if (version_major >= 3)
        {
            frame_header_size = 10;		/* ID3V2.3的标签头为10个字节 */
        }
        else
        {
            frame_header_size = 6;
        }
        i = p = 10;
        
        /* iterate through frames */
        while (p < tag_size)				 /* 从标签头后开始处理 */
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

            /* 帧标识"TT2"/"TIT2"表示内容为这首歌的 标题 */
            if (strncmp("TT2", (char *) readBuf + i, 3) == 0 || strncmp("TIT2", (char *) readBuf + i, 4) == 0)
            {
                strncpy(info->title, (char *) readBuf + i + frame_header_size + 1, MIN(frame_size - 1, sizeof(info->title) - 1));
                if( ( info->title[0] == 0xFE && info->title[1] == 0xFF ) || ( info->title[0] == 0xFF && info->title[1] == 0xFE ) )
                {
                    /* unicode 格式*/
                    memset(info->title,0,sizeof(info->title));
                    printf( "-- MP3 title no support unicode \r\n");			
                }       
            }

						/* 帧标识"TP1"/"TPE1"表示内容为这首歌的 作者 */
            else if (strncmp("TP1", (char *) readBuf + i, 3) == 0 || strncmp("TPE1", (char *) readBuf + i, 4) == 0)
            {
                strncpy(info->artist, (char *) readBuf + i + frame_header_size + 1, MIN(frame_size - 1, sizeof(info->artist) - 1));
                
                if( ( info->artist[0] == 0xFE && info->artist[1] == 0xFF ) || ( info->artist[0] == 0xFF && info->artist[1] == 0xFE ) )
                {
                    /* unicode 格式*/
                    memset(info->artist,0,sizeof(info->artist));
                    printf( "-- MP3 artist no support unicode \r\n");
                }
            }
            
            p += frame_size + frame_header_size;
            i += frame_size + frame_header_size;
        }
    }
}

/******************* (C) COPYRIGHT 2011 野火嵌入式开发工作室 *****END OF FILE****/
