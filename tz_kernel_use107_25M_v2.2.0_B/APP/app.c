/*
你计算机上一个有效的策略使你无法连接到此打印队列。请与你的系统管理员联系
https://baijiahao.baidu.com/s?id=1739583361867564493&wfr=spider&for=pc







STM32引脚列表中主功能，默认复用功能和重定义功能的区别

1 主功能就是STM32基本IO口，与外设没有连接的，我们可以直接输出或读入高低电平

使用时采用要初始化GPIO结构体参数，并打开端口的时钟

2 默认复用功能是与外设连接的IO口，单片机通过控制外设来控制IO口

使用时采用要初始化GPIO结构体参数，IO口的工作模式要更具STM32中文参考手册中，IO口复用功能的设置工作模式，
设置时，与主功能的唯一区别就是IO口的工作模式的不同。

3 当我想把外设不连接到默认引脚上，那就根据“重定义功能”这一列来重新定义外设连接的IO口。一般情况我们不会用到。

 

注意：
一旦需要对AFIO寄存器配置时，一定要打开AFIO的时钟（一般在使用外部中断EXTI或外设引脚重定义时）
--------------------------------------------------------------------------------------------------







适应的电路板为BMT-DP-MAIN-01B.PCB
还有一种上面有背板的，尺寸大上面有一块背板，型号为GSFG-DP-1A.PCB
设定奇数为开发树，表示功能正在验证。。。
设定偶数为稳定树，表示功能已经得到验证（参考LINUX内核的开发流程做）

以下引脚定义虽然基于103的，但是用在407上也可以借鉴！！added by sjw 10.18

STM32 = 基于ARM的32位微控制器
F     = 通用类型 
103   = 增强型 
R     = 64脚                                  
V     = 100脚                                  
Z     = 144脚 
C     = 256K字节的闪存存储器                                  
D     = 384K字节的闪存存储器                                  
E     = 512K字节的闪存存储器
H     = BGA                                  
T     = LQFP                                  
Y     = WLCSP64 
 
STM32F103VET6片上资源
 CPU     : 32-bit 
 SRAM    : 64kB
 Flash   : 512KB
 FSMC    : 1 Flexible Static Memory Controller for SRAM, PSRAM, NOR and NAND Flash,
 PLL     : 1 PLL, 
 RCC     : Embedded Internal RC 8MHz and 32kHz,  
 RTC     : 1 Real-Time Clock,
 NVIC    : 1 Nested Interrupt Controller, Power Saving Modes, JTAG and SWD,
 TIM     : 4 Synch. 16-bit Timers with Input Capture, Output Compare and PWM,
 TIM     : 2 16-bit Advanced Timer, 2 16-bit Basic Timer, 2 16-bit Watchdog Timers,
           2 个16位带死区控制和     2 个16位基本定时器        独立型和窗口型
           紧急刹车，用于电机控制的PWM高级控制定时器   用于驱动DAC 
                            
                                      
SysTick : 1 SysTick Timer, 系统时间定时器，24位自减型计数器
SPI/I2S : 3 SPI/I2S, 有两个可复用为 I2S
         : SPI1 PIN DESRIPTION
           * PA4 - SPI1_NSS
           * PA5 - SPI1_SCK
           * PA6 - SPI1_MISO
           * PA7 - SPI1_MOSI
                  
           SPI2 PIN DESCRIPTION
           * PB12 - SPI2_NSS
           * PB13 - SPI2_SCK
           * PB14 - SPI2_MISO
           * PB15 - SPI2_MOSI

 					 I2C     : 2 I2C, 
           I2C1：PB6-I2C1_SCL、PB7-I2C1_SDA
           I2C2：PB10-I2C2_SCL、PB11-12C2_SDA
           
 					 USART   : 5 USART,
           PA9  - USART1(Tx) - USART1可用于程序下载
           PA10 - USART1(Rx) 
                   
 					 USB     : 1 USB 2.0 Full Speed Interface,
 					 CAN     : 1 CAN 2.0B Active,
           PB8 - CAN_RX
           PB9 - CAN_TX        
					                   
					 A/D     : 3 12-bit 16-ch A/D Converter, 
					 D/A     : 2 12-bit D/A Converter, 
					 SDIO    : 1 SDIO, 
					 GPIO    ：Fast I/O Ports
					 DMA     : 12 通道 DMA 控制器
        支持的外设：定时器、ADC、DAC、SDIO、
           I2S、SPI、I2C 和 USART

-----------------------------------------------------------------------------
STM32F103VET6引脚功能
脚位  管脚名称         类型    I/O电平    主功能        默认复用功能                        重映射定义功能
 1     PE2              I/O     FT         PE2           TRACECK/FSMC_A23    STM32的资料上面写了带FT的引脚可以耐5V那就是可以接5V的
 2     PE3              I/O     FT         PE3           TRACED0/FSMC_A19	   灌电流，可以的，不过电压高了，要考虑好分流电阻。
 3     PE4              I/O     FT         PE4           TRACED1/FSMC_A20		 影响肯定有，电流大了烧I/O，电压高了烧钳位二极管。
 4     PE5              I/O     FT         PE5           TRACED2/FSMC_A21		 有FT标记的脚设置为输入或OD输出时可以，设置为推挽输出不行。
 5     PE6              I/O     FT         PE6           TRACED3/FSMC_A22
 ------------------------------------------------------------------------------
 6     VBAT             S       -          VBAT	查到FT的含义，也就是那个5V容忍的IO结构，结构内部确实是一对二极管，但是那个到VDD的二极管似乎有点特殊，
 																								特殊在于他得IO口输入电压超过5V时，才会往VDD灌电流。类似于这个二极管的降压比较大。
																								去看datasheet，有一张表有写了很多io口，有些标了“FT”的就是可以5v
 ------------------------------------------------------------------------------
 7     PC13-
      TAMPER-RTC (4)   I/O     -          PC13 (5)      TAMPER-RTC

 8     PC14-
      OSC32_IN (4)     I/O     -          PC14 (5)      OSC32_IN
 9     PC15-
      OSC32_OUT (4)    I/O     -          PC15 (5)      OSC32_OUT

 10    VSS_5            S       -          VSS_5
 11    VDD_5            S       -          VDD_5
 ------------------------------------------------------------------------------
 12    OSC_IN           I       -          OSC_IN
 13    OSC_OUT          O       -          OSC_OUT
  ------------------------------------------------------------------------------

 14    NRST             I/O     -          NRST				 低电平复位
  ------------------------------------------------------------------------------

 15    PC0              I/O     -          PC0           ADC123_IN10
 16    PC1              I/O     -          PC1           ADC123_IN11
 17    PC2              I/O     -          PC2           ADC123_IN12
 18    PC3              I/O     -          PC3           ADC123_IN13
  ------------------------------------------------------------------------------

 19    VSSA             S       -          VSSA
 20    VREF-            S       -          VREF-
 21    VREF+            S       -          VREF+
 22    VDDA             S       -          VDDA
  ------------------------------------------------------------------------------

 23    PA0-WKUP         I/O     -          PA0           WKUP/USART2_CTS (7)                                               
                                                         ADC123_IN0
                                                         TIM2_CH1_ETR
                                                         TIM5_CH1/TIM8_ETR

 24    PA1               I/O    -          PA1           USART2_RTS (7)                                       
                                                         ADC123_IN1/
                                                         TIM5_CH2/TIM2_CH2 (7)

 25    PA2               I/O    -          PA2           USART2_TX (7) /TIM5_CH3/
                                                         ADC123_IN2/TIM2_CH3 (7)

 26    PA3               I/O    -          PA3           USART2_RX (7) /TIM5_CH4
                                                         ADC123_IN3/TIM2_CH4 (7)
------------------------------------------------------------------------------

 27    VSS_4             S      -          VSS_4
 28    VDD_4             S      -          VDD_4
------------------------------------------------------------------------------

 29    PA4               I/O    -          PA4           SPI1_NSS (7) /USART2_CK (7)
                                                         DAC_OUT1/ADC12_IN4
                                                         
 30    PA5               I/O    -          PA5           SPI1_SCK (7)
                                                         DAC_OUT2/ADC12_IN5
 31    PA6               I/O    -          PA6           SPI1_MISO (7) /TIM8_BKIN            TIM1_BKIN
                                                         ADC12_IN6/TIM3_CH1 (7)

 32    PA7               I/O    -          PA7           SPI1_MOSI (7) /TIM8_CH1N            TIM1_CH1N
                                                         ADC12_IN7/TIM3_CH2 (7)
-----------------------------------------------------------------------------


 33    PC4               I/O    -          PC4           ADC12_IN14
 34    PC5               I/O    -          PC5           ADC12_IN15
 35    PB0               I/O    -          PB0           ADC12_IN8/TIM3_CH3                  TIM1_CH2N
                                                         TIM8_CH2N
 36    PB1               I/O    -          PB1           ADC12_IN9/TIM3_CH4 (7)              TIM1_CH3N
                                                         TIM8_CH3N

 37    PB2               I/O    FT         PB2/BOOT1
 38    PE7               I/O    FT         PE7           FSMC_D4                             TIM1_ETR
 39    PE8               I/O    FT         PE8           FSMC_D5                             TIM1_CH1N
 40    PE9               I/O    FT         PE9           FSMC_D6                             TIM1_CH1
 41    PE10              I/O    FT         PE10          FSMC_D7                             TIM1_CH2N
 42    PE11              I/O    FT         PE11          FSMC_D8                             TIM1_CH2
 43    PE12              I/O    FT         PE12          FSMC_D9                             TIM1_CH3N
 44    PE13              I/O    FT         PE13          FSMC_D10                            TIM1_CH3
 45    PE14              I/O    FT         PE14          FSMC_D11                            TIM1_CH4
 46    PE15              I/O    FT         PE15          FSMC_D12                            TIM1_BKIN
 -----------------------------------------------------------------------------

 47    PB10              I/O    FT         PB10          I2C2_SCL/USART3_TX (7)              TIM2_CH3
 48    PB11              I/O    FT         PB11          I2C2_SDA/USART3_RX (7)              TIM2_CH4
 -----------------------------------------------------------------------------

 49    VSS_1             S      -          VSS_1
 50    VDD_1             S      -          VDD_1
 -----------------------------------------------------------------------------

 51    PB12              I/O    FT         PB12          SPI2_NSS/I2S2_WS/
                                                         I2C2_SMBA/USART3_CK (7)
                                                         TIM1_BKIN (7)

 52    PB13              I/O    FT         PB13          SPI2_SCK/I2S2_CK
                                                         USART3_CTS (7) /
                                                         TIM1_CH1N

 53    PB14              I/O    FT         PB14          SPI2_MISO/TIM1_CH2N
                                                         USART3_RTS (7)

 54    PB15              I/O    FT         PB15          SPI2_MOSI/I2S2_SD
                                                         TIM1_CH3N (7)
-----------------------------------------------------------------------------

 55    PD8               I/O    FT         PD8           FSMC_D13                            USART3_TX
 56    PD9               I/O    FT         PD9           FSMC_D14                            USART3_RX
 57    PD10              I/O    FT         PD10          FSMC_D15                            USART3_CK
 58    PD11              I/O    FT         PD11          FSMC_A16                            USART3_CTS
 59    PD12              I/O    FT         PD12          FSMC_A17                            TIM4_CH1/
                                                                                             USART3_RTS
 60    PD13              I/O    FT         PD13          FSMC_A18                            TIM4_CH2
 61    PD14              I/O    FT         PD14          FSMC_D0                             TIM4_CH3
 62    PD15              I/O    FT         PD15          FSMC_D1                             TIM4_CH4
-----------------------------------------------------------------------------

 63    PC6               I/O    FT         PC6           I2S2_MCK/TIM8_CH1                   TIM3_CH1
                                                         SDIO_D6
 64    PC7               I/O    FT         PC7           I2S3_MCK/TIM8_CH2                   TIM3_CH2
                                                         SDIO_D7
 65    PC8               I/O    FT         PC8           TIM8_CH3/SDIO_D0                    TIM3_CH3
 66    PC9               I/O    FT         PC9           TIM8_CH4/SDIO/D1                    TIM3_CH4
 -----------------------------------------------------------------------------

 67    PA8               I/O    FT         PA8           USART1_CK
                                                         TIM1_CH1 (7) /MCO
 68    PA9               I/O    FT         PA9           USART1_TX (7)/TIM1_CH2 (7)
                                                         
 69    PA10              I/O    FT         PA10          USART1_RX (7) /TIM1_CH3 (7)
 70    PA11              I/O    FT         PA11          USART1_CTS/USBDM USBDM = USB Data Minus，USB数据负信号；
                                                         CAN_RX (7) /TIM1_CH4 (7)
 71    PA12              I/O    FT         PA12          USART1_RTS/USBDP/USBDP = USB Data Positive，USB数据正信号
                                                         CAN_TX (7) /TIM1_ETR (7)
 72    PA13              I/O    FT         JTMS/SWDIO                                        PA13
-----------------------------------------------------------------------------

 73    未连接
 -----------------------------------------------------------------------------

 74    VSS_2             S      -          VSS_2
 75    VDD_2             S      -          V DD_2
 -----------------------------------------------------------------------------

 76    PA14              I/O    FT         JTCK/SWCLK                                        PA14
                                           

 77    PA15              I/O    FT         JTDI          SPI3_NSS/I2S3_WS                    TIM2_CH1_ETR
                                                                                             PA15/SPI1_NSS
-----------------------------------------------------------------------------

 78    PC10              I/O    FT         PC10          USART4_TX/SDIO_D2                   USART3_TX
 79    PC11              I/O    FT         PC11          USART4_RX/SDIO_D3                   USART3_RX
 80    PC12              I/O    FT         PC12          USART5_TX/SDIO_CK                   USART3_CK
-----------------------------------------------------------------------------

 81    PD0               I/O    FT         OSC_IN (8)    FSMC_D2 (9)                         CAN_RX
 82    PD1               I/O    FT         OSC_OUT (8)   FSMC_D3 (9)                         CAN_TX
 83    PD2               I/O    FT         PD2           TIM3_ETR/USART5_RX/SDIO_CMD
 84    PD3               I/O    FT         PD3           FSMC_CLK                            USART2_CTS
 85    PD4               I/O    FT         PD4           FSMC_NOE                            USART2_RTS
 86    PD5               I/O    FT         PD5           FSMC_NWE                            USART2_TX
 87    PD6               I/O    FT         PD6           FSMC_NWAIT                          USART2_RX
 88    PD7               I/O    FT         PD7           FSMC_NE1/FSMC_NCE2                  USART2_CK
 -----------------------------------------------------------------------------

 89    PB3               I/O    FT         JTDO          SPI3_SCK / I2S3_CK                  PB3/TRACESWO
                                                                                             TIM2_CH2/
                                                                                             SPI1_SCK

 90    PB4               I/O    FT         NJTRST        SPI3_MISO                           PB4/TIM3_CH1/
                                                                                             SPI1_MISO

 91    PB5               I/O    -          PB5           I2C1_SMBA/ SPI3_MOSI                TIM3_CH2/SPI1_MOSI
                                                         I2S3_SD
 
 “想用PB6 PB7 还使能FSMC时钟”，同时用作I2C和FSMC当然是不可能的，分时使用是可以的。
 如果打开了FSMC时钟，即使不用FSMC_NADV引脚，但是这个引脚还是默认成高电平；从而于I2C1_SDA冲突。
 92    PB6               I/O   FT          PB6           I2C1_SCL (7) /TIM4_CH1 (7)          USART1_TX
 93    PB7               I/O   FT          PB7           I2C1_SDA (7) /FSMC_NADV             USART1_RX
                                                         TIM4_CH2 (7) 
-----------------------------------------------------------------------------


 94    BOOT0             I     -           BOOT0
 -----------------------------------------------------------------------------

 95    PB8               I/O   FT          PB8           TIM4_CH3 (7) /SDIO_D4               I2C1_SCL/CAN_RX
 96    PB9               I/O   FT          PB9           TIM4_CH4 (7) /SDIO_D5               I2C1_SDA/CAN_TX
-----------------------------------------------------------------------------


 97    PE0               I/O  FT           PE0           TIM4_ETR/FSMC_NBL0
 98    PE1               I/O  FT           PE1           FSMC_NBL1
 -----------------------------------------------------------------------------

 99    VSS_3             S    -            VSS_3
 100   VDD_3             S    -            VDD_3




 使用FSMC后，STM32F103ZE的高位数据地址可以做IO口使用
 如果要使用某个管脚为FSMC功能，则配置对应的GPIO为复用输出功能；
 如果不使用它的FSMC功能，则只需配置对应的GPIO为普通输出功能(推挽或开漏)或输入功能即可。

 FSMC分为四个BANK，其中BANK1通过NE[1..4]可以片选四个外设，一般对于入门者来说主要看的就是BANK1的操作，
 比如NOR Flash和LCD的操作。这里我主要说BANK1的设置。
 对BANK1的操作主要是首先设置FSMC_BCRx[1..4]，FSMC_BTRx[1..4]和FSMC_BWTRx[1..4]寄存器，把这几个寄存器的意义弄明白了就基本好了：
 FSMC_BCRx是控制设置。
 FSMC_BTRx是读写时序设置。
 FSMC_BWTRx是写时序设置，具体内容与FSMC_BTRx相同。
 如果FSMC_BCRx[1..4]中设置了EXTMOD位, 则FSMC_BTRx[1..4]和FSMC_BWTRx[1..4]两个时序寄存器分别对应读、写操作。
 如果未设置EXTMOD位，则读和写使用相同的时序FSMC_BTRx[1..4]。



-----------------------------------------------------------------------------
I=输入  O=输出  S=电源   HIZ=高阻   FT=容忍5伏
TIM2_CH1_ETR表示可以配置功能为TIM2_TI1或者TIM2_ETR



LQFP48和LQFP64引脚定义(括号内的为48引脚的定义）
脚位  管脚名称            类型    I/O电平    主功能（复位后）        默认复用功能                        重定义功能
 1(1)		 VBAT					      s									 VBAT
 2(2)		 PC13-TAMPER-RTC		I/O								 PC13									TEMPER-RTC
 3(3)		 PC14-OSC32IN		    I/O								 PC14									OSC32-IN
 4(4)		 PC15-OSC32OUT		    I/O								 PC15									OSC32-OUT
 5(5)			PD0					I/O		 FT					 OSC_IN								can_rx
 6(6)			PD1					O		 FT					 OSC_OUT							can_tx
 7(7)			NRST				I/O		    				 NRST
 8			  PC0					I/O		 					 PC0									 ADC_IN10						 
 9				PC1					I/O		 					 PC1									 ADC_IN11
 10				PC2					I/O		 					 PC2									 ADC_IN12
 11				PC3					I/O		 					 PC3									 ADC_IN13
 12(8)    VSSA              S       VSSA
 13(9)    VDDA              S                  VDDA
14(10)		PA0-WKUP				I/O								 PA0									 WKUP/USART2_CTS/ADC_IN0/TIM2_CH1_ETR
                                                                       
																																			                                           
15(11)		PA1								I/O								 PA1										USART2_RTS/ADC_IN1
																																			/TIM2_CH2

16(12)		PA2								I/O								 PA2									  USART2_TX/ADC_IN2
																																			/TIM2_CH3

17(13)		PA3								I/O								 PA3									  USART2_RX/ADC_IN3
																																			/TIM2_CH4
18				VSS_4							 S								 VSS_4
19				VDD_4							 S								 VDD_4
20(14)		PA4								 I/O							 PA4									 SPI1_NSS/ADC_IN4
																																		 USART2_CK
21(15)		PA5								I/O			 					 PA5									 SPI1_SCLK/ADC_IN5

SPI的时钟不冲突，就可以，之前我是既开 spi的时钟，因为 这个PA6引脚既有SPI功能，又有 TIM3的 CH1 功能，如果 时能了SPI时钟，
然后实用的是TIM3 CH1 功能，那输出就不正确了。我停止了SPI时钟，就OK了。

22(16)		PA6								I/O				 				 PA6									 SPI1_MISO/ADC_IN6/TIM3_CH1
23(17)		PA7								I/O				 				 PA7									 SPI1_MOSI/ADC_IN7/TIM3_CH2
24        PC4								I/0								 PC4									 ADC_IN14
25        PC5								I/0								 PC5									 ADC_IN15
26(18)		PB0								I/O                PB0									 ADC_IN8/TIM3_CH3                    tim1_ch2n
27(19)		PB1								I/O                PB1									 ADC_IN9/TIM3_CH4			               tim1_ch3n
28(20)		PB2								I/O			FT				 PB2/BOOT1
29(21)    PB10							I/O			FT				 PB10									 I2C2_SCL/USART3_TX									 TIM2_CH3
30(22)    PB11							I/O			FT				 PB11									 I2C2_SDA/USART3_RX									 TIM2_CH4
31(23)		VSS_1							S									 VSS_1
32(24)		VDD_1							S									 VDD_1
33(25)		PB12							I/O			FT				 PB12									 SPI2_NSS/I2C2_SMBAI/USART3_CK /tim1_bkin
34(26)		PB13							I/O			FT				 PB13									 SPI2_SCK/USART3_CTS /tim1_ch1n
35(27)		PB14							I/O			FT				 PB14									 SPI2_MISO/USART3_RTS	/tim1_ch2n
36(28)		PB15							I/O			FT				 PB15									 SPI2_MOSI /tim1_ch3n
37		    PC6							  I/O			FT				 PC6																											 TIM3_CH1
38		    PC7							  I/O			FT				 PC7																											 TIM3_CH2
39		    PC8							  I/O			FT				 PC8																											 TIM3_CH3
40		    PC9							  I/O			FT				 PC9																											 TIM3_CH4
41(29)		PA8								I/O			FT				 PA8									 USART1_CK/MCO/tim1_ch1
42(30)		PA9								I/O			FT				 PA9									 USART1_TX /tim1_ch2
43(31)		PA10							I/O			FT				 PA10									 USART1_RX/tim1_ch3
44(32)		PA11							I/O			FT				 PA11									 USART1_CTS/USBDM/can_rx/tim1_ch4
45(33)		PA12							I/O			FT				 PA12									 USART1_RTS/USBDP/can_tx/tim1_etr
46(34)		PA13							I/O			FT				 JTMS/SWDIO																								 PA13
47(35)		VSS_2							S									 VSS_2
48(36)		VDD_2							S									 VDD_2
49(37)		PA14							I/O			FT				 JTCK/SWCLK																								 PA14
50(38)		PA15							I/O     FT				 JTDI																											 TIM2_CH1_ETR/PA15/SPI1_NSS
51     		PC10							I/O			FT				 PC10																							         USART3_TX
52     		PC11							S 			FT				 PC11																							         USART3_RX
53     		PC12							S 			FT				 PC12																							         USART3_CK
54     		PD2							  I/O 		FT				 PD2										TIM3_ETR													 
55(39)		PB3							  I/O     FT				 JTDO																											 TIM2_CH2/PB3 TRACESWO/SPI1_SCK
56(40)		PB4							  I/O     FT				 NJTRST																										 PB4/TIM3_CH1/SPI1_MISO
57(41)		PB5							  I/O       				 PB5										I2C1_SMBAI												tim3_ch2/spi1_mosi		
58(42)		PB6							  I/O     FT				 PB6										I2C2_SCL/TIM4_CH1									 USART1_TX
59(43)		PB7							  I/O     FT				 PB7										I2C2_SDA/TIM4_CH2									 USART1_RX
60(44)		BOOT0							I									 BOOT0
61(45)		PB8							  I/O     FT				 PB8										TIM4_CH3									         I2C1_SCL/can_rx
62(46)		PB9							  I/O     FT				 PB9										TIM4_CH4									         I2C1_SDA/can_tx
63(47)		VSS_3							S									 VSS_3
64(48)		VDD_3							S									 VDD_3


一个ARM程序包含3部分：RO，RW和ZI。RO是程序中的指令和常量；RW是程序中的已初始化变量;ZI是程序中的未初始化的变量.
由以上3点说明可以理解为：RO就是readonly，RW就是read/write，ZI就是zero

bss段：
BSS段（bsssegment）通常是指用来存放程序中未初始化的全局变量的一块内存区域。
BSS是英文BlockStarted by Symbol的简称。BSS段属于静态内存分配。

data段：
数据段（datasegment）通常是指用来存放程序中已初始化的全局变量的一块内存区域。数据段属于静态内存分配。

text段：
代码段（codesegment/textsegment）通常是指用来存放程序执行代码的一块内存区域。
这部分区域的大小在程序运行前就已经确定，并且内存区域通常属于只读,某些架构也允许代码段为可写，即允许修改程序。
在代码段中，也有可能包含一些只读的常数变量，例如字符串常量等。

rodata段：
存放C中的字符串和#define定义的常量

heap堆：
堆是用于存放进程运行中被动态分配的内存段，它的大小并不固定，可动态扩张或缩减。
当进程调用malloc等函数分配内存时，新分配的内存就被动态添加到堆上（堆被扩张）；
当利用free等函数释放内存时，被释放的内存从堆中被剔除（堆被缩减）

stack栈：
是用户存放程序临时创建的局部变量，也就是说我们函数括弧“{}”中定义的变量
（但不包括static声明的变量，static意味着在数据段中存放变量）。
除此以外，在函数被调用时，其参数也会被压入发起调用的进程栈中，并且待到调用结束后，函数的返回值也会被存放回栈中。
由于栈的先进先出特点，所以栈特别方便用来保存/恢复调用现场。
从这个意义上讲，我们可以把堆栈看成一个寄存、交换临时数据的内存区。


每个用户的任务都必须符合事件驱动的编程模型，即uC/OS-II的应用程序都必须是“事件驱动的编程模型”。
一个任务首先等待一个事件的发生，事件可以是系统中断发出的，也可以是其它任务发出的，又可以是任务自身等待的时间片。
当一个事件发生了，任务再作相应处理，处理结束后又开始等待下一个事件的发生。
如此周而复始的任务处理模型就是“事件驱动的编程模型”。事件驱动模型也涵盖了中断驱动模型，
uC/OS-II事件归根结底来自三个方面：
　　(1)中断服务函数发送的事件
　　(2)系统延时时间到所引起的
　　(3)其它任务发送的事件。
其中“中断服务函数发送的事件”就是指每当有硬件中断发生，那么中断服务程序就会以事件的形式告诉任务，
而等待该事件的最高优先级任务就会马上得以运行；“系统延时时间到所引起的”事件其实也是硬件中断导致的，
那就是系统定时器中断。而“其它任务发送的事件”则是由任务代码自身决定的，这是完全的“软事件”。不管“软事件”还是“硬事件”，
反正引起uC/OS-II任务切换的原因就是“事件”，所以用户编写应用代码的时候一定要体现出“事件驱动的编程模型”。
	exti_imr
		
RO是程序中的指令和常量
RW是程序中的已初始化变量
ZI是程序中的未初始化的变量
由以上3点说明可以理解为：
RO就是readonly，
RW就是read/write，
ZI就是zero 
					

*/




#include 	"includes.h"
#include 	"temp.h"
#include  "bsp.h"
#include  "BSTree.h"
#include  "usb_pwr.h"
#include  "usb_hw.h"
#include  "app.h"
#include  "stm32f10x.h"
#include  "motordrive.h"
#include  "iic_sw.h"
#include  "hd7279.h"
#include  "gps.h"
#include  "uart.h"
#include  "time.h"
#include  "motordrive.h"
#include  "mp3.h"
#include  "key.h"
#include  "ds3231.h"





#define PACK_STRUCT_BEGIN __packed
#define PACK_STRUCT_STRUCT 
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x

#define maxSize  10
#define hex2ascii(hex) ((hex)>=10?(hex)+55:(hex)+'0')
#define		ONESECTORLENGTH		512

 //#define		PROG_TEST_STA_FUNC


INT32U   NTP;















					// 文件系统相关的变量			
					BYTE  		buffer[ONESECTORLENGTH];// file copy buffer 
					
					INT8U		  SdCardMessage[16];	
					mytime 		hms_variant[5];
					mytime 		*p_timemu=&hms_variant[0];	
					mytime 		*p_timeslave;
					
					
					BOOLEAN		MainUsart2NoRxdFlag;
					BOOLEAN		MainBsOnOffStatusFlag;
					BOOLEAN		MainBsJsValidFlag;
					BOOLEAN		MainBsStartFlag;
					INT8U		  MainBsPayOrXms;
					INT8U		  MainBsKnockCnt;
			
					OS_EVENT 	*Mutex_USART1; // 定义USART1互斥型事件	
					OS_EVENT 	*Mutex_USART2; // 定义USART2互斥型事件
					OS_EVENT 	*Mutex_FATFS;  // 定义FATFS互斥型事件		
					BOOLEAN 	ShowDirfiles(char *path);			
					void 		  VS1003_Reset(void);
					void 		  StartMp3Ring(void);
					void 		  MP3_Play(void);	


					OS_EVENT	*pMainMotorSemEve,*pMainBsSemEve;
					INT8U     *pMainProcess;
          INT8U     StartEraseNandFlag;
				

					INT8U 		pps1_rising_sig = 0;
					INT8U 		pps1_falling_sig = 0;
					INT8U 		pps1_status;
					INT8U 		pps1_tim = 0;   
					INT8U 		pps1_status = 0;
          INT8U		  TimeDisValidFlag;


					

extern    INT8U 		uart1_rx_sig;
extern    config 		board;
extern 		gps_info 	gps ;
extern    INT8U 	  Uart1_Rx_Buf[UART1_RX_SIZE];





static	  void      GPIO_Motor_Config(void);
static	  void      GPIO_I2C_Config(void);

static	  void      GPIO_Key_Config(void);
static	  void      N31_pps_init(void);


static  	OS_STK 		App_TaskStartStk[APP_TASK_START_STK_SIZE];  // TaskStart 任务堆栈 
static  	OS_STK 		AppTask1Stk[APP_TASK1_STK_SIZE];//  任务堆栈 
static  	OS_STK 		AppTask2Stk[APP_TASK2_STK_SIZE ]; //AppTaskUsart2任务堆栈 
static  	OS_STK 		AppTask3Stk[APP_TASK3_STK_SIZE ]; //AppTaskUsart3任务堆栈 
static  	OS_STK 		AppTask4Stk[APP_TASK4_STK_SIZE ]; //AppTaskUsart4任务堆栈 
static  	OS_STK 		AppTask5Stk[APP_TASK5_STK_SIZE ]; //AppTaskUsart5任务堆栈 
static  	OS_STK 		AppTask6Stk[APP_TASK6_STK_SIZE ]; //AppTaskUsart6任务堆栈 
static  	OS_STK 		AppTask7Stk[APP_TASK7_STK_SIZE ]; //AppTaskUsart7任务堆栈 
static  	OS_STK 		AppTask8Stk[APP_TASK8_STK_SIZE ]; //AppTaskUsart7任务堆栈 




static  	void  		App_TaskStart(void* p_arg);          // 声明 TaskStart 函数
static  	void  		AppTask1(void* p_arg);      // 声明 TaskPrintf 函数
static  	void 		  AppTask2(void* p_arg);        // 声明 测量CPU频率的函数
static    void      AppTask3(void* p_arg);
static    void      AppTask4(void* p_arg);
static    void      AppTask5(void* p_arg);
static    void      AppTask6(void* p_arg);
static    void      AppTask7(void* p_arg);
static    void      AppTask8(void* p_arg);

void EnterEastNormalRun(void);
void EnterSouthNormalRun(void);
void EnterWestNormalRun(void);
void EnterNorthNormalRun(void);

void  EnterEastFzRun(void);
void  EnterSouthFzRun(void);
void  EnterWestFzRun(void);
void  EnterNorthFzRun(void);









static		void 		  LED1234_ON_OFF(CPU_INT08U Num);             // 声明流水灯函数
extern		BOOLEAN		Vs1003bPowOnFlag;
extern		INT8U 		USART2_RX_FIFO[USART2_RX_CNT];  		        // 定义环形数据
extern		void 		  DelayMs(vu32 m);
extern		void 		  DelayUs(vu32 m);	


extern    void DemoFatFS(uint8_t *cmd);
extern		INT8U 	USART1_RX_FIFO[USART1_RX_CNT];  			// 定义环形数据
extern		INT8U 	*pPut_USART1_RX_FIFO ; 	// 定义环形数组放数指针
extern		INT8U 	*pGet_USART1_RX_FIFO ; 	// 定义环形数组取数指针



void MainSwapValue(INT16U *p1,INT16U *p2);//直接交换了地址里面的内容，也就是值！！
void MainSwapValueErr(volatile INT16U *p1,volatile INT16U *p2);//直接交换了地址里面的内容，也就是值！！
void MainSwapAddr(INT16U **p1,INT16U **p2);//要交换内容，间接用交换地址来实现。
void  BspNand_Init(void);
void LedBsZm_Init(void);
void Mp3Drive_Init(void);

void LedPortSpecialInit(void);
void MainProcessTimeAdd(config data,INT8U order);
void MainProcessTimeSub(config data,INT8U order);


/*
*********************************************************************************************************
                                                main()
												RE:__use_two_region_memory与macro-lib什么关系？
_use_two_region_memory用于指定存储器模式为双段模式，即一部分储存区用于栈空间，其他的存储区用于堆空间，堆区空间可以为0，
但是，这样就不能调用malloc()内存分配函数；堆区空间也可以由存储器分配，也可以从执行环境中继承。
*********************************************************************************************************
*/


//在2015年11月30日用一个光耦，一个200R电阻，一个10k上拉电阻解决了5伏单片机母钟和3.3伏arm单片机之间的rs485通讯的问题！
//该版本的软件在usart2中接收一个字节后便进入任务3中，在任务中处理报时，虽然可以不太保险，恐怕漏报！
//因为主板5伏通讯板和arm板通讯涉及到的供电电源问题，RS485通讯不可靠，我在2015年12月2日将
//ARM板上的通讯芯片75LBC184的第六脚（A）添加一个10K的上拉电阻，第七脚（B）添加一个10K的下拉电阻后



//解决了两块板卡通讯不可靠的问题，解决了ARM板插到连接板上后用仿真器仿真不了的问题。！！
//我试验了vs1003芯片，发现温度比较烫，添加报时结束后，文件关闭，他也关闭！在每个小时58分的时候复位vs1003准备播放mp3文件
//播放完毕后该芯片处于掉电状态！
//将该程序作为最终成品程序给刘了！！

/*
第一部分实现顺序表的操作
已知一个顺序表，其中的元素递增有序排列，设计一个算法，插入一个元素x（x为int型）后保持该顺序表仍然递增有序排列（假设总能成功）
实现方法：
1，找到比x大的第一个元素的位置，函数返回该位置
2.
*/


PACK_STRUCT_BEGIN
typedef struct
{
	INT8U data[maxSize];
	INT8U length;//遗留一个问题，为什么该变量得值变为了0!!
}Sqlist;       //考察了顺序表的插入，删除等
PACK_STRUCT_END
Sqlist *q;
Sqlist *p;
 

//单链表的操作
//head1和head2是两个递增的单链表，设计一个算法，将head1和head2归并到一个链表head3中
//使着head3递增有序，
typedef struct LNode
{
	INT8U data;
	struct LNode *next;
}LNode;

//LNode MainLnode1;
//LNode MainLnode2;
//LNode *MainLnode3;
//void MainMerge(LNode *head1,LNode *head2,LNode **head3);


/*
//下述代码演示了如何创建BST二叉树
typedef struct Node
{
	struct Node *left;
	struct Node *right;
	size_t size;  //数据的空间大小
	INT8U  data[];//数据本身
}Node_t;
//必须提供两个辅助的函数，第一个用来得到“对应于数据”的键值；第二个用来比较两个键值
typedef const void *GetKeyFunc_t (const void *dData);//第一个函数具有如下原型
//第二个函数类似于标准函数bsearch（）所使用的“比较函数”
typedef INT16U CmpFunc_t(const void *pKey1,const void *pKey2);
//调用比较函数时所传递的自变量，是指向两个“计划比较”的键值得指针。此函数的返回值小于0，表示第一个键值小于第二个键值；
//等于0，表示两个键值相等；大于0，表示第一个键值大于第二个键值；
//接下来，我们定义一个结构类型，用来代表一个树，此机构有三个成员：
//指向树根的指针
//指向计算键值得指针（类型为GetKeyFunc_t)
//指向比较函数的指针（类型为CmpFunc_t)

typedef struct {
	struct Node *pRoot;  //指向树根的指针
	CmpFunc_t *cmp;      //比较两个键值
	GetKeyFunc_t *getKey;//将数值变为键值
}BST_t;
*/

typedef struct BSTNode
{
	INT32U data;
	struct BSTNode *left;
	struct BSTNode *right;
}BSTNode;

struct BSTNode *createnode(INT32U data)//将节点的数据项对比后插入二叉树中
{
	struct BSTNode *n1=(struct BSTNode *)malloc(sizeof(struct BSTNode));
	n1->data=data;
	n1->left=NULL;
	n1->right=NULL;
	return n1;
}

void insertnode(struct BSTNode **proot,struct BSTNode *n)
{
	struct BSTNode *temp=*proot;
	
	if(temp==NULL)
		*proot=n;
	else{
		if(n->data<temp->data)			
		   insertnode(&(temp->left),n);				
		else	if(n->data>temp->data)		
			 insertnode(&(temp->right),n);		
		//pBstRoot=*proot;
		//pBstRoot=n;
		//pBstRoot=(struct BSTNode *)&proot;
	}
}



INT8U compare(void)
{
	static u8 a=10,b=10;
	return(a==b);
}	

INT32U   MainArray1[3]={7,8,9};
INT32U   MainArray2[3]={4,5,6};
INT32U   *My;

typedef INT32U * (*MainFunc)(INT8U  data1,INT8U  data2);

INT32U  *Test1(INT8U  data1,INT8U  data2)
{
	INT8U  a,b;
	a=data1;
	b=data2;
	return ((a>b)?MainArray1:MainArray2);	
	//return((a>b)?9:8);
}


//https://blog.csdn.net/qq_41028985/article/details/82859199---参考网址，涉及到单链表的头插法和尾插法！！
//http://blog.sina.com.cn/s/blog_c689bd6c0102wvdd.html---C99的一些特征
typedef struct myNode {
	INT8U data;                // 存储链表数据
	struct myNode *next;     		//  存储结点的地址
}myLNode,*Linklist;

//在进入创建链表之前，我们先写好主函数的用来输出的输出函数。
void Illustrate(Linklist head) {
	Linklist tem = head;              //  将头指针的地址赋给临时的指针
	while (tem->next != NULL) {       //  指向最后一个结点的指针域时会停止
		tem = tem->next;                //  结点不断向后移动
		//printf("%d\n", tem->data);
		//USART1_Printf(&(hex2ascii(tem->next)));
		//USART1_Printf(&tem"->data);
		printf("\r\n %d",tem->data);
		
	}
}

//头插法代码：
Linklist HeadInsert_List(Linklist head) {
	INT8U i;//注意：变量声明不允许出现在语句之后，否则提示出现 error！
	myLNode *mynode = NULL;                  //  定义新结点
	
	INT16U count = 16;                        //  创建结点的个数
	head = (Linklist)malloc(sizeof(myLNode));//  为头指针开辟内存空间
	head->next = NULL; 
			             
	mynode = head->next;              	       //  将最后一个结点的指针域永远保持为NULL
	printf("\r\n 以下显示头插法插入的顺序为: ");	
	for ( i = 0; i < count; i++) {
		mynode = (Linklist)malloc(sizeof(LNode));//  为新结点开辟内存空间
		mynode->data = i;                        //  为新结点的数据域赋值
		mynode->next = head->next;               //  将头指针所指向的下一个结点的地址，赋给新创建结点的next 
		head->next = mynode;                     //  将新创建的结点的地址赋给头指针的下一个结点
	}
	return head;//必须有返回值，为了从单链表头部输出数据；added by sjw
}
//头插法创建链表的根本在于深刻理解最后两条语句
//mynode->next = head->next;    //  将头指针所指向的下一个结点的地址，赋给新创建结点的next 
//head->next = mynode;          //  将新创建的结点的地址赋给头指针的下一个结点


//尾插法代码：
Linklist TailInsert_List(Linklist head) {
  INT16U  count = 16 ;                 //  结点个数
	INT16U  i;
	Linklist node = NULL;           //  定义结点
	Linklist tailer = NULL;            //  定义尾结点
	
	head = (Linklist)malloc(sizeof(LNode));          //  为头指针开辟内存空间
	head->next = NULL;              //  初始化头结点指向的下一个地址为 NULL
	tailer = head;                     //  未创建其余结点之前，只有一个头结点
	
	printf("\r\n 以下显示尾插法插入的顺序为: ");
	for (i = 0; i < count; i++) {
		node = (Linklist)malloc(sizeof(LNode));          //  为新结点开辟新内存
		node->data = i;                                  //  新结点的数据域赋值
		tailer->next = node;                      		
		tailer = node;
	}
	tailer->next = NULL;
	return head;//必须有返回值，为了从单链表头部输出数据；added by sjw
}
//尾插法深刻理解如下两句：
//end->next = node;                      		
//end = node;



const 	uint8_t   *pmp3tabel[26]={
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3", 
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3",
		
	  "MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3", 
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3",
		
		
	};
	

Linklist phead = NULL;            //  链表的头指针
INT8U MainFindElem(Sqlist L,INT8U x);//本函数返回第一个比x值大的元素的位置
void   MainInsertElem(Sqlist *L,INT8U x);
Sqlist MainArray;

extern void     NAND_OutBadBlockInfo(void);
extern	void    FSMC_NAND_Test(void);
extern uint8_t   FSMC_NAND_ReadData(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount);
//extern void NAND_DispLogicPageData(uint32_t _uiLogicPageNo);
extern  uint32_t NAND_FormatCapacity(void);
//extern  uint8_t FSMC_NAND_WriteData(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount);
extern  uint8_t FSMC_NAND_WritePage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount);
extern  uint8_t FSMC_NAND_ReadPage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount);
extern  uint8_t FSMC_NAND_EraseBlock(uint32_t _ulBlockNo);
extern  void	 FSMC_NAND_TestRead(void);


void 	NoKeyProm(void);
void 	KeyProm1(void);
void 	KeyProm2(void);
void 	KeyProm3(void);
void 	KeyProm4(void);
void 	KeyProm5(void);
void 	KeyProm6(void);
INT8U	ReadKey(void);


//函数指针数组定义及附初值！
void (*KeyProcTab[])()={NoKeyProm,KeyProm1,KeyProm2,KeyProm3,KeyProm4,KeyProm5,KeyProm6};
float *find(float(*pionter)[4],int n);//函数声明 

/*
//float(*pionter)[4]   比如  int (*p)[10]; p即为指向数组的指针，又称数组指针。
int Func(int x);        //声明一个函数
int (*p) (int x);       //定义一个函数指针
p = Func;               //将Func函数的首地址赋给指针变量p

1.定义函数指针类型：
typedef int (*fun_ptr)(int,int);    
2.声明变量，赋值：                                   typedef
fun_ptr max_func=max;
也就是说，赋给函数指针的函数应该和函数指针所指的函数原型是一致的


STM32f103VE寄存器--定义篇
https://www.it610.com/article/1294459351842496512.htm
*/


extern uint16_t  TestCount;
extern uint8_t  TestCountHL[2];
extern  uint8_t do_erase_nandflash(uint32_t _ulBlockNo);



//ECC算法的实现
//深入浅出NandFlash里的ECC校验算法原理与实现(1)
//https://blog.csdn.net/qwe5959798/article/details/116481300   此文章非常好，理解ECC
//网上关于NandFlash的ECC校验文章很多，但没有一个深得我心。
//深入浅出NandFlash里的ECC校验算法原理与实现(2)
//https://blog.csdn.net/qwe5959798/article/details/121931611   





struct FAT32_DBR
{
unsigned char BS_jmpBoot[3];     	//跳转指令offset: 0
unsigned char BS_OEMName[8]; 			// offset: 3
unsigned char BPB_BytesPerSec[2];	//每扇区字节数offset:11
unsigned char BPB_SecPerClus[1]; 	//每簇扇区数offset:13
unsigned char BPB_RsvdSecCnt[2]; 	//保留扇区数目offset:14
unsigned char BPB_NumFATs[1]; 		//此卷中FAT 表数offset:16
unsigned char BPB_RootEntCnt[2]; 	//FAT32 为0 offset:17
unsigned char BPB_TotSec16[2]; 		//FAT32 为0 offset:19
unsigned char BPB_Media[1]; 			//存储介质offset:21
unsigned char BPB_FATSz16[2]; 		//FAT32 为0 offset:22
unsigned char BPB_SecPerTrk[2]; 	//磁道扇区数offset:24
unsigned char BPB_NumHeads[2]; 		//磁头数offset:26
unsigned char BPB_HiddSec[4]; 		//FAT 区前隐扇区数offset:28
	
	
unsigned char BPB_TotSec32[4]; 		//该卷总扇区数offset:32
unsigned char BPB_FATSz32[4]; 		//一个FAT 表扇区数offset:36
unsigned char BPB_ExtFlags[2]; 		//FAT32 特有offset:40
unsigned char BPB_FSVer[2]; 			//FAT32 特有offset:42
unsigned char BPB_RootClus[4]; 		//根目录簇号offset:44
unsigned char FSInfo[2]; 					//保留扇区FSINFO 扇区数offset:48
unsigned char BPB_BkBootSec[2]; 	//通常为6 offset:50
unsigned char BPB_Reserved[12]; 	//扩展用offset:52
unsigned char BS_DrvNum[1]; 			// offset:64
unsigned char BS_Reserved1[1]; 		// offset:65
unsigned char BS_BootSig[1]; 			// offset:66
unsigned char BS_VolID[4]; 				// offset:67
unsigned char BS_FilSysType[11]; 	// offset:71
unsigned char BS_FilSysType1[8]; 	//"FAT32 " offset:82
};


struct FAT32_Init_Arg
{
unsigned char BPB_Sector_No; //BPB 所在扇区号
unsigned long Total_Size; //磁盘的总容量
unsigned long FirstDirClust; //根目录的开始簇
unsigned long FirstDataSector; //文件数据开始扇区号
unsigned int BytesPerSector; //每个扇区的字节数
unsigned int FATsectors; //FAT 表所占扇区数
unsigned int SectorsPerClust; //每簇的扇区数
unsigned long FirstFATSector; //第一个FAT 表所在扇区
unsigned long FirstDirSector; //第一个目录所在扇区
unsigned long RootDirSectors; //根目录所占扇区数
unsigned long RootDirCount; //根目录下的目录与文件数
};

/*
void FAT32_Init(struct FAT32_Init_Arg *arg)
{
		struct FAT32_BPB *bpb=(struct FAT32_BPB *)(FAT32_Buffer);//将数据缓冲区指针转为struct FAT32_BPB 型指针
		arg->BPB_Sector_No =FAT32_FindBPB();//FAT32_FindBPB()可以返回BPB 所在的扇区号
		arg->Total_Size =FAT32_Get_Total_Size();//FAT32_Get_Total_Size()可以返回磁盘的总容量，单位是兆
		arg->FATsectors =lb2bb((bpb->BPB_FATSz32) ,4);//装入FAT 表占用的扇区数到FATsectors 中
		arg->FirstDirClust =lb2bb((bpb->BPB_RootClus) ,4);//装入根目录簇号到FirstDirClust 中
		arg->BytesPerSector =lb2bb((bpb->BPB_BytesPerSec),2);//装入每扇区字节数到BytesPerSector 中
		arg->SectorsPerClust =lb2bb((bpb->BPB_SecPerClus) ,1);//装入每簇扇区数到SectorsPerClust 中
		arg->FirstFATSector=lb2bb((bpb->BPB_RsvdSecCnt) ,2)+arg->BPB_Sector_No;//装入第一个FAT 表扇区号到FirstFATSector 中
		arg->RootDirCount =lb2bb((bpb->BPB_RootEntCnt) ,2);//装入根目录项数到RootDirCount 中
		arg->RootDirSectors =(arg->RootDirCount)*32>>9;//装入根目录占用的扇区数到RootDirSectors 中
		arg->FirstDirSector=(arg->FirstFATSector)+(bpb->BPB_NumFATs[0])*(arg->FATsectors);//装入第一个目录扇区到FirstDirSector 中
		arg->FirstDataSector =(arg->FirstDirSector)+(arg->RootDirSectors);//装入第一个数据扇区到FirstDataSector 中
}



FATFS文件移植的debug问题（非常好）
http://www.360doc.com/content/18/0530/06/6889381_758125759.shtml

*/





 static u8   *(*CopyData[10])(u16 Length);
 u8 *my;

 static u8   *(see)(u16 sjw)
{
	
	u16 temp=sjw;
	return my;
}
//没有    数组指针函数     这一个概念，因为指针补鞥既指向数组又执行函数！！！
//但是有  函数指针数组     这一个概念，用它来实现散转指向特别方便！！
u16 MainTestArray[10][10];
u16 (*pMainTestArray)[10]=MainTestArray;
	
//该程序能实现上电后即开始播放SD卡内的文件功能！播放“西敏寺”后即开始播放12下语音的功能！！
//此程序将外部+12伏接上后，上电能够开始通过vs1003实现放音功能！！如果不能出来声音，更换一块核心板即可！
//振南对WAV音频格式深入剖析(ADPCM编码) 对VS1003录WAV及解码有用      https://bbs.21ic.com/icview-1604404-1-1.html


//stm32-USART1重映射   参考网址：https://blog.csdn.net/qinrenzhi/article/details/81875348
//STM32F103 FSMC详解以及驱动LCD的应用   参考网址：https://blog.csdn.net/weixin_30918415/article/details/98433064
//FSMC机制       参考网址：http://blog.sina.com.cn/s/blog_7880d3350101ih1z.html


/*
目的：将K9F1208作为一个U盘，实现往里面copy文件的目的！！之后收到网络核心板指令后，按要求播放U盘里面的文件！！
学习将FATFS移植到NandFlash（K9F1208）内的过程记录
1.https://blog.csdn.net/cwcwj3069/article/details/7882978
u盘  理解了DBR （dos boot record)和BPB(bois parameter block)
          MBR(main boot record)几个名词的意义，有意思
2.NAND_FLASH(K9F1208U0C)驱动分析
https://blog.csdn.net/lshiceman/article/details/37929167

3.STM32 FSMC NAND控制器 驱动NAND FLASH 注意事项
https://blog.csdn.net/qq_15404645/article/details/80911266

4.fatfs文件系统详解之f_mkfs函数分析
https://blog.csdn.net/agony_isolate/article/details/106243899

5.https://blog.csdn.net/qq_44884287/article/details/89517209
nand flash结构以及读写分析——写的比较经典（转载）


6. VBR (Volume Boot Record) or PBR (Private Boot Record), 
FAT 卷中最重要的数据结构是 BPB（BIOS Parameter Block，BIOS 参数块），其中存储 FAT 卷的配置参数。 
BPB 位于引导扇区中。 引导扇区通常称为 VBR（Volume Boot Record，卷引导记录）或 PBR（Private Boot Record，专用引导记录），
但它只是保留区域的第一个扇区，即卷的第一个扇区。
  https://dandelioncloud.cn/article/details/1460588983884529666
	此网站的内容详细解释了文件系统的一个扇区字节的含义，特别有参考价值！added by sjw
	
	
7.网上发现得一篇写磁盘扇区得文章（值得一看）
http://blog.chinaunix.net/uid-8613773-id-2018359.html

8.//我在2022-7-19日将此宏变为1使能！！
在文件ffconf.h的第164行上！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！


9.C++ f_mount函数代码示例
https://vimsky.com/examples/detail/cpp-ex-----f_mount-function.html

10.FatFs模块功能配置选项 
	https://blog.51cto.com/u_15294654/3112876
	a.功能配置
	b.命名空间和本地环境配置
	c.卷/驱动器配置
	d.系统配置
	
11.fatfs网站：
	http://elm-chan.org/fsw/ff/00index_e.html

12.将FATFS移植STM32RBT6遇到的挂载不成功和返回值问题
http://www.eepw.com.cn/article/201611/322277.htm

原来在定义FATFS *FS;是需要分配内存的，据说空间分配有两种方式一个是数组，另一个是定义指针，
定义指针时要使用malloc分配内存还要free释放内存，而我定义了fatfs结构的指针没有分配内存，
造成返回值FR_NO_FILESYSTEM,// (13) There is no valid FAT volume ，后来我改成fatfs fs;

 
   1block=(512+16)bytes x 32pages
   4096block
   A[23:14][13:9]
   block   page
*/







	 
  INT32U  BigOrSmallValue=0x12345678;
  INT32U  *pBigOrSmallValue=&BigOrSmallValue;
	 INT32U  **ppBigOrSmallValue=&pBigOrSmallValue;
  extern void  SumsungTestEcc(void);

extern  uint8_t  UsartRxBuf[USART_REC_LEN];

					INT8U		  SdCardMessageInfo[16];	
extern  uint8_t    ItWaitFlag;




/*
	注意；在文件stm32f10x_fsmc.c中提示出四个错误（此文件已经被“火牛”下同名文件代替，就是为了实现FlashWriteOneSector  FlashReadOneSector）
	第183行被我屏蔽
	第205行被我屏蔽
	第385行被我屏蔽

	注意都解决好后，需要打开此屏蔽！
	
	
		
2.	https://blog.csdn.net/chengdong1314/article/details/81369601
    STM32 USB的枚举过程简介   此文介绍的非常好！满足我一步一步枚举时候发生的动作的观察愿望！！
	
		
3.  https://blog.csdn.net/dierui2904/article/details/101759783  
	此网站的内容非常不错，用它来做参考我理解开发USB肯定没有问题   按照提示操作，格式化不成功，可用磁盘空间和已用磁盘空间都为0。
	以下这个网站非常和我进行开发相似！非常可以借鉴！！
4.  http://www.javashuo.com/article/p-ybcbwxvw-ky.html


5.FatFs文件系统Nandflash驱动函数详解
https://www.likecs.com/show-204034824.html

6.可怕的问题：FATFS f_open() 返回可怕的 FR_NO_FILESYS
https://bbs.21ic.com/icview-619554-1-1.html

7.STM32 文件系统 fatfs 移植笔记详解   MBR和DBR通过0扇区的数据解释特别到位！！
https://blog.51cto.com/u_15284384/3052087

8.将文件的第110行修改为第113行上，明显的看到是FATFS32的类型了，并且仿真fs的数据都看着靠谱
	
	*/

//1 SPI的基本介绍   https://blog.csdn.net/qq_39792063/article/details/120942630
//此文介绍的很形象！
//将文件SD_driver.c用文件夹nand_fatfs010b_noOS_TF下的文件代替（先验证好用的）之后，不会出现stm32f10x_spi.c的第170行上的警告了！
//另外跳转到   B       HardFaultException  是因为宏指令 OS_ENTER_CRITICAL();和 OS_EXIT_CRITICAL();的乱用造成的















































































































































































































































































































































































































































































































































































































































































































































































































































































































































/*
24C02,256  ×8(2K bits)- 
24C04,512  ×8(4K bits)- *16byte??????????????????????????
24C08,1024 ×8(8K bits)-
24C16,2048 ×8(16K bits)- 
24C32,4096 ×8(32K bits)- 
24C64,8192 ×8(64K bits)-

页写:8字节页(24C02),16字节页(24C04/08/16),32字节页(24C32/64)可按字节，随机和序列读
高可靠性擦写寿命:100万次-数据保持时间:100年



STM32F105、107RB使用外部晶振8M时配置外设时钟为72M

https://www.cnblogs.com/tlazy-12138/p/17619353.html




备注1：该软件的核心密码为“450706”，只有输入正确的密码后，才会成为
			 合法用户，任何操作都不受限制！ (2008/8/28上午设定的密码)
备注2：该软件共有6个键盘（包括复位键）分别为：
      “状态”  “位选”  “加”  “减”	  KY0 与RL0,RL1,RL2,RL3
			“启/停” “蓄电池”                  KY1 与RL0,RL1		



当前的嵌入式应用程序开发过程里，C语言已成为了绝大部分场合的最佳选择。如此一来main函数似乎成为了理所当然的起点——因为C程序往往从main函数开始执行。
但一个经常会被忽略的问题是：微控制器（单片机）上电后，是如何寻找到并执行main函数的呢？很显然微控制器无法从硬件上定位main函数的入口地址，
因为使用C语言作为开发语言后，变量/函数的地址便由编译器在编译时自行分配，这样一来main函数的入口地址在微控制器的内部存储空间中不再是绝对不变的。
相信读者都可以回答这个问题，答案也许大同小异，但肯定都有个关键词，叫“启动文件”，用英文单词来描述是“Bootloader”。

无论性能高下，结构简繁，价格贵贱，每一种微控制器（处理器）都必须有启动文件，
启动文件的作用便是负责执行微控制器从“复位”到“开始执行main函数”中间这段时间（称为启动过程）所必须进行的工作。
最为常见的51，AVR或MSP430等微控制器当然也有对应启动文件，但开发环境往往自动完整地提供了这个启动文件，不需要开发人员再行干预启动过程，
只需要从main函数开始进行应用程序的设计即可。



UC/OS-III学习——触发PendSV中断
https://www.itxm.cn/post/ajffea1a1.html


移植ucosii遇到的问题 B OSStartHang
https://blog.csdn.net/special00/article/details/73929966
其实很简单，因为STM32本身的异常中断PendSV_Handler替代了UCOS的异常中断OSPendSV，使其不能正常执行。
这样我们就需要更改PendSV_Handler为OSPendSV以让中断正常。



STM32-端口复用和重映射
https://blog.csdn.net/qq_39792063/article/details/120565875
此文章解释的相当详细，非常不错，是操作STM32f10x的利器！！added by sjw



cl：互联型产品，    	stm32f105/107系列
vl：超值型产品，    	stm32f100系列
xl：超高密度产品，		stm32f101/103系列
ld：低密度产品，				FLASH小于64K
md：中等密度产品，			FLASH=64 or 128
hd：高密度产品，				FLASH大于128

IO端口复位后处于浮空状况，也便是其电平状况由外围电路决议，这很重要，假如规划工业品的话，这是必需要确认的；
─ 输入浮空
─ 输入上拉
─ 输入下拉
─ 模拟输入

─ 开漏输出
─ 推挽式输出
─ 复用推挽式
─ 复用开漏功用


STM32时钟初始化函数SystemInit()详解
https://blog.csdn.net/xuzhexing/article/details/90380971

*/
#define   CLOSE_MINUTE  2

			
	
//#define strcpy Unsafe_strcpy



INT8U  Time_Modify[6]={0x00,0x00,0x00,0x00,0x02,0x01}; //母钟时间修改缓存
INT8U  Mp3_Ok=0,Mp3_Error=0;       //MP3发送命令成功

void Light_Control(void);
void Time_Notice(void);
void  Key_Operation(void);
 void Menue_Mastertime(void);
void SPI1_Init (void);
INT8U SPIx_ReadWriteByte(INT8U TxData);

INT8U  LightSlotFlag;
INT16U LightSlotValue;

extern  INT8U     IntDisFlag;

extern  const INT8U   Volume[6];
extern const INT8U Rythem_Name[15]; 
extern INT16U Strike_Head[8];

extern INT8U  Rythem_Number,Strike_Number; 
extern INT8U  Rythem_Second[15];
extern INT8U  Rythem_Minite[15];
	
extern	INT8U  Rythem_Number,Strike_Number;
  
extern INT8U Report_Time[24];
extern enum _useKey   KeyState;

extern INT8U   receive_data[UART1_RX_SIZE];
extern INT8U   isLinear(INT32U data);
extern  void set_pps1_sig(void);



extern  void MathEastSub_Qd220(mytime * ux);
extern  void MathEastAdd_Qd220(mytime * ux);
extern  INT8U  MotorZZ_Flag,MotorFZ_Flag,MotorStop_Flag;

INT8U  PowerOnFLag=1;
INT8U  Key_Time;
INT8U  Light_En=1;                       //照明使能  
INT8U  Light_Start=19,Light_End=6;       //照明时间段
INT8U  Rythem_Number=8,Strike_Number=7;  //报时音乐号，钟声号	

INT8U   MotorActFlag;
INT8U  ReadKey_Value=0xff;               //读到的键值
//GPS模块调试成功，目前执行isLinear(_ntp)后跳入HardFault_Exception!!
//键盘接口及显示都调试成功！
//DS3231模块调试成功！
//电机驱动及电机反馈模块调试成功！
//报时模块已经调试成功！！
extern enum   KeyRun_Order Key_Subclock_State1;
extern uint8_t    ItWaitFlag3;


extern INT8U compare_zf(mytime *u,  mytime *v);

 
int main(void)
{ 
		
	OS_CPU_SR  cpu_sr;	
	struct FAT32_DBR  *pSector;
	INT32U 		base,offset;
	INT8U err;	
	
	

	#if 0
		INT32U sect=ApplicationAddress;
		RCC_DeInit();
		NVIC_DeInit();
		base=(sect>NVIC_VectTab_FLASH)? NVIC_VectTab_FLASH : NVIC_VectTab_RAM;//中断向量表的基地址
		offset=sect-base;	             	//中断向量表的偏移	
		#ifdef VECT_TAB_RAM
		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);// Set the Vector Table base location at 0x20000000
		#else
		NVIC_SetVectorTable(base,offset);	//重新定位中断向量表
		#endif	
	#endif
	 
	 
	
	
	  //DelayMs(12000);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//初始化中断向量   设置系统中断优先级分组		
	  OS_CPU_SysTickInit();
    #if (OS_TASK_STAT_EN > 0)// 统计任务 
			OSStatInit(); 
	  #endif	
		
		OSInit();
    OSTaskCreateExt( App_TaskStart, 
										 (void *) 0, 
	                   (OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                   	 APP_TASK_START_PRIO,
                     APP_TASK_START_PRIO, 
	                   (OS_STK *) &App_TaskStartStk[0], 
	                   APP_TASK_START_STK_SIZE , 
	                   (void *) 0, 
	                   OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );
    OSStart();
}


/*
	phead = HeadInsert_List(phead);  //  创建链表
	Illustrate(phead);               //  输出每个结点的数据域
	phead = TailInsert_List(phead);
	Illustrate(phead);               //  输出每个结点的数据域

系统的第一个任务，负责开OS时钟，建立其他任务
RO是程序中的指令和常量
RW是程序中已经初始化的变量
ZI是程序中已经没有初始化的变量
*********************************************************************************************************
*/
static  void App_TaskStart(void* p_arg)
{
	OS_CPU_SR  cpu_sr;	
	INT8U 	err;
	static	INT32U 	i=0,j=0; 	
	INT16U 	count=0; 
	INT16U 	js=20;
	static	INT16U	vs1003status[5],vs1003testram,value;
	static	INT16U status,status1,status2,mp3Time;
	
	
			
			
			
		 OS_ENTER_CRITICAL();
	
	
     OSTaskCreateExt(  AppTask1, //  建立第1个任务 	
										  (void *) 0, 
										  (OS_STK *) &AppTask1Stk[APP_TASK1_STK_SIZE- 1],
										  APP_TASK1_PRIO,
                      APP_TASK1_PRIO,
										  (OS_STK *) &AppTask1Stk[0],
										  APP_TASK1_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 											

	 
	
   OSTaskCreateExt(   AppTask2, //  建立报时任务 	
										  (void *) 0, 
										  (OS_STK *) &AppTask2Stk[APP_TASK2_STK_SIZE- 1],
										  APP_TASK2_PRIO,
                      APP_TASK2_PRIO,
										  (OS_STK *) &AppTask2Stk[0],
										  APP_TASK2_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );


       OSTaskCreateExt(  AppTask3, //  建立第3个任务 	
										  (void *) 0, 
										  (OS_STK *) &AppTask3Stk[APP_TASK3_STK_SIZE- 1],
										  APP_TASK3_PRIO,
                      APP_TASK3_PRIO,
										  (OS_STK *) &AppTask3Stk[0],
										  APP_TASK3_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 


      OSTaskCreateExt(  AppTask4, //  建立第4个任务 	
										  (void *) 0, 
										  (OS_STK *) &AppTask4Stk[APP_TASK4_STK_SIZE- 1],
										  APP_TASK4_PRIO,
                      APP_TASK4_PRIO,
										  (OS_STK *) &AppTask4Stk[0],
										  APP_TASK4_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 


   
    
											
											
		OSTaskCreateExt(	AppTask5, //  建立主任务，包括电机走时、电机反馈及照明  建立第5个任务 
											(void *) 0, 
											(OS_STK *) &AppTask5Stk[APP_TASK5_STK_SIZE - 1], 
											APP_TASK5_PRIO,
											APP_TASK5_PRIO, 
											(OS_STK *) &AppTask5Stk[0], 
											APP_TASK5_STK_SIZE , 
											(void *) 0,  
											 OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 
		
											
     OSTaskCreateExt(  AppTask6, //  建立第6个任务 	 最低任务进行反复亮灭指示灯！！
										  (void *) 0, 
										  (OS_STK *) &AppTask6Stk[APP_TASK6_STK_SIZE- 1],
										  APP_TASK6_PRIO,
                      APP_TASK6_PRIO,
										  (OS_STK *) &AppTask6Stk[0],
										  APP_TASK6_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );
									 
									 
									 
		OSTaskCreateExt(  AppTask7, //  建立第7个任务 	 专门处理gps！！
										  (void *) 0, 
										  (OS_STK *) &AppTask7Stk[APP_TASK7_STK_SIZE- 1],
										  APP_TASK7_PRIO,
                      APP_TASK7_PRIO,
										  (OS_STK *) &AppTask7Stk[0],
										  APP_TASK7_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );
											
											
		OSTaskCreateExt(  AppTask8, //  建立第8个任务 	 专门测试！！
										  (void *) 0, 
										  (OS_STK *) &AppTask8Stk[APP_TASK8_STK_SIZE- 1],
										  APP_TASK8_PRIO,
                      APP_TASK8_PRIO,
										  (OS_STK *) &AppTask8Stk[0],
										  APP_TASK8_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );									
											
     OS_EXIT_CRITICAL();												
											
																						
	
  OSTaskDel (OS_PRIO_SELF);
}

/*printf函数
%%：显示一个%，''对%无效，需要用"%%"输出%
 %ns：显示n个字符的字符串，不足n用空格在左侧填充
%0ns：显示n个字符的字符串，不足n用0在左侧填充
%-ns：显示n个字符的字符串，不足n用空格在右侧填充

*/


	


static  void AppTask1(void* p_arg)
{
	OS_CPU_SR  cpu_sr;	
	INT8U err;	
	INT16U  count;
	const INT8U bsdata[]={0x24,0x0F,0x04,0x01,0x0C,0x4D,0x50,0x33,0x5F,0x30,0x30,0x36,0x36,0x2E,0x4D,0x50,0x33,0x77};
	const INT8U *pbsdata=bsdata;	
	
		
	
	
	
   OS_ENTER_CRITICAL();	
	 p_arg = p_arg;
   PowerOnFLag=1;
	/*
	ucos 多个任务等待一个信号量  举例非常直观，值得推敲   added by sjw
	https://blog.csdn.net/gtkknd/article/details/52212097
	*/
	 pMainMotorSemEve=OSSemCreate(0);//如果Semp = OSSemCreate(0), 该信号量表示等待一个事件或者多个事件的发生。
	 pMainBsSemEve=OSSemCreate(0);
	 
	
	 Mutex_USART1 = OSMutexCreate(USART1_MUTEX_PRIO, &err);  // 建立USART1互斥型信号量
	 Mutex_USART2= OSMutexCreate(USART2_MUTEX_PRIO, &err);   // 建立USART2互斥型信号量	
	
	 GPIO_Motor_Config();       //内含电机驱动端口IO初始化---电机反馈端口初始化   
	 GPIO_I2C_Config();
	 LedPortSpecialInit();
	 //在调试的时候，PE2总是出现高电平，不跟软件指令动作，反复测量硬件没有问题，单独核心板就一根线直接到  HDR2*12插座，无任何问题
	 //另一块核心板同样如此，万用表测量PE2引脚发现是小于3.3伏，平时一直为1.8-1.9伏，考虑到不能是两个cpu端口都坏掉了吧，
	 //电压上不去，反复测试，另一个SSR正常，最后发现端口E的时钟没有打开，在函数中打开一切正常，记住电压上不去的可能原因是时钟没使能
	 //added  by sjw    !!!!!!!!!!!!!!!!!!!
	 LedBsZm_Init();                 //工作指示灯,报时、照明端口初始化  PB4为报时输出口！！  PE2为照明输出口！！
   Mp3Drive_Init();

	 Hd7279_Init();
	 //https://blog.csdn.net/m0_52850679/article/details/124506315
	 //片内外设的DMAx通道y      added by sjw
	 
	 TIM1_Config();             //                                                主中断0，次级中断0
	 N31_pps_init();            //GPS的pps中断信号    gps端口初始化 pps的中断：     主中断0，次级中断1
	 USART1_Init(9600);	        // 初始化串口1,9600波特率							            主中断1，次级中断0
	 GPIO_Key_Config();         //键盘键盘端口及其中断  								            主中断1，次级中断1
   USART2_Init(9600);         //                                                主中断1，次级中断2                                                  
	 //printf("**        欢迎使用ARM开发板        **\r\n");通过重定位测试串口2是没有问题！  added by sjw
	 USART_ClearFlag(USART2,USART_FLAG_TC); 
	 
	
	
	 
/*
塔钟或吉祥钟发出报时数据
24  0F 04 01 0C 4D 50 33 5F 30    30 36 36 2E 4D 50 33 77   --西敏寺前奏！
24  0F 04 01 0C 4D 50 33 5F 30    30 35 36 2E 4D 50 33 74  敲钟n下重复发送n次


24  0F 04 01 0C 4D 50 33 5F 30    30 36 32 2E 4D 50 33 73  东方红前奏！
24  0F 04 01 0C 4D 50 33 5F 30    30 35 35 2E 4D 50 33 77敲钟n下重复发送n次


https://blog.csdn.net/horton11/article/details/120361823  
	 
7、注意到这一句：由软件序列清除该位(先读USART_SR，然后写入USART_DR)。 也就是说，要先read USART_SR,然后write USART_DR，才能完成TC状态位的清除。而硬件复位后，串口发送的首个数据之前没有read SR的操作，是直接write DR，也就是说，TC没有被清除掉。 说明我们前面的猜测是对的。  
8、那么，应该把在传输第一个字节前面加：USART_ClearFlag(USART1,USART_FLAG_TC); 改为USART_GetFlagStatus(USART1, USART_FLAG_TC);，应该也能消除错误。测试后证实，确实如此，在发送首个数据之前，先读取一下USART_SR，那么就不会出现首个数据丢失的情况了。  
9、总结：硬件复位后，串口发送首个数据之前，先读取一下USART_SR，则能够保证首个数据发送时，不出现覆盖的情况。当然，也有别的方法，比如先清除TC状态位，或是，在write USART_DR之后，加入一个小延时，让数据发送完毕，应该也能间接排除这个错误
————————————————
版权声明：本文为CSDN博主「horton11」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/horton11/article/details/120361823 
*/	 
	
	 /*
	 for( count=0; count<18; count++){
		  USART_SendData(USART2,*pbsdata);
      //USART2->DR=*pbsdata;		 
			while((USART2->SR & 0x40)==0);//循环发送,直到发送完毕 
		  pbsdata++;
	 }*/
	 
	 #ifdef  USB_DEBUG_KERNEL  //USB_DEBUG0		
			printf("*************************************\r\n"); // LOGO 
			printf("**                                 **\r\n");
			printf("**        欢迎使用ARM开发板        **\r\n");
			printf("**  我们将引领您进入嵌入式系统开发 **\r\n");
			printf("**           您的最佳选择          **\r\n");
			printf("**                                 **\r\n");
			printf("*************************************\r\n");
			
			//printf("\n\r ############ WWW.ARMJISHU.COM! ############ ("__DATE__ " - " __TIME__ ")");

			printf("\r\n");
			printf("  _____ _______ __  __ ____ ___  ______ __  ___\r\n");
			printf(" / ____|__   __|  \\/  |___ \\__ \\|  ____/_ |/ _ \\\r\n");
			printf("| (___    | |  | \\  / | __) | ) | |__   | | | | |_  __\r\n");
			printf(" \\___ \\   | |  | |\\/| ||__ < / /|  __|  | | | | \\ \\/ /\r\n");
			printf(" ____) |  | |  | |  | |___) / /_| |     | | |_| |>  <\r\n");
			printf("|_____/   |_|  |_|  |_|____/____|_|     |_|\\___//_/\\_\\\r\n");
			printf("\r\n");

			/*printf("\n\r WWW.ARMJISHU.COM use __STM32F10X_STDPERIPH_VERSION %d.%d.%d\n\r",
					__STM32F10X_STDPERIPH_VERSION_MAIN,
					__STM32F10X_STDPERIPH_VERSION_SUB1,
					__STM32F10X_STDPERIPH_VERSION_SUB2);
					*/
			printf("\n\r 产品内部Flash大小为：%dK字节！ \t www.armjishu.com\n\r",  *(__IO uint16_t*)(0x1FFFF7E0));
			printf("变量BigOrSmallValue的地址为%p\r\n",&BigOrSmallValue);
			printf("指针pBigOrSmallValue的地址为%p\r\n",pBigOrSmallValue);
		#endif	
	  OS_EXIT_CRITICAL();	
		
		
		
	
/*
const unsigned char       Volume[6]={0x24,0x03,0x0F,0x01,0x1F,0x12};                     //MP3音量设置
unsigned char             Mp3data[18]={0x24,0x0F,0x04,0x01,0x0C,0x4D,0x50,0x33,0x5F,0x30,  //播放MP3指定文件
                                     0x30,0x30,0x32,0x2E,0x4D,0x50,0x33,0x74};


主板的CPU给MP3模块的数据如下：  
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--发送字节为60个
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16点前奏：
		24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
17点前奏：
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
    24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 

18点前奏：
    24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

		
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z	
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z
16点敲点次数：
		24 0F 04 01 0C 4D 50 33 5F 30 32 38 37 2E 4D 50 33 7A 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		37 2E 4D 50 33 7A 24 0F 04 01 0C 4D 50 33 5F 30 32 38 37 2E 4D 50 33 7A 
17点敲点次数：
$MP3_0288.MP3u$MP3_0288.MP3u$MP3_0288.MP3u------------------------发送字节为54个
$MP3_0288.MP3u$MP3_0288.MP3u$MP3_0288.MP3u
    24 0F 04 01 0C 4D 50 33 5F 30 32 38 38 2E 4D 50 33 75 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		38 2E 4D 50 33 75 24 0F 04 01 0C 4D 50 33 5F 30 32 38 38 2E 4D 50 33 75 				
18点敲点次数：
    24 0F 04 01 0C 4D 50 33 5F 30 32 38 39 2E 4D 50 33 74 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		39 2E 4D 50 33 74 24 0F 04 01 0C 4D 50 33 5F 30 32 38 39 2E 4D 50 33 74

控制字符ASCII码表
https://www.perfcode.com/p/control-character.html
*/	

	
	while(1){
		//OSTimeDly (500);
	   
		  OSTimeDlyHMSM(0, 0, 0, 400);
	}
  
}






//观察usart2中断接收的母钟发送的数据，9个！
static  void AppTask2(void* p_arg)
{
   INT8U err;
   INT8U temp;

  p_arg = p_arg;
	//OSTimeDly(1000);
 

  while (1) {
		
       #if 0
	     OSTaskSuspend(OS_PRIO_SELF); 		    // 先将任务挂起，在串口接收中断中恢复任务
       OSMutexPend(Mutex_USART2, 0, &err);  // 等待信号量
       while(USART2_GetByte(&temp)){    	  // 如果串口接收到数据打印出来
           USART2_SendByte(temp);
       }  
	   
	    if((USART2_RX_FIFO[0]==0xbb)&&(USART2_RX_FIFO[7]==0x0d)&&(USART2_RX_FIFO[8]==0x0a)){ 	
					p_timemu->hour=USART2_RX_FIFO[1];
					p_timemu->minute=USART2_RX_FIFO[2];
					p_timemu->second=USART2_RX_FIFO[3];
					MainBsPayOrXms=USART2_RX_FIFO[4];		//0为平安夜报时；1为西敏寺报时！
					MainBsKnockCnt=USART2_RX_FIFO[5]%12;   	//钟声次数！
					if(USART2_RX_FIFO[6]==0){		 		//报时打开或者关死状态！
						//MainBsOnOffStatusFlag=FALSE;
						//MainBsJsValidFlag=FALSE;		
					}else{
						//MainBsOnOffStatusFlag=TRUE;
						//MainBsJsValidFlag=TRUE;
					}	
			}
      OSMutexPost(Mutex_USART2);            // 释放信号量  
			#endif
			OSTimeDlyHMSM(0, 0, 0, 470);
			
			
   }
}





//此任务用来调试一些状态位，在上位机里直观检测！！
static  void AppTask3(void* p_arg)//键盘处理任务！！
{	
	INT8U tempdata;
 static INT8U rxjs=0x11;	
	
	      char  *des;
	      char  *r;
	const char  *source;
	
	
	/*
	
	所以，在编写程序时，最安全的方法，就是尽可能不去使用 strcpy 函数。可以在程序的开头加上 #define strcpy Unsafe_strcpy。这样，
	就会使 strcpy 函数在编译时产生错误，从而使我们在编程时可以完全摒弃strcpy 函数。在完全丢弃 strcpy 函数的同时，也就丢掉了众多依附于 strcpy 函数的 bug。
	*/
	
	#if 0
		if (ucKeyValue > 0)
		{
				/* 暂时不做任何处理，用户可以自己添加处理代码 */
				switch (ucKeyValue)
				{
					case KEY_DOWN_JOY_UP:		/* 摇杆UP键按下  */
					case KEY_DOWN_JOY_DOWN:		/* 摇杆DOWN键按下  */
					case KEY_DOWN_JOY_LEFT:		/* 摇杆LEFT键按下 */
					case KEY_DOWN_JOY_RIGHT:	/* 摇杆RIGHT键按下 */
					case KEY_DOWN_JOY_OK:		/* 摇杆中键按下 */
					case KEY_DOWN_USER:			/* USER键按下 */
						break;					

					default:
						break;
				}
		}
#endif
		
		
		while(1){
			
			//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);//检查接受标志位，是否可以接受added by sjw
			//rxjs=SPI_I2S_ReceiveData(SPI1);
			
     #ifdef PROG_TEST_STA_FUNC
			     if(ItWaitFlag3==1){
							//USART_SendData(USART2,Key_Subclock_State1); //发送一次当前状态!
						  printf("\r\n 电机状态为：%d ",Key_Subclock_State1);
						  printf("初始上电为：%d ",PowerOnFLag);
						  printf("正转标志：%d ", MotorZZ_Flag);
						  printf("反转标志：%d ", MotorFZ_Flag);
						  printf("\r\n GPS状态：%d ,%d ,%d ,%d", board.refeid[0],board.refeid[1],board.refeid[2],board.refeid[3]);
						  ItWaitFlag3=0;
						 // while((*r++ = *source++)!='\0');while((*des++=*source++));的解释： 赋值表达式返回左操作数，所以在赋值'\0'后，循环停止。
					 }
		 #endif
			OSTimeDlyHMSM(0, 0, 0, 300);
			
		}
}





/*
本文采用DMA+环形缓冲区对GPS报文进行解析，思路是通过DMA中断接收到GPS报文后，存放到环形缓冲区，然后在主程序中解析GPS报文。
解析GPS报文的关键是：将环形缓冲区中的字节转换成字符串，然后在字符串中查找GPS报文头标识（例如：GPGGA）和GPS报文尾部标识（回车换行）。
————————————————
版权声明：本文为CSDN博主「ba_wang_mao」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/ba_wang_mao/article/details/115530153


//https://blog.csdn.net/ba_wang_mao/article/details/115530153
	//STM32F407 单片机+DMA+环形缓冲区+GPS报文解析
	
	//https://www.codenong.com/cs107108405/
	//串口空闲中断+DMA接收数据
解释GPS任务放在任务4中处理！
*/











/*
NTP时间戳转换成UTC时间的过程
https://blog.csdn.net/weixin_45873923/article/details/120119622


①NTP时间戳用一个64bit无符号定点数表示，它表示自从1900年1月1日00:00:00到现在过了多少秒。
②UTC时间，格林威治时间1970年1月1日00:00:00（北京时间1970年1月1日08:00:00）起至现在的总秒数，表示为1970-01-01 00:00:00 UTC。程序里习惯叫做UTC时间戳。
 NTP协议中有四个时间戳，本文不讨论这四个时间戳的区别，只简单的拿其中一个NTP时间戳报文分析如何转换成UTC时间。
例如一段时间戳报文为“D9 FD 84 95 94 F8 59 7C”，下面我们一起学习该NTP时间戳是如何转换成UTC时间的。


mktimev(&now)函数将年月日时分秒转换为NTP的秒数
to_tm(NTP - JAN_1970, &now);函数将秒数转换为UTC时间

*/


//GPS模块调试成功，目前执行isLinear(_ntp)后跳入HardFault_Exception!!


//此任务专门处理GPS信号！！
static  void AppTask4(void* p_arg)
{
	extern 	INT16U 	Usart1_Rx_Len;
	extern 	head 		header;
	extern 	INT8U		ItFlag;

	INT32U     _ntp = 0; 
  OS_CPU_SR  cpu_sr;
	struct tm  now;
	INT8U sjw[8],eeprom_page;
	
	
	
	while(1){
		
			set_pps1_sig();//当pps1_tim > 101时候，需要pps1_status=0和秒脉冲同步！
		
			if(uart1_rx_sig){			
				uart1_rx_sig = 0;	
				board.err &= ~err_gps1;
				
				//gps.status = gps_bd2_ascii(Uart1_Rx_Buf, Usart1_Rx_Len);	//
				gps.status = gps_bd2_ascii(receive_data, Usart1_Rx_Len);	//receive_data

				memset(Uart1_Rx_Buf,0,UART1_RX_SIZE);    //处理完毕进行清空数组的工作！！	
				
				
				//uCOS临界段函数的理解：CPU_SR_ALLOC() 写的非常棒，避免中断嵌套中对临界段程序的破坏！！added by sjw
		    //https://blog.csdn.net/m0_43443861/article/details/125956776						
				
				
				if(gps.status){								
						  _ntp = do_gps(); //将GPS接收的标准UTC数据送给变量  注意此时已经将UTC时间变为CTC时间added by sjw		
						//if(isLinear(_ntp) && (pps1_status>10))//执行函数isLinear(_ntp)后跳入异常！！added by sjw
					    if(pps1_status>10){
									NTP = _ntp;								  
									if(!(_ntp %180) ){		  //保留往3231里面压gps数据的功能！每3分钟一次！
										
										OS_ENTER_CRITICAL();	//进入临界区						
										//OSSchedLock(&err);		//UCOSII的方式,禁止调度 		
										ds3231_tm_wr(NTP);   //等待x分钟往里压入保存！);	
										/*
										调度器上锁函数OSSchedlock()的功能是用于禁止任务调度，使任务保持对CPU的控制权。调度器开锁函数OSSchedUnlock()的功能是解除对任务调度的禁止。
										调度器上锁和开锁的实现原理是：对全局变量锁定嵌套计数器OSLockNesting进行操作，OSLockNesting跟踪OS SchedLock() 函数被调用的次数，
										允许嵌套深度达255层。调度器上锁即对变量OSLockNesting进行加1操作，开锁即对变量OSLockNesting进行减1操作。
										————————————————
										版权声明：本文为CSDN博主「fillthesky」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
										原文链接：https://blog.csdn.net/fillthesky/article/details/46697179
										*/
										//OSSchedUnlock(&err);	//UCOSII的方式,恢复调度
										
										OS_EXIT_CRITICAL();	  //临界区	
								  }
									header.msg4 = 0x04;				
									board.stratum = 1;
									strcpy(board.refeid, "GPS"); 														
						}
				 }else{	
						extern u8 syn[4]; 	
						header.msg4 = 0x07;
						strcpy(board.refeid, "LOCL"); 					 
				 }	 		 		
			}
			OSTimeDlyHMSM(0, 0, 0, 217);
	 }
}









//此任务专门处理报时功能，看看前奏和钟声分别是什么、是否到报时时间了！！added by sjw


//此任务专门处理显示，键盘及照明和报时！
static  void AppTask5(void* p_arg)
{
	OS_CPU_SR  	cpu_sr;
	INT8U err,eeprom_page;
	INT8U js=0,flag=0,count;
  struct tm  now;
	INT8U    wait=0;
	
	
	
		
		#if 0  //32页里256个单元全部验证，无任何问题！！  added by sjw  2023-10-14 周六 goto work
		 OS_ENTER_CRITICAL();
		 for(eeprom_page=0;eeprom_page<32;eeprom_page++){
				iic_sw_write(eep_chip_24cxx, iic_eeprom_east+eeprom_page*8, tx1, 8);//注意芯片是一页就8个字节，如何大于8个字节，又缠绕翻转到开始地址！！added by sjw
				DelayMs(100);
		 }
		 OS_EXIT_CRITICAL();	
		 OSTimeDlyHMSM(0, 0, 1, 500);
		 OS_ENTER_CRITICAL();
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_east, &board.east_time[0], 8);//注意I2C有个写周期，大约10ms，多页写要大于此写周期！！added by sjw
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_south, &board.south_time[0], 8);
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_west, &board.west_time[0], 8);
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_north, &board.north_time[0], 8);
		 OS_EXIT_CRITICAL();		
		#endif
		
		
		/*
	  //该指令使所有的LED全部点亮，并处于闪烁状态，主要用于测试。
    Set7279CS(0);
    SendByteToHd7279(CMD_TEST);
    DelayMs(2400);		
    Set7279CS(1); 
	*/


   for(wait=0;wait<5;){ //开机等待5秒  added by sjw
		 
			if(ItWaitFlag==1){ 
				 Set7279CS(0);
				Display();
				 Set7279CS(1);
				wait++;       
				ItWaitFlag=0;                                     
			}    
   
   }
	 
#if 1
		OS_ENTER_CRITICAL();
		//temp=0x1c;
		//iic_sw_write(eep_chip_24cxx, 0x0e,&temp , 1);//模拟RTC  
		get_time();//读取RTC的时间
	 //由原来函数get_iic_setting  挪动位置到这个位置，added by sjw
	  get_iic_setting();//读取子钟时间、报时开关设定的小时、报时前奏及钟声和照明开关的设定！！added by sjw
		OS_EXIT_CRITICAL();	
		#endif
	 
  
   TimeDisValidFlag=1;//读出时间数据正确后，标志有效！！added by sjw
  
	//test1=HEX_to_BCD(0x19);//0x19是16进制,转换为    BCD码应该为0x25  运行后此结果正确！！added by sjw
	//test2=BCD_to_HEX(37);  //BCD码为37    转换为    16进制应该为0x25  运行后此结果不正确！！正确结果应该为0x19 added by sjw

	
	 	
		
		
	while(1){	
				Light_Control();  //照明 
				Time_Notice();    //报时
				if(IntDisFlag){   //显示母钟时间,现在修改为300ms显示一次
						Set7279CS(0);
						Display();
						Set7279CS(1);
						IntDisFlag=0;
				}
				
				
				if(Key_Time==1){ //处理按键操作
					Set7279CS(0);
					Key_Operation();  //  出现抖动现象，是因为   片选信号   操作的位置出错，接近于片选一直选中，所以8个数字全部闪烁！！added by sjw
					Set7279CS(1);
					Key_Time=0;
				}
				
				OSTimeDlyHMSM(0, 0, 0, 90);		
				
				//OSSemPend(pMainBsSemEve,0,&err);//

	}
}




//此任务专门处理键盘快追（正转或者反转功能！！）added by sjw


//此任务没用！
static  void AppTask6(void* p_arg)
{
	INT8U err;	
	
	
	
	while(1){
		   
		
		  /*
		   if((MotorZZ_Flag)&&(!MotorFZ_Flag)){
					EnterEastNormalRun();	 
			 }else if((MotorFZ_Flag)&&(!MotorZZ_Flag)){
					EnterEastFzRun();	 
			 }
			 OSTimeDlyHMSM(0, 0, 0, 100);
			 */
		
		
		/*
		   switch ( Key_Subclock_State1){  //判断是否按键调整过  子钟状态  使其变化有效了！！
				case NC:
					 
				break;
				
					
				case WALK:
					 
				break;
				 
				case RUN_FORWARD:	 
				   EnterEastNormalRun();	 
				break;
					 
				 
				case STOP:
					     EAST_ZZ_IDLE;
							 EAST_FZ_IDLE;
						    
				break;
						
				case RUN_REVERSE:					
					  EnterEastFzRun();	
				break;
						
				case CALIB:
						
					 
				break;
						
				 
				
			 }
			 
			 */
			
			 
			 
			 OSTimeDlyHMSM(0, 0, 0, 160);
		  
		
	}
}





//电机驱动及电机反馈模块调试成功！
//在上电追时完毕后，电机开始正常走时！！added by sjw


//此任务专门处理电机正常走时、正追及反追
static  void AppTask7(void* p_arg)
{	
	 INT8U err;
   INT8U temp[3];
   OS_CPU_SR  cpu_sr;	
	 INT16U i,count;	
	 GPIO_InitTypeDef GPIO_InitStructure;
	static INT8U first_flag;
 
   
   p_arg = p_arg;
	
	
	 while(1)
	 {	
		
		 // OSSemPend(pMainMotorSemEve,0,&err);//正常的走时，
		 
		 //if((MotorZZ_Flag)&&(!MotorFZ_Flag)&&(!PowerOnFLag)){
		 if((MotorZZ_Flag)&&(!MotorFZ_Flag)){
				  EnterEastNormalRun();
			}//else if((MotorFZ_Flag)&&(!MotorZZ_Flag)&&(!PowerOnFLag)){
					else if((MotorFZ_Flag)&&(!MotorZZ_Flag)){
				  EnterEastFzRun();
			}else if((!MotorZZ_Flag)&&(!MotorZZ_Flag)&&(PowerOnFLag)){ 
					 if(!first_flag){	
								if(compare_zf(p_timemu,p_timeslave)==1){//表示追时完毕，需要将数据压l入AT24Cxx里保存！！
									 temp[0]= p_timeslave->hour;
									 temp[1]= p_timeslave->minute;
									 temp[2]= p_timeslave->second;
									
									 OS_ENTER_CRITICAL();
									 iic_sw_write(eep_chip_24cxx,  iic_eeprom_east, temp, 3);
									 OS_EXIT_CRITICAL();	
									 DelayMs(100);
									
									 OS_ENTER_CRITICAL();
									 iic_sw_read(eep_chip_24cxx,  iic_eeprom_east, temp, 3);
									 p_timeslave->hour= temp[0];
									 p_timeslave->minute=temp[1];
									 p_timeslave->second=temp[2]; 
									 OS_EXIT_CRITICAL();
									
									
									 PowerOnFLag=0;
									 Key_Subclock_State1=WALK;//必须添加此指令，代表初始追时结束后，系统为WALK状态！！added by sjw
									 first_flag=1;
									
								}
					}
			}//else if((!MotorZZ_Flag)&&(!MotorZZ_Flag)&&(!PowerOnFLag)){
				 else if((!MotorZZ_Flag)&&(!MotorZZ_Flag)){
				
					if(MotorActFlag){
							#ifdef USE_MOTOR_ONE	
								 EnterEastNormalRun();
							#endif
							MotorActFlag=0;
							OSTimeDlyHMSM(0, 0, 0, 110);
					 }else{
							OSTimeDlyHMSM(0, 0, 0, 510);
					 }
					 
					
			}
			 
			 
		 
		 
		 
	 }
}







//键盘接口及显示都调试成功！！
//为了解决用户在初始上电快追时调整键盘的体验，将显示和键盘模块移动到任务7上，！！added by sjw
//此优先级最低的任务专门处理刚上电后的快追动作，这样处理其不干扰键盘和显示的调整！！added by sjw





//此任务在设定的时间读取一次DS3231里面的时间！
static  void AppTask8(void* p_arg)
{
	INT8U  err;
	static INT8U first_flag;
	INT8U  eeprom_page,temp[8];
	INT32U     _ntp = 0; 
  OS_CPU_SR  cpu_sr;
	struct tm  now;
	INT8U    wait=0;
	
	//2023年10月20日15：32:50
	static INT8U  tx[11]={0x00,0x07,0xe7,0x0a,0x14,0x0f,0x20,0x032,0x00,0x00,0x05};	 
	

		
	while(1){	
		//time_set();      //母钟时间校对
		
				
		if((p_timemu->minute == 10) && (p_timemu->second == 5)){
			//OS_ENTER_CRITICAL();
			get_time();//1个小时读取一次RTC的时间
			//OS_EXIT_CRITICAL();
		}
	  
		OSTimeDlyHMSM(0, 0, 0, 10);
	}
}

/*

								
 


    if(LED_time==1)  //显示母钟时间
    {     
     display();                                                                                                                                                                                                                                                                             
     LED_time=0;    
    }  


    if(Key_time==1) //处理按键操作
    {
     CS_7279=0;       
     if(KEY_INT==0) 
      {
      Key_value=read7279(CMD_READ);      
      } 
     key_operation();         
     CS_7279=1; 
     Key_time=0;    
    } 
		
		
*/		
		

/*********************************
*功 能：子钟未记住时间时，将母钟时间
*        作为自己的时间
*********************************/
void reset_subcolock(void)
{
	
}

/*
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
*****************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
*******************************************************************************************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
*******************************************************************************************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
*************************

*/



/*********************************
*功 能：母钟时间校对
*        
*********************************/
/*

void time_set(void)
 {
         INT8U  rtc_read,time[3]={0};
  static INT8U  data_reset=0;

  if(Gpscycle>=WAITTIME&&Gpscycle<=(WAITTIME+10)&&Uart2mp3==0)   
    {    
     if(data_reset==0)
      {
       gps_data();   
       data_reset=1;            
      } 
      
     if(uart1_receive())
      {    
       set_rtc();      
       Subclock1.timesource=1;
       Subclock2.timesource=1; 
       Subclock3.timesource=1;
       Subclock4.timesource=1;        
       Time_adjust=1;//校时标志   
       Master_second=(Masterclock.hour%12)*3600+Masterclock.minute*60+Masterclock.second;  
       Gpscycle=0; 
       data_reset=0;      
      }      
    }
   else if(Gpscycle>(WAITTIME+10)&&Uart2mp3==0)
    {      
     rtc_read=readbyte(0x0f);
     if((rtc_read&0x80)==0x00)
      {
       time[0]=BCD_to_HEX(readbyte(0x00));
       time[1]=BCD_to_HEX(readbyte(0x01));
       time[2]=BCD_to_HEX(readbyte(0x02)); 
       if(time[0]==0&&time[1]==0&&time[2]==0)  ;
       else if(time[0]<60&&time[1]<60&&time[2]<24)
        {
         Masterclock.second=time[0];
         Masterclock.minute=time[1];
         Masterclock.hour=time[2];              
         Subclock1.timesource=1;
         Subclock2.timesource=1;
         Subclock3.timesource=1;
         Subclock4.timesource=1;
         Master_second=(Masterclock.hour%12)*3600+Masterclock.minute*60+Masterclock.second;
         Time_adjust=1;//校时标志          
        } 
       time[2]=BCD_to_HEX(readbyte(0x04));
       time[1]=BCD_to_HEX(readbyte(0x05));
       time[0]=BCD_to_HEX(readbyte(0x06)); 
       if(time[2]>0&&time[2]<=31&&time[1]>0&&time[1]<=12&&time[0]>0&&time[0]<=99)
       {
        Masterclock.year=time[0];
        Masterclock.month=time[1];
        Masterclock.day=time[2];
       }          
      } 
     Gpscycle=0; 
     data_reset=0;          
    }
 }

*/























void EnterEastNormalRun(void)
{
	static enum{IDLE,WAIT_TIME,HIGH,HIGH_KEEP,LOW,LOW_KEEP,STOP}status=IDLE;
	INT8U   temp[3];
	INT32U     _ntp = 0; 
  OS_CPU_SR  cpu_sr;
	
	
  EAST_ZZ_IDLE;
  EAST_FZ_IDLE;
	OSTimeDlyHMSM(0, 0, 0, 20);	//此三句指令添加上保险！！added by sjw
	
  EAST_ZZ;
	while(1){
			switch(status){
						case IDLE:
								status=WAIT_TIME;
						    LightSlotFlag=1;
						break;
						
						
						
						case WAIT_TIME://强制等待500ms，一定越过光槽位置了！added by sjw
							  if(LightSlotValue>500){
									  LightSlotFlag=0;
								    LightSlotValue=0;
										status=HIGH;
								}else{
									OSTimeDly(20);
								}
						break;
						
						case HIGH:
							  if(EAST_FK_PIN==0){//开始 侦测  到达光槽的位置了，
									OSTimeDly(20);
									status=HIGH_KEEP;
								}else{
									OSTimeDly(20);
								}
						break;
								
						case HIGH_KEEP://
								if(EAST_FK_PIN==0){
									status=LOW;
								}else{
									OSTimeDly(20);
									status=HIGH;
								}
						break;
								
								
								
				//*******************************		
        //*******************************									
								
						
						case LOW:
								if(EAST_FK_PIN==1){
									OSTimeDly(30);
									status=LOW_KEEP;
								}else{
									OSTimeDly(20);
								}
						break;
								
						case LOW_KEEP:
								if(EAST_FK_PIN==1){
									status=STOP;
									OSTimeDly(20);
								}else{
									OSTimeDly(20);
								}
						break;	

						case STOP:
								if(EAST_FK_PIN==1){
									EAST_ZZ_IDLE;
                  EAST_FZ_IDLE;
									status=IDLE;
									/*
									EEPROM不分什么扇区，以字节为操作单位，分扇区的是FLASH。MCU集成的EEPROM是专做非易失数据存储器的，占用地址是RAM空间。MCU集成的FLASH是程序存储器，
									支持IAP的话，可以利用FLASH程序存储器作为非易失数据存储器，但性质与EEPROM可不同。非易失存储器的可擦写寿命由最短寿的那一字节决定，
									不论EEPROM还是FLASH均如此。有些做数据存储的大容量FLASH则以坏块的百分比作为寿命判定依据，显然放宽了很多。
									
									EEPROM不分扇区的，分页，这是不同的概念。
									担心存储器寿命可以用FRAM存储器，这个寿命长
									
									
									MCU上的EEPROM都是拿FLASH模拟的，所以都标称10万次擦除。
                  真正的EEPROM都是百万次擦除。
									
									
					FRAM提供一种与RAM一致的性能,但又有与ROM 一样的非易失性。 FRAM 克服以上二种记忆体的缺陷并合并它们的优点，它是全新创造的产品，一个非易失性随机存取储存器。
									*/
											//MainProcessTimeAdd(board,1);//每分钟必须要压入AT24Cxx内一次，此芯片寿命为100万/1440次每天=690天，大约2年,added by sjw
									MathEastAdd_Qd220(p_timeslave);
									
									temp[0]=p_timeslave->hour;
									temp[1]=p_timeslave->minute;
									temp[2]=p_timeslave->second;
									
									 OS_ENTER_CRITICAL();
									 iic_sw_write(eep_chip_24cxx,  iic_eeprom_east, temp, 3);
									 OS_EXIT_CRITICAL();	
									 DelayMs(30);
									
									 OS_ENTER_CRITICAL();
									 iic_sw_read(eep_chip_24cxx,  iic_eeprom_east, temp, 3);
									 p_timeslave->hour= temp[0];
									 p_timeslave->minute=temp[1];
									 p_timeslave->second=temp[2]; 
									 OS_EXIT_CRITICAL();
									
									goto force_exit1;  //强制跳出无限循环！！added by sjw
								}else{
									status=LOW_KEEP;
								}
						break;										
			}			
	}
	force_exit1:
		OSTimeDlyHMSM(0, 0, 0, 15);	
	
}



void  EnterEastFzRun(void)
{
		
	 INT8U err;
	 INT8U temp[3];
	 OS_CPU_SR  cpu_sr;	
	 INT16U i,count;	
	 static enum{IDLE,WAIT_TIME,HIGH,HIGH_KEEP,LOW,LOW_KEEP,STOP}status=IDLE;

	
  EAST_ZZ_IDLE;
  EAST_FZ_IDLE;
	OSTimeDlyHMSM(0, 0, 0, 20);//此三句指令添加上合适！！added by sjw	 2023-12-5 in  tuesday!!
	
  EAST_FZ;
	while(1){
			switch(status){
						case IDLE:
								status=WAIT_TIME;
						    LightSlotFlag=1;
						break;
						
						
						
						case WAIT_TIME://强制等待500ms，一定越过光槽位置了！added by sjw
							  if(LightSlotValue>500){
									  LightSlotFlag=0;
								    LightSlotValue=0;
										status=HIGH;
								}else{
									OSTimeDly(20);
								}
						break;
						
						case HIGH:
							  if(EAST_FK_PIN==0){//开始 侦测  到达光槽的位置了，
									OSTimeDly(20);
									status=HIGH_KEEP;
								}else{
									OSTimeDly(20);
								}
						break;
								
						case HIGH_KEEP://
								if(EAST_FK_PIN==0){
									status=LOW;
								}else{
									OSTimeDly(20);
									status=HIGH;
								}
						break;
								
								
								
				//*******************************		
        //*******************************									
								
						
						case LOW:
								if(EAST_FK_PIN==1){
									OSTimeDly(30);
									status=LOW_KEEP;
								}else{
									OSTimeDly(20);
								}
						break;
								
						case LOW_KEEP:
								if(EAST_FK_PIN==1){
									status=STOP;
									OSTimeDly(20);
								}else{
									OSTimeDly(20);
								}
						break;	

						case STOP:
								if(EAST_FK_PIN==1){
									EAST_ZZ_IDLE;
                  EAST_FZ_IDLE;
									status=IDLE;
									
									MathEastSub_Qd220(p_timeslave);

									
									temp[0]=p_timeslave->hour;
									temp[1]=p_timeslave->minute;
									temp[2]=p_timeslave->second;
									
									 OS_ENTER_CRITICAL();
									 iic_sw_write(eep_chip_24cxx,  iic_eeprom_east, temp, 3);
									 OS_EXIT_CRITICAL();	
									 DelayMs(30);
									
									 OS_ENTER_CRITICAL();
									 iic_sw_read(eep_chip_24cxx,  iic_eeprom_east, temp, 3);
									 p_timeslave->hour= temp[0];
									 p_timeslave->minute=temp[1];
									 p_timeslave->second=temp[2]; 
									 OS_EXIT_CRITICAL();
									
									goto force_exit2;  //强制跳出无限循环！！added by sjw
								}else{
									status=LOW_KEEP;
								}
						break;										
			}			
	}
	force_exit2:
		OSTimeDlyHMSM(0, 0, 0, 10);	
}
 






































void EnterSouthNormalRun(void)
{
	static enum{IDLE,HIGH,LOW_EDGE,LOW_KEEP,STOP_EDGE}status=IDLE;

	
	
  SOUTH_ZZ_IDLE;
  SOUTH_FZ_IDLE;
	OSTimeDlyHMSM(0, 0, 0, 100);	
	
  SOUTH_ZZ;
	while(1){
			switch(status){
						case IDLE:
								status=HIGH;
						break;
						
						case HIGH:
								if(SOUTH_FK_PIN==0){
									status=LOW_EDGE;
									OSTimeDly(50);
								}else{
									OSTimeDly(50);
								}
						break;
						
						case LOW_EDGE:
								if(SOUTH_FK_PIN==0){
									status=LOW_KEEP;
								}else{
									status=IDLE;
								}
						break;
								
						case LOW_KEEP:
								if(SOUTH_FK_PIN==1){
									status=STOP_EDGE;
									OSTimeDly(3);
								}
						break;	

						case STOP_EDGE:
								if(SOUTH_FK_PIN==1){
									SOUTH_ZZ_IDLE;
									status=IDLE;
									MainProcessTimeAdd(board,2);//每次走完必须要压入AT24Cxx内一次，此芯片寿命为100万/2880次每天=347天，大约1年,added by sjw
									goto force_exit;
								}else{
									status=IDLE;
								}
						break;										
			}			
	}
	force_exit:
		OSTimeDlyHMSM(0, 0, 0, 10);	
	
}




void EnterWestNormalRun(void)
{
	static enum{IDLE,HIGH,LOW_EDGE,LOW_KEEP,STOP_EDGE}status=IDLE;

	
	
  WEST_ZZ_IDLE;
  WEST_FZ_IDLE;
	OSTimeDlyHMSM(0, 0, 0, 100);	
	
  WEST_ZZ;
	while(1){
			switch(status){
						case IDLE:
								status=HIGH;
						break;
						
						case HIGH:
								if(WEST_FK_PIN==0){
									status=LOW_EDGE;
									OSTimeDly(50);
								}else{
									OSTimeDly(50);
								}
						break;
						
						case LOW_EDGE:
								if(WEST_FK_PIN==0){
									status=LOW_KEEP;
								}else{
									status=IDLE;
								}
						break;
								
						case LOW_KEEP:
								if(WEST_FK_PIN==1){
									status=STOP_EDGE;
									OSTimeDly(3);
								}
						break;	

						case STOP_EDGE:
								if(WEST_FK_PIN==1){
									WEST_ZZ_IDLE;
									status=IDLE;
									MainProcessTimeAdd(board,3);//每次走完必须要压入AT24Cxx内一次，此芯片寿命为100万/2880次每天=347天，大约1年,added by sjw
									goto force_exit;
								}else{
									status=IDLE;
								}
						break;										
			}			
	}
	force_exit:
		OSTimeDlyHMSM(0, 0, 0, 10);	
	
}


void EnterNorthNormalRun(void)
{
	static enum{IDLE,HIGH,LOW_EDGE,LOW_KEEP,STOP_EDGE}status=IDLE;

	
	
  NORTH_ZZ_IDLE;
  NORTH_FZ_IDLE;
	OSTimeDlyHMSM(0, 0, 0, 100);	
	
  NORTH_ZZ;
	while(1){
			switch(status){
						case IDLE:
								status=HIGH;
						break;
						
						case HIGH:
								if(NORTH_FK_PIN==0){
									status=LOW_EDGE;
									OSTimeDly(50);
								}else{
									OSTimeDly(50);
								}
						break;
						
						case LOW_EDGE:
								if(NORTH_FK_PIN==0){
									status=LOW_KEEP;
								}else{
									status=IDLE;
								}
						break;
								
						case LOW_KEEP:
								if(NORTH_FK_PIN==1){
									status=STOP_EDGE;
									OSTimeDly(3);
								}
						break;	

						case STOP_EDGE:
								if(NORTH_FK_PIN==1){
									NORTH_ZZ_IDLE;
									status=IDLE;
									MainProcessTimeAdd(board,4);//每次走完必须要压入AT24Cxx内一次，此芯片寿命为100万/2880次每天=347天，大约1年,added by sjw
									goto force_exit;
								}else{
									status=IDLE;
								}
						break;										
			}			
	}
	force_exit:
		OSTimeDlyHMSM(0, 0, 0, 10);	
	
}




void MainProcessTimeAdd(config data,INT8U order)
{ 
  static enum{INVALID,VALID}tempstatus1=INVALID,tempstatus2=INVALID,tempstatus3=INVALID,tempstatus4=INVALID;
	static INT8U  flag;
	
			switch (order)
			{
				case 1:
						data.east_time[2]+=30;
						if(data.east_time[2]>=60){
								data.east_time[2]=0;
								data.east_time[1]++;
								if(data.east_time[1]>=60){
									 data.east_time[1]=0;
									 data.east_time[0]++;
									 if(data.east_time[0]>=12){
											data.east_time[0]=0;
									 }
								}
							
						}
						switch(tempstatus1)
						{
							case INVALID:
								 if(p_timemu->second>=58){//1分钟将时间压入AT24C里面！！
									   iic_sw_write(eep_chip_24cxx, iic_eeprom_east, &data.east_time[0], 8);
									   tempstatus1=VALID;
								 }
							break;
							case VALID:
								 if(p_timemu->second==59){
									  tempstatus1=INVALID;
								 }
								
							break;
						  default:
									tempstatus1=INVALID;
							
						}
						
				break;
						
				case 2:
						data.south_time[2]+=30;
						if(data.south_time[2]>=60){
								data.south_time[2]=0;
								data.south_time[1]++;
								if(data.south_time[1]>=60){
									 data.south_time[1]=0;
									 data.south_time[0]++;
									 if(data.south_time[0]>=12){
											data.south_time[0]=0;
									 }
								}
							
						}
						switch(tempstatus1)
						{
							case INVALID:
								 if(p_timemu->second>=58){//1分钟将时间压入AT24C里面！！
									   iic_sw_write(eep_chip_24cxx, iic_eeprom_south, &data.south_time[0], 8);
									   tempstatus1=VALID;
								 }
							break;
							case VALID:
								 if(p_timemu->second==59){
									  tempstatus1=INVALID;
								 }
								
							break;
						  default:
									tempstatus1=INVALID;
							
						}
				break;	




				case 3:
						data.west_time[2]+=30;
						if(data.west_time[2]>=60){
								data.west_time[2]=0;
								data.west_time[1]++;
								if(data.west_time[1]>=60){
									 data.west_time[1]=0;
									 data.west_time[0]++;
									 if(data.west_time[0]>=12){
											data.west_time[0]=0;
									 }
								}
							
						}
						switch(tempstatus1)
						{
							case INVALID:
								 if(p_timemu->second>=58){//1分钟将时间压入AT24C里面！！
									   iic_sw_write(eep_chip_24cxx, iic_eeprom_west, &data.west_time[0], 8);
									   tempstatus1=VALID;
								 }
							break;
							case VALID:
								 if(p_timemu->second==59){
									  tempstatus1=INVALID;
								 }
								
							break;
						  default:
									tempstatus1=INVALID;
							
						}
						
				break;
						
						
						
				case 4:
						data.north_time[2]+=30;
						if(data.north_time[2]>=60){
								data.north_time[2]=0;
								data.north_time[1]++;
								if(data.north_time[1]>=60){
									 data.north_time[1]=0;
									 data.north_time[0]++;
									 if(data.north_time[0]>=12){
											data.north_time[0]=0;
									 }
								}
							
						}
						switch(tempstatus1)
						{
							case INVALID:
								 if(p_timemu->second>=58){//1分钟将时间压入AT24C里面！！
									   iic_sw_write(eep_chip_24cxx, iic_eeprom_north, &data.north_time[0], 8);
									   tempstatus1=VALID;
								 }
							break;
							case VALID:
								 if(p_timemu->second==59){
									  tempstatus1=INVALID;
								 }
								
							break;
						  default:
									tempstatus1=INVALID;
							
						}
						
				break;
						
			}
	
}





void MainProcessTimeSub(config data,INT8U order)
{
	static INT8U  flag;
	
			switch (order)
			{
				case 1:
						data.east_time[2]-=30;
						if(data.east_time[2]>=0xe2){
								data.east_time[2]=30;
								data.east_time[1]--;
								if(data.east_time[1]>=0xe2){
									 data.east_time[1]=59;
									 data.east_time[0]--;
									 if(data.east_time[0]>=0xe2){
											data.east_time[0]=11;
									 }
								}
							
						}
						if((p_timemu->second==58)&&(!flag)){//1分钟将时间压入AT24C里面！！
								flag=1;
								iic_sw_write(eep_chip_24cxx, iic_eeprom_east, &data.east_time[0], 8);
						}
						
						if(p_timemu->second==59){
								flag=0;		
						}
				break;
						
				
						
			}
	
}














/*
https://aiops.com/news/post/165.html
1、两块板子一定要共地。

2、两块板子的MOSI与MISO不需要交叉连接。

连线方式
SCK----SCK
MOSI----MOSI
MISO----MISO
NSS----NSS

*/
void SPI1_Init (void)
{

		GPIO_InitTypeDef  GPIO_InitStructure;
		SPI_InitTypeDef   SPI_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE); //使能SPI2、PB


	
	//配置MOSI端口
		GPIO_InitStructure.GPIO_Pin = SPI_MOSI_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI_MOSI_GPIO_PORT,&GPIO_InitStructure);
	
	
	
	   //配置MISO端口
		GPIO_InitStructure.GPIO_Pin = SPI_MISO_GPIO_PIN;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(SPI_MISO_GPIO_PORT,&GPIO_InitStructure);
		
		
		
		 //配置SCK端口
		GPIO_InitStructure.GPIO_Pin = SPI_SCK_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI_SCK_GPIO_PORT,&GPIO_InitStructure);



    //配置CS端口
		GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(SPI_CS_PORT,&GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure); //PB12配置成推挽输出 （CS）

	
	
	/*
	  SPI1->DR=0x98;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6? | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure); //PA5、PA6、PA7,复用推挽输出（SCK、MISO、MOSI）
*/







		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //双工模式
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave ; 											//SPI   x模式
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 									//8bit数据

		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //CLK空闲时为高电平
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //CLK上升沿采样，因为上升沿是第二个边沿动作，所以也可以理解为第二个边沿采样

		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                         	//片选用软件控制
		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制

		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; 	//SPI频率：72M/4 = 18M
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 									//高位在前
		SPI_InitStructure.SPI_CRCPolynomial = 7; 														//crc7，stm32spi带硬件ecc
		SPI_Init(SPI1, &SPI_InitStructure);

		SPI_Cmd(SPI1, ENABLE);

		//SPIx_ReadWriteByte(0xff);//启动传输



}



INT8U SPIx_ReadWriteByte(INT8U TxData)
{

  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);


  SPI_I2S_SendData(SPI2, TxData);


  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);


  return SPI_I2S_ReceiveData(SPI2);
}			  




/*********************************
*功能：开机参数设置
*输入：
*********************************/
void StartGetSysParm(void)
 { 
  unsigned int read_data[24],t,check=0; 
  
	  

	 /*
	 //读取子钟1时间 秒  
	 //读取子钟1时间 分
	 //读取子钟1时间 时
	 //读取子钟1时间 步数 
	 //校验 
	 
	
	 */
	 
	 /*
	iic_sw_read(eep_chip_24cxx, iic_eeprom_0page, p_timemu->east_time, 8);
  check=read_data[0]^read_data[1]^read_data[2]^read_data[3];  
  if((read_data[0]<60)&&(read_data[1]<60)&&(read_data[2]<12)&&(read_data[4]==check)){ 
   
    if((read_data[0]==0)&&(read_data[1]==0)&&(read_data[2]==0)&&(read_data[3]==0)) 
			Rest_set1=0xaa; 
    else{
       Subclock1.second=read_data[0];
       Subclock1.minute=read_data[1];
       Subclock1.hour=read_data[2]; 
       Subclock1.step=read_data[3];    
       Rest_set1=0x55; 
     }                  
  }else{       
    Rest_set1=0xaa;      
   } 

  Light_start=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR);    //读取照明开始时间
  if(Light_start>=24)    Light_start=19;

  Light_end=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR+0x02); //读取照明结束时间
  if(Light_end>=24)      Light_end=6;

  Light_en=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR+0x04);  //读取照明使能
  if(Light_en>=2)       Light_en=1;  

  Songs_nummber=(unsigned char) Eeprom_ReadWord(DATA_START+SONG_ADDR);   //读取报时音乐号
  if(Songs_nummber>14)   Songs_nummber=9;

  Strike_nummmber=(unsigned char) Eeprom_ReadWord(DATA_START+STRIKE_ADDR); //读取敲钟号
  if(Strike_nummmber>11) Strike_nummmber=7;


  for(t=0;t<5;t++)     //读取自定义报时音乐长度
   {
    Songs_minite[t+10]=(unsigned char) Eeprom_ReadWord(DATA_START+LONG_ADDR+t*2);
    Songs_second[t+10]=(unsigned char) Eeprom_ReadWord(DATA_START+LONG_ADDR+0x10+t*2);

    if(Songs_minite[t+10]>4||Songs_second[t+10]>59)
     {
      Songs_minite[t+10]=1;
      Songs_second[t+10]=30;
     }
   } 

  for(t=0;t<24;t++)    //读取报时点
   {
     read_data[t]=Eeprom_ReadWord(DATA_START+REPORT_ADDR+t*2);
     if(read_data[t]>1) break;
   } 
  if(t>=24)
   {
     for(t=0;t<24;t++)  Report_time[t]=(unsigned char)read_data[t];
   }
  else
   {
    for(t=0;t<24;t++) 
     Eeprom_WriteWord(DATA_START+REPORT_ADDR+t*2,(unsigned int)Report_time[t]);
   }

  for(t=0;t<2;t++)    //时区设置
   {
     read_data[t]=Eeprom_ReadWord(DATA_START+TIM_ZONE+t*2);     
   }
  if((read_data[0]&0x01)==0&&read_data[1]<=24)
   {
    Time_zone[0]=read_data[0];
    Time_zone[1]=read_data[1];
   }
 else if((read_data[0]&0x01)==0x01&&read_data[1]<=22)
   {
    Time_zone[0]=read_data[0];
    Time_zone[1]=read_data[1];
   }

  read_data[0]=Eeprom_ReadWord(DATA_START+WARN_ADDR);//电机故障记录
  if(read_data[0]<0x10)
   {
    Warn_record=(unsigned char) read_data[0];
   }

  writebyte(0x0e,0x1c);  //RTC 
  Masterclock.year=8;
  Masterclock.month=8;
  Masterclock.day=8;  
  Masterclock.minute=2; 
  Gpscycle=WAITTIME-3;  


*/
	 
 }
 
 
 
 
 

/*********************************
*功能：照明电源控制
*
*********************************/

void Light_Control(void)
 { 
  if(Light_En){
    if(Light_Start<=Light_End){  
      if((p_timemu->hour>=Light_Start && p_timemu->hour<=Light_End))                               
          SSR_ZM_STATUS(1);
      else  
					SSR_ZM_STATUS(0);
     } 
		
    else if(Light_Start>Light_End){ 
      if((p_timemu->hour>=Light_Start || p_timemu->hour<Light_End))   //原来为p_timemu->hour<=Light_End ，现修改为p_timemu->hour<Light_End   added by sjw                      
          SSR_ZM_STATUS(1);
      else  
					SSR_ZM_STATUS(0);
     }
   }else 
				SSR_ZM_STATUS(0); 
 }




/*
功能：播放MP3
输入：MP3序号，格式为mp3_xxxx.mp3
       xxxx为MP3序号
			 
			 

塔钟或吉祥钟发出报时数据
24  0F 04 01 0C 4D 50 33 5F 30    30 36 36 2E 4D 50 33 77   --西敏寺前奏！ 发送3次！！
24  0F 04 01 0C 4D 50 33 5F 30    30 35 36 2E 4D 50 33 74  敲钟n下         发送3次！！


24  0F 04 01 0C 4D 50 33 5F 30    30 36 32 2E 4D 50 33 73  东方红前奏！    发送3次！！
24  0F 04 01 0C 4D 50 33 5F 30    30 35 35 2E 4D 50 33 77敲钟n下          发送3次！！
	 

主板的CPU给MP3模块的数据如下：  
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--发送字节为60个
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16点前奏：
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77   --西敏寺前奏！
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
17点前奏：
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
    24 03 0F 01 1F 12
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 


控制字符ASCII码表
https://www.perfcode.com/p/control-character.html

	
主板的CPU给MP3模块的数据如下：  
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--发送字节为60个
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16点前奏：
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
	
	
	
	
35秒mp3模块发：24 04 00 00 1F 12 24 04 00 0B   16点
整份mp3模块发：24 04 00 0B 

35秒mp3模块发：24 04 00 00 1F 12 24 04 00 0B   17点
整份mp3模块发：24 04 00 0B 
	
任何时段报时的时候，MP3模块都是反馈给主机以上数据   added by sjw  
	
单独测试小板的时候，细节如下  9600 ，n，8,1

比如：  41 00 00 00 00 01 00 0D 0A-------------------共9个字节,播放西敏寺
       41 00 00 00 00 02 00 0D 0A-------------------共9个字节,播放pay

*/




/*********************************
*功 能：报 时 
*输 入：
*********************************/
void Time_Notice(void){
  OS_CPU_SR  	cpu_sr;        
  static INT8U  	play_count=0,mp3_state=0;
  static INT8U 		rythem_number=0,strike_number=0;             //
  static INT8U 		start_hour=0,start_minite=0,start_second=0;  //   
  static INT8U 		end_hour=0,end_minite=0;                     //   
  static INT8U 		power_on_hour=0,power_on_minite=0;           //
  static INT8U 		report_hour=0,report_minute=0;               // 
				 
	INT8U 	k,t,count;
	
/*	
	16点前奏：
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77   --西敏寺前奏！
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
	
	敲点文件15点
	24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B 
24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B 
24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B

	 
*/
  switch(mp3_state){
		
			case 0 :      
				 for(k=0;k<24;k++){      
					 if(Report_Time[k]==1){      	 
						report_hour=k;                 //报时开始时   
						report_minute=0;               //报时开始分  

						 
						rythem_number=Rythem_Number;   //前奏音乐号
						strike_number=Strike_Number;   //敲钟钟声号 
					 
						start_second=59-Rythem_Second[rythem_number];   //报时起始点        
						start_minite=59-(Rythem_Minite[rythem_number]-report_minute);
						start_hour=report_hour-1;
						 
						if(start_hour>=24) start_hour=23;  
						
						power_on_minite=start_minite-1; //功放电源开启时间
						if(power_on_minite>=60){  
								power_on_minite=59;
								power_on_hour=start_hour-1;
								if(power_on_hour>=24) power_on_hour=23;
						}else 
								power_on_hour=start_hour;  
						
						if((p_timemu->hour==power_on_hour)&&(p_timemu->minute==power_on_minite)){   
							
								SSR_BS_STATUS(1);//开启音响电源                        
								mp3_state=1;
							  
								break;  
						}                  
					}   
				 }      
       break; 
			 case 1 :
					if((p_timemu->hour==start_hour)&&(p_timemu->minute==start_minite)&&(p_timemu->second==start_second)){  //			 
							             
							end_minite=report_minute+CLOSE_MINUTE;

							if(end_minite>=60){
								end_minite=0;
								end_hour=report_hour+1;
								if(end_hour>=24) end_hour=0;   
							}else 
								end_hour=report_hour;  
						
							mp3_state=2;
							Mp3_Ok=0;
					 }else if((p_timemu->hour==start_hour)&&(p_timemu->minute==start_minite)&&(p_timemu->second>start_second))   
							mp3_state=7;
			 break;  
			 case 2 :        
				if(Mp3_Ok==0){			
					 
						//MP3_RESET_STATUS(0);
						//OSTimeDlyHMSM(0, 0, 0,100);
						//MP3_RESET_STATUS(1);
					
						/*
					24 03 0F 01 1F 12 
					24 0F 04 01 0C 4D 50 33 5F 30 30 36 35 2E 4D 50 33 74 

					
						for(count=0;count<sizeof(mp3);count++){
							USART_SendData(USART2,*pmp3_second++);
							while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
						}
						pmp3_second=mp3;
						*/
						//OSSemPost(pMainBsSemEve); 
					
					
					  OS_ENTER_CRITICAL();
					  mp3_volume();
						OS_EXIT_CRITICAL();
						DelayMs(10);
						mp3play(Rythem_Name[Rythem_Number]); 
						Mp3_Ok=1; 
					                
				 }else{
						 mp3_state=3;        
						 play_count=0;
						 Mp3_Ok=0;          
				 }    
			break;
				 
				 
				 
    case 3 :
      if((p_timemu->hour==start_hour)&&(p_timemu->minute==59)&&(p_timemu->second==59)){
        play_count=0;
        mp3_state=4;
      }else if((p_timemu->hour==report_hour)&&(p_timemu->minute==report_minute)&&(p_timemu->second>0)) mp3_state=7;    
    break;
			 
    case 4 :       
      if(report_minute==0){  
        if((report_hour%12)==0)  count=12;
        else count=report_hour%12;   
      }else count=1;  
         
      if(Strike_Number<8){////// 
				 DelayMs(6400);
         mp3play(Strike_Head[Strike_Number]+count-1);
         mp3_state=7;           
         play_count=0;       
         Mp3_Ok=0; 
      }      
    break;  
    case 7 : 
      if(p_timemu->hour==end_hour  &&  p_timemu->minute==end_minite){ 
         mp3_state=0;   
           
         SSR_BS_STATUS(0); //关闭报时电源    
       }
    break;
    default:mp3_state=0;
   } 
 }

	     



 
 
 
 
 
 
 
 
 
 
 
 
 
 
 



/*
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
*****************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
*******************************************************************************************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
*******************************************************************************************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
****************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
*/








/*
*********************************************************************************************************

   打印线程，将串口1接收到的数据打印出来

*********************************************************************************************************
*/


/*

对于一些违反常理的问题，一般手册上都会有额外的说明为什么回事这样，所以手册很重要，
就今天而言，我做一个小项目时用到了STM32的PB4这个管脚，然后采用了一般GPIO的通用配置，但是在调试时，却发现这个脚不论怎样都不能置为低，
所以我赶紧去看了下手册，然后发现PB4管脚还有复用功能，是一个JTAG的调试引脚，而且定睛一看，还发现这个管脚在上电复位时会默认为调试引脚的功能，
而它的复用功能才是普通IO口，类似的还有PB3/PA13/PA14等管脚都是一样，要用作普通IO口，需要配置为复用模式。

1、必须先打开复用时钟，再使用函数禁用JTAG调试，否则可能会配置不成功。

STM32 PC13 PC14 PC15 PB3 PB4 PA13 PA14 PA15 做普通IO口笔记
*/
void LedPortSpecialInit(void)
{
		//STM32的PB3、PB4、PA15用作普通IO口设置方法，禁用jtag，使用SW 作者：创客阿酷 https://www.bilibili.com/read/cv23389778/ 出处：bilibili
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);      //使能PA,PB端口时钟   注意和下一句的顺序，必须先开启AFIO时钟		
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);    //对三个引脚进行重映射 :  改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能

	//关闭JTAG的PB3 PB4 PA15的功能，作为普通I/O口使用，不影响SWD的下载调试。 作者：创客阿酷 https://www.bilibili.com/read/cv23389778/ 出处：bilibili
	
	//关闭JTAG的PB3 PB4 PA15的功能，作为普通I/O口使用，不影响SWD的下载调试。 作者：创客阿酷 https://www.bilibili.com/read/cv23389778/ 出处：bilibili


	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);打开此指令后，PA15就不闪烁了，！！！！！！！！！！！！！added by sjw
	//原因参考以下文章：   https://blog.csdn.net/weixin_46528483/article/details/113940390
	//因为执行指令GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);后还是不能用PA15！！！added by sjw
	
	
	//单独关闭PB4的JTAG功能，将PB4做为普通I/O使用。 作者：创客阿酷 https://www.bilibili.com/read/cv23389778/ 出处：bilibili
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);       //释放JTAG脚作为普通IO口, 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
}



void LedBsZm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO,ENABLE );
	//PWR_BackupAccessCmd( ENABLE );/* 允许修改RTC和后备寄存器*/
	//RCC_LSEConfig( RCC_LSE_OFF ); /* 关闭外部低速时钟,PC14、PC15可以用作普通IO*/
	//BKP_TamperPinCmd(DISABLE);  /* 关闭入侵检测功能,PC13可以用作普通IO 作者：创客阿酷 https://www.bilibili.com/read/cv23389778/ 出处：bilibili*/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //GPIO_Mode_AF_PP;  GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //GPIO_Mode_AF_PP;  GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //GPIO_Mode_AF_PP;  GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	
	
	
	SSR_BS_STATUS(0);
	SSR_ZM_STATUS(0);
	
	//PWR_BackupAccessCmd(DISABLE);/* 禁止修改RTC和后备寄存器*/
    //BKP_ITConfig(DISABLE);       /* 禁止TAMPER 中断*/ 作者：创客阿酷 https://www.bilibili.com/read/cv23389778/ 出处：bilibili
	
}

void Mp3Drive_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = MP3_KEY_PIN; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MP3_KEY_PORT, &GPIO_InitStructure); 
	
	



  GPIO_InitStructure.GPIO_Pin = MP3_RESET_PIN; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MP3_RESET_PORT, &GPIO_InitStructure); 
	
	
	 MP3_RESET_STATUS(1);//变高后VS1003小板复位结束！！  added by  sjw
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************

	GPIO_InitStructure.GPIO_Pin = MP3_DECT_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //GPIO_Mode_IPD;//
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MP3_DECT_PORT, &GPIO_InitStructure); 
	
	
	
	
	
	
	GPIO_InitStructure.GPIO_Pin = MP3_ACK_PIN; 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MP3_ACK_PORT, &GPIO_InitStructure); 
	
	//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************
//*************************************************************************


  MP3_KEY_STATUS(1);
  
}



/*
*********************************************************************************************************
*********************************************************************************************************
*                                          uC/OS-II APP HOOKS
*********************************************************************************************************
*********************************************************************************************************
*/

#if (OS_APP_HOOKS_EN > 0)
/*
*********************************************************************************************************
*                                      TASK CREATION HOOK (APPLICATION)
*
* Description : This function is called when a task is created.
*
* Argument : ptcb   is a pointer to the task control block of the task being created.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskCreateHook(OS_TCB* ptcb)
{
}

/*
*********************************************************************************************************
*                                    TASK DELETION HOOK (APPLICATION)
*
* Description : This function is called when a task is deleted.
*
* Argument : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskDelHook(OS_TCB* ptcb)
{
   (void) ptcb;
}

/*
*********************************************************************************************************
*                                      IDLE TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
*               has been added to allow you to do such things as STOP the CPU to conserve power.
*
* Argument : none.
*
* Note     : (1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void App_TaskIdleHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                        STATISTIC TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
*               statistics task.  This allows your application to add functionality to the statistics task.
*
* Argument : none.
*********************************************************************************************************
*/

void App_TaskStatHook(void)
{
}

/*
*********************************************************************************************************
*                                        TASK SWITCH HOOK (APPLICATION)
*
* Description : This function is called when a task switch is performed.  This allows you to perform other
*               operations during a context switch.
*
* Argument : none.
*
* Note     : 1 Interrupts are disabled during this call.
*
*            2  It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                  task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void App_TaskSwHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                     OS_TCBInit() HOOK (APPLICATION)
*
* Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
*               up most of the TCB.
*
* Argument : ptcb    is a pointer to the TCB of the task being created.
*
* Note     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void App_TCBInitHook(OS_TCB* ptcb)
{
   (void) ptcb;
}
#endif

#endif

/******************************************
*
*             LED 流水灯
*
 ****************************************/
void LED1234_ON_OFF(CPU_INT08U Num)
{
    switch (Num) {
        case 0:
        GPIO_SetBits(GPIOD, GPIO_Pin_8);
        GPIO_ResetBits(GPIOD, GPIO_Pin_9);
        GPIO_ResetBits(GPIOD, GPIO_Pin_10);
        GPIO_ResetBits(GPIOD, GPIO_Pin_11);
        break;

        case 1:
        GPIO_ResetBits(GPIOD, GPIO_Pin_8);
        GPIO_SetBits(GPIOD, GPIO_Pin_9);
        GPIO_ResetBits(GPIOD, GPIO_Pin_10);
        GPIO_ResetBits(GPIOD, GPIO_Pin_11);
        break;

        case 2:
        GPIO_ResetBits(GPIOD, GPIO_Pin_8);
        GPIO_ResetBits(GPIOD, GPIO_Pin_9);
        GPIO_SetBits(GPIOD, GPIO_Pin_10);
        GPIO_ResetBits(GPIOD, GPIO_Pin_11);
        break;

        case 3:
        GPIO_ResetBits(GPIOD, GPIO_Pin_8);
        GPIO_ResetBits(GPIOD, GPIO_Pin_9);
        GPIO_ResetBits(GPIOD, GPIO_Pin_10);
        GPIO_SetBits(GPIOD, GPIO_Pin_11);
        break;

        default:
        break;
    }
}


/*
2．4 液晶显示模块 
　　LCD3310液晶是一个48行84列的液晶显示器。其带有低功耗PCD8544的CMOS LCD控制驱动器，串行输入速度最高可达4．O Mb／s。
为了让LCD3310液晶能够显示4行12×12的汉字，系统开辟了一个6×84字节的缓冲区。写液晶时就不用直接写入LCD3310的静态 DDRAM了，
可以先写入系统为它开辟的数据缓冲区，最后再刷新修改的部分就可以显示出要显示的内容。LCD3310的接口采用SPI模式，其电路如图6 所示。 

3 软件设计 
　　图7是MP3播放器的软件流程。系统启动后，先初始化硬件模块。由单片机通过FAT32文件系统接口读取SD卡的一些基本信息，
如容量、扇区大小、FAT 表以及根目录所在的起始扇区等。通过这些信息就可以找出SD卡是否有可以播放的音乐文件。
若有，单片机通过SPI总线方式读出音频信息，并将歌曲的码流信息送入到VS1003芯片中，
通过VS1003解码芯片及其内含的高质量立体声DAC和耳机驱动电路，实现MP3歌曲的播放功能。
在按键的控制下，通过 LCD3310中菜单选项的选择，实现对歌曲选择及音量控制等功能；
在播放的同时，LCD3310上显示的信息除歌曲名称外，还包括进度和音量等。 


　　经过运行测试，系统可以正常流畅地播放出320 kb／s的高音质MP3音乐文件，
而且在使用500 mA锂电池的情况下，可以连续正常地播放长达10个小时。可见，其功耗比较低。 

*/




static	void GPIO_Motor_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
		 													 
	
	

//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE );  
//	GPIO_InitStruct.GPIO_Pin   =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15  ;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOC, &GPIO_InitStruct); 
//	
//	
//	PWR_BackupAccessCmd(ENABLE);//允许修改RTC 和后备寄存器 
//    RCC_LSEConfig(RCC_LSE_OFF);//关闭外部低速外部时钟信号功能 后，PC13 PC14 PC15 才可以当普通IO用。 
//    PWR_BackupAccessCmd(DISABLE);//禁止修改后备寄存器 
	

	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC  | RCC_APB2Periph_GPIOE, ENABLE );  
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_OD;//
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOB, &GPIO_InitStruct);

  	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12  ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOC, &GPIO_InitStruct);
		
		
		
		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOE, &GPIO_InitStruct);
  	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9  ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOC, &GPIO_InitStruct);
		
		
		
			
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOE, &GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		
  	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11  ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOC, &GPIO_InitStruct);


    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOE, &GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		
  	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10  ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		 
		GPIO_Init(GPIOC, &GPIO_InitStruct);

		
		EAST_ZZ_IDLE;
		EAST_FZ_IDLE;
		
		SOUTH_ZZ_IDLE;
		SOUTH_FZ_IDLE;
		
		WEST_ZZ_IDLE;
		WEST_FZ_IDLE;
		
		NORTH_ZZ_IDLE;
		NORTH_FZ_IDLE;
		
	
}


/*********************************
*功能：开机参数设置
*输入：
*********************************/

static	void GPIO_I2C_Config(void)
{
	struct tm now;
	
	 iic_sw_init();
	// get_iic_setting();//读取子钟时间、报时开关设定的小时、报时前奏及钟声和照明开关的设定！！added by sjw
	

	
}








static	void GPIO_Key_Config(void)
{
	
	EXTI_InitTypeDef EXTI_InitStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;//将PE10绑定在EXTI_Line10上作为PPS信号的输入，下沿沿有效!!added by sjw
	
	
	
	
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE );  //PE10为输入中断！！
    GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
		GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	
		
		
	
	  EXTI_InitStructure.EXTI_Line 	= EXTI_Line10;
    EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger =  EXTI_Trigger_Falling;//EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource10);
    EXTI_ClearITPendingBit(EXTI_Line10);	



    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	  
}





static	void N31_pps_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;//将PA11作为pps信号的输入端!   added by sjw
	
	
	
	
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );  //PA11为输入中断！！
    GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
    EXTI_InitStructure.EXTI_Line 	= EXTI_Line11;
    EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger =  EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);
    EXTI_ClearITPendingBit(EXTI_Line11);	



    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
}







//直接交换了地址里面的内容，也就是值！！
//在函数内部确实交换了数据内容，退出函数后，没有交换！！
void MainSwapValue(INT16U *p1,INT16U *p2)
{
	INT16U value;
	value=*p1;
	*p1=*p2;
	*p2=value;
}

//直接交换了地址里面的内容，也就是值！！
void MainSwapValueErr(volatile INT16U *px,volatile INT16U *py)
{
	volatile INT16U *pt;
	DelayMs(10);
	pt=px;
	DelayMs(20);
	*px=*py;
	DelayMs(30);
	py=pt;
	DelayMs(40);
}

void MainSwapAddr(INT16U **p1,INT16U **p2)//要交换内容，间接用交换地址来实现。
{
	INT16U *pvalue;
	pvalue=*p1;
	*p1=*p2;
	*p2=pvalue;
}
	


INT8U MainFindElem(Sqlist L,INT8U x)
{
	INT8U i;
	for(i=0;i<L.length;i++)
	{
		if(x<L.data[i])
			break;
			//return i;//或者该语句也可以！
	}
		return i;
	
}

void MainInsertElem(Sqlist *L,INT8U x)
{
	
	INT8U p,i;
	p=MainFindElem(*L,x);
	for(i=L->length-1;i>=p;i--)
		L->data[i+1]=L->data[i];
	L->data[p]=x;
	++(L->length);
}

void MainMerge(LNode *head1,LNode *head2,LNode **head3)
{
	LNode *p=head1;
	LNode *q=head2;
	LNode **r=head3;
	
	while(p->next!=NULL && q->next!=NULL)
	{
		if(p->data<=q->data)
		{
			r=&p;
			r=&(p->next);
			r=&q;
		}else{
			r=&q;
			r=&(q->next);
			r=&p;
		}
	}
	if(p->next==NULL) r=&(q->next);
	if(q->next==NULL) r=&(p->next);
	
	
}



void MainInsertLnode(LNode *L,INT8U x)
{
	INT8U i;
	if(L->next==NULL) L->data=x;
	else if(x<L->data)
	{
		;
	}
	
}


void 	NoKeyProm(void)
{
}
void 	KeyProm1(void)
{
}
void 	KeyProm2(void)
{
}
void 	KeyProm3(void)
{
}
void 	KeyProm4(void)
{
}
void 	KeyProm5(void)
{
}
void 	KeyProm6(void)
{
}

INT8U	ReadKey(void)
{
	return 0;
}

/*输出格式如下：

产品内部Flash大小为：512K字节！ 	 www.armjishu.com

K9F1G08U0B
  1024 Blocks, 64 pages per block, 2048 + 64 bytes per page
0------- -------- -------- -------- -------- -------- -------- -------- 
------- -------- -------- -------- -------- -------- -------- -------- 
-------- -------- -------- -------- -------- ------- -------- -------- 
-------- -------- -------- -------- -------- -------- 0------- -------- 
--000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 0000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000 00000000 00000000 00000000 -0-000-0 
Bad Block Count = 4  ( < 80 is OK), Used = 257 
  67  173  443  598 

Bad Block Count = 4


*/

/*
————————————————
版权声明：本文为CSDN博主「shaohui973」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/shaohui973/article/details/109627989
hamming weight algorithm(汉明算法)以及kernel的实现
https://blog.csdn.net/shaohui973/article/details/109627989

汉明距离是使用在数据传输差错控制编码里面的，汉明距离是一个概念
对两个字符串进行异或运算，并统计结果为1的个数，那么这个数就是汉明距离。
汉明重量是字符串相对于同样长度的零字符串的汉明距离，也就是说，它是字符串中非零的元素个数：
对于二进制字符串来说，就是 1 的个数，所以 11101 的汉明重量是 4。
*/
INT32U Hamming_weight(uint32_t n ) {

    n = (n&0x55555555) + ((n>>1)&0x55555555);

    n = (n&0x33333333) + ((n>>2)&0x33333333);

    n = (n&0x0f0f0f0f) + ((n>>4)&0x0f0f0f0f);

    n = (n&0x00ff00ff) + ((n>>8)&0x00ff00ff);

    n = (n&0x0000ffff) + ((n>>16)&0x0000ffff);

    return n;

}





	// FSMC_NAND_Test();
	//配置修改参数如下:::
	 /*
	 1.将文件ffconf.h的第40行  _USE_MKFS         设置为  1
	 2.	将文件ffconf.h的第36行_USE_STRFUNC	      设置为  1
	 
	 3. 将文件ffconf.h的第48行_USE_LABEL		      设置为  1	
	 
	 4.将文件ffconf.h的第122行 _FS_RPATH         设置为  1	
	 5.将文件ffconf.h的第148行	_MULTI_PARTITION	设置为  1	
	 
	 7.将文件demo_nand_fatfs.h的第27行  #define BUF_SIZE				(4*1024)   修改成(2*1024)
	 
	 8.将文件integer.h的第7行 添加上  #define _WIN32             added by sjw
	 9.将文件bsp_nand_flash.h的第101行 #define NAND_MAX_ZONE  修改为102行上！
	 10.将文件bsp_nand_flash.h的第97行 #define NAND_PAGE_SIZE  修改为98行上！
	 
	 11.将文件bsp_nand_flash.h的第105行屏蔽
	 12.将文件bsp_nand_flash.h的第97行#define NAND_PAGE_SIZE             ((uint16_t)0x0800) 修改为0x0200
	 
	 13.将文件bsp_nand_flash.h的第99行#define NAND_BLOCK_SIZE            ((uint16_t)0x0040) 修改为0x20
	 
	 14.将文件bsp_nand_flash.h的第100行	#define NAND_ZONE_SIZE           ((uint16_t)0x0400) 修改为0x1000(4096个块)
	 15.将文件bsp_nand_flash.h的第101行#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0040) 修改为0x10
	 
	 16.将文件bsp_nand_flash.h的第112行#define NAND_ADDR_5					       1修改为0
	 17.将文件bsp_nand_flash.h的第125行#define NAND_BLOCK_COUNT			   1024 // 块个数 修改成4096个块
   18.将文件famc_nand.h的第56行#define FLASH_MAX_ADDR 0x7FFFFFF变为0x4000000 这是64M
	 19.将文件bsp_nand_flash.h的第108行#define NAND_MAX_ZONE       变为       ((uint16_t)0x0004)
	 20.将文件bsp_nand_flash.h的第133行#define BI_OFFSET				    0		块内第1个page备用区的第1个字节是坏块标志  变为6
   21.将文件bsp_nand_flash.c的第1651行到1655行屏蔽！
	 22.将文件famc_nand.h的第59行#define FLASH_BLOCK_SIZE 0x20000  128k---->16K
	 23.将文件bsp_nand_flash.h的第137行#define VALID_SPARE_SIZE		4变为6		 实际使用的备用区大小,用于函数内部声明数据缓冲区大小 


	 
	 //K9F1208U0M 64M nand flash 手册阅读以及相关驱动程序分析
   //https://blog.csdn.net/hfdghjh/article/details/86776939
	  

	
	//https://blog.csdn.net/xiaoluoshan/article/details/51695121
	//Nandflash K9F1208U0B学习   此资料非常实用！！
	
	STM32 IO模拟nand flash的高手请进
	https://bbs.csdn.net/topics/380034182
	
	
	NAND FLASH存储器实现在系统中的读写和控制 也间接介绍了模拟gpio端口的操作时序！，也挺好的了
	https://www.elecfans.com/d/744442.html
	
	
	//LUT查找表实现各种RAM及ROM原理精讲
	//https://blog.csdn.net/weiaipan1314/article/details/104327009
	
	//Stm32文件系统FATFS（开始于2021-09-09）
	//https://blog.csdn.net/weixin_51915497/article/details/120201305?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~aggregatepage~first_rank_ecpm_v1~rank_v31_ecpm-7-120201305.pc_agg_new_rank&utm_term=fatfs+fdisk%E4%B8%8Esfd%E7%9A%84%E5%8C%BA%E5%88%AB&spm=1000.2123.3001.4430
	 
	
	
	//https://blog.csdn.net/hanchaoman/article/details/102660884
	//STM32-移植FATFS的NANDFLASH驱动
	//使用原来板卡自带的存储芯片DF2M8HM（里面已经有mp3报时文件了），用新103ve操作，格式化失败，补鞥成功！显示FR_NOT_READY，
	//仿真测试,发现1024个块全部为坏块，因为底层我没有操作正确！
	//FatFs学习(1)——枚举：返回值FRESULT            https://blog.csdn.net/qq_38318207/article/details/108554207 
	//三星第一个内存芯片个格式化的时候，好块为0x0183个block
	/*
		第个内存芯片个格式化的时候，好块为0x18c个block                             第2个内存芯片个格式化的时候，好块为0x3ea个block
		

	
	//https://www.zhihu.com/question/62799132
	//一个合格的嵌入式软件开发工程师要掌握哪些知识？
	
	
	//【文件系统将对文件的块的操作转换为对物理存储器扇区的各种操作】
	//https://blog.csdn.net/hanchaoman/article/details/86607456
	 
	 
	 https://bbs.elecfans.com/jishu_1096766_1_1.html
	 
	 在单步调试时，找到错误位置首先，进入f_open，在f_open中有find_volume函数，
	 在这个函数中，从0扇区读取fat所占扇区大小、每个扇区字节数、fat个数、根目录位置等有关信息，并且如果该函数返回值不是FR_OK，将直接退出f_open函数；

进入find_volume函数，在find_volume函数中有这样一行代码：
fmt = check_f( fs, bsect );并且根据返回值，也就是fmt的值，来确定是否为fat文件系统；

然后进入check_fs函数，发现先进行move_window操作，然后判断结尾是否为0XAA55，开头的跳转指令是否是0XEB 0X** 0X90，然后判断是否找到FAT或是FAT3字样；

在move_window函数中，主要实现了fs->win[]中的数据回写，然后重新读取指定扇区的内容，
结果，问题就出来这里，在读取0扇区的内容时，读取的内容错误，因此就导致了在check_fs函数中判断扇区结尾是否是0XAA55时，发生了错误，反回了2，
然后在find_volume函数中，判断fmt时，返回了FR_NO_FILESYSTEM；
	 

stm32f2系列：基于NAND FLASH之上的Fatfs的移植   此文思想可以借鉴 added by sjw
http://blog.sina.com.cn/s/blog_c5c2bd470102v2p2.html
	 
	 
	 
	
		
		
		STM32 USB部分中断函数简要分析
		https://blog.csdn.net/yxfabcdefg/article/details/52336070?locationNum=4&fps=1
		
		
		
		
		http://www.elecfans.com/emb/arm/20171106575725.html
		
		
		stm32f103 usb驱动电脑无法识别解决办法：
　　1、usb所使用的IO口在设置为usb后自动分配功能，不需要再设置，一定要设置的话会被忽略，所以也没什么影响。

　　2、usb时钟配置只有两种可用：主频72M，usb时钟1.5分频；主频48M，usb时钟1分频。

　　3、PA12（USBP / D+）一定要接1.5k的上拉电阻，用于电脑识别设备，官方库使用了lO口控制了上拉，
       这样方便软件控制断开与重新连接，直接上拉到电源也是可以的，不过需要断开和重新连接时只能手动插拔。

　　4、stm32f103的can和usb不能同时使用，can的时钟打开后，电脑就会识别不出usb设备，
        所以两个功能都要用到的话，还是换成f105或f107，这两种型号是可以同时使用的。
		
		
	
	
	
	
		
		基于STM32的USB枚举过程学习笔记（转）
		https://www.cnblogs.com/erhu-67786482/p/10790814.htm	
		
		
		
		
		
		https://blog.csdn.net/qq236106303/article/details/8177568
		基于STM32的USB枚举过程学习笔记(二)
		接下来介绍USB设备的枚举，枚举就是从设备读取各种描述符信息，这样主机就可以根据这些信息来加载合适的驱动，从而知道是什么样的设备，如何进行通信。
		枚举过程使用的是控制传输。控制传输可以保证数据的正确性。控制传输分三个过程：建立过程，可选数据过程及状态过程
		
				
		STM32-USB学习笔记（一） USB基础
		https://www.doc88.com/p-505935487642.html

		STM32 USB部分中断函数简要分析
		https://blog.csdn.net/yxfabcdefg/article/details/52336070

		https://www.pianshen.com/article/97651154818/

		基于STM32的USB枚举过程学习笔记(二)
		https://blog.csdn.net/qq236106303/article/details/8177568   和
		http://www.360doc.com/content/17/1025/06/6889381_697883568.shtml
		http://www.360doc.com/content/17/1025/06/6889381_697884130.shtml


		基于STM32的USB枚举过程学习笔记(三)
		https://blog.csdn.net/qq236106303/article/details/8179005


		基于STM32的USB枚举过程学习笔记(四)
		https://blog.csdn.net/qq236106303/article/details/8181336?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&utm_relevant_index=2

    
		USB枚举过程分析
		https://blog.csdn.net/duan_xiaosu/article/details/68930643
		在这个网站的内容可以帮助我将usb枚举的各个字段理解透切！非常不错的好文章！
		
		

	 
	
	 
	 	
  		bDeviceState 全局变量在usb_pwr.c中定义，用于表示USB Device的状态 
	  typedef enum _DEVICE_STATE
		{
			UNCONNECTED,
			ATTACHED,
			POWERED,
			SUSPENDED,
			ADDRESSED,
			CONFIGURED
		} DEVICE_STATE;
  	
  	  	
  	//还有一个USB开关
  	// Enable the SDIO AHB Clock 
		
	*/
	
	
	 




