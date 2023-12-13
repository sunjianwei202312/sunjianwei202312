/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               fsmc_nand.c
** Descriptions:            The FSMC Nand application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2011-12-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "fsmc_nand.h"
#include "bsp_nand_flash.h"
/* Private define ------------------------------------------------------------*/
#define NAND_FLASH_START_ADDR     ((uint32_t)0x70000000) 

#define ROW_ADDRESS (Address.Page + (Address.Block + (Address.Zone * NAND_ZONE_SIZE)) * NAND_BLOCK_SIZE)

/* Private variables ---------------------------------------------------------*/
//static uint8_t TxBuffer [NAND_PAGE_SIZE];
//static uint8_t RxBuffer [NAND_PAGE_SIZE];
extern uint8_t FSMC_NAND_WritePage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount);
extern uint8_t FSMC_NAND_ReadPage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount);




/******************************************************************************
* Function Name  : FSMC_NAND_WriteSmallPage
* Description    : This routine is for writing one or several 512 Bytes Page size.
* Input          : - pBuffer: pointer on the Buffer containing data to be written   
*                  - Address: First page address
*                  - NumPageToWrite: Number of page to write  
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate 
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation 
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
* Attention		 : None
*******************************************************************************/
uint32_t FSMC_NAND_WriteSmallPage(uint8_t *pBuffer, NAND_ADDRESS_T Address, uint32_t NumPageToWrite)
{
  uint32_t index = 0x00, numpagewritten = 0x00, addressstatus = NAND_VALID_ADDRESS_T;
  uint32_t status = NAND_READY, size = 0x00;
	
  while((NumPageToWrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
  {
		 /*!< Page write command and address */
    *(__IO uint8_t *)(NAND_FLASH_START_ADDR| CMD_AREA) = NAND_CMD_READ_A ;//NAND_CMD_AREA_A;
    *(__IO uint8_t *)(NAND_FLASH_START_ADDR | CMD_AREA) =NAND_CMD_PAGEPROGRAM  ;// NAND_CMD_WRITE0;
    *(__IO uint8_t *)(NAND_FLASH_START_ADDR | ADDR_AREA) = 0x00;
    *(__IO uint8_t *)(NAND_FLASH_START_ADDR | ADDR_AREA) = 0x00;//添加此句
    *(__IO uint8_t *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
    *(__IO uint8_t *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
//    *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);//原版有此句	
    /* Calculate the size */
    size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpagewritten);//统计写入数目



/*!< Write data */
    for(; index < size; index++)
    {
      *(__IO uint8_t *)(NAND_FLASH_START_ADDR | DATA_AREA) = pBuffer[index];
    }
    
    *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_PAGEPROGRAM_TRUE;
		
		
		
    /* 读忙脚 */
    while( GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0 );
    
    /* Check status for successful operation */
    status = FSMC_NAND_GetStatus();
    
    if(status == NAND_READY)
    {
      numpagewritten++;

      NumPageToWrite--;

      /* Calculate Next small page Address */
      addressstatus = FSMC_NAND_AddressIncrement(&Address);    
    }    
  }
  
  return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_ReadSmallPage
* Description    : This routine is for sequential read from one or several 
*                  512 Bytes Page size.
* Input          : - pBuffer: pointer on the Buffer to fill  
*                  - Address: First page address
*                  - NumPageToRead: Number of page to read
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate 
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation 
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
* Attention		 : None
*******************************************************************************/
uint32_t FSMC_NAND_ReadSmallPage(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead)
{
  uint32_t index = 0x00, numpageread = 0x00, addressstatus = NAND_VALID_ADDRESS;
  uint32_t status = NAND_READY, size = 0x00;
	
	
	
  while((NumPageToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
  {	   
		/* 页读命令和页地址*/
    /* Page Read command and page address */
    *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_READ_1;             //发送命令00H到命令区0x70010000
   
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = 0x00;                       //发送地址A0~A7（00H）到地址区0x70020000
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);//发送地址A9~A16到地址区0x70020000  
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);//发送地址A17~A24到地址区0x70020000
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);//发送地址A25到地址区0x70020000

    *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_READ_TRUE; 
   
    /* 读忙脚 */
    while( GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0 );
    
    /* Calculate the size */
    size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpageread);
    
	for(index=0; index < 0x690; index++);//延时

    /* Get Data into Buffer */    
    for(index=0; index < size; index++)
    {
      pBuffer[index]= *(vu8 *)(NAND_FLASH_START_ADDR | DATA_AREA);
    }

    numpageread++;
    
    NumPageToRead--;

    /* Calculate page address */           			 
    addressstatus = FSMC_NAND_AddressIncrement(&Address);
  }

  status = FSMC_NAND_GetStatus();
  
  return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_WriteSpareArea
* Description    : This routine write the spare area information for the specified 
*                  pages addresses.
* Input          : - pBuffer: pointer on the Buffer containing data to be written 
*                  - Address: First page address
*                  - NumSpareAreaTowrite: Number of Spare Area to write
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate 
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation 
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
* Attention		 : None
*******************************************************************************/
uint32_t FSMC_NAND_WriteSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite)
{
  uint32_t index = 0x00, numsparesreawritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
  uint32_t status = NAND_READY, size = 0x00; 

  while((NumSpareAreaTowrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
  {
    /* Page write Spare area command and address */
    *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_PAGEPROGRAM;

    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = 0x00; 
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = 0x08; 
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);  
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);   

    /* Calculate the size */ 
    size = NAND_SPARE_AREA_SIZE + (NAND_SPARE_AREA_SIZE * numsparesreawritten);

    /* Write the data */ 
    for(; index < size; index++)
    {
      *(vu8 *)(NAND_FLASH_START_ADDR | DATA_AREA) = pBuffer[index];
    }
    
    *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_PAGEPROGRAM_TRUE;

    /* 读忙脚 */
    while( GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_6) == 0 );

    /* Check status for successful operation */
    status = FSMC_NAND_GetStatus();

    if(status == NAND_READY)
    {
      numsparesreawritten++;      

      NumSpareAreaTowrite--;  
    
      /* Calculate Next page Address */
      addressstatus = FSMC_NAND_AddressIncrement(&Address);
    }       
  }
  
  return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_ReadSpareArea
* Description    : This routine read the spare area information from the specified
*                  pages addresses.
* Input          : - pBuffer: pointer on the Buffer to fill  
*                  - Address: First page address
*                  - NumSpareAreaToRead: Number of Spare Area to read
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate 
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation 
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
* Attention		 : None
*******************************************************************************/
uint32_t FSMC_NAND_ReadSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead)
{
  uint32_t numsparearearead = 0x00, index = 0x00, addressstatus = NAND_VALID_ADDRESS;
  uint32_t status = NAND_READY, size = 0x00;

  while((NumSpareAreaToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
  {     
    /* Page Read command and page address */     
    *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_READ_1;

    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = 0x00; 
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = 0x08;     
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);  
    *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);    

    *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_READ_TRUE;

    /* 读忙脚 */
    while( GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_6) == 0 );
    
    /* Data Read */
    size = NAND_SPARE_AREA_SIZE +  (NAND_SPARE_AREA_SIZE * numsparearearead);
	
    /* Get Data into Buffer */
    for ( ;index < size; index++)
    {
      pBuffer[index] = *(vu8 *)(NAND_FLASH_START_ADDR | DATA_AREA);
    }
    
    numsparearearead++;
    
    NumSpareAreaToRead--;

    /* Calculate page address */           			 
    addressstatus = FSMC_NAND_AddressIncrement(&Address);
  }

  status = FSMC_NAND_GetStatus();

  return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_EraseBlock
* Description    : This routine erase complete block from NAND FLASH
* Input          : - Address: Any address into block to be erased
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate 
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation 
* Attention		 : None
*******************************************************************************/
/*uint32_t FSMC_NAND_EraseBlock(NAND_ADDRESS Address)
{
  *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_ERASE0;
  
  *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);  
  *(vu8 *)(NAND_FLASH_START_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);  
		
  *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_ERASE1; 

  
  //while( GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_6) == 0 );
  
  return (FSMC_NAND_GetStatus());
}
*/

/******************************************************************************
* Function Name  : FSMC_NAND_Reset
* Description    : This routine reset the NAND FLASH
* Input          : None
* Output         : None
* Return         : NAND_READY
* Attention		 : None
*******************************************************************************/
/*uint32_t FSMC_NAND_Reset(void)
{
  *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_RESET;

  return (NAND_READY);
}
*/

/******************************************************************************
* Function Name  : FSMC_NAND_GetStatus
* Description    : Get the NAND operation status
* Input          : None
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate 
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation  
* Attention		 : None  
*******************************************************************************/
/*uint32_t FSMC_NAND_GetStatus(void)
{
  uint32_t timeout = 0x1000000, status = NAND_READY;

  status = FSMC_NAND_ReadStatus(); 

  // Wait for a NAND operation to complete or a TIMEOUT to occur 
  while ((status != NAND_READY) &&( timeout != 0x00))
  {
     status = FSMC_NAND_ReadStatus();
     timeout --;      
  }

  if(timeout == 0x00)
  {          
    status =  NAND_TIMEOUT_ERROR;      
  } 

  // Return the operation status 
  return (status);      
}

*/
/******************************************************************************
* Function Name  : FSMC_NAND_ReadStatus
* Description    : Reads the NAND memory status using the Read status command 
* Input          : None
* Output         : None
* Return         : The status of the NAND memory. This parameter can be:
*                   - NAND_BUSY: when memory is busy
*                   - NAND_READY: when memory is ready for the next operation    
*                   - NAND_ERROR: when the previous operation gererates error  
* Attention		 : None 
*******************************************************************************/
/*uint32_t FSMC_NAND_ReadStatus(void)
{
  uint32_t data = 0x00, status = NAND_BUSY;

  // Read status operation ------------------------------------ 
  *(vu8 *)(NAND_FLASH_START_ADDR | CMD_AREA) = NAND_CMD_STATUS;
  data = *(vu8 *)(NAND_FLASH_START_ADDR);

  if((data & NAND_ERROR) == NAND_ERROR)
  {
    status = NAND_ERROR;
  } 
  else if((data & NAND_READY) == NAND_READY)
  {
    status = NAND_READY;
  }
  else
  {
    status = NAND_BUSY; 
  }
  
  return (status);
}

*/
/******************************************************************************
* Function Name  : NAND_AddressIncrement
* Description    : Increment the NAND memory address
* Input          : - Address: address to be incremented.
* Output         : None
* Return         : The new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
* Attention		 : None
*******************************************************************************/
uint32_t FSMC_NAND_AddressIncrement(NAND_ADDRESS* Address)
{
  uint32_t status = NAND_VALID_ADDRESS;
 
  Address->Page++;

  if(Address->Page == NAND_BLOCK_SIZE)
  {
    Address->Page = 0;
    Address->Block++;
    
    if(Address->Block == NAND_ZONE_SIZE)
    {
      Address->Block = 0;
      Address->Zone++;

      if(Address->Zone == NAND_MAX_ZONE)
      {
        status = NAND_INVALID_ADDRESS;
      }
    }
  } 
  
  return (status);
}



/******************************************************************************
* Function Name  : FSMC_NAND_Test
* Description    : NAND test
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void FSMC_NAND_Test(void)
{
  uint16_t index;
  uint16_t j;
  static NAND_IDTypeDef NAND_ID;
  static NAND_ADDRESS WriteReadAddr;//"static"is added by sjw for see...
static uint32_t  ID;
	extern uint32_t NAND_ReadID(void);

	
	
  FSMC_NANDDeInit(FSMC_Bank2_NAND);
  FSMC_NAND_Init();

	
	
	// /* 读NAND ID操作 */
	ID = NAND_ReadID();
  /* 检测NAND Flash */
	// /* 读NAND ID操作 */
  //FSMC_NAND_ReadID(&NAND_ID);
	NAND_ID.Maker_ID =(ID&0xff000000)>>24;
	NAND_ID.Device_ID =(ID&0x00ff0000)>>16;
	NAND_ID.Third_ID=(ID&0x0000ff00)>>8;
	NAND_ID.Fourth_ID =(ID&0x000000ff);
	
		printf("Nand Flash ID = %02X,%02X,%02X,%02X  ",NAND_ID.Maker_ID, NAND_ID.Device_ID,NAND_ID.Third_ID, NAND_ID.Fourth_ID );
  
	if ((NAND_ID.Maker_ID == 0xEC) && (NAND_ID.Device_ID == 0xF1)&& (NAND_ID.Third_ID == 0x80) && (NAND_ID.Fourth_ID == 0x15))
  {
		printf("Type = K9F1G08U0A\r\n");
  }
  else if ((NAND_ID.Maker_ID == 0xEC) && (NAND_ID.Device_ID == 0xF1)&& (NAND_ID.Third_ID == 0x00) && (NAND_ID.Fourth_ID == 0x95))
  {
		printf("Type = K9F1G08U0B\r\n");		
  }
  else if ((NAND_ID.Maker_ID == 0xAD) && (NAND_ID.Device_ID == 0xF1)&& (NAND_ID.Third_ID == 0x80) && (NAND_ID.Fourth_ID == 0x1D))
  {
		printf("Type = HY27UF081G2A\r\n");		
  }
  else
  {
	 printf("Type = Unknow\r\n");
  }

	 /* 检查ID是否正确 */
	//if((NAND_ID.Maker_ID == NAND_K9F1208_MakerID) && (NAND_ID.Device_ID == NAND_K9F1208_DeviceID))
	
	
  /* NAND memory address to write to */
  /* 初始化要写入NAND的页地址 */ 
  WriteReadAddr.Zone = 0x00;
  WriteReadAddr.Block = 1000;
  WriteReadAddr.Page = 0x00;


  /* Erase the NAND first Block */
	/* 擦除NAND FLASH的第一个块（第1和第2页所在的块） */
  FSMC_NAND_EraseBlock(WriteReadAddr);

	
	 /* 写数据到NAND FLASH的第1和第2页 */
    /* 填充要发送的数据到buffer */
  /* Write data to FSMC NOR memory */
  /* Fill the buffer to send */
  for (index = 0; index < NAND_PAGE_SIZE; index++ )
  {
     TxBuffer[index] = index;
  }

	FSMC_NAND_WritePage(TxBuffer,1000,0, 2048);	
  //FSMC_NAND_WriteSmallPage(TxBuffer, WriteReadAddr, 1);//表示要写入第x页
//   printf("\r\nWritten to the number of： \r\n");
//   for(j = 0; j < 128; j++)
	printf("%x  \r",TxBuffer[j]);

	
	
	
  /* Read back the written data */
  FSMC_NAND_ReadSmallPage (RxBuffer, WriteReadAddr, 1);
//     printf("\r\nRead several： \r\n");
//    for(j = 0; j < 128; j++)
	printf("%x  \r",RxBuffer[j]);   


}


void	 FSMC_NAND_TestRead(void)
{

		//FSMC_NAND_ReadPage(RxBuffer,0,0, 2048);
		FSMC_NAND_CompPage(RxBuffer,0,0, 2048);

}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
