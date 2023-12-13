//https://wenku.baidu.com/view/a8f7904faa8271fe910ef12d2af90242a995ab74.html
//flashEcc算法

//https://wenku.baidu.com/view/f0f73410084c2e3f5727a5e9856a561253d3215f.html

//深入浅出NandFlash里的ECC校验算法原理与实现(2)
//https://blog.csdn.net/qwe5959798/article/details/121931611



/*****************************************************************************/
/*                                                                           */
/* PROJECT : SAMSUNG ECC for 256byte                                         */
/* FILE    : SAMSUNG_ECC.c                                                   */
/* PURPOSE : This file implements core ECC algorithms adopted				 */
/*           Hamming Error Correction and Detection Algorithm                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        COPYRIGHT 2000-2004, SAMSUNG ELECTRONICS CO., LTD.                 */
/*                      ALL RIGHTS RESERVED                                  */
/*                                                                           */
/*   Permission is hereby granted to licensees of Samsung Electronics        */
/*   Co., Ltd. products to use or abstract this computer program for the     */
/*   sole purpose of implementing a product based on Samsung                 */
/*   Electronics Co., Ltd. products. No other rights to reproduce, use,      */
/*   or disseminate this computer program, whether in part or in whole,      */
/*   are granted.                                                            */
/*                                                                           */
/*   Samsung Electronics Co., Ltd. makes no representation or warranties     */
/*   with respect to the performance of this computer program, and           */
/*   specifically disclaims any responsibility for any damages,              */
/*   special or consequential, connected with the use of this program.       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* REVISION HISTORY                                                          */
/*                                                                           */
/*  13-NOV-2003 [Chang JongBaek] : 	first writing                            */
/*  03-MAR-2004 [ Kim YoungGon ] :  Second writing                           */
/*  03-MAR-2004 [  Lee JaeBum  ] :  Third writing                            */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* NOTES                                                                     */
/*                                                                           */
/* - Make ECC parity code of 256bytes is represented                         */
/*   And ECC compare & Correction code is also represented                   */
/*                                                                           */
/*****************************************************************************/



//#include <stdio.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <sys/timeb.h>
//#include <string.h>

///*****************************************************************************/
///* Address Types                                                             */
///*****************************************************************************/

//typedef unsigned char *		address_t;			/* address (pointer) */
//typedef unsigned long		address_value_t;	/* address (for calculation) */

//typedef unsigned long		ULONG;	/* address (for calculation) */

//typedef unsigned int        uint;
//typedef unsigned char       uchar;


///*****************************************************************************/
///* Integer Types                                                             */
///*****************************************************************************/

//typedef unsigned int		uint32_t;			/* unsigned 4 byte integer */
//typedef signed int			int32_t;			/* signed 4 byte integer */
//typedef unsigned short		uint16_t;			/* unsigned 2 byte integer */
//typedef signed short		int16_t;			/* signed 2 byte integer */
//typedef unsigned char		uint8_t;			/* unsigned 1 byte integer */
//typedef signed char			int8_t;				/* signed 1 byte integer */
//typedef unsigned int		UINT32;			/* unsigned 4 byte integer */
//typedef unsigned char		UINT8;			/* unsigned 1 byte integer */
//typedef signed int			INT32;			/* signed 4 byte integer */

//typedef unsigned int		UINT;			/* unsigned 4 byte integer */
//typedef signed int		    INT;			/* signed   4 byte integer */
//typedef unsigned short		USHORT;			/* unsigned 2 byte integer */
//typedef signed short		SHORT;			/* signed   2 byte integer */
//typedef unsigned char		UCHAR;			/* unsigned 1 byte integer */
//typedef signed char		    CHAR;			/* signed   1 byte integer */


#include <stdint.h>
#include "includes.h"

uint8_t  EccOldWriteData[256],EccNewReadData[256];
uint8_t  EccOldWriteGen[3],EccNewReadGen[3];
uint8_t  *pPagedata,pOffset,pCorrected;


typedef enum {
	ECC_NO_ERROR			= 0,		/* no error */
	ECC_CORRECTABLE_ERROR	= 1,		/* one bit data error */
	ECC_ECC_ERROR			= 2,		/* one bit ECC error */
	ECC_UNCORRECTABLE_ERROR	= 3			/* uncorrectable error */
} eccdiff_t;

void	    make_ecc_256(unsigned char*, unsigned char*);
eccdiff_t	compare_ecc(unsigned char*, unsigned char*, unsigned char*, int, unsigned char);

/*****************************************************************************/
/*                                                                           */
/* NAME                                                                      */
/*		make_ecc_256                                                         */
/* DESCRIPTION                                                               */
/*		This function generates 3 byte ECC for 256 byte data.                */
/*      (Software ECC)                                                       */
/* PARAMETERS                                                                */
/*		ecc_buf			the location where ECC should be stored              */
/*		data_buf		given data                                           */
/* RETURN VALUES                                                             */
/*		none                                                                 */
/*                                                                           */
/*****************************************************************************/
void make_ecc_256(unsigned char* ecc_buf, unsigned char* data_buf)
{
	
    unsigned int	i;
	unsigned int	tmp;
	unsigned int	uiparity = 0;
	unsigned int	parityCol, ecc = 0;
	unsigned int	parityCol4321 = 0, parityCol4343 = 0, parityCol4242 = 0, parityColTot = 0;
	unsigned int*	Data = (unsigned int*)(data_buf);
	unsigned int	Xorbit=0;

	for( i = 0; i < 8; i++)
	{
		parityCol = *Data++; 
		tmp = *Data++; 		parityCol ^= tmp; parityCol4242 ^= tmp;
		tmp = *Data++; 		parityCol ^= tmp; parityCol4343 ^= tmp;
		tmp = *Data++; 		parityCol ^= tmp; parityCol4343 ^= tmp; parityCol4242 ^= tmp;
		tmp = *Data++; 		parityCol ^= tmp; parityCol4321 ^= tmp;
		tmp = *Data++; 		parityCol ^= tmp; parityCol4242 ^= tmp; parityCol4321 ^= tmp;
		tmp = *Data++; 		parityCol ^= tmp; parityCol4343 ^= tmp; parityCol4321 ^= tmp;
		tmp = *Data++; 		parityCol ^= tmp; parityCol4242 ^= tmp; parityCol4343 ^= tmp; parityCol4321 ^= tmp;

		parityColTot ^= parityCol;

		tmp = (parityCol >> 16) ^ parityCol;
		tmp = (tmp >> 8) ^ tmp;
		tmp = (tmp >> 4) ^ tmp;
		tmp = ((tmp >> 2) ^ tmp) & 0x03;
		if ((tmp == 0x01) || (tmp == 0x02))
		{
			uiparity ^= i;
			Xorbit ^= 0x01;
		}
	}

	tmp = (parityCol4321 >> 16) ^ parityCol4321;
	tmp = (tmp << 8) ^ tmp;
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp >> 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x200;	// p128

	tmp = (parityCol4343 >> 16) ^ parityCol4343;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 4) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x80;	// p64

	tmp = (parityCol4242 >> 16) ^ parityCol4242;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 4) ^ tmp;
	tmp = (tmp >> 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x20;	// p32

	tmp = parityColTot & 0xFFFF0000;
	tmp = tmp >> 16;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x08;	// p16

	tmp = parityColTot & 0xFF00FF00;
	tmp = (tmp >> 16) ^ tmp;
	tmp = (tmp >> 8);
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp >> 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x02;	// p8

	tmp = parityColTot & 0xF0F0F0F0 ;
	tmp = (tmp << 16) ^ tmp;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x800000;	// p4

	tmp = parityColTot & 0xCCCCCCCC ;
	tmp = (tmp << 16) ^ tmp;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 4) ^ tmp;
	tmp = (tmp >> 2);
	ecc |= ((tmp << 1) ^ tmp) & 0x200000;	// p2

	tmp = parityColTot & 0xAAAAAAAA ;
	tmp = (tmp << 16) ^ tmp;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= (tmp & 0x80000);	// p1

	ecc |= (uiparity & 0x01) <<11;	// parit256_1
	ecc |= (uiparity & 0x02) <<12;	// parit512_1
	ecc |= (uiparity & 0x04) <<13;	// parit1024_1

	if (Xorbit)
	{
		ecc |= (ecc ^ 0x00A8AAAA)>>1;
	}
	else
	{
		ecc |= (ecc >> 1);
	}

	ecc = ~ecc;
	*(ecc_buf + 2) = (unsigned char) (ecc >> 16);
	*(ecc_buf + 1) = (unsigned char) (ecc >> 8);
	*(ecc_buf + 0) = (unsigned char) (ecc);
}


/*****************************************************************************/
/*                                                                           */
/* NAME                                                                      */
/*		compare_ecc_256                                                      */
/* DESCRIPTION                                                               */
/*		This function compares two ECCs and indicates if there is an error.  */
/* PARAMETERS                                                                */
/*		ecc_data1		one ECC to be compared                               */
/*		ecc_data2		the other ECC to be compared                         */
/*		page_data		content of data page                                 */
/*		offset			where the error occurred                             */
/*		corrected		correct data                                         */
/* RETURN VALUES                                                             */
/*		Upon successful completion, compare_ecc returns SSR_SUCCESS.         */
/*      Otherwise, corresponding error code is returned.                     */
/*                                                                           */
/*****************************************************************************/
eccdiff_t compare_ecc_256(uint8_t *iEccdata1, uint8_t *iEccdata2, 
          uint8_t *pPagedata, int32_t pOffset, uint8_t pCorrected)
{
	
	
	  uint32_t  iCompecc = 0, iEccsum = 0;
    uint32_t  iFindbyte   = 0;
    uint32_t  iIndex;
    uint32_t  nT1 = 0, nT2 =0;
	  uint8_t   iNewvalue;
    uint8_t   iFindbit    = 0;

    uint8_t   *pEcc1 = (uint8_t *)iEccdata1;
    uint8_t   *pEcc2 = (uint8_t *)iEccdata2;

	  for ( iIndex = 0; iIndex <2; iIndex++)
    {
        nT1 ^= (((*pEcc1) >> iIndex) & 0x01);
        nT2 ^= (((*pEcc2) >> iIndex) & 0x01);
    }

    for (iIndex = 0; iIndex < 3; iIndex++)
        iCompecc |= ((~(*pEcc1++) ^ ~(*pEcc2++)) << iIndex * 8);
    
    for(iIndex = 0; iIndex < 24; iIndex++) {
        iEccsum += ((iCompecc >> iIndex) & 0x01);
    }
    
    switch (iEccsum) {
    case 0 :
				printf("\r\n  RESULT : no error\n");
        return ECC_NO_ERROR;

	  case 1 :
				printf("RESULT : ECC 1 bit error\n");
				return ECC_ECC_ERROR;

    case 11 :
        if (nT1 != nT2)
        {
            iFindbyte = (  ((iCompecc >> 15 & 1) << 7) + ((iCompecc >> 13 & 1) << 6)
                      + ((iCompecc >> 11 & 1) << 5) + ((iCompecc >> 9 & 1) << 4) + ((iCompecc >> 7 & 1) << 3)
                      + ((iCompecc >> 5 & 1) << 2) + ((iCompecc >> 3 & 1) << 1) + (iCompecc >> 1 & 1) );
            iFindbit =  (uint8_t)(((iCompecc >> 23 & 1) << 2) + ((iCompecc >> 21 & 1) << 1) + (iCompecc >> 19 & 1));
            iNewvalue = (uint8_t)(pPagedata[iFindbyte] ^ (1 << iFindbit));
   	        printf("iCompecc = %d\n",iCompecc);
            printf("RESULT : one bit error\r\n");
            printf("byte = %d, bit = %d\r\n", iFindbyte, iFindbit);
            printf("corrupted = %x, corrected = %x\r\n", pPagedata[iFindbyte], iNewvalue);
            if (pOffset != NULL) {
                pOffset = iFindbyte;
            }
            if (pCorrected != NULL) {
                pCorrected = iNewvalue;
            }
            
            return ECC_CORRECTABLE_ERROR;
        }
        else
            return ECC_UNCORRECTABLE_ERROR;

    default :
					printf("RESULT : unrecoverable error\n");
					return ECC_UNCORRECTABLE_ERROR;
    }   
}


void  SumsungTestEcc(uint8_t offset,uint8_t bit,uint8_t ifchange)
{
	
	uint16_t i;
	uint8_t temp1,temp2,temp3;
	
	
	
	
	
	for(i=0;i<256;i++)
		 EccOldWriteData[i]=i;	
	make_ecc_256(EccOldWriteGen, EccOldWriteData);
	
	
	
	for(i=0;i<256;i++)	 
	   EccNewReadData[i]=i;	
	
	
	if(ifchange!=0){		
				temp1=EccNewReadData[offset];
				
		    temp2=(temp1>>bit);	
		    temp2 &= 0x01;
				switch(bit)//代表第bit个位变化，或者由1->0 或者 由0>1
				{
					case 0:
						if(temp2==0)
							EccNewReadData[offset] |=  0x01;
						else
							EccNewReadData[offset] &= ~(0x01);			
					break;
					
					case 1:
						if(temp2==0)
							EccNewReadData[offset] |=  (0x02);	
						else
							EccNewReadData[offset] &= ~(0x02);				
					break;
					
					case 2:
						if(temp2==0)
							EccNewReadData[offset] |=  (0x04);	
						else
							EccNewReadData[offset] &= ~(0x04);
					break;
					
					case 3:
						if(temp2==0)		
							EccNewReadData[offset] |=  (0x08);	
						else
							EccNewReadData[offset] &= ~(0x08);
					 
						
					break;
					
					case 4:
						if(temp2==0)
							EccNewReadData[offset] |=  (0x10);	
						else
							EccNewReadData[offset] &= ~(0x10);
					 
					break;
					
					case 5:
						if(temp2==0)
							EccNewReadData[offset] |=  (0x20);	
							
						else
							EccNewReadData[offset] &= ~(0x20);
						
						
					break;
					
					case 6:
						if(temp2==0)
							EccNewReadData[offset] |=  (0x40);	
							
						else
							EccNewReadData[offset] &= ~(0x40);
						
								
							
					break;
					
					case 7:
						if(temp2==0)
							EccNewReadData[offset] |=  (0x80);	
						
						else
							EccNewReadData[offset] &= ~(0x80);	
					
						
					break;	
				}
	}
	make_ecc_256(EccNewReadGen, EccNewReadData);
	
	
	
	compare_ecc_256(EccOldWriteGen,EccNewReadGen,pPagedata,pOffset,pCorrected);
	

	


}
	

