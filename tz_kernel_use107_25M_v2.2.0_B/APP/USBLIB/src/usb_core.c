/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_core.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Standard protocol processing (USB v2.0)
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_hw.h"//below 4 rows added by sjw
#include <stdio.h>
#include <string.h>
#include <stdlib.h>





/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ValBit(VAR,Place)    (VAR & (1 << Place))
#define SetBit(VAR,Place)    (VAR |= (1 << Place))
#define ClrBit(VAR,Place)    (VAR &= ((1 << Place) ^ 255))

#define Send0LengthData() { _SetEPTxCount(ENDP0, 0); \
    vSetEPTxStatus(EP_TX_VALID); \
  }

#define vSetEPRxStatus(st) (SaveRState = st)
#define vSetEPTxStatus(st) (SaveTState = st)

#define USB_StatusIn() Send0LengthData()
#define USB_StatusOut() vSetEPRxStatus(EP_RX_VALID)

#define StatusInfo0 StatusInfo.bw.bb1 /* Reverse bb0 & bb1 */
#define StatusInfo1 StatusInfo.bw.bb0

u8 CoreTest[32];
u8 *pCoreTest=CoreTest;

void (*sjw)(u8 );

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u16_u8 StatusInfo;
bool Data_Mul_MaxPacketSize = FALSE;
/* Private function prototypes -----------------------------------------------*/
static void DataStageOut(void);
static void DataStageIn(void);
static void NoData_Setup0(void);
static void Data_Setup0(void);

u8 USB_Test_Value;


/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Standard_GetConfiguration.
* Description    : Return the current configuration variable address.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 1 , if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*******************************************************************************/
u8 *Standard_GetConfiguration(u16 Length)
{
  //sjw=SetDeviceAddress;added by sjw for test "function pointer"
	if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength =
      sizeof(pInformation->Current_Configuration);
    return 0;
  }
  pUser_Standard_Requests->User_GetConfiguration();
  return (u8 *)&pInformation->Current_Configuration;
}

/*******************************************************************************
* Function Name  : Standard_SetConfiguration.
* Description    : This routine is called to set the configuration value
*                  Then each class should configure device themself.
* Input          : None.
* Output         : None.
* Return         : Return USB_SUCCESS, if the request is performed.
*                  Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetConfiguration(void)
{

  if ((pInformation->USBwValue0 <=
      Device_Table.Total_Configuration) && (pInformation->USBwValue1 == 0)
      && (pInformation->USBwIndex == 0)) /*call Back usb spec 2.0*/
  {
    pInformation->Current_Configuration = pInformation->USBwValue0;
    pUser_Standard_Requests->User_SetConfiguration();
    return USB_SUCCESS;
  }
  else
  {
    return USB_UNSUPPORT;
  }
}

/*******************************************************************************
* Function Name  : Standard_GetInterface.
* Description    : Return the Alternate Setting of the current interface.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*******************************************************************************/
u8 *Standard_GetInterface(u16 Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength =
      sizeof(pInformation->Current_AlternateSetting);
    return 0;
  }
  pUser_Standard_Requests->User_GetInterface();
  return (u8 *)&pInformation->Current_AlternateSetting;
}

/*******************************************************************************
* Function Name  : Standard_SetInterface.
* Description    : This routine is called to set the interface.
*                  Then each class should configure the interface them self.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetInterface(void)
{
  RESULT Re;
  /*Test if the specified Interface and Alternate Setting are supported by
    the application Firmware*/
  Re = (*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, pInformation->USBwValue0);

  if (pInformation->Current_Configuration != 0)
  {
    if ((Re != USB_SUCCESS) || (pInformation->USBwIndex1 != 0)
        || (pInformation->USBwValue1 != 0))
    {
      return  USB_UNSUPPORT;
    }
    else if (Re == USB_SUCCESS)
    {
      pUser_Standard_Requests->User_SetInterface();
      pInformation->Current_Interface = pInformation->USBwIndex0;
      pInformation->Current_AlternateSetting = pInformation->USBwValue0;
      return USB_SUCCESS;
    }

  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Standard_GetStatus.
* Description    : Copy the device request data to "StatusInfo buffer".
* Input          : - Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is at end of data block,
*                  or is invalid when "Length" is 0.
*******************************************************************************/
u8 *Standard_GetStatus(u16 Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 2;
    return 0;
  }

  StatusInfo.w = 0;
  /* Reset Status Information */

  if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {
    /*Get Device Status */
    u8 Feature = pInformation->Current_Feature;

    /* Remote Wakeup enabled */
    if (ValBit(Feature, 5))
    {
      SetBit(StatusInfo0, 1);
    }

    /* Bus-powered */
    if (ValBit(Feature, 6))
    {
      ClrBit(StatusInfo0, 0);
    }
    else /* Self-powered */
    {
      SetBit(StatusInfo0, 0);
    }
  }
  /*Interface Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    return (u8 *)&StatusInfo;
  }
  /*Get EndPoint Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {
    u8 Related_Endpoint;
    u8 wIndex0 = pInformation->USBwIndex0;

    Related_Endpoint = (wIndex0 & 0x0f);
    if (ValBit(wIndex0, 7))
    {
      /* IN endpoint */
      if (_GetTxStallStatus(Related_Endpoint))
      {
        SetBit(StatusInfo0, 0); /* IN Endpoint stalled */
      }
    }
    else
    {
      /* OUT endpoint */
      if (_GetRxStallStatus(Related_Endpoint))
      {
        SetBit(StatusInfo0, 0); /* OUT Endpoint stalled */
      }
    }

  }
  else
  {
    return NULL;
  }
  pUser_Standard_Requests->User_GetStatus();
  return (u8 *)&StatusInfo;
}

/*******************************************************************************
* Function Name  : Standard_ClearFeature.
* Description    : Clear or disable a specific feature.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_ClearFeature(void)
{
  u32     Type_Rec = Type_Recipient;
  u32     Status;


  if (Type_Rec == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {/*Device Clear Feature*/
    ClrBit(pInformation->Current_Feature, 5);
    return USB_SUCCESS;
  }
  else if (Type_Rec == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {/*EndPoint Clear Feature*/
    DEVICE* pDev;
    u32 Related_Endpoint;
    u32 wIndex0;
    u32 rEP;

    if ((pInformation->USBwValue != ENDPOINT_STALL)
        || (pInformation->USBwIndex1 != 0))
    {
      return USB_UNSUPPORT;
    }

    pDev = &Device_Table;
    wIndex0 = pInformation->USBwIndex0;
    rEP = wIndex0 & ~0x80;
    Related_Endpoint = ENDP0 + rEP;

    if (ValBit(pInformation->USBwIndex0, 7))
    {
      /*Get Status of endpoint & stall the request if the related_ENdpoint
      is Disabled*/
      Status = _GetEPTxStatus(Related_Endpoint);
    }
    else
    {
      Status = _GetEPRxStatus(Related_Endpoint);
    }

    if ((rEP >= pDev->Total_Endpoint) || (Status == 0)
        || (pInformation->Current_Configuration == 0))
    {
      return USB_UNSUPPORT;
    }


    if (wIndex0 & 0x80)
    {
      /* IN endpoint */
      if (_GetTxStallStatus(Related_Endpoint ))
      {
        ClearDTOG_TX(Related_Endpoint);
        SetEPTxStatus(Related_Endpoint, EP_TX_VALID);
      }
    }
    else
    {
      /* OUT endpoint */
      if (_GetRxStallStatus(Related_Endpoint))
      {
        if (Related_Endpoint == ENDP0)
        {
          /* After clear the STALL, enable the default endpoint receiver */
          SetEPRxCount(Related_Endpoint, Device_Property.MaxPacketSize);
          _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
        }
        else
        {
          ClearDTOG_RX(Related_Endpoint);
          _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
        }
      }
    }
    pUser_Standard_Requests->User_ClearFeature();
    return USB_SUCCESS;
  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Standard_SetEndPointFeature
* Description    : Set or enable a specific feature of EndPoint
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetEndPointFeature(void)
{
  u32    wIndex0;
  u32    Related_Endpoint;
  u32    rEP;
  u32   Status;

  wIndex0 = pInformation->USBwIndex0;
  rEP = wIndex0 & ~0x80;
  Related_Endpoint = ENDP0 + rEP;

  if (ValBit(pInformation->USBwIndex0, 7))
  {
    /* get Status of endpoint & stall the request if the related_ENdpoint
    is Disabled*/
    Status = _GetEPTxStatus(Related_Endpoint);
  }
  else
  {
    Status = _GetEPRxStatus(Related_Endpoint);
  }

  if (Related_Endpoint >= Device_Table.Total_Endpoint
      || pInformation->USBwValue != 0 || Status == 0
      || pInformation->Current_Configuration == 0)
  {
    return USB_UNSUPPORT;
  }
  else
  {
    if (wIndex0 & 0x80)
    {
      /* IN endpoint */
      _SetEPTxStatus(Related_Endpoint, EP_TX_STALL);
    }

    else
    {
      /* OUT endpoint */
      _SetEPRxStatus(Related_Endpoint, EP_RX_STALL);
    }
  }
  pUser_Standard_Requests->User_SetEndPointFeature();
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_SetDeviceFeature.
* Description    : Set or enable a specific feature of Device.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetDeviceFeature(void)
{
  SetBit(pInformation->Current_Feature, 5);
  pUser_Standard_Requests->User_SetDeviceFeature();
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_GetDescriptorData.
* Description    : Standard_GetDescriptorData is used for descriptors transfer.
*                : This routine is used for the descriptors resident in Flash
*                  or RAM
*                  pDesc can be in either Flash or RAM
*                  The purpose of this routine is to have a versatile way to
*                  response descriptors request. It allows user to generate
*                  certain descriptors with software or read descriptors from
*                  external storage part by part.
* Input          : - Length - Length of the data in this transfer.
*                  - pDesc - A pointer points to descriptor struct.
*                  The structure gives the initial address of the descriptor and
*                  its original size.
* Output         : None.
* Return         : Address of a part of the descriptor pointed by the Usb_
*                  wOffset The buffer pointed by this address contains at least
*                  Length bytes.
*******************************************************************************/
u8 *Standard_GetDescriptorData(u16 Length, ONE_DESCRIPTOR *pDesc)
{
  u32  wOffset;

  wOffset = pInformation->Ctrl_Info.Usb_wOffset;
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size - wOffset;
    return 0;
  }

  return pDesc->Descriptor + wOffset;
	/*added by sjw
	https://blog.csdn.net/pq113_6/article/details/106374395
	
	
	这里Length都是为0，所以执行的结果是pInformation->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size；

pInformation->Ctrl_Info.Usb_wLength应该是记录下需要传输的数据长度。
	*/
}

/*******************************************************************************
* Function Name  : DataStageOut.
* Description    : Data stage of a Control Write Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DataStageOut(void)
{
  ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
  u32 save_rLength;

  save_rLength = pEPinfo->Usb_rLength;

  if (pEPinfo->CopyData && save_rLength)
  {
    u8 *Buffer;
    u32 Length;

    Length = pEPinfo->PacketSize;
    if (Length > save_rLength)
    {
      Length = save_rLength;
    }

    Buffer = (*pEPinfo->CopyData)(Length);
    pEPinfo->Usb_rLength -= Length;
    pEPinfo->Usb_rOffset += Length;

    PMAToUserBufferCopy(Buffer, GetEPRxAddr(ENDP0), Length);
  }

  if (pEPinfo->Usb_rLength != 0)
  {
    vSetEPRxStatus(EP_RX_VALID);/* re-enable for next data reception */
    SetEPTxCount(ENDP0, 0);
    vSetEPTxStatus(EP_TX_VALID);/* Expect the host to abort the data OUT stage */
  }
  /* Set the next State*/
  if (pEPinfo->Usb_rLength >= pEPinfo->PacketSize)
  {
    pInformation->ControlState = OUT_DATA;
  }
  else
  {
    if (pEPinfo->Usb_rLength > 0)
    {
      pInformation->ControlState = LAST_OUT_DATA;
    }
    else if (pEPinfo->Usb_rLength == 0)
    {
      pInformation->ControlState = WAIT_STATUS_IN;
      USB_StatusIn();
    }
  }
}

/*******************************************************************************
* Function Name  : DataStageIn.
* Description    : Data stage of a Control Read Transfer.
* Input          : None.
* Output         : None.
* Return         : None.

https://blog.csdn.net/pq113_6/article/details/106406974
基于STM32F103的USB学习笔记22 - DataStageIn
函数DataStageIn是从端点0读取数据的过程。USB主机知道要读取的总长度，如果一次读入不够，
主机会发多次IN读完数据，所以需要一个机制来确认每笔数据的内容和长度。added by sjw
*******************************************************************************/
void DataStageIn(void)
{
  ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
  u32 save_wLength = pEPinfo->Usb_wLength;
  u32 ControlState = pInformation->ControlState;
	u8 temp,js;

  u8 *DataBuffer;
  u32 Length;

	pInformation->Ctrl_Info.PacketSize = pProperty->MaxPacketSize;
	
  if ((save_wLength == 0) && (ControlState == LAST_IN_DATA))//需要传输的数据长度为0并且是最后一笔数据
  {
    if(Data_Mul_MaxPacketSize == TRUE)//总的数据长度是端点最大包长度的整数倍
    {
      /* No more data to send and empty packet */
			#ifdef  USB_DEBUG_KERNEL 		
		      printf("发送一个空包！！\r\n");
	    #endif 
      Send0LengthData(); //发送一个空包
      ControlState = LAST_IN_DATA;
      Data_Mul_MaxPacketSize = FALSE;
    }
    else 
    {
      /* No more data to send so STALL the TX Status*/
      ControlState = WAIT_STATUS_OUT;
      vSetEPTxStatus(EP_TX_STALL);
//			#ifdef  USB_DEBUG_KERNEL 		
//		      printf("ControlState = WAIT_STATUS_OUT  so STALL the TX Status！！\r\n");
//	    #endif 
    }
    
    goto Expect_Status_Out;
  }

  Length = pEPinfo->PacketSize;
  ControlState = (save_wLength <= Length) ? LAST_IN_DATA : IN_DATA;//判断是不是最后一笔数据

  if (Length > save_wLength)//如果端点长度大于数据长度
  {
    Length = save_wLength;
  }

	//这是我仿真捕获的IN数据，响应描叙符 0x12 0x01 0x00 0x02 0x0 0x0 0x0 0x40 x83 0x04 0x20 0x57 0x0 0x02 0x1 0x2 0x3 0x1
  DataBuffer = (*pEPinfo->CopyData)(Length);//获取要发送的数据buffer指针    //取得用户描述符缓冲区的地址，这里共18个字节

  UserToPMABufferCopy(DataBuffer, GetEPTxAddr(ENDP0), Length);//将数据拷贝到PMA中  //将设备描述符复制到用户的发送缓冲区

  SetEPTxCount(ENDP0, Length);     //设置端点Tx的长度（即PMA中有效数据长度）  //设置发送字节的数目：18
	temp=Length;

  pEPinfo->Usb_wLength -= Length;  //把总数据长度减掉这次发送的长度  //等于0
  pEPinfo->Usb_wOffset += Length;  //把数据的偏移值加上这次发送的长度  //偏移到18
  vSetEPTxStatus(EP_TX_VALID);     //设置端点Tx的状态为有效  //使能端点发送，只要主机的IN令牌包一来，SIE就会将描述符返回给主机
	
	for(js=0;js<temp;js++)	
			CoreTest[js]=*DataBuffer++;
	
	#ifdef  USB_DEBUG_KERNEL
		    printf("设备回馈HOST:\r\n");
	      for(js=0;js<temp;js++)
						printf("0x%x ", CoreTest[js]);
				printf("\r\n");	 
	 #endif 
	
  USB_StatusOut();/* Expect the host to abort the data IN stage */// 这个实际上是使接收也有效，主机可取消 IN


Expect_Status_Out:
  pInformation->ControlState = ControlState;
	
//	#ifdef  USB_DEBUG_KERNEL 		
//		     // printf("准备执行Device-》Host的传输，现在已经进入了函数DataStageIn里面！\r\n");
//		     // printf("pInformation->Ctrl_Info.Usb_wOffset=%u,pInformation->Ctrl_Info.PacketSize=%d",\
//		              //pInformation->Ctrl_Info.Usb_wOffset,pInformation->Ctrl_Info.PacketSize);
//	        printf("save_wLength=%lu,ControlState=%lu\r\n",save_wLength,ControlState);
//	 #endif 	
	

	
}

/*******************************************************************************
* Function Name  : NoData_Setup0.
* Description    : Proceed the processing of setup request without data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void NoData_Setup0(void)
{
  RESULT Result = USB_UNSUPPORT;
  u32 RequestNo = pInformation->USBbRequest;
  u32 ControlState;

  if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {
    /* Device Request*/
	//判断具体的请求，根据不同的请求做出相关的操作
    /* SET_CONFIGURATION*/
    if (RequestNo == SET_CONFIGURATION)
    {
      Result = Standard_SetConfiguration();
    }

    /*SET ADDRESS*/
    else if (RequestNo == SET_ADDRESS)
    {
      if ((pInformation->USBwValue0 > 127) || (pInformation->USBwValue1 != 0)
          || (pInformation->USBwIndex != 0)
          || (pInformation->Current_Configuration != 0))
        /* Device Address should be 127 or less*/
      {
        ControlState = STALLED;
        goto exit_NoData_Setup0;
      }
      else
      {
        Result = USB_SUCCESS;
      }
    }
    /*SET FEATURE for Device*/
    else if (RequestNo == SET_FEATURE)
    {
      if ((pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP)
          && (pInformation->USBwIndex == 0)
          && (ValBit(pInformation->Current_Feature, 5)))
      {
        Result = Standard_SetDeviceFeature();
      }
      else
      {
        Result = USB_UNSUPPORT;
      }
    }
    /*Clear FEATURE for Device */
    else if (RequestNo == CLEAR_FEATURE)
    {
      if (pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP
          && pInformation->USBwIndex == 0
          && ValBit(pInformation->Current_Feature, 5))
      {
        Result = Standard_ClearFeature();
      }
      else
      {
        Result = USB_UNSUPPORT;
      }
    }

  }

  /* Interface Request*/
  else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    /*SET INTERFACE*/
    if (RequestNo == SET_INTERFACE)
    {
      Result = Standard_SetInterface();
    }
  }

  /* EndPoint Request*/
  else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {
    /*CLEAR FEATURE for EndPoint*/
    if (RequestNo == CLEAR_FEATURE)
    {
      Result = Standard_ClearFeature();
    }
    /* SET FEATURE for EndPoint*/
    else if (RequestNo == SET_FEATURE)
    {
      Result = Standard_SetEndPointFeature();
    }
  }
  else
  {
    Result = USB_UNSUPPORT;
  }


  if (Result != USB_SUCCESS)
  {
    Result = (*pProperty->Class_NoData_Setup)(RequestNo);
    if (Result == USB_NOT_READY)
    {
      ControlState = PAUSE;
      goto exit_NoData_Setup0;
    }
  }

  if (Result != USB_SUCCESS)
  {
    ControlState = STALLED;
    goto exit_NoData_Setup0;
  }

  ControlState = WAIT_STATUS_IN;/* After no data stage SETUP */

  USB_StatusIn();

exit_NoData_Setup0:
  pInformation->ControlState = ControlState;
  return;
}

/*******************************************************************************
* Function Name  : Data_Setup0.
* Description    : Proceed the processing of setup request with data stage.
* Input          : None.
* Output         : None.
* Return         : None.
该函数根据请求的不同描述符，执行不同的回调函数CopyRoutine()，
并在DataStageIn()函数中把要发送给主机的描述符填入USB缓冲区，等待USB主机发送IN令牌包。added by sjw
*******************************************************************************/

//该函数根据请求的不同描述符，执行不同的回调函数CopyRoutine()，并在DataStageIn()函数中把要发送给主机的描述符填入USB缓冲区，等待USB主机发送IN令牌包。

//主机在建立过程最后收到ACK以后，发送IN令牌包，从而进入到数据过程。
//在CTR_LP()函数中判断是IN0中断后，进入In0_Process()函数。在数据过程将之前填在USB缓冲器的设备描述符发给主机，并等待主机的应答。

/*
https://blog.csdn.net/pq113_6/article/details/106374395
	
基于STM32F103的USB学习笔记21 - Data_Setup0

a. GET_DESCRIPTOR
				命令	           bmRequestType	  bRequest	       wValue	             wIndex	     wLength	  Data	
				Get_Descriptor	   10000000B	   GET_DESCRIPTOR	 描述表种类(高字节）	0或语言标志	描述表长度 	描述表
																												 和索引（低字节）
					
				这里只读取的标准描述符，类描述符并没有处理。标准描述符的种类值如下表。
					描述符	                                描述符值
					设备描述符（Device Descriptor)            0x01
					配置描述符（Configuration Descriptor）	  0x02 
					字符串描述符（String Descriptor）	        0x03  
					接口描述符（Interface Descriptor）	      0x04
					端点描述符（EndPont Descriptor）	        0x05
					
					
				比如开始枚举：	设备接收数据如下:	0x80 0x6 0x0 0x1 0x0 0x0 0x40 0x0
												
												 
b. GET_STATUS
		命令	        bmRequestType	  bRequest	   wValue	   wIndex	               wLength	          Data
		
   Get_Status		  10000000B      GET_STATUS      0      0（返回设备状态）          2               设备状态
	                10000001B                             接口号（对象是接口时）                     接口状态
									10000010B                             端点号（对象是端点时）                     端点状态
		
		
		Get_Status命令对设备，接口，端点都有效，wValue都是0，而wIndex根据设备，接口，端点有不同的意义，而wIndex一定是2，接下来的Data数据一定是2个字节。
		
		
c. GET_CONFIGURATION		
		
   命令	         bmRequestType	    bRequest	       wValue	wIndex	wLength	   Data		
		
	Get_Configuration	10000000B	   GET_CONFIGURATION	   0	    0	      1	      配置值	
		
d. GET_INTERFACE
	 命令	           bmRequestType	   bRequest	   wValue	   wIndex	   wLength	  Data
   Get_Interface	   10000001B	   GET_INTERFACE	   0	    接口号	      1	     可选设置
	 获取标准的描述符的代码都类似，都是调用库函数Standard_GetDescriptorData
   Standard_GetDescriptorData
*/

	
void Data_Setup0(void)
{
  u8 *(*CopyRoutine)(u16);
  RESULT Result;
  u32 Request_No = pInformation->USBbRequest;

  u32 Related_Endpoint, Reserved;
  u32 wOffset, Status;

  CopyRoutine = NULL;
  wOffset = 0;

  if (Request_No == GET_DESCRIPTOR) //获取描述符
  {    
		if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {	
      u8 wValue1 = pInformation->USBwValue1;
      if (wValue1 == DEVICE_DESCRIPTOR)         //设备描述符   ,USB_Test_Value
      {
        #ifdef  USB_DEBUG_KERNEL 		
		      printf("该控制传输需要获取“设备描叙符”，进入分支1！\r\n");
	      #endif 
				CopyRoutine = pProperty->GetDeviceDescriptor;
      }
      else if (wValue1 == CONFIG_DESCRIPTOR)   //配置描述符
      {
        #ifdef  USB_DEBUG_KERNEL 		
		      printf("该控制传输需要获取“配置描叙符”，进入分支2！\r\n");
	      #endif 
				CopyRoutine = pProperty->GetConfigDescriptor;
      }
      else if (wValue1 == STRING_DESCRIPTOR) 
      {
        #ifdef  USB_DEBUG_KERNEL 		
		      printf("该控制传输需要获取“字符串描叙符”，进入分支3！\r\n");
	      #endif 
				CopyRoutine = pProperty->GetStringDescriptor;  //字符串描述符
      }  /* End of GET_DESCRIPTOR */
    }
		//return;//added by sjw for watch!!
  }

  /*GET STATUS*/
  else if ((Request_No == GET_STATUS) && (pInformation->USBwValue == 0)
           && (pInformation->USBwLength == 0x0002)
           && (pInformation->USBwIndex1 == 0))
  {
		#ifdef USB_DEBUG_KERNEL 	
			printf("该控制传输需要得到状态！\r\n");
	  #endif 
    /* GET STATUS for Device*/
    if ((Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
        && (pInformation->USBwIndex == 0))
    {
      CopyRoutine = Standard_GetStatus;
    }

    /* GET STATUS for Interface*/
    else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    {
      if (((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS)
          && (pInformation->Current_Configuration != 0))
      {
        CopyRoutine = Standard_GetStatus;
      }
    }

    /* GET STATUS for EndPoint*/
    else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
      Related_Endpoint = (pInformation->USBwIndex0 & 0x0f);
      Reserved = pInformation->USBwIndex0 & 0x70;

      if (ValBit(pInformation->USBwIndex0, 7))
      {
        /*Get Status of endpoint & stall the request if the related_ENdpoint
        is Disabled*/
        Status = _GetEPTxStatus(Related_Endpoint);
      }
      else
      {
        Status = _GetEPRxStatus(Related_Endpoint);
      }

      if ((Related_Endpoint < Device_Table.Total_Endpoint) && (Reserved == 0)
          && (Status != 0))
      {
        CopyRoutine = Standard_GetStatus;
      }
    }
  }

  /*GET CONFIGURATION*/ //获取配置
  else if (Request_No == GET_CONFIGURATION)
  {
		#ifdef USB_DEBUG_KERNEL 	
		printf("需要获取“配置描叙符”！\r\n");
	  #endif 
    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
      CopyRoutine = Standard_GetConfiguration;
    }
  }
  /*GET INTERFACE*/
  else if (Request_No == GET_INTERFACE)
  {
		#ifdef USB_DEBUG0		
		printf("该控制传输需要获取接口！\r\n");
	  #endif 
    if ((Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
        && (pInformation->Current_Configuration != 0) && (pInformation->USBwValue == 0)
        && (pInformation->USBwIndex1 == 0) && (pInformation->USBwLength == 0x0001)
        && ((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS))
    {
      CopyRoutine = Standard_GetInterface;
    }

  }
  
	
	
  if (CopyRoutine)
  {
		 
    pInformation->Ctrl_Info.Usb_wOffset = wOffset;
    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    /* sb in the original the cast to word was directly */
    /* now the cast is made step by step */
    (*CopyRoutine)(0);//这个函数在这里调用的目的是设置pInformation中需要写入的描述符的长度
    Result = USB_SUCCESS;
		
		//return;//added by sjw for watch!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }
  else
  {
    Result = (*pProperty->Class_Data_Setup)(pInformation->USBbRequest);
    if (Result == USB_NOT_READY)
    {
      pInformation->ControlState = PAUSE;
      return;
    }
  }

  if (pInformation->Ctrl_Info.Usb_wLength == 0xFFFF)
  {
    /* Data is not ready, wait it */
    pInformation->ControlState = PAUSE;
    return;
  }
  if ((Result == USB_UNSUPPORT) || (pInformation->Ctrl_Info.Usb_wLength == 0))
  {
    /* Unsupported request */
    pInformation->ControlState = STALLED;
    return;
  }


  if (ValBit(pInformation->USBbmRequestType, 7))/* Device ==> Host ：此时为80，说明方向是IN*/
  {
    /* Device ==> Host */
    vu32 wLength = pInformation->USBwLength;//这个一般是64
		
    /* Restrict the data length to be the one host asks */
    if (pInformation->Ctrl_Info.Usb_wLength > wLength)
    {
      pInformation->Ctrl_Info.Usb_wLength = wLength;//设备描述符长度18
    }
    
    else if (pInformation->Ctrl_Info.Usb_wLength < pInformation->USBwLength)
    {
      if (pInformation->Ctrl_Info.Usb_wLength < pProperty->MaxPacketSize)
      {
        Data_Mul_MaxPacketSize = FALSE;
      }
      else if ((pInformation->Ctrl_Info.Usb_wLength % pProperty->MaxPacketSize) == 0)
      {
        Data_Mul_MaxPacketSize = TRUE;
      }
    }
    DataStageIn();//调用这个函数实现描述符的输出准备
  }
  else
  {
    pInformation->ControlState = OUT_DATA;
    vSetEPRxStatus(EP_RX_VALID); /* enable for next data reception */
  }

  return;
}

/*******************************************************************************
* Function Name  : Setup0_Process
* Description    : Get the device request data and dispatch to individual process.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
//在打印信息之后直接就让函数返回，使主机得不到ACK应答，下面根据打印信息看下测试情况。
   /*
	 return Post0_Process();//added by sjw
	 
	 
		这个过程通过串口发现出现四次--我是win10操作系统！
		设备接收数据如下:
		0x80 0x6 0x0 0x1 0x0 0x0 0x40 0x0 
		之后主机放弃！！
		*/
			
	 
	 
	 

//————————————————
//版权声明：本文为CSDN博主「qq236106303」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/qq236106303/article/details/8177568		
	
	/*在打印信息之后直接就让函数返回，使主机得不到ACK应答，下面根据打印信息看下测试情况。
	
	根据打印信息，由于从机没有ACK应答给PC机的请求，在PC机尝试发了3-4次请求后，就放弃了。可以在PC机的设备管理器看到，
	在请求打印3次以后出现了unknown device。

    关于8个字节的请求代码的具体含义请参照USB协议，或者在《圈圈教你玩USB》里面对照。

    以上就是枚举过程获取设备描述符的第一步控制传输的建立过程，主机发送获取描述符的请求，下一篇我们将代码中ACK返回，
		使主机接收到建立过程的应答，从而进入到数据过程，即设备响应主机的请求，将设备描述符发送给主机。
————————————————
版权声明：本文为CSDN博主「qq236106303」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq236106303/article/details/8177568






https://blog.csdn.net/qq236106303/article/details/8179005
基于STM32的USB枚举过程学习笔记(三)
上一篇介绍到了主机上电复位USB设备，在控制传输的建立过程，发送了8个字节的数据给设备，这8个字节为0x80 0x06 0x00 0x01 0x00 0x00 0x40 0x00，
该请求为USB标准设备请求中的GET_DESCRIPTOR请求。0x80表示标准设备请求，数据方向是设备到主机。0x06表示请求类型GET_DESCRIPTOR。
0x01表示描述符类型是设备描述符。0x40表示描述符长度。

设备在收到该请求以后，首先进行解析，根据请求中的0x40表示该控制传输有数据过程，因此进入到Data_Setup0()函数。

————————————————
版权声明：本文为CSDN博主「qq236106303」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq236106303/article/details/8179005

	*/
	
	
u8 Setup0_Process(void)//这个函数执行的时候，主机发来的请求数据包已经存在ENDP0_RXADDR缓冲区了。大部分的标志位已经清除，除了SETUP位，这个位将由下一个令牌包自动清除
{

  union
  {
    u8* b;
    u16* w;
  } pBuf;

  pBuf.b = PMAAddr + (u8 *)(_GetEPRxAddr(ENDP0) * 2); /* *2 for 32 bits addr *//* *2 for 32 bits addr ：这是取得端点0接收缓冲区的起始地址*/   
	//PMAAddr是包缓冲区起始地址，_GetEPRxAddr(ENDP0)获得端点0描述符表里的接收缓冲区地址。
  //乘以2的原因是，描述符里地址项为16位，使用的是相对偏移。
	
	

  //将缓冲数据填到设备请求的各字段中  注意，这是从USB寄存器的地址里面取出host发送过啦的数据！content added by sjw
  if (pInformation->ControlState != PAUSE)
  {
    pInformation->USBbmRequestType = *pBuf.b++;     /* bmRequestType *//* bmRequestType：请求类型，表示方向和接收对象(设备、接口还是端点)此时为80，表明设备到主机。*/
    pInformation->USBbRequest = *pBuf.b++;          /* bRequest */ /* bRequest：请求代码，第一次时应该为6，表明主机要获取设备描述符。 */
    pBuf.w++;                                       /* word not accessed because of 32 bits addressing */
    pInformation->USBwValue = ByteSwap(*pBuf.w++);  /* wValue */
    pBuf.w++;                                       /* word not accessed because of 32 bits addressing */
    pInformation->USBwIndex  = ByteSwap(*pBuf.w++); /* wIndex */
    pBuf.w++;                                       /* word not accessed because of 32 bits addressing */
    pInformation->USBwLength = *pBuf.w;             /* wLength */
  }


	 
	 	
#ifdef  USB_DEBUG_KERNEL   //USB_DEBUG0 ||
    printf("设备接收:\r\n");
    printf("0x%x ",pInformation->USBbmRequestType);//用于指定请求的 数据传输反向 请求类型 请求的接收者
    printf("0x%x ",pInformation->USBbRequest);     //标准请求及代码
 
    printf("0x%x ",pInformation->USBwValue0);
    printf("0x%x ",pInformation->USBwValue1);      //具体见圈圈书P77页
 
    printf("0x%x ",pInformation->USBwIndex0);
    printf("0x%x ",pInformation->USBwIndex1);  
 
    printf("0x%x ",pInformation->USBwLength1);
    printf("0x%x ",pInformation->USBwLength0);
    printf("\r\n");
#endif /* USB_DEBUG0 */
	
  pInformation->ControlState = SETTING_UP;
  if (pInformation->USBwLength == 0)		   //判断请求是否带数据，为0表示不带数据
 // if (!((pInformation->USBbmRequestType &0x80)==0x80))	  //圈圈的程序是通过USBbmRequestType的D7
                                                            //位来判断数据的方向，D7位为1，说明是输入
															//请求，为0是输出请求，输入是带数据的，输出是不带数据的																												
  {
		/* Setup with no data stage */	
    NoData_Setup0();	        //不带数据 （输出清求）
  }
  else
  {
		//该函数根据请求的不同描述符，执行不同的回调函数CopyRoutine()，
		//并在DataStageIn()函数中把要发送给主机的描述符填入USB缓冲区，等待USB主机发送IN令牌包。
		//每次处理CTR_TX中断时，写进hw_buf的内容都是下次要发送的内容，
		//因此，在首次处理IN请求之前需要准备好hw_buf，如果SETUP的数据阶段是IN，就要在Setup0_Process()中调用DataStageIn()填充首次需要准备的内容。
		//参考：            https://blog.csdn.net/mr_bean_1031/article/details/75944777
    //USB请求由SETUP transaction完成，一条完整的USB请求存放在其中的DATA0 packet中，字节序为小端模式。
		
		//0x0 0x5 0x25 0x0 0x0 0x0 0x0 0x0 
		//0x0 0x5 0x29 0x0 0x0 0x0 0x0 0x0 
		/* Setup with data stage */
    Data_Setup0();		  //带数据	 （输入请求）
		
  }
  return Post0_Process();
}

/*******************************************************************************
* Function Name  : In0_Process
* Description    : Process the IN token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
u8 In0_Process(void)
{
  u32 ControlState = pInformation->ControlState;

  if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
  {
    DataStageIn(); //第一次取设备描述符，只取一次。此次调用后，当前状态变为WAIT_STATUS_OUT，表明设备等待状态过程，主机输出0字节
    /* ControlState may be changed outside the function */
    ControlState = pInformation->ControlState;
  }

  else if (ControlState == WAIT_STATUS_IN)
  {
    if ((pInformation->USBbRequest == SET_ADDRESS) &&
        (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)))
    {
      SetDeviceAddress(pInformation->USBwValue0);
      pUser_Standard_Requests->User_SetDeviceAddress();
    }
    (*pProperty->Process_Status_IN)();
    ControlState = STALLED;
  }

  else
  {
    ControlState = STALLED;
  }

  pInformation->ControlState = ControlState;

  return Post0_Process();
}

/*******************************************************************************
* Function Name  : Out0_Process
* Description    : Process the OUT token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.

主机收到18字节描述符后，进入状态事务过程，此时过程的令牌包为OUT，字节数为0，只需要用户返回一个ACK。
    所以中断处理程序会进入Out0_Process()。
*******************************************************************************/
u8 Out0_Process(void)
{
  u32 ControlState = pInformation->ControlState;

  if ((ControlState == OUT_DATA) || (ControlState == LAST_OUT_DATA))
  {
    DataStageOut();
    ControlState = pInformation->ControlState; /* may be changed outside the function */
  }

  else if (ControlState == WAIT_STATUS_OUT)
  {
    (*pProperty->Process_Status_OUT)();
    ControlState = STALLED;
  }

  else if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
  {
    /* host aborts the transfer before finish */
    ControlState = STALLED;
  }

  /* Unexpect state, STALL the endpoint */
  else
  {
    ControlState = STALLED;
  }

  pInformation->ControlState = ControlState;

  return Post0_Process();
}

/*******************************************************************************
* Function Name  : Post0_Process
* Description    : Stall the Endpoint 0 in case of error.
* Input          : None.
* Output         : None.
* Return         : - 0 if the control State is in PAUSE
*                  - 1 if not.
*******************************************************************************/
u8 Post0_Process(void)//返回时调用这个函数，没做什么事
{
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);

  if (pInformation->ControlState == STALLED)
  {
    vSetEPRxStatus(EP_RX_STALL);
    vSetEPTxStatus(EP_TX_STALL);
  }

  return (pInformation->ControlState == PAUSE);
}

/*******************************************************************************
* Function Name  : SetDeviceAddress.
* Description    : Set the device and all the used Endpoints addresses.
* Input          : - Val: device adress.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetDeviceAddress(u8 Val)
{
  u32 i;
  u32 nEP = Device_Table.Total_Endpoint;

  /* set address in every used endpoint */
  for (i = 0; i < nEP; i++)
  {
    _SetEPAddress((u8)i, (u8)i);
  } /* for */
  _SetDADDR(Val | DADDR_EF); /* set device address and enable function */
}

/*******************************************************************************
* Function Name  : NOP_Process
* Description    : No operation function.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void NOP_Process(void)
{
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
