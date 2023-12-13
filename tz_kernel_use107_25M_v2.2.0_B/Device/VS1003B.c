#include 	"VS1003B.h"
#include 	"SPECREW.h"
#include  "mp3play.h"
#define 	SPI_SPEED_LOW 	 0


//STM32有硬件SPI的。最好不要模拟
//https://ishare.iask.sina.com.cn/f/brK42nCEImF.html                 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

static uint8_t VS1003_SPI_ReadWriteByte( uint8_t TxData );

 u8 readBuf[READBUF_SIZE];

u16 VS1003_GetDecodeTime(void);
//得到mp3的播放时间 n sec

/*
和其它芯片一样，初始化对于vs10xx同样非常重要，过程如下：
1.硬件复位；接xRESET拉低
2.延时，将xDCS、xCS、xRESET拉高
3。向mode中写入0x0804
4.等待DREQ变高
5.设置vs的时钟，SCI_CLOCKF=0x9800,3倍频
6.设置vs的采样率:SCI_AUDATA=0xbb81,采样率48K，立体声
7.设置重音：SCI_BASS=0x0055
8.设置音量：SCI_VOL=0x3030  最大
9.向vs发送4个字节的无效数据，用以启动SPI的发送
在初始化后，还要着重检查一下vs的模拟部分是否正常，将vs的所有DVDD,AVDD
管脚以及xRESET、TEST（第32p）接3.3伏，然后测量vs的44个引脚RCAP，应该在1.3V
左右，否则芯片的模拟部分未正常工作！！

之后就可以让vs进行正弦测试了



VS1053的应用其实非常简单，基本的步骤如下：

    1. 编写好SPI总线驱动代码；

    2. 编写好VS1053初始化代码；

    3. 编写正弦波测试代码；

    4. 内存测试代码。

完成以上几个步骤后就可以进行MP3解码了。
void VS1053SineTest(uint8 freq){
    uint8 i;
    uint8 test[] = {0x53, 0xEF, 0x6E, 0x24, 0x00, 0x00, 0x00, 0x00}; // 向vs发送正弦测试命令
    uint8 back[] = {0x45, 0x78, 0x69, 0x74, 0x00, 0x00, 0x00, 0x00}; // 向vs发送退出测试命令


 VS_XRESET_CLR();         // xreset = 0
 VS1053_Delay(100);
 SSP1Send(0xFF);         // 发送一个字节的无效数据，启动SPI传输

 VS_CS_SET();            // cs = 1
 VS_XDCS_SET();          // xdcs = 1
 VS_XRESET_SET();        // xreset = 1
 VS1053_Delay(100);

 VS1053WriteReg(VS_SCI_MODE, 0x0820); // enter vs1003 test model
 while (VS_DREQ_PIN() == 0);          // wait for DREQ Highlevel

 GPIOSetValue(1, 2, 0);     // xdcs = 0
 test[3] = freq;       // 写入频率
 for (i=0; i<8; i++){
     VS1053WriteData(test[i]);   // 程序执行到这里后应该能从耳机听到一个单一频率的声音
 }

 VS_XDCS_SET();             // xdcs = 1
 VS1053_Delay(100000);

 GPIOSetValue(1, 2, 0);     // xdcs = 0
 for (i=0; i<8; i++)
 {
     VS1053WriteData(back[i]);   // 退出正弦测试
 }

 VS_XDCS_SET();             // xdcs = 1
 VS1053_Delay(200);
}
*/



/*************************************************

     VS1003B延时 72M下13us

*************************************************/
void VS1003B_Delay(INT16U time)
{
    INT16U i;

    for(; time > 0; time--){
        for(i = 0; i < 100; i++);
    }
}  		  

/********************************

  VS1003写命令    写命令的过程如下：

 1.等待DREQ为高（当DREQ为低时，说明芯片还没有就绪）

 2.将XCS（命令片选）拉低

 3.写入0x02

 4.写入寄存器地址

 5.分别写入数据的高字节与低字节

 6.将XCS置高
 
**********************************/
void VS1003B_CMD_Write(INT8U address, INT16U data,INT8U device)//OK!
{  
	if(device==1){
    while(VS1003B_WAIT_DREQ( )==0);            //等待命令传输结束--等待空闲
    SPI1_SetSpeed(0);//低速   
    MP3_xDCS(1);		 			//xDCS=1;
	  MP3_xCS(0); 				  //xCS=0
	  SPI1_ReadWriteByte(VS_WRITE_COMMAND);	//发送VS1003的写命令
    SPI1_ReadWriteByte(address); 			//地址
    SPI1_ReadWriteByte(data>>8); 			//发送高八位
    SPI1_ReadWriteByte(data);    			//第八位	
    MP3_xCS(1);  					//xCS=1
    SPI1_SetSpeed(1);//高速
	}else if(device==2){
		while(VS1003B_WAIT_DREQ( )==0);            //等待命令传输结束--等待空闲
    SPI2_SetSpeed(0);//低速   
    MP3_xDCS(1);		 			//xDCS=1;
	  MP3_xCS(0); 				  //xCS=0
	  SPI2_ReadWriteByte(VS_WRITE_COMMAND);	//发送VS1003的写命令
    SPI2_ReadWriteByte(address); 			//地址
    SPI2_ReadWriteByte(data>>8); 			//发送高八位
    SPI2_ReadWriteByte(data);    			//第八位	
    MP3_xCS(1);  					//xCS=1
    SPI2_SetSpeed(1);//高速
	}
} 


/*******************************************************************************
* Function Name  : VS1003_WriteData
* Description    : VS1003写数据
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/  
void VS1003B_WriteData( uint8_t *buf)
{		
   uint8_t  count = 32;

   MP3_xDCS(0);   
   while( count-- )
   {
	  VS1003_SPI_ReadWriteByte( *buf++ );
   }
   MP3_xDCS(1);  
   MP3_xCS(1);  
} 


/********************************

  VS1003写数据  br最大值为32

* Function Name  : VS1003_WriteData
* Description    : VS1003写数据
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/  
void VS1003B_DATA_Write(unsigned char *buf, INT8U bw)
{
    INT8U i;
 
	   MP3_xDCS(0);			//xDCS=0
	  
	   //while(VS1003B_WAIT_DREQ( )==0);	//不必要这条，因为可以一次写入32个字节！
     for(i = 0; i < bw; i++){
        SPI2_ReadWriteByte(*buf++);
     }   	
     MP3_xDCS(1);					//xDCS=1;
		 MP3_xCS(1); 			    //xCS=1
}



/********************************

  VS1003读寄存器 
//读VS1003的寄存器           
//读VS1003
//注意不要用倍速读取,会出错


* Function Name  : VS1003_ReadReg
* Description    : VS1003读寄存器
* Input          : - reg: 命令地址
* Output         : None
* Return         : - value: 数据
* Attention		 : None
*******************************************************************************/
INT16U VS1003B_REG_Read(INT8U address)
{ 
    INT16U temp = 0; 

    while(VS1003B_WAIT_DREQ( ) == 0);		//等待 空闲
    SPI2_SetSpeed(0);        //低速 
	 MP3_xCS(0);   				     //xCS=0;选中命令传输
	  MP3_xDCS(1);	  			   //xDCS=1;
	 
    SPI2_ReadWriteByte(VS_READ_COMMAND);//发送VS1003的读命令
    SPI2_ReadWriteByte(address);        //地址
    temp = SPI2_ReadWriteByte(0xff);    //读取高字节
    temp = temp << 8;
    temp |= SPI2_ReadWriteByte(0xff);   //读取低字节
    MP3_xCS(1); 	
    SPI2_SetSpeed(1);       //高速
    return temp; 
}  





/****************************************

     VS1003B 复位解码时间

******************************************/ 
void VS1003B_ResetDecodeTime(void)
{
    VS1003B_CMD_Write(SPI_DECODE_TIME,0x0000,2);
    VS1003B_CMD_Write(SPI_DECODE_TIME,0x0000,2);//操作两次
}




/*******************************************************************************
* Function Name  : SD_SPIDrive_Init
* Description    : VS1003 SPI Init
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
如果CPHA(时钟相位)位被置位，SCK 时钟的第二个边沿(CPOL 位为0 时就是下
	降沿，CPOL 位为1 时就是上升沿)进行数据位的采样。数据在第一个时钟边沿被锁存。
	
	如果CPHA 位被复位，SCK 时钟的第一边沿(CPOL 位为0 时就是下降
	沿，CPOL 位为1 时就是上升沿)进行数据位采样。数据在第二个时钟边沿被锁存。

单片机SPI1主   SD卡从，vs1003从，驱动VS1003播放速度慢，没有声音、失败，注意上电VS1003最大SPI速度2M 
VS1003 12M晶振，上电后， SIP最大速度是CLKI/6，因为CLKI是12M，还没有设置倍频，所以SPI最大速度是2M。
如果单片机SPI设置速度超过2M。很可能初始化VS1003失败，导致没有声音播放，或者播放慢速问题。 



单片机SPI 一个接口同时接两个SPI从机时，注意从机SPI最大速度。
这里SPI FLASH 速度足够快，但是VS1003，初始化时，必须把SPI速度降下来。
CLKI倍频后，如3倍频，初始化完后，SPI 再提高速度。不超过CLKI/6 ，就可以正常驱动解码MP3了。 
*******************************************************************************/
void SD_SPIDrive_Init(uint8_t device)
{
  SPI_InitTypeDef  SPI_InitStructure;

		
	if(device==1)
	{
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE);	
			SPI_Cmd(SPI1, DISABLE);/* Disable SPI1  */
		 
			/* SPI1 configuration */
			SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
			SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
			SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
			//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//这样spi的开始速度为72M/128=562.5K
			SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
			SPI_InitStructure.SPI_CRCPolynomial = 7;
			SPI_Init(SPI1, &SPI_InitStructure);
			/* Enable SPI1  */
			SPI_Cmd(SPI1, ENABLE);
		
	}else if(device==2){
      RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2,ENABLE ); //低速APB(APB1)
			SPI_Cmd(SPI2, DISABLE);/* Disable SPI2  */
		 
			/* SPIx configuration */
			SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
			SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      //设置SPI工作模式:设置为主SPI
			SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  //设置SPI的数据大小:SPI发送接收8位帧结构
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                        //串行同步时钟的空闲状态为高电平
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                       //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
			SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;           //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
			//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//这样spi的开始速度为72M/128=562.5K   //定义波特率预分频的值:波特率预分频值为256
			SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
			SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC值计算的多项式
			SPI_Init(SPI2, &SPI_InitStructure);                //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
			
		
		/* Enable SPI2  */
			SPI_Cmd(SPI2, ENABLE);                                               //使能SPI外设
		  SPI2_ReadWriteByte(0xff);//启动传输
	}
}


/*******************************************************************************
* Function Name  : VS1003B_HardReset
* Description    : VS1003??
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003B_HardReset(void)
{
   MP3_Reset(0);
   DelayMs(10);
   SPI2_ReadWriteByte(0xFF);
   MP3_xDCS(1);	  //xDCS  取消数据传输
   MP3_xCS(1);    //xCS   取消命令传输 
   MP3_Reset(1); //复位结束
   while(VS1003B_WAIT_DREQ( ) == 0);//等待 空闲
}

/********************************

  VS1003软复位    VS1003的初始化

如其它芯片一样，初始化对于VS1003来说同样是极其重要的。初始化的过程大致是这样的：

1.硬件复位：接XRESET拉低

2.延时，将XDCS、XCS、XRESET置高

3.向MODE中写入0X0804

4.等待DREQ为高

5.设置VS1003的时钟：SCI_CLOCKF=0x9800，3倍频

6.设置VS1003的采样率：SPI_AUDATA=0xbb81，采样率48k，立体声

7.设置重音：SPI_BASS=0x0055

8.设置音量：SCI_VOL=0x2020

9.这一步被很多人忽视，向VS1003发送4个字节的无效数据，用以启动SPI发送




在进行了正确的初始化后，还要着重检查一下VS1003的模拟部分是否正常

将VS1003的所有DVDD、AVDD管脚以及XRESET、TEST（第32个引脚）接+3.0V，
然后测量RCAP引脚，它应该是1.3V左右，否则芯片模拟部分未正常工作。


●软件复位：SPI_MODE = 0x0804；
●等待DREQ为高（软件复位结束）；
●设置VS1003的时钟：SCI_CLOCKF = 0x9800，3倍频；
●设置VS1003的采样率：SPI_AUDATA = 0xBB81，采样率48k，立体声；
●设置重音：SPI_BASS = 0x0055；
●设置音量：SCI_VOL = 0x2020；
●向vs1003发送4个字节无效数据，用以启动SPI发送。



	
CLOCKF 寄存器，这个寄存器用来设置时钟频率、倍频等相关信息，该寄存器的各位描述如表所示：
CLOCKF 寄存器
位	              15:13	                     12:11	                   10:0

名称              SC_MULT                    SC_ADD                    SC_FREQ

描述              时钟倍频数                  允许倍频                   时钟频率

说明	 CLKI=XTALI× (SC_MULT× 0.5+1)     倍频增量 =SC_ADD*0.5      当外部时钟频率不为12.288Mhz 时，外部时钟的频率。
																	 外部时钟频率为12.288Mhz 时，此部分设置为 0
SC_FREQ 是以 4Khz 为步进的一个时钟寄存器，当外部时钟不是 12.288M 的时候，
其计算公式为： SC_FREQ=(XTALI-8000000)/4000 式中为 XTALI 的单位为 Hz。
上表中 CLKI 是内部时钟频率， XTALI 是外部晶振的时钟频率。
由于我们使用的是 12.288M 的晶振，所以SC_FREQ = 0；

用模块播放音频文件非常的简单，一般的音频文件（MP3/WMA/OGG/WAV/MIDI/AAC等），只需要简单的 3 步操作即可实现音频播放。
（1）复位VS1003
这里包括了硬复位和软复位，是为了让VS1003的状态回到原始状态，准备解码下一首歌曲。这里建议在每首歌曲播放之前都执行一次硬件复位和软件复位，以便更好的播放音乐。
（2）配置VS1003相关寄存器
配置的寄存器包括 VS1003 的模式寄存器（MODE）、时钟寄存器（CLOCKF）、音调寄存器（BASS）、音量寄存器（VOL）等。
（3）发送音频数据
当经过以上两步配置以后，我们剩下来要做的事情，就是往VS1003里面扔音频数据了，


	
	//VS1003B_CMD_Write(SPI_CLOCKF, 0X4430);    // 2.0x 12.288MHz
	//VS1003B_CMD_Write(SPI_CLOCKF, 0X4000);    // 2.0x 12.288MHz
	
    //VS1003B_CMD_Write(SPI_CLOCKF, 0XE000 | 0x1800 | 0x3ff);
    //VS1003B_CMD_Write(SPI_AUDATA, 0Xfefe); 	//采样率65k，立体声	
	
	8.6.6 SCI AUDATA (RW)
When decoding correct data, the current sample rate and number of channels can be found in bits 15:1
and 0 of SCI AUDATA, respectively. Bits 15:1 contain the sample rate divided by two, and bit 0 is 0 for
mono data and 1 for stereo. Writing to SCI AUDATA will change the sample rate directly.
Note: due to a bug, an odd sample rate reverses the operation of the stereo bit in VS1003b.
Example: 44100 Hz stereo data reads as 0xAC45 (44101).
Example: 11025 Hz mono data reads as 0x2B10 (11025).
Example: 11025 Hz stereo data reads as 0x2B11 (11026).
Example: Writing 0xAC80 sets sample rate to 44160 Hz, stereo mode does not change.
	
   // VS1003B_CMD_Write(SPI_AUDATA, 0Xac45); 	//采样率44100，立体声

**********************************/




void VS1003B_SoftReset(void){//软复位
	
	
	 INT8U	count=0;
	
	
	 VS1003B_HardReset();//硬件复位结束
	
	
   VS1003B_CMD_Write(SPI_MODE,0x0804,2);// 软件复位,新模式	
   while(VS1003B_WAIT_DREQ( )==0);
   
	 while(VS1003B_REG_Read(SPI_CLOCKF)!=0x9800){//设置VS10XX的时钟,3.5倍频 ,2xADD
			VS1003B_CMD_Write(SPI_CLOCKF, 0X9800,2);    // 3.0x 12.288MHz
			DelayMs(10);
			count++;
			if(count>200) break;	
	 } 
	 count=0;
	 while(VS1003B_WAIT_DREQ( )==0);		//等待DREQ信号变高
	
	 while(VS1003B_REG_Read(SPI_AUDATA)!=0xbb81){// 采样率48k，立体声
			VS1003B_CMD_Write(SPI_AUDATA, 0xbb81,2); 	//(0xbb81)采样率48k，立体声//(0Xfefe); 	//采样率65k，立体声	
			DelayMs(10);
			count++;
			if(count>200) break;	
	 } 
	 count=0;
	 while(VS1003B_WAIT_DREQ( )==0);		//等待DREQ信号变高
	
	 while(VS1003B_REG_Read(SPI_BASS)!=0x0055){// 设置重低音，0x00F6对60HZ以下的音频信号进行15dB的增强，0x7A00对10KHZ以上的信号进行10.5dB的增强
			VS1003B_CMD_Write(SPI_BASS,0x0055,2);
			DelayMs(10);
			count++;
			if(count>200) break;	
	 }  
	 count=0;
	 while(VS1003B_WAIT_DREQ( )==0);
	 
	 while(VS1003B_REG_Read(SPI_VOL)!=0x1010){// VS10XX 音量
			VS1003B_CMD_Write(SPI_VOL,0x00002,2);  	
		  //VS1003B_CMD_Write(SPI_VOL,0x3030,2);   //音量 0x3030 		这是控制VS1003的音量！！最大 
			DelayMs(10);
			count++;
			if(count>200) break;	
	  }  
    
  VS1003B_ResetDecodeTime();				 //复位解码时间     
    
    while(VS1003B_WAIT_DREQ( )==0); 		//等待DREQ信号变高
    MP3_xDCS(0);		 					        //xDCS=0;选中数据传输
    MP3_xCS(1);  					            //xCS=1;
    SPI2_ReadWriteByte(0xFF);         //向vs1003发送4个字节无效数据，用以启动SPI发送  
    SPI2_ReadWriteByte(0xFF);
    SPI2_ReadWriteByte(0xFF);
    SPI2_ReadWriteByte(0xFF);
    MP3_xDCS(1);	   				           //xDCS=1;取消数据传输
		DelayMs(10);
}


	


/*
	检查SCI命令是否正确写入
给音量控制寄存器SCI_VOL循环写入最高值和最低值，正常情况下能从耳机听到滴滴
的声音，具体步骤如下：
●拉低xCS；
●设置音量最高：SCI_VOL = 0x0000；
●拉高xCS；
●等待500ms，这个时间控制在0.5到1s之间，太大太小可能都无法听到；
●拉低xCS；
●设置音量最低：SCI_VOL = 0xFFFF；
●等待500ms，道理同上；
●拉高xCS；
●循环，否则以上步骤无法识别。


9．7．4 SCI 测试
SCI 测试通过发送8字节的序列初始化，0x53 0x70 0xEE n 0 0 0 0,这里的n 减去48 为测试的寄存
器编号。给定的被测试寄存器的内容被复制到SCI_HDAT0,若被测试的寄存器为SCI_HDAT0，则其结果被复制
到SCI_HDAT1。
例如：若n等于48，则寄存器0（SCI_MODE）的内容被复制到SCI_HDAT0.

*/

void VS1003B_SCI_Test(void)
{   
	  MP3_xCS(1); 
	  MP3_xDCS(0);		
    VS1003B_CMD_Write(SPI_MODE,0x0820,2);	//进入vs1003的测试模式	      
	  MP3_xDCS(0);		 				//xDCS=0;选中数据传输
    MP3_xCS(1);  				    //xCS=1;
    SPI1_ReadWriteByte(0x53);
    SPI1_ReadWriteByte(0x70);
    SPI1_ReadWriteByte(0xee);
    SPI1_ReadWriteByte(48);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);	
    MP3_xDCS(1);	    			//xDCS=1;取消数据传输
}














void VS1003B_DetectSCIOk(void){
	
	VS1003B_CMD_Write(SPI_MODE,0x0820,2);	     //进入vs1003的测试模式	      
	while(VS1003B_WAIT_DREQ( )==0);            //等待命令传输结束--等待空闲

	MP3_xCS(0); 
	VS1003B_CMD_Write(SPI_VOL,0xfefe,2);      //音量 
	MP3_xCS(1); 
	while(VS1003B_WAIT_DREQ( )==0);            //等待命令传输结束--等待空闲

	MP3_xCS(0); 
	VS1003B_CMD_Write(SPI_VOL,0xffff,2);      
	MP3_xCS(1); 
	while(VS1003B_WAIT_DREQ( )==0);            //等待命令传输结束--等待空闲
}



/****************************************

      VS1003 IMA ADPCM录音初始化

*****************************************/
void InitRecordADPCM(void)
{
    VS1003B_CMD_Write(SPI_VOL,     0x1414,2); //  录音音量
    VS1003B_CMD_Write(SPI_BASS,    0x0,2);    //  录音音效
    VS1003B_CMD_Write(SPI_CLOCKF,  0x4430,2); //  内频Fc = 2.0 * 12.288MHZ
    VS1003B_CMD_Write(SPI_AICTRL0, 12,2);     //  分频系数D=12，采样率8KHZ；D=8，采样率12KHZ；D=6，采样率16KHZ
    VS1003B_CMD_Write(SPI_AICTRL1, 0,2);      //  使能自动增益
    VS1003B_CMD_Write(SPI_MODE,    0x1804,2); //  使能麦克风录音
}

/********************************

  加载频谱分析的代码到VS1003

**********************************/
void VS1003B_LoadPatch(void)
{
    u16 i;

    for (i = 0; i < 943; i++){
        VS1003B_CMD_Write(atab[i],dtab[i],2); 
    }
}

/********************************

  得到频谱数据

**********************************/
void VS1003B_GetSpec(INT8U *p)
{
    INT8U i;

    VS1003B_CMD_Write(SPI_WRAMADDR,0x1804,2);                                                                                             
    for(i = 0; i < 14; i++){                                                                               
        *p++ = VS1003B_REG_Read(SPI_WRAM) & 0x63;//取小于100的数    
    } 
}

/****************************************

     VS1003B正旋波测试
 uint8 test[] = {0x53, 0xEF, 0x6E, 0x24, 0x00, 0x00, 0x00, 0x00}; // 向vs发送正弦测试命令
 uint8 back[] = {0x45, 0x78, 0x69, 0x74, 0x00, 0x00, 0x00, 0x00}; // 向vs发送退出测试命令

这里提供启动正弦测试的流程，在真实的硬件运行通过，最终的效果是在耳机中听到单一频率的正弦音（频率可以通过程序来更改）。

具体流程如下：

 1.进入VS1003的测试模式：SPI_MODE=0X0820

 2.等待DREQ为高

 3.将XDCS接低，而XCS要置高，选择VS1003的数据接口

 4.向VS1003发送正弦测试命令：0X53 0XEF 0X6E 0X30 0X00 0X00 0X00 0X00

   其中0X30为频率，用户可以修改为其它值

 5.延时一段时间

 6.退出正弦测试，发送命令：0X45 0X78 0X69 0X74 0X00 0X00 0X00 0X00

 7.延时一段时间

 8.循环以上流程

//使正弦波的频率依次增加，适当延时，这样在耳机中就能听到音调越来越高的声音
******************************************/
void VS1003B_SineTest(INT8U fre)
{   
//	VS1003B_RESET_ENABLE;
//	SPI1_ReadWriteByte(0xff);               // 启动传输
//	VS1003B_XDCS_DISABLE;
//	VS1003B_XCS_DISABLE;
//	VS1003B_RESET_DISABLE;
	
//#if VS1003_DEBUG      187     int16u_t data = 0x0;;188     printf("Vs1003_Sine_Test:begin\nGet in SinTest Mode\n");189     #endif
 //#if VS1003_DEBUG     193     data = Vs1003_CMD_Read(SPI_MODE);194     printf("Read REGS-SIN, SPI_MODE=%x\n",data);195     #endif	
   
	  VS1003B_CMD_Write(SPI_MODE,0x0820,2);	//进入vs1003的测试模式 启动测试，向 0 号寄存器写入 0x0820 SM_SDINEW 为 1  SM_TEST 为 1 	
	  while(VS1003B_WAIT_DREQ( ) == 0);		    //等待空  VS1003的DREQ为高才能写入数据
	
	
	  MP3_xDCS(0);		 				  //xDCS=0;选中数据传输  打开数据片选，即开启SDI传输
    MP3_xCS(1);   				  //xCS=1;
    SPI2_ReadWriteByte(0x53);//写入以下 8 个字节 ,进入正弦测试
    SPI2_ReadWriteByte(0xef);
    SPI2_ReadWriteByte(0x6e);
    SPI2_ReadWriteByte(fre); /* 参数 x 用来调整正弦测试中正弦波的频率*/
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);	
		
		DelayMs(5000);
    //while(VS1003B_WAIT_DREQ( ) == 0);		//等待空   这里延时一段时间 ,可以听到“正弦音”或者用延时函数代替！
		
    SPI2_ReadWriteByte(0x45); /* 写入以下 8 个字节 ,退出正弦测试 */
	  SPI2_ReadWriteByte(0x78);
    SPI2_ReadWriteByte(0x69);
    SPI2_ReadWriteByte(0x74);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);  
		
	 //while(VS1003B_WAIT_DREQ( ) == 0);		//等待空   这里延时一段时间 ,可以听到“正弦音”或者用延时函数代替！
	  DelayMs(5000);

    MP3_xDCS(1);	   			//xDCS=1;取消数据传输  关闭数据片选
}





/*
** 函数名称 : void VS_SinTest(INT8U x).
** 功能描述 : 正弦测试函数 ,检查 vs1003是否正常 .
** 输入参数 : INT8U x 正弦波频率 .
** 输出参数 : None.
** 返回参数 : None.
版权声明：本文为CSDN博主「yi_tianchou」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/yi_tianchou/article/details/104724302
*/































/*******************************************************************************
* Function Name  : VS1003_RamTest
* Description    : VS1003 RAM??
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/																			 
//void VS1003_RamTest(void)
//{
//   volatile uint16_t value;
//     
//   VS1003_Reset();     
//   VS1003_WriteReg(SPI_MODE,0x0820);/* 进入vs1003的测试模式 */
//   while((GPIO_ReadInputDataBit(VS1003B_DREQ_PORT, VS1003B_DREQ_BIT)) == 0);//等待空闲
//   MP3_xDCS(0);	       			     /* xDCS = 1,??vs1003????? */
//   VS1003_SPI_ReadWriteByte(0x4d);
//   VS1003_SPI_ReadWriteByte(0xea);
//   VS1003_SPI_ReadWriteByte(0x6d);
//   VS1003_SPI_ReadWriteByte(0x54);
//   VS1003_SPI_ReadWriteByte(0x00);
//   VS1003_SPI_ReadWriteByte(0x00);
//   VS1003_SPI_ReadWriteByte(0x00);
//   VS1003_SPI_ReadWriteByte(0x00);
//   delay_ms(50);  
//   MP3_xDCS(1);
//   value = VS1003_ReadReg(SPI_HDAT0); /* 如果得到的值为0x807F，则表明完好。 */
///printf("regvalueH:%x\n",regvalue>>8);//输出结果 
        //printf("regvalueL:%x\n",regvalue&0xff);//输出结果 

//}     



/****************************************

     VS1003B RAM 测试
     返回0X807F，成功
* FunctionName   : VS1053RamTest()
* Description    : 内存测试，0x8000表示测试完成，0x83FF表示完好
* EntryParameter : None
* ReturnValue    : 完好返回0，否则返回1
 uint8 test[] = {0x4D, 0xEA, 0x6D, 0x54, 0x00, 0x00, 0x00, 0x00}; // 


9．7．3 存储器测试
存储器测试模式通过发送8 字节的序列0x4D 0xEA 0x6D 0x54 0 0 0 0来初始化。在此序列之后，等
待500000 个时钟周期，就可以从SCI 寄存器SCI_HDAT0中读取结果。读出数据的每位解释如下：
位                   掩码            含义

15                  0x8000           测试结束
14:7                                 未使用
6                   0x0040           所有测试成功
5                   0x0020           I RAM 完好
4                   0x0010           Y RAM 完好
3                   0x0008           X RAM 完好
2                   0x0004           I ROM 完好
1                   0x0002           Y ROM 完好
0                   0x0001           X ROM 完好
                   0x807F 所有都完好
******************************************/
INT16U VS1003B_RAMTest(void)
{   
    INT16U state = 0;
    	 
    VS1003B_CMD_Write(SPI_MODE,0x0820,2);	//进入vs1003的测试模式    	   
    while(VS1003B_WAIT_DREQ( ) == 0);		//等待空闲
    
	  MP3_xDCS(0);		  				//xDCS=0;选中数据传输
    MP3_xCS(1);  				      //xCS=1;
    SPI2_ReadWriteByte(0x4d);
    SPI2_ReadWriteByte(0xea);
    SPI2_ReadWriteByte(0x6d);
    SPI2_ReadWriteByte(0x54);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
	
	  DelayMs(50);  
    MP3_xDCS(1);	   			   //xDCS=1;取消数据传输
	
    while(VS1003B_WAIT_DREQ( ) == 0);
    state  = VS1003B_REG_Read(SPI_HDAT0) << 8;
    state |= VS1003B_REG_Read(SPI_HDAT1);/* 如果得到的值为0x807F，则表明完好。 */
    
    return(state);		 
}



/*
这里抛开存储介质不谈，只谈数据的写入方法。其实写入数据的方法十分简单。
主要就是看DREQ信号，在VS1003的FIFO能够接受数据的时候输出高电平。
每次可以写入32个字节的数据。而DREQ变低时，单片机就要停止数据的发送。

具体的写数据的方法如下：
1.将XDCS拉低
2.等待DREQ为高
3.通过SPI写入数据
4.在文件没有结束前不断重复2与3操作
5.在所有的数据都发送完毕后，最后发送2048个无效字节，用以清除VS1003的数据缓冲区
6.将XDCS置高


for(temp=0;temp<2048;temp++)

 {

  DREQ=1;

  while(!DREQ);

  spi_write(0);

 }

 XDCS=1;

*/





		

void SD_SPIPin_Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;
		SPI_InitTypeDef  SPI_InitStructure;
		
		
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	
  
	// 配置SPI1串行通讯引脚  SD卡片选引脚SD_CS    SPI1_SCK, SPI1_MISO, SPI1_MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}


/*******************************************************************************
* Function Name  : VS1003_Init
* Description    : VS1003端口初始化
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void VS1003BPin_Init(void)
{		  
  GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |  RCC_APB2Periph_GPIOB|  RCC_APB2Periph_GPIOC  , ENABLE);
	  
	/* SPI的IO口和SPI外设打开时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);


	//SPI的IO口设置 
	
	 //GPIO_Pin_12  NSS note that NSS pin of the SPI slave is use to select the
   // device, if it is pulled up, SPI slave will not shift
   // any byte to its shift register

	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;  // SPI    NSS由软件控制  GPIO_Pin_12 |
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		/*
		NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = SPI2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);
*/
	
	
	// 设置VS1003控制引脚:            DREQ设置为输入,   XREST   xDCS 设置为输出
		//******************************************
		//******************************************
	
		GPIO_InitStructure.GPIO_Pin = VS1003B_DREQ_BIT ;  // 数据控制端口    DREQ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//DREQ设置为输入,
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VS1003B_DREQ_PORT, &GPIO_InitStructure);	
	
	
	
	  GPIO_InitStructure.GPIO_Pin =VS1003B_RESET_BIT;		  		//XREST   硬件缺少一根IO复位线，顶层图没连接上线！????????????????????????????
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VS1003B_RESET_PORT, &GPIO_InitStructure);
	

    GPIO_InitStructure.GPIO_Pin =   VS1003B_DATA_CS_BIT;	//   xDCS 	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VS1003B_DATA_CS_PORT, &GPIO_InitStructure);
	
	
	  GPIO_InitStructure.GPIO_Pin =   VS1003B_CMD_CS_BIT; 	//     xDS 	端口分为A  B，添加这四句，血的教训！！！！
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VS1003B_CMD_CS_PORT, &GPIO_InitStructure);
	
	
		MP3_Reset(0);
		VS1003B_Delay(2);
		MP3_Reset(1);
		MP3_xDCS(1); 
		MP3_xCS(1); 
}


/*******************************************************************************
* Function Name  : VS1003_SPI_ReadWriteByte
* Description    : None
* Input          : - TxData: Write Byte
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static uint8_t VS1003_SPI_ReadWriteByte( uint8_t TxData )
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI2, TxData);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI2);
}





void TestReadFile(void)
{
	FRESULT   result;
	FATFS 		fs;
	DIR 			DirInf;
  FIL 			file;
	UINT 		  br;             		// File R/W count  文件读计数器  
	
 
	f_mount(&fs,"0:", 0);  	     // 注册文件系统--//挂载SD卡 		
		
	// 打开文件 
	result = f_open(&file, "0:sjw.txt", FA_OPEN_ALWAYS | FA_READ);//记住：以前用FA_CREATE_ALWAYS | FA_READ
	if (result !=  FR_OK)
	{
		printf("Don't Find File:  sjw.txt\r\n");
		return;
	}else
	    printf("打开文件sjw.txt成功！！！\r\n");
	

	// 读取文件 
	result = f_read(&file, &readBuf, sizeof(readBuf) - 1, &br);
	if (br > 0){
		printf("\r\n sjw.txt 文件内容 : \r\n %s\r\n", readBuf);
		//readBuf[br]=0;
	}else{
		printf("\r\n sjw.txt.txt 文件内容 : \r\n");
	}
	//关闭文件
	f_close(&file);
	// 卸载文件系统 
	f_mount( NULL,"0", 0);
	
}


//FA_OPEN_ALWAYS   如果文件存在，则打开；否则，创建一个新文件。
void TestWriteFile(void)
{
		// 文件系统相关的变量			
  FRESULT  result;
  FATFS    fs;
	DIR      DirInf;
  FIL      file;
	UINT 		 bw;             		// File R/W count  文件写计数器  
	
	
  f_mount(&fs,"0:", 0);  	     // 注册文件系统--//挂载SD卡 				
		
	// 打开文件 
	result = f_open(&file, "0:sjw.txt", FA_OPEN_ALWAYS | FA_WRITE );//记住：以前用FA_CREATE_ALWAYS | FA_WRITE
		// 写一串数据 
	result = f_write(&file, "sjw is miss my baba & mama for ever! \r\n", 36, &bw);
	if (result == FR_OK){
		printf("sjw.txt 文件写入成功\r\n");
	}else{
		printf("sjw.txt 文件写入失败\r\n");
	}	

	//关闭文件
	f_close(&file);
	// 卸载文件系统 
	f_mount( NULL,"0", 0);
}
	
	
		

void SPI2_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	//pADC=&SPI2_RxBuf[160];
	//pDAC=&SPI2_TxBuf[160];
	
	NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;          
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&SPI2->DR;			//外设地址
//	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)SPI2_RxBuf;					//DMA1内存地址
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;											//数据传输方向:外设到内存
	DMA_InitStructure.DMA_BufferSize=320;								//DMA1缓存大小
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;				//外设地址不变
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; 								//内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; //数据宽度16位
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; 		//数据宽度16位
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;														//DMA1工作循环模式
	DMA_InitStructure.DMA_Priority=DMA_Priority_Low;											//DMA1通道4中优先级低
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;														//DMA1非内存到内存传输
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&SPI2->DR;			//外设地址
	//DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)SPI2_TxBuf;					//DMA1内存地址
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;											//数据传输方向:内存到外设
	DMA_InitStructure.DMA_BufferSize=320;								//DMA1缓存大小
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;				//外设地址不变
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; 								//内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; //数据宽度16位
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; 		//数据宽度16位
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;														//DMA1工作循环模式
	DMA_InitStructure.DMA_Priority=DMA_Priority_Low;											//DMA1通道5中优先级低
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;														//DMA1非内存到内存传输
	DMA_Init(DMA1_Channel5,&DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel4,DMA_IT_HT,ENABLE);
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	
	DMA_Cmd(DMA1_Channel4,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);
 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;		//SPI从机
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//发送接收16位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//时钟悬空低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//数据捕获于第1个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;       //CS引脚硬件配置
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//定义波特率预分频的值:波特率预分频值为16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//数据传输从MSB位开始
	SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx,ENABLE);
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx,ENABLE);
	SPI_Cmd(SPI2,ENABLE);
}
 

 /*
void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_HT4) == SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_HT4);
		pADC=&SPI2RxBuf[0];
		pDAC=&SPI2_TxBuf[0];
		SPI2_Flag=1;
	}
	if(DMA_GetITStatus(DMA1_IT_TC4) == SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TC4);
		pADC=&SPI2_RxBuf[160];
		pDAC=&SPI2_TxBuf[160];
		SPI2_Flag=1;
	}
}
————————————————
版权声明：本文为CSDN博主「Younique741」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_44065318/article/details/125883338


————————————————
版权声明：本文为CSDN博主「Younique741」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_44065318/article/details/125883338
*/


/****************************************

     VS1003B 读取解码时间  //得到mp3的播放时间 n sec

******************************************/ 
INT16U VS1003B_GetDecodeTime(void)
{
    return(VS1003B_REG_Read(SPI_DECODE_TIME));
}

/*
//得到mp3的播放时间 n sec
u16 VS1003_GetDecodeTime(void)
{
        return VS1003B_REG_Read(0x04);
}
*/