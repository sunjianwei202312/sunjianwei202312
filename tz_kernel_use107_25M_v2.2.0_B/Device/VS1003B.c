#include 	"VS1003B.h"
#include 	"SPECREW.h"
#include  "mp3play.h"
#define 	SPI_SPEED_LOW 	 0


//STM32��Ӳ��SPI�ġ���ò�Ҫģ��
//https://ishare.iask.sina.com.cn/f/brK42nCEImF.html                 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

static uint8_t VS1003_SPI_ReadWriteByte( uint8_t TxData );

 u8 readBuf[READBUF_SIZE];

u16 VS1003_GetDecodeTime(void);
//�õ�mp3�Ĳ���ʱ�� n sec

/*
������оƬһ������ʼ������vs10xxͬ���ǳ���Ҫ���������£�
1.Ӳ����λ����xRESET����
2.��ʱ����xDCS��xCS��xRESET����
3����mode��д��0x0804
4.�ȴ�DREQ���
5.����vs��ʱ�ӣ�SCI_CLOCKF=0x9800,3��Ƶ
6.����vs�Ĳ�����:SCI_AUDATA=0xbb81,������48K��������
7.����������SCI_BASS=0x0055
8.����������SCI_VOL=0x3030  ���
9.��vs����4���ֽڵ���Ч���ݣ���������SPI�ķ���
�ڳ�ʼ���󣬻�Ҫ���ؼ��һ��vs��ģ�ⲿ���Ƿ���������vs������DVDD,AVDD
�ܽ��Լ�xRESET��TEST����32p����3.3����Ȼ�����vs��44������RCAP��Ӧ����1.3V
���ң�����оƬ��ģ�ⲿ��δ������������

֮��Ϳ�����vs�������Ҳ�����



VS1053��Ӧ����ʵ�ǳ��򵥣������Ĳ������£�

    1. ��д��SPI�����������룻

    2. ��д��VS1053��ʼ�����룻

    3. ��д���Ҳ����Դ��룻

    4. �ڴ���Դ��롣

������ϼ��������Ϳ��Խ���MP3�����ˡ�
void VS1053SineTest(uint8 freq){
    uint8 i;
    uint8 test[] = {0x53, 0xEF, 0x6E, 0x24, 0x00, 0x00, 0x00, 0x00}; // ��vs�������Ҳ�������
    uint8 back[] = {0x45, 0x78, 0x69, 0x74, 0x00, 0x00, 0x00, 0x00}; // ��vs�����˳���������


 VS_XRESET_CLR();         // xreset = 0
 VS1053_Delay(100);
 SSP1Send(0xFF);         // ����һ���ֽڵ���Ч���ݣ�����SPI����

 VS_CS_SET();            // cs = 1
 VS_XDCS_SET();          // xdcs = 1
 VS_XRESET_SET();        // xreset = 1
 VS1053_Delay(100);

 VS1053WriteReg(VS_SCI_MODE, 0x0820); // enter vs1003 test model
 while (VS_DREQ_PIN() == 0);          // wait for DREQ Highlevel

 GPIOSetValue(1, 2, 0);     // xdcs = 0
 test[3] = freq;       // д��Ƶ��
 for (i=0; i<8; i++){
     VS1053WriteData(test[i]);   // ����ִ�е������Ӧ���ܴӶ�������һ����һƵ�ʵ�����
 }

 VS_XDCS_SET();             // xdcs = 1
 VS1053_Delay(100000);

 GPIOSetValue(1, 2, 0);     // xdcs = 0
 for (i=0; i<8; i++)
 {
     VS1053WriteData(back[i]);   // �˳����Ҳ���
 }

 VS_XDCS_SET();             // xdcs = 1
 VS1053_Delay(200);
}
*/



/*************************************************

     VS1003B��ʱ 72M��13us

*************************************************/
void VS1003B_Delay(INT16U time)
{
    INT16U i;

    for(; time > 0; time--){
        for(i = 0; i < 100; i++);
    }
}  		  

/********************************

  VS1003д����    д����Ĺ������£�

 1.�ȴ�DREQΪ�ߣ���DREQΪ��ʱ��˵��оƬ��û�о�����

 2.��XCS������Ƭѡ������

 3.д��0x02

 4.д��Ĵ�����ַ

 5.�ֱ�д�����ݵĸ��ֽ�����ֽ�

 6.��XCS�ø�
 
**********************************/
void VS1003B_CMD_Write(INT8U address, INT16U data,INT8U device)//OK!
{  
	if(device==1){
    while(VS1003B_WAIT_DREQ( )==0);            //�ȴ���������--�ȴ�����
    SPI1_SetSpeed(0);//����   
    MP3_xDCS(1);		 			//xDCS=1;
	  MP3_xCS(0); 				  //xCS=0
	  SPI1_ReadWriteByte(VS_WRITE_COMMAND);	//����VS1003��д����
    SPI1_ReadWriteByte(address); 			//��ַ
    SPI1_ReadWriteByte(data>>8); 			//���͸߰�λ
    SPI1_ReadWriteByte(data);    			//�ڰ�λ	
    MP3_xCS(1);  					//xCS=1
    SPI1_SetSpeed(1);//����
	}else if(device==2){
		while(VS1003B_WAIT_DREQ( )==0);            //�ȴ���������--�ȴ�����
    SPI2_SetSpeed(0);//����   
    MP3_xDCS(1);		 			//xDCS=1;
	  MP3_xCS(0); 				  //xCS=0
	  SPI2_ReadWriteByte(VS_WRITE_COMMAND);	//����VS1003��д����
    SPI2_ReadWriteByte(address); 			//��ַ
    SPI2_ReadWriteByte(data>>8); 			//���͸߰�λ
    SPI2_ReadWriteByte(data);    			//�ڰ�λ	
    MP3_xCS(1);  					//xCS=1
    SPI2_SetSpeed(1);//����
	}
} 


/*******************************************************************************
* Function Name  : VS1003_WriteData
* Description    : VS1003д����
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

  VS1003д����  br���ֵΪ32

* Function Name  : VS1003_WriteData
* Description    : VS1003д����
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/  
void VS1003B_DATA_Write(unsigned char *buf, INT8U bw)
{
    INT8U i;
 
	   MP3_xDCS(0);			//xDCS=0
	  
	   //while(VS1003B_WAIT_DREQ( )==0);	//����Ҫ��������Ϊ����һ��д��32���ֽڣ�
     for(i = 0; i < bw; i++){
        SPI2_ReadWriteByte(*buf++);
     }   	
     MP3_xDCS(1);					//xDCS=1;
		 MP3_xCS(1); 			    //xCS=1
}



/********************************

  VS1003���Ĵ��� 
//��VS1003�ļĴ���           
//��VS1003
//ע�ⲻҪ�ñ��ٶ�ȡ,�����


* Function Name  : VS1003_ReadReg
* Description    : VS1003���Ĵ���
* Input          : - reg: �����ַ
* Output         : None
* Return         : - value: ����
* Attention		 : None
*******************************************************************************/
INT16U VS1003B_REG_Read(INT8U address)
{ 
    INT16U temp = 0; 

    while(VS1003B_WAIT_DREQ( ) == 0);		//�ȴ� ����
    SPI2_SetSpeed(0);        //���� 
	 MP3_xCS(0);   				     //xCS=0;ѡ�������
	  MP3_xDCS(1);	  			   //xDCS=1;
	 
    SPI2_ReadWriteByte(VS_READ_COMMAND);//����VS1003�Ķ�����
    SPI2_ReadWriteByte(address);        //��ַ
    temp = SPI2_ReadWriteByte(0xff);    //��ȡ���ֽ�
    temp = temp << 8;
    temp |= SPI2_ReadWriteByte(0xff);   //��ȡ���ֽ�
    MP3_xCS(1); 	
    SPI2_SetSpeed(1);       //����
    return temp; 
}  





/****************************************

     VS1003B ��λ����ʱ��

******************************************/ 
void VS1003B_ResetDecodeTime(void)
{
    VS1003B_CMD_Write(SPI_DECODE_TIME,0x0000,2);
    VS1003B_CMD_Write(SPI_DECODE_TIME,0x0000,2);//��������
}




/*******************************************************************************
* Function Name  : SD_SPIDrive_Init
* Description    : VS1003 SPI Init
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
���CPHA(ʱ����λ)λ����λ��SCK ʱ�ӵĵڶ�������(CPOL λΪ0 ʱ������
	���أ�CPOL λΪ1 ʱ����������)��������λ�Ĳ����������ڵ�һ��ʱ�ӱ��ر����档
	
	���CPHA λ����λ��SCK ʱ�ӵĵ�һ����(CPOL λΪ0 ʱ�����½�
	�أ�CPOL λΪ1 ʱ����������)��������λ�����������ڵڶ���ʱ�ӱ��ر����档

��Ƭ��SPI1��   SD���ӣ�vs1003�ӣ�����VS1003�����ٶ�����û��������ʧ�ܣ�ע���ϵ�VS1003���SPI�ٶ�2M 
VS1003 12M�����ϵ�� SIP����ٶ���CLKI/6����ΪCLKI��12M����û�����ñ�Ƶ������SPI����ٶ���2M��
�����Ƭ��SPI�����ٶȳ���2M���ܿ��ܳ�ʼ��VS1003ʧ�ܣ�����û���������ţ����߲����������⡣ 



��Ƭ��SPI һ���ӿ�ͬʱ������SPI�ӻ�ʱ��ע��ӻ�SPI����ٶȡ�
����SPI FLASH �ٶ��㹻�죬����VS1003����ʼ��ʱ�������SPI�ٶȽ�������
CLKI��Ƶ����3��Ƶ����ʼ�����SPI ������ٶȡ�������CLKI/6 ���Ϳ���������������MP3�ˡ� 
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
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//����spi�Ŀ�ʼ�ٶ�Ϊ72M/128=562.5K
			SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
			SPI_InitStructure.SPI_CRCPolynomial = 7;
			SPI_Init(SPI1, &SPI_InitStructure);
			/* Enable SPI1  */
			SPI_Cmd(SPI1, ENABLE);
		
	}else if(device==2){
      RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2,ENABLE ); //����APB(APB1)
			SPI_Cmd(SPI2, DISABLE);/* Disable SPI2  */
		 
			/* SPIx configuration */
			SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
			SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      //����SPI����ģʽ:����Ϊ��SPI
			SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                        //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                       //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
			SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;           //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
			//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//����spi�Ŀ�ʼ�ٶ�Ϊ72M/128=562.5K   //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
			SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
			SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRCֵ����Ķ���ʽ
			SPI_Init(SPI2, &SPI_InitStructure);                //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
			
		
		/* Enable SPI2  */
			SPI_Cmd(SPI2, ENABLE);                                               //ʹ��SPI����
		  SPI2_ReadWriteByte(0xff);//��������
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
   MP3_xDCS(1);	  //xDCS  ȡ�����ݴ���
   MP3_xCS(1);    //xCS   ȡ������� 
   MP3_Reset(1); //��λ����
   while(VS1003B_WAIT_DREQ( ) == 0);//�ȴ� ����
}

/********************************

  VS1003��λ    VS1003�ĳ�ʼ��

������оƬһ������ʼ������VS1003��˵ͬ���Ǽ�����Ҫ�ġ���ʼ���Ĺ��̴����������ģ�

1.Ӳ����λ����XRESET����

2.��ʱ����XDCS��XCS��XRESET�ø�

3.��MODE��д��0X0804

4.�ȴ�DREQΪ��

5.����VS1003��ʱ�ӣ�SCI_CLOCKF=0x9800��3��Ƶ

6.����VS1003�Ĳ����ʣ�SPI_AUDATA=0xbb81��������48k��������

7.����������SPI_BASS=0x0055

8.����������SCI_VOL=0x2020

9.��һ�����ܶ��˺��ӣ���VS1003����4���ֽڵ���Ч���ݣ���������SPI����




�ڽ�������ȷ�ĳ�ʼ���󣬻�Ҫ���ؼ��һ��VS1003��ģ�ⲿ���Ƿ�����

��VS1003������DVDD��AVDD�ܽ��Լ�XRESET��TEST����32�����ţ���+3.0V��
Ȼ�����RCAP���ţ���Ӧ����1.3V���ң�����оƬģ�ⲿ��δ����������


�������λ��SPI_MODE = 0x0804��
��ȴ�DREQΪ�ߣ������λ��������
������VS1003��ʱ�ӣ�SCI_CLOCKF = 0x9800��3��Ƶ��
������VS1003�Ĳ����ʣ�SPI_AUDATA = 0xBB81��������48k����������
������������SPI_BASS = 0x0055��
������������SCI_VOL = 0x2020��
����vs1003����4���ֽ���Ч���ݣ���������SPI���͡�



	
CLOCKF �Ĵ���������Ĵ�����������ʱ��Ƶ�ʡ���Ƶ�������Ϣ���üĴ����ĸ�λ���������ʾ��
CLOCKF �Ĵ���
λ	              15:13	                     12:11	                   10:0

����              SC_MULT                    SC_ADD                    SC_FREQ

����              ʱ�ӱ�Ƶ��                  ����Ƶ                   ʱ��Ƶ��

˵��	 CLKI=XTALI�� (SC_MULT�� 0.5+1)     ��Ƶ���� =SC_ADD*0.5      ���ⲿʱ��Ƶ�ʲ�Ϊ12.288Mhz ʱ���ⲿʱ�ӵ�Ƶ�ʡ�
																	 �ⲿʱ��Ƶ��Ϊ12.288Mhz ʱ���˲�������Ϊ 0
SC_FREQ ���� 4Khz Ϊ������һ��ʱ�ӼĴ��������ⲿʱ�Ӳ��� 12.288M ��ʱ��
����㹫ʽΪ�� SC_FREQ=(XTALI-8000000)/4000 ʽ��Ϊ XTALI �ĵ�λΪ Hz��
�ϱ��� CLKI ���ڲ�ʱ��Ƶ�ʣ� XTALI ���ⲿ�����ʱ��Ƶ�ʡ�
��������ʹ�õ��� 12.288M �ľ�������SC_FREQ = 0��

��ģ�鲥����Ƶ�ļ��ǳ��ļ򵥣�һ�����Ƶ�ļ���MP3/WMA/OGG/WAV/MIDI/AAC�ȣ���ֻ��Ҫ�򵥵� 3 ����������ʵ����Ƶ���š�
��1����λVS1003
���������Ӳ��λ����λ����Ϊ����VS1003��״̬�ص�ԭʼ״̬��׼��������һ�׸��������ｨ����ÿ�׸�������֮ǰ��ִ��һ��Ӳ����λ�������λ���Ա���õĲ������֡�
��2������VS1003��ؼĴ���
���õļĴ������� VS1003 ��ģʽ�Ĵ�����MODE����ʱ�ӼĴ�����CLOCKF���������Ĵ�����BASS���������Ĵ�����VOL���ȡ�
��3��������Ƶ����
�������������������Ժ�����ʣ����Ҫ�������飬������VS1003��������Ƶ�����ˣ�


	
	//VS1003B_CMD_Write(SPI_CLOCKF, 0X4430);    // 2.0x 12.288MHz
	//VS1003B_CMD_Write(SPI_CLOCKF, 0X4000);    // 2.0x 12.288MHz
	
    //VS1003B_CMD_Write(SPI_CLOCKF, 0XE000 | 0x1800 | 0x3ff);
    //VS1003B_CMD_Write(SPI_AUDATA, 0Xfefe); 	//������65k��������	
	
	8.6.6 SCI AUDATA (RW)
When decoding correct data, the current sample rate and number of channels can be found in bits 15:1
and 0 of SCI AUDATA, respectively. Bits 15:1 contain the sample rate divided by two, and bit 0 is 0 for
mono data and 1 for stereo. Writing to SCI AUDATA will change the sample rate directly.
Note: due to a bug, an odd sample rate reverses the operation of the stereo bit in VS1003b.
Example: 44100 Hz stereo data reads as 0xAC45 (44101).
Example: 11025 Hz mono data reads as 0x2B10 (11025).
Example: 11025 Hz stereo data reads as 0x2B11 (11026).
Example: Writing 0xAC80 sets sample rate to 44160 Hz, stereo mode does not change.
	
   // VS1003B_CMD_Write(SPI_AUDATA, 0Xac45); 	//������44100��������

**********************************/




void VS1003B_SoftReset(void){//��λ
	
	
	 INT8U	count=0;
	
	
	 VS1003B_HardReset();//Ӳ����λ����
	
	
   VS1003B_CMD_Write(SPI_MODE,0x0804,2);// �����λ,��ģʽ	
   while(VS1003B_WAIT_DREQ( )==0);
   
	 while(VS1003B_REG_Read(SPI_CLOCKF)!=0x9800){//����VS10XX��ʱ��,3.5��Ƶ ,2xADD
			VS1003B_CMD_Write(SPI_CLOCKF, 0X9800,2);    // 3.0x 12.288MHz
			DelayMs(10);
			count++;
			if(count>200) break;	
	 } 
	 count=0;
	 while(VS1003B_WAIT_DREQ( )==0);		//�ȴ�DREQ�źű��
	
	 while(VS1003B_REG_Read(SPI_AUDATA)!=0xbb81){// ������48k��������
			VS1003B_CMD_Write(SPI_AUDATA, 0xbb81,2); 	//(0xbb81)������48k��������//(0Xfefe); 	//������65k��������	
			DelayMs(10);
			count++;
			if(count>200) break;	
	 } 
	 count=0;
	 while(VS1003B_WAIT_DREQ( )==0);		//�ȴ�DREQ�źű��
	
	 while(VS1003B_REG_Read(SPI_BASS)!=0x0055){// �����ص�����0x00F6��60HZ���µ���Ƶ�źŽ���15dB����ǿ��0x7A00��10KHZ���ϵ��źŽ���10.5dB����ǿ
			VS1003B_CMD_Write(SPI_BASS,0x0055,2);
			DelayMs(10);
			count++;
			if(count>200) break;	
	 }  
	 count=0;
	 while(VS1003B_WAIT_DREQ( )==0);
	 
	 while(VS1003B_REG_Read(SPI_VOL)!=0x1010){// VS10XX ����
			VS1003B_CMD_Write(SPI_VOL,0x00002,2);  	
		  //VS1003B_CMD_Write(SPI_VOL,0x3030,2);   //���� 0x3030 		���ǿ���VS1003������������� 
			DelayMs(10);
			count++;
			if(count>200) break;	
	  }  
    
  VS1003B_ResetDecodeTime();				 //��λ����ʱ��     
    
    while(VS1003B_WAIT_DREQ( )==0); 		//�ȴ�DREQ�źű��
    MP3_xDCS(0);		 					        //xDCS=0;ѡ�����ݴ���
    MP3_xCS(1);  					            //xCS=1;
    SPI2_ReadWriteByte(0xFF);         //��vs1003����4���ֽ���Ч���ݣ���������SPI����  
    SPI2_ReadWriteByte(0xFF);
    SPI2_ReadWriteByte(0xFF);
    SPI2_ReadWriteByte(0xFF);
    MP3_xDCS(1);	   				           //xDCS=1;ȡ�����ݴ���
		DelayMs(10);
}


	


/*
	���SCI�����Ƿ���ȷд��
���������ƼĴ���SCI_VOLѭ��д�����ֵ�����ֵ������������ܴӶ��������ε�
�����������岽�����£�
������xCS��
������������ߣ�SCI_VOL = 0x0000��
������xCS��
��ȴ�500ms�����ʱ�������0.5��1s֮�䣬̫��̫С���ܶ��޷�������
������xCS��
������������ͣ�SCI_VOL = 0xFFFF��
��ȴ�500ms������ͬ�ϣ�
������xCS��
��ѭ�����������ϲ����޷�ʶ��


9��7��4 SCI ����
SCI ����ͨ������8�ֽڵ����г�ʼ����0x53 0x70 0xEE n 0 0 0 0,�����n ��ȥ48 Ϊ���ԵļĴ�
����š������ı����ԼĴ��������ݱ����Ƶ�SCI_HDAT0,�������ԵļĴ���ΪSCI_HDAT0��������������
��SCI_HDAT1��
���磺��n����48����Ĵ���0��SCI_MODE�������ݱ����Ƶ�SCI_HDAT0.

*/

void VS1003B_SCI_Test(void)
{   
	  MP3_xCS(1); 
	  MP3_xDCS(0);		
    VS1003B_CMD_Write(SPI_MODE,0x0820,2);	//����vs1003�Ĳ���ģʽ	      
	  MP3_xDCS(0);		 				//xDCS=0;ѡ�����ݴ���
    MP3_xCS(1);  				    //xCS=1;
    SPI1_ReadWriteByte(0x53);
    SPI1_ReadWriteByte(0x70);
    SPI1_ReadWriteByte(0xee);
    SPI1_ReadWriteByte(48);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);	
    MP3_xDCS(1);	    			//xDCS=1;ȡ�����ݴ���
}














void VS1003B_DetectSCIOk(void){
	
	VS1003B_CMD_Write(SPI_MODE,0x0820,2);	     //����vs1003�Ĳ���ģʽ	      
	while(VS1003B_WAIT_DREQ( )==0);            //�ȴ���������--�ȴ�����

	MP3_xCS(0); 
	VS1003B_CMD_Write(SPI_VOL,0xfefe,2);      //���� 
	MP3_xCS(1); 
	while(VS1003B_WAIT_DREQ( )==0);            //�ȴ���������--�ȴ�����

	MP3_xCS(0); 
	VS1003B_CMD_Write(SPI_VOL,0xffff,2);      
	MP3_xCS(1); 
	while(VS1003B_WAIT_DREQ( )==0);            //�ȴ���������--�ȴ�����
}



/****************************************

      VS1003 IMA ADPCM¼����ʼ��

*****************************************/
void InitRecordADPCM(void)
{
    VS1003B_CMD_Write(SPI_VOL,     0x1414,2); //  ¼������
    VS1003B_CMD_Write(SPI_BASS,    0x0,2);    //  ¼����Ч
    VS1003B_CMD_Write(SPI_CLOCKF,  0x4430,2); //  ��ƵFc = 2.0 * 12.288MHZ
    VS1003B_CMD_Write(SPI_AICTRL0, 12,2);     //  ��Ƶϵ��D=12��������8KHZ��D=8��������12KHZ��D=6��������16KHZ
    VS1003B_CMD_Write(SPI_AICTRL1, 0,2);      //  ʹ���Զ�����
    VS1003B_CMD_Write(SPI_MODE,    0x1804,2); //  ʹ����˷�¼��
}

/********************************

  ����Ƶ�׷����Ĵ��뵽VS1003

**********************************/
void VS1003B_LoadPatch(void)
{
    u16 i;

    for (i = 0; i < 943; i++){
        VS1003B_CMD_Write(atab[i],dtab[i],2); 
    }
}

/********************************

  �õ�Ƶ������

**********************************/
void VS1003B_GetSpec(INT8U *p)
{
    INT8U i;

    VS1003B_CMD_Write(SPI_WRAMADDR,0x1804,2);                                                                                             
    for(i = 0; i < 14; i++){                                                                               
        *p++ = VS1003B_REG_Read(SPI_WRAM) & 0x63;//ȡС��100����    
    } 
}

/****************************************

     VS1003B����������
 uint8 test[] = {0x53, 0xEF, 0x6E, 0x24, 0x00, 0x00, 0x00, 0x00}; // ��vs�������Ҳ�������
 uint8 back[] = {0x45, 0x78, 0x69, 0x74, 0x00, 0x00, 0x00, 0x00}; // ��vs�����˳���������

�����ṩ�������Ҳ��Ե����̣�����ʵ��Ӳ������ͨ�������յ�Ч�����ڶ�����������һƵ�ʵ���������Ƶ�ʿ���ͨ�����������ģ���

�����������£�

 1.����VS1003�Ĳ���ģʽ��SPI_MODE=0X0820

 2.�ȴ�DREQΪ��

 3.��XDCS�ӵͣ���XCSҪ�øߣ�ѡ��VS1003�����ݽӿ�

 4.��VS1003�������Ҳ������0X53 0XEF 0X6E 0X30 0X00 0X00 0X00 0X00

   ����0X30ΪƵ�ʣ��û������޸�Ϊ����ֵ

 5.��ʱһ��ʱ��

 6.�˳����Ҳ��ԣ��������0X45 0X78 0X69 0X74 0X00 0X00 0X00 0X00

 7.��ʱһ��ʱ��

 8.ѭ����������

//ʹ���Ҳ���Ƶ���������ӣ��ʵ���ʱ�������ڶ����о�����������Խ��Խ�ߵ�����
******************************************/
void VS1003B_SineTest(INT8U fre)
{   
//	VS1003B_RESET_ENABLE;
//	SPI1_ReadWriteByte(0xff);               // ��������
//	VS1003B_XDCS_DISABLE;
//	VS1003B_XCS_DISABLE;
//	VS1003B_RESET_DISABLE;
	
//#if VS1003_DEBUG      187     int16u_t data = 0x0;;188     printf("Vs1003_Sine_Test:begin\nGet in SinTest Mode\n");189     #endif
 //#if VS1003_DEBUG     193     data = Vs1003_CMD_Read(SPI_MODE);194     printf("Read REGS-SIN, SPI_MODE=%x\n",data);195     #endif	
   
	  VS1003B_CMD_Write(SPI_MODE,0x0820,2);	//����vs1003�Ĳ���ģʽ �������ԣ��� 0 �żĴ���д�� 0x0820 SM_SDINEW Ϊ 1  SM_TEST Ϊ 1 	
	  while(VS1003B_WAIT_DREQ( ) == 0);		    //�ȴ���  VS1003��DREQΪ�߲���д������
	
	
	  MP3_xDCS(0);		 				  //xDCS=0;ѡ�����ݴ���  ������Ƭѡ��������SDI����
    MP3_xCS(1);   				  //xCS=1;
    SPI2_ReadWriteByte(0x53);//д������ 8 ���ֽ� ,�������Ҳ���
    SPI2_ReadWriteByte(0xef);
    SPI2_ReadWriteByte(0x6e);
    SPI2_ReadWriteByte(fre); /* ���� x �����������Ҳ��������Ҳ���Ƶ��*/
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);	
		
		DelayMs(5000);
    //while(VS1003B_WAIT_DREQ( ) == 0);		//�ȴ���   ������ʱһ��ʱ�� ,��������������������������ʱ�������棡
		
    SPI2_ReadWriteByte(0x45); /* д������ 8 ���ֽ� ,�˳����Ҳ��� */
	  SPI2_ReadWriteByte(0x78);
    SPI2_ReadWriteByte(0x69);
    SPI2_ReadWriteByte(0x74);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);  
		
	 //while(VS1003B_WAIT_DREQ( ) == 0);		//�ȴ���   ������ʱһ��ʱ�� ,��������������������������ʱ�������棡
	  DelayMs(5000);

    MP3_xDCS(1);	   			//xDCS=1;ȡ�����ݴ���  �ر�����Ƭѡ
}





/*
** �������� : void VS_SinTest(INT8U x).
** �������� : ���Ҳ��Ժ��� ,��� vs1003�Ƿ����� .
** ������� : INT8U x ���Ҳ�Ƶ�� .
** ������� : None.
** ���ز��� : None.
��Ȩ����������ΪCSDN������yi_tianchou����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/yi_tianchou/article/details/104724302
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
//   VS1003_WriteReg(SPI_MODE,0x0820);/* ����vs1003�Ĳ���ģʽ */
//   while((GPIO_ReadInputDataBit(VS1003B_DREQ_PORT, VS1003B_DREQ_BIT)) == 0);//�ȴ�����
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
//   value = VS1003_ReadReg(SPI_HDAT0); /* ����õ���ֵΪ0x807F���������á� */
///printf("regvalueH:%x\n",regvalue>>8);//������ 
        //printf("regvalueL:%x\n",regvalue&0xff);//������ 

//}     



/****************************************

     VS1003B RAM ����
     ����0X807F���ɹ�
* FunctionName   : VS1053RamTest()
* Description    : �ڴ���ԣ�0x8000��ʾ������ɣ�0x83FF��ʾ���
* EntryParameter : None
* ReturnValue    : ��÷���0�����򷵻�1
 uint8 test[] = {0x4D, 0xEA, 0x6D, 0x54, 0x00, 0x00, 0x00, 0x00}; // 


9��7��3 �洢������
�洢������ģʽͨ������8 �ֽڵ�����0x4D 0xEA 0x6D 0x54 0 0 0 0����ʼ�����ڴ�����֮�󣬵�
��500000 ��ʱ�����ڣ��Ϳ��Դ�SCI �Ĵ���SCI_HDAT0�ж�ȡ������������ݵ�ÿλ�������£�
λ                   ����            ����

15                  0x8000           ���Խ���
14:7                                 δʹ��
6                   0x0040           ���в��Գɹ�
5                   0x0020           I RAM ���
4                   0x0010           Y RAM ���
3                   0x0008           X RAM ���
2                   0x0004           I ROM ���
1                   0x0002           Y ROM ���
0                   0x0001           X ROM ���
                   0x807F ���ж����
******************************************/
INT16U VS1003B_RAMTest(void)
{   
    INT16U state = 0;
    	 
    VS1003B_CMD_Write(SPI_MODE,0x0820,2);	//����vs1003�Ĳ���ģʽ    	   
    while(VS1003B_WAIT_DREQ( ) == 0);		//�ȴ�����
    
	  MP3_xDCS(0);		  				//xDCS=0;ѡ�����ݴ���
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
    MP3_xDCS(1);	   			   //xDCS=1;ȡ�����ݴ���
	
    while(VS1003B_WAIT_DREQ( ) == 0);
    state  = VS1003B_REG_Read(SPI_HDAT0) << 8;
    state |= VS1003B_REG_Read(SPI_HDAT1);/* ����õ���ֵΪ0x807F���������á� */
    
    return(state);		 
}



/*
�����׿��洢���ʲ�̸��̸ֻ���ݵ�д�뷽������ʵд�����ݵķ���ʮ�ּ򵥡�
��Ҫ���ǿ�DREQ�źţ���VS1003��FIFO�ܹ��������ݵ�ʱ������ߵ�ƽ��
ÿ�ο���д��32���ֽڵ����ݡ���DREQ���ʱ����Ƭ����Ҫֹͣ���ݵķ��͡�

�����д���ݵķ������£�
1.��XDCS����
2.�ȴ�DREQΪ��
3.ͨ��SPIд������
4.���ļ�û�н���ǰ�����ظ�2��3����
5.�����е����ݶ�������Ϻ������2048����Ч�ֽڣ��������VS1003�����ݻ�����
6.��XDCS�ø�


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
	
  
	// ����SPI1����ͨѶ����  SD��Ƭѡ����SD_CS    SPI1_SCK, SPI1_MISO, SPI1_MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}


/*******************************************************************************
* Function Name  : VS1003_Init
* Description    : VS1003�˿ڳ�ʼ��
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
	  
	/* SPI��IO�ں�SPI�����ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);


	//SPI��IO������ 
	
	 //GPIO_Pin_12  NSS note that NSS pin of the SPI slave is use to select the
   // device, if it is pulled up, SPI slave will not shift
   // any byte to its shift register

	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;  // SPI    NSS���������  GPIO_Pin_12 |
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������		
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
	
	
	// ����VS1003��������:            DREQ����Ϊ����,   XREST   xDCS ����Ϊ���
		//******************************************
		//******************************************
	
		GPIO_InitStructure.GPIO_Pin = VS1003B_DREQ_BIT ;  // ���ݿ��ƶ˿�    DREQ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//DREQ����Ϊ����,
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VS1003B_DREQ_PORT, &GPIO_InitStructure);	
	
	
	
	  GPIO_InitStructure.GPIO_Pin =VS1003B_RESET_BIT;		  		//XREST   Ӳ��ȱ��һ��IO��λ�ߣ�����ͼû�������ߣ�????????????????????????????
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VS1003B_RESET_PORT, &GPIO_InitStructure);
	

    GPIO_InitStructure.GPIO_Pin =   VS1003B_DATA_CS_BIT;	//   xDCS 	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VS1003B_DATA_CS_PORT, &GPIO_InitStructure);
	
	
	  GPIO_InitStructure.GPIO_Pin =   VS1003B_CMD_CS_BIT; 	//     xDS 	�˿ڷ�ΪA  B��������ľ䣬Ѫ�Ľ�ѵ��������
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
	UINT 		  br;             		// File R/W count  �ļ���������  
	
 
	f_mount(&fs,"0:", 0);  	     // ע���ļ�ϵͳ--//����SD�� 		
		
	// ���ļ� 
	result = f_open(&file, "0:sjw.txt", FA_OPEN_ALWAYS | FA_READ);//��ס����ǰ��FA_CREATE_ALWAYS | FA_READ
	if (result !=  FR_OK)
	{
		printf("Don't Find File:  sjw.txt\r\n");
		return;
	}else
	    printf("���ļ�sjw.txt�ɹ�������\r\n");
	

	// ��ȡ�ļ� 
	result = f_read(&file, &readBuf, sizeof(readBuf) - 1, &br);
	if (br > 0){
		printf("\r\n sjw.txt �ļ����� : \r\n %s\r\n", readBuf);
		//readBuf[br]=0;
	}else{
		printf("\r\n sjw.txt.txt �ļ����� : \r\n");
	}
	//�ر��ļ�
	f_close(&file);
	// ж���ļ�ϵͳ 
	f_mount( NULL,"0", 0);
	
}


//FA_OPEN_ALWAYS   ����ļ����ڣ���򿪣����򣬴���һ�����ļ���
void TestWriteFile(void)
{
		// �ļ�ϵͳ��صı���			
  FRESULT  result;
  FATFS    fs;
	DIR      DirInf;
  FIL      file;
	UINT 		 bw;             		// File R/W count  �ļ�д������  
	
	
  f_mount(&fs,"0:", 0);  	     // ע���ļ�ϵͳ--//����SD�� 				
		
	// ���ļ� 
	result = f_open(&file, "0:sjw.txt", FA_OPEN_ALWAYS | FA_WRITE );//��ס����ǰ��FA_CREATE_ALWAYS | FA_WRITE
		// дһ������ 
	result = f_write(&file, "sjw is miss my baba & mama for ever! \r\n", 36, &bw);
	if (result == FR_OK){
		printf("sjw.txt �ļ�д��ɹ�\r\n");
	}else{
		printf("sjw.txt �ļ�д��ʧ��\r\n");
	}	

	//�ر��ļ�
	f_close(&file);
	// ж���ļ�ϵͳ 
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
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&SPI2->DR;			//�����ַ
//	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)SPI2_RxBuf;					//DMA1�ڴ��ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;											//���ݴ��䷽��:���赽�ڴ�
	DMA_InitStructure.DMA_BufferSize=320;								//DMA1�����С
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;				//�����ַ����
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; 								//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; //���ݿ��16λ
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; 		//���ݿ��16λ
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;														//DMA1����ѭ��ģʽ
	DMA_InitStructure.DMA_Priority=DMA_Priority_Low;											//DMA1ͨ��4�����ȼ���
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;														//DMA1���ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&SPI2->DR;			//�����ַ
	//DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)SPI2_TxBuf;					//DMA1�ڴ��ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;											//���ݴ��䷽��:�ڴ浽����
	DMA_InitStructure.DMA_BufferSize=320;								//DMA1�����С
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;				//�����ַ����
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable; 								//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord; //���ݿ��16λ
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; 		//���ݿ��16λ
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;														//DMA1����ѭ��ģʽ
	DMA_InitStructure.DMA_Priority=DMA_Priority_Low;											//DMA1ͨ��5�����ȼ���
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;														//DMA1���ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel5,&DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel4,DMA_IT_HT,ENABLE);
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	
	DMA_Cmd(DMA1_Channel4,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);
 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;		//SPI�ӻ�
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//���ͽ���16λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//ʱ�����յ�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//���ݲ����ڵ�1��ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;       //CS����Ӳ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//���ݴ����MSBλ��ʼ
	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
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
��������������������������������
��Ȩ����������ΪCSDN������Younique741����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/qq_44065318/article/details/125883338


��������������������������������
��Ȩ����������ΪCSDN������Younique741����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/qq_44065318/article/details/125883338
*/


/****************************************

     VS1003B ��ȡ����ʱ��  //�õ�mp3�Ĳ���ʱ�� n sec

******************************************/ 
INT16U VS1003B_GetDecodeTime(void)
{
    return(VS1003B_REG_Read(SPI_DECODE_TIME));
}

/*
//�õ�mp3�Ĳ���ʱ�� n sec
u16 VS1003_GetDecodeTime(void)
{
        return VS1003B_REG_Read(0x04);
}
*/