/*
*********************************************************
*   					 ͷ�ļ�
*********************************************************
*/
#include <string.h>
//#include "def.h"
//#include "option.h"
//#include "2410addr.h"
//#include "2410lib.h"
//#include "2410slib.h" 

/*
*********************************************************
*   					 �궨��
*********************************************************
*/
#define BAD_CHECK   (1)
#define ECC_CHECK   (0)
/*
*********************************************************
*   					 ����ԭ��
*********************************************************
*/
static U16 NF_CheckId(void);
static void NF_Reset(void);
static void NF_Init(void);
char Check10(int data, char seq);
static int NF_EraseBlock(U32 blockNum);
static int NF_WritePage(U32 block,U32 page,U8 *buffer);
static int NF_ReadPage(U32 block,U32 page,U8 *buffer);
int TestECC(void);
/*buffer size is 512 bytes*/
/*static int NF_IsBadBlock(U32 block);*/
/*static int NF_MarkBadBlock(U32 block);*/


int DownloadData(void);
static void InputTargetBlock(void);

/*
*********************************************************
*   					 ����
*********************************************************
*/
static U32 srcAddress;
/*static U32 targetBlock;    */ /* Block number (0 ~ 4095)*/
static U32 targetSize;      /* Total byte size */

U32 downloadAddress;
U32 downloadProgramSize=0x0;
U32 targetBlock = 200;
/*
*********************************************************
* �������ܣ���������NAND FLASH K9F1208 ��̲��Ժ�����				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/

void K9F1208_Program(void)
{
    int i;
    int programError=0;
    U8 *srcPt,*saveSrcPt;
    U32 blockIndex;

    downloadAddress=0x30500000;
    printf("\n[SMC(K9F1208V0M) NAND Flash writing program]\n");

    NF_Init();/*��ʼ��*/
    /*rINTMSK = BIT_ALLMSK;*/   
    targetSize=downloadProgramSize;
    if(targetSize==0)
    {
        srcAddress=0x30500000;          
    }
    else 
        srcAddress=downloadAddress+4; /*to discard the data head for the size*/
        
    /*InputTargetBlock();*/	/*�Ӵ��ڽ�����д�ļ��ĸ�����Ϣ srcAddress��targetBlock��targetSize will be determined*/
    
    printf("source base address(0x3050000x)=0x%x\n",srcAddress);
    printf("target start block number      =%d\n",targetBlock);
    printf("target size        (0x4000*n)  =0x%x\n",targetSize);

    srcPt=(U8 *)srcAddress;
    blockIndex=targetBlock;
    while(1)
    {
        saveSrcPt=srcPt;    

  /*      #if BAD_CHECK  */   /*������  */
  /*          if(NF_IsBadBlock(blockIndex)) */  /* 1:bad 0:good*/
  /*          {
                blockIndex++;  */ /* for next block*/
 /*               continue;
            }
        #endif
 */       
        if(!NF_EraseBlock(blockIndex))/*�����*/
        {
            blockIndex++;   /* for next block*/
            continue;
        }        
        for(i=0;i<2;i++)
        {
            if(!NF_WritePage(blockIndex,i,srcPt))/* block num, page num, buffer*/
            {
                programError=1;
                break;
            }
            /*#if ECC_CHECK*/    
            if(!NF_ReadPage(blockIndex,i,srcPt))
            {
                    printf("ECC Error(block=%d,page=%d!!!\n",blockIndex,i);
            }
            /*#endif*/      
            srcPt+=512; /* Increase buffer addr one pase size*/
            printf(".");
            if((U32)srcPt>=(srcAddress+targetSize)) /* Check end of buffer*/
                break;  /* Exit for loop*/
        }
        
        if(programError==1)
        {
            blockIndex++;
            srcPt=saveSrcPt;
            programError=0;
            continue;
        }
        
        if((U32)srcPt>=(srcAddress+targetSize))
            break;  /* Exit while loop*/
        blockIndex++;
    }
}


/*
*********************************************************
* �������ܣ��������������ż���С��				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
/*
static void InputTargetBlock(void)
{
    printf("\nSource size:0h~%xh\n",downloadProgramSize);
    printf("\nAvailable target block number: 0~4095\n");
    printf("\nInput target block number:");
    targetBlock=Uart_GetIntNum();  */ /* Block number(0~4095)*/
/*    if(targetSize==0)
    {
        printf("Input target size(0x4000*n):");
        targetSize=Uart_GetIntNum();  */  /* Total byte size*/
 /*  }
}
*/
/*
*********************************************************
* �������ܣ����������������š�				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
/*
void K9F1208_PrintBadBlockNum(void)
{
    int i;
    U16 id;

    printf("\n[SMC(K9F1208V0M) NAND Flash bad block check]\n");
    
    NF_Init();
    id=NF_CheckId();*//*IDУ��*/
 /*   printf("ID=%x(0xec76)\n",id);
    if(id!=0xec76)*//*����Ҫ����K9F1208��ID�ţ���������������*/
 /*   return;
    
    for(i=0;i<4096;i++)
    {
    	NF_IsBadBlock(i);  */ /* Print bad block*/
 /*   }
}
*/
/*
*********************************************************
* �������ܣ������������һҳ���ݡ�				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
/* Printf one page*//*
void K9F1208_PrintBlock(void)
{
    int i,j;
    U16 id;
    U32 block,page;
    U8  buffer[512];

    printf("\n[SMC(K9F1208V0M) NAND Flash block read]\n"); 
    
    NF_Init();
    id=NF_CheckId();
    printf("ID=%x(0xec76)\n",id);
    if(id!=0xec76)
    return;

    printf("Input target block number :");
    block=Uart_GetIntNum();
    printf("Input target page number :");   
    page=Uart_GetIntNum();

    NF_ReadPage(block,page,buffer);
    printf("block=%d,page=%d:",block,page);
    for(j=0;j<512;j++)
    {
        if(j%16==0)
        printf("\n%3xh:",j);
        printf("%02x ",buffer[j]);
    }
    printf("\n");      
}
*/
/**************************************************
/***           H/W dependent functions           **
/************************************************** 

/* block0: reserved for boot strap*/
/* block1~4095: used for OS image*/
/* badblock SE: xx xx xx xx xx 00 ....*/
/* good block SE: ECC0 ECC1 ECC2 FF FF FF ....*/

#define WRITEVERIFY  (0)  /*verifing is enable at writing.*/

#define NF_CMD(cmd) 	{rNFCMD=cmd;}
#define NF_ADDR(addr)   {rNFADDR=addr;} 
#define NF_nFCE_L() 	{rNFCONF&=~(1<<11);}
#define NF_nFCE_H() 	{rNFCONF|=(1<<11);}
#define NF_RSTECC() 	{rNFCONF|=(1<<12);}
#define NF_RDDATA()     (rNFDATA)
#define NF_WRDATA(data) {rNFDATA=data;}

#define NF_WAITRB()    {while(!(rNFSTAT&(1<<0)));} 
/*wait tWB and check F_RNB pin.   */

#define ID_K9F1208V0M   0xec76 /*����ȷ��ID��*/

#if 1
/* HCLK=100Mhz*/
#define TACLS       0  /*1clk(0ns)*/ 
#define TWRPH0      3  /*3clk(25ns)*/
#define TWRPH1      0  /*1clk(10ns)*/  /*TACLS+TWRPH0+TWRPH1>=50ns*/
#else
/* HCLK=50Mhz*/
#define TACLS       0  /*1clk(0ns)*/
#define TWRPH0      1  /*2clk(25ns)*/
#define TWRPH1      0  /*1clk(10ns)*/
#endif


static U8 seBuf[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};


/*
*********************************************************
* �������ܣ��������ǵײ�ȷ������ĳ���				
* ���������block--���
* �����������
* ����ֵ  ����
*********************************************************
*/
/*static int NF_IsBadBlock(U32 block)
{
    int i;
    unsigned int blockPage;
    U8 data;
    
    
    blockPage=(block<<5);  */ /* For 2'nd cycle I/O[7:5]*/ 
/*    
    NF_nFCE_L();    
    NF_CMD(0x50);   */    /* Spare array read command*/
 /*   NF_ADDR(517&0xf);   */    /* Read the mark of bad block in spare array(M addr=5)*/ 
 /*   NF_ADDR(blockPage&0xff);  */  /* The mark of bad block is in 0 page*/
  /*  NF_ADDR((blockPage>>8)&0xff); */  /* For block number A[24:17]*/
  /*  NF_ADDR((blockPage>>16)&0xff); */ /* For block number A[25]*/
/*
   for(i=0;i<10;i++); */  /* wait tWB(100ns) ?????*/
  /*  
    NF_WAITRB();*/    /* Wait tR(max 12us)*/
    /*
    data=NF_RDDATA();

    NF_nFCE_H();    

    if(data!=0xff)
    {
        printf("[block %d has been marked as a bad block(%x)]\n",block,data);
        return 1;
    }
    else
    {
        return 0;
    }
}
*/
/*
*********************************************************
* �������ܣ��������ǵײ��ǻ���ĳ���				
* ���������block--���
* �����������
* ����ֵ  ����
*********************************************************
*//*
static int NF_MarkBadBlock(U32 block)
{
    int i;
    U32 blockPage=(block<<5);
 
    seBuf[0]=0xff;
    seBuf[1]=0xff;    
    seBuf[2]=0xff;    
    seBuf[5]=0x44; */  /* Bad blcok mark=0*/
    /*
    NF_nFCE_L(); 
    NF_CMD(0x50); */  /*????*/
 /*   NF_CMD(0x80);  */ /* Write 1st command*/
 /*   
    NF_ADDR(0x0);  */         /* The mark of bad block is*/ 
  /*  NF_ADDR(blockPage&0xff);  */      /* marked 5th spare array*/ 
 /*   NF_ADDR((blockPage>>8)&0xff); */  /* in the 1st page.*/
  /*  NF_ADDR((blockPage>>16)&0xff);  
    
    for(i=0;i<16;i++)
    {
    	NF_WRDATA(seBuf[i]);  */  /* Write spare array*/
  /*  }

    NF_CMD(0x10); */  /* Write 2nd command*/
/*    
    for(i=0;i<10;i++);*/  /*tWB = 100ns. ???????*/
/*
    NF_WAITRB();  */    /* Wait tPROG(200~500us)*/
  /*
    NF_CMD(0x70);
    
    for(i=0;i<3;i++); */ /*twhr=60ns??????*/
    /*
    if (NF_RDDATA()&0x1)*/ /* Spare arrray write error*/
 /*   {   
        NF_nFCE_H();
        printf("[Program error is occurred but ignored]\n");
    }
    else 
    {
        NF_nFCE_H();
    }

    printf("[block #%d is marked as a bad block]\n",block);
    return 1;
}
*/

/*
*********************************************************
* �������ܣ��������ǵײ�NF ID��У�����				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
static U16 NF_CheckId(void)
{
    int i;
    U16 id;
    
    NF_nFCE_L();
    
    NF_CMD(0x90);
    NF_ADDR(0x0);
    
    for(i=0;i<10;i++); /*wait tWB(100ns)?????*/
    
    id=NF_RDDATA()<<8;  /* Maker code(K9S1208V:0xec)*/
    id|=NF_RDDATA();    /* Devide code(K9S1208V:0x76)*/
    
    NF_nFCE_H();
    
    return id;
}

/*
*********************************************************
* �������ܣ��������ǵײ�NF ��λ����				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
static void NF_Reset(void)
{
    int i;
    U16 id;
    
    
    NF_nFCE_L();

    NF_CMD(0xFF);   /*reset command*/

    for(i=0;i<10;i++);  /*tWB = 100ns. ??????*/

    NF_WAITRB();      /*wait 200~500us;*/
     
    NF_nFCE_H();
}

/*
*********************************************************
* �������ܣ��������ǵײ�NF ��ʼ������				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
static void NF_Init(void)
{
    rNFCONF=(1<<15)|(1<<14)|(1<<13)|(1<<12)|(1<<11)|(TACLS<<8)|(TWRPH0<<4)|(TWRPH1<<0); 
    /* 1  1    1     1,   1      xxx,  r xxx,   r xxx  */      
    /* En 512B 4step ECCR nFCE=H tACLS   tWRPH0   tWRPH1*/
    
    NF_Reset();
}

/*
*********************************************************
* �������ܣ���������Check '10'����				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*//* Check '10' pattern*/
char Check10(int data, char seq) 
{
    if(data & (0x2<< seq*2) )
    return 1;
    else
    return 0;
}

/* 1block=(512+16)bytes x 32pages*/
/* 4096block*/
/* A[23:14][13:9]*/
/*  block   page*/
/*
*********************************************************
* �������ܣ��������ǵײ���������				
* ���������block--���
* �����������
* ����ֵ  ����
*********************************************************
*/
static int NF_EraseBlock(U32 block)
{
    U32 blockPage=(block<<5);
    int i;
/*
#if BAD_CHECK*//*����У��*/
/*    if(NF_IsBadBlock(block))
    	return 0;
#endif*/

    NF_nFCE_L();/*NF��CE��Ƭѡ������*/
    
    NF_CMD(0x60);   /* Erase one block 1st command*/

    NF_ADDR(blockPage&0xff);        /* Page number=0*/
    NF_ADDR((blockPage>>8)&0xff);   
    NF_ADDR((blockPage>>16)&0xff);

    NF_CMD(0xd0);   /* Erase one blcok 2nd command*/
    
    for(i=0;i<10;i++); /*wait tWB(100ns)/*??????*/

    NF_WAITRB();    /* Wait tBERS max 3ms.*/
    NF_CMD(0x70);   /* Read status command*/

    if (NF_RDDATA()&0x1) /* Erase error*/
    {   
        NF_nFCE_H();
    	printf("[ERASE_ERROR:block#=%d]\n",block);
    	/*NF_MarkBadBlock(block);*/
    	return 0;
    }
    else 
    {
        NF_nFCE_H();/*//NF��CE��Ƭѡ������*/
        return 1;
    }
}


/*
*********************************************************
* �������ܣ���������NAND FLASH K9F1208 ��������				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
/*
void K9F1208_Erase(void)
{
    int i;
    U32 blockIndex=0;

    printf("\n[ SMC(K9F1208V0M) NAND Flash Erase Program ]\n");
    printf("\nNow NAND Flash Erasing ....\n");    
*/
    /*NF_Init();*//*��ʼ��*/
/*
    rINTMSK = BIT_ALLMSK; */ /*close all intterrupt*/
/*
    for(blockIndex=0;blockIndex<4096;blockIndex++)
    {
        #if BAD_CHECK    */   /*������*/
     /*       if(NF_IsBadBlock(blockIndex))  */ /* 1:bad 0:good*/
  /*          {
                blockIndex++;  */ /* for next block*/
 /*               continue;
            }
        #endif
        
        if(!NF_EraseBlock(blockIndex))
        {
            blockIndex++;  */ /* for next block*/
  /*          continue;
        }       
    }
    printf("\nSMC(K9F1208V0M) NAND Flash Erase Completed !!!\n");    
}
*/

/*
*********************************************************
* �������ܣ��������ǵײ�дһҳ���ݵĳ���				
* ���������block--���
*           page--ҳ��
*           buffer--��д�����ݷŵĻ���ռ�
* �����������
* ����ֵ  ����
*********************************************************
*/
static int NF_WritePage(U32 block,U32 page,U8 *buffer)
{
    int i;
    U32 blockPage=(block<<5)+page;
    U8 *bufPt = "1234567890";

    NF_RSTECC();    /* Initialize ECC*/
    
    NF_nFCE_L(); 
    NF_CMD(0x0);
    NF_CMD(0x80);   /* Write 1st command*/
    NF_ADDR(0);             /* Column 0*/
    NF_ADDR(blockPage&0xff);        
    NF_ADDR((blockPage>>8)&0xff);   /* Block & page num.*/
    NF_ADDR((blockPage>>16)&0xff);  

    for(i=0;i<512;i++)
    {
    	NF_WRDATA(*bufPt++);    /* Write one page to NFM from buffer*/
    }  
    
    seBuf[0]=rNFECC0;
    seBuf[1]=rNFECC1;
    seBuf[2]=rNFECC2;
    seBuf[5]=0xff;      /* Marking good block*/
    
    for(i=0;i<16;i++)
    {
    	NF_WRDATA(seBuf[i]);    /* Write spare array(ECC and Mark)*/
    }  

    NF_CMD(0x10);   /* Write 2nd command*/
    
    for(i=0;i<10;i++);  /*tWB = 100ns. *??????*/

    NF_WAITRB();    /*wait tPROG 200~500us;*/
 
    NF_CMD(0x70);   /* Read status command   */
    
    for(i=0;i<3;i++);  /*twhr=60ns*/
    
    if (NF_RDDATA()&0x1) /* Page write error*/
    {   
        NF_nFCE_H();
    	printf("[PROGRAM_ERROR:block#=%d]\n",block);
   /* 	NF_MarkBadBlock(block);*/
    return 0;
    }
    
    else 
    {
        NF_nFCE_H();
    	#if (WRITEVERIFY==1)
    		/*return NF_VerifyPage(block,page,pPage);*/   
   		 #else
   		printf("NF_WritePage data is: %s\n",buffer);
    	return 1;
    	#endif
    }
}

/*
*********************************************************
* �������ܣ��������ǵײ��һҳ���ݵĳ���				
* ���������block--���
*           page--ҳ��
*           buffer--���������ݷ���Ļ���ռ�
* �����������
* ����ֵ  ����
*********************************************************
*/
static int NF_ReadPage(U32 block,U32 page,U8 *buffer)
{
    int i;
    unsigned int blockPage;
    U8 ecc0,ecc1,ecc2;
    U8 *bufPt = srcAddress;
    U8 se[16];     
    
    page=page&0x1f;
    blockPage=(block<<5)+page;
    NF_RSTECC();    /* Initialize ECC*/
    
    NF_nFCE_L();    
    NF_CMD(0x00);   /* Read command*/
    NF_ADDR(0);     /* Column = 0*/
    NF_ADDR(blockPage&0xff);        
    NF_ADDR((blockPage>>8)&0xff);   /* Block & Page num.*/
    NF_ADDR((blockPage>>16)&0xff);  

    for(i=0;i<10;i++); /*wait tWB(100ns)*/
    
    NF_WAITRB();    /* Wait tR(max 12us)*/
    for(i=0;i<512;i++)
    {
        *bufPt++=NF_RDDATA();   /* Read one page*/
    }
    ecc0=rNFECC0;
    ecc1=rNFECC1;
    ecc2=rNFECC2;
    for(i=0;i<16;i++)
    {
        se[i]=NF_RDDATA();  /* Read spare array*/
    }

    NF_nFCE_H();    

    if(ecc0==se[0] && ecc1==se[1] && ecc2==se[2])/*ECCУ��*/
    {
    	printf("[ECC OK:%x,%x,%x]\n",se[0],se[1],se[2]);
    	printf("NF_ReadPage data is: %s",buffer);
        return 1;
    }
    else
    {
    	printf("[ECC ERROR(RD):read:%x,%x,%x, reg:%x,%x,%x]\n",
        se[0],se[1],se[2],ecc0,ecc1,ecc2);
        return 0;
    }       
}

/*
*********************************************************
* �������ܣ���������ECC���Գ���				
* �����������
* �����������
* ����ֵ  ����
*********************************************************
*/
int TestECC(void)
{
    int i;
    U32 colECC=0,lowECC=0;
    U32 col=0, low=0;

    rNFCONF=(1<<15)|(1<<12);

    for(i=0;i<512;i++)
    NF_WRDATA(0x0); /* Write one page*/
    
    seBuf[0]=rNFECC0;
    seBuf[1]=rNFECC1;
    seBuf[2]=rNFECC2;

    printf("Old: ECC0=0x%x, ECC1=0x%x, ECC2=0x%x\n",seBuf[0],seBuf[1], seBuf[2]);

    rNFCONF=(1<<15)|(1<<12);

    for(i=0;i<200;i++)
    NF_WRDATA(0x0); 	/* Write 200 byte*/
    NF_WRDATA(0x20);    /* Write one btte(col: 5th, line: 200th)*/
    for(i=0;i<311;i++)
    NF_WRDATA(0x0); 	/* Write 311 byte*/

    seBuf[3]=rNFECC0;
    seBuf[4]=rNFECC1;
    seBuf[5]=rNFECC2;

    printf("New: ECC0=0x%x, ECC1=0x%x, ECC2=0x%x\n",seBuf[3],seBuf[4],seBuf[5]);

    seBuf[6]=seBuf[0]^seBuf[3];
    seBuf[7]=seBuf[1]^seBuf[4];
    seBuf[8]=seBuf[2]^seBuf[5];
    
    printf("XOR: ECC0=0x%x, ECC1=0x%x, ECC2=0x%x\n",seBuf[6],seBuf[7],seBuf[8]);

    colECC=seBuf[8]>>2;
    lowECC=((seBuf[8]&0x3)<<16)|(seBuf[7]<<8)|(seBuf[6]<<0);
    printf("Low ECC=0x%x, Col ECC=0x%x\n", lowECC, colECC);

    /* Column parity*/
    for(i=0;i<3;i++)
    col |= (Check10(colECC, i) <<i);

    printf("col=%dth\n",col); 

    /* Line parity*/
    for(i=0;i<9;i++)
    low |= (Check10(lowECC, i) <<i);
    printf("low=%dth\n",low); 
}
