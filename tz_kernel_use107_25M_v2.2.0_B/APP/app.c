/*
��������һ����Ч�Ĳ���ʹ���޷����ӵ��˴�ӡ���С��������ϵͳ����Ա��ϵ
https://baijiahao.baidu.com/s?id=1739583361867564493&wfr=spider&for=pc







STM32�����б��������ܣ�Ĭ�ϸ��ù��ܺ��ض��幦�ܵ�����

1 �����ܾ���STM32����IO�ڣ�������û�����ӵģ����ǿ���ֱ����������ߵ͵�ƽ

ʹ��ʱ����Ҫ��ʼ��GPIO�ṹ����������򿪶˿ڵ�ʱ��

2 Ĭ�ϸ��ù��������������ӵ�IO�ڣ���Ƭ��ͨ����������������IO��

ʹ��ʱ����Ҫ��ʼ��GPIO�ṹ�������IO�ڵĹ���ģʽҪ����STM32���Ĳο��ֲ��У�IO�ڸ��ù��ܵ����ù���ģʽ��
����ʱ���������ܵ�Ψһ�������IO�ڵĹ���ģʽ�Ĳ�ͬ��

3 ����������費���ӵ�Ĭ�������ϣ��Ǿ͸��ݡ��ض��幦�ܡ���һ�������¶����������ӵ�IO�ڡ�һ��������ǲ����õ���

 

ע�⣺
һ����Ҫ��AFIO�Ĵ�������ʱ��һ��Ҫ��AFIO��ʱ�ӣ�һ����ʹ���ⲿ�ж�EXTI�����������ض���ʱ��
--------------------------------------------------------------------------------------------------







��Ӧ�ĵ�·��ΪBMT-DP-MAIN-01B.PCB
����һ�������б���ģ��ߴ��������һ�鱳�壬�ͺ�ΪGSFG-DP-1A.PCB
�趨����Ϊ����������ʾ����������֤������
�趨ż��Ϊ�ȶ�������ʾ�����Ѿ��õ���֤���ο�LINUX�ں˵Ŀ�����������

�������Ŷ�����Ȼ����103�ģ���������407��Ҳ���Խ������added by sjw 10.18

STM32 = ����ARM��32λ΢������
F     = ͨ������ 
103   = ��ǿ�� 
R     = 64��                                  
V     = 100��                                  
Z     = 144�� 
C     = 256K�ֽڵ�����洢��                                  
D     = 384K�ֽڵ�����洢��                                  
E     = 512K�ֽڵ�����洢��
H     = BGA                                  
T     = LQFP                                  
Y     = WLCSP64 
 
STM32F103VET6Ƭ����Դ
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
           2 ��16λ���������ƺ�     2 ��16λ������ʱ��        �����ͺʹ�����
           ����ɲ�������ڵ�����Ƶ�PWM�߼����ƶ�ʱ��   ��������DAC 
                            
                                      
SysTick : 1 SysTick Timer, ϵͳʱ�䶨ʱ����24λ�Լ��ͼ�����
SPI/I2S : 3 SPI/I2S, �������ɸ���Ϊ I2S
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
           I2C1��PB6-I2C1_SCL��PB7-I2C1_SDA
           I2C2��PB10-I2C2_SCL��PB11-12C2_SDA
           
 					 USART   : 5 USART,
           PA9  - USART1(Tx) - USART1�����ڳ�������
           PA10 - USART1(Rx) 
                   
 					 USB     : 1 USB 2.0 Full Speed Interface,
 					 CAN     : 1 CAN 2.0B Active,
           PB8 - CAN_RX
           PB9 - CAN_TX        
					                   
					 A/D     : 3 12-bit 16-ch A/D Converter, 
					 D/A     : 2 12-bit D/A Converter, 
					 SDIO    : 1 SDIO, 
					 GPIO    ��Fast I/O Ports
					 DMA     : 12 ͨ�� DMA ������
        ֧�ֵ����裺��ʱ����ADC��DAC��SDIO��
           I2S��SPI��I2C �� USART

-----------------------------------------------------------------------------
STM32F103VET6���Ź���
��λ  �ܽ�����         ����    I/O��ƽ    ������        Ĭ�ϸ��ù���                        ��ӳ�䶨�幦��
 1     PE2              I/O     FT         PE2           TRACECK/FSMC_A23    STM32����������д�˴�FT�����ſ�����5V�Ǿ��ǿ��Խ�5V��
 2     PE3              I/O     FT         PE3           TRACED0/FSMC_A19	   ����������Եģ�������ѹ���ˣ�Ҫ���Ǻ÷������衣
 3     PE4              I/O     FT         PE4           TRACED1/FSMC_A20		 Ӱ��϶��У�����������I/O����ѹ������ǯλ�����ܡ�
 4     PE5              I/O     FT         PE5           TRACED2/FSMC_A21		 ��FT��ǵĽ�����Ϊ�����OD���ʱ���ԣ�����Ϊ����������С�
 5     PE6              I/O     FT         PE6           TRACED3/FSMC_A22
 ------------------------------------------------------------------------------
 6     VBAT             S       -          VBAT	�鵽FT�ĺ��壬Ҳ�����Ǹ�5V���̵�IO�ṹ���ṹ�ڲ�ȷʵ��һ�Զ����ܣ������Ǹ���VDD�Ķ������ƺ��е����⣬
 																								������������IO�������ѹ����5Vʱ���Ż���VDD���������������������ܵĽ�ѹ�Ƚϴ�
																								ȥ��datasheet����һ�ű���д�˺ܶ�io�ڣ���Щ���ˡ�FT���ľ��ǿ���5v
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

 14    NRST             I/O     -          NRST				 �͵�ƽ��λ
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
 70    PA11              I/O    FT         PA11          USART1_CTS/USBDM USBDM = USB Data Minus��USB���ݸ��źţ�
                                                         CAN_RX (7) /TIM1_CH4 (7)
 71    PA12              I/O    FT         PA12          USART1_RTS/USBDP/USBDP = USB Data Positive��USB�������ź�
                                                         CAN_TX (7) /TIM1_ETR (7)
 72    PA13              I/O    FT         JTMS/SWDIO                                        PA13
-----------------------------------------------------------------------------

 73    δ����
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
 
 ������PB6 PB7 ��ʹ��FSMCʱ�ӡ���ͬʱ����I2C��FSMC��Ȼ�ǲ����ܵģ���ʱʹ���ǿ��Եġ�
 �������FSMCʱ�ӣ���ʹ����FSMC_NADV���ţ�����������Ż���Ĭ�ϳɸߵ�ƽ���Ӷ���I2C1_SDA��ͻ��
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




 ʹ��FSMC��STM32F103ZE�ĸ�λ���ݵ�ַ������IO��ʹ��
 ���Ҫʹ��ĳ���ܽ�ΪFSMC���ܣ������ö�Ӧ��GPIOΪ����������ܣ�
 �����ʹ������FSMC���ܣ���ֻ�����ö�Ӧ��GPIOΪ��ͨ�������(�����©)�����빦�ܼ��ɡ�

 FSMC��Ϊ�ĸ�BANK������BANK1ͨ��NE[1..4]����Ƭѡ�ĸ����裬һ�������������˵��Ҫ���ľ���BANK1�Ĳ�����
 ����NOR Flash��LCD�Ĳ�������������Ҫ˵BANK1�����á�
 ��BANK1�Ĳ�����Ҫ����������FSMC_BCRx[1..4]��FSMC_BTRx[1..4]��FSMC_BWTRx[1..4]�Ĵ��������⼸���Ĵ���������Ū�����˾ͻ������ˣ�
 FSMC_BCRx�ǿ������á�
 FSMC_BTRx�Ƕ�дʱ�����á�
 FSMC_BWTRx��дʱ�����ã�����������FSMC_BTRx��ͬ��
 ���FSMC_BCRx[1..4]��������EXTMODλ, ��FSMC_BTRx[1..4]��FSMC_BWTRx[1..4]����ʱ��Ĵ����ֱ��Ӧ����д������
 ���δ����EXTMODλ�������дʹ����ͬ��ʱ��FSMC_BTRx[1..4]��



-----------------------------------------------------------------------------
I=����  O=���  S=��Դ   HIZ=����   FT=����5��
TIM2_CH1_ETR��ʾ�������ù���ΪTIM2_TI1����TIM2_ETR



LQFP48��LQFP64���Ŷ���(�����ڵ�Ϊ48���ŵĶ��壩
��λ  �ܽ�����            ����    I/O��ƽ    �����ܣ���λ��        Ĭ�ϸ��ù���                        �ض��幦��
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

SPI��ʱ�Ӳ���ͻ���Ϳ��ԣ�֮ǰ���Ǽȿ� spi��ʱ�ӣ���Ϊ ���PA6���ż���SPI���ܣ����� TIM3�� CH1 ���ܣ���� ʱ����SPIʱ�ӣ�
Ȼ��ʵ�õ���TIM3 CH1 ���ܣ�������Ͳ���ȷ�ˡ���ֹͣ��SPIʱ�ӣ���OK�ˡ�

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


һ��ARM�������3���֣�RO��RW��ZI��RO�ǳ����е�ָ��ͳ�����RW�ǳ����е��ѳ�ʼ������;ZI�ǳ����е�δ��ʼ���ı���.
������3��˵���������Ϊ��RO����readonly��RW����read/write��ZI����zero

bss�Σ�
BSS�Σ�bsssegment��ͨ����ָ������ų�����δ��ʼ����ȫ�ֱ�����һ���ڴ�����
BSS��Ӣ��BlockStarted by Symbol�ļ�ơ�BSS�����ھ�̬�ڴ���䡣

data�Σ�
���ݶΣ�datasegment��ͨ����ָ������ų������ѳ�ʼ����ȫ�ֱ�����һ���ڴ��������ݶ����ھ�̬�ڴ���䡣

text�Σ�
����Σ�codesegment/textsegment��ͨ����ָ������ų���ִ�д����һ���ڴ�����
�ⲿ������Ĵ�С�ڳ�������ǰ���Ѿ�ȷ���������ڴ�����ͨ������ֻ��,ĳЩ�ܹ�Ҳ��������Ϊ��д���������޸ĳ���
�ڴ�����У�Ҳ�п��ܰ���һЩֻ���ĳ��������������ַ��������ȡ�

rodata�Σ�
���C�е��ַ�����#define����ĳ���

heap�ѣ�
�������ڴ�Ž��������б���̬������ڴ�Σ����Ĵ�С�����̶����ɶ�̬���Ż�������
�����̵���malloc�Ⱥ��������ڴ�ʱ���·�����ڴ�ͱ���̬��ӵ����ϣ��ѱ����ţ���
������free�Ⱥ����ͷ��ڴ�ʱ�����ͷŵ��ڴ�Ӷ��б��޳����ѱ�������

stackջ��
���û���ų�����ʱ�����ľֲ�������Ҳ����˵���Ǻ���������{}���ж���ı���
����������static�����ı�����static��ζ�������ݶ��д�ű�������
�������⣬�ں���������ʱ�������Ҳ�ᱻѹ�뷢����õĽ���ջ�У����Ҵ������ý����󣬺����ķ���ֵҲ�ᱻ��Ż�ջ�С�
����ջ���Ƚ��ȳ��ص㣬����ջ�ر𷽱���������/�ָ������ֳ���
����������Ͻ������ǿ��԰Ѷ�ջ����һ���Ĵ桢������ʱ���ݵ��ڴ�����


ÿ���û������񶼱�������¼������ı��ģ�ͣ���uC/OS-II��Ӧ�ó��򶼱����ǡ��¼������ı��ģ�͡���
һ���������ȵȴ�һ���¼��ķ������¼�������ϵͳ�жϷ����ģ�Ҳ�������������񷢳��ģ��ֿ�������������ȴ���ʱ��Ƭ��
��һ���¼������ˣ�����������Ӧ��������������ֿ�ʼ�ȴ���һ���¼��ķ�����
����ܶ���ʼ��������ģ�;��ǡ��¼������ı��ģ�͡����¼�����ģ��Ҳ�������ж�����ģ�ͣ�
uC/OS-II�¼������������������棺
����(1)�жϷ��������͵��¼�
����(2)ϵͳ��ʱʱ�䵽�������
����(3)���������͵��¼���
���С��жϷ��������͵��¼�������ָÿ����Ӳ���жϷ�������ô�жϷ������ͻ����¼�����ʽ��������
���ȴ����¼���������ȼ�����ͻ����ϵ������У���ϵͳ��ʱʱ�䵽������ġ��¼���ʵҲ��Ӳ���жϵ��µģ�
�Ǿ���ϵͳ��ʱ���жϡ��������������͵��¼������������������������ģ�������ȫ�ġ����¼��������ܡ����¼������ǡ�Ӳ�¼�����
��������uC/OS-II�����л���ԭ����ǡ��¼����������û���дӦ�ô����ʱ��һ��Ҫ���ֳ����¼������ı��ģ�͡���
	exti_imr
		
RO�ǳ����е�ָ��ͳ���
RW�ǳ����е��ѳ�ʼ������
ZI�ǳ����е�δ��ʼ���ı���
������3��˵���������Ϊ��
RO����readonly��
RW����read/write��
ZI����zero 
					

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


INT32U   NTP;















					// �ļ�ϵͳ��صı���			
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
			
					OS_EVENT 	*Mutex_USART1; // ����USART1�������¼�	
					OS_EVENT 	*Mutex_USART2; // ����USART2�������¼�
					OS_EVENT 	*Mutex_FATFS;  // ����FATFS�������¼�		
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


static  	OS_STK 		App_TaskStartStk[APP_TASK_START_STK_SIZE];  // TaskStart �����ջ 
static  	OS_STK 		AppTask1Stk[APP_TASK1_STK_SIZE];//  �����ջ 
static  	OS_STK 		AppTask2Stk[APP_TASK2_STK_SIZE ]; //AppTaskUsart2�����ջ 
static  	OS_STK 		AppTask3Stk[APP_TASK3_STK_SIZE ]; //AppTaskUsart3�����ջ 
static  	OS_STK 		AppTask4Stk[APP_TASK4_STK_SIZE ]; //AppTaskUsart4�����ջ 
static  	OS_STK 		AppTask5Stk[APP_TASK5_STK_SIZE ]; //AppTaskUsart5�����ջ 
static  	OS_STK 		AppTask6Stk[APP_TASK6_STK_SIZE ]; //AppTaskUsart6�����ջ 
static  	OS_STK 		AppTask7Stk[APP_TASK7_STK_SIZE ]; //AppTaskUsart7�����ջ 
static  	OS_STK 		AppTask8Stk[APP_TASK8_STK_SIZE ]; //AppTaskUsart7�����ջ 




static  	void  		App_TaskStart(void* p_arg);          // ���� TaskStart ����
static  	void  		AppTask1(void* p_arg);      // ���� TaskPrintf ����
static  	void 		  AppTask2(void* p_arg);        // ���� ����CPUƵ�ʵĺ���
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









static		void 		  LED1234_ON_OFF(CPU_INT08U Num);             // ������ˮ�ƺ���
extern		BOOLEAN		Vs1003bPowOnFlag;
extern		INT8U 		USART2_RX_FIFO[USART2_RX_CNT];  		        // ���廷������
extern		void 		  DelayMs(vu32 m);
extern		void 		  DelayUs(vu32 m);	


extern    void DemoFatFS(uint8_t *cmd);
extern		INT8U 	USART1_RX_FIFO[USART1_RX_CNT];  			// ���廷������
extern		INT8U 	*pPut_USART1_RX_FIFO ; 	// ���廷���������ָ��
extern		INT8U 	*pGet_USART1_RX_FIFO ; 	// ���廷������ȡ��ָ��



void MainSwapValue(INT16U *p1,INT16U *p2);//ֱ�ӽ����˵�ַ��������ݣ�Ҳ����ֵ����
void MainSwapValueErr(volatile INT16U *p1,volatile INT16U *p2);//ֱ�ӽ����˵�ַ��������ݣ�Ҳ����ֵ����
void MainSwapAddr(INT16U **p1,INT16U **p2);//Ҫ�������ݣ�����ý�����ַ��ʵ�֡�
void  BspNand_Init(void);
void LedBsZm_Init(void);
void Mp3Drive_Init(void);

void LedPortSpecialInit(void);
void MainProcessTimeAdd(config data,INT8U order);
void MainProcessTimeSub(config data,INT8U order);


/*
*********************************************************************************************************
                                                main()
												RE:__use_two_region_memory��macro-libʲô��ϵ��
_use_two_region_memory����ָ���洢��ģʽΪ˫��ģʽ����һ���ִ���������ջ�ռ䣬�����Ĵ洢�����ڶѿռ䣬�����ռ����Ϊ0��
���ǣ������Ͳ��ܵ���malloc()�ڴ���亯���������ռ�Ҳ�����ɴ洢�����䣬Ҳ���Դ�ִ�л����м̳С�
*********************************************************************************************************
*/


//��2015��11��30����һ�����һ��200R���裬һ��10k������������5����Ƭ��ĸ�Ӻ�3.3��arm��Ƭ��֮���rs485ͨѶ�����⣡
//�ð汾�������usart2�н���һ���ֽں���������3�У��������д���ʱ����Ȼ���Բ�̫���գ�����©����
//��Ϊ����5��ͨѶ���arm��ͨѶ�漰���Ĺ����Դ���⣬RS485ͨѶ���ɿ�������2015��12��2�ս�
//ARM���ϵ�ͨѶоƬ75LBC184�ĵ����ţ�A�����һ��10K���������裬���߽ţ�B�����һ��10K�����������



//���������忨ͨѶ���ɿ������⣬�����ARM��嵽���Ӱ��Ϻ��÷��������治�˵����⡣����
//��������vs1003оƬ�������¶ȱȽ��̣���ӱ�ʱ�������ļ��رգ���Ҳ�رգ���ÿ��Сʱ58�ֵ�ʱ��λvs1003׼������mp3�ļ�
//������Ϻ��оƬ���ڵ���״̬��
//���ó�����Ϊ���ճ�Ʒ��������ˣ���

/*
��һ����ʵ��˳���Ĳ���
��֪һ��˳������е�Ԫ�ص����������У����һ���㷨������һ��Ԫ��x��xΪint�ͣ��󱣳ָ�˳�����Ȼ�����������У��������ܳɹ���
ʵ�ַ�����
1���ҵ���x��ĵ�һ��Ԫ�ص�λ�ã��������ظ�λ��
2.
*/


PACK_STRUCT_BEGIN
typedef struct
{
	INT8U data[maxSize];
	INT8U length;//����һ�����⣬Ϊʲô�ñ�����ֵ��Ϊ��0!!
}Sqlist;       //������˳���Ĳ��룬ɾ����
PACK_STRUCT_END
Sqlist *q;
Sqlist *p;
 

//������Ĳ���
//head1��head2�����������ĵ��������һ���㷨����head1��head2�鲢��һ������head3��
//ʹ��head3��������
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
//����������ʾ����δ���BST������
typedef struct Node
{
	struct Node *left;
	struct Node *right;
	size_t size;  //���ݵĿռ��С
	INT8U  data[];//���ݱ���
}Node_t;
//�����ṩ���������ĺ�������һ�������õ�����Ӧ�����ݡ��ļ�ֵ���ڶ��������Ƚ�������ֵ
typedef const void *GetKeyFunc_t (const void *dData);//��һ��������������ԭ��
//�ڶ������������ڱ�׼����bsearch������ʹ�õġ��ȽϺ�����
typedef INT16U CmpFunc_t(const void *pKey1,const void *pKey2);
//���ñȽϺ���ʱ�����ݵ��Ա�������ָ���������ƻ��Ƚϡ��ļ�ֵ��ָ�롣�˺����ķ���ֵС��0����ʾ��һ����ֵС�ڵڶ�����ֵ��
//����0����ʾ������ֵ��ȣ�����0����ʾ��һ����ֵ���ڵڶ�����ֵ��
//�����������Ƕ���һ���ṹ���ͣ���������һ�������˻�����������Ա��
//ָ��������ָ��
//ָ������ֵ��ָ�루����ΪGetKeyFunc_t)
//ָ��ȽϺ�����ָ�루����ΪCmpFunc_t)

typedef struct {
	struct Node *pRoot;  //ָ��������ָ��
	CmpFunc_t *cmp;      //�Ƚ�������ֵ
	GetKeyFunc_t *getKey;//����ֵ��Ϊ��ֵ
}BST_t;
*/

typedef struct BSTNode
{
	INT32U data;
	struct BSTNode *left;
	struct BSTNode *right;
}BSTNode;

struct BSTNode *createnode(INT32U data)//���ڵ��������ԱȺ�����������
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


//https://blog.csdn.net/qq_41028985/article/details/82859199---�ο���ַ���漰���������ͷ�巨��β�巨����
//http://blog.sina.com.cn/s/blog_c689bd6c0102wvdd.html---C99��һЩ����
typedef struct myNode {
	INT8U data;                // �洢��������
	struct myNode *next;     		//  �洢���ĵ�ַ
}myLNode,*Linklist;

//�ڽ��봴������֮ǰ��������д����������������������������
void Illustrate(Linklist head) {
	Linklist tem = head;              //  ��ͷָ��ĵ�ַ������ʱ��ָ��
	while (tem->next != NULL) {       //  ָ�����һ������ָ����ʱ��ֹͣ
		tem = tem->next;                //  ��㲻������ƶ�
		//printf("%d\n", tem->data);
		//USART1_Printf(&(hex2ascii(tem->next)));
		//USART1_Printf(&tem"->data);
		printf("\r\n %d",tem->data);
		
	}
}

//ͷ�巨���룺
Linklist HeadInsert_List(Linklist head) {
	INT8U i;//ע�⣺����������������������֮�󣬷�����ʾ���� error��
	myLNode *mynode = NULL;                  //  �����½��
	
	INT16U count = 16;                        //  �������ĸ���
	head = (Linklist)malloc(sizeof(myLNode));//  Ϊͷָ�뿪���ڴ�ռ�
	head->next = NULL; 
			             
	mynode = head->next;              	       //  �����һ������ָ������Զ����ΪNULL
	printf("\r\n ������ʾͷ�巨�����˳��Ϊ: ");	
	for ( i = 0; i < count; i++) {
		mynode = (Linklist)malloc(sizeof(LNode));//  Ϊ�½�㿪���ڴ�ռ�
		mynode->data = i;                        //  Ϊ�½���������ֵ
		mynode->next = head->next;               //  ��ͷָ����ָ�����һ�����ĵ�ַ�������´�������next 
		head->next = mynode;                     //  ���´����Ľ��ĵ�ַ����ͷָ�����һ�����
	}
	return head;//�����з���ֵ��Ϊ�˴ӵ�����ͷ��������ݣ�added by sjw
}
//ͷ�巨��������ĸ�����������������������
//mynode->next = head->next;    //  ��ͷָ����ָ�����һ�����ĵ�ַ�������´�������next 
//head->next = mynode;          //  ���´����Ľ��ĵ�ַ����ͷָ�����һ�����


//β�巨���룺
Linklist TailInsert_List(Linklist head) {
  INT16U  count = 16 ;                 //  ������
	INT16U  i;
	Linklist node = NULL;           //  ������
	Linklist tailer = NULL;            //  ����β���
	
	head = (Linklist)malloc(sizeof(LNode));          //  Ϊͷָ�뿪���ڴ�ռ�
	head->next = NULL;              //  ��ʼ��ͷ���ָ�����һ����ַΪ NULL
	tailer = head;                     //  δ����������֮ǰ��ֻ��һ��ͷ���
	
	printf("\r\n ������ʾβ�巨�����˳��Ϊ: ");
	for (i = 0; i < count; i++) {
		node = (Linklist)malloc(sizeof(LNode));          //  Ϊ�½�㿪�����ڴ�
		node->data = i;                                  //  �½���������ֵ
		tailer->next = node;                      		
		tailer = node;
	}
	tailer->next = NULL;
	return head;//�����з���ֵ��Ϊ�˴ӵ�����ͷ��������ݣ�added by sjw
}
//β�巨�������������䣺
//end->next = node;                      		
//end = node;



const 	uint8_t   *pmp3tabel[26]={
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3", 
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3",
		
	  "MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3", 
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3",
		
		
	};
	

Linklist phead = NULL;            //  �����ͷָ��
INT8U MainFindElem(Sqlist L,INT8U x);//���������ص�һ����xֵ���Ԫ�ص�λ��
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


//����ָ�����鶨�弰����ֵ��
void (*KeyProcTab[])()={NoKeyProm,KeyProm1,KeyProm2,KeyProm3,KeyProm4,KeyProm5,KeyProm6};
float *find(float(*pionter)[4],int n);//�������� 

/*
//float(*pionter)[4]   ����  int (*p)[10]; p��Ϊָ�������ָ�룬�ֳ�����ָ�롣
int Func(int x);        //����һ������
int (*p) (int x);       //����һ������ָ��
p = Func;               //��Func�������׵�ַ����ָ�����p

1.���庯��ָ�����ͣ�
typedef int (*fun_ptr)(int,int);    
2.������������ֵ��                                   typedef
fun_ptr max_func=max;
Ҳ����˵����������ָ��ĺ���Ӧ�úͺ���ָ����ָ�ĺ���ԭ����һ�µ�


STM32f103VE�Ĵ���--����ƪ
https://www.it610.com/article/1294459351842496512.htm
*/


extern uint16_t  TestCount;
extern uint8_t  TestCountHL[2];
extern  uint8_t do_erase_nandflash(uint32_t _ulBlockNo);



//ECC�㷨��ʵ��
//����ǳ��NandFlash���ECCУ���㷨ԭ����ʵ��(1)
//https://blog.csdn.net/qwe5959798/article/details/116481300   �����·ǳ��ã����ECC
//���Ϲ���NandFlash��ECCУ�����ºܶ࣬��û��һ��������ġ�
//����ǳ��NandFlash���ECCУ���㷨ԭ����ʵ��(2)
//https://blog.csdn.net/qwe5959798/article/details/121931611   





struct FAT32_DBR
{
unsigned char BS_jmpBoot[3];     	//��תָ��offset: 0
unsigned char BS_OEMName[8]; 			// offset: 3
unsigned char BPB_BytesPerSec[2];	//ÿ�����ֽ���offset:11
unsigned char BPB_SecPerClus[1]; 	//ÿ��������offset:13
unsigned char BPB_RsvdSecCnt[2]; 	//����������Ŀoffset:14
unsigned char BPB_NumFATs[1]; 		//�˾���FAT ����offset:16
unsigned char BPB_RootEntCnt[2]; 	//FAT32 Ϊ0 offset:17
unsigned char BPB_TotSec16[2]; 		//FAT32 Ϊ0 offset:19
unsigned char BPB_Media[1]; 			//�洢����offset:21
unsigned char BPB_FATSz16[2]; 		//FAT32 Ϊ0 offset:22
unsigned char BPB_SecPerTrk[2]; 	//�ŵ�������offset:24
unsigned char BPB_NumHeads[2]; 		//��ͷ��offset:26
unsigned char BPB_HiddSec[4]; 		//FAT ��ǰ��������offset:28
	
	
unsigned char BPB_TotSec32[4]; 		//�þ���������offset:32
unsigned char BPB_FATSz32[4]; 		//һ��FAT ��������offset:36
unsigned char BPB_ExtFlags[2]; 		//FAT32 ����offset:40
unsigned char BPB_FSVer[2]; 			//FAT32 ����offset:42
unsigned char BPB_RootClus[4]; 		//��Ŀ¼�غ�offset:44
unsigned char FSInfo[2]; 					//��������FSINFO ������offset:48
unsigned char BPB_BkBootSec[2]; 	//ͨ��Ϊ6 offset:50
unsigned char BPB_Reserved[12]; 	//��չ��offset:52
unsigned char BS_DrvNum[1]; 			// offset:64
unsigned char BS_Reserved1[1]; 		// offset:65
unsigned char BS_BootSig[1]; 			// offset:66
unsigned char BS_VolID[4]; 				// offset:67
unsigned char BS_FilSysType[11]; 	// offset:71
unsigned char BS_FilSysType1[8]; 	//"FAT32 " offset:82
};


struct FAT32_Init_Arg
{
unsigned char BPB_Sector_No; //BPB ����������
unsigned long Total_Size; //���̵�������
unsigned long FirstDirClust; //��Ŀ¼�Ŀ�ʼ��
unsigned long FirstDataSector; //�ļ����ݿ�ʼ������
unsigned int BytesPerSector; //ÿ���������ֽ���
unsigned int FATsectors; //FAT ����ռ������
unsigned int SectorsPerClust; //ÿ�ص�������
unsigned long FirstFATSector; //��һ��FAT ����������
unsigned long FirstDirSector; //��һ��Ŀ¼��������
unsigned long RootDirSectors; //��Ŀ¼��ռ������
unsigned long RootDirCount; //��Ŀ¼�µ�Ŀ¼���ļ���
};

/*
void FAT32_Init(struct FAT32_Init_Arg *arg)
{
		struct FAT32_BPB *bpb=(struct FAT32_BPB *)(FAT32_Buffer);//�����ݻ�����ָ��תΪstruct FAT32_BPB ��ָ��
		arg->BPB_Sector_No =FAT32_FindBPB();//FAT32_FindBPB()���Է���BPB ���ڵ�������
		arg->Total_Size =FAT32_Get_Total_Size();//FAT32_Get_Total_Size()���Է��ش��̵�����������λ����
		arg->FATsectors =lb2bb((bpb->BPB_FATSz32) ,4);//װ��FAT ��ռ�õ���������FATsectors ��
		arg->FirstDirClust =lb2bb((bpb->BPB_RootClus) ,4);//װ���Ŀ¼�غŵ�FirstDirClust ��
		arg->BytesPerSector =lb2bb((bpb->BPB_BytesPerSec),2);//װ��ÿ�����ֽ�����BytesPerSector ��
		arg->SectorsPerClust =lb2bb((bpb->BPB_SecPerClus) ,1);//װ��ÿ����������SectorsPerClust ��
		arg->FirstFATSector=lb2bb((bpb->BPB_RsvdSecCnt) ,2)+arg->BPB_Sector_No;//װ���һ��FAT �������ŵ�FirstFATSector ��
		arg->RootDirCount =lb2bb((bpb->BPB_RootEntCnt) ,2);//װ���Ŀ¼������RootDirCount ��
		arg->RootDirSectors =(arg->RootDirCount)*32>>9;//װ���Ŀ¼ռ�õ���������RootDirSectors ��
		arg->FirstDirSector=(arg->FirstFATSector)+(bpb->BPB_NumFATs[0])*(arg->FATsectors);//װ���һ��Ŀ¼������FirstDirSector ��
		arg->FirstDataSector =(arg->FirstDirSector)+(arg->RootDirSectors);//װ���һ������������FirstDataSector ��
}



FATFS�ļ���ֲ��debug���⣨�ǳ��ã�
http://www.360doc.com/content/18/0530/06/6889381_758125759.shtml

*/





 static u8   *(*CopyData[10])(u16 Length);
 u8 *my;

 static u8   *(see)(u16 sjw)
{
	
	u16 temp=sjw;
	return my;
}
//û��    ����ָ�뺯��     ��һ�������Ϊָ�벹�E��ָ��������ִ�к���������
//������  ����ָ������     ��һ�����������ʵ��ɢתָ���ر𷽱㣡��
u16 MainTestArray[10][10];
u16 (*pMainTestArray)[10]=MainTestArray;
	
//�ó�����ʵ���ϵ�󼴿�ʼ����SD���ڵ��ļ����ܣ����š������¡��󼴿�ʼ����12�������Ĺ��ܣ���
//�˳����ⲿ+12�����Ϻ��ϵ��ܹ���ʼͨ��vs1003ʵ�ַ������ܣ���������ܳ�������������һ����İ弴�ɣ�
//���϶�WAV��Ƶ��ʽ��������(ADPCM����) ��VS1003¼WAV����������      https://bbs.21ic.com/icview-1604404-1-1.html


//stm32-USART1��ӳ��   �ο���ַ��https://blog.csdn.net/qinrenzhi/article/details/81875348
//STM32F103 FSMC����Լ�����LCD��Ӧ��   �ο���ַ��https://blog.csdn.net/weixin_30918415/article/details/98433064
//FSMC����       �ο���ַ��http://blog.sina.com.cn/s/blog_7880d3350101ih1z.html


/*
Ŀ�ģ���K9F1208��Ϊһ��U�̣�ʵ��������copy�ļ���Ŀ�ģ���֮���յ�������İ�ָ��󣬰�Ҫ�󲥷�U��������ļ�����
ѧϰ��FATFS��ֲ��NandFlash��K9F1208���ڵĹ��̼�¼
1.https://blog.csdn.net/cwcwj3069/article/details/7882978
u��  �����DBR ��dos boot record)��BPB(bois parameter block)
          MBR(main boot record)�������ʵ����壬����˼
2.NAND_FLASH(K9F1208U0C)��������
https://blog.csdn.net/lshiceman/article/details/37929167

3.STM32 FSMC NAND������ ����NAND FLASH ע������
https://blog.csdn.net/qq_15404645/article/details/80911266

4.fatfs�ļ�ϵͳ���֮f_mkfs��������
https://blog.csdn.net/agony_isolate/article/details/106243899

5.https://blog.csdn.net/qq_44884287/article/details/89517209
nand flash�ṹ�Լ���д��������д�ıȽϾ��䣨ת�أ�


6. VBR (Volume Boot Record) or PBR (Private Boot Record), 
FAT ��������Ҫ�����ݽṹ�� BPB��BIOS Parameter Block��BIOS �����飩�����д洢 FAT ������ò����� 
BPB λ�����������С� ��������ͨ����Ϊ VBR��Volume Boot Record����������¼���� PBR��Private Boot Record��ר��������¼����
����ֻ�Ǳ�������ĵ�һ������������ĵ�һ��������
  https://dandelioncloud.cn/article/details/1460588983884529666
	����վ��������ϸ�������ļ�ϵͳ��һ�������ֽڵĺ��壬�ر��вο���ֵ��added by sjw
	
	
7.���Ϸ��ֵ�һƪд�������������£�ֵ��һ����
http://blog.chinaunix.net/uid-8613773-id-2018359.html

8.//����2022-7-19�ս��˺��Ϊ1ʹ�ܣ���
���ļ�ffconf.h�ĵ�164���ϣ�������������������������������������������������������������������������������������������������������


9.C++ f_mount��������ʾ��
https://vimsky.com/examples/detail/cpp-ex-----f_mount-function.html

10.FatFsģ�鹦������ѡ�� 
	https://blog.51cto.com/u_15294654/3112876
	a.��������
	b.�����ռ�ͱ��ػ�������
	c.��/����������
	d.ϵͳ����
	
11.fatfs��վ��
	http://elm-chan.org/fsw/ff/00index_e.html

12.��FATFS��ֲSTM32RBT6�����Ĺ��ز��ɹ��ͷ���ֵ����
http://www.eepw.com.cn/article/201611/322277.htm

ԭ���ڶ���FATFS *FS;����Ҫ�����ڴ�ģ���˵�ռ���������ַ�ʽһ�������飬��һ���Ƕ���ָ�룬
����ָ��ʱҪʹ��malloc�����ڴ滹Ҫfree�ͷ��ڴ棬���Ҷ�����fatfs�ṹ��ָ��û�з����ڴ棬
��ɷ���ֵFR_NO_FILESYSTEM,// (13) There is no valid FAT volume �������Ҹĳ�fatfs fs;

 
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
	ע�⣻���ļ�stm32f10x_fsmc.c����ʾ���ĸ����󣨴��ļ��Ѿ�������ţ����ͬ���ļ����棬����Ϊ��ʵ��FlashWriteOneSector  FlashReadOneSector��
	��183�б�������
	��205�б�������
	��385�б�������

	ע�ⶼ����ú���Ҫ�򿪴����Σ�
	
	
		
2.	https://blog.csdn.net/chengdong1314/article/details/81369601
    STM32 USB��ö�ٹ��̼��   ���Ľ��ܵķǳ��ã�������һ��һ��ö��ʱ�����Ķ����Ĺ۲�Ը������
	
		
3.  https://blog.csdn.net/dierui2904/article/details/101759783  
	����վ�����ݷǳ��������������ο�����⿪��USB�϶�û������   ������ʾ��������ʽ�����ɹ������ô��̿ռ�����ô��̿ռ䶼Ϊ0��
	���������վ�ǳ����ҽ��п������ƣ��ǳ����Խ������
4.  http://www.javashuo.com/article/p-ybcbwxvw-ky.html


5.FatFs�ļ�ϵͳNandflash�����������
https://www.likecs.com/show-204034824.html

6.���µ����⣺FATFS f_open() ���ؿ��µ� FR_NO_FILESYS
https://bbs.21ic.com/icview-619554-1-1.html

7.STM32 �ļ�ϵͳ fatfs ��ֲ�ʼ����   MBR��DBRͨ��0���������ݽ����ر�λ����
https://blog.51cto.com/u_15284384/3052087

8.���ļ��ĵ�110���޸�Ϊ��113���ϣ����ԵĿ�����FATFS32�������ˣ����ҷ���fs�����ݶ����ſ���
	
	*/

//1 SPI�Ļ�������   https://blog.csdn.net/qq_39792063/article/details/120942630
//���Ľ��ܵĺ�����
//���ļ�SD_driver.c���ļ���nand_fatfs010b_noOS_TF�µ��ļ����棨����֤���õģ�֮�󣬲������stm32f10x_spi.c�ĵ�170���ϵľ����ˣ�
//������ת��   B       HardFaultException  ����Ϊ��ָ�� OS_ENTER_CRITICAL();�� OS_EXIT_CRITICAL();��������ɵ�















































































































































































































































































































































































































































































































































































































































































































































































































































































































































/*
24C02,256  ��8(2K bits)- 
24C04,512  ��8(4K bits)- *16byte??????????????????????????
24C08,1024 ��8(8K bits)-
24C16,2048 ��8(16K bits)- 
24C32,4096 ��8(32K bits)- 
24C64,8192 ��8(64K bits)-

ҳд:8�ֽ�ҳ(24C02),16�ֽ�ҳ(24C04/08/16),32�ֽ�ҳ(24C32/64)�ɰ��ֽڣ���������ж�
�߿ɿ��Բ�д����:100���-���ݱ���ʱ��:100��



STM32F105��107RBʹ���ⲿ����8Mʱ��������ʱ��Ϊ72M

https://www.cnblogs.com/tlazy-12138/p/17619353.html




��ע1��������ĺ�������Ϊ��450706����ֻ��������ȷ������󣬲Ż��Ϊ
			 �Ϸ��û����κβ������������ƣ� (2008/8/28�����趨������)
��ע2�����������6�����̣�������λ�����ֱ�Ϊ��
      ��״̬��  ��λѡ��  ���ӡ�  ������	  KY0 ��RL0,RL1,RL2,RL3
			����/ͣ�� �����ء�                  KY1 ��RL0,RL1		



��ǰ��Ƕ��ʽӦ�ó��򿪷������C�����ѳ�Ϊ�˾��󲿷ֳ��ϵ����ѡ�����һ��main�����ƺ���Ϊ��������Ȼ����㡪����ΪC����������main������ʼִ�С�
��һ�������ᱻ���Ե������ǣ�΢����������Ƭ�����ϵ�������Ѱ�ҵ���ִ��main�������أ�����Ȼ΢�������޷���Ӳ���϶�λmain��������ڵ�ַ��
��Ϊʹ��C������Ϊ�������Ժ󣬱���/�����ĵ�ַ���ɱ������ڱ���ʱ���з��䣬����һ��main��������ڵ�ַ��΢���������ڲ��洢�ռ��в����Ǿ��Բ���ġ�
���Ŷ��߶����Իش�������⣬��Ҳ���ͬС�죬���϶����и��ؼ��ʣ��С������ļ�������Ӣ�ĵ����������ǡ�Bootloader����

�������ܸ��£��ṹ�򷱣��۸�����ÿһ��΢�����������������������������ļ���
�����ļ������ñ��Ǹ���ִ��΢�������ӡ���λ��������ʼִ��main�������м����ʱ�䣨��Ϊ�������̣���������еĹ�����
��Ϊ������51��AVR��MSP430��΢��������ȻҲ�ж�Ӧ�����ļ������������������Զ��������ṩ����������ļ�������Ҫ������Ա���и�Ԥ�������̣�
ֻ��Ҫ��main������ʼ����Ӧ�ó������Ƽ��ɡ�



UC/OS-IIIѧϰ��������PendSV�ж�
https://www.itxm.cn/post/ajffea1a1.html


��ֲucosii���������� B OSStartHang
https://blog.csdn.net/special00/article/details/73929966
��ʵ�ܼ򵥣���ΪSTM32������쳣�ж�PendSV_Handler�����UCOS���쳣�ж�OSPendSV��ʹ�䲻������ִ�С�
�������Ǿ���Ҫ����PendSV_HandlerΪOSPendSV�����ж�������



STM32-�˿ڸ��ú���ӳ��
https://blog.csdn.net/qq_39792063/article/details/120565875
�����½��͵��൱��ϸ���ǳ������ǲ���STM32f10x����������added by sjw



cl�������Ͳ�Ʒ��    	stm32f105/107ϵ��
vl����ֵ�Ͳ�Ʒ��    	stm32f100ϵ��
xl�������ܶȲ�Ʒ��		stm32f101/103ϵ��
ld�����ܶȲ�Ʒ��				FLASHС��64K
md���е��ܶȲ�Ʒ��			FLASH=64 or 128
hd�����ܶȲ�Ʒ��				FLASH����128

IO�˿ڸ�λ���ڸ���״����Ҳ�������ƽ״������Χ��·���飬�����Ҫ������滮��ҵƷ�Ļ������Ǳ���Ҫȷ�ϵģ�
�� ���븡��
�� ��������
�� ��������
�� ģ������

�� ��©���
�� ����ʽ���
�� ��������ʽ
�� ���ÿ�©����


STM32ʱ�ӳ�ʼ������SystemInit()���
https://blog.csdn.net/xuzhexing/article/details/90380971

*/
#define   CLOSE_MINUTE  2

			
	




INT8U  Time_Modify[6]={0x00,0x00,0x00,0x00,0x02,0x01}; //ĸ��ʱ���޸Ļ���
INT8U  Mp3_Ok=0,Mp3_Error=0;       //MP3��������ɹ�

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
INT8U  Light_En=1;                       //����ʹ��  
INT8U  Light_Start=19,Light_End=6;       //����ʱ���
INT8U  Rythem_Number=8,Strike_Number=7;  //��ʱ���ֺţ�������	

INT8U   MotorActFlag;
INT8U  ReadKey_Value=0xff;               //�����ļ�ֵ
//GPSģ����Գɹ���Ŀǰִ��isLinear(_ntp)������HardFault_Exception!!
//���̽ӿڼ���ʾ�����Գɹ���
//DS3231ģ����Գɹ���
//����������������ģ����Գɹ���
//��ʱģ���Ѿ����Գɹ�����
extern enum   KeyRun_Order Key_Subclock_State1;

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
		base=(sect>NVIC_VectTab_FLASH)? NVIC_VectTab_FLASH : NVIC_VectTab_RAM;//�ж�������Ļ���ַ
		offset=sect-base;	             	//�ж��������ƫ��	
		#ifdef VECT_TAB_RAM
		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);// Set the Vector Table base location at 0x20000000
		#else
		NVIC_SetVectorTable(base,offset);	//���¶�λ�ж�������
		#endif	
	#endif
	 
	 
	
	
	  //DelayMs(12000);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//��ʼ���ж�����   ����ϵͳ�ж����ȼ�����		
	  OS_CPU_SysTickInit();
    #if (OS_TASK_STAT_EN > 0)// ͳ������ 
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
	phead = HeadInsert_List(phead);  //  ��������
	Illustrate(phead);               //  ���ÿ������������
	phead = TailInsert_List(phead);
	Illustrate(phead);               //  ���ÿ������������

ϵͳ�ĵ�һ�����񣬸���OSʱ�ӣ�������������
RO�ǳ����е�ָ��ͳ���
RW�ǳ������Ѿ���ʼ���ı���
ZI�ǳ������Ѿ�û�г�ʼ���ı���
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
	
	
     OSTaskCreateExt(  AppTask1, //  ������1������ 	
										  (void *) 0, 
										  (OS_STK *) &AppTask1Stk[APP_TASK1_STK_SIZE- 1],
										  APP_TASK1_PRIO,
                      APP_TASK1_PRIO,
										  (OS_STK *) &AppTask1Stk[0],
										  APP_TASK1_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 											

	 
	
   OSTaskCreateExt(   AppTask2, //  ������ʱ���� 	
										  (void *) 0, 
										  (OS_STK *) &AppTask2Stk[APP_TASK2_STK_SIZE- 1],
										  APP_TASK2_PRIO,
                      APP_TASK2_PRIO,
										  (OS_STK *) &AppTask2Stk[0],
										  APP_TASK2_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );


       OSTaskCreateExt(  AppTask3, //  ������3������ 	
										  (void *) 0, 
										  (OS_STK *) &AppTask3Stk[APP_TASK3_STK_SIZE- 1],
										  APP_TASK3_PRIO,
                      APP_TASK3_PRIO,
										  (OS_STK *) &AppTask3Stk[0],
										  APP_TASK3_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 


      OSTaskCreateExt(  AppTask4, //  ������4������ 	
										  (void *) 0, 
										  (OS_STK *) &AppTask4Stk[APP_TASK4_STK_SIZE- 1],
										  APP_TASK4_PRIO,
                      APP_TASK4_PRIO,
										  (OS_STK *) &AppTask4Stk[0],
										  APP_TASK4_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 


   
    
											
											
		OSTaskCreateExt(	AppTask5, //  ���������񣬰��������ʱ���������������  ������5������ 
											(void *) 0, 
											(OS_STK *) &AppTask5Stk[APP_TASK5_STK_SIZE - 1], 
											APP_TASK5_PRIO,
											APP_TASK5_PRIO, 
											(OS_STK *) &AppTask5Stk[0], 
											APP_TASK5_STK_SIZE , 
											(void *) 0,  
											 OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 
		
											
     OSTaskCreateExt(  AppTask6, //  ������6������ 	 ���������з�������ָʾ�ƣ���
										  (void *) 0, 
										  (OS_STK *) &AppTask6Stk[APP_TASK6_STK_SIZE- 1],
										  APP_TASK6_PRIO,
                      APP_TASK6_PRIO,
										  (OS_STK *) &AppTask6Stk[0],
										  APP_TASK6_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );
									 
									 
									 
		OSTaskCreateExt(  AppTask7, //  ������7������ 	 ר�Ŵ���gps����
										  (void *) 0, 
										  (OS_STK *) &AppTask7Stk[APP_TASK7_STK_SIZE- 1],
										  APP_TASK7_PRIO,
                      APP_TASK7_PRIO,
										  (OS_STK *) &AppTask7Stk[0],
										  APP_TASK7_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );
											
											
		OSTaskCreateExt(  AppTask8, //  ������8������ 	 ר�Ų��ԣ���
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

/*printf����
%%����ʾһ��%��''��%��Ч����Ҫ��"%%"���%
 %ns����ʾn���ַ����ַ���������n�ÿո���������
%0ns����ʾn���ַ����ַ���������n��0��������
%-ns����ʾn���ַ����ַ���������n�ÿո����Ҳ����

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
	ucos �������ȴ�һ���ź���  �����ǳ�ֱ�ۣ�ֵ������   added by sjw
	https://blog.csdn.net/gtkknd/article/details/52212097
	*/
	 pMainMotorSemEve=OSSemCreate(0);//���Semp = OSSemCreate(0), ���ź�����ʾ�ȴ�һ���¼����߶���¼��ķ�����
	 pMainBsSemEve=OSSemCreate(0);
	 
	
	 Mutex_USART1 = OSMutexCreate(USART1_MUTEX_PRIO, &err);  // ����USART1�������ź���
	 Mutex_USART2= OSMutexCreate(USART2_MUTEX_PRIO, &err);   // ����USART2�������ź���	
	
	 GPIO_Motor_Config();       //�ں���������˿�IO��ʼ��---��������˿ڳ�ʼ��   
	 GPIO_I2C_Config();
	 LedPortSpecialInit();
	 //�ڵ��Ե�ʱ��PE2���ǳ��ָߵ�ƽ���������ָ�������������Ӳ��û�����⣬�������İ��һ����ֱ�ӵ�  HDR2*12���������κ�����
	 //��һ����İ�ͬ����ˣ����ñ����PE2���ŷ�����С��3.3����ƽʱһֱΪ1.8-1.9�������ǵ�����������cpu�˿ڶ������˰ɣ�
	 //��ѹ�ϲ�ȥ���������ԣ���һ��SSR����������ֶ˿�E��ʱ��û�д򿪣��ں����д�һ����������ס��ѹ�ϲ�ȥ�Ŀ���ԭ����ʱ��ûʹ��
	 //added  by sjw    !!!!!!!!!!!!!!!!!!!
	 LedBsZm_Init();                 //����ָʾ��,��ʱ�������˿ڳ�ʼ��  PB4Ϊ��ʱ����ڣ���  PE2Ϊ��������ڣ���
   Mp3Drive_Init();

	 Hd7279_Init();
	 //https://blog.csdn.net/m0_52850679/article/details/124506315
	 //Ƭ�������DMAxͨ��y      added by sjw
	 
	 TIM1_Config();             //                                                ���ж�0���μ��ж�0
	 N31_pps_init();            //GPS��pps�ж��ź�    gps�˿ڳ�ʼ�� pps���жϣ�     ���ж�0���μ��ж�1
	 USART1_Init(9600);	        // ��ʼ������1,9600������							            ���ж�1���μ��ж�0
	 GPIO_Key_Config();         //���̼��̶˿ڼ����ж�  								            ���ж�1���μ��ж�1
   USART2_Init(9600);         //                                                ���ж�1���μ��ж�2                                                  
	 //printf("**        ��ӭʹ��ARM������        **\r\n");ͨ���ض�λ���Դ���2��û�����⣡  added by sjw
	 USART_ClearFlag(USART2,USART_FLAG_TC); 
	 
	
	
	 
/*
���ӻ����ӷ�����ʱ����
24  0F 04 01 0C 4D 50 33 5F 30    30 36 36 2E 4D 50 33 77   --������ǰ�࣡
24  0F 04 01 0C 4D 50 33 5F 30    30 35 36 2E 4D 50 33 74  ����n���ظ�����n��


24  0F 04 01 0C 4D 50 33 5F 30    30 36 32 2E 4D 50 33 73  ������ǰ�࣡
24  0F 04 01 0C 4D 50 33 5F 30    30 35 35 2E 4D 50 33 77����n���ظ�����n��


https://blog.csdn.net/horton11/article/details/120361823  
	 
7��ע�⵽��һ�䣺��������������λ(�ȶ�USART_SR��Ȼ��д��USART_DR)�� Ҳ����˵��Ҫ��read USART_SR,Ȼ��write USART_DR���������TC״̬λ���������Ӳ����λ�󣬴��ڷ��͵��׸�����֮ǰû��read SR�Ĳ�������ֱ��write DR��Ҳ����˵��TCû�б�������� ˵������ǰ��Ĳ²��ǶԵġ�  
8����ô��Ӧ�ð��ڴ����һ���ֽ�ǰ��ӣ�USART_ClearFlag(USART1,USART_FLAG_TC); ��ΪUSART_GetFlagStatus(USART1, USART_FLAG_TC);��Ӧ��Ҳ���������󡣲��Ժ�֤ʵ��ȷʵ��ˣ��ڷ����׸�����֮ǰ���ȶ�ȡһ��USART_SR����ô�Ͳ�������׸����ݶ�ʧ������ˡ�  
9���ܽ᣺Ӳ����λ�󣬴��ڷ����׸�����֮ǰ���ȶ�ȡһ��USART_SR�����ܹ���֤�׸����ݷ���ʱ�������ָ��ǵ��������Ȼ��Ҳ�б�ķ��������������TC״̬λ�����ǣ���write USART_DR֮�󣬼���һ��С��ʱ�������ݷ�����ϣ�Ӧ��Ҳ�ܼ���ų��������
��������������������������������
��Ȩ����������ΪCSDN������horton11����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/horton11/article/details/120361823 
*/	 
	
	 /*
	 for( count=0; count<18; count++){
		  USART_SendData(USART2,*pbsdata);
      //USART2->DR=*pbsdata;		 
			while((USART2->SR & 0x40)==0);//ѭ������,ֱ��������� 
		  pbsdata++;
	 }*/
	 
	 #ifdef  USB_DEBUG_KERNEL  //USB_DEBUG0		
			printf("*************************************\r\n"); // LOGO 
			printf("**                                 **\r\n");
			printf("**        ��ӭʹ��ARM������        **\r\n");
			printf("**  ���ǽ�����������Ƕ��ʽϵͳ���� **\r\n");
			printf("**           �������ѡ��          **\r\n");
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
			printf("\n\r ��Ʒ�ڲ�Flash��СΪ��%dK�ֽڣ� \t www.armjishu.com\n\r",  *(__IO uint16_t*)(0x1FFFF7E0));
			printf("����BigOrSmallValue�ĵ�ַΪ%p\r\n",&BigOrSmallValue);
			printf("ָ��pBigOrSmallValue�ĵ�ַΪ%p\r\n",pBigOrSmallValue);
		#endif	
	  OS_EXIT_CRITICAL();	
		
		
		
	
/*
const unsigned char       Volume[6]={0x24,0x03,0x0F,0x01,0x1F,0x12};                     //MP3��������
unsigned char             Mp3data[18]={0x24,0x0F,0x04,0x01,0x0C,0x4D,0x50,0x33,0x5F,0x30,  //����MP3ָ���ļ�
                                     0x30,0x30,0x32,0x2E,0x4D,0x50,0x33,0x74};


�����CPU��MP3ģ����������£�  
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--�����ֽ�Ϊ60��
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16��ǰ�ࣺ
		24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
17��ǰ�ࣺ
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
    24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 

18��ǰ�ࣺ
    24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

		
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z	
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z
16���õ������
		24 0F 04 01 0C 4D 50 33 5F 30 32 38 37 2E 4D 50 33 7A 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		37 2E 4D 50 33 7A 24 0F 04 01 0C 4D 50 33 5F 30 32 38 37 2E 4D 50 33 7A 
17���õ������
$MP3_0288.MP3u$MP3_0288.MP3u$MP3_0288.MP3u------------------------�����ֽ�Ϊ54��
$MP3_0288.MP3u$MP3_0288.MP3u$MP3_0288.MP3u
    24 0F 04 01 0C 4D 50 33 5F 30 32 38 38 2E 4D 50 33 75 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		38 2E 4D 50 33 75 24 0F 04 01 0C 4D 50 33 5F 30 32 38 38 2E 4D 50 33 75 				
18���õ������
    24 0F 04 01 0C 4D 50 33 5F 30 32 38 39 2E 4D 50 33 74 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		39 2E 4D 50 33 74 24 0F 04 01 0C 4D 50 33 5F 30 32 38 39 2E 4D 50 33 74

�����ַ�ASCII���
https://www.perfcode.com/p/control-character.html
*/	

	
	while(1){
		//OSTimeDly (500);
	   
		  OSTimeDlyHMSM(0, 0, 0, 400);
	}
  
}






//�۲�usart2�жϽ��յ�ĸ�ӷ��͵����ݣ�9����
static  void AppTask2(void* p_arg)
{
   INT8U err;
   INT8U temp;

  p_arg = p_arg;
	//OSTimeDly(1000);
 

  while (1) {
		
       #if 0
	     OSTaskSuspend(OS_PRIO_SELF); 		    // �Ƚ���������ڴ��ڽ����ж��лָ�����
       OSMutexPend(Mutex_USART2, 0, &err);  // �ȴ��ź���
       while(USART2_GetByte(&temp)){    	  // ������ڽ��յ����ݴ�ӡ����
           USART2_SendByte(temp);
       }  
	   
	    if((USART2_RX_FIFO[0]==0xbb)&&(USART2_RX_FIFO[7]==0x0d)&&(USART2_RX_FIFO[8]==0x0a)){ 	
					p_timemu->hour=USART2_RX_FIFO[1];
					p_timemu->minute=USART2_RX_FIFO[2];
					p_timemu->second=USART2_RX_FIFO[3];
					MainBsPayOrXms=USART2_RX_FIFO[4];		//0Ϊƽ��ҹ��ʱ��1Ϊ�����±�ʱ��
					MainBsKnockCnt=USART2_RX_FIFO[5]%12;   	//����������
					if(USART2_RX_FIFO[6]==0){		 		//��ʱ�򿪻��߹���״̬��
						//MainBsOnOffStatusFlag=FALSE;
						//MainBsJsValidFlag=FALSE;		
					}else{
						//MainBsOnOffStatusFlag=TRUE;
						//MainBsJsValidFlag=TRUE;
					}	
			}
      OSMutexPost(Mutex_USART2);            // �ͷ��ź���  
			#endif
			OSTimeDlyHMSM(0, 0, 0, 470);
			
			
   }
}




static  void AppTask3(void* p_arg)//���̴������񣡣�
{	
	INT8U tempdata;
 static INT8U rxjs=0x11;	
	
	
	
	
	#if 0
		if (ucKeyValue > 0)
		{
				/* ��ʱ�����κδ����û������Լ���Ӵ������ */
				switch (ucKeyValue)
				{
					case KEY_DOWN_JOY_UP:		/* ҡ��UP������  */
					case KEY_DOWN_JOY_DOWN:		/* ҡ��DOWN������  */
					case KEY_DOWN_JOY_LEFT:		/* ҡ��LEFT������ */
					case KEY_DOWN_JOY_RIGHT:	/* ҡ��RIGHT������ */
					case KEY_DOWN_JOY_OK:		/* ҡ���м����� */
					case KEY_DOWN_USER:			/* USER������ */
						break;					

					default:
						break;
				}
		}
#endif
		
		
		while(1){
			
			//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);//�����ܱ�־λ���Ƿ���Խ���added by sjw
			//rxjs=SPI_I2S_ReceiveData(SPI1);
			

			OSTimeDlyHMSM(0, 0, 0, 300);
			
		}
}







/*
���Ĳ���DMA+���λ�������GPS���Ľ��н�����˼·��ͨ��DMA�жϽ��յ�GPS���ĺ󣬴�ŵ����λ�������Ȼ�����������н���GPS���ġ�
����GPS���ĵĹؼ��ǣ������λ������е��ֽ�ת�����ַ�����Ȼ�����ַ����в���GPS����ͷ��ʶ�����磺GPGGA����GPS����β����ʶ���س����У���
��������������������������������
��Ȩ����������ΪCSDN������ba_wang_mao����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/ba_wang_mao/article/details/115530153


//https://blog.csdn.net/ba_wang_mao/article/details/115530153
	//STM32F407 ��Ƭ��+DMA+���λ�����+GPS���Ľ���
	
	//https://www.codenong.com/cs107108405/
	//���ڿ����ж�+DMA��������
����GPS�����������4�д���
*/











/*
NTPʱ���ת����UTCʱ��Ĺ���
https://blog.csdn.net/weixin_45873923/article/details/120119622


��NTPʱ�����һ��64bit�޷��Ŷ�������ʾ������ʾ�Դ�1900��1��1��00:00:00�����ڹ��˶����롣
��UTCʱ�䣬��������ʱ��1970��1��1��00:00:00������ʱ��1970��1��1��08:00:00���������ڵ�����������ʾΪ1970-01-01 00:00:00 UTC��������ϰ�߽���UTCʱ�����
 NTPЭ�������ĸ�ʱ��������Ĳ��������ĸ�ʱ���������ֻ�򵥵�������һ��NTPʱ������ķ������ת����UTCʱ�䡣
����һ��ʱ�������Ϊ��D9 FD 84 95 94 F8 59 7C������������һ��ѧϰ��NTPʱ��������ת����UTCʱ��ġ�


mktimev(&now)������������ʱ����ת��ΪNTP������
to_tm(NTP - JAN_1970, &now);����������ת��ΪUTCʱ��

*/


//GPSģ����Գɹ���Ŀǰִ��isLinear(_ntp)������HardFault_Exception!!
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
		
			set_pps1_sig();//��pps1_tim > 101ʱ����Ҫpps1_status=0��������ͬ����
		
			if(uart1_rx_sig){			
				uart1_rx_sig = 0;	
				board.err &= ~err_gps1;
				
				//gps.status = gps_bd2_ascii(Uart1_Rx_Buf, Usart1_Rx_Len);	//
				gps.status = gps_bd2_ascii(receive_data, Usart1_Rx_Len);	//receive_data

				memset(Uart1_Rx_Buf,0,UART1_RX_SIZE);    //������Ͻ����������Ĺ�������	
				
				
				//uCOS�ٽ�κ�������⣺CPU_SR_ALLOC() д�ķǳ����������ж�Ƕ���ж��ٽ�γ�����ƻ�����added by sjw
		    //https://blog.csdn.net/m0_43443861/article/details/125956776						
				
				
				if(gps.status){								
						  _ntp = do_gps(); //��GPS���յı�׼UTC�����͸�����  ע���ʱ�Ѿ���UTCʱ���ΪCTCʱ��added by sjw		
						//if(isLinear(_ntp) && (pps1_status>10))//ִ�к���isLinear(_ntp)�������쳣����added by sjw
					    if(pps1_status>10){
									NTP = _ntp;								  
									if(!(_ntp %180) ){		  //������3231����ѹgps���ݵĹ��ܣ�ÿ3����һ�Σ�
										
										OS_ENTER_CRITICAL();	//�����ٽ���						
										//OSSchedLock(&err);		//UCOSII�ķ�ʽ,��ֹ���� 		
										ds3231_tm_wr(NTP);   //�ȴ�x��������ѹ�뱣�棡);	
										/*
										��������������OSSchedlock()�Ĺ��������ڽ�ֹ������ȣ�ʹ���񱣳ֶ�CPU�Ŀ���Ȩ����������������OSSchedUnlock()�Ĺ����ǽ����������ȵĽ�ֹ��
										�����������Ϳ�����ʵ��ԭ���ǣ���ȫ�ֱ�������Ƕ�׼�����OSLockNesting���в�����OSLockNesting����OS SchedLock() ���������õĴ�����
										����Ƕ����ȴ�255�㡣�������������Ա���OSLockNesting���м�1�������������Ա���OSLockNesting���м�1������
										��������������������������������
										��Ȩ����������ΪCSDN������fillthesky����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
										ԭ�����ӣ�https://blog.csdn.net/fillthesky/article/details/46697179
										*/
										//OSSchedUnlock(&err);	//UCOSII�ķ�ʽ,�ָ�����
										
										OS_EXIT_CRITICAL();	  //�ٽ���	
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









//������ר�Ŵ���ʱ���ܣ�����ǰ��������ֱ���ʲô���Ƿ񵽱�ʱʱ���ˣ���added by sjw
static  void AppTask5(void* p_arg)
{
	OS_CPU_SR  	cpu_sr;
	INT8U err,eeprom_page;
	INT8U js=0,flag=0,count;
  struct tm  now;
	INT8U    wait=0;
	
	
	
		
		#if 0  //32ҳ��256����Ԫȫ����֤�����κ����⣡��  added by sjw  2023-10-14 ���� goto work
		 OS_ENTER_CRITICAL();
		 for(eeprom_page=0;eeprom_page<32;eeprom_page++){
				iic_sw_write(eep_chip_24cxx, iic_eeprom_east+eeprom_page*8, tx1, 8);//ע��оƬ��һҳ��8���ֽڣ���δ���8���ֽڣ��ֲ��Ʒ�ת����ʼ��ַ����added by sjw
				DelayMs(100);
		 }
		 OS_EXIT_CRITICAL();	
		 OSTimeDlyHMSM(0, 0, 1, 500);
		 OS_ENTER_CRITICAL();
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_east, &board.east_time[0], 8);//ע��I2C�и�д���ڣ���Լ10ms����ҳдҪ���ڴ�д���ڣ���added by sjw
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_south, &board.south_time[0], 8);
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_west, &board.west_time[0], 8);
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_north, &board.north_time[0], 8);
		 OS_EXIT_CRITICAL();		
		#endif
		
		
		/*
	  //��ָ��ʹ���е�LEDȫ����������������˸״̬����Ҫ���ڲ��ԡ�
    Set7279CS(0);
    SendByteToHd7279(CMD_TEST);
    DelayMs(2400);		
    Set7279CS(1); 
	*/


   for(wait=0;wait<5;){ //�����ȴ�5��  added by sjw
		 
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
		//iic_sw_write(eep_chip_24cxx, 0x0e,&temp , 1);//ģ��RTC  
		get_time();//��ȡRTC��ʱ��
	 //��ԭ������get_iic_setting  Ų��λ�õ����λ�ã�added by sjw
	  get_iic_setting();//��ȡ����ʱ�䡢��ʱ�����趨��Сʱ����ʱǰ�༰�������������ص��趨����added by sjw
		OS_EXIT_CRITICAL();	
		#endif
	 
  
   TimeDisValidFlag=1;//����ʱ��������ȷ�󣬱�־��Ч����added by sjw
  
	//test1=HEX_to_BCD(0x19);//0x19��16����,ת��Ϊ    BCD��Ӧ��Ϊ0x25  ���к�˽����ȷ����added by sjw
	//test2=BCD_to_HEX(37);  //BCD��Ϊ37    ת��Ϊ    16����Ӧ��Ϊ0x25  ���к�˽������ȷ������ȷ���Ӧ��Ϊ0x19 added by sjw

	
	 	
		
		
	while(1){	
				Light_Control();  //���� 
				Time_Notice();    //��ʱ
				if(IntDisFlag){   //��ʾĸ��ʱ��,�����޸�Ϊ300ms��ʾһ��
						Set7279CS(0);
						Display();
						Set7279CS(1);
						IntDisFlag=0;
				}
				
				
				if(Key_Time==1){ //����������
					Set7279CS(0);
					Key_Operation();  //  ���ֶ�����������Ϊ   Ƭѡ�ź�   ������λ�ó����ӽ���Ƭѡһֱѡ�У�����8������ȫ����˸����added by sjw
					Set7279CS(1);
					Key_Time=0;
				}
				
				OSTimeDlyHMSM(0, 0, 0, 90);		
				
				//OSSemPend(pMainBsSemEve,0,&err);//

	}
}





static  void AppTask6(void* p_arg)//������ר�Ŵ�����̿�׷����ת���߷�ת���ܣ�����added by sjw
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
		   switch ( Key_Subclock_State1){  //�ж��Ƿ񰴼�������  ����״̬  ʹ��仯��Ч�ˣ���
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
			 
			 
			 OSTimeDlyHMSM(0, 0, 0, 100);
		  
		
	}
}





//����������������ģ����Գɹ���
//���ϵ�׷ʱ��Ϻ󣬵����ʼ������ʱ����added by sjw
static  void AppTask7(void* p_arg)
{	
	 INT8U err;
   INT8U temp;
   OS_CPU_SR  cpu_sr;	
	 INT16U i,count;	
	 GPIO_InitTypeDef GPIO_InitStructure;
 
   
   p_arg = p_arg;
	
	
	 while(1)
	 {	
		
		 // OSSemPend(pMainMotorSemEve,0,&err);//��������ʱ��
		 
		 if(MotorActFlag){
			  #ifdef USE_MOTOR_ONE	
					 EnterEastNormalRun();
				#elif   USE_MOTOR_TWO
					 EnterSouthNormalRun();
				#elif   USE_MOTOR_THREE
					 EnterWestNormalRun();
				#else
					 EnterNorthNormalRun();
				#endif
			  MotorActFlag=0;
			  OSTimeDlyHMSM(0, 0, 0, 110);
		 }else{
			  OSTimeDlyHMSM(0, 0, 0, 510);
		 }
	 }
}







//���̽ӿڼ���ʾ�����Գɹ�����
//Ϊ�˽���û��ڳ�ʼ�ϵ��׷ʱ�������̵����飬����ʾ�ͼ���ģ���ƶ�������7�ϣ�����added by sjw
//�����ȼ���͵�����ר�Ŵ�����ϵ��Ŀ�׷���������������䲻���ż��̺���ʾ�ĵ�������added by sjw
static  void AppTask8(void* p_arg)
{
	INT8U  err;
	static INT8U first_flag;
	INT8U  eeprom_page,temp[8];
	INT32U     _ntp = 0; 
  OS_CPU_SR  cpu_sr;
	struct tm  now;
	INT8U    wait=0;
	
	//2023��10��20��15��32:50
	static INT8U  tx[11]={0x00,0x07,0xe7,0x0a,0x14,0x0f,0x20,0x032,0x00,0x00,0x05};	 
	

		
	while(1){	
		//time_set();      //ĸ��ʱ��У��
		if(!first_flag){	
		      if(compare_zf(p_timemu,p_timeslave)==1){//��ʾ׷ʱ��ϣ���Ҫ������ѹl��AT24Cxx�ﱣ�棡��
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
				     first_flag=1;
						 Key_Subclock_State1=WALK;//������Ӵ�ָ������ʼ׷ʱ������ϵͳΪWALK״̬����added by sjw
						
					}
		}
				
				
		if((p_timemu->minute == 10) && (p_timemu->second == 5)){
			get_time();//1��Сʱ��ȡһ��RTC��ʱ��
		}
	  
		OSTimeDlyHMSM(0, 0, 0, 130);
	}
}

/*

								
 


    if(LED_time==1)  //��ʾĸ��ʱ��
    {     
     display();                                                                                                                                                                                                                                                                             
     LED_time=0;    
    }  


    if(Key_time==1) //����������
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
*�� �ܣ�����δ��סʱ��ʱ����ĸ��ʱ��
*        ��Ϊ�Լ���ʱ��
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
*�� �ܣ�ĸ��ʱ��У��
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
       Time_adjust=1;//Уʱ��־   
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
         Time_adjust=1;//Уʱ��־          
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
	OSTimeDlyHMSM(0, 0, 0, 20);	//������ָ������ϱ��գ���added by sjw
	
  EAST_ZZ;
	while(1){
			switch(status){
						case IDLE:
								status=WAIT_TIME;
						    LightSlotFlag=1;
						break;
						
						
						
						case WAIT_TIME://ǿ�Ƶȴ�500ms��һ��Խ�����λ���ˣ�added by sjw
							  if(LightSlotValue>500){
									  LightSlotFlag=0;
								    LightSlotValue=0;
										status=HIGH;
								}else{
									OSTimeDly(20);
								}
						break;
						
						case HIGH:
							  if(EAST_FK_PIN==0){//��ʼ ���  �����۵�λ���ˣ�
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
									EEPROM����ʲô���������ֽ�Ϊ������λ������������FLASH��MCU���ɵ�EEPROM��ר������ʧ���ݴ洢���ģ�ռ�õ�ַ��RAM�ռ䡣MCU���ɵ�FLASH�ǳ���洢����
									֧��IAP�Ļ�����������FLASH����洢����Ϊ����ʧ���ݴ洢������������EEPROM�ɲ�ͬ������ʧ�洢���Ŀɲ�д����������ٵ���һ�ֽھ�����
									����EEPROM����FLASH����ˡ���Щ�����ݴ洢�Ĵ�����FLASH���Ի���İٷֱ���Ϊ�����ж����ݣ���Ȼ�ſ��˺ܶࡣ
									
									EEPROM���������ģ���ҳ�����ǲ�ͬ�ĸ��
									���Ĵ洢������������FRAM�洢�������������
									
									
									MCU�ϵ�EEPROM������FLASHģ��ģ����Զ����10��β�����
                  ������EEPROM���ǰ���β�����
									
									
					FRAM�ṩһ����RAMһ�µ�����,��������ROM һ���ķ���ʧ�ԡ� FRAM �˷����϶��ּ������ȱ�ݲ��ϲ����ǵ��ŵ㣬����ȫ�´���Ĳ�Ʒ��һ������ʧ�������ȡ��������
									*/
											//MainProcessTimeAdd(board,1);//ÿ���ӱ���Ҫѹ��AT24Cxx��һ�Σ���оƬ����Ϊ100��/1440��ÿ��=690�죬��Լ2��,added by sjw
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
									
									goto force_exit1;  //ǿ����������ѭ������added by sjw
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
	OSTimeDlyHMSM(0, 0, 0, 20);//������ָ������Ϻ��ʣ���added by sjw	 2023-12-5 in  tuesday!!
	
  EAST_FZ;
	while(1){
			switch(status){
						case IDLE:
								status=WAIT_TIME;
						    LightSlotFlag=1;
						break;
						
						
						
						case WAIT_TIME://ǿ�Ƶȴ�500ms��һ��Խ�����λ���ˣ�added by sjw
							  if(LightSlotValue>500){
									  LightSlotFlag=0;
								    LightSlotValue=0;
										status=HIGH;
								}else{
									OSTimeDly(20);
								}
						break;
						
						case HIGH:
							  if(EAST_FK_PIN==0){//��ʼ ���  �����۵�λ���ˣ�
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
									
									goto force_exit2;  //ǿ����������ѭ������added by sjw
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
									MainProcessTimeAdd(board,2);//ÿ���������Ҫѹ��AT24Cxx��һ�Σ���оƬ����Ϊ100��/2880��ÿ��=347�죬��Լ1��,added by sjw
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
									MainProcessTimeAdd(board,3);//ÿ���������Ҫѹ��AT24Cxx��һ�Σ���оƬ����Ϊ100��/2880��ÿ��=347�죬��Լ1��,added by sjw
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
									MainProcessTimeAdd(board,4);//ÿ���������Ҫѹ��AT24Cxx��һ�Σ���оƬ����Ϊ100��/2880��ÿ��=347�죬��Լ1��,added by sjw
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
								 if(p_timemu->second>=58){//1���ӽ�ʱ��ѹ��AT24C���棡��
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
								 if(p_timemu->second>=58){//1���ӽ�ʱ��ѹ��AT24C���棡��
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
								 if(p_timemu->second>=58){//1���ӽ�ʱ��ѹ��AT24C���棡��
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
								 if(p_timemu->second>=58){//1���ӽ�ʱ��ѹ��AT24C���棡��
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
						if((p_timemu->second==58)&&(!flag)){//1���ӽ�ʱ��ѹ��AT24C���棡��
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
1���������һ��Ҫ���ء�

2��������ӵ�MOSI��MISO����Ҫ�������ӡ�

���߷�ʽ
SCK----SCK
MOSI----MOSI
MISO----MISO
NSS----NSS

*/
void SPI1_Init (void)
{

		GPIO_InitTypeDef  GPIO_InitStructure;
		SPI_InitTypeDef   SPI_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE); //ʹ��SPI2��PB


	
	//����MOSI�˿�
		GPIO_InitStructure.GPIO_Pin = SPI_MOSI_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI_MOSI_GPIO_PORT,&GPIO_InitStructure);
	
	
	
	   //����MISO�˿�
		GPIO_InitStructure.GPIO_Pin = SPI_MISO_GPIO_PIN;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(SPI_MISO_GPIO_PORT,&GPIO_InitStructure);
		
		
		
		 //����SCK�˿�
		GPIO_InitStructure.GPIO_Pin = SPI_SCK_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI_SCK_GPIO_PORT,&GPIO_InitStructure);



    //����CS�˿�
		GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(SPI_CS_PORT,&GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure); //PB12���ó�������� ��CS��

	
	
	/*
	  SPI1->DR=0x98;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6? | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure); //PA5��PA6��PA7,�������������SCK��MISO��MOSI��
*/







		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //˫��ģʽ
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave ; 											//SPI   xģʽ
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 									//8bit����

		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //CLK����ʱΪ�ߵ�ƽ
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //CLK�����ز�������Ϊ�������ǵڶ������ض���������Ҳ�������Ϊ�ڶ������ز���

		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                         	//Ƭѡ���������
		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����

		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; 	//SPIƵ�ʣ�72M/4 = 18M
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 									//��λ��ǰ
		SPI_InitStructure.SPI_CRCPolynomial = 7; 														//crc7��stm32spi��Ӳ��ecc
		SPI_Init(SPI1, &SPI_InitStructure);

		SPI_Cmd(SPI1, ENABLE);

		//SPIx_ReadWriteByte(0xff);//��������



}



INT8U SPIx_ReadWriteByte(INT8U TxData)
{

  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);


  SPI_I2S_SendData(SPI2, TxData);


  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);


  return SPI_I2S_ReceiveData(SPI2);
}			  




/*********************************
*���ܣ�������������
*���룺
*********************************/
void StartGetSysParm(void)
 { 
  unsigned int read_data[24],t,check=0; 
  
	  

	 /*
	 //��ȡ����1ʱ�� ��  
	 //��ȡ����1ʱ�� ��
	 //��ȡ����1ʱ�� ʱ
	 //��ȡ����1ʱ�� ���� 
	 //У�� 
	 
	
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

  Light_start=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR);    //��ȡ������ʼʱ��
  if(Light_start>=24)    Light_start=19;

  Light_end=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR+0x02); //��ȡ��������ʱ��
  if(Light_end>=24)      Light_end=6;

  Light_en=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR+0x04);  //��ȡ����ʹ��
  if(Light_en>=2)       Light_en=1;  

  Songs_nummber=(unsigned char) Eeprom_ReadWord(DATA_START+SONG_ADDR);   //��ȡ��ʱ���ֺ�
  if(Songs_nummber>14)   Songs_nummber=9;

  Strike_nummmber=(unsigned char) Eeprom_ReadWord(DATA_START+STRIKE_ADDR); //��ȡ���Ӻ�
  if(Strike_nummmber>11) Strike_nummmber=7;


  for(t=0;t<5;t++)     //��ȡ�Զ��屨ʱ���ֳ���
   {
    Songs_minite[t+10]=(unsigned char) Eeprom_ReadWord(DATA_START+LONG_ADDR+t*2);
    Songs_second[t+10]=(unsigned char) Eeprom_ReadWord(DATA_START+LONG_ADDR+0x10+t*2);

    if(Songs_minite[t+10]>4||Songs_second[t+10]>59)
     {
      Songs_minite[t+10]=1;
      Songs_second[t+10]=30;
     }
   } 

  for(t=0;t<24;t++)    //��ȡ��ʱ��
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

  for(t=0;t<2;t++)    //ʱ������
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

  read_data[0]=Eeprom_ReadWord(DATA_START+WARN_ADDR);//������ϼ�¼
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
*���ܣ�������Դ����
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
      if((p_timemu->hour>=Light_Start || p_timemu->hour<Light_End))   //ԭ��Ϊp_timemu->hour<=Light_End �����޸�Ϊp_timemu->hour<Light_End   added by sjw                      
          SSR_ZM_STATUS(1);
      else  
					SSR_ZM_STATUS(0);
     }
   }else 
				SSR_ZM_STATUS(0); 
 }




/*
���ܣ�����MP3
���룺MP3��ţ���ʽΪmp3_xxxx.mp3
       xxxxΪMP3���
			 
			 

���ӻ����ӷ�����ʱ����
24  0F 04 01 0C 4D 50 33 5F 30    30 36 36 2E 4D 50 33 77   --������ǰ�࣡ ����3�Σ���
24  0F 04 01 0C 4D 50 33 5F 30    30 35 36 2E 4D 50 33 74  ����n��         ����3�Σ���


24  0F 04 01 0C 4D 50 33 5F 30    30 36 32 2E 4D 50 33 73  ������ǰ�࣡    ����3�Σ���
24  0F 04 01 0C 4D 50 33 5F 30    30 35 35 2E 4D 50 33 77����n��          ����3�Σ���
	 

�����CPU��MP3ģ����������£�  
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--�����ֽ�Ϊ60��
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16��ǰ�ࣺ
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77   --������ǰ�࣡
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
17��ǰ�ࣺ
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
    24 03 0F 01 1F 12
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 


�����ַ�ASCII���
https://www.perfcode.com/p/control-character.html

	
�����CPU��MP3ģ����������£�  
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--�����ֽ�Ϊ60��
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16��ǰ�ࣺ
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
	
	
	
	
35��mp3ģ�鷢��24 04 00 00 1F 12 24 04 00 0B   16��
����mp3ģ�鷢��24 04 00 0B 

35��mp3ģ�鷢��24 04 00 00 1F 12 24 04 00 0B   17��
����mp3ģ�鷢��24 04 00 0B 
	
�κ�ʱ�α�ʱ��ʱ��MP3ģ�鶼�Ƿ�����������������   added by sjw  
	
��������С���ʱ��ϸ������  9600 ��n��8,1

���磺  41 00 00 00 00 01 00 0D 0A-------------------��9���ֽ�,����������
       41 00 00 00 00 02 00 0D 0A-------------------��9���ֽ�,����pay

*/




/*********************************
*�� �ܣ��� ʱ 
*�� �룺
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
	16��ǰ�ࣺ
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77   --������ǰ�࣡
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
	
	�õ��ļ�15��
	24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B 
24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B 
24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B

	 
*/
  switch(mp3_state){
		
			case 0 :      
				 for(k=0;k<24;k++){      
					 if(Report_Time[k]==1){      	 
						report_hour=k;                 //��ʱ��ʼʱ   
						report_minute=0;               //��ʱ��ʼ��  

						 
						rythem_number=Rythem_Number;   //ǰ�����ֺ�
						strike_number=Strike_Number;   //���������� 
					 
						start_second=59-Rythem_Second[rythem_number];   //��ʱ��ʼ��        
						start_minite=59-(Rythem_Minite[rythem_number]-report_minute);
						start_hour=report_hour-1;
						 
						if(start_hour>=24) start_hour=23;  
						
						power_on_minite=start_minite-1; //���ŵ�Դ����ʱ��
						if(power_on_minite>=60){  
								power_on_minite=59;
								power_on_hour=start_hour-1;
								if(power_on_hour>=24) power_on_hour=23;
						}else 
								power_on_hour=start_hour;  
						
						if((p_timemu->hour==power_on_hour)&&(p_timemu->minute==power_on_minite)){   
							
								SSR_BS_STATUS(1);//���������Դ                        
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
           
         SSR_BS_STATUS(0); //�رձ�ʱ��Դ    
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

   ��ӡ�̣߳�������1���յ������ݴ�ӡ����

*********************************************************************************************************
*/


/*

����һЩΥ����������⣬һ���ֲ��϶����ж����˵��Ϊʲô���������������ֲ����Ҫ��
�ͽ�����ԣ�����һ��С��Ŀʱ�õ���STM32��PB4����ܽţ�Ȼ�������һ��GPIO��ͨ�����ã������ڵ���ʱ��ȴ��������Ų���������������Ϊ�ͣ�
�����ҸϽ�ȥ�������ֲᣬȻ����PB4�ܽŻ��и��ù��ܣ���һ��JTAG�ĵ������ţ����Ҷ���һ��������������ܽ����ϵ縴λʱ��Ĭ��Ϊ�������ŵĹ��ܣ�
�����ĸ��ù��ܲ�����ͨIO�ڣ����ƵĻ���PB3/PA13/PA14�ȹܽŶ���һ����Ҫ������ͨIO�ڣ���Ҫ����Ϊ����ģʽ��

1�������ȴ򿪸���ʱ�ӣ���ʹ�ú�������JTAG���ԣ�������ܻ����ò��ɹ���

STM32 PC13 PC14 PC15 PB3 PB4 PA13 PA14 PA15 ����ͨIO�ڱʼ�
*/
void LedPortSpecialInit(void)
{
		//STM32��PB3��PB4��PA15������ͨIO�����÷���������jtag��ʹ��SW ���ߣ����Ͱ��� https://www.bilibili.com/read/cv23389778/ ������bilibili
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);      //ʹ��PA,PB�˿�ʱ��   ע�����һ���˳�򣬱����ȿ���AFIOʱ��		
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);    //���������Ž�����ӳ�� :  �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ��

	//�ر�JTAG��PB3 PB4 PA15�Ĺ��ܣ���Ϊ��ͨI/O��ʹ�ã���Ӱ��SWD�����ص��ԡ� ���ߣ����Ͱ��� https://www.bilibili.com/read/cv23389778/ ������bilibili
	
	//�ر�JTAG��PB3 PB4 PA15�Ĺ��ܣ���Ϊ��ͨI/O��ʹ�ã���Ӱ��SWD�����ص��ԡ� ���ߣ����Ͱ��� https://www.bilibili.com/read/cv23389778/ ������bilibili


	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);�򿪴�ָ���PA15�Ͳ���˸�ˣ���������������������������added by sjw
	//ԭ��ο��������£�   https://blog.csdn.net/weixin_46528483/article/details/113940390
	//��Ϊִ��ָ��GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);���ǲ�����PA15������added by sjw
	
	
	//�����ر�PB4��JTAG���ܣ���PB4��Ϊ��ͨI/Oʹ�á� ���ߣ����Ͱ��� https://www.bilibili.com/read/cv23389778/ ������bilibili
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);       //�ͷ�JTAG����Ϊ��ͨIO��, �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_Disable SWJ ��ȫ���ã�JTAG+SW-DP��
}



void LedBsZm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO,ENABLE );
	//PWR_BackupAccessCmd( ENABLE );/* �����޸�RTC�ͺ󱸼Ĵ���*/
	//RCC_LSEConfig( RCC_LSE_OFF ); /* �ر��ⲿ����ʱ��,PC14��PC15����������ͨIO*/
	//BKP_TamperPinCmd(DISABLE);  /* �ر����ּ�⹦��,PC13����������ͨIO ���ߣ����Ͱ��� https://www.bilibili.com/read/cv23389778/ ������bilibili*/

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
	
	//PWR_BackupAccessCmd(DISABLE);/* ��ֹ�޸�RTC�ͺ󱸼Ĵ���*/
    //BKP_ITConfig(DISABLE);       /* ��ֹTAMPER �ж�*/ ���ߣ����Ͱ��� https://www.bilibili.com/read/cv23389778/ ������bilibili
	
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
	
	
	 MP3_RESET_STATUS(1);//��ߺ�VS1003С�帴λ��������  added by  sjw
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
*             LED ��ˮ��
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
2��4 Һ����ʾģ�� 
����LCD3310Һ����һ��48��84�е�Һ����ʾ��������е͹���PCD8544��CMOS LCD���������������������ٶ���߿ɴ�4��O Mb��s��
Ϊ����LCD3310Һ���ܹ���ʾ4��12��12�ĺ��֣�ϵͳ������һ��6��84�ֽڵĻ�������дҺ��ʱ�Ͳ���ֱ��д��LCD3310�ľ�̬ DDRAM�ˣ�
������д��ϵͳΪ�����ٵ����ݻ������������ˢ���޸ĵĲ��־Ϳ�����ʾ��Ҫ��ʾ�����ݡ�LCD3310�Ľӿڲ���SPIģʽ�����·��ͼ6 ��ʾ�� 

3 ������ 
����ͼ7��MP3��������������̡�ϵͳ�������ȳ�ʼ��Ӳ��ģ�顣�ɵ�Ƭ��ͨ��FAT32�ļ�ϵͳ�ӿڶ�ȡSD����һЩ������Ϣ��
��������������С��FAT ���Լ���Ŀ¼���ڵ���ʼ�����ȡ�ͨ����Щ��Ϣ�Ϳ����ҳ�SD���Ƿ��п��Բ��ŵ������ļ���
���У���Ƭ��ͨ��SPI���߷�ʽ������Ƶ��Ϣ������������������Ϣ���뵽VS1003оƬ�У�
ͨ��VS1003����оƬ�����ں��ĸ�����������DAC�Ͷ���������·��ʵ��MP3�����Ĳ��Ź��ܡ�
�ڰ����Ŀ����£�ͨ�� LCD3310�в˵�ѡ���ѡ��ʵ�ֶԸ���ѡ���������Ƶȹ��ܣ�
�ڲ��ŵ�ͬʱ��LCD3310����ʾ����Ϣ�����������⣬���������Ⱥ������ȡ� 


�����������в��ԣ�ϵͳ�������������ز��ų�320 kb��s�ĸ�����MP3�����ļ���
������ʹ��500 mA﮵�ص�����£��������������ز��ų���10��Сʱ���ɼ����书�ıȽϵ͡� 

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
//	PWR_BackupAccessCmd(ENABLE);//�����޸�RTC �ͺ󱸼Ĵ��� 
//    RCC_LSEConfig(RCC_LSE_OFF);//�ر��ⲿ�����ⲿʱ���źŹ��� ��PC13 PC14 PC15 �ſ��Ե���ͨIO�á� 
//    PWR_BackupAccessCmd(DISABLE);//��ֹ�޸ĺ󱸼Ĵ��� 
	

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
*���ܣ�������������
*���룺
*********************************/

static	void GPIO_I2C_Config(void)
{
	struct tm now;
	
	 iic_sw_init();
	// get_iic_setting();//��ȡ����ʱ�䡢��ʱ�����趨��Сʱ����ʱǰ�༰�������������ص��趨����added by sjw
	

	
}








static	void GPIO_Key_Config(void)
{
	
	EXTI_InitTypeDef EXTI_InitStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;//��PE10����EXTI_Line10����ΪPPS�źŵ����룬��������Ч!!added by sjw
	
	
	
	
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE );  //PE10Ϊ�����жϣ���
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
  GPIO_InitTypeDef GPIO_InitStructure;//��PA11��Ϊpps�źŵ������!   added by sjw
	
	
	
	
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );  //PA11Ϊ�����жϣ���
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







//ֱ�ӽ����˵�ַ��������ݣ�Ҳ����ֵ����
//�ں����ڲ�ȷʵ�������������ݣ��˳�������û�н�������
void MainSwapValue(INT16U *p1,INT16U *p2)
{
	INT16U value;
	value=*p1;
	*p1=*p2;
	*p2=value;
}

//ֱ�ӽ����˵�ַ��������ݣ�Ҳ����ֵ����
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

void MainSwapAddr(INT16U **p1,INT16U **p2)//Ҫ�������ݣ�����ý�����ַ��ʵ�֡�
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
			//return i;//���߸����Ҳ���ԣ�
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

/*�����ʽ���£�

��Ʒ�ڲ�Flash��СΪ��512K�ֽڣ� 	 www.armjishu.com

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
��������������������������������
��Ȩ����������ΪCSDN������shaohui973����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/shaohui973/article/details/109627989
hamming weight algorithm(�����㷨)�Լ�kernel��ʵ��
https://blog.csdn.net/shaohui973/article/details/109627989

����������ʹ�������ݴ�������Ʊ�������ģ�����������һ������
�������ַ�������������㣬��ͳ�ƽ��Ϊ1�ĸ�������ô��������Ǻ������롣
�����������ַ��������ͬ�����ȵ����ַ����ĺ������룬Ҳ����˵�������ַ����з����Ԫ�ظ�����
���ڶ������ַ�����˵������ 1 �ĸ��������� 11101 �ĺ��������� 4��
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
	//�����޸Ĳ�������:::
	 /*
	 1.���ļ�ffconf.h�ĵ�40��  _USE_MKFS         ����Ϊ  1
	 2.	���ļ�ffconf.h�ĵ�36��_USE_STRFUNC	      ����Ϊ  1
	 
	 3. ���ļ�ffconf.h�ĵ�48��_USE_LABEL		      ����Ϊ  1	
	 
	 4.���ļ�ffconf.h�ĵ�122�� _FS_RPATH         ����Ϊ  1	
	 5.���ļ�ffconf.h�ĵ�148��	_MULTI_PARTITION	����Ϊ  1	
	 
	 7.���ļ�demo_nand_fatfs.h�ĵ�27��  #define BUF_SIZE				(4*1024)   �޸ĳ�(2*1024)
	 
	 8.���ļ�integer.h�ĵ�7�� �����  #define _WIN32             added by sjw
	 9.���ļ�bsp_nand_flash.h�ĵ�101�� #define NAND_MAX_ZONE  �޸�Ϊ102���ϣ�
	 10.���ļ�bsp_nand_flash.h�ĵ�97�� #define NAND_PAGE_SIZE  �޸�Ϊ98���ϣ�
	 
	 11.���ļ�bsp_nand_flash.h�ĵ�105������
	 12.���ļ�bsp_nand_flash.h�ĵ�97��#define NAND_PAGE_SIZE             ((uint16_t)0x0800) �޸�Ϊ0x0200
	 
	 13.���ļ�bsp_nand_flash.h�ĵ�99��#define NAND_BLOCK_SIZE            ((uint16_t)0x0040) �޸�Ϊ0x20
	 
	 14.���ļ�bsp_nand_flash.h�ĵ�100��	#define NAND_ZONE_SIZE           ((uint16_t)0x0400) �޸�Ϊ0x1000(4096����)
	 15.���ļ�bsp_nand_flash.h�ĵ�101��#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0040) �޸�Ϊ0x10
	 
	 16.���ļ�bsp_nand_flash.h�ĵ�112��#define NAND_ADDR_5					       1�޸�Ϊ0
	 17.���ļ�bsp_nand_flash.h�ĵ�125��#define NAND_BLOCK_COUNT			   1024 // ����� �޸ĳ�4096����
   18.���ļ�famc_nand.h�ĵ�56��#define FLASH_MAX_ADDR 0x7FFFFFF��Ϊ0x4000000 ����64M
	 19.���ļ�bsp_nand_flash.h�ĵ�108��#define NAND_MAX_ZONE       ��Ϊ       ((uint16_t)0x0004)
	 20.���ļ�bsp_nand_flash.h�ĵ�133��#define BI_OFFSET				    0		���ڵ�1��page�������ĵ�1���ֽ��ǻ����־  ��Ϊ6
   21.���ļ�bsp_nand_flash.c�ĵ�1651�е�1655�����Σ�
	 22.���ļ�famc_nand.h�ĵ�59��#define FLASH_BLOCK_SIZE 0x20000  128k---->16K
	 23.���ļ�bsp_nand_flash.h�ĵ�137��#define VALID_SPARE_SIZE		4��Ϊ6		 ʵ��ʹ�õı�������С,���ں����ڲ��������ݻ�������С 


	 
	 //K9F1208U0M 64M nand flash �ֲ��Ķ��Լ���������������
   //https://blog.csdn.net/hfdghjh/article/details/86776939
	  

	
	//https://blog.csdn.net/xiaoluoshan/article/details/51695121
	//Nandflash K9F1208U0Bѧϰ   �����Ϸǳ�ʵ�ã���
	
	STM32 IOģ��nand flash�ĸ������
	https://bbs.csdn.net/topics/380034182
	
	
	NAND FLASH�洢��ʵ����ϵͳ�еĶ�д�Ϳ��� Ҳ��ӽ�����ģ��gpio�˿ڵĲ���ʱ�򣡣�Ҳͦ�õ���
	https://www.elecfans.com/d/744442.html
	
	
	//LUT���ұ�ʵ�ָ���RAM��ROMԭ����
	//https://blog.csdn.net/weiaipan1314/article/details/104327009
	
	//Stm32�ļ�ϵͳFATFS����ʼ��2021-09-09��
	//https://blog.csdn.net/weixin_51915497/article/details/120201305?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~aggregatepage~first_rank_ecpm_v1~rank_v31_ecpm-7-120201305.pc_agg_new_rank&utm_term=fatfs+fdisk%E4%B8%8Esfd%E7%9A%84%E5%8C%BA%E5%88%AB&spm=1000.2123.3001.4430
	 
	
	
	//https://blog.csdn.net/hanchaoman/article/details/102660884
	//STM32-��ֲFATFS��NANDFLASH����
	//ʹ��ԭ���忨�Դ��Ĵ洢оƬDF2M8HM�������Ѿ���mp3��ʱ�ļ��ˣ�������103ve��������ʽ��ʧ�ܣ����E�ɹ�����ʾFR_NOT_READY��
	//�������,����1024����ȫ��Ϊ���飬��Ϊ�ײ���û�в�����ȷ��
	//FatFsѧϰ(1)����ö�٣�����ֵFRESULT            https://blog.csdn.net/qq_38318207/article/details/108554207 
	//���ǵ�һ���ڴ�оƬ����ʽ����ʱ�򣬺ÿ�Ϊ0x0183��block
	/*
		�ڸ��ڴ�оƬ����ʽ����ʱ�򣬺ÿ�Ϊ0x18c��block                             ��2���ڴ�оƬ����ʽ����ʱ�򣬺ÿ�Ϊ0x3ea��block
		

	
	//https://www.zhihu.com/question/62799132
	//һ���ϸ��Ƕ��ʽ�����������ʦҪ������Щ֪ʶ��
	
	
	//���ļ�ϵͳ�����ļ��Ŀ�Ĳ���ת��Ϊ������洢�������ĸ��ֲ�����
	//https://blog.csdn.net/hanchaoman/article/details/86607456
	 
	 
	 https://bbs.elecfans.com/jishu_1096766_1_1.html
	 
	 �ڵ�������ʱ���ҵ�����λ�����ȣ�����f_open����f_open����find_volume������
	 ����������У���0������ȡfat��ռ������С��ÿ�������ֽ�����fat��������Ŀ¼λ�õ��й���Ϣ����������ú�������ֵ����FR_OK����ֱ���˳�f_open������

����find_volume��������find_volume������������һ�д��룺
fmt = check_f( fs, bsect );���Ҹ��ݷ���ֵ��Ҳ����fmt��ֵ����ȷ���Ƿ�Ϊfat�ļ�ϵͳ��

Ȼ�����check_fs�����������Ƚ���move_window������Ȼ���жϽ�β�Ƿ�Ϊ0XAA55����ͷ����תָ���Ƿ���0XEB 0X** 0X90��Ȼ���ж��Ƿ��ҵ�FAT����FAT3������

��move_window�����У���Ҫʵ����fs->win[]�е����ݻ�д��Ȼ�����¶�ȡָ�����������ݣ�
���������ͳ�������ڶ�ȡ0����������ʱ����ȡ�����ݴ�����˾͵�������check_fs�������ж�������β�Ƿ���0XAA55ʱ�������˴��󣬷�����2��
Ȼ����find_volume�����У��ж�fmtʱ��������FR_NO_FILESYSTEM��
	 

stm32f2ϵ�У�����NAND FLASH֮�ϵ�Fatfs����ֲ   ����˼����Խ�� added by sjw
http://blog.sina.com.cn/s/blog_c5c2bd470102v2p2.html
	 
	 
	 
	
		
		
		STM32 USB�����жϺ�����Ҫ����
		https://blog.csdn.net/yxfabcdefg/article/details/52336070?locationNum=4&fps=1
		
		
		
		
		http://www.elecfans.com/emb/arm/20171106575725.html
		
		
		stm32f103 usb���������޷�ʶ�����취��
����1��usb��ʹ�õ�IO��������Ϊusb���Զ����书�ܣ�����Ҫ�����ã�һ��Ҫ���õĻ��ᱻ���ԣ�����ҲûʲôӰ�졣

����2��usbʱ������ֻ�����ֿ��ã���Ƶ72M��usbʱ��1.5��Ƶ����Ƶ48M��usbʱ��1��Ƶ��

����3��PA12��USBP / D+��һ��Ҫ��1.5k���������裬���ڵ���ʶ���豸���ٷ���ʹ����lO�ڿ�����������
       ��������������ƶϿ����������ӣ�ֱ����������ԴҲ�ǿ��Եģ�������Ҫ�Ͽ�����������ʱֻ���ֶ���Ρ�

����4��stm32f103��can��usb����ͬʱʹ�ã�can��ʱ�Ӵ򿪺󣬵��Ծͻ�ʶ�𲻳�usb�豸��
        �����������ܶ�Ҫ�õ��Ļ������ǻ���f105��f107���������ͺ��ǿ���ͬʱʹ�õġ�
		
		
	
	
	
	
		
		����STM32��USBö�ٹ���ѧϰ�ʼǣ�ת��
		https://www.cnblogs.com/erhu-67786482/p/10790814.htm	
		
		
		
		
		
		https://blog.csdn.net/qq236106303/article/details/8177568
		����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
		����������USB�豸��ö�٣�ö�پ��Ǵ��豸��ȡ������������Ϣ�����������Ϳ��Ը�����Щ��Ϣ�����غ��ʵ��������Ӷ�֪����ʲô�����豸����ν���ͨ�š�
		ö�ٹ���ʹ�õ��ǿ��ƴ��䡣���ƴ�����Ա�֤���ݵ���ȷ�ԡ����ƴ�����������̣��������̣���ѡ���ݹ��̼�״̬����
		
				
		STM32-USBѧϰ�ʼǣ�һ�� USB����
		https://www.doc88.com/p-505935487642.html

		STM32 USB�����жϺ�����Ҫ����
		https://blog.csdn.net/yxfabcdefg/article/details/52336070

		https://www.pianshen.com/article/97651154818/

		����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
		https://blog.csdn.net/qq236106303/article/details/8177568   ��
		http://www.360doc.com/content/17/1025/06/6889381_697883568.shtml
		http://www.360doc.com/content/17/1025/06/6889381_697884130.shtml


		����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
		https://blog.csdn.net/qq236106303/article/details/8179005


		����STM32��USBö�ٹ���ѧϰ�ʼ�(��)
		https://blog.csdn.net/qq236106303/article/details/8181336?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&utm_relevant_index=2

    
		USBö�ٹ��̷���
		https://blog.csdn.net/duan_xiaosu/article/details/68930643
		�������վ�����ݿ��԰����ҽ�usbö�ٵĸ����ֶ����͸�У��ǳ�����ĺ����£�
		
		

	 
	
	 
	 	
  		bDeviceState ȫ�ֱ�����usb_pwr.c�ж��壬���ڱ�ʾUSB Device��״̬ 
	  typedef enum _DEVICE_STATE
		{
			UNCONNECTED,
			ATTACHED,
			POWERED,
			SUSPENDED,
			ADDRESSED,
			CONFIGURED
		} DEVICE_STATE;
  	
  	  	
  	//����һ��USB����
  	// Enable the SDIO AHB Clock 
		
	*/
	
	
	 




