	//       打开iap.h代码如下：
	#ifndef __APP_H__
	#define __APP_H__
	//#include "sys.h" 
	typedef  void (*appfun)(void);   //定义一个函数类型的参数. 
	#define MOUDLECPUID          (0x00001100)
	#define BootloaderAddress    (0x08000000) //，*(__IO uint32_t*)ApplicationAddress)
	#define ApplicationAddress   (0x08007000) //，*(__IO uint32_t*)ApplicationAddress)
	#define FLASH_ADDR           (0x0800fc00)   //stm32rbt6地址共64K,其它芯片注意flash大小！
    #define FLASH_DATA           (0x5a5b5c5d)  //要写入的数据
	#define IAP_PROGRAMCMD       (0xbcbdbebf)

	void AppLoadIap(vu32 appxaddr);                             //跳转到APP程序执行
	void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 applen);  //在指定地址开始,写入bin
	#endif


