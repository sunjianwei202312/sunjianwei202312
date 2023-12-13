	//       ��iap.h�������£�
	#ifndef __APP_H__
	#define __APP_H__
	//#include "sys.h" 
	typedef  void (*appfun)(void);   //����һ���������͵Ĳ���. 
	#define MOUDLECPUID          (0x00001100)
	#define BootloaderAddress    (0x08000000) //��*(__IO uint32_t*)ApplicationAddress)
	#define ApplicationAddress   (0x08007000) //��*(__IO uint32_t*)ApplicationAddress)
	#define FLASH_ADDR           (0x0800fc00)   //stm32rbt6��ַ��64K,����оƬע��flash��С��
    #define FLASH_DATA           (0x5a5b5c5d)  //Ҫд�������
	#define IAP_PROGRAMCMD       (0xbcbdbebf)

	void AppLoadIap(vu32 appxaddr);                             //��ת��APP����ִ��
	void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 applen);  //��ָ����ַ��ʼ,д��bin
	#endif


