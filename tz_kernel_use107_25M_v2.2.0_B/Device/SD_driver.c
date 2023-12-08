/*****************************************************************

          SD�� ��������
          �� �� �ˣ�LJ128
          ����ʱ�䣺2008��8��3��
		  
�й�SD�����ߵ�̽����Ϊʲô��׼SD���ǾŸ��ߣ���һ��ԭ��ͼ�϶���11���߻�����أ���
����˵�������
SD����<=2GB
SDHC����SD High Capacity��������SD������4GB~32GB
SDXC����SD eXtended Capacity����64GB~2TB������2009��SDЭ�ᷢ�����±�׼
SDIO��SD Input Output ������������豸��SD��

SD��������SD����SDHC����SDXC���ȣ��������ǰ���������С��Э��������ֵģ�ÿ��һ���������������ķ�Խ��
������SDЭ����CES 2009����������һ���洢����׼SDXC��SD eXtended Capacity���������Ϊ2TB��
SD��SDHC������ַ�Ϊ��׼����mini����micro�������е���micro�����С����Ϊ��׼�����ķ�֮һ��Լָ�״�С�����������ɿ��ԡ��ٶȶ����׼����ͬ��

��׼SD����Secure Digital����ȫ���ֿ����Ĵ�С����24mm x 32mm x 2.1mm��Լ�൱����Ʊ��С��������Ϊ2�ˣ�Ȼ��ȴ���Դﵽ���2GB��������
SDHC����SD High Capacity��������SD����������Χ��չ����4GB��32GB��������Ա��ѡ��ָ���б�֤����������ʵ���������д���ٶȣ�
����SDHC�ٶȵȼ� (�ȼ� 2���ȼ� 4���ȼ� 6) ÿ��ֱ�ɴ������� 2MB��4MB��6MB�����ݡ�


SD���Ľӿڿ���֧��SD��ģʽ��SPIģʽ���ֲ���ģʽ������ϵͳ����ѡ��������һģʽ��SD��ģʽ����4�ߵĸ������ݴ��䣻
SPIģʽ�����ͨ�õ�SPIͨ���ӿڣ�����SPIģʽ�����SDģʽ��������ɥʧ�˸��ٶȡ�

*****************************************************************/

#include "SD_driver.h"

void DelayMs(vu32 m);
void DelayUs(vu32 m);
static void GPIO_Configuration(void);


u8  SD_Type = SD_TYPE_MMC; // SD��������
//u8  SD_Type = SD_TYPE_V1; // SD��������






void SPI1_SetSpeed(u8 SpeedSet)
{
    SPI_InitTypeDef 	SPI_InitStructure ;
    
    SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;
    SPI_InitStructure.SPI_Mode=SPI_Mode_Master ;
    SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b ;
    SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge ;
    SPI_InitStructure.SPI_NSS=SPI_NSS_Soft ;
    
	//����ٶ���������0�������ģʽ����0�����ģʽ
    if(SpeedSet==SPI_SPEED_LOW)
    {
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;//�����ܵ��õ��٣�
    }
    else 
    {
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;//72/4=18mhz
    }
    //moon.mp3: 4707774 Byte size Ŀ���ļ� ��Ϊbuffer[512]     
    //speed:ʵ��������ݣ�����ٶ� 392314 Byte/S��
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
    
	//����ٶ���������0�������ģʽ����0�����ģʽ
    if(SpeedSet==SPI_SPEED_LOW)
    {
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;//�����ܵ��õ��٣�
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

//TXE�����ͻ���Ϊ��
//0�����ͻ���ǿ�
//1�����ͻ���Ϊ��

	RXNE�����ջ���ǿ� 
	0�����ջ���Ϊ�� 
	1�����ջ���ǿ� 
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
��������������������������������
��Ȩ����������ΪCSDN������howareyou23����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/w942401053/article/details/125178639
				*/
}


//TXE�����ͻ���Ϊ��
//0�����ͻ���ǿ�
//1�����ͻ���Ϊ��
u8 SPI2_ReadWriteByte(u8 TxData)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);//��鷢���Ƿ���ɣ�����Ժ��ٷ�������added by sjw

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI2, TxData);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);//�����ܱ�־λ���Ƿ���Խ���added by sjw

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI2);
}

/*******************************************************************************
* Function Name  : SD_WaitReady
* Description    : �ȴ�SD��Ready
* Input          : None
* Output         : None
* Return         : u8 
*                   0�� �ɹ�
*                   other��ʧ��
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
* Description    : ��SD������һ������
* Input          : u8 cmd   ���� 
*                  u32 arg  �������
*                  u8 crc   crcУ��ֵ
* Output         : None
* Return         : u8 r1 SD�����ص���Ӧ
*******************************************************************************/
u8 SD_SendCommand(u8 cmd, u32 arg, u8 crc)
{
    unsigned char r1;
    unsigned char Retry = 0;

  
    SPI1_ReadWriteByte(0xff);
    SD_CS_ENABLE();  //Ƭѡ���õͣ�ѡ��SD��
   
	//����
    SPI1_ReadWriteByte(cmd | 0x40);                         //�ֱ�д������
    SPI1_ReadWriteByte(arg >> 24);
    SPI1_ReadWriteByte(arg >> 16);
    SPI1_ReadWriteByte(arg >> 8);
    SPI1_ReadWriteByte(arg);
    SPI1_ReadWriteByte(crc);
   
	//�ȴ���Ӧ����ʱ�˳�
    while((r1 = SPI1_ReadWriteByte(0xFF))==0xFF)
    {
        Retry++;
        if(Retry > 200)
        {
            break;
        }
    }
    //�ر�Ƭѡ
    SD_CS_DISABLE();
    //�������϶�������8��ʱ�ӣ���SD�����ʣ�µĹ���
    SPI1_ReadWriteByte(0xFF);
    //����״ֵ̬
    return r1;
}


/*******************************************************************************
* Function Name  : SD_SendCommand_NoDeassert
* Description    : ��SD������һ������(�����ǲ�ʧ��Ƭѡ�����к������ݴ�����
* Input          : u8 cmd   ���� 
*                  u32 arg  �������
*                  u8 crc   crcУ��ֵ
* Output         : None
* Return         : u8 r1 SD�����ص���Ӧ
*******************************************************************************/
u8 SD_SendCommand_NoDeassert(u8 cmd, u32 arg, u8 crc)
{
    unsigned char r1;
    unsigned char Retry = 0;

    //????????
    SPI1_ReadWriteByte(0xff);
    //Ƭѡ���õͣ�ѡ��SD��
    SD_CS_ENABLE();

    //����
    SPI1_ReadWriteByte(cmd | 0x40);                         //�ֱ�д������
    SPI1_ReadWriteByte(arg >> 24);
    SPI1_ReadWriteByte(arg >> 16);
    SPI1_ReadWriteByte(arg >> 8);
    SPI1_ReadWriteByte(arg);
    SPI1_ReadWriteByte(crc);

    //�ȴ���Ӧ����ʱ�˳�
    while((r1 = SPI1_ReadWriteByte(0xFF))==0xFF)
    {
        Retry++;
        if(Retry > 200)
        {
            break;
        }
    }
    //������Ӧֵ
    return r1;
}

/*******************************************************************************
* Function Name  : SD_Init
* Description    : ��ʼ��SD��
* Input          : None
* Output         : None
* Return         : u8 
*                  0��NO_ERR
*                  1��TIME_OUT
*                  2��û�в���SD��

SD��ֻ��ʹ��3.3V��IO��ƽ�����ԣ�MCUһ��Ҫ�ܹ�֧��3.3V��IO�˿������ע�⣺��SPIģʽ�£�
CS/MOSI/MISO/CLK����Ҫ��10~100K���ҵ��������衣 
SD��Ҫ����SPIģʽ�ܼ򵥣�������SD���յ���λ���CMD0��ʱ��CSΪ��Ч��ƽ���͵�ƽ����SPIģʽ�����á������ڷ���CMD0֮ǰ��Ҫ����>74��ʱ�ӣ�
������ΪSD���ڲ��и������ѹ����ʱ�䣬���Ϊ64��CLK��ʣ�µ�10��CLK����SD��ͬ����֮����ܿ�ʼCMD0�Ĳ�����
�ڿ���ʼ����ʱ��                      CLKʱ������ܳ���400Khz����  
ALENTEK MiniSTM32������ʹ�õ���SPIģʽ����дSD�����������Ǿ��ص����һ��SD����SPIģʽ�µ���ز�����
*******************************************************************************/

//// ��������MMC_SD_Init 
// ��  �ܣ�sd����ʼ�� 
// ��  ������ 
// ����ֵ��uint8 type         
// �����ͷ���ֵ: 0x10 SD, 0x20 MMC 

u8 SD_Init(void)
{
    u16 i;      // ����ѭ������
    u8 r1;      // ���SD���ķ���ֵ
    u16 retry;  // �������г�ʱ����
   volatile u8 buff[6];

	
	
	  /* Configure SDIO interface GPIO */
   // GPIO_Configuration();
	
	  /* Enable the SDIO AHB Clock */
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, ENABLE);
  /* Enable the DMA2 Clock */
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
    //SDIO_DeInit();

	
	//Ҫʹ��SD������ô���ȿ϶��ö�SD�����г�ʼ������ô��ν��г�ʼ���أ�
	//Э��涨���ڸ�SD���ϵ�֮����Ҫ��������74��ʱ������󣬲��ܽ�����ص�SD��ʼ������
    SD_PWR_ON();       //SD���ϵ�
    SPI1_SetSpeed(0);  //����SPI�ٶ�Ϊ���� //�Ȳ���>74�����壬��SD���Լ���ʼ�����
    for(i=0;i<10;i++){
        SPI1_ReadWriteByte(0xFF);
    }
	
	/*
	Ȼ�����Э����˵�������Ǹ�λ�����ϵ��ʱ��SD����SD���ƼĴ������ڿ�ʶ��ģʽ�еĿ���ģʽ�ģ����������ưɡ�
	���������ǲ���Ҫ���͸�λ�����˵ģ��������ǲ�֪�����ǵ�SD��֧�ֵĵ�ѹ��Χ��
	���ԣ�������û����ȸ���һ����λָ�Ȼ�������һ����ȡ������ѹ��ָ�����Ҳ�ǱȽϱ��գ�
	�����SD��������ѹ�����ʵģ���ô�͵�ȥ��оƬ�ֲ��ˡ��������֪ʶ��������Ĵ���Ͳ���������	
	*/
    retry = 0;
    do{
        //����CMD0����SD������IDLE״̬
        r1 = SD_SendCommand(CMD0, 0, 0x95);
        retry++;
    }while((r1 != 0x01) && (retry<200));
    //����ѭ���󣬼��ԭ�򣺳�ʼ���ɹ���or ���Գ�ʱ��

    if(retry==200){
        return 1;   //��ʱ����1
    }
			
    //-----------------SD����λ��idle����-----------------
    //��ȡ��Ƭ��SD�汾��Ϣ
    r1 = SD_SendCommand_NoDeassert(8, 0x1aa, 0x87);

    //�����Ƭ�汾��Ϣ��v1.0�汾�ģ���r1=0x05����������³�ʼ��
    if(r1 == 0x05){  
        SD_Type = SD_TYPE_V1;//���ÿ�����ΪSDV1.0����������⵽ΪMMC�������޸�ΪMMC
        //�����V1.0����CMD8ָ���û�к�������       
        SD_CS_DISABLE();//Ƭѡ�øߣ������������� 
        SPI1_ReadWriteByte(0xFF);//�෢8��CLK����SD������������

        //-----------------SD����MMC����ʼ����ʼ-----------------
        //������ʼ��ָ��CMD55+ACMD41
        // �����Ӧ��˵����SD�����ҳ�ʼ�����
        // û�л�Ӧ��˵����MMC�������������Ӧ��ʼ��
        retry = 0;
        do{       
            r1 = SD_SendCommand(CMD55, 0, 0); //�ȷ�CMD55��Ӧ����0x01���������
            if(r1 != 0x01)
            {
                return r1;  
            }        
            r1 = SD_SendCommand(ACMD41, 0, 0);//�õ���ȷ��Ӧ�󣬷�ACMD41��Ӧ�õ�����ֵ0x00����������200��
            retry++;
        }while((r1!=0x00) && (retry<400));
        // �ж��ǳ�ʱ���ǵõ���ȷ��Ӧ
        // ���л�Ӧ����SD����û�л�Ӧ����MMC��
        
        //----------MMC�������ʼ��������ʼ------------
        if(retry==400){
            retry = 0;
            //����MMC����ʼ�����û�в��ԣ�
            do{
                r1 = SD_SendCommand(1, 0, 0);
                retry++;
            }while((r1!=0x00)&& (retry<400));
            if(retry==400){
                return 1;   //MMC����ʼ����ʱ
            }
            //д�뿨����
            SD_Type = SD_TYPE_MMC;
        }
        //----------MMC�������ʼ����������------------
						              
        SPI1_SetSpeed(1);//����SPIΪ����ģʽ
        SPI1_ReadWriteByte(0xFF);
           
        //����Sector Size
        r1 = SD_SendCommand(CMD16, 512, 0xff);
        if(r1 != 0x00){
            return r1;  //������󣬷���r1
        }
        //-----------------SD����MMC����ʼ������-----------------

    }//SD��ΪV1.0�汾�ĳ�ʼ������,��ʼ����SD�����������������鿴����SD��������
	
    
																
    //������V2.0���ĳ�ʼ��
    //������Ҫ��ȡOCR���ݣ��ж���SD2.0����SD2.0HC��
    else if(r1 == 0x01){
        //V2.0�Ŀ���CMD8�����ᴫ��4�ֽڵ����ݣ�Ҫ�����ٽ���������
        buff[0] = SPI1_ReadWriteByte(0xFF);  //should be 0x00
        buff[1] = SPI1_ReadWriteByte(0xFF);  //should be 0x00
        buff[2] = SPI1_ReadWriteByte(0xFF);  //should be 0x01
        buff[3] = SPI1_ReadWriteByte(0xFF);  //should be 0xAA
     
        SD_CS_DISABLE();     
        SPI1_ReadWriteByte(0xFF);//the next 8 clocks
        
        
		/*
			            �жϸÿ��Ƿ�֧��2.7V-3.6V�ĵ�ѹ��Χ
		Э���ϻ��ᵽACMD41�����Ŀ���Ǹ��� SD��������һ��ʶ�� SD���Ƿ����������Vdd ��Χ�¹����Ļ��ƣ�
		��� SD ���޷���ָ�� Vdd ��Χ�ڹ��������������ǻ״̬��Inactive state �����������ǽ�������Ҫ����������
		�����ڷ����������֮ǰ��Ҫ֪������һ��Ӧ���͵��������Ҫ����CMD55���
		*/
        if(buff[2]==0x01 && buff[3]==0xAA){
            //֧�ֵ�ѹ��Χ�����Բ���
            retry = 0;         
            do{
                r1 = SD_SendCommand(CMD55, 0, 0);//������ʼ��ָ��CMD55+ACMD41
                if(r1!=0x01){
                    return r1;
                }
                r1 = SD_SendCommand(ACMD41, 0x40000000, 0);
                if(retry>200){
                    return r1;  //��ʱ�򷵻�r1״̬
                }
            }while(r1!=0);
          
            //��ʼ��ָ�����ɣ���������ȡOCR��Ϣ
            //-----------����SD2.0���汾��ʼ-----------
            r1 = SD_SendCommand_NoDeassert(CMD58, 0, 0);
            if(r1!=0x00)
            {
                return r1;  //�������û�з�����ȷӦ��ֱ���˳�������Ӧ��
            }
            //��OCRָ����󣬽�������4�ֽڵ�OCR��Ϣ
            buff[0] = SPI1_ReadWriteByte(0xFF);
            buff[1] = SPI1_ReadWriteByte(0xFF); 
            buff[2] = SPI1_ReadWriteByte(0xFF);
            buff[3] = SPI1_ReadWriteByte(0xFF);

            //OCR������ɣ�Ƭѡ�ø�
            SD_CS_DISABLE();
            SPI1_ReadWriteByte(0xFF);

            //�����յ���OCR�е�bit30λ��CCS����ȷ����ΪSD2.0����SDHC
            //���CCS=1��SDHC   CCS=0��SD2.0
            if(buff[0]&0x40)    //���CCS
            {
                SD_Type = SD_TYPE_V2HC;
            }
            else
            {
                SD_Type = SD_TYPE_V2;
            }
            //-----------����SD2.0���汾����-----------
                    
            SPI1_SetSpeed(1);  //����SPIΪ����ģʽ
        }
    }
    return r1;
}



/*******************************************************************************
* Function Name  : SD_ReceiveData
* Description    : ��SD���ж���ָ�����ȵ����ݣ������ڸ���λ��
* Input          : u8 *data(��Ŷ������ݵ��ڴ�>len)
*                  u16 len(���ݳ��ȣ�
*                  u8 release(������ɺ��Ƿ��ͷ�����CS�ø�     0�����ͷ� 1���ͷţ�
* Output         : None
* Return         : u8 
*                  0��NO_ERR
*                  other��������Ϣ
*******************************************************************************/
u8 SD_ReceiveData(u8 *data, u16 len, u8 release)
{
    u16 retry;
    u8 r1;

    // ����һ�δ���
    SD_CS_ENABLE();
    //�ȴ�SD������������ʼ����0xFE
    retry = 0;
    do
    {
        r1 = SPI1_ReadWriteByte(0xFF);
        retry++;
        if(retry>2000)  //2000�εȴ���û��Ӧ���˳�����
        {
            SD_CS_DISABLE();
            return 1;
        }
    }while(r1 != 0xFE);
    //��ʼ��������
    while(len--)
    {
        *data = SPI1_ReadWriteByte(0xFF);
        data++;
    }
    //������2��αCRC��dummy CRC��
    SPI1_ReadWriteByte(0xFF);
    SPI1_ReadWriteByte(0xFF);
    //�����ͷ����ߣ���CS�ø�
    if(release == RELEASE)
    {
        //�������
        SD_CS_DISABLE();
        SPI1_ReadWriteByte(0xFF);
    }

    return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCID
* Description    : ��ȡSD����CID��Ϣ��������������Ϣ
* Input          : u8 *cid_data(���CID���ڴ棬����16Byte��
* Output         : None
* Return         : u8 
*                  0��NO_ERR
*                  1��TIME_OUT
*                  other��������Ϣ
*******************************************************************************/
u8 SD_GetCID(u8 *cid_data)
{
    u8 r1;

    //��CMD10�����CID
    r1 = SD_SendCommand(CMD10, 0, 0xFF);
    if(r1 != 0x00)
    {
        return r1;  //û������ȷӦ�����˳�������
    }
    //����16���ֽڵ�����
    SD_ReceiveData(cid_data, 16, RELEASE);

    return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCSD
* Description    : ��ȡSD����CSD��Ϣ�������������ٶ���Ϣ
* Input          : u8 *cid_data(���CID���ڴ棬����16Byte��
* Output         : None
* Return         : u8 
*                  0��NO_ERR
*                  1��TIME_OUT
*                  other��������Ϣ
*******************************************************************************/
u8 SD_GetCSD(u8 *csd_data)
{
    u8 r1;

    //��CMD9�����CSD
    r1 = SD_SendCommand(CMD9, 0, 0xFF);
    if(r1 != 0x00)
    {
        return r1;  //û������ȷӦ�����˳�������
    }
    //����16���ֽڵ�����
    SD_ReceiveData(csd_data, 16, RELEASE);

    return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCapacity
* Description    : ��ȡSD��������
* Input          : None
* Output         : None
* Return         : u32 capacity 
*                   0�� ȡ�������� 
*******************************************************************************/
u32 SD_GetCapacity(void)
{
    u8 csd[16];
    u32 Capacity;
    u8 r1;
    u16 i;
    u16 temp;

    //ȡCSD��Ϣ������ڼ��������0
    if(SD_GetCSD(csd)!=0)
    {
        return 0;
    }
       
    //���ΪSDHC�����������淽ʽ����
    if((csd[0]&0xC0)==0x40)
    {
        Capacity =  (((u32)csd[8])<<8 + (u32)csd[9] +1)*(u32)1024;
    }
    else
    {
        //�������Ϊ���ϰ汾
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
* Description    : ��SD����һ��block
* Input          : u32 sector ȡ��ַ��sectorֵ���������ַ�� 
*                  u8 *buffer ���ݴ洢��ַ����С����512byte�� 
* Output         : None
* Return         : u8 r1 
*                  0��    �ɹ�
*                  other��ʧ��
*******************************************************************************/
u8 SD_ReadSingleBlock(u32 sector, u8 *buffer)
{
    u8 r1;

    //����Ϊ����ģʽ
    SPI1_SetSpeed(SPI_SPEED_HIGH);
    
    //�������SDHC����sector��ַת��byte��ַ
    sector = sector<<9;

    r1 = SD_SendCommand(CMD17, sector, 0);//������
    
    if(r1 != 0x00)
    {
        return r1;
    }
    
    r1 = SD_ReceiveData(buffer, 512, RELEASE);
    if(r1 != 0)
    {
        return r1;   //�����ݳ���
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
* Function Name  : SD_WriteSingleBlock
* Description    : д��SD����һ��block
* Input          : u32 sector ������ַ��sectorֵ���������ַ�� 
*                  u8 *buffer ���ݴ洢��ַ����С����512byte�� 
* Output         : None
* Return         : u8 r1 
*                  0��    �ɹ�
*                  other��ʧ��
*******************************************************************************/
u8 SD_WriteSingleBlock(u32 sector, const u8 *data)
{
    u8 r1;
    u16 i;
    u16 retry;

    //����Ϊ����ģʽ
    SPI1_SetSpeed(SPI_SPEED_HIGH);

    //�������SDHC����������sector��ַ������ת����byte��ַ
    if(SD_Type!=SD_TYPE_V2HC)
    {
        sector = sector<<9;
    }

    r1 = SD_SendCommand(CMD24, sector, 0x00);
    if(r1 != 0x00)
    {
        return r1;  //Ӧ����ȷ��ֱ�ӷ���
    }
    
    //��ʼ׼�����ݴ���
    SD_CS_ENABLE();
    //�ȷ�3�������ݣ��ȴ�SD��׼����
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);
   
		//����ʼ����0xFE
    SPI1_ReadWriteByte(0xFE);

    //��һ��sector������
    for(i=0;i<512;i++)
    {
        SPI1_ReadWriteByte(*data++);
    }
    //��2��Byte��dummy CRC
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);
    
    //�ȴ�SD��Ӧ��
    r1 = SPI1_ReadWriteByte(0xff);
    if((r1&0x1F)!=0x05)
    {
        SD_CS_DISABLE();
        return r1;
    }
    
    //�ȴ��������
    retry = 0;
    while(!SPI1_ReadWriteByte(0xff))
    {
        retry++;
        if(retry>0xfffe)        //�����ʱ��д��û����ɣ������˳�
        {
            SD_CS_DISABLE();
            return 1;           //д�볬ʱ����1
        }
    }

    //д����ɣ�Ƭѡ��1
    SD_CS_DISABLE();
    SPI1_ReadWriteByte(0xff);

    return 0;
}


/*******************************************************************************
* Function Name  : SD_ReadMultiBlock
* Description    : ��SD���Ķ��block
* Input          : u32 sector ȡ��ַ��sectorֵ���������ַ�� 
*                  u8 *buffer ���ݴ洢��ַ����С����512byte��
*                  u8 count ������count��block
* Output         : None
* Return         : u8 r1 
*                   0��    �ɹ�
*                   other��ʧ��
*******************************************************************************/
u8 SD_ReadMultiBlock(u32 sector, u8 *buffer, u8 count)
{
    u8 r1;

    //����Ϊ����ģʽ
    SPI1_SetSpeed(SPI_SPEED_HIGH);
    
    //�������SDHC����sector��ַת��byte��ַ
    sector = sector<<9;
	
    //SD_WaitReady();   ����������� 
    r1 = SD_SendCommand(CMD18, sector, 0);//������
    if(r1 != 0x00)
    {
        return r1;
    }
    //��ʼ��������
    do
    {
        if(SD_ReceiveData(buffer, 512, NO_RELEASE) != 0x00)
        {
            break;
        }
        buffer += 512;
    } while(--count);

    //ȫ��������ϣ�����ֹͣ����
    SD_SendCommand(CMD12, 0, 0);
    //�ͷ�����
    SD_CS_DISABLE();
    SPI1_ReadWriteByte(0xFF);
    
    if(count != 0)
    {
        return count;   //���û�д��꣬����ʣ�����
    }
    else
    {
        return 0;
    }
}


/*******************************************************************************
* Function Name  : SD_WriteMultiBlock
* Description    : д��SD����N��block
* Input          : u32 sector ������ַ��sectorֵ���������ַ�� 
*                  u8 *buffer ���ݴ洢��ַ����С����512byte��
*                  u8 count д���block��Ŀ
* Output         : None
* Return         : u8 r1 
*                  0��    �ɹ�
*                  other��ʧ��
*******************************************************************************/
u8 SD_WriteMultiBlock(u32 sector, const u8 *data, u8 count)
{
    u8 r1;
    u16 i;

    //����Ϊ����ģʽ
    SPI1_SetSpeed(SPI_SPEED_HIGH);

    //�������SDHC����������sector��ַ������ת����byte��ַ
    if(SD_Type != SD_TYPE_V2HC)
    {
        sector = sector<<9;
    }
    //���Ŀ�꿨����MMC��������ACMD23ָ��ʹ��Ԥ����
    if(SD_Type != SD_TYPE_MMC)
    {
        r1 = SD_SendCommand(ACMD23, count, 0x00);
    }
    //�����д��ָ��
    r1 = SD_SendCommand(CMD25, sector, 0x00);
    if(r1 != 0x00)
    {
        return r1;  //Ӧ����ȷ��ֱ�ӷ���
    }
    
    //��ʼ׼�����ݴ���
    SD_CS_ENABLE();
    //�ȷ�3�������ݣ��ȴ�SD��׼����
    SPI1_ReadWriteByte(0xff);
    SPI1_ReadWriteByte(0xff);

    //--------������N��sectorд���ѭ������
    do
    {
        //����ʼ����0xFC �����Ƕ��д��
        SPI1_ReadWriteByte(0xFC);
    
        //��һ��sector������
        for(i=0;i<512;i++)
        {
            SPI1_ReadWriteByte(*data++);
        }
        //��2��Byte��dummy CRC
        SPI1_ReadWriteByte(0xff);
        SPI1_ReadWriteByte(0xff);
        
        //�ȴ�SD��Ӧ��
        r1 = SPI1_ReadWriteByte(0xff);
        if((r1&0x1F)!=0x05)
        {
            SD_CS_DISABLE();    //���Ӧ��Ϊ��������������ֱ���˳�
            return r1;
        }

        //�ȴ�SD��д�����
        if(SD_WaitReady()==1)
        {
            SD_CS_DISABLE();    //�ȴ�SD��д����ɳ�ʱ��ֱ���˳�����
            return 1;
        }

        //��sector���ݴ������
    }while(--count);
    
    //��������������0xFD
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
    
    //д����ɣ�Ƭѡ��1
    SD_CS_DISABLE();
    SPI1_ReadWriteByte(0xff);

    return count;   //����countֵ�����д����count=0������count=1
}










//���������ú���ִ��ʱ��Ϊ3.6us
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
// ������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ������SD��
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : SPI_Configuration
* Description    : SPIģ���ʼ�������������IO�ڵĳ�ʼ����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Configuration(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	//����SPIʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    //////������SPI���GPIO��ʼ��//////
    //SPI1ģ���Ӧ��SCK��MISO��MOSIΪAF����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PB12 pin: SD_CS 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  

    //////SPIģ������//////
    //һ��ʼSD��ʼ���׶Σ�SPIʱ��Ƶ�ʱ���<400K
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
** �������� �� void DelayMs(vu32 m)
** �������� �� ����ʱ����	 m=1,��ʱ1ms
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void DelayMs(vu32 m){
  u32 i;
	 for(; m != 0; m--)	
       for (i=0; i<1000; i++);
}



//���Կ����������Ļ�����Ҫ����3�����CMD32��CMD33��CMD38��
//�������1 ��������ʼ������ַ
//�������2 �����Ľ���������ַ

//����ֵ ���������Ƿ�ɹ�
SD_Error SD_Erase(uint32_t sector_start, uint32_t sector_stop)
//uint8_t SD_erase_sector(uint32_t sector_start, uint32_t sector_stop)
{

		 // ����һ�δ���
    SD_CS_ENABLE();
		SPI1_ReadWriteByte(0xff);

		//��������32�����ò�����������ʼ��ַ      ����Ӧ��Ϊ00

		if(SD_SendCommand(32,sector_start,0xff))
		{
			SD_CS_DISABLE(); //��ЧƬѡ
			return   0;//ERASE_SECTOR_ERROR;
		}
		//��������33�����ò�����������ֹ��ַ			//����Ӧ��Ϊ00

		if(SD_SendCommand(33,sector_stop,0xff))
		{
			  SD_CS_DISABLE(); 
				return 0;//ERASE_SECTOR_ERROR;

		}		
			//��������38��������ѡ����			//����Ӧ��Ϊ00
		if(SD_SendCommand(38,0,0xff))
		{
				SD_CS_DISABLE();
				return  0;//ERASE_SECTOR_ERROR;
		}
			
		SD_CS_DISABLE();  //��ЧƬѡ

		return  1;//ERASE_SECTOR_SUCCESS;	

}

void 	SD_SPIDrive_Init(uint8_t device)
{
	
}

