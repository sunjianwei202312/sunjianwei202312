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
	
	
	����Length����Ϊ0������ִ�еĽ����pInformation->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size��

pInformation->Ctrl_Info.Usb_wLengthӦ���Ǽ�¼����Ҫ��������ݳ��ȡ�
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
����STM32F103��USBѧϰ�ʼ�22 - DataStageIn
����DataStageIn�ǴӶ˵�0��ȡ���ݵĹ��̡�USB����֪��Ҫ��ȡ���ܳ��ȣ����һ�ζ��벻����
�����ᷢ���IN�������ݣ�������Ҫһ��������ȷ��ÿ�����ݵ����ݺͳ��ȡ�added by sjw
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
	
  if ((save_wLength == 0) && (ControlState == LAST_IN_DATA))//��Ҫ��������ݳ���Ϊ0���������һ������
  {
    if(Data_Mul_MaxPacketSize == TRUE)//�ܵ����ݳ����Ƕ˵��������ȵ�������
    {
      /* No more data to send and empty packet */
			#ifdef  USB_DEBUG_KERNEL 		
		      printf("����һ���հ�����\r\n");
	    #endif 
      Send0LengthData(); //����һ���հ�
      ControlState = LAST_IN_DATA;
      Data_Mul_MaxPacketSize = FALSE;
    }
    else 
    {
      /* No more data to send so STALL the TX Status*/
      ControlState = WAIT_STATUS_OUT;
      vSetEPTxStatus(EP_TX_STALL);
//			#ifdef  USB_DEBUG_KERNEL 		
//		      printf("ControlState = WAIT_STATUS_OUT  so STALL the TX Status����\r\n");
//	    #endif 
    }
    
    goto Expect_Status_Out;
  }

  Length = pEPinfo->PacketSize;
  ControlState = (save_wLength <= Length) ? LAST_IN_DATA : IN_DATA;//�ж��ǲ������һ������

  if (Length > save_wLength)//����˵㳤�ȴ������ݳ���
  {
    Length = save_wLength;
  }

	//�����ҷ��沶���IN���ݣ���Ӧ����� 0x12 0x01 0x00 0x02 0x0 0x0 0x0 0x40 x83 0x04 0x20 0x57 0x0 0x02 0x1 0x2 0x3 0x1
  DataBuffer = (*pEPinfo->CopyData)(Length);//��ȡҪ���͵�����bufferָ��    //ȡ���û��������������ĵ�ַ�����ﹲ18���ֽ�

  UserToPMABufferCopy(DataBuffer, GetEPTxAddr(ENDP0), Length);//�����ݿ�����PMA��  //���豸���������Ƶ��û��ķ��ͻ�����

  SetEPTxCount(ENDP0, Length);     //���ö˵�Tx�ĳ��ȣ���PMA����Ч���ݳ��ȣ�  //���÷����ֽڵ���Ŀ��18
	temp=Length;

  pEPinfo->Usb_wLength -= Length;  //�������ݳ��ȼ�����η��͵ĳ���  //����0
  pEPinfo->Usb_wOffset += Length;  //�����ݵ�ƫ��ֵ������η��͵ĳ���  //ƫ�Ƶ�18
  vSetEPTxStatus(EP_TX_VALID);     //���ö˵�Tx��״̬Ϊ��Ч  //ʹ�ܶ˵㷢�ͣ�ֻҪ������IN���ư�һ����SIE�ͻὫ���������ظ�����
	
	for(js=0;js<temp;js++)	
			CoreTest[js]=*DataBuffer++;
	
	#ifdef  USB_DEBUG_KERNEL
		    printf("�豸����HOST:\r\n");
	      for(js=0;js<temp;js++)
						printf("0x%x ", CoreTest[js]);
				printf("\r\n");	 
	 #endif 
	
  USB_StatusOut();/* Expect the host to abort the data IN stage */// ���ʵ������ʹ����Ҳ��Ч��������ȡ�� IN


Expect_Status_Out:
  pInformation->ControlState = ControlState;
	
//	#ifdef  USB_DEBUG_KERNEL 		
//		     // printf("׼��ִ��Device-��Host�Ĵ��䣬�����Ѿ������˺���DataStageIn���棡\r\n");
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
	//�жϾ�������󣬸��ݲ�ͬ������������صĲ���
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
�ú�����������Ĳ�ͬ��������ִ�в�ͬ�Ļص�����CopyRoutine()��
����DataStageIn()�����а�Ҫ���͸�����������������USB���������ȴ�USB��������IN���ư���added by sjw
*******************************************************************************/

//�ú�����������Ĳ�ͬ��������ִ�в�ͬ�Ļص�����CopyRoutine()������DataStageIn()�����а�Ҫ���͸�����������������USB���������ȴ�USB��������IN���ư���

//�����ڽ�����������յ�ACK�Ժ󣬷���IN���ư����Ӷ����뵽���ݹ��̡�
//��CTR_LP()�������ж���IN0�жϺ󣬽���In0_Process()�����������ݹ��̽�֮ǰ����USB���������豸�������������������ȴ�������Ӧ��

/*
https://blog.csdn.net/pq113_6/article/details/106374395
	
����STM32F103��USBѧϰ�ʼ�21 - Data_Setup0

a. GET_DESCRIPTOR
				����	           bmRequestType	  bRequest	       wValue	             wIndex	     wLength	  Data	
				Get_Descriptor	   10000000B	   GET_DESCRIPTOR	 ����������(���ֽڣ�	0�����Ա�־	�������� 	������
																												 �����������ֽڣ�
					
				����ֻ��ȡ�ı�׼������������������û�д�����׼������������ֵ���±�
					������	                                ������ֵ
					�豸��������Device Descriptor)            0x01
					������������Configuration Descriptor��	  0x02 
					�ַ�����������String Descriptor��	        0x03  
					�ӿ���������Interface Descriptor��	      0x04
					�˵���������EndPont Descriptor��	        0x05
					
					
				���翪ʼö�٣�	�豸������������:	0x80 0x6 0x0 0x1 0x0 0x0 0x40 0x0
												
												 
b. GET_STATUS
		����	        bmRequestType	  bRequest	   wValue	   wIndex	               wLength	          Data
		
   Get_Status		  10000000B      GET_STATUS      0      0�������豸״̬��          2               �豸״̬
	                10000001B                             �ӿںţ������ǽӿ�ʱ��                     �ӿ�״̬
									10000010B                             �˵�ţ������Ƕ˵�ʱ��                     �˵�״̬
		
		
		Get_Status������豸���ӿڣ��˵㶼��Ч��wValue����0����wIndex�����豸���ӿڣ��˵��в�ͬ�����壬��wIndexһ����2����������Data����һ����2���ֽڡ�
		
		
c. GET_CONFIGURATION		
		
   ����	         bmRequestType	    bRequest	       wValue	wIndex	wLength	   Data		
		
	Get_Configuration	10000000B	   GET_CONFIGURATION	   0	    0	      1	      ����ֵ	
		
d. GET_INTERFACE
	 ����	           bmRequestType	   bRequest	   wValue	   wIndex	   wLength	  Data
   Get_Interface	   10000001B	   GET_INTERFACE	   0	    �ӿں�	      1	     ��ѡ����
	 ��ȡ��׼���������Ĵ��붼���ƣ����ǵ��ÿ⺯��Standard_GetDescriptorData
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

  if (Request_No == GET_DESCRIPTOR) //��ȡ������
  {    
		if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {	
      u8 wValue1 = pInformation->USBwValue1;
      if (wValue1 == DEVICE_DESCRIPTOR)         //�豸������   ,USB_Test_Value
      {
        #ifdef  USB_DEBUG_KERNEL 		
		      printf("�ÿ��ƴ�����Ҫ��ȡ���豸��������������֧1��\r\n");
	      #endif 
				CopyRoutine = pProperty->GetDeviceDescriptor;
      }
      else if (wValue1 == CONFIG_DESCRIPTOR)   //����������
      {
        #ifdef  USB_DEBUG_KERNEL 		
		      printf("�ÿ��ƴ�����Ҫ��ȡ��������������������֧2��\r\n");
	      #endif 
				CopyRoutine = pProperty->GetConfigDescriptor;
      }
      else if (wValue1 == STRING_DESCRIPTOR) 
      {
        #ifdef  USB_DEBUG_KERNEL 		
		      printf("�ÿ��ƴ�����Ҫ��ȡ���ַ�����������������֧3��\r\n");
	      #endif 
				CopyRoutine = pProperty->GetStringDescriptor;  //�ַ���������
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
			printf("�ÿ��ƴ�����Ҫ�õ�״̬��\r\n");
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

  /*GET CONFIGURATION*/ //��ȡ����
  else if (Request_No == GET_CONFIGURATION)
  {
		#ifdef USB_DEBUG_KERNEL 	
		printf("��Ҫ��ȡ���������������\r\n");
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
		printf("�ÿ��ƴ�����Ҫ��ȡ�ӿڣ�\r\n");
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
    (*CopyRoutine)(0);//���������������õ�Ŀ��������pInformation����Ҫд����������ĳ���
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


  if (ValBit(pInformation->USBbmRequestType, 7))/* Device ==> Host ����ʱΪ80��˵��������IN*/
  {
    /* Device ==> Host */
    vu32 wLength = pInformation->USBwLength;//���һ����64
		
    /* Restrict the data length to be the one host asks */
    if (pInformation->Ctrl_Info.Usb_wLength > wLength)
    {
      pInformation->Ctrl_Info.Usb_wLength = wLength;//�豸����������18
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
    DataStageIn();//�����������ʵ�������������׼��
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
//�ڴ�ӡ��Ϣ֮��ֱ�Ӿ��ú������أ�ʹ�����ò���ACKӦ��������ݴ�ӡ��Ϣ���²��������
   /*
	 return Post0_Process();//added by sjw
	 
	 
		�������ͨ�����ڷ��ֳ����Ĵ�--����win10����ϵͳ��
		�豸������������:
		0x80 0x6 0x0 0x1 0x0 0x0 0x40 0x0 
		֮��������������
		*/
			
	 
	 
	 

//��������������������������������
//��Ȩ����������ΪCSDN������qq236106303����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https://blog.csdn.net/qq236106303/article/details/8177568		
	
	/*�ڴ�ӡ��Ϣ֮��ֱ�Ӿ��ú������أ�ʹ�����ò���ACKӦ��������ݴ�ӡ��Ϣ���²��������
	
	���ݴ�ӡ��Ϣ�����ڴӻ�û��ACKӦ���PC����������PC�����Է���3-4������󣬾ͷ����ˡ�������PC�����豸������������
	�������ӡ3���Ժ������unknown device��

    ����8���ֽڵ��������ľ��庬�������USBЭ�飬�����ڡ�ȦȦ������USB��������ա�

    ���Ͼ���ö�ٹ��̻�ȡ�豸�������ĵ�һ�����ƴ���Ľ������̣��������ͻ�ȡ��������������һƪ���ǽ�������ACK���أ�
		ʹ�������յ��������̵�Ӧ�𣬴Ӷ����뵽���ݹ��̣����豸��Ӧ���������󣬽��豸���������͸�������
��������������������������������
��Ȩ����������ΪCSDN������qq236106303����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/qq236106303/article/details/8177568






https://blog.csdn.net/qq236106303/article/details/8179005
����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
��һƪ���ܵ��������ϵ縴λUSB�豸���ڿ��ƴ���Ľ������̣�������8���ֽڵ����ݸ��豸����8���ֽ�Ϊ0x80 0x06 0x00 0x01 0x00 0x00 0x40 0x00��
������ΪUSB��׼�豸�����е�GET_DESCRIPTOR����0x80��ʾ��׼�豸�������ݷ������豸��������0x06��ʾ��������GET_DESCRIPTOR��
0x01��ʾ�������������豸��������0x40��ʾ���������ȡ�

�豸���յ��������Ժ����Ƚ��н��������������е�0x40��ʾ�ÿ��ƴ��������ݹ��̣���˽��뵽Data_Setup0()������

��������������������������������
��Ȩ����������ΪCSDN������qq236106303����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/qq236106303/article/details/8179005

	*/
	
	
u8 Setup0_Process(void)//�������ִ�е�ʱ�������������������ݰ��Ѿ�����ENDP0_RXADDR�������ˡ��󲿷ֵı�־λ�Ѿ����������SETUPλ�����λ������һ�����ư��Զ����
{

  union
  {
    u8* b;
    u16* w;
  } pBuf;

  pBuf.b = PMAAddr + (u8 *)(_GetEPRxAddr(ENDP0) * 2); /* *2 for 32 bits addr *//* *2 for 32 bits addr ������ȡ�ö˵�0���ջ���������ʼ��ַ*/   
	//PMAAddr�ǰ���������ʼ��ַ��_GetEPRxAddr(ENDP0)��ö˵�0����������Ľ��ջ�������ַ��
  //����2��ԭ���ǣ����������ַ��Ϊ16λ��ʹ�õ������ƫ�ơ�
	
	

  //������������豸����ĸ��ֶ���  ע�⣬���Ǵ�USB�Ĵ����ĵ�ַ����ȡ��host���͹��������ݣ�content added by sjw
  if (pInformation->ControlState != PAUSE)
  {
    pInformation->USBbmRequestType = *pBuf.b++;     /* bmRequestType *//* bmRequestType���������ͣ���ʾ����ͽ��ն���(�豸���ӿڻ��Ƕ˵�)��ʱΪ80�������豸��������*/
    pInformation->USBbRequest = *pBuf.b++;          /* bRequest */ /* bRequest��������룬��һ��ʱӦ��Ϊ6����������Ҫ��ȡ�豸�������� */
    pBuf.w++;                                       /* word not accessed because of 32 bits addressing */
    pInformation->USBwValue = ByteSwap(*pBuf.w++);  /* wValue */
    pBuf.w++;                                       /* word not accessed because of 32 bits addressing */
    pInformation->USBwIndex  = ByteSwap(*pBuf.w++); /* wIndex */
    pBuf.w++;                                       /* word not accessed because of 32 bits addressing */
    pInformation->USBwLength = *pBuf.w;             /* wLength */
  }


	 
	 	
#ifdef  USB_DEBUG_KERNEL   //USB_DEBUG0 ||
    printf("�豸����:\r\n");
    printf("0x%x ",pInformation->USBbmRequestType);//����ָ������� ���ݴ��䷴�� �������� ����Ľ�����
    printf("0x%x ",pInformation->USBbRequest);     //��׼���󼰴���
 
    printf("0x%x ",pInformation->USBwValue0);
    printf("0x%x ",pInformation->USBwValue1);      //�����ȦȦ��P77ҳ
 
    printf("0x%x ",pInformation->USBwIndex0);
    printf("0x%x ",pInformation->USBwIndex1);  
 
    printf("0x%x ",pInformation->USBwLength1);
    printf("0x%x ",pInformation->USBwLength0);
    printf("\r\n");
#endif /* USB_DEBUG0 */
	
  pInformation->ControlState = SETTING_UP;
  if (pInformation->USBwLength == 0)		   //�ж������Ƿ�����ݣ�Ϊ0��ʾ��������
 // if (!((pInformation->USBbmRequestType &0x80)==0x80))	  //ȦȦ�ĳ�����ͨ��USBbmRequestType��D7
                                                            //λ���ж����ݵķ���D7λΪ1��˵��������
															//����Ϊ0��������������Ǵ����ݵģ�����ǲ������ݵ�																												
  {
		/* Setup with no data stage */	
    NoData_Setup0();	        //�������� ���������
  }
  else
  {
		//�ú�����������Ĳ�ͬ��������ִ�в�ͬ�Ļص�����CopyRoutine()��
		//����DataStageIn()�����а�Ҫ���͸�����������������USB���������ȴ�USB��������IN���ư���
		//ÿ�δ���CTR_TX�ж�ʱ��д��hw_buf�����ݶ����´�Ҫ���͵����ݣ�
		//��ˣ����״δ���IN����֮ǰ��Ҫ׼����hw_buf�����SETUP�����ݽ׶���IN����Ҫ��Setup0_Process()�е���DataStageIn()����״���Ҫ׼�������ݡ�
		//�ο���            https://blog.csdn.net/mr_bean_1031/article/details/75944777
    //USB������SETUP transaction��ɣ�һ��������USB�����������е�DATA0 packet�У��ֽ���ΪС��ģʽ��
		
		//0x0 0x5 0x25 0x0 0x0 0x0 0x0 0x0 
		//0x0 0x5 0x29 0x0 0x0 0x0 0x0 0x0 
		/* Setup with data stage */
    Data_Setup0();		  //������	 ����������
		
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
    DataStageIn(); //��һ��ȡ�豸��������ֻȡһ�Ρ��˴ε��ú󣬵�ǰ״̬��ΪWAIT_STATUS_OUT�������豸�ȴ�״̬���̣��������0�ֽ�
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

�����յ�18�ֽ��������󣬽���״̬������̣���ʱ���̵����ư�ΪOUT���ֽ���Ϊ0��ֻ��Ҫ�û�����һ��ACK��
    �����жϴ����������Out0_Process()��
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
u8 Post0_Process(void)//����ʱ�������������û��ʲô��
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
