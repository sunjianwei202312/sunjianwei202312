/*****************************************************************

          SD卡 驱动程序
          修 改 人：LJ128
          创建时间：2008年8月3日
		  
有关SD卡接线的探索（为什么标准SD卡是九根线，而一般原理图上都是11根线或更多呢？）
首先说几个概念：
SD卡：<=2GB
SDHC卡（SD High Capacity，大容量SD卡）：4GB~32GB
SDXC卡（SD eXtended Capacity）：64GB~2TB，这是2009年SD协会发布的新标准
SDIO：SD Input Output 带有输入输出设备的SD卡

SD技术包含SD卡、SDHC卡和SDXC卡等，这三者是按照容量大小及协议差别而区分的，每次一升级均带来容量的飞越，
尤其是SD协会在CES 2009上宣布的新一代存储卡标准SDXC（SD eXtended Capacity）最大容量为2TB。
SD与SDHC从体积又分为标准卡、mini卡和micro卡，其中当属micro体积最小，仅为标准卡的四分之一，约指甲大小，但能力、可靠性、速度都与标准卡相同。

标准SD卡（Secure Digital，安全数字卡）的大小仅有24mm x 32mm x 2.1mm，约相当于邮票大小，重量仅为2克，然而却可以达到最大2GB的容量；
SDHC卡（SD High Capacity，大容量SD卡）容量范围扩展至从4GB至32GB，开发人员能选择指定有保证最低数据速率的三种数据写入速度，
三种SDHC速度等级 (等级 2、等级 4、等级 6) 每秒分别可传输至少 2MB、4MB、6MB的数据。


SD卡的接口可以支持SD卡模式和SPI模式两种操作模式。主机系统可以选择其中任一模式，SD卡模式允许4线的高速数据传输；
SPI模式允许简单通用的SPI通道接口，但是SPI模式相比于SD模式的劣势是丧失了高速度。

*****************************************************************/

#include "SD_driver.h"

void DelayMs(vu32 m);
void DelayUs(vu32 m);
static void GPIO_Configuration(void);


u8  SD_Type = SD_TYPE_MMC; // SD卡的类型
//u8  SD_Type = SD_TYPE_V1; // SD卡的类型






void SPI1_SetSpeed(u8 SpeedSet)
{
    SPI_InitTypeDef 	SPI_InitStructure ;
    
    SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;
    SPI_InitStructure.SPI_Mode=SPI_Mode_Master ;
    SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b ;
    SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge ;
    SPI_InitStructure.SPI_NSS=SPI_NSS_Soft ;
    
	//如果速度设置输入0，则低速模式，非0则高速模式
    if(SpeedSet==SPI_SPEED_LOW)
    {
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;//尽可能的用低速！
    }
    else 
    {
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;//72/4=18mhz
    }
    //moon.mp3: 4707774 Byte size 目标文件 设为buffer[512]     
    //speed:实验测试数据，最大速度 392314 Byte/S，
    //Prescaler_128, 59592 Byte/S
    //Prescaler_64, 104617 Byte/S
    //Prescaler_32, 168134 Byte/S    162337 Byte/S
    //Prescaler_16, 261543 Byte/S    247777 Byte/S
    //Prescaler_8,  313851 Byte/S    336269 Byte/S
    //Prescaler_4,  392314 Byte/S    392314 Byte/S
    //Prescaler_2,  392314 Byte/S

    SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB ;
    SPI_InitStructure.SPI_CRCPolynomial=7 ;
    SPI_Init(SPI1,&SPI_InitStructure);
}





void SPI2_SetSpeed(u8 SpeedSet)
{
    SPI_InitTypeDef 	SPI_InitStructure ;
    
    SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;
    SPI_InitStructure.SPI_Mode=SPI_Mode_Master ;
    SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b ;
    SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge ;
    SPI_InitStructure.SPI_NSS=SPI_NSS_Soft ;
    
	//如果速度设置输入0，则低速模式，非0则高速模式
    if(SpeedSet==SPI_SPEED_LOW)
    {
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;//尽可能的用低速！
    }
    else 
    {
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;//72/4=18mhz
    }

    SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB ;
    SPI_InitStructure.SPI_CRCPolynomial=7 ;
    SPI_Init(SPI2,&SPI_InitStructure);
}



/*

//TXE：发送缓冲为空
//0：发送缓冲非空
//1：发送缓冲为空

	RXNE：接收缓冲非空 
	0：接收缓冲为空 
	1：接收缓冲非空 
*/
u8 SPI1_ReadWriteByte(u8 TxData)
{
  /*
	// Loop while DR register in not emplty 
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  // Send byte through the SPI1 peripheral 
  SPI_I2S_SendData(SPI1, TxData);

  //Wait to receive a byte 
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  //Return the byte read from the SPI bus 
  return SPI_I2S_ReceiveData(SPI1);
	*/
	
	
	u8 retry=0;                     
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){ 
			retry++;
			if(retry>200)return 0;
		}              
    SPI_I2S_SendData(SPI1, TxData);
    retry=0;

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){
        
        retry++;
        if(retry>200)return 0;
    }                                  
    return SPI_I2S_ReceiveData(SPI1);    
				
				/*
————————————————
版权声明：本文为CSDN博主「howareyou23」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/w942401053/article/details/125178639
				*/
}


//TXE：发送缓冲为空
//0：发送缓冲非空
//1：发送缓冲为空
u8 SPI2_ReadWriteByte(u8 TxData)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);//检查发送是否完成，完成以后再发送数据added by sjw

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI2, TxData);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);//检查接受标志位，是否可以接受added by sjw

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI2);
}

/*******************************************************************************
* Function Name  : SD_WaitReady
* Description    : 等待SD卡Ready
* Input          : None
* Output         : None
* Return         : u8 
*                   0： 成功
*                   other：失败
*******************************************************************************/
u8 SD_WaitReady(void)
{
    u8 r1;
    u16 retry;
    retry = 0;
    do{
        r1 = SPI1_ReadWriteByte(0xFF);
        if(retry==0xfffe)
        {
            return 1;
        }
    }while(r1!=0xFF);

    return 0;
}   	 



/*******************************************************************************
* Function Name  : SD_SendCommand
* Description    : 向SD卡发送一个命令
* Input          : u8 cmd   命令 
*                  u32 arg  命令参数
*                  u8 crc   crc校验值
* Output         : None
* Return         : u8 r1 SD卡返回的响应
*******************************************************************************/
u8 SD_SendCommand(u8 cmd, u32 arg, u8 crc)
{
    unsigned char r1;
    unsigned char Retry = 0;

  
    SPI1_ReadWriteByte(0xff);
    SD_CS_ENABLE();  //片选端置低，选中SD卡
   
	//发送
    SPI1_ReadWriteByte(cmd | 0x40);                         //分别写入命令
    SPI1_ReadWriteByte(arg >> 24);
    SPI1_ReadWriteByte(arg >> 16);
    SPI1_ReadWriteByte(arg >> 8);
    SPI1_ReadWriteByte(arg);
    SPI1_ReadWriteByte(crc);
   
	//等待响应，或超时退出
    while((r1 = SPI1_ReadWriteByte(0xFF))==0xFF)
    {
        Retry++;
        if(Retry > 200)
        {
            break;
        }
    }
    //关闭片选
    SD_CS_DISABLE();
    //在总线上额外增加8个时钟，让SD卡完成剩下的工作
    SPI1_ReadWriteByte(0xFF);
    //返回状态值
    return r1;
}


/*******************************************************************************
* Function Name  : SD_SendCommand_NoDeassert
* Description    : 向SD卡发送一个命令(结束是不失能片选，还有后续数据传来）
* Input          : u8 cmd   命令 
*                  u32 arg  命令参数
*                  u8 crc   crc校验值
* Output         : None
* Return         : u8 r1 SD卡返回的响应
*******************************************************************************/
u8 SD_SendCommand_NoDeassert(u8 cmd, u32 arg, u8 crc)
{
    unsigned char r1;
    unsigned char Retry = 0;

    //????????
    SPI1_ReadWriteByte(0xff);
    //片选端置低，选中SD卡
    SD_CS_ENABLE();

    //发送
    SPI1_ReadWriteByte(cmd | 0x40);                         //分别写入命令
    SPI1_ReadWriteByte(arg >> 24);
    SPI1_ReadWriteByte(arg >> 16);
    SPI1_ReadWriteByte(arg >> 8);
    SPI1_ReadWriteByte(arg);
    SPI1_ReadWriteByte(crc);

    //等待响应，或超时退出
    while((r1 = SPI1_ReadWriteByte(0xFF))==0xFF)
    {
        Retry++;
        if(Retry > 200)
        {
            break;
        }
    }
    //返回响应值
    return r1;
}

/*******************************************************************************
* Function Name  : SD_Init
* Description    : 初始化SD卡
* Input          : None
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  1：TIME_OUT
*                  2：没有插入SD卡

SD卡只能使用3.3V的IO电平，所以，MCU一定要能够支持3.3V的IO端口输出。注意：在SPI模式下，
CS/MOSI/MISO/CLK都需要加10~100K左右的上拉电阻。 
SD卡要进入SPI模式很简单，就是在SD卡收到复位命令（CMD0）时，CS为有效电平（低电平）则SPI模式被启用。不过在发送CMD0之前，要发送>74个时钟，
这是因为SD卡内部有个供电电压上升时间，大概为64个CLK，剩下的10个CLK用于SD卡同步，之后才能开始CMD0的操作，
在卡初始化的时候，                      CLK时钟最大不能超过400Khz！。  
ALENTEK MiniSTM32开发板使用的是SPI模式来读写SD卡，下面我们就重点介绍一下SD卡在SPI模式下的相关操作。
*******************************************************************************/

//// 函数名：MMC_SD_Init 
// 功  能：sd卡初始化 
// 参  数：无 
// 返回值：uint8 type         
// 卡类型返回值: 0x10 SD, 0x20 MMC 

u8 SD_Init(void)
{
    u16 i;      // 用来循环计数
    u8 r1;      // 存放SD卡的返回值
    u16 retry;  // 用来进行超时计数
   volatile u8 buff[6];

	
	
	  /* Configure SDIO interface GPIO */
   // GPIO_Configuration();
	
	  /* Enable the SDIO AHB Clock */
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, ENABLE);
  /* Enable the DMA2 Clock */
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
    //SDIO_DeInit();

	
	//要使用SD卡，那么首先肯定得对SD卡进行初始化，那么如何进行初始化呢？
	//协议规定了在给SD卡上电之后需要给出至少74个时钟脉冲后，才能进行相关的SD初始化工作
    SD_PWR_ON();       //SD卡上电
    SPI1_SetSpeed(0);  //设置SPI速度为低速 //先产生>74个脉冲，让SD卡自己初始化完成
    for(i=0;i<10;i++){
        SPI1_ReadWriteByte(0xFF);
    }
	
	/*
	然后就是协议中说到当我们复位或者上电的时候，SD卡的SD控制寄存器处于卡识别模式中的空闲模式的，暂且这样称吧。
	本来我们是不需要发送复位命令了的，但是我们不知道我们的SD所支持的电压范围。
	所以，我们最好还是先给出一条复位指令，然后紧接着一条获取工作电压的指令，这样也是比较保险，
	如果多SD卡工作电压有疑问的，那么就得去看芯片手册了。有了这个知识，那下面的代码就不成问题了	
	*/
    retry = 0;
    do{
        //发送CMD0，让SD卡进入IDLE状态
        r1 = SD_SendCommand(CMD0, 0, 0x95);
        retry++;
    }while((r1 != 0x01) && (retry<200));
    //跳出循环后，检查原因：初始化成功？or 重试超时？

    if(retry==200){
        return 1;   //超时返回1
    }
			
    //-----------------SD卡复位到idle结束-----------------
    //获取卡片的SD版本信息
    r1 = SD_SendCommand_NoDeassert(8, 0x1aa, 0x87);

    //如果卡片版本信息是v1.0版本的，即r1=0x05，则进行以下初始化
    if(r1 == 0x05){  
        SD_Type = SD_TYPE_V1;//设置卡类型为SDV1.0，如果后面检测到为MMC卡，再修改为MMC
        //如果是V1.0卡，CMD8指令后没有后续数据       
        SD_CS_DISABLE();//片选置高，结束本次命令 
        SPI1_ReadWriteByte(0xFF);//多发8个CLK，让SD结束后续操作

        //-----------------SD卡、MMC卡初始化开始-----------------
        //发卡初始化指令CMD55+ACMD41
        // 如果有应答，说明是SD卡，且初始化完成
        // 没有回应，说明是MMC卡，额外进行相应初始化
        retry = 0;
        do{       
            r1 = SD_SendCommand(CMD55, 0, 0); //先发CMD55，应返回0x01；否则出错
            if(r1 != 0x01)
            {
                return r1;  
            }        
            r1 = SD_SendCommand(ACMD41, 0, 0);//得到正确响应后，发ACMD41，应得到返回值0x00，否则重试200次
            retry++;
        }while((r1!=0x00) && (retry<400));
        // 判断是超时还是得到正确回应
        // 若有回应：是SD卡；没有回应：是MMC卡
        
        //----------MMC卡额外初始化操作开始------------
        if(retry==400){
            retry = 0;
            //发送MMC卡初始化命令（没有测试）
            do{
                r1 = SD_SendCommand(1, 0, 0);
                retry++;
            }while((r1!=0x00)&& (retry<400));
            if(retry==400){
                return 1;   //MMC卡初始化超时
            }
            //写入卡类型
            SD_Type = SD_TYPE_MMC;
        }
        //----------MMC卡额外初始化操作结束------------
						              
        SPI1_SetSpeed(1);//设置SPI为高速模式
        SPI1_ReadWriteByte(0xFF);
           
        //设置Sector Size
        r1 = SD_SendCommand(CMD16, 512, 0xff);
        if(r1 != 0x00){
            return r1;  //命令错误，返回r1
        }
        //-----------------SD卡、MMC卡初始化结束-----------------

    }//SD卡为V1.0版本的初始化结束,初始化完SD卡，接下来如果你想查看我们SD的容量，
	
    
																
    //下面是V2.0卡的初始化
    //其中需要读取OCR数据，判断是SD2.0还是SD2.0HC卡
    else if(r1 == 0x01){
        //V2.0的卡，CMD8命令后会传回4字节的数据，要跳过再结束本命令
        buff[0] = SPI1_ReadWriteByte(0xFF);  //should be 0x00
        buff[1] = SPI1_ReadWriteByte(0xFF);  //should be 0x00
        buff[2] = SPI1_ReadWriteByte(0xFF);  //should be 0x01
        buff[3] = SPI1_ReadWriteByte(0xFF);  //should be 0xAA
     
        SD_CS_DISABLE();     
        SPI1_ReadWriteByte(0xFF);//the next 8 clocks
        
        
		/*
			            判断该卡是否支持2.7V-3.6V的电压范围
		协议上还提到ACMD41命令的目的是给予 SD卡控制器一个识别 SD卡是否可以在所给Vdd 范围下工作的机制，
		如果 SD 卡无法在指定 Vdd 范围内工作，则它会进入非活动状态（Inactive state ），所以我们接下来需要发送这个命令，
		但是在发送这个命令之前，要知道这是一个应用型的命令，所以要加上CMD55命令，
		*/
        if(buff[2]==0x01 && buff[3]==0xAA){
            //支持电压范围，可以操作
            retry = 0;         
            do{
                r1 = SD_SendCommand(CMD55, 0, 0);//发卡初始化指令CMD55+ACMD41
                if(r1!=0x01){
                    return r1;
                }
                r1 = SD_SendCommand(ACMD41, 0x40000000, 0);
                if(retry>200){
                    return r1;  //超时则返回r1状态
                }
            }while(r1!=0);
          
            //初始化指令发送完成，接下来获取OCR信息
            //-----------鉴别SD2.0卡版本开始-----------
            r1 = SD_SendCommand_NoDeassert(CMD58, 0, 0);
            if(r1!=0x00)
            {
                return r1;  //如果命令没有返回正确应答，直接退出，返回应答
            }
            //读OCR指令发出后，紧接着是4字节的OCR信息
            buff[0] = SPI1_ReadWriteByte(0xFF);
            buff[1] = SPI1_ReadWriteByte(0xFF); 
            buff[2] = SPI1_ReadWriteByte(0xFF);
            buff[3] = SPI1_ReadWriteByte(0xFF);

            //OCR接收完成，片选置高
            SD_CS_DISABLE();
            SPI1_ReadWriteByte(0xFF);

            //检查接收到的OCR中的bit30位（CCS），确定其为SD2.0还是SDHC
            //如果CCS=1：SDHC   CCS=0：SD2.0
            if(buff[0]&0x40)    //检查CCS
            {
                SD_Type = SD_TYPE_V2HC;
            }
            else
            {
                SD_Type = SD_TYPE_V2;
            }
            //-----------鉴别SD2.0卡版本结束-----------
                    
            SPI1_SetSpeed(1);  //设置SPI为高速模式
        }
    }
    return r1;
}



/*******************************************************************************
* Function Name  : SD_ReceiveData
* Description    : 从SD卡中读回指定长度的数据，放置在给定位置
* Input          : u8 *data(存放读回数据的内存>len)
*                  u16 len(数据长度）
*                  u8 release(传输完成后是否释放总线CS置高     0：不释放 1：释放）
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  other：错误信息
*******************************************************************************/
u8 SD_ReceiveData(u8 *data, u16 len, u8 release)
{
    u16 retry;
    u8 r1;

    // 启动一次传输
    SD_CS_ENABLE();
    //等待SD卡发回数据起始令牌0xFE
    retry = 0;
    do
    {
        r1 = SPI1_ReadWriteByte(0xFF);
        retry++;
        if(retry>2000)  //2000次等待后没有应答，退出报错
        {
            SD_CS_DISABLE();
            return 1;
        }
    }while(r1 != 0xFE);
    //开始接收数据
    while(len--)
    {
        *data = SPI1_ReadWriteByte(0xFF);
        data++;
    }
    //下面是2个伪CRC（dummy CRC）
    SPI1_ReadWriteByte(0xFF);
    SPI1_ReadWriteByte(0xFF);
    //按需释放总线，将CS置高
    if(release == RELEASE)
    {
        //传输结束
        SD_CS_DISABLE();
        SPI1_ReadWriteByte(0xFF);
    }

    return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCID
* Description    : 获取SD卡的CID信息，包括制造商信息
* Input          : u8 *cid_data(存放CID的内存，至少16Byte）
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  1：TIME_OUT
*                  other：错误信息
*******************************************************************************/
u8 SD_GetCID(u8 *cid_data)
{
    u8 r1;

    //发CMD10命令，读CID
    r1 = SD_SendCommand(CMD10, 0, 0xFF);
    if(r1 != 0x00)
    {
        return r1;  //没返回正确应答，则退出，报错
    }
    //接收16个字节的数据
    SD_ReceiveData(cid_data, 16, RELEASE);

    return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCSD
* Description    : 获取SD卡的CSD信息，包括容量和速度信息
* Input          : u8 *cid_data(存放CID的内存，至少16Byte）
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  1：TIME_OUT
*                  other：错误信息
*******************************************************************************/
u8 SD_GetCSD(u8 *csd_data)
{
    u8 r1;

    //发CMD9命令，读CSD
    r1 = SD_SendCommand(CMD9, 0, 0xFF);
    if(r1 != 0x00)
    {
        return r1;  //没返回正确应答，则退出，报错
    }
    //接收16个字节的数据
    SD_ReceiveData(csd_data, 16, RELEASE);

    return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCapacity
* Description    : 获取SD卡的容量
* Input          : None
* Output         : None
* Return         : u32 capacity 
*                   0： 取容量出错 
*******************************************************************************/
u32 SD_GetCapacity(void)
{
    u8 csd[16];
    u32 Capacity;
    u8 r1;
    u16 i;
    u16 temp;

    //取CSD信息，如果期间出错，返回0
    if(SD_GetCSD(csd)!=0)
    {
        return 0;
    }
       
    //如果为SDHC卡，按照下面方式计算
    if((csd[0]&0xC0)==0x40)
    {
        Capacity =  (((u32)csd[8])<<8 + (u32)csd[9] +1)*(u32)1024;
    }
    else
    {
        //下面代码为网上版本
        ////////////formula of the capacity///////////////
        //
        //  memory capacity = BLOCKNR * BLOCK_LEN
        //  
        //  BLOCKNR = (C_SIZE + 1)* MULT
        //
        //           C_SIZE_MULT+2
        //  MULT = 2
        //
        //               READ_BL_LEN
        //  BLOCK_LEN = 2
        /**********************************************/
        //C_SIZE
        i = csd[6]&0x03;
        i<<=8;
        i += csd[7];
        i<<=2;
        i += ((csd[8]&0xc0)>>6);
    
        //C_SIZE_MULT
        r1 = csd[9]&0x03;
        r1<<=1;
        r1 += ((csd[10]&0x80)>>7);
    
        //BLOCKNR
        r1+=2;
        temp = 1;
        while(r1)
        {
            temp*=2;
            r1--;
        }
        Capacity = ((u32)(i+1))*((u32)temp);
    
        // READ_BL_LEN
        i = csd[5]&0x0f;
        //BLOCK_LEN
        temp = 1;
        while(i)
        {
            temp*=2;
            i--;
        }
        //The final result
        Capacity *= (u32)temp; 
        //Capacity /= 512;
    }
    return (u32)Capacity;
}


/*******************************************************************************
* Function Name  : SD_ReadSingleBlock
* Description    : 读SD卡的一个block
* Input          : u32 sector 取地址（sector值，非物理地址） 
*                  u8 *buffer 数据存储地址（大小至少512byte） 
* Output         : None
* Return         : u8 r1 
*                  0：    成功
*                  other：失败
*******************************************************************************/
u8 SD_ReadSingleBlock(u32 sector, u8 *buffer)
{
    u8 r1;

    //设置为高速模式
    SPI1_SetSpeed(SPI_SPEED_HIGH);
    
    //如果不是SDHC，将sector地址转成byte地址
    sector = sector<<9;

    r1 = SD_SendCommand(CMD17, sector, 0);//读命令
    
    if(r1 != 0x00)
    {
        return r1;
    }
    
    r1 = SD_ReceiveData(buffer, 512, RELEASE);
    if(r1 != 0)
    {
        return r1;   //读数据出错！
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
* Function Name  : SD_WriteSingleBlock
* Description    : 写入SD卡的一个block
* Input          : u32 sector 扇区地址（sector值，非物理地址） 
*                  u8 *buffer 数据存储地址（大小至少512byte） 
* Output         : None
* Return         : u8 r1 
*                  0：    成功
*                  other：失败
*******************************************************************************/
u8 SD_WriteSingleBlock(u32 sector, const u8 *data)
{
    u8 r1;
    u16 i;
    u16 retry;

    //设置为高速模式
    SPI1_SetSpeed(SPI_SPEED_HIGH);

    //如果不是SDHC，给定的是sector地址，将其转换成byte地址
    if(SD_Type!=SD_TYPE_V2HC)
    {
        sector = sector<<9;
    }

    r1 = SD_SendCommand(CMD24, sector, 0x00);
    if(r1 != 0x00)
    {
        return r1;  //应答不正确，直接返回
    }
    
    //开始准备数据传输
    SD_CS_ENABLE();
    //先放3个空数据，等待SD卡准备好
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);
   
		//放起始令牌0xFE
    SPI1_ReadWriteByte(0xFE);

    //放一个sector的数据
    for(i=0;i<512;i++)
    {
        SPI1_ReadWriteByte(*data++);
    }
    //发2个Byte的dummy CRC
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);
    
    //等待SD卡应答
    r1 = SPI1_ReadWriteByte(0xff);
    if((r1&0x1F)!=0x05)
    {
        SD_CS_DISABLE();
        return r1;
    }
    
    //等待操作完成
    retry = 0;
    while(!SPI1_ReadWriteByte(0xff))
    {
        retry++;
        if(retry>0xfffe)        //如果长时间写入没有完成，报错退出
        {
            SD_CS_DISABLE();
            return 1;           //写入超时返回1
        }
    }

    //写入完成，片选置1
    SD_CS_DISABLE();
    SPI1_ReadWriteByte(0xff);

    return 0;
}


/*******************************************************************************
* Function Name  : SD_ReadMultiBlock
* Description    : 读SD卡的多个block
* Input          : u32 sector 取地址（sector值，非物理地址） 
*                  u8 *buffer 数据存储地址（大小至少512byte）
*                  u8 count 连续读count个block
* Output         : None
* Return         : u8 r1 
*                   0：    成功
*                   other：失败
*******************************************************************************/
u8 SD_ReadMultiBlock(u32 sector, u8 *buffer, u8 count)
{
    u8 r1;

    //设置为高速模式
    SPI1_SetSpeed(SPI_SPEED_HIGH);
    
    //如果不是SDHC，将sector地址转成byte地址
    sector = sector<<9;
	
    //SD_WaitReady();   发读多块命令 
    r1 = SD_SendCommand(CMD18, sector, 0);//读命令
    if(r1 != 0x00)
    {
        return r1;
    }
    //开始接收数据
    do
    {
        if(SD_ReceiveData(buffer, 512, NO_RELEASE) != 0x00)
        {
            break;
        }
        buffer += 512;
    } while(--count);

    //全部传输完毕，发送停止命令
    SD_SendCommand(CMD12, 0, 0);
    //释放总线
    SD_CS_DISABLE();
    SPI1_ReadWriteByte(0xFF);
    
    if(count != 0)
    {
        return count;   //如果没有传完，返回剩余个数
    }
    else
    {
        return 0;
    }
}


/*******************************************************************************
* Function Name  : SD_WriteMultiBlock
* Description    : 写入SD卡的N个block
* Input          : u32 sector 扇区地址（sector值，非物理地址） 
*                  u8 *buffer 数据存储地址（大小至少512byte）
*                  u8 count 写入的block数目
* Output         : None
* Return         : u8 r1 
*                  0：    成功
*                  other：失败
*******************************************************************************/
u8 SD_WriteMultiBlock(u32 sector, const u8 *data, u8 count)
{
    u8 r1;
    u16 i;

    //设置为高速模式
    SPI1_SetSpeed(SPI_SPEED_HIGH);

    //如果不是SDHC，给定的是sector地址，将其转换成byte地址
    if(SD_Type != SD_TYPE_V2HC)
    {
        sector = sector<<9;
    }
    //如果目标卡不是MMC卡，启用ACMD23指令使能预擦除
    if(SD_Type != SD_TYPE_MMC)
    {
        r1 = SD_SendCommand(ACMD23, count, 0x00);
    }
    //发多块写入指令
    r1 = SD_SendCommand(CMD25, sector, 0x00);
    if(r1 != 0x00)
    {
        return r1;  //应答不正确，直接返回
    }
    
    //开始准备数据传输
    SD_CS_ENABLE();
    //先放3个空数据，等待SD卡准备好
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);

    //--------下面是N个sector写入的循环部分
    do
    {
        //放起始令牌0xFC 表明是多块写入
        SPI1_ReadWriteByte(0xFC);
    
        //放一个sector的数据
        for(i=0;i<512;i++)
        {
            SPI1_ReadWriteByte(*data++);
        }
        //发2个Byte的dummy CRC
        SPI1_ReadWriteByte(0xff);
        SPI1_ReadWriteByte(0xff);
        
        //等待SD卡应答
        r1 = SPI1_ReadWriteByte(0xff);
        if((r1&0x1F)!=0x05)
        {
            SD_CS_DISABLE();    //如果应答为报错，则带错误代码直接退出
            return r1;
        }

        //等待SD卡写入完成
        if(SD_WaitReady()==1)
        {
            SD_CS_DISABLE();    //等待SD卡写入完成超时，直接退出报错
            return 1;
        }

        //本sector数据传输完成
    }while(--count);
    
    //发结束传输令牌0xFD
    r1 = SPI1_ReadWriteByte(0xFD);
    if(r1==0x00)
    {
        count =  0xfe;
    }

    if(SD_WaitReady())
    {
        while(1)
        {
        }
    }
    
    //写入完成，片选置1
    SD_CS_DISABLE();
    SPI1_ReadWriteByte(0xff);

    return count;   //返回count值，如果写完则count=0，否则count=1
}










//仿真计算出该函数执行时间为3.6us
void DelayUs(u32 Num){
    int i = 0;
    while(Num){
        for(i=1; i>0; i--){
            ;
        }
        Num --;
    }
}

/* Private functions ---------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////
// 以下是SPI模块的初始化代码，配置成主机模式，访问SD卡
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : SPI_Configuration
* Description    : SPI模块初始化，【包括相关IO口的初始化】
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Configuration(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	//启动SPI时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    //////下面是SPI相关GPIO初始化//////
    //SPI1模块对应的SCK、MISO、MOSI为AF引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PB12 pin: SD_CS 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  

    //////SPI模块配置//////
    //一开始SD初始化阶段，SPI时钟频率必须<400K
  SD_CS_DISABLE();

  /* SPI1 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* Enable SPI1  */
  SPI_Cmd(SPI2, ENABLE);
}

/**
  * @brief  Configures the SDIO Corresponding GPIO Ports
  * @param  None
  * @retval : None
  */
static void GPIO_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Configure PA4, PA5, PA6, PA7 pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//	SD_SPIDrive_Init(1);

}


/*
********************************************************************************
** 函数名称 ： void DelayMs(vu32 m)
** 函数功能 ： 长延时函数	 m=1,延时1ms
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void DelayMs(vu32 m){
  u32 i;
	 for(; m != 0; m--)	
       for (i=0; i<1000; i++);
}



//可以看出，擦除的话，需要发送3个命令，CMD32，CMD33，CMD38。
//输入参数1 擦除的起始扇区地址
//输入参数2 擦除的结束扇区地址

//返回值 擦除扇区是否成功
SD_Error SD_Erase(uint32_t sector_start, uint32_t sector_stop)
//uint8_t SD_erase_sector(uint32_t sector_start, uint32_t sector_stop)
{

		 // 启动一次传输
    SD_CS_ENABLE();
		SPI1_ReadWriteByte(0xff);

		//发送命令32，设置擦除扇区的起始地址      返回应该为00

		if(SD_SendCommand(32,sector_start,0xff))
		{
			SD_CS_DISABLE(); //无效片选
			return   0;//ERASE_SECTOR_ERROR;
		}
		//发送命令33，设置擦除扇区的终止地址			//返回应该为00

		if(SD_SendCommand(33,sector_stop,0xff))
		{
			  SD_CS_DISABLE(); 
				return 0;//ERASE_SECTOR_ERROR;

		}		
			//发送命令38，擦除所选扇区			//返回应该为00
		if(SD_SendCommand(38,0,0xff))
		{
				SD_CS_DISABLE();
				return  0;//ERASE_SECTOR_ERROR;
		}
			
		SD_CS_DISABLE();  //无效片选

		return  1;//ERASE_SECTOR_SUCCESS;	

}

void 	SD_SPIDrive_Init(uint8_t device)
{
	
}

