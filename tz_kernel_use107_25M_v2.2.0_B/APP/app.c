/*
Äã¼ÆËã»úÉÏÒ»¸öÓÐÐ§µÄ²ßÂÔÊ¹ÄãÎÞ·¨Á¬½Óµ½´Ë´òÓ¡¶ÓÁÐ¡£ÇëÓëÄãµÄÏµÍ³¹ÜÀíÔ±ÁªÏµ
https://baijiahao.baidu.com/s?id=1739583361867564493&wfr=spider&for=pc







STM32Òý½ÅÁÐ±íÖÐÖ÷¹¦ÄÜ£¬Ä¬ÈÏ¸´ÓÃ¹¦ÄÜºÍÖØ¶¨Òå¹¦ÄÜµÄÇø±ð

1 Ö÷¹¦ÄÜ¾ÍÊÇSTM32»ù±¾IO¿Ú£¬ÓëÍâÉèÃ»ÓÐÁ¬½ÓµÄ£¬ÎÒÃÇ¿ÉÒÔÖ±½ÓÊä³ö»ò¶ÁÈë¸ßµÍµçÆ½

Ê¹ÓÃÊ±²ÉÓÃÒª³õÊ¼»¯GPIO½á¹¹Ìå²ÎÊý£¬²¢´ò¿ª¶Ë¿ÚµÄÊ±ÖÓ

2 Ä¬ÈÏ¸´ÓÃ¹¦ÄÜÊÇÓëÍâÉèÁ¬½ÓµÄIO¿Ú£¬µ¥Æ¬»úÍ¨¹ý¿ØÖÆÍâÉèÀ´¿ØÖÆIO¿Ú

Ê¹ÓÃÊ±²ÉÓÃÒª³õÊ¼»¯GPIO½á¹¹Ìå²ÎÊý£¬IO¿ÚµÄ¹¤×÷Ä£Ê½Òª¸ü¾ßSTM32ÖÐÎÄ²Î¿¼ÊÖ²áÖÐ£¬IO¿Ú¸´ÓÃ¹¦ÄÜµÄÉèÖÃ¹¤×÷Ä£Ê½£¬
ÉèÖÃÊ±£¬ÓëÖ÷¹¦ÄÜµÄÎ¨Ò»Çø±ð¾ÍÊÇIO¿ÚµÄ¹¤×÷Ä£Ê½µÄ²»Í¬¡£

3 µ±ÎÒÏë°ÑÍâÉè²»Á¬½Óµ½Ä¬ÈÏÒý½ÅÉÏ£¬ÄÇ¾Í¸ù¾Ý¡°ÖØ¶¨Òå¹¦ÄÜ¡±ÕâÒ»ÁÐÀ´ÖØÐÂ¶¨ÒåÍâÉèÁ¬½ÓµÄIO¿Ú¡£Ò»°ãÇé¿öÎÒÃÇ²»»áÓÃµ½¡£

 

×¢Òâ£º
Ò»µ©ÐèÒª¶ÔAFIO¼Ä´æÆ÷ÅäÖÃÊ±£¬Ò»¶¨Òª´ò¿ªAFIOµÄÊ±ÖÓ£¨Ò»°ãÔÚÊ¹ÓÃÍâ²¿ÖÐ¶ÏEXTI»òÍâÉèÒý½ÅÖØ¶¨ÒåÊ±£©
--------------------------------------------------------------------------------------------------







ÊÊÓ¦µÄµçÂ·°åÎªBMT-DP-MAIN-01B.PCB
»¹ÓÐÒ»ÖÖÉÏÃæÓÐ±³°åµÄ£¬³ß´ç´óÉÏÃæÓÐÒ»¿é±³°å£¬ÐÍºÅÎªGSFG-DP-1A.PCB
Éè¶¨ÆæÊýÎª¿ª·¢Ê÷£¬±íÊ¾¹¦ÄÜÕýÔÚÑéÖ¤¡£¡£¡£
Éè¶¨Å¼ÊýÎªÎÈ¶¨Ê÷£¬±íÊ¾¹¦ÄÜÒÑ¾­µÃµ½ÑéÖ¤£¨²Î¿¼LINUXÄÚºËµÄ¿ª·¢Á÷³Ì×ö£©

ÒÔÏÂÒý½Å¶¨ÒåËäÈ»»ùÓÚ103µÄ£¬µ«ÊÇÓÃÔÚ407ÉÏÒ²¿ÉÒÔ½è¼ø£¡£¡added by sjw 10.18

STM32 = »ùÓÚARMµÄ32Î»Î¢¿ØÖÆÆ÷
F     = Í¨ÓÃÀàÐÍ 
103   = ÔöÇ¿ÐÍ 
R     = 64½Å                                  
V     = 100½Å                                  
Z     = 144½Å 
C     = 256K×Ö½ÚµÄÉÁ´æ´æ´¢Æ÷                                  
D     = 384K×Ö½ÚµÄÉÁ´æ´æ´¢Æ÷                                  
E     = 512K×Ö½ÚµÄÉÁ´æ´æ´¢Æ÷
H     = BGA                                  
T     = LQFP                                  
Y     = WLCSP64 
 
STM32F103VET6Æ¬ÉÏ×ÊÔ´
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
           2 ¸ö16Î»´øËÀÇø¿ØÖÆºÍ     2 ¸ö16Î»»ù±¾¶¨Ê±Æ÷        ¶ÀÁ¢ÐÍºÍ´°¿ÚÐÍ
           ½ô¼±É²³µ£¬ÓÃÓÚµç»ú¿ØÖÆµÄPWM¸ß¼¶¿ØÖÆ¶¨Ê±Æ÷   ÓÃÓÚÇý¶¯DAC 
                            
                                      
SysTick : 1 SysTick Timer, ÏµÍ³Ê±¼ä¶¨Ê±Æ÷£¬24Î»×Ô¼õÐÍ¼ÆÊýÆ÷
SPI/I2S : 3 SPI/I2S, ÓÐÁ½¸ö¿É¸´ÓÃÎª I2S
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
           I2C1£ºPB6-I2C1_SCL¡¢PB7-I2C1_SDA
           I2C2£ºPB10-I2C2_SCL¡¢PB11-12C2_SDA
           
 					 USART   : 5 USART,
           PA9  - USART1(Tx) - USART1¿ÉÓÃÓÚ³ÌÐòÏÂÔØ
           PA10 - USART1(Rx) 
                   
 					 USB     : 1 USB 2.0 Full Speed Interface,
 					 CAN     : 1 CAN 2.0B Active,
           PB8 - CAN_RX
           PB9 - CAN_TX        
					                   
					 A/D     : 3 12-bit 16-ch A/D Converter, 
					 D/A     : 2 12-bit D/A Converter, 
					 SDIO    : 1 SDIO, 
					 GPIO    £ºFast I/O Ports
					 DMA     : 12 Í¨µÀ DMA ¿ØÖÆÆ÷
        Ö§³ÖµÄÍâÉè£º¶¨Ê±Æ÷¡¢ADC¡¢DAC¡¢SDIO¡¢
           I2S¡¢SPI¡¢I2C ºÍ USART

-----------------------------------------------------------------------------
STM32F103VET6Òý½Å¹¦ÄÜ
½ÅÎ»  ¹Ü½ÅÃû³Æ         ÀàÐÍ    I/OµçÆ½    Ö÷¹¦ÄÜ        Ä¬ÈÏ¸´ÓÃ¹¦ÄÜ                        ÖØÓ³Éä¶¨Òå¹¦ÄÜ
 1     PE2              I/O     FT         PE2           TRACECK/FSMC_A23    STM32µÄ×ÊÁÏÉÏÃæÐ´ÁË´øFTµÄÒý½Å¿ÉÒÔÄÍ5VÄÇ¾ÍÊÇ¿ÉÒÔ½Ó5VµÄ
 2     PE3              I/O     FT         PE3           TRACED0/FSMC_A19	   ¹àµçÁ÷£¬¿ÉÒÔµÄ£¬²»¹ýµçÑ¹¸ßÁË£¬Òª¿¼ÂÇºÃ·ÖÁ÷µç×è¡£
 3     PE4              I/O     FT         PE4           TRACED1/FSMC_A20		 Ó°Ïì¿Ï¶¨ÓÐ£¬µçÁ÷´óÁËÉÕI/O£¬µçÑ¹¸ßÁËÉÕÇ¯Î»¶þ¼«¹Ü¡£
 4     PE5              I/O     FT         PE5           TRACED2/FSMC_A21		 ÓÐFT±ê¼ÇµÄ½ÅÉèÖÃÎªÊäÈë»òODÊä³öÊ±¿ÉÒÔ£¬ÉèÖÃÎªÍÆÍìÊä³ö²»ÐÐ¡£
 5     PE6              I/O     FT         PE6           TRACED3/FSMC_A22
 ------------------------------------------------------------------------------
 6     VBAT             S       -          VBAT	²éµ½FTµÄº¬Òå£¬Ò²¾ÍÊÇÄÇ¸ö5VÈÝÈÌµÄIO½á¹¹£¬½á¹¹ÄÚ²¿È·ÊµÊÇÒ»¶Ô¶þ¼«¹Ü£¬µ«ÊÇÄÇ¸öµ½VDDµÄ¶þ¼«¹ÜËÆºõÓÐµãÌØÊâ£¬
 																								ÌØÊâÔÚÓÚËûµÃIO¿ÚÊäÈëµçÑ¹³¬¹ý5VÊ±£¬²Å»áÍùVDD¹àµçÁ÷¡£ÀàËÆÓÚÕâ¸ö¶þ¼«¹ÜµÄ½µÑ¹±È½Ï´ó¡£
																								È¥¿´datasheet£¬ÓÐÒ»ÕÅ±íÓÐÐ´ÁËºÜ¶àio¿Ú£¬ÓÐÐ©±êÁË¡°FT¡±µÄ¾ÍÊÇ¿ÉÒÔ5v
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

 14    NRST             I/O     -          NRST				 µÍµçÆ½¸´Î»
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
 70    PA11              I/O    FT         PA11          USART1_CTS/USBDM USBDM = USB Data Minus£¬USBÊý¾Ý¸ºÐÅºÅ£»
                                                         CAN_RX (7) /TIM1_CH4 (7)
 71    PA12              I/O    FT         PA12          USART1_RTS/USBDP/USBDP = USB Data Positive£¬USBÊý¾ÝÕýÐÅºÅ
                                                         CAN_TX (7) /TIM1_ETR (7)
 72    PA13              I/O    FT         JTMS/SWDIO                                        PA13
-----------------------------------------------------------------------------

 73    Î´Á¬½Ó
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
 
 ¡°ÏëÓÃPB6 PB7 »¹Ê¹ÄÜFSMCÊ±ÖÓ¡±£¬Í¬Ê±ÓÃ×÷I2CºÍFSMCµ±È»ÊÇ²»¿ÉÄÜµÄ£¬·ÖÊ±Ê¹ÓÃÊÇ¿ÉÒÔµÄ¡£
 Èç¹û´ò¿ªÁËFSMCÊ±ÖÓ£¬¼´Ê¹²»ÓÃFSMC_NADVÒý½Å£¬µ«ÊÇÕâ¸öÒý½Å»¹ÊÇÄ¬ÈÏ³É¸ßµçÆ½£»´Ó¶øÓÚI2C1_SDA³åÍ»¡£
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




 Ê¹ÓÃFSMCºó£¬STM32F103ZEµÄ¸ßÎ»Êý¾ÝµØÖ·¿ÉÒÔ×öIO¿ÚÊ¹ÓÃ
 Èç¹ûÒªÊ¹ÓÃÄ³¸ö¹Ü½ÅÎªFSMC¹¦ÄÜ£¬ÔòÅäÖÃ¶ÔÓ¦µÄGPIOÎª¸´ÓÃÊä³ö¹¦ÄÜ£»
 Èç¹û²»Ê¹ÓÃËüµÄFSMC¹¦ÄÜ£¬ÔòÖ»ÐèÅäÖÃ¶ÔÓ¦µÄGPIOÎªÆÕÍ¨Êä³ö¹¦ÄÜ(ÍÆÍì»ò¿ªÂ©)»òÊäÈë¹¦ÄÜ¼´¿É¡£

 FSMC·ÖÎªËÄ¸öBANK£¬ÆäÖÐBANK1Í¨¹ýNE[1..4]¿ÉÒÔÆ¬Ñ¡ËÄ¸öÍâÉè£¬Ò»°ã¶ÔÓÚÈëÃÅÕßÀ´ËµÖ÷Òª¿´µÄ¾ÍÊÇBANK1µÄ²Ù×÷£¬
 ±ÈÈçNOR FlashºÍLCDµÄ²Ù×÷¡£ÕâÀïÎÒÖ÷ÒªËµBANK1µÄÉèÖÃ¡£
 ¶ÔBANK1µÄ²Ù×÷Ö÷ÒªÊÇÊ×ÏÈÉèÖÃFSMC_BCRx[1..4]£¬FSMC_BTRx[1..4]ºÍFSMC_BWTRx[1..4]¼Ä´æÆ÷£¬°ÑÕâ¼¸¸ö¼Ä´æÆ÷µÄÒâÒåÅªÃ÷°×ÁË¾Í»ù±¾ºÃÁË£º
 FSMC_BCRxÊÇ¿ØÖÆÉèÖÃ¡£
 FSMC_BTRxÊÇ¶ÁÐ´Ê±ÐòÉèÖÃ¡£
 FSMC_BWTRxÊÇÐ´Ê±ÐòÉèÖÃ£¬¾ßÌåÄÚÈÝÓëFSMC_BTRxÏàÍ¬¡£
 Èç¹ûFSMC_BCRx[1..4]ÖÐÉèÖÃÁËEXTMODÎ», ÔòFSMC_BTRx[1..4]ºÍFSMC_BWTRx[1..4]Á½¸öÊ±Ðò¼Ä´æÆ÷·Ö±ð¶ÔÓ¦¶Á¡¢Ð´²Ù×÷¡£
 Èç¹ûÎ´ÉèÖÃEXTMODÎ»£¬Ôò¶ÁºÍÐ´Ê¹ÓÃÏàÍ¬µÄÊ±ÐòFSMC_BTRx[1..4]¡£



-----------------------------------------------------------------------------
I=ÊäÈë  O=Êä³ö  S=µçÔ´   HIZ=¸ß×è   FT=ÈÝÈÌ5·ü
TIM2_CH1_ETR±íÊ¾¿ÉÒÔÅäÖÃ¹¦ÄÜÎªTIM2_TI1»òÕßTIM2_ETR



LQFP48ºÍLQFP64Òý½Å¶¨Òå(À¨ºÅÄÚµÄÎª48Òý½ÅµÄ¶¨Òå£©
½ÅÎ»  ¹Ü½ÅÃû³Æ            ÀàÐÍ    I/OµçÆ½    Ö÷¹¦ÄÜ£¨¸´Î»ºó£©        Ä¬ÈÏ¸´ÓÃ¹¦ÄÜ                        ÖØ¶¨Òå¹¦ÄÜ
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

SPIµÄÊ±ÖÓ²»³åÍ»£¬¾Í¿ÉÒÔ£¬Ö®Ç°ÎÒÊÇ¼È¿ª spiµÄÊ±ÖÓ£¬ÒòÎª Õâ¸öPA6Òý½Å¼ÈÓÐSPI¹¦ÄÜ£¬ÓÖÓÐ TIM3µÄ CH1 ¹¦ÄÜ£¬Èç¹û Ê±ÄÜÁËSPIÊ±ÖÓ£¬
È»ºóÊµÓÃµÄÊÇTIM3 CH1 ¹¦ÄÜ£¬ÄÇÊä³ö¾Í²»ÕýÈ·ÁË¡£ÎÒÍ£Ö¹ÁËSPIÊ±ÖÓ£¬¾ÍOKÁË¡£

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


Ò»¸öARM³ÌÐò°üº¬3²¿·Ö£ºRO£¬RWºÍZI¡£ROÊÇ³ÌÐòÖÐµÄÖ¸ÁîºÍ³£Á¿£»RWÊÇ³ÌÐòÖÐµÄÒÑ³õÊ¼»¯±äÁ¿;ZIÊÇ³ÌÐòÖÐµÄÎ´³õÊ¼»¯µÄ±äÁ¿.
ÓÉÒÔÉÏ3µãËµÃ÷¿ÉÒÔÀí½âÎª£ºRO¾ÍÊÇreadonly£¬RW¾ÍÊÇread/write£¬ZI¾ÍÊÇzero

bss¶Î£º
BSS¶Î£¨bsssegment£©Í¨³£ÊÇÖ¸ÓÃÀ´´æ·Å³ÌÐòÖÐÎ´³õÊ¼»¯µÄÈ«¾Ö±äÁ¿µÄÒ»¿éÄÚ´æÇøÓò¡£
BSSÊÇÓ¢ÎÄBlockStarted by SymbolµÄ¼ò³Æ¡£BSS¶ÎÊôÓÚ¾²Ì¬ÄÚ´æ·ÖÅä¡£

data¶Î£º
Êý¾Ý¶Î£¨datasegment£©Í¨³£ÊÇÖ¸ÓÃÀ´´æ·Å³ÌÐòÖÐÒÑ³õÊ¼»¯µÄÈ«¾Ö±äÁ¿µÄÒ»¿éÄÚ´æÇøÓò¡£Êý¾Ý¶ÎÊôÓÚ¾²Ì¬ÄÚ´æ·ÖÅä¡£

text¶Î£º
´úÂë¶Î£¨codesegment/textsegment£©Í¨³£ÊÇÖ¸ÓÃÀ´´æ·Å³ÌÐòÖ´ÐÐ´úÂëµÄÒ»¿éÄÚ´æÇøÓò¡£
Õâ²¿·ÖÇøÓòµÄ´óÐ¡ÔÚ³ÌÐòÔËÐÐÇ°¾ÍÒÑ¾­È·¶¨£¬²¢ÇÒÄÚ´æÇøÓòÍ¨³£ÊôÓÚÖ»¶Á,Ä³Ð©¼Ü¹¹Ò²ÔÊÐí´úÂë¶ÎÎª¿ÉÐ´£¬¼´ÔÊÐíÐÞ¸Ä³ÌÐò¡£
ÔÚ´úÂë¶ÎÖÐ£¬Ò²ÓÐ¿ÉÄÜ°üº¬Ò»Ð©Ö»¶ÁµÄ³£Êý±äÁ¿£¬ÀýÈç×Ö·û´®³£Á¿µÈ¡£

rodata¶Î£º
´æ·ÅCÖÐµÄ×Ö·û´®ºÍ#define¶¨ÒåµÄ³£Á¿

heap¶Ñ£º
¶ÑÊÇÓÃÓÚ´æ·Å½ø³ÌÔËÐÐÖÐ±»¶¯Ì¬·ÖÅäµÄÄÚ´æ¶Î£¬ËüµÄ´óÐ¡²¢²»¹Ì¶¨£¬¿É¶¯Ì¬À©ÕÅ»òËõ¼õ¡£
µ±½ø³Ìµ÷ÓÃmallocµÈº¯Êý·ÖÅäÄÚ´æÊ±£¬ÐÂ·ÖÅäµÄÄÚ´æ¾Í±»¶¯Ì¬Ìí¼Óµ½¶ÑÉÏ£¨¶Ñ±»À©ÕÅ£©£»
µ±ÀûÓÃfreeµÈº¯ÊýÊÍ·ÅÄÚ´æÊ±£¬±»ÊÍ·ÅµÄÄÚ´æ´Ó¶ÑÖÐ±»ÌÞ³ý£¨¶Ñ±»Ëõ¼õ£©

stackÕ»£º
ÊÇÓÃ»§´æ·Å³ÌÐòÁÙÊ±´´½¨µÄ¾Ö²¿±äÁ¿£¬Ò²¾ÍÊÇËµÎÒÃÇº¯ÊýÀ¨»¡¡°{}¡±ÖÐ¶¨ÒåµÄ±äÁ¿
£¨µ«²»°üÀ¨staticÉùÃ÷µÄ±äÁ¿£¬staticÒâÎ¶×ÅÔÚÊý¾Ý¶ÎÖÐ´æ·Å±äÁ¿£©¡£
³ý´ËÒÔÍâ£¬ÔÚº¯Êý±»µ÷ÓÃÊ±£¬Æä²ÎÊýÒ²»á±»Ñ¹Èë·¢Æðµ÷ÓÃµÄ½ø³ÌÕ»ÖÐ£¬²¢ÇÒ´ýµ½µ÷ÓÃ½áÊøºó£¬º¯ÊýµÄ·µ»ØÖµÒ²»á±»´æ·Å»ØÕ»ÖÐ¡£
ÓÉÓÚÕ»µÄÏÈ½øÏÈ³öÌØµã£¬ËùÒÔÕ»ÌØ±ð·½±ãÓÃÀ´±£´æ/»Ö¸´µ÷ÓÃÏÖ³¡¡£
´ÓÕâ¸öÒâÒåÉÏ½²£¬ÎÒÃÇ¿ÉÒÔ°Ñ¶ÑÕ»¿´³ÉÒ»¸ö¼Ä´æ¡¢½»»»ÁÙÊ±Êý¾ÝµÄÄÚ´æÇø¡£


Ã¿¸öÓÃ»§µÄÈÎÎñ¶¼±ØÐë·ûºÏÊÂ¼þÇý¶¯µÄ±à³ÌÄ£ÐÍ£¬¼´uC/OS-IIµÄÓ¦ÓÃ³ÌÐò¶¼±ØÐëÊÇ¡°ÊÂ¼þÇý¶¯µÄ±à³ÌÄ£ÐÍ¡±¡£
Ò»¸öÈÎÎñÊ×ÏÈµÈ´ýÒ»¸öÊÂ¼þµÄ·¢Éú£¬ÊÂ¼þ¿ÉÒÔÊÇÏµÍ³ÖÐ¶Ï·¢³öµÄ£¬Ò²¿ÉÒÔÊÇÆäËüÈÎÎñ·¢³öµÄ£¬ÓÖ¿ÉÒÔÊÇÈÎÎñ×ÔÉíµÈ´ýµÄÊ±¼äÆ¬¡£
µ±Ò»¸öÊÂ¼þ·¢ÉúÁË£¬ÈÎÎñÔÙ×÷ÏàÓ¦´¦Àí£¬´¦Àí½áÊøºóÓÖ¿ªÊ¼µÈ´ýÏÂÒ»¸öÊÂ¼þµÄ·¢Éú¡£
Èç´ËÖÜ¶ø¸´Ê¼µÄÈÎÎñ´¦ÀíÄ£ÐÍ¾ÍÊÇ¡°ÊÂ¼þÇý¶¯µÄ±à³ÌÄ£ÐÍ¡±¡£ÊÂ¼þÇý¶¯Ä£ÐÍÒ²º­¸ÇÁËÖÐ¶ÏÇý¶¯Ä£ÐÍ£¬
uC/OS-IIÊÂ¼þ¹é¸ù½áµ×À´×ÔÈý¸ö·½Ãæ£º
¡¡¡¡(1)ÖÐ¶Ï·þÎñº¯Êý·¢ËÍµÄÊÂ¼þ
¡¡¡¡(2)ÏµÍ³ÑÓÊ±Ê±¼äµ½ËùÒýÆðµÄ
¡¡¡¡(3)ÆäËüÈÎÎñ·¢ËÍµÄÊÂ¼þ¡£
ÆäÖÐ¡°ÖÐ¶Ï·þÎñº¯Êý·¢ËÍµÄÊÂ¼þ¡±¾ÍÊÇÖ¸Ã¿µ±ÓÐÓ²¼þÖÐ¶Ï·¢Éú£¬ÄÇÃ´ÖÐ¶Ï·þÎñ³ÌÐò¾Í»áÒÔÊÂ¼þµÄÐÎÊ½¸æËßÈÎÎñ£¬
¶øµÈ´ý¸ÃÊÂ¼þµÄ×î¸ßÓÅÏÈ¼¶ÈÎÎñ¾Í»áÂíÉÏµÃÒÔÔËÐÐ£»¡°ÏµÍ³ÑÓÊ±Ê±¼äµ½ËùÒýÆðµÄ¡±ÊÂ¼þÆäÊµÒ²ÊÇÓ²¼þÖÐ¶Ïµ¼ÖÂµÄ£¬
ÄÇ¾ÍÊÇÏµÍ³¶¨Ê±Æ÷ÖÐ¶Ï¡£¶ø¡°ÆäËüÈÎÎñ·¢ËÍµÄÊÂ¼þ¡±ÔòÊÇÓÉÈÎÎñ´úÂë×ÔÉí¾ö¶¨µÄ£¬ÕâÊÇÍêÈ«µÄ¡°ÈíÊÂ¼þ¡±¡£²»¹Ü¡°ÈíÊÂ¼þ¡±»¹ÊÇ¡°Ó²ÊÂ¼þ¡±£¬
·´ÕýÒýÆðuC/OS-IIÈÎÎñÇÐ»»µÄÔ­Òò¾ÍÊÇ¡°ÊÂ¼þ¡±£¬ËùÒÔÓÃ»§±àÐ´Ó¦ÓÃ´úÂëµÄÊ±ºòÒ»¶¨ÒªÌåÏÖ³ö¡°ÊÂ¼þÇý¶¯µÄ±à³ÌÄ£ÐÍ¡±¡£
	exti_imr
		
ROÊÇ³ÌÐòÖÐµÄÖ¸ÁîºÍ³£Á¿
RWÊÇ³ÌÐòÖÐµÄÒÑ³õÊ¼»¯±äÁ¿
ZIÊÇ³ÌÐòÖÐµÄÎ´³õÊ¼»¯µÄ±äÁ¿
ÓÉÒÔÉÏ3µãËµÃ÷¿ÉÒÔÀí½âÎª£º
RO¾ÍÊÇreadonly£¬
RW¾ÍÊÇread/write£¬
ZI¾ÍÊÇzero 
					

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















					// ÎÄ¼þÏµÍ³Ïà¹ØµÄ±äÁ¿			
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
			
					OS_EVENT 	*Mutex_USART1; // ¶¨ÒåUSART1»¥³âÐÍÊÂ¼þ	
					OS_EVENT 	*Mutex_USART2; // ¶¨ÒåUSART2»¥³âÐÍÊÂ¼þ
					OS_EVENT 	*Mutex_FATFS;  // ¶¨ÒåFATFS»¥³âÐÍÊÂ¼þ		
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


static  	OS_STK 		App_TaskStartStk[APP_TASK_START_STK_SIZE];  // TaskStart ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask1Stk[APP_TASK1_STK_SIZE];//  ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask2Stk[APP_TASK2_STK_SIZE ]; //AppTaskUsart2ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask3Stk[APP_TASK3_STK_SIZE ]; //AppTaskUsart3ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask4Stk[APP_TASK4_STK_SIZE ]; //AppTaskUsart4ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask5Stk[APP_TASK5_STK_SIZE ]; //AppTaskUsart5ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask6Stk[APP_TASK6_STK_SIZE ]; //AppTaskUsart6ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask7Stk[APP_TASK7_STK_SIZE ]; //AppTaskUsart7ÈÎÎñ¶ÑÕ» 
static  	OS_STK 		AppTask8Stk[APP_TASK8_STK_SIZE ]; //AppTaskUsart7ÈÎÎñ¶ÑÕ» 




static  	void  		App_TaskStart(void* p_arg);          // ÉùÃ÷ TaskStart º¯Êý
static  	void  		AppTask1(void* p_arg);      // ÉùÃ÷ TaskPrintf º¯Êý
static  	void 		  AppTask2(void* p_arg);        // ÉùÃ÷ ²âÁ¿CPUÆµÂÊµÄº¯Êý
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









static		void 		  LED1234_ON_OFF(CPU_INT08U Num);             // ÉùÃ÷Á÷Ë®µÆº¯Êý
extern		BOOLEAN		Vs1003bPowOnFlag;
extern		INT8U 		USART2_RX_FIFO[USART2_RX_CNT];  		        // ¶¨Òå»·ÐÎÊý¾Ý
extern		void 		  DelayMs(vu32 m);
extern		void 		  DelayUs(vu32 m);	


extern    void DemoFatFS(uint8_t *cmd);
extern		INT8U 	USART1_RX_FIFO[USART1_RX_CNT];  			// ¶¨Òå»·ÐÎÊý¾Ý
extern		INT8U 	*pPut_USART1_RX_FIFO ; 	// ¶¨Òå»·ÐÎÊý×é·ÅÊýÖ¸Õë
extern		INT8U 	*pGet_USART1_RX_FIFO ; 	// ¶¨Òå»·ÐÎÊý×éÈ¡ÊýÖ¸Õë



void MainSwapValue(INT16U *p1,INT16U *p2);//Ö±½Ó½»»»ÁËµØÖ·ÀïÃæµÄÄÚÈÝ£¬Ò²¾ÍÊÇÖµ£¡£¡
void MainSwapValueErr(volatile INT16U *p1,volatile INT16U *p2);//Ö±½Ó½»»»ÁËµØÖ·ÀïÃæµÄÄÚÈÝ£¬Ò²¾ÍÊÇÖµ£¡£¡
void MainSwapAddr(INT16U **p1,INT16U **p2);//Òª½»»»ÄÚÈÝ£¬¼ä½ÓÓÃ½»»»µØÖ·À´ÊµÏÖ¡£
void  BspNand_Init(void);
void LedBsZm_Init(void);
void Mp3Drive_Init(void);

void LedPortSpecialInit(void);
void MainProcessTimeAdd(config data,INT8U order);
void MainProcessTimeSub(config data,INT8U order);


/*
*********************************************************************************************************
                                                main()
												RE:__use_two_region_memoryÓëmacro-libÊ²Ã´¹ØÏµ£¿
_use_two_region_memoryÓÃÓÚÖ¸¶¨´æ´¢Æ÷Ä£Ê½ÎªË«¶ÎÄ£Ê½£¬¼´Ò»²¿·Ö´¢´æÇøÓÃÓÚÕ»¿Õ¼ä£¬ÆäËûµÄ´æ´¢ÇøÓÃÓÚ¶Ñ¿Õ¼ä£¬¶ÑÇø¿Õ¼ä¿ÉÒÔÎª0£¬
µ«ÊÇ£¬ÕâÑù¾Í²»ÄÜµ÷ÓÃmalloc()ÄÚ´æ·ÖÅäº¯Êý£»¶ÑÇø¿Õ¼äÒ²¿ÉÒÔÓÉ´æ´¢Æ÷·ÖÅä£¬Ò²¿ÉÒÔ´ÓÖ´ÐÐ»·¾³ÖÐ¼Ì³Ð¡£
*********************************************************************************************************
*/


//ÔÚ2015Äê11ÔÂ30ÈÕÓÃÒ»¸ö¹âñî£¬Ò»¸ö200Rµç×è£¬Ò»¸ö10kÉÏÀ­µç×è½â¾öÁË5·üµ¥Æ¬»úÄ¸ÖÓºÍ3.3·üarmµ¥Æ¬»úÖ®¼äµÄrs485Í¨Ñ¶µÄÎÊÌâ£¡
//¸Ã°æ±¾µÄÈí¼þÔÚusart2ÖÐ½ÓÊÕÒ»¸ö×Ö½Úºó±ã½øÈëÈÎÎñ3ÖÐ£¬ÔÚÈÎÎñÖÐ´¦Àí±¨Ê±£¬ËäÈ»¿ÉÒÔ²»Ì«±£ÏÕ£¬¿ÖÅÂÂ©±¨£¡
//ÒòÎªÖ÷°å5·üÍ¨Ñ¶°åºÍarm°åÍ¨Ñ¶Éæ¼°µ½µÄ¹©µçµçÔ´ÎÊÌâ£¬RS485Í¨Ñ¶²»¿É¿¿£¬ÎÒÔÚ2015Äê12ÔÂ2ÈÕ½«
//ARM°åÉÏµÄÍ¨Ñ¶Ð¾Æ¬75LBC184µÄµÚÁù½Å£¨A£©Ìí¼ÓÒ»¸ö10KµÄÉÏÀ­µç×è£¬µÚÆß½Å£¨B£©Ìí¼ÓÒ»¸ö10KµÄÏÂÀ­µç×èºó



//½â¾öÁËÁ½¿é°å¿¨Í¨Ñ¶²»¿É¿¿µÄÎÊÌâ£¬½â¾öÁËARM°å²åµ½Á¬½Ó°åÉÏºóÓÃ·ÂÕæÆ÷·ÂÕæ²»ÁËµÄÎÊÌâ¡££¡£¡
//ÎÒÊÔÑéÁËvs1003Ð¾Æ¬£¬·¢ÏÖÎÂ¶È±È½ÏÌÌ£¬Ìí¼Ó±¨Ê±½áÊøºó£¬ÎÄ¼þ¹Ø±Õ£¬ËûÒ²¹Ø±Õ£¡ÔÚÃ¿¸öÐ¡Ê±58·ÖµÄÊ±ºò¸´Î»vs1003×¼±¸²¥·Åmp3ÎÄ¼þ
//²¥·ÅÍê±Ïºó¸ÃÐ¾Æ¬´¦ÓÚµôµç×´Ì¬£¡
//½«¸Ã³ÌÐò×÷Îª×îÖÕ³ÉÆ·³ÌÐò¸øÁõÁË£¡£¡

/*
µÚÒ»²¿·ÖÊµÏÖË³Ðò±íµÄ²Ù×÷
ÒÑÖªÒ»¸öË³Ðò±í£¬ÆäÖÐµÄÔªËØµÝÔöÓÐÐòÅÅÁÐ£¬Éè¼ÆÒ»¸öËã·¨£¬²åÈëÒ»¸öÔªËØx£¨xÎªintÐÍ£©ºó±£³Ö¸ÃË³Ðò±íÈÔÈ»µÝÔöÓÐÐòÅÅÁÐ£¨¼ÙÉè×ÜÄÜ³É¹¦£©
ÊµÏÖ·½·¨£º
1£¬ÕÒµ½±Èx´óµÄµÚÒ»¸öÔªËØµÄÎ»ÖÃ£¬º¯Êý·µ»Ø¸ÃÎ»ÖÃ
2.
*/


PACK_STRUCT_BEGIN
typedef struct
{
	INT8U data[maxSize];
	INT8U length;//ÒÅÁôÒ»¸öÎÊÌâ£¬ÎªÊ²Ã´¸Ã±äÁ¿µÃÖµ±äÎªÁË0!!
}Sqlist;       //¿¼²ìÁËË³Ðò±íµÄ²åÈë£¬É¾³ýµÈ
PACK_STRUCT_END
Sqlist *q;
Sqlist *p;
 

//µ¥Á´±íµÄ²Ù×÷
//head1ºÍhead2ÊÇÁ½¸öµÝÔöµÄµ¥Á´±í£¬Éè¼ÆÒ»¸öËã·¨£¬½«head1ºÍhead2¹é²¢µ½Ò»¸öÁ´±íhead3ÖÐ
//Ê¹×Åhead3µÝÔöÓÐÐò£¬
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
//ÏÂÊö´úÂëÑÝÊ¾ÁËÈçºÎ´´½¨BST¶þ²æÊ÷
typedef struct Node
{
	struct Node *left;
	struct Node *right;
	size_t size;  //Êý¾ÝµÄ¿Õ¼ä´óÐ¡
	INT8U  data[];//Êý¾Ý±¾Éí
}Node_t;
//±ØÐëÌá¹©Á½¸ö¸¨ÖúµÄº¯Êý£¬µÚÒ»¸öÓÃÀ´µÃµ½¡°¶ÔÓ¦ÓÚÊý¾Ý¡±µÄ¼üÖµ£»µÚ¶þ¸öÓÃÀ´±È½ÏÁ½¸ö¼üÖµ
typedef const void *GetKeyFunc_t (const void *dData);//µÚÒ»¸öº¯Êý¾ßÓÐÈçÏÂÔ­ÐÍ
//µÚ¶þ¸öº¯ÊýÀàËÆÓÚ±ê×¼º¯Êýbsearch£¨£©ËùÊ¹ÓÃµÄ¡°±È½Ïº¯Êý¡±
typedef INT16U CmpFunc_t(const void *pKey1,const void *pKey2);
//µ÷ÓÃ±È½Ïº¯ÊýÊ±Ëù´«µÝµÄ×Ô±äÁ¿£¬ÊÇÖ¸ÏòÁ½¸ö¡°¼Æ»®±È½Ï¡±µÄ¼üÖµµÃÖ¸Õë¡£´Ëº¯ÊýµÄ·µ»ØÖµÐ¡ÓÚ0£¬±íÊ¾µÚÒ»¸ö¼üÖµÐ¡ÓÚµÚ¶þ¸ö¼üÖµ£»
//µÈÓÚ0£¬±íÊ¾Á½¸ö¼üÖµÏàµÈ£»´óÓÚ0£¬±íÊ¾µÚÒ»¸ö¼üÖµ´óÓÚµÚ¶þ¸ö¼üÖµ£»
//½ÓÏÂÀ´£¬ÎÒÃÇ¶¨ÒåÒ»¸ö½á¹¹ÀàÐÍ£¬ÓÃÀ´´ú±íÒ»¸öÊ÷£¬´Ë»ú¹¹ÓÐÈý¸ö³ÉÔ±£º
//Ö¸ÏòÊ÷¸ùµÄÖ¸Õë
//Ö¸Ïò¼ÆËã¼üÖµµÃÖ¸Õë£¨ÀàÐÍÎªGetKeyFunc_t)
//Ö¸Ïò±È½Ïº¯ÊýµÄÖ¸Õë£¨ÀàÐÍÎªCmpFunc_t)

typedef struct {
	struct Node *pRoot;  //Ö¸ÏòÊ÷¸ùµÄÖ¸Õë
	CmpFunc_t *cmp;      //±È½ÏÁ½¸ö¼üÖµ
	GetKeyFunc_t *getKey;//½«ÊýÖµ±äÎª¼üÖµ
}BST_t;
*/

typedef struct BSTNode
{
	INT32U data;
	struct BSTNode *left;
	struct BSTNode *right;
}BSTNode;

struct BSTNode *createnode(INT32U data)//½«½ÚµãµÄÊý¾ÝÏî¶Ô±Èºó²åÈë¶þ²æÊ÷ÖÐ
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


//https://blog.csdn.net/qq_41028985/article/details/82859199---²Î¿¼ÍøÖ·£¬Éæ¼°µ½µ¥Á´±íµÄÍ·²å·¨ºÍÎ²²å·¨£¡£¡
//http://blog.sina.com.cn/s/blog_c689bd6c0102wvdd.html---C99µÄÒ»Ð©ÌØÕ÷
typedef struct myNode {
	INT8U data;                // ´æ´¢Á´±íÊý¾Ý
	struct myNode *next;     		//  ´æ´¢½áµãµÄµØÖ·
}myLNode,*Linklist;

//ÔÚ½øÈë´´½¨Á´±íÖ®Ç°£¬ÎÒÃÇÏÈÐ´ºÃÖ÷º¯ÊýµÄÓÃÀ´Êä³öµÄÊä³öº¯Êý¡£
void Illustrate(Linklist head) {
	Linklist tem = head;              //  ½«Í·Ö¸ÕëµÄµØÖ·¸³¸øÁÙÊ±µÄÖ¸Õë
	while (tem->next != NULL) {       //  Ö¸Ïò×îºóÒ»¸ö½áµãµÄÖ¸ÕëÓòÊ±»áÍ£Ö¹
		tem = tem->next;                //  ½áµã²»¶ÏÏòºóÒÆ¶¯
		//printf("%d\n", tem->data);
		//USART1_Printf(&(hex2ascii(tem->next)));
		//USART1_Printf(&tem"->data);
		printf("\r\n %d",tem->data);
		
	}
}

//Í·²å·¨´úÂë£º
Linklist HeadInsert_List(Linklist head) {
	INT8U i;//×¢Òâ£º±äÁ¿ÉùÃ÷²»ÔÊÐí³öÏÖÔÚÓï¾äÖ®ºó£¬·ñÔòÌáÊ¾³öÏÖ error£¡
	myLNode *mynode = NULL;                  //  ¶¨ÒåÐÂ½áµã
	
	INT16U count = 16;                        //  ´´½¨½áµãµÄ¸öÊý
	head = (Linklist)malloc(sizeof(myLNode));//  ÎªÍ·Ö¸Õë¿ª±ÙÄÚ´æ¿Õ¼ä
	head->next = NULL; 
			             
	mynode = head->next;              	       //  ½«×îºóÒ»¸ö½áµãµÄÖ¸ÕëÓòÓÀÔ¶±£³ÖÎªNULL
	printf("\r\n ÒÔÏÂÏÔÊ¾Í·²å·¨²åÈëµÄË³ÐòÎª: ");	
	for ( i = 0; i < count; i++) {
		mynode = (Linklist)malloc(sizeof(LNode));//  ÎªÐÂ½áµã¿ª±ÙÄÚ´æ¿Õ¼ä
		mynode->data = i;                        //  ÎªÐÂ½áµãµÄÊý¾ÝÓò¸³Öµ
		mynode->next = head->next;               //  ½«Í·Ö¸ÕëËùÖ¸ÏòµÄÏÂÒ»¸ö½áµãµÄµØÖ·£¬¸³¸øÐÂ´´½¨½áµãµÄnext 
		head->next = mynode;                     //  ½«ÐÂ´´½¨µÄ½áµãµÄµØÖ·¸³¸øÍ·Ö¸ÕëµÄÏÂÒ»¸ö½áµã
	}
	return head;//±ØÐëÓÐ·µ»ØÖµ£¬ÎªÁË´Óµ¥Á´±íÍ·²¿Êä³öÊý¾Ý£»added by sjw
}
//Í·²å·¨´´½¨Á´±íµÄ¸ù±¾ÔÚÓÚÉî¿ÌÀí½â×îºóÁ½ÌõÓï¾ä
//mynode->next = head->next;    //  ½«Í·Ö¸ÕëËùÖ¸ÏòµÄÏÂÒ»¸ö½áµãµÄµØÖ·£¬¸³¸øÐÂ´´½¨½áµãµÄnext 
//head->next = mynode;          //  ½«ÐÂ´´½¨µÄ½áµãµÄµØÖ·¸³¸øÍ·Ö¸ÕëµÄÏÂÒ»¸ö½áµã


//Î²²å·¨´úÂë£º
Linklist TailInsert_List(Linklist head) {
  INT16U  count = 16 ;                 //  ½áµã¸öÊý
	INT16U  i;
	Linklist node = NULL;           //  ¶¨Òå½áµã
	Linklist tailer = NULL;            //  ¶¨ÒåÎ²½áµã
	
	head = (Linklist)malloc(sizeof(LNode));          //  ÎªÍ·Ö¸Õë¿ª±ÙÄÚ´æ¿Õ¼ä
	head->next = NULL;              //  ³õÊ¼»¯Í·½áµãÖ¸ÏòµÄÏÂÒ»¸öµØÖ·Îª NULL
	tailer = head;                     //  Î´´´½¨ÆäÓà½áµãÖ®Ç°£¬Ö»ÓÐÒ»¸öÍ·½áµã
	
	printf("\r\n ÒÔÏÂÏÔÊ¾Î²²å·¨²åÈëµÄË³ÐòÎª: ");
	for (i = 0; i < count; i++) {
		node = (Linklist)malloc(sizeof(LNode));          //  ÎªÐÂ½áµã¿ª±ÙÐÂÄÚ´æ
		node->data = i;                                  //  ÐÂ½áµãµÄÊý¾ÝÓò¸³Öµ
		tailer->next = node;                      		
		tailer = node;
	}
	tailer->next = NULL;
	return head;//±ØÐëÓÐ·µ»ØÖµ£¬ÎªÁË´Óµ¥Á´±íÍ·²¿Êä³öÊý¾Ý£»added by sjw
}
//Î²²å·¨Éî¿ÌÀí½âÈçÏÂÁ½¾ä£º
//end->next = node;                      		
//end = node;



const 	uint8_t   *pmp3tabel[26]={
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3", 
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3",
		
	  "MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3", 
		"MP3_0066.mp3",   "MP3_0066.mp3",   "MP3_0066.mp3",  "MP3_0066.mp3",  "MP3_0066.mp3",   "MP3_0066.mp3",
		
		
	};
	

Linklist phead = NULL;            //  Á´±íµÄÍ·Ö¸Õë
INT8U MainFindElem(Sqlist L,INT8U x);//±¾º¯Êý·µ»ØµÚÒ»¸ö±ÈxÖµ´óµÄÔªËØµÄÎ»ÖÃ
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


//º¯ÊýÖ¸ÕëÊý×é¶¨Òå¼°¸½³õÖµ£¡
void (*KeyProcTab[])()={NoKeyProm,KeyProm1,KeyProm2,KeyProm3,KeyProm4,KeyProm5,KeyProm6};
float *find(float(*pionter)[4],int n);//º¯ÊýÉùÃ÷ 

/*
//float(*pionter)[4]   ±ÈÈç  int (*p)[10]; p¼´ÎªÖ¸ÏòÊý×éµÄÖ¸Õë£¬ÓÖ³ÆÊý×éÖ¸Õë¡£
int Func(int x);        //ÉùÃ÷Ò»¸öº¯Êý
int (*p) (int x);       //¶¨ÒåÒ»¸öº¯ÊýÖ¸Õë
p = Func;               //½«Funcº¯ÊýµÄÊ×µØÖ·¸³¸øÖ¸Õë±äÁ¿p

1.¶¨Òåº¯ÊýÖ¸ÕëÀàÐÍ£º
typedef int (*fun_ptr)(int,int);    
2.ÉùÃ÷±äÁ¿£¬¸³Öµ£º                                   typedef
fun_ptr max_func=max;
Ò²¾ÍÊÇËµ£¬¸³¸øº¯ÊýÖ¸ÕëµÄº¯ÊýÓ¦¸ÃºÍº¯ÊýÖ¸ÕëËùÖ¸µÄº¯ÊýÔ­ÐÍÊÇÒ»ÖÂµÄ


STM32f103VE¼Ä´æÆ÷--¶¨ÒåÆª
https://www.it610.com/article/1294459351842496512.htm
*/


extern uint16_t  TestCount;
extern uint8_t  TestCountHL[2];
extern  uint8_t do_erase_nandflash(uint32_t _ulBlockNo);



//ECCËã·¨µÄÊµÏÖ
//ÉîÈëÇ³³öNandFlashÀïµÄECCÐ£ÑéËã·¨Ô­ÀíÓëÊµÏÖ(1)
//https://blog.csdn.net/qwe5959798/article/details/116481300   ´ËÎÄÕÂ·Ç³£ºÃ£¬Àí½âECC
//ÍøÉÏ¹ØÓÚNandFlashµÄECCÐ£ÑéÎÄÕÂºÜ¶à£¬µ«Ã»ÓÐÒ»¸öÉîµÃÎÒÐÄ¡£
//ÉîÈëÇ³³öNandFlashÀïµÄECCÐ£ÑéËã·¨Ô­ÀíÓëÊµÏÖ(2)
//https://blog.csdn.net/qwe5959798/article/details/121931611   





struct FAT32_DBR
{
unsigned char BS_jmpBoot[3];     	//Ìø×ªÖ¸Áîoffset: 0
unsigned char BS_OEMName[8]; 			// offset: 3
unsigned char BPB_BytesPerSec[2];	//Ã¿ÉÈÇø×Ö½ÚÊýoffset:11
unsigned char BPB_SecPerClus[1]; 	//Ã¿´ØÉÈÇøÊýoffset:13
unsigned char BPB_RsvdSecCnt[2]; 	//±£ÁôÉÈÇøÊýÄ¿offset:14
unsigned char BPB_NumFATs[1]; 		//´Ë¾íÖÐFAT ±íÊýoffset:16
unsigned char BPB_RootEntCnt[2]; 	//FAT32 Îª0 offset:17
unsigned char BPB_TotSec16[2]; 		//FAT32 Îª0 offset:19
unsigned char BPB_Media[1]; 			//´æ´¢½éÖÊoffset:21
unsigned char BPB_FATSz16[2]; 		//FAT32 Îª0 offset:22
unsigned char BPB_SecPerTrk[2]; 	//´ÅµÀÉÈÇøÊýoffset:24
unsigned char BPB_NumHeads[2]; 		//´ÅÍ·Êýoffset:26
unsigned char BPB_HiddSec[4]; 		//FAT ÇøÇ°ÒþÉÈÇøÊýoffset:28
	
	
unsigned char BPB_TotSec32[4]; 		//¸Ã¾í×ÜÉÈÇøÊýoffset:32
unsigned char BPB_FATSz32[4]; 		//Ò»¸öFAT ±íÉÈÇøÊýoffset:36
unsigned char BPB_ExtFlags[2]; 		//FAT32 ÌØÓÐoffset:40
unsigned char BPB_FSVer[2]; 			//FAT32 ÌØÓÐoffset:42
unsigned char BPB_RootClus[4]; 		//¸ùÄ¿Â¼´ØºÅoffset:44
unsigned char FSInfo[2]; 					//±£ÁôÉÈÇøFSINFO ÉÈÇøÊýoffset:48
unsigned char BPB_BkBootSec[2]; 	//Í¨³£Îª6 offset:50
unsigned char BPB_Reserved[12]; 	//À©Õ¹ÓÃoffset:52
unsigned char BS_DrvNum[1]; 			// offset:64
unsigned char BS_Reserved1[1]; 		// offset:65
unsigned char BS_BootSig[1]; 			// offset:66
unsigned char BS_VolID[4]; 				// offset:67
unsigned char BS_FilSysType[11]; 	// offset:71
unsigned char BS_FilSysType1[8]; 	//"FAT32 " offset:82
};


struct FAT32_Init_Arg
{
unsigned char BPB_Sector_No; //BPB ËùÔÚÉÈÇøºÅ
unsigned long Total_Size; //´ÅÅÌµÄ×ÜÈÝÁ¿
unsigned long FirstDirClust; //¸ùÄ¿Â¼µÄ¿ªÊ¼´Ø
unsigned long FirstDataSector; //ÎÄ¼þÊý¾Ý¿ªÊ¼ÉÈÇøºÅ
unsigned int BytesPerSector; //Ã¿¸öÉÈÇøµÄ×Ö½ÚÊý
unsigned int FATsectors; //FAT ±íËùÕ¼ÉÈÇøÊý
unsigned int SectorsPerClust; //Ã¿´ØµÄÉÈÇøÊý
unsigned long FirstFATSector; //µÚÒ»¸öFAT ±íËùÔÚÉÈÇø
unsigned long FirstDirSector; //µÚÒ»¸öÄ¿Â¼ËùÔÚÉÈÇø
unsigned long RootDirSectors; //¸ùÄ¿Â¼ËùÕ¼ÉÈÇøÊý
unsigned long RootDirCount; //¸ùÄ¿Â¼ÏÂµÄÄ¿Â¼ÓëÎÄ¼þÊý
};

/*
void FAT32_Init(struct FAT32_Init_Arg *arg)
{
		struct FAT32_BPB *bpb=(struct FAT32_BPB *)(FAT32_Buffer);//½«Êý¾Ý»º³åÇøÖ¸Õë×ªÎªstruct FAT32_BPB ÐÍÖ¸Õë
		arg->BPB_Sector_No =FAT32_FindBPB();//FAT32_FindBPB()¿ÉÒÔ·µ»ØBPB ËùÔÚµÄÉÈÇøºÅ
		arg->Total_Size =FAT32_Get_Total_Size();//FAT32_Get_Total_Size()¿ÉÒÔ·µ»Ø´ÅÅÌµÄ×ÜÈÝÁ¿£¬µ¥Î»ÊÇÕ×
		arg->FATsectors =lb2bb((bpb->BPB_FATSz32) ,4);//×°ÈëFAT ±íÕ¼ÓÃµÄÉÈÇøÊýµ½FATsectors ÖÐ
		arg->FirstDirClust =lb2bb((bpb->BPB_RootClus) ,4);//×°Èë¸ùÄ¿Â¼´ØºÅµ½FirstDirClust ÖÐ
		arg->BytesPerSector =lb2bb((bpb->BPB_BytesPerSec),2);//×°ÈëÃ¿ÉÈÇø×Ö½ÚÊýµ½BytesPerSector ÖÐ
		arg->SectorsPerClust =lb2bb((bpb->BPB_SecPerClus) ,1);//×°ÈëÃ¿´ØÉÈÇøÊýµ½SectorsPerClust ÖÐ
		arg->FirstFATSector=lb2bb((bpb->BPB_RsvdSecCnt) ,2)+arg->BPB_Sector_No;//×°ÈëµÚÒ»¸öFAT ±íÉÈÇøºÅµ½FirstFATSector ÖÐ
		arg->RootDirCount =lb2bb((bpb->BPB_RootEntCnt) ,2);//×°Èë¸ùÄ¿Â¼ÏîÊýµ½RootDirCount ÖÐ
		arg->RootDirSectors =(arg->RootDirCount)*32>>9;//×°Èë¸ùÄ¿Â¼Õ¼ÓÃµÄÉÈÇøÊýµ½RootDirSectors ÖÐ
		arg->FirstDirSector=(arg->FirstFATSector)+(bpb->BPB_NumFATs[0])*(arg->FATsectors);//×°ÈëµÚÒ»¸öÄ¿Â¼ÉÈÇøµ½FirstDirSector ÖÐ
		arg->FirstDataSector =(arg->FirstDirSector)+(arg->RootDirSectors);//×°ÈëµÚÒ»¸öÊý¾ÝÉÈÇøµ½FirstDataSector ÖÐ
}



FATFSÎÄ¼þÒÆÖ²µÄdebugÎÊÌâ£¨·Ç³£ºÃ£©
http://www.360doc.com/content/18/0530/06/6889381_758125759.shtml

*/





 static u8   *(*CopyData[10])(u16 Length);
 u8 *my;

 static u8   *(see)(u16 sjw)
{
	
	u16 temp=sjw;
	return my;
}
//Ã»ÓÐ    Êý×éÖ¸Õëº¯Êý     ÕâÒ»¸ö¸ÅÄî£¬ÒòÎªÖ¸Õë²¹íE¼ÈÖ¸ÏòÊý×éÓÖÖ´ÐÐº¯Êý£¡£¡£¡
//µ«ÊÇÓÐ  º¯ÊýÖ¸ÕëÊý×é     ÕâÒ»¸ö¸ÅÄî£¬ÓÃËüÀ´ÊµÏÖÉ¢×ªÖ¸ÏòÌØ±ð·½±ã£¡£¡
u16 MainTestArray[10][10];
u16 (*pMainTestArray)[10]=MainTestArray;
	
//¸Ã³ÌÐòÄÜÊµÏÖÉÏµçºó¼´¿ªÊ¼²¥·ÅSD¿¨ÄÚµÄÎÄ¼þ¹¦ÄÜ£¡²¥·Å¡°Î÷ÃôËÂ¡±ºó¼´¿ªÊ¼²¥·Å12ÏÂÓïÒôµÄ¹¦ÄÜ£¡£¡
//´Ë³ÌÐò½«Íâ²¿+12·ü½ÓÉÏºó£¬ÉÏµçÄÜ¹»¿ªÊ¼Í¨¹ývs1003ÊµÏÖ·ÅÒô¹¦ÄÜ£¡£¡Èç¹û²»ÄÜ³öÀ´ÉùÒô£¬¸ü»»Ò»¿éºËÐÄ°å¼´¿É£¡
//ÕñÄÏ¶ÔWAVÒôÆµ¸ñÊ½ÉîÈëÆÊÎö(ADPCM±àÂë) ¶ÔVS1003Â¼WAV¼°½âÂëÓÐÓÃ      https://bbs.21ic.com/icview-1604404-1-1.html


//stm32-USART1ÖØÓ³Éä   ²Î¿¼ÍøÖ·£ºhttps://blog.csdn.net/qinrenzhi/article/details/81875348
//STM32F103 FSMCÏê½âÒÔ¼°Çý¶¯LCDµÄÓ¦ÓÃ   ²Î¿¼ÍøÖ·£ºhttps://blog.csdn.net/weixin_30918415/article/details/98433064
//FSMC»úÖÆ       ²Î¿¼ÍøÖ·£ºhttp://blog.sina.com.cn/s/blog_7880d3350101ih1z.html


/*
Ä¿µÄ£º½«K9F1208×÷ÎªÒ»¸öUÅÌ£¬ÊµÏÖÍùÀïÃæcopyÎÄ¼þµÄÄ¿µÄ£¡£¡Ö®ºóÊÕµ½ÍøÂçºËÐÄ°åÖ¸Áîºó£¬°´ÒªÇó²¥·ÅUÅÌÀïÃæµÄÎÄ¼þ£¡£¡
Ñ§Ï°½«FATFSÒÆÖ²µ½NandFlash£¨K9F1208£©ÄÚµÄ¹ý³Ì¼ÇÂ¼
1.https://blog.csdn.net/cwcwj3069/article/details/7882978
uÅÌ  Àí½âÁËDBR £¨dos boot record)ºÍBPB(bois parameter block)
          MBR(main boot record)¼¸¸öÃû´ÊµÄÒâÒå£¬ÓÐÒâË¼
2.NAND_FLASH(K9F1208U0C)Çý¶¯·ÖÎö
https://blog.csdn.net/lshiceman/article/details/37929167

3.STM32 FSMC NAND¿ØÖÆÆ÷ Çý¶¯NAND FLASH ×¢ÒâÊÂÏî
https://blog.csdn.net/qq_15404645/article/details/80911266

4.fatfsÎÄ¼þÏµÍ³Ïê½âÖ®f_mkfsº¯Êý·ÖÎö
https://blog.csdn.net/agony_isolate/article/details/106243899

5.https://blog.csdn.net/qq_44884287/article/details/89517209
nand flash½á¹¹ÒÔ¼°¶ÁÐ´·ÖÎö¡ª¡ªÐ´µÄ±È½Ï¾­µä£¨×ªÔØ£©


6. VBR (Volume Boot Record) or PBR (Private Boot Record), 
FAT ¾íÖÐ×îÖØÒªµÄÊý¾Ý½á¹¹ÊÇ BPB£¨BIOS Parameter Block£¬BIOS ²ÎÊý¿é£©£¬ÆäÖÐ´æ´¢ FAT ¾íµÄÅäÖÃ²ÎÊý¡£ 
BPB Î»ÓÚÒýµ¼ÉÈÇøÖÐ¡£ Òýµ¼ÉÈÇøÍ¨³£³ÆÎª VBR£¨Volume Boot Record£¬¾íÒýµ¼¼ÇÂ¼£©»ò PBR£¨Private Boot Record£¬×¨ÓÃÒýµ¼¼ÇÂ¼£©£¬
µ«ËüÖ»ÊÇ±£ÁôÇøÓòµÄµÚÒ»¸öÉÈÇø£¬¼´¾íµÄµÚÒ»¸öÉÈÇø¡£
  https://dandelioncloud.cn/article/details/1460588983884529666
	´ËÍøÕ¾µÄÄÚÈÝÏêÏ¸½âÊÍÁËÎÄ¼þÏµÍ³µÄÒ»¸öÉÈÇø×Ö½ÚµÄº¬Òå£¬ÌØ±ðÓÐ²Î¿¼¼ÛÖµ£¡added by sjw
	
	
7.ÍøÉÏ·¢ÏÖµÃÒ»ÆªÐ´´ÅÅÌÉÈÇøµÃÎÄÕÂ£¨ÖµµÃÒ»¿´£©
http://blog.chinaunix.net/uid-8613773-id-2018359.html

8.//ÎÒÔÚ2022-7-19ÈÕ½«´Ëºê±äÎª1Ê¹ÄÜ£¡£¡
ÔÚÎÄ¼þffconf.hµÄµÚ164ÐÐÉÏ£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡


9.C++ f_mountº¯Êý´úÂëÊ¾Àý
https://vimsky.com/examples/detail/cpp-ex-----f_mount-function.html

10.FatFsÄ£¿é¹¦ÄÜÅäÖÃÑ¡Ïî 
	https://blog.51cto.com/u_15294654/3112876
	a.¹¦ÄÜÅäÖÃ
	b.ÃüÃû¿Õ¼äºÍ±¾µØ»·¾³ÅäÖÃ
	c.¾í/Çý¶¯Æ÷ÅäÖÃ
	d.ÏµÍ³ÅäÖÃ
	
11.fatfsÍøÕ¾£º
	http://elm-chan.org/fsw/ff/00index_e.html

12.½«FATFSÒÆÖ²STM32RBT6Óöµ½µÄ¹ÒÔØ²»³É¹¦ºÍ·µ»ØÖµÎÊÌâ
http://www.eepw.com.cn/article/201611/322277.htm

Ô­À´ÔÚ¶¨ÒåFATFS *FS;ÊÇÐèÒª·ÖÅäÄÚ´æµÄ£¬¾ÝËµ¿Õ¼ä·ÖÅäÓÐÁ½ÖÖ·½Ê½Ò»¸öÊÇÊý×é£¬ÁíÒ»¸öÊÇ¶¨ÒåÖ¸Õë£¬
¶¨ÒåÖ¸ÕëÊ±ÒªÊ¹ÓÃmalloc·ÖÅäÄÚ´æ»¹ÒªfreeÊÍ·ÅÄÚ´æ£¬¶øÎÒ¶¨ÒåÁËfatfs½á¹¹µÄÖ¸ÕëÃ»ÓÐ·ÖÅäÄÚ´æ£¬
Ôì³É·µ»ØÖµFR_NO_FILESYSTEM,// (13) There is no valid FAT volume £¬ºóÀ´ÎÒ¸Ä³Éfatfs fs;

 
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
	×¢Òâ£»ÔÚÎÄ¼þstm32f10x_fsmc.cÖÐÌáÊ¾³öËÄ¸ö´íÎó£¨´ËÎÄ¼þÒÑ¾­±»¡°»ðÅ£¡±ÏÂÍ¬ÃûÎÄ¼þ´úÌæ£¬¾ÍÊÇÎªÁËÊµÏÖFlashWriteOneSector  FlashReadOneSector£©
	µÚ183ÐÐ±»ÎÒÆÁ±Î
	µÚ205ÐÐ±»ÎÒÆÁ±Î
	µÚ385ÐÐ±»ÎÒÆÁ±Î

	×¢Òâ¶¼½â¾öºÃºó£¬ÐèÒª´ò¿ª´ËÆÁ±Î£¡
	
	
		
2.	https://blog.csdn.net/chengdong1314/article/details/81369601
    STM32 USBµÄÃ¶¾Ù¹ý³Ì¼ò½é   ´ËÎÄ½éÉÜµÄ·Ç³£ºÃ£¡Âú×ãÎÒÒ»²½Ò»²½Ã¶¾ÙÊ±ºò·¢ÉúµÄ¶¯×÷µÄ¹Û²ìÔ¸Íû£¡£¡
	
		
3.  https://blog.csdn.net/dierui2904/article/details/101759783  
	´ËÍøÕ¾µÄÄÚÈÝ·Ç³£²»´í£¬ÓÃËüÀ´×ö²Î¿¼ÎÒÀí½â¿ª·¢USB¿Ï¶¨Ã»ÓÐÎÊÌâ   °´ÕÕÌáÊ¾²Ù×÷£¬¸ñÊ½»¯²»³É¹¦£¬¿ÉÓÃ´ÅÅÌ¿Õ¼äºÍÒÑÓÃ´ÅÅÌ¿Õ¼ä¶¼Îª0¡£
	ÒÔÏÂÕâ¸öÍøÕ¾·Ç³£ºÍÎÒ½øÐÐ¿ª·¢ÏàËÆ£¡·Ç³£¿ÉÒÔ½è¼ø£¡£¡
4.  http://www.javashuo.com/article/p-ybcbwxvw-ky.html


5.FatFsÎÄ¼þÏµÍ³NandflashÇý¶¯º¯ÊýÏê½â
https://www.likecs.com/show-204034824.html

6.¿ÉÅÂµÄÎÊÌâ£ºFATFS f_open() ·µ»Ø¿ÉÅÂµÄ FR_NO_FILESYS
https://bbs.21ic.com/icview-619554-1-1.html

7.STM32 ÎÄ¼þÏµÍ³ fatfs ÒÆÖ²±Ê¼ÇÏê½â   MBRºÍDBRÍ¨¹ý0ÉÈÇøµÄÊý¾Ý½âÊÍÌØ±ðµ½Î»£¡£¡
https://blog.51cto.com/u_15284384/3052087

8.½«ÎÄ¼þµÄµÚ110ÐÐÐÞ¸ÄÎªµÚ113ÐÐÉÏ£¬Ã÷ÏÔµÄ¿´µ½ÊÇFATFS32µÄÀàÐÍÁË£¬²¢ÇÒ·ÂÕæfsµÄÊý¾Ý¶¼¿´×Å¿¿Æ×
	
	*/

//1 SPIµÄ»ù±¾½éÉÜ   https://blog.csdn.net/qq_39792063/article/details/120942630
//´ËÎÄ½éÉÜµÄºÜÐÎÏó£¡
//½«ÎÄ¼þSD_driver.cÓÃÎÄ¼þ¼Ðnand_fatfs010b_noOS_TFÏÂµÄÎÄ¼þ´úÌæ£¨ÏÈÑéÖ¤ºÃÓÃµÄ£©Ö®ºó£¬²»»á³öÏÖstm32f10x_spi.cµÄµÚ170ÐÐÉÏµÄ¾¯¸æÁË£¡
//ÁíÍâÌø×ªµ½   B       HardFaultException  ÊÇÒòÎªºêÖ¸Áî OS_ENTER_CRITICAL();ºÍ OS_EXIT_CRITICAL();µÄÂÒÓÃÔì³ÉµÄ















































































































































































































































































































































































































































































































































































































































































































































































































































































































































/*
24C02,256  ¡Á8(2K bits)- 
24C04,512  ¡Á8(4K bits)- *16byte??????????????????????????
24C08,1024 ¡Á8(8K bits)-
24C16,2048 ¡Á8(16K bits)- 
24C32,4096 ¡Á8(32K bits)- 
24C64,8192 ¡Á8(64K bits)-

Ò³Ð´:8×Ö½ÚÒ³(24C02),16×Ö½ÚÒ³(24C04/08/16),32×Ö½ÚÒ³(24C32/64)¿É°´×Ö½Ú£¬Ëæ»úºÍÐòÁÐ¶Á
¸ß¿É¿¿ÐÔ²ÁÐ´ÊÙÃü:100Íò´Î-Êý¾Ý±£³ÖÊ±¼ä:100Äê



STM32F105¡¢107RBÊ¹ÓÃÍâ²¿¾§Õñ8MÊ±ÅäÖÃÍâÉèÊ±ÖÓÎª72M

https://www.cnblogs.com/tlazy-12138/p/17619353.html




±¸×¢1£º¸ÃÈí¼þµÄºËÐÄÃÜÂëÎª¡°450706¡±£¬Ö»ÓÐÊäÈëÕýÈ·µÄÃÜÂëºó£¬²Å»á³ÉÎª
			 ºÏ·¨ÓÃ»§£¬ÈÎºÎ²Ù×÷¶¼²»ÊÜÏÞÖÆ£¡ (2008/8/28ÉÏÎçÉè¶¨µÄÃÜÂë)
±¸×¢2£º¸ÃÈí¼þ¹²ÓÐ6¸ö¼üÅÌ£¨°üÀ¨¸´Î»¼ü£©·Ö±ðÎª£º
      ¡°×´Ì¬¡±  ¡°Î»Ñ¡¡±  ¡°¼Ó¡±  ¡°¼õ¡±	  KY0 ÓëRL0,RL1,RL2,RL3
			¡°Æô/Í£¡± ¡°Ðîµç³Ø¡±                  KY1 ÓëRL0,RL1		



µ±Ç°µÄÇ¶ÈëÊ½Ó¦ÓÃ³ÌÐò¿ª·¢¹ý³ÌÀï£¬CÓïÑÔÒÑ³ÉÎªÁË¾ø´ó²¿·Ö³¡ºÏµÄ×î¼ÑÑ¡Ôñ¡£Èç´ËÒ»À´mainº¯ÊýËÆºõ³ÉÎªÁËÀíËùµ±È»µÄÆðµã¡ª¡ªÒòÎªC³ÌÐòÍùÍù´Ómainº¯Êý¿ªÊ¼Ö´ÐÐ¡£
µ«Ò»¸ö¾­³£»á±»ºöÂÔµÄÎÊÌâÊÇ£ºÎ¢¿ØÖÆÆ÷£¨µ¥Æ¬»ú£©ÉÏµçºó£¬ÊÇÈçºÎÑ°ÕÒµ½²¢Ö´ÐÐmainº¯ÊýµÄÄØ£¿ºÜÏÔÈ»Î¢¿ØÖÆÆ÷ÎÞ·¨´ÓÓ²¼þÉÏ¶¨Î»mainº¯ÊýµÄÈë¿ÚµØÖ·£¬
ÒòÎªÊ¹ÓÃCÓïÑÔ×÷Îª¿ª·¢ÓïÑÔºó£¬±äÁ¿/º¯ÊýµÄµØÖ·±ãÓÉ±àÒëÆ÷ÔÚ±àÒëÊ±×ÔÐÐ·ÖÅä£¬ÕâÑùÒ»À´mainº¯ÊýµÄÈë¿ÚµØÖ·ÔÚÎ¢¿ØÖÆÆ÷µÄÄÚ²¿´æ´¢¿Õ¼äÖÐ²»ÔÙÊÇ¾ø¶Ô²»±äµÄ¡£
ÏàÐÅ¶ÁÕß¶¼¿ÉÒÔ»Ø´ðÕâ¸öÎÊÌâ£¬´ð°¸Ò²Ðí´óÍ¬Ð¡Òì£¬µ«¿Ï¶¨¶¼ÓÐ¸ö¹Ø¼ü´Ê£¬½Ð¡°Æô¶¯ÎÄ¼þ¡±£¬ÓÃÓ¢ÎÄµ¥´ÊÀ´ÃèÊöÊÇ¡°Bootloader¡±¡£

ÎÞÂÛÐÔÄÜ¸ßÏÂ£¬½á¹¹¼ò·±£¬¼Û¸ñ¹ó¼ú£¬Ã¿Ò»ÖÖÎ¢¿ØÖÆÆ÷£¨´¦ÀíÆ÷£©¶¼±ØÐëÓÐÆô¶¯ÎÄ¼þ£¬
Æô¶¯ÎÄ¼þµÄ×÷ÓÃ±ãÊÇ¸ºÔðÖ´ÐÐÎ¢¿ØÖÆÆ÷´Ó¡°¸´Î»¡±µ½¡°¿ªÊ¼Ö´ÐÐmainº¯Êý¡±ÖÐ¼äÕâ¶ÎÊ±¼ä£¨³ÆÎªÆô¶¯¹ý³Ì£©Ëù±ØÐë½øÐÐµÄ¹¤×÷¡£
×îÎª³£¼ûµÄ51£¬AVR»òMSP430µÈÎ¢¿ØÖÆÆ÷µ±È»Ò²ÓÐ¶ÔÓ¦Æô¶¯ÎÄ¼þ£¬µ«¿ª·¢»·¾³ÍùÍù×Ô¶¯ÍêÕûµØÌá¹©ÁËÕâ¸öÆô¶¯ÎÄ¼þ£¬²»ÐèÒª¿ª·¢ÈËÔ±ÔÙÐÐ¸ÉÔ¤Æô¶¯¹ý³Ì£¬
Ö»ÐèÒª´Ómainº¯Êý¿ªÊ¼½øÐÐÓ¦ÓÃ³ÌÐòµÄÉè¼Æ¼´¿É¡£



UC/OS-IIIÑ§Ï°¡ª¡ª´¥·¢PendSVÖÐ¶Ï
https://www.itxm.cn/post/ajffea1a1.html


ÒÆÖ²ucosiiÓöµ½µÄÎÊÌâ B OSStartHang
https://blog.csdn.net/special00/article/details/73929966
ÆäÊµºÜ¼òµ¥£¬ÒòÎªSTM32±¾ÉíµÄÒì³£ÖÐ¶ÏPendSV_HandlerÌæ´úÁËUCOSµÄÒì³£ÖÐ¶ÏOSPendSV£¬Ê¹Æä²»ÄÜÕý³£Ö´ÐÐ¡£
ÕâÑùÎÒÃÇ¾ÍÐèÒª¸ü¸ÄPendSV_HandlerÎªOSPendSVÒÔÈÃÖÐ¶ÏÕý³£¡£



STM32-¶Ë¿Ú¸´ÓÃºÍÖØÓ³Éä
https://blog.csdn.net/qq_39792063/article/details/120565875
´ËÎÄÕÂ½âÊÍµÄÏàµ±ÏêÏ¸£¬·Ç³£²»´í£¬ÊÇ²Ù×÷STM32f10xµÄÀûÆ÷£¡£¡added by sjw



cl£º»¥ÁªÐÍ²úÆ·£¬    	stm32f105/107ÏµÁÐ
vl£º³¬ÖµÐÍ²úÆ·£¬    	stm32f100ÏµÁÐ
xl£º³¬¸ßÃÜ¶È²úÆ·£¬		stm32f101/103ÏµÁÐ
ld£ºµÍÃÜ¶È²úÆ·£¬				FLASHÐ¡ÓÚ64K
md£ºÖÐµÈÃÜ¶È²úÆ·£¬			FLASH=64 or 128
hd£º¸ßÃÜ¶È²úÆ·£¬				FLASH´óÓÚ128

IO¶Ë¿Ú¸´Î»ºó´¦ÓÚ¸¡¿Õ×´¿ö£¬Ò²±ãÊÇÆäµçÆ½×´¿öÓÉÍâÎ§µçÂ·¾öÒé£¬ÕâºÜÖØÒª£¬¼ÙÈç¹æ»®¹¤ÒµÆ·µÄ»°£¬ÕâÊÇ±ØÐèÒªÈ·ÈÏµÄ£»
©¤ ÊäÈë¸¡¿Õ
©¤ ÊäÈëÉÏÀ­
©¤ ÊäÈëÏÂÀ­
©¤ Ä£ÄâÊäÈë

©¤ ¿ªÂ©Êä³ö
©¤ ÍÆÍìÊ½Êä³ö
©¤ ¸´ÓÃÍÆÍìÊ½
©¤ ¸´ÓÃ¿ªÂ©¹¦ÓÃ


STM32Ê±ÖÓ³õÊ¼»¯º¯ÊýSystemInit()Ïê½â
https://blog.csdn.net/xuzhexing/article/details/90380971

*/
#define   CLOSE_MINUTE  2

			
	




INT8U  Time_Modify[6]={0x00,0x00,0x00,0x00,0x02,0x01}; //Ä¸ÖÓÊ±¼äÐÞ¸Ä»º´æ
INT8U  Mp3_Ok=0,Mp3_Error=0;       //MP3·¢ËÍÃüÁî³É¹¦

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
INT8U  Light_En=1;                       //ÕÕÃ÷Ê¹ÄÜ  
INT8U  Light_Start=19,Light_End=6;       //ÕÕÃ÷Ê±¼ä¶Î
INT8U  Rythem_Number=8,Strike_Number=7;  //±¨Ê±ÒôÀÖºÅ£¬ÖÓÉùºÅ	

INT8U   MotorActFlag;
INT8U  ReadKey_Value=0xff;               //¶Áµ½µÄ¼üÖµ
//GPSÄ£¿éµ÷ÊÔ³É¹¦£¬Ä¿Ç°Ö´ÐÐisLinear(_ntp)ºóÌøÈëHardFault_Exception!!
//¼üÅÌ½Ó¿Ú¼°ÏÔÊ¾¶¼µ÷ÊÔ³É¹¦£¡
//DS3231Ä£¿éµ÷ÊÔ³É¹¦£¡
//µç»úÇý¶¯¼°µç»ú·´À¡Ä£¿éµ÷ÊÔ³É¹¦£¡
//±¨Ê±Ä£¿éÒÑ¾­µ÷ÊÔ³É¹¦£¡£¡
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
		base=(sect>NVIC_VectTab_FLASH)? NVIC_VectTab_FLASH : NVIC_VectTab_RAM;//ÖÐ¶ÏÏòÁ¿±íµÄ»ùµØÖ·
		offset=sect-base;	             	//ÖÐ¶ÏÏòÁ¿±íµÄÆ«ÒÆ	
		#ifdef VECT_TAB_RAM
		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);// Set the Vector Table base location at 0x20000000
		#else
		NVIC_SetVectorTable(base,offset);	//ÖØÐÂ¶¨Î»ÖÐ¶ÏÏòÁ¿±í
		#endif	
	#endif
	 
	 
	
	
	  //DelayMs(12000);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//³õÊ¼»¯ÖÐ¶ÏÏòÁ¿   ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é		
	  OS_CPU_SysTickInit();
    #if (OS_TASK_STAT_EN > 0)// Í³¼ÆÈÎÎñ 
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
	phead = HeadInsert_List(phead);  //  ´´½¨Á´±í
	Illustrate(phead);               //  Êä³öÃ¿¸ö½áµãµÄÊý¾ÝÓò
	phead = TailInsert_List(phead);
	Illustrate(phead);               //  Êä³öÃ¿¸ö½áµãµÄÊý¾ÝÓò

ÏµÍ³µÄµÚÒ»¸öÈÎÎñ£¬¸ºÔð¿ªOSÊ±ÖÓ£¬½¨Á¢ÆäËûÈÎÎñ
ROÊÇ³ÌÐòÖÐµÄÖ¸ÁîºÍ³£Á¿
RWÊÇ³ÌÐòÖÐÒÑ¾­³õÊ¼»¯µÄ±äÁ¿
ZIÊÇ³ÌÐòÖÐÒÑ¾­Ã»ÓÐ³õÊ¼»¯µÄ±äÁ¿
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
	
	
     OSTaskCreateExt(  AppTask1, //  ½¨Á¢µÚ1¸öÈÎÎñ 	
										  (void *) 0, 
										  (OS_STK *) &AppTask1Stk[APP_TASK1_STK_SIZE- 1],
										  APP_TASK1_PRIO,
                      APP_TASK1_PRIO,
										  (OS_STK *) &AppTask1Stk[0],
										  APP_TASK1_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 											

	 
	
   OSTaskCreateExt(   AppTask2, //  ½¨Á¢±¨Ê±ÈÎÎñ 	
										  (void *) 0, 
										  (OS_STK *) &AppTask2Stk[APP_TASK2_STK_SIZE- 1],
										  APP_TASK2_PRIO,
                      APP_TASK2_PRIO,
										  (OS_STK *) &AppTask2Stk[0],
										  APP_TASK2_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );


       OSTaskCreateExt(  AppTask3, //  ½¨Á¢µÚ3¸öÈÎÎñ 	
										  (void *) 0, 
										  (OS_STK *) &AppTask3Stk[APP_TASK3_STK_SIZE- 1],
										  APP_TASK3_PRIO,
                      APP_TASK3_PRIO,
										  (OS_STK *) &AppTask3Stk[0],
										  APP_TASK3_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 


      OSTaskCreateExt(  AppTask4, //  ½¨Á¢µÚ4¸öÈÎÎñ 	
										  (void *) 0, 
										  (OS_STK *) &AppTask4Stk[APP_TASK4_STK_SIZE- 1],
										  APP_TASK4_PRIO,
                      APP_TASK4_PRIO,
										  (OS_STK *) &AppTask4Stk[0],
										  APP_TASK4_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 


   
    
											
											
		OSTaskCreateExt(	AppTask5, //  ½¨Á¢Ö÷ÈÎÎñ£¬°üÀ¨µç»ú×ßÊ±¡¢µç»ú·´À¡¼°ÕÕÃ÷  ½¨Á¢µÚ5¸öÈÎÎñ 
											(void *) 0, 
											(OS_STK *) &AppTask5Stk[APP_TASK5_STK_SIZE - 1], 
											APP_TASK5_PRIO,
											APP_TASK5_PRIO, 
											(OS_STK *) &AppTask5Stk[0], 
											APP_TASK5_STK_SIZE , 
											(void *) 0,  
											 OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   ); 
		
											
     OSTaskCreateExt(  AppTask6, //  ½¨Á¢µÚ6¸öÈÎÎñ 	 ×îµÍÈÎÎñ½øÐÐ·´¸´ÁÁÃðÖ¸Ê¾µÆ£¡£¡
										  (void *) 0, 
										  (OS_STK *) &AppTask6Stk[APP_TASK6_STK_SIZE- 1],
										  APP_TASK6_PRIO,
                      APP_TASK6_PRIO,
										  (OS_STK *) &AppTask6Stk[0],
										  APP_TASK6_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );
									 
									 
									 
		OSTaskCreateExt(  AppTask7, //  ½¨Á¢µÚ7¸öÈÎÎñ 	 ×¨ÃÅ´¦Àígps£¡£¡
										  (void *) 0, 
										  (OS_STK *) &AppTask7Stk[APP_TASK7_STK_SIZE- 1],
										  APP_TASK7_PRIO,
                      APP_TASK7_PRIO,
										  (OS_STK *) &AppTask7Stk[0],
										  APP_TASK7_STK_SIZE , 
										  (void *) 0, 
										  OS_TASK_OPT_STK_CHK |  OS_TASK_OPT_STK_CLR 
                   );
											
											
		OSTaskCreateExt(  AppTask8, //  ½¨Á¢µÚ8¸öÈÎÎñ 	 ×¨ÃÅ²âÊÔ£¡£¡
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

/*printfº¯Êý
%%£ºÏÔÊ¾Ò»¸ö%£¬''¶Ô%ÎÞÐ§£¬ÐèÒªÓÃ"%%"Êä³ö%
 %ns£ºÏÔÊ¾n¸ö×Ö·ûµÄ×Ö·û´®£¬²»×ãnÓÃ¿Õ¸ñÔÚ×ó²àÌî³ä
%0ns£ºÏÔÊ¾n¸ö×Ö·ûµÄ×Ö·û´®£¬²»×ãnÓÃ0ÔÚ×ó²àÌî³ä
%-ns£ºÏÔÊ¾n¸ö×Ö·ûµÄ×Ö·û´®£¬²»×ãnÓÃ¿Õ¸ñÔÚÓÒ²àÌî³ä

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
	ucos ¶à¸öÈÎÎñµÈ´ýÒ»¸öÐÅºÅÁ¿  ¾ÙÀý·Ç³£Ö±¹Û£¬ÖµµÃÍÆÇÃ   added by sjw
	https://blog.csdn.net/gtkknd/article/details/52212097
	*/
	 pMainMotorSemEve=OSSemCreate(0);//Èç¹ûSemp = OSSemCreate(0), ¸ÃÐÅºÅÁ¿±íÊ¾µÈ´ýÒ»¸öÊÂ¼þ»òÕß¶à¸öÊÂ¼þµÄ·¢Éú¡£
	 pMainBsSemEve=OSSemCreate(0);
	 
	
	 Mutex_USART1 = OSMutexCreate(USART1_MUTEX_PRIO, &err);  // ½¨Á¢USART1»¥³âÐÍÐÅºÅÁ¿
	 Mutex_USART2= OSMutexCreate(USART2_MUTEX_PRIO, &err);   // ½¨Á¢USART2»¥³âÐÍÐÅºÅÁ¿	
	
	 GPIO_Motor_Config();       //ÄÚº¬µç»úÇý¶¯¶Ë¿ÚIO³õÊ¼»¯---µç»ú·´À¡¶Ë¿Ú³õÊ¼»¯   
	 GPIO_I2C_Config();
	 LedPortSpecialInit();
	 //ÔÚµ÷ÊÔµÄÊ±ºò£¬PE2×ÜÊÇ³öÏÖ¸ßµçÆ½£¬²»¸úÈí¼þÖ¸Áî¶¯×÷£¬·´¸´²âÁ¿Ó²¼þÃ»ÓÐÎÊÌâ£¬µ¥¶ÀºËÐÄ°å¾ÍÒ»¸ùÏßÖ±½Óµ½  HDR2*12²å×ù£¬ÎÞÈÎºÎÎÊÌâ
	 //ÁíÒ»¿éºËÐÄ°åÍ¬ÑùÈç´Ë£¬ÍòÓÃ±í²âÁ¿PE2Òý½Å·¢ÏÖÊÇÐ¡ÓÚ3.3·ü£¬Æ½Ê±Ò»Ö±Îª1.8-1.9·ü£¬¿¼ÂÇµ½²»ÄÜÊÇÁ½¸öcpu¶Ë¿Ú¶¼»µµôÁË°É£¬
	 //µçÑ¹ÉÏ²»È¥£¬·´¸´²âÊÔ£¬ÁíÒ»¸öSSRÕý³££¬×îºó·¢ÏÖ¶Ë¿ÚEµÄÊ±ÖÓÃ»ÓÐ´ò¿ª£¬ÔÚº¯ÊýÖÐ´ò¿ªÒ»ÇÐÕý³££¬¼Ç×¡µçÑ¹ÉÏ²»È¥µÄ¿ÉÄÜÔ­ÒòÊÇÊ±ÖÓÃ»Ê¹ÄÜ
	 //added  by sjw    !!!!!!!!!!!!!!!!!!!
	 LedBsZm_Init();                 //¹¤×÷Ö¸Ê¾µÆ,±¨Ê±¡¢ÕÕÃ÷¶Ë¿Ú³õÊ¼»¯  PB4Îª±¨Ê±Êä³ö¿Ú£¡£¡  PE2ÎªÕÕÃ÷Êä³ö¿Ú£¡£¡
   Mp3Drive_Init();

	 Hd7279_Init();
	 //https://blog.csdn.net/m0_52850679/article/details/124506315
	 //Æ¬ÄÚÍâÉèµÄDMAxÍ¨µÀy      added by sjw
	 
	 TIM1_Config();             //                                                Ö÷ÖÐ¶Ï0£¬´Î¼¶ÖÐ¶Ï0
	 N31_pps_init();            //GPSµÄppsÖÐ¶ÏÐÅºÅ    gps¶Ë¿Ú³õÊ¼»¯ ppsµÄÖÐ¶Ï£º     Ö÷ÖÐ¶Ï0£¬´Î¼¶ÖÐ¶Ï1
	 USART1_Init(9600);	        // ³õÊ¼»¯´®¿Ú1,9600²¨ÌØÂÊ							            Ö÷ÖÐ¶Ï1£¬´Î¼¶ÖÐ¶Ï0
	 GPIO_Key_Config();         //¼üÅÌ¼üÅÌ¶Ë¿Ú¼°ÆäÖÐ¶Ï  								            Ö÷ÖÐ¶Ï1£¬´Î¼¶ÖÐ¶Ï1
   USART2_Init(9600);         //                                                Ö÷ÖÐ¶Ï1£¬´Î¼¶ÖÐ¶Ï2                                                  
	 //printf("**        »¶Ó­Ê¹ÓÃARM¿ª·¢°å        **\r\n");Í¨¹ýÖØ¶¨Î»²âÊÔ´®¿Ú2ÊÇÃ»ÓÐÎÊÌâ£¡  added by sjw
	 USART_ClearFlag(USART2,USART_FLAG_TC); 
	 
	
	
	 
/*
ËþÖÓ»ò¼ªÏéÖÓ·¢³ö±¨Ê±Êý¾Ý
24  0F 04 01 0C 4D 50 33 5F 30    30 36 36 2E 4D 50 33 77   --Î÷ÃôËÂÇ°×à£¡
24  0F 04 01 0C 4D 50 33 5F 30    30 35 36 2E 4D 50 33 74  ÇÃÖÓnÏÂÖØ¸´·¢ËÍn´Î


24  0F 04 01 0C 4D 50 33 5F 30    30 36 32 2E 4D 50 33 73  ¶«·½ºìÇ°×à£¡
24  0F 04 01 0C 4D 50 33 5F 30    30 35 35 2E 4D 50 33 77ÇÃÖÓnÏÂÖØ¸´·¢ËÍn´Î


https://blog.csdn.net/horton11/article/details/120361823  
	 
7¡¢×¢Òâµ½ÕâÒ»¾ä£ºÓÉÈí¼þÐòÁÐÇå³ý¸ÃÎ»(ÏÈ¶ÁUSART_SR£¬È»ºóÐ´ÈëUSART_DR)¡£ Ò²¾ÍÊÇËµ£¬ÒªÏÈread USART_SR,È»ºówrite USART_DR£¬²ÅÄÜÍê³ÉTC×´Ì¬Î»µÄÇå³ý¡£¶øÓ²¼þ¸´Î»ºó£¬´®¿Ú·¢ËÍµÄÊ×¸öÊý¾ÝÖ®Ç°Ã»ÓÐread SRµÄ²Ù×÷£¬ÊÇÖ±½Ówrite DR£¬Ò²¾ÍÊÇËµ£¬TCÃ»ÓÐ±»Çå³ýµô¡£ ËµÃ÷ÎÒÃÇÇ°ÃæµÄ²Â²âÊÇ¶ÔµÄ¡£  
8¡¢ÄÇÃ´£¬Ó¦¸Ã°ÑÔÚ´«ÊäµÚÒ»¸ö×Ö½ÚÇ°Ãæ¼Ó£ºUSART_ClearFlag(USART1,USART_FLAG_TC); ¸ÄÎªUSART_GetFlagStatus(USART1, USART_FLAG_TC);£¬Ó¦¸ÃÒ²ÄÜÏû³ý´íÎó¡£²âÊÔºóÖ¤Êµ£¬È·ÊµÈç´Ë£¬ÔÚ·¢ËÍÊ×¸öÊý¾ÝÖ®Ç°£¬ÏÈ¶ÁÈ¡Ò»ÏÂUSART_SR£¬ÄÇÃ´¾Í²»»á³öÏÖÊ×¸öÊý¾Ý¶ªÊ§µÄÇé¿öÁË¡£  
9¡¢×Ü½á£ºÓ²¼þ¸´Î»ºó£¬´®¿Ú·¢ËÍÊ×¸öÊý¾ÝÖ®Ç°£¬ÏÈ¶ÁÈ¡Ò»ÏÂUSART_SR£¬ÔòÄÜ¹»±£Ö¤Ê×¸öÊý¾Ý·¢ËÍÊ±£¬²»³öÏÖ¸²¸ÇµÄÇé¿ö¡£µ±È»£¬Ò²ÓÐ±ðµÄ·½·¨£¬±ÈÈçÏÈÇå³ýTC×´Ì¬Î»£¬»òÊÇ£¬ÔÚwrite USART_DRÖ®ºó£¬¼ÓÈëÒ»¸öÐ¡ÑÓÊ±£¬ÈÃÊý¾Ý·¢ËÍÍê±Ï£¬Ó¦¸ÃÒ²ÄÜ¼ä½ÓÅÅ³ýÕâ¸ö´íÎó
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
°æÈ¨ÉùÃ÷£º±¾ÎÄÎªCSDN²©Ö÷¡¸horton11¡¹µÄÔ­´´ÎÄÕÂ£¬×ñÑ­CC 4.0 BY-SA°æÈ¨Ð­Òé£¬×ªÔØÇë¸½ÉÏÔ­ÎÄ³ö´¦Á´½Ó¼°±¾ÉùÃ÷¡£
Ô­ÎÄÁ´½Ó£ºhttps://blog.csdn.net/horton11/article/details/120361823 
*/	 
	
	 /*
	 for( count=0; count<18; count++){
		  USART_SendData(USART2,*pbsdata);
      //USART2->DR=*pbsdata;		 
			while((USART2->SR & 0x40)==0);//Ñ­»··¢ËÍ,Ö±µ½·¢ËÍÍê±Ï 
		  pbsdata++;
	 }*/
	 
	 #ifdef  USB_DEBUG_KERNEL  //USB_DEBUG0		
			printf("*************************************\r\n"); // LOGO 
			printf("**                                 **\r\n");
			printf("**        »¶Ó­Ê¹ÓÃARM¿ª·¢°å        **\r\n");
			printf("**  ÎÒÃÇ½«ÒýÁìÄú½øÈëÇ¶ÈëÊ½ÏµÍ³¿ª·¢ **\r\n");
			printf("**           ÄúµÄ×î¼ÑÑ¡Ôñ          **\r\n");
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
			printf("\n\r ²úÆ·ÄÚ²¿Flash´óÐ¡Îª£º%dK×Ö½Ú£¡ \t www.armjishu.com\n\r",  *(__IO uint16_t*)(0x1FFFF7E0));
			printf("±äÁ¿BigOrSmallValueµÄµØÖ·Îª%p\r\n",&BigOrSmallValue);
			printf("Ö¸ÕëpBigOrSmallValueµÄµØÖ·Îª%p\r\n",pBigOrSmallValue);
		#endif	
	  OS_EXIT_CRITICAL();	
		
		
		
	
/*
const unsigned char       Volume[6]={0x24,0x03,0x0F,0x01,0x1F,0x12};                     //MP3ÒôÁ¿ÉèÖÃ
unsigned char             Mp3data[18]={0x24,0x0F,0x04,0x01,0x0C,0x4D,0x50,0x33,0x5F,0x30,  //²¥·ÅMP3Ö¸¶¨ÎÄ¼þ
                                     0x30,0x30,0x32,0x2E,0x4D,0x50,0x33,0x74};


Ö÷°åµÄCPU¸øMP3Ä£¿éµÄÊý¾ÝÈçÏÂ£º  
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--·¢ËÍ×Ö½ÚÎª60¸ö
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16µãÇ°×à£º
		24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
17µãÇ°×à£º
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
    24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 

18µãÇ°×à£º
    24 03 0F 01 1F 12 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 
		50 33 5F 30 30 36 36 2E 4D 50 33 77 24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

		
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z	
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z
$MP3_0287.MP3z$MP3_0287.MP3z$MP3_0287.MP3z
16µãÇÃµã´ÎÊý£º
		24 0F 04 01 0C 4D 50 33 5F 30 32 38 37 2E 4D 50 33 7A 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		37 2E 4D 50 33 7A 24 0F 04 01 0C 4D 50 33 5F 30 32 38 37 2E 4D 50 33 7A 
17µãÇÃµã´ÎÊý£º
$MP3_0288.MP3u$MP3_0288.MP3u$MP3_0288.MP3u------------------------·¢ËÍ×Ö½ÚÎª54¸ö
$MP3_0288.MP3u$MP3_0288.MP3u$MP3_0288.MP3u
    24 0F 04 01 0C 4D 50 33 5F 30 32 38 38 2E 4D 50 33 75 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		38 2E 4D 50 33 75 24 0F 04 01 0C 4D 50 33 5F 30 32 38 38 2E 4D 50 33 75 				
18µãÇÃµã´ÎÊý£º
    24 0F 04 01 0C 4D 50 33 5F 30 32 38 39 2E 4D 50 33 74 24 0F 04 01 0C 4D 50 33 5F 30 32 38 
		39 2E 4D 50 33 74 24 0F 04 01 0C 4D 50 33 5F 30 32 38 39 2E 4D 50 33 74

¿ØÖÆ×Ö·ûASCIIÂë±í
https://www.perfcode.com/p/control-character.html
*/	

	
	while(1){
		//OSTimeDly (500);
	   
		  OSTimeDlyHMSM(0, 0, 0, 400);
	}
  
}






//¹Û²ìusart2ÖÐ¶Ï½ÓÊÕµÄÄ¸ÖÓ·¢ËÍµÄÊý¾Ý£¬9¸ö£¡
static  void AppTask2(void* p_arg)
{
   INT8U err;
   INT8U temp;

  p_arg = p_arg;
	//OSTimeDly(1000);
 

  while (1) {
		
       #if 0
	     OSTaskSuspend(OS_PRIO_SELF); 		    // ÏÈ½«ÈÎÎñ¹ÒÆð£¬ÔÚ´®¿Ú½ÓÊÕÖÐ¶ÏÖÐ»Ö¸´ÈÎÎñ
       OSMutexPend(Mutex_USART2, 0, &err);  // µÈ´ýÐÅºÅÁ¿
       while(USART2_GetByte(&temp)){    	  // Èç¹û´®¿Ú½ÓÊÕµ½Êý¾Ý´òÓ¡³öÀ´
           USART2_SendByte(temp);
       }  
	   
	    if((USART2_RX_FIFO[0]==0xbb)&&(USART2_RX_FIFO[7]==0x0d)&&(USART2_RX_FIFO[8]==0x0a)){ 	
					p_timemu->hour=USART2_RX_FIFO[1];
					p_timemu->minute=USART2_RX_FIFO[2];
					p_timemu->second=USART2_RX_FIFO[3];
					MainBsPayOrXms=USART2_RX_FIFO[4];		//0ÎªÆ½°²Ò¹±¨Ê±£»1ÎªÎ÷ÃôËÂ±¨Ê±£¡
					MainBsKnockCnt=USART2_RX_FIFO[5]%12;   	//ÖÓÉù´ÎÊý£¡
					if(USART2_RX_FIFO[6]==0){		 		//±¨Ê±´ò¿ª»òÕß¹ØËÀ×´Ì¬£¡
						//MainBsOnOffStatusFlag=FALSE;
						//MainBsJsValidFlag=FALSE;		
					}else{
						//MainBsOnOffStatusFlag=TRUE;
						//MainBsJsValidFlag=TRUE;
					}	
			}
      OSMutexPost(Mutex_USART2);            // ÊÍ·ÅÐÅºÅÁ¿  
			#endif
			OSTimeDlyHMSM(0, 0, 0, 470);
			
			
   }
}




static  void AppTask3(void* p_arg)//¼üÅÌ´¦ÀíÈÎÎñ£¡£¡
{	
	INT8U tempdata;
 static INT8U rxjs=0x11;	
	
	
	
	
	#if 0
		if (ucKeyValue > 0)
		{
				/* ÔÝÊ±²»×öÈÎºÎ´¦Àí£¬ÓÃ»§¿ÉÒÔ×Ô¼ºÌí¼Ó´¦Àí´úÂë */
				switch (ucKeyValue)
				{
					case KEY_DOWN_JOY_UP:		/* Ò¡¸ËUP¼ü°´ÏÂ  */
					case KEY_DOWN_JOY_DOWN:		/* Ò¡¸ËDOWN¼ü°´ÏÂ  */
					case KEY_DOWN_JOY_LEFT:		/* Ò¡¸ËLEFT¼ü°´ÏÂ */
					case KEY_DOWN_JOY_RIGHT:	/* Ò¡¸ËRIGHT¼ü°´ÏÂ */
					case KEY_DOWN_JOY_OK:		/* Ò¡¸ËÖÐ¼ü°´ÏÂ */
					case KEY_DOWN_USER:			/* USER¼ü°´ÏÂ */
						break;					

					default:
						break;
				}
		}
#endif
		
		
		while(1){
			
			//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);//¼ì²é½ÓÊÜ±êÖ¾Î»£¬ÊÇ·ñ¿ÉÒÔ½ÓÊÜadded by sjw
			//rxjs=SPI_I2S_ReceiveData(SPI1);
			

			OSTimeDlyHMSM(0, 0, 0, 300);
			
		}
}







/*
±¾ÎÄ²ÉÓÃDMA+»·ÐÎ»º³åÇø¶ÔGPS±¨ÎÄ½øÐÐ½âÎö£¬Ë¼Â·ÊÇÍ¨¹ýDMAÖÐ¶Ï½ÓÊÕµ½GPS±¨ÎÄºó£¬´æ·Åµ½»·ÐÎ»º³åÇø£¬È»ºóÔÚÖ÷³ÌÐòÖÐ½âÎöGPS±¨ÎÄ¡£
½âÎöGPS±¨ÎÄµÄ¹Ø¼üÊÇ£º½«»·ÐÎ»º³åÇøÖÐµÄ×Ö½Ú×ª»»³É×Ö·û´®£¬È»ºóÔÚ×Ö·û´®ÖÐ²éÕÒGPS±¨ÎÄÍ·±êÊ¶£¨ÀýÈç£ºGPGGA£©ºÍGPS±¨ÎÄÎ²²¿±êÊ¶£¨»Ø³µ»»ÐÐ£©¡£
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
°æÈ¨ÉùÃ÷£º±¾ÎÄÎªCSDN²©Ö÷¡¸ba_wang_mao¡¹µÄÔ­´´ÎÄÕÂ£¬×ñÑ­CC 4.0 BY-SA°æÈ¨Ð­Òé£¬×ªÔØÇë¸½ÉÏÔ­ÎÄ³ö´¦Á´½Ó¼°±¾ÉùÃ÷¡£
Ô­ÎÄÁ´½Ó£ºhttps://blog.csdn.net/ba_wang_mao/article/details/115530153


//https://blog.csdn.net/ba_wang_mao/article/details/115530153
	//STM32F407 µ¥Æ¬»ú+DMA+»·ÐÎ»º³åÇø+GPS±¨ÎÄ½âÎö
	
	//https://www.codenong.com/cs107108405/
	//´®¿Ú¿ÕÏÐÖÐ¶Ï+DMA½ÓÊÕÊý¾Ý
½âÊÍGPSÈÎÎñ·ÅÔÚÈÎÎñ4ÖÐ´¦Àí£¡
*/











/*
NTPÊ±¼ä´Á×ª»»³ÉUTCÊ±¼äµÄ¹ý³Ì
https://blog.csdn.net/weixin_45873923/article/details/120119622


¢ÙNTPÊ±¼ä´ÁÓÃÒ»¸ö64bitÎÞ·ûºÅ¶¨µãÊý±íÊ¾£¬Ëü±íÊ¾×Ô´Ó1900Äê1ÔÂ1ÈÕ00:00:00µ½ÏÖÔÚ¹ýÁË¶àÉÙÃë¡£
¢ÚUTCÊ±¼ä£¬¸ñÁÖÍþÖÎÊ±¼ä1970Äê1ÔÂ1ÈÕ00:00:00£¨±±¾©Ê±¼ä1970Äê1ÔÂ1ÈÕ08:00:00£©ÆðÖÁÏÖÔÚµÄ×ÜÃëÊý£¬±íÊ¾Îª1970-01-01 00:00:00 UTC¡£³ÌÐòÀïÏ°¹ß½Ð×öUTCÊ±¼ä´Á¡£
 NTPÐ­ÒéÖÐÓÐËÄ¸öÊ±¼ä´Á£¬±¾ÎÄ²»ÌÖÂÛÕâËÄ¸öÊ±¼ä´ÁµÄÇø±ð£¬Ö»¼òµ¥µÄÄÃÆäÖÐÒ»¸öNTPÊ±¼ä´Á±¨ÎÄ·ÖÎöÈçºÎ×ª»»³ÉUTCÊ±¼ä¡£
ÀýÈçÒ»¶ÎÊ±¼ä´Á±¨ÎÄÎª¡°D9 FD 84 95 94 F8 59 7C¡±£¬ÏÂÃæÎÒÃÇÒ»ÆðÑ§Ï°¸ÃNTPÊ±¼ä´ÁÊÇÈçºÎ×ª»»³ÉUTCÊ±¼äµÄ¡£


mktimev(&now)º¯Êý½«ÄêÔÂÈÕÊ±·ÖÃë×ª»»ÎªNTPµÄÃëÊý
to_tm(NTP - JAN_1970, &now);º¯Êý½«ÃëÊý×ª»»ÎªUTCÊ±¼ä

*/


//GPSÄ£¿éµ÷ÊÔ³É¹¦£¬Ä¿Ç°Ö´ÐÐisLinear(_ntp)ºóÌøÈëHardFault_Exception!!
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
		
			set_pps1_sig();//µ±pps1_tim > 101Ê±ºò£¬ÐèÒªpps1_status=0ºÍÃëÂö³åÍ¬²½£¡
		
			if(uart1_rx_sig){			
				uart1_rx_sig = 0;	
				board.err &= ~err_gps1;
				
				//gps.status = gps_bd2_ascii(Uart1_Rx_Buf, Usart1_Rx_Len);	//
				gps.status = gps_bd2_ascii(receive_data, Usart1_Rx_Len);	//receive_data

				memset(Uart1_Rx_Buf,0,UART1_RX_SIZE);    //´¦ÀíÍê±Ï½øÐÐÇå¿ÕÊý×éµÄ¹¤×÷£¡£¡	
				
				
				//uCOSÁÙ½ç¶Îº¯ÊýµÄÀí½â£ºCPU_SR_ALLOC() Ð´µÄ·Ç³£°ô£¬±ÜÃâÖÐ¶ÏÇ¶Ì×ÖÐ¶ÔÁÙ½ç¶Î³ÌÐòµÄÆÆ»µ£¡£¡added by sjw
		    //https://blog.csdn.net/m0_43443861/article/details/125956776						
				
				
				if(gps.status){								
						  _ntp = do_gps(); //½«GPS½ÓÊÕµÄ±ê×¼UTCÊý¾ÝËÍ¸ø±äÁ¿  ×¢Òâ´ËÊ±ÒÑ¾­½«UTCÊ±¼ä±äÎªCTCÊ±¼äadded by sjw		
						//if(isLinear(_ntp) && (pps1_status>10))//Ö´ÐÐº¯ÊýisLinear(_ntp)ºóÌøÈëÒì³££¡£¡added by sjw
					    if(pps1_status>10){
									NTP = _ntp;								  
									if(!(_ntp %180) ){		  //±£ÁôÍù3231ÀïÃæÑ¹gpsÊý¾ÝµÄ¹¦ÄÜ£¡Ã¿3·ÖÖÓÒ»´Î£¡
										
										OS_ENTER_CRITICAL();	//½øÈëÁÙ½çÇø						
										//OSSchedLock(&err);		//UCOSIIµÄ·½Ê½,½ûÖ¹µ÷¶È 		
										ds3231_tm_wr(NTP);   //µÈ´ýx·ÖÖÓÍùÀïÑ¹Èë±£´æ£¡);	
										/*
										µ÷¶ÈÆ÷ÉÏËøº¯ÊýOSSchedlock()µÄ¹¦ÄÜÊÇÓÃÓÚ½ûÖ¹ÈÎÎñµ÷¶È£¬Ê¹ÈÎÎñ±£³Ö¶ÔCPUµÄ¿ØÖÆÈ¨¡£µ÷¶ÈÆ÷¿ªËøº¯ÊýOSSchedUnlock()µÄ¹¦ÄÜÊÇ½â³ý¶ÔÈÎÎñµ÷¶ÈµÄ½ûÖ¹¡£
										µ÷¶ÈÆ÷ÉÏËøºÍ¿ªËøµÄÊµÏÖÔ­ÀíÊÇ£º¶ÔÈ«¾Ö±äÁ¿Ëø¶¨Ç¶Ì×¼ÆÊýÆ÷OSLockNesting½øÐÐ²Ù×÷£¬OSLockNesting¸ú×ÙOS SchedLock() º¯Êý±»µ÷ÓÃµÄ´ÎÊý£¬
										ÔÊÐíÇ¶Ì×Éî¶È´ï255²ã¡£µ÷¶ÈÆ÷ÉÏËø¼´¶Ô±äÁ¿OSLockNesting½øÐÐ¼Ó1²Ù×÷£¬¿ªËø¼´¶Ô±äÁ¿OSLockNesting½øÐÐ¼õ1²Ù×÷¡£
										¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
										°æÈ¨ÉùÃ÷£º±¾ÎÄÎªCSDN²©Ö÷¡¸fillthesky¡¹µÄÔ­´´ÎÄÕÂ£¬×ñÑ­CC 4.0 BY-SA°æÈ¨Ð­Òé£¬×ªÔØÇë¸½ÉÏÔ­ÎÄ³ö´¦Á´½Ó¼°±¾ÉùÃ÷¡£
										Ô­ÎÄÁ´½Ó£ºhttps://blog.csdn.net/fillthesky/article/details/46697179
										*/
										//OSSchedUnlock(&err);	//UCOSIIµÄ·½Ê½,»Ö¸´µ÷¶È
										
										OS_EXIT_CRITICAL();	  //ÁÙ½çÇø	
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









//´ËÈÎÎñ×¨ÃÅ´¦Àí±¨Ê±¹¦ÄÜ£¬¿´¿´Ç°×àºÍÖÓÉù·Ö±ðÊÇÊ²Ã´¡¢ÊÇ·ñµ½±¨Ê±Ê±¼äÁË£¡£¡added by sjw
static  void AppTask5(void* p_arg)
{
	OS_CPU_SR  	cpu_sr;
	INT8U err,eeprom_page;
	INT8U js=0,flag=0,count;
  struct tm  now;
	INT8U    wait=0;
	
	
	
		
		#if 0  //32Ò³Àï256¸öµ¥ÔªÈ«²¿ÑéÖ¤£¬ÎÞÈÎºÎÎÊÌâ£¡£¡  added by sjw  2023-10-14 ÖÜÁù goto work
		 OS_ENTER_CRITICAL();
		 for(eeprom_page=0;eeprom_page<32;eeprom_page++){
				iic_sw_write(eep_chip_24cxx, iic_eeprom_east+eeprom_page*8, tx1, 8);//×¢ÒâÐ¾Æ¬ÊÇÒ»Ò³¾Í8¸ö×Ö½Ú£¬ÈçºÎ´óÓÚ8¸ö×Ö½Ú£¬ÓÖ²øÈÆ·­×ªµ½¿ªÊ¼µØÖ·£¡£¡added by sjw
				DelayMs(100);
		 }
		 OS_EXIT_CRITICAL();	
		 OSTimeDlyHMSM(0, 0, 1, 500);
		 OS_ENTER_CRITICAL();
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_east, &board.east_time[0], 8);//×¢ÒâI2CÓÐ¸öÐ´ÖÜÆÚ£¬´óÔ¼10ms£¬¶àÒ³Ð´Òª´óÓÚ´ËÐ´ÖÜÆÚ£¡£¡added by sjw
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_south, &board.south_time[0], 8);
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_west, &board.west_time[0], 8);
		 iic_sw_read(eep_chip_24cxx, iic_eeprom_north, &board.north_time[0], 8);
		 OS_EXIT_CRITICAL();		
		#endif
		
		
		/*
	  //¸ÃÖ¸ÁîÊ¹ËùÓÐµÄLEDÈ«²¿µãÁÁ£¬²¢´¦ÓÚÉÁË¸×´Ì¬£¬Ö÷ÒªÓÃÓÚ²âÊÔ¡£
    Set7279CS(0);
    SendByteToHd7279(CMD_TEST);
    DelayMs(2400);		
    Set7279CS(1); 
	*/


   for(wait=0;wait<5;){ //¿ª»úµÈ´ý5Ãë  added by sjw
		 
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
		//iic_sw_write(eep_chip_24cxx, 0x0e,&temp , 1);//Ä£ÄâRTC  
		get_time();//¶ÁÈ¡RTCµÄÊ±¼ä
	 //ÓÉÔ­À´º¯Êýget_iic_setting  Å²¶¯Î»ÖÃµ½Õâ¸öÎ»ÖÃ£¬added by sjw
	  get_iic_setting();//¶ÁÈ¡×ÓÖÓÊ±¼ä¡¢±¨Ê±¿ª¹ØÉè¶¨µÄÐ¡Ê±¡¢±¨Ê±Ç°×à¼°ÖÓÉùºÍÕÕÃ÷¿ª¹ØµÄÉè¶¨£¡£¡added by sjw
		OS_EXIT_CRITICAL();	
		#endif
	 
  
   TimeDisValidFlag=1;//¶Á³öÊ±¼äÊý¾ÝÕýÈ·ºó£¬±êÖ¾ÓÐÐ§£¡£¡added by sjw
  
	//test1=HEX_to_BCD(0x19);//0x19ÊÇ16½øÖÆ,×ª»»Îª    BCDÂëÓ¦¸ÃÎª0x25  ÔËÐÐºó´Ë½á¹ûÕýÈ·£¡£¡added by sjw
	//test2=BCD_to_HEX(37);  //BCDÂëÎª37    ×ª»»Îª    16½øÖÆÓ¦¸ÃÎª0x25  ÔËÐÐºó´Ë½á¹û²»ÕýÈ·£¡£¡ÕýÈ·½á¹ûÓ¦¸ÃÎª0x19 added by sjw

	
	 	
		
		
	while(1){	
				Light_Control();  //ÕÕÃ÷ 
				Time_Notice();    //±¨Ê±
				if(IntDisFlag){   //ÏÔÊ¾Ä¸ÖÓÊ±¼ä,ÏÖÔÚÐÞ¸ÄÎª300msÏÔÊ¾Ò»´Î
						Set7279CS(0);
						Display();
						Set7279CS(1);
						IntDisFlag=0;
				}
				
				
				if(Key_Time==1){ //´¦Àí°´¼ü²Ù×÷
					Set7279CS(0);
					Key_Operation();  //  ³öÏÖ¶¶¶¯ÏÖÏó£¬ÊÇÒòÎª   Æ¬Ñ¡ÐÅºÅ   ²Ù×÷µÄÎ»ÖÃ³ö´í£¬½Ó½üÓÚÆ¬Ñ¡Ò»Ö±Ñ¡ÖÐ£¬ËùÒÔ8¸öÊý×ÖÈ«²¿ÉÁË¸£¡£¡added by sjw
					Set7279CS(1);
					Key_Time=0;
				}
				
				OSTimeDlyHMSM(0, 0, 0, 90);		
				
				//OSSemPend(pMainBsSemEve,0,&err);//

	}
}





static  void AppTask6(void* p_arg)//´ËÈÎÎñ×¨ÃÅ´¦Àí¼üÅÌ¿ì×·£¨Õý×ª»òÕß·´×ª¹¦ÄÜ£¡£¡£©added by sjw
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
		   switch ( Key_Subclock_State1){  //ÅÐ¶ÏÊÇ·ñ°´¼üµ÷Õû¹ý  ×ÓÖÓ×´Ì¬  Ê¹Æä±ä»¯ÓÐÐ§ÁË£¡£¡
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





//µç»úÇý¶¯¼°µç»ú·´À¡Ä£¿éµ÷ÊÔ³É¹¦£¡
//ÔÚÉÏµç×·Ê±Íê±Ïºó£¬µç»ú¿ªÊ¼Õý³£×ßÊ±£¡£¡added by sjw
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
		
		 // OSSemPend(pMainMotorSemEve,0,&err);//Õý³£µÄ×ßÊ±£¬
		 
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







//¼üÅÌ½Ó¿Ú¼°ÏÔÊ¾¶¼µ÷ÊÔ³É¹¦£¡£¡
//ÎªÁË½â¾öÓÃ»§ÔÚ³õÊ¼ÉÏµç¿ì×·Ê±µ÷Õû¼üÅÌµÄÌåÑé£¬½«ÏÔÊ¾ºÍ¼üÅÌÄ£¿éÒÆ¶¯µ½ÈÎÎñ7ÉÏ£¬£¡£¡added by sjw
//´ËÓÅÏÈ¼¶×îµÍµÄÈÎÎñ×¨ÃÅ´¦Àí¸ÕÉÏµçºóµÄ¿ì×·¶¯×÷£¬ÕâÑù´¦ÀíÆä²»¸ÉÈÅ¼üÅÌºÍÏÔÊ¾µÄµ÷Õû£¡£¡added by sjw
static  void AppTask8(void* p_arg)
{
	INT8U  err;
	static INT8U first_flag;
	INT8U  eeprom_page,temp[8];
	INT32U     _ntp = 0; 
  OS_CPU_SR  cpu_sr;
	struct tm  now;
	INT8U    wait=0;
	
	//2023Äê10ÔÂ20ÈÕ15£º32:50
	static INT8U  tx[11]={0x00,0x07,0xe7,0x0a,0x14,0x0f,0x20,0x032,0x00,0x00,0x05};	 
	

		
	while(1){	
		//time_set();      //Ä¸ÖÓÊ±¼äÐ£¶Ô
		if(!first_flag){	
		      if(compare_zf(p_timemu,p_timeslave)==1){//±íÊ¾×·Ê±Íê±Ï£¬ÐèÒª½«Êý¾ÝÑ¹lÈëAT24CxxÀï±£´æ£¡£¡
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
						 Key_Subclock_State1=WALK;//±ØÐëÌí¼Ó´ËÖ¸Áî£¬´ú±í³õÊ¼×·Ê±½áÊøºó£¬ÏµÍ³ÎªWALK×´Ì¬£¡£¡added by sjw
						
					}
		}
				
				
		if((p_timemu->minute == 10) && (p_timemu->second == 5)){
			get_time();//1¸öÐ¡Ê±¶ÁÈ¡Ò»´ÎRTCµÄÊ±¼ä
		}
	  
		OSTimeDlyHMSM(0, 0, 0, 130);
	}
}

/*

								
 


    if(LED_time==1)  //ÏÔÊ¾Ä¸ÖÓÊ±¼ä
    {     
     display();                                                                                                                                                                                                                                                                             
     LED_time=0;    
    }  


    if(Key_time==1) //´¦Àí°´¼ü²Ù×÷
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
*¹¦ ÄÜ£º×ÓÖÓÎ´¼Ç×¡Ê±¼äÊ±£¬½«Ä¸ÖÓÊ±¼ä
*        ×÷Îª×Ô¼ºµÄÊ±¼ä
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
*¹¦ ÄÜ£ºÄ¸ÖÓÊ±¼äÐ£¶Ô
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
       Time_adjust=1;//Ð£Ê±±êÖ¾   
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
         Time_adjust=1;//Ð£Ê±±êÖ¾          
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
	OSTimeDlyHMSM(0, 0, 0, 20);	//´ËÈý¾äÖ¸ÁîÌí¼ÓÉÏ±£ÏÕ£¡£¡added by sjw
	
  EAST_ZZ;
	while(1){
			switch(status){
						case IDLE:
								status=WAIT_TIME;
						    LightSlotFlag=1;
						break;
						
						
						
						case WAIT_TIME://Ç¿ÖÆµÈ´ý500ms£¬Ò»¶¨Ô½¹ý¹â²ÛÎ»ÖÃÁË£¡added by sjw
							  if(LightSlotValue>500){
									  LightSlotFlag=0;
								    LightSlotValue=0;
										status=HIGH;
								}else{
									OSTimeDly(20);
								}
						break;
						
						case HIGH:
							  if(EAST_FK_PIN==0){//¿ªÊ¼ Õì²â  µ½´ï¹â²ÛµÄÎ»ÖÃÁË£¬
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
									EEPROM²»·ÖÊ²Ã´ÉÈÇø£¬ÒÔ×Ö½ÚÎª²Ù×÷µ¥Î»£¬·ÖÉÈÇøµÄÊÇFLASH¡£MCU¼¯³ÉµÄEEPROMÊÇ×¨×ö·ÇÒ×Ê§Êý¾Ý´æ´¢Æ÷µÄ£¬Õ¼ÓÃµØÖ·ÊÇRAM¿Õ¼ä¡£MCU¼¯³ÉµÄFLASHÊÇ³ÌÐò´æ´¢Æ÷£¬
									Ö§³ÖIAPµÄ»°£¬¿ÉÒÔÀûÓÃFLASH³ÌÐò´æ´¢Æ÷×÷Îª·ÇÒ×Ê§Êý¾Ý´æ´¢Æ÷£¬µ«ÐÔÖÊÓëEEPROM¿É²»Í¬¡£·ÇÒ×Ê§´æ´¢Æ÷µÄ¿É²ÁÐ´ÊÙÃüÓÉ×î¶ÌÊÙµÄÄÇÒ»×Ö½Ú¾ö¶¨£¬
									²»ÂÛEEPROM»¹ÊÇFLASH¾ùÈç´Ë¡£ÓÐÐ©×öÊý¾Ý´æ´¢µÄ´óÈÝÁ¿FLASHÔòÒÔ»µ¿éµÄ°Ù·Ö±È×÷ÎªÊÙÃüÅÐ¶¨ÒÀ¾Ý£¬ÏÔÈ»·Å¿íÁËºÜ¶à¡£
									
									EEPROM²»·ÖÉÈÇøµÄ£¬·ÖÒ³£¬ÕâÊÇ²»Í¬µÄ¸ÅÄî¡£
									µ£ÐÄ´æ´¢Æ÷ÊÙÃü¿ÉÒÔÓÃFRAM´æ´¢Æ÷£¬Õâ¸öÊÙÃü³¤
									
									
									MCUÉÏµÄEEPROM¶¼ÊÇÄÃFLASHÄ£ÄâµÄ£¬ËùÒÔ¶¼±ê³Æ10Íò´Î²Á³ý¡£
                  ÕæÕýµÄEEPROM¶¼ÊÇ°ÙÍò´Î²Á³ý¡£
									
									
					FRAMÌá¹©Ò»ÖÖÓëRAMÒ»ÖÂµÄÐÔÄÜ,µ«ÓÖÓÐÓëROM Ò»ÑùµÄ·ÇÒ×Ê§ÐÔ¡£ FRAM ¿Ë·þÒÔÉÏ¶þÖÖ¼ÇÒäÌåµÄÈ±ÏÝ²¢ºÏ²¢ËüÃÇµÄÓÅµã£¬ËüÊÇÈ«ÐÂ´´ÔìµÄ²úÆ·£¬Ò»¸ö·ÇÒ×Ê§ÐÔËæ»ú´æÈ¡´¢´æÆ÷¡£
									*/
											//MainProcessTimeAdd(board,1);//Ã¿·ÖÖÓ±ØÐëÒªÑ¹ÈëAT24CxxÄÚÒ»´Î£¬´ËÐ¾Æ¬ÊÙÃüÎª100Íò/1440´ÎÃ¿Ìì=690Ìì£¬´óÔ¼2Äê,added by sjw
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
									
									goto force_exit1;  //Ç¿ÖÆÌø³öÎÞÏÞÑ­»·£¡£¡added by sjw
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
	OSTimeDlyHMSM(0, 0, 0, 20);//´ËÈý¾äÖ¸ÁîÌí¼ÓÉÏºÏÊÊ£¡£¡added by sjw	 2023-12-5 in  tuesday!!
	
  EAST_FZ;
	while(1){
			switch(status){
						case IDLE:
								status=WAIT_TIME;
						    LightSlotFlag=1;
						break;
						
						
						
						case WAIT_TIME://Ç¿ÖÆµÈ´ý500ms£¬Ò»¶¨Ô½¹ý¹â²ÛÎ»ÖÃÁË£¡added by sjw
							  if(LightSlotValue>500){
									  LightSlotFlag=0;
								    LightSlotValue=0;
										status=HIGH;
								}else{
									OSTimeDly(20);
								}
						break;
						
						case HIGH:
							  if(EAST_FK_PIN==0){//¿ªÊ¼ Õì²â  µ½´ï¹â²ÛµÄÎ»ÖÃÁË£¬
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
									
									goto force_exit2;  //Ç¿ÖÆÌø³öÎÞÏÞÑ­»·£¡£¡added by sjw
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
									MainProcessTimeAdd(board,2);//Ã¿´Î×ßÍê±ØÐëÒªÑ¹ÈëAT24CxxÄÚÒ»´Î£¬´ËÐ¾Æ¬ÊÙÃüÎª100Íò/2880´ÎÃ¿Ìì=347Ìì£¬´óÔ¼1Äê,added by sjw
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
									MainProcessTimeAdd(board,3);//Ã¿´Î×ßÍê±ØÐëÒªÑ¹ÈëAT24CxxÄÚÒ»´Î£¬´ËÐ¾Æ¬ÊÙÃüÎª100Íò/2880´ÎÃ¿Ìì=347Ìì£¬´óÔ¼1Äê,added by sjw
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
									MainProcessTimeAdd(board,4);//Ã¿´Î×ßÍê±ØÐëÒªÑ¹ÈëAT24CxxÄÚÒ»´Î£¬´ËÐ¾Æ¬ÊÙÃüÎª100Íò/2880´ÎÃ¿Ìì=347Ìì£¬´óÔ¼1Äê,added by sjw
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
								 if(p_timemu->second>=58){//1·ÖÖÓ½«Ê±¼äÑ¹ÈëAT24CÀïÃæ£¡£¡
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
								 if(p_timemu->second>=58){//1·ÖÖÓ½«Ê±¼äÑ¹ÈëAT24CÀïÃæ£¡£¡
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
								 if(p_timemu->second>=58){//1·ÖÖÓ½«Ê±¼äÑ¹ÈëAT24CÀïÃæ£¡£¡
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
								 if(p_timemu->second>=58){//1·ÖÖÓ½«Ê±¼äÑ¹ÈëAT24CÀïÃæ£¡£¡
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
						if((p_timemu->second==58)&&(!flag)){//1·ÖÖÓ½«Ê±¼äÑ¹ÈëAT24CÀïÃæ£¡£¡
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
1¡¢Á½¿é°å×ÓÒ»¶¨Òª¹²µØ¡£

2¡¢Á½¿é°å×ÓµÄMOSIÓëMISO²»ÐèÒª½»²æÁ¬½Ó¡£

Á¬Ïß·½Ê½
SCK----SCK
MOSI----MOSI
MISO----MISO
NSS----NSS

*/
void SPI1_Init (void)
{

		GPIO_InitTypeDef  GPIO_InitStructure;
		SPI_InitTypeDef   SPI_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE); //Ê¹ÄÜSPI2¡¢PB


	
	//ÅäÖÃMOSI¶Ë¿Ú
		GPIO_InitStructure.GPIO_Pin = SPI_MOSI_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI_MOSI_GPIO_PORT,&GPIO_InitStructure);
	
	
	
	   //ÅäÖÃMISO¶Ë¿Ú
		GPIO_InitStructure.GPIO_Pin = SPI_MISO_GPIO_PIN;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(SPI_MISO_GPIO_PORT,&GPIO_InitStructure);
		
		
		
		 //ÅäÖÃSCK¶Ë¿Ú
		GPIO_InitStructure.GPIO_Pin = SPI_SCK_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI_SCK_GPIO_PORT,&GPIO_InitStructure);



    //ÅäÖÃCS¶Ë¿Ú
		GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(SPI_CS_PORT,&GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure); //PB12ÅäÖÃ³ÉÍÆÍìÊä³ö £¨CS£©

	
	
	/*
	  SPI1->DR=0x98;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6? | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure); //PA5¡¢PA6¡¢PA7,¸´ÓÃÍÆÍìÊä³ö£¨SCK¡¢MISO¡¢MOSI£©
*/







		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //Ë«¹¤Ä£Ê½
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave ; 											//SPI   xÄ£Ê½
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 									//8bitÊý¾Ý

		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //CLK¿ÕÏÐÊ±Îª¸ßµçÆ½
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //CLKÉÏÉýÑØ²ÉÑù£¬ÒòÎªÉÏÉýÑØÊÇµÚ¶þ¸ö±ßÑØ¶¯×÷£¬ËùÒÔÒ²¿ÉÒÔÀí½âÎªµÚ¶þ¸ö±ßÑØ²ÉÑù

		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                         	//Æ¬Ñ¡ÓÃÈí¼þ¿ØÖÆ
		//NSSÐÅºÅÓÉÓ²¼þ£¨NSS¹Ü½Å£©»¹ÊÇÈí¼þ£¨Ê¹ÓÃSSIÎ»£©¹ÜÀí:ÄÚ²¿NSSÐÅºÅÓÐSSIÎ»¿ØÖÆ

		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; 	//SPIÆµÂÊ£º72M/4 = 18M
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 									//¸ßÎ»ÔÚÇ°
		SPI_InitStructure.SPI_CRCPolynomial = 7; 														//crc7£¬stm32spi´øÓ²¼þecc
		SPI_Init(SPI1, &SPI_InitStructure);

		SPI_Cmd(SPI1, ENABLE);

		//SPIx_ReadWriteByte(0xff);//Æô¶¯´«Êä



}



INT8U SPIx_ReadWriteByte(INT8U TxData)
{

  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);


  SPI_I2S_SendData(SPI2, TxData);


  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);


  return SPI_I2S_ReceiveData(SPI2);
}			  




/*********************************
*¹¦ÄÜ£º¿ª»ú²ÎÊýÉèÖÃ
*ÊäÈë£º
*********************************/
void StartGetSysParm(void)
 { 
  unsigned int read_data[24],t,check=0; 
  
	  

	 /*
	 //¶ÁÈ¡×ÓÖÓ1Ê±¼ä Ãë  
	 //¶ÁÈ¡×ÓÖÓ1Ê±¼ä ·Ö
	 //¶ÁÈ¡×ÓÖÓ1Ê±¼ä Ê±
	 //¶ÁÈ¡×ÓÖÓ1Ê±¼ä ²½Êý 
	 //Ð£Ñé 
	 
	
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

  Light_start=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR);    //¶ÁÈ¡ÕÕÃ÷¿ªÊ¼Ê±¼ä
  if(Light_start>=24)    Light_start=19;

  Light_end=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR+0x02); //¶ÁÈ¡ÕÕÃ÷½áÊøÊ±¼ä
  if(Light_end>=24)      Light_end=6;

  Light_en=(unsigned char) Eeprom_ReadWord(DATA_START+LIGHT_ADDR+0x04);  //¶ÁÈ¡ÕÕÃ÷Ê¹ÄÜ
  if(Light_en>=2)       Light_en=1;  

  Songs_nummber=(unsigned char) Eeprom_ReadWord(DATA_START+SONG_ADDR);   //¶ÁÈ¡±¨Ê±ÒôÀÖºÅ
  if(Songs_nummber>14)   Songs_nummber=9;

  Strike_nummmber=(unsigned char) Eeprom_ReadWord(DATA_START+STRIKE_ADDR); //¶ÁÈ¡ÇÃÖÓºÅ
  if(Strike_nummmber>11) Strike_nummmber=7;


  for(t=0;t<5;t++)     //¶ÁÈ¡×Ô¶¨Òå±¨Ê±ÒôÀÖ³¤¶È
   {
    Songs_minite[t+10]=(unsigned char) Eeprom_ReadWord(DATA_START+LONG_ADDR+t*2);
    Songs_second[t+10]=(unsigned char) Eeprom_ReadWord(DATA_START+LONG_ADDR+0x10+t*2);

    if(Songs_minite[t+10]>4||Songs_second[t+10]>59)
     {
      Songs_minite[t+10]=1;
      Songs_second[t+10]=30;
     }
   } 

  for(t=0;t<24;t++)    //¶ÁÈ¡±¨Ê±µã
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

  for(t=0;t<2;t++)    //Ê±ÇøÉèÖÃ
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

  read_data[0]=Eeprom_ReadWord(DATA_START+WARN_ADDR);//µç»ú¹ÊÕÏ¼ÇÂ¼
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
*¹¦ÄÜ£ºÕÕÃ÷µçÔ´¿ØÖÆ
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
      if((p_timemu->hour>=Light_Start || p_timemu->hour<Light_End))   //Ô­À´Îªp_timemu->hour<=Light_End £¬ÏÖÐÞ¸ÄÎªp_timemu->hour<Light_End   added by sjw                      
          SSR_ZM_STATUS(1);
      else  
					SSR_ZM_STATUS(0);
     }
   }else 
				SSR_ZM_STATUS(0); 
 }




/*
¹¦ÄÜ£º²¥·ÅMP3
ÊäÈë£ºMP3ÐòºÅ£¬¸ñÊ½Îªmp3_xxxx.mp3
       xxxxÎªMP3ÐòºÅ
			 
			 

ËþÖÓ»ò¼ªÏéÖÓ·¢³ö±¨Ê±Êý¾Ý
24  0F 04 01 0C 4D 50 33 5F 30    30 36 36 2E 4D 50 33 77   --Î÷ÃôËÂÇ°×à£¡ ·¢ËÍ3´Î£¡£¡
24  0F 04 01 0C 4D 50 33 5F 30    30 35 36 2E 4D 50 33 74  ÇÃÖÓnÏÂ         ·¢ËÍ3´Î£¡£¡


24  0F 04 01 0C 4D 50 33 5F 30    30 36 32 2E 4D 50 33 73  ¶«·½ºìÇ°×à£¡    ·¢ËÍ3´Î£¡£¡
24  0F 04 01 0C 4D 50 33 5F 30    30 35 35 2E 4D 50 33 77ÇÃÖÓnÏÂ          ·¢ËÍ3´Î£¡£¡
	 

Ö÷°åµÄCPU¸øMP3Ä£¿éµÄÊý¾ÝÈçÏÂ£º  
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--·¢ËÍ×Ö½ÚÎª60¸ö
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16µãÇ°×à£º
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77   --Î÷ÃôËÂÇ°×à£¡
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		
17µãÇ°×à£º
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$$MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
    24 03 0F 01 1F 12
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 


¿ØÖÆ×Ö·ûASCIIÂë±í
https://www.perfcode.com/p/control-character.html

	
Ö÷°åµÄCPU¸øMP3Ä£¿éµÄÊý¾ÝÈçÏÂ£º  
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w--·¢ËÍ×Ö½ÚÎª60¸ö
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
$     $MP3_0066.MP3w$MP3_0066.MP3w$MP3_0066.MP3w
16µãÇ°×à£º
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
	
	
	
	
35Ãëmp3Ä£¿é·¢£º24 04 00 00 1F 12 24 04 00 0B   16µã
Õû·Ýmp3Ä£¿é·¢£º24 04 00 0B 

35Ãëmp3Ä£¿é·¢£º24 04 00 00 1F 12 24 04 00 0B   17µã
Õû·Ýmp3Ä£¿é·¢£º24 04 00 0B 
	
ÈÎºÎÊ±¶Î±¨Ê±µÄÊ±ºò£¬MP3Ä£¿é¶¼ÊÇ·´À¡¸øÖ÷»úÒÔÉÏÊý¾Ý   added by sjw  
	
µ¥¶À²âÊÔÐ¡°åµÄÊ±ºò£¬Ï¸½ÚÈçÏÂ  9600 £¬n£¬8,1

±ÈÈç£º  41 00 00 00 00 01 00 0D 0A-------------------¹²9¸ö×Ö½Ú,²¥·ÅÎ÷ÃôËÂ
       41 00 00 00 00 02 00 0D 0A-------------------¹²9¸ö×Ö½Ú,²¥·Åpay

*/




/*********************************
*¹¦ ÄÜ£º±¨ Ê± 
*Êä Èë£º
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
	16µãÇ°×à£º
		24 03 0F 01 1F 12 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77   --Î÷ÃôËÂÇ°×à£¡
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
		24 0F 04 01 0C 4D 50 33 5F 30 30 36 36 2E 4D 50 33 77 
	
	ÇÃµãÎÄ¼þ15µã
	24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B 
24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B 
24 0F 04 01 0C 4D 50 33 5F 30 32 38 36 2E 4D 50 33 7B

	 
*/
  switch(mp3_state){
		
			case 0 :      
				 for(k=0;k<24;k++){      
					 if(Report_Time[k]==1){      	 
						report_hour=k;                 //±¨Ê±¿ªÊ¼Ê±   
						report_minute=0;               //±¨Ê±¿ªÊ¼·Ö  

						 
						rythem_number=Rythem_Number;   //Ç°×àÒôÀÖºÅ
						strike_number=Strike_Number;   //ÇÃÖÓÖÓÉùºÅ 
					 
						start_second=59-Rythem_Second[rythem_number];   //±¨Ê±ÆðÊ¼µã        
						start_minite=59-(Rythem_Minite[rythem_number]-report_minute);
						start_hour=report_hour-1;
						 
						if(start_hour>=24) start_hour=23;  
						
						power_on_minite=start_minite-1; //¹¦·ÅµçÔ´¿ªÆôÊ±¼ä
						if(power_on_minite>=60){  
								power_on_minite=59;
								power_on_hour=start_hour-1;
								if(power_on_hour>=24) power_on_hour=23;
						}else 
								power_on_hour=start_hour;  
						
						if((p_timemu->hour==power_on_hour)&&(p_timemu->minute==power_on_minite)){   
							
								SSR_BS_STATUS(1);//¿ªÆôÒôÏìµçÔ´                        
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
           
         SSR_BS_STATUS(0); //¹Ø±Õ±¨Ê±µçÔ´    
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

   ´òÓ¡Ïß³Ì£¬½«´®¿Ú1½ÓÊÕµ½µÄÊý¾Ý´òÓ¡³öÀ´

*********************************************************************************************************
*/


/*

¶ÔÓÚÒ»Ð©Î¥·´³£ÀíµÄÎÊÌâ£¬Ò»°ãÊÖ²áÉÏ¶¼»áÓÐ¶îÍâµÄËµÃ÷ÎªÊ²Ã´»ØÊÂÕâÑù£¬ËùÒÔÊÖ²áºÜÖØÒª£¬
¾Í½ñÌì¶øÑÔ£¬ÎÒ×öÒ»¸öÐ¡ÏîÄ¿Ê±ÓÃµ½ÁËSTM32µÄPB4Õâ¸ö¹Ü½Å£¬È»ºó²ÉÓÃÁËÒ»°ãGPIOµÄÍ¨ÓÃÅäÖÃ£¬µ«ÊÇÔÚµ÷ÊÔÊ±£¬È´·¢ÏÖÕâ¸ö½Å²»ÂÛÔõÑù¶¼²»ÄÜÖÃÎªµÍ£¬
ËùÒÔÎÒ¸Ï½ôÈ¥¿´ÁËÏÂÊÖ²á£¬È»ºó·¢ÏÖPB4¹Ü½Å»¹ÓÐ¸´ÓÃ¹¦ÄÜ£¬ÊÇÒ»¸öJTAGµÄµ÷ÊÔÒý½Å£¬¶øÇÒ¶¨¾¦Ò»¿´£¬»¹·¢ÏÖÕâ¸ö¹Ü½ÅÔÚÉÏµç¸´Î»Ê±»áÄ¬ÈÏÎªµ÷ÊÔÒý½ÅµÄ¹¦ÄÜ£¬
¶øËüµÄ¸´ÓÃ¹¦ÄÜ²ÅÊÇÆÕÍ¨IO¿Ú£¬ÀàËÆµÄ»¹ÓÐPB3/PA13/PA14µÈ¹Ü½Å¶¼ÊÇÒ»Ñù£¬ÒªÓÃ×÷ÆÕÍ¨IO¿Ú£¬ÐèÒªÅäÖÃÎª¸´ÓÃÄ£Ê½¡£

1¡¢±ØÐëÏÈ´ò¿ª¸´ÓÃÊ±ÖÓ£¬ÔÙÊ¹ÓÃº¯Êý½ûÓÃJTAGµ÷ÊÔ£¬·ñÔò¿ÉÄÜ»áÅäÖÃ²»³É¹¦¡£

STM32 PC13 PC14 PC15 PB3 PB4 PA13 PA14 PA15 ×öÆÕÍ¨IO¿Ú±Ê¼Ç
*/
void LedPortSpecialInit(void)
{
		//STM32µÄPB3¡¢PB4¡¢PA15ÓÃ×÷ÆÕÍ¨IO¿ÚÉèÖÃ·½·¨£¬½ûÓÃjtag£¬Ê¹ÓÃSW ×÷Õß£º´´¿Í°¢¿á https://www.bilibili.com/read/cv23389778/ ³ö´¦£ºbilibili
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);      //Ê¹ÄÜPA,PB¶Ë¿ÚÊ±ÖÓ   ×¢ÒâºÍÏÂÒ»¾äµÄË³Ðò£¬±ØÐëÏÈ¿ªÆôAFIOÊ±ÖÓ		
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);    //¶ÔÈý¸öÒý½Å½øÐÐÖØÓ³Éä :  ¸Ä±äÖ¸¶¨¹Ü½ÅµÄÓ³Éä GPIO_Remap_SWJ_JTAGDisable £¬JTAG-DP ½ûÓÃ + SW-DP Ê¹ÄÜ

	//¹Ø±ÕJTAGµÄPB3 PB4 PA15µÄ¹¦ÄÜ£¬×÷ÎªÆÕÍ¨I/O¿ÚÊ¹ÓÃ£¬²»Ó°ÏìSWDµÄÏÂÔØµ÷ÊÔ¡£ ×÷Õß£º´´¿Í°¢¿á https://www.bilibili.com/read/cv23389778/ ³ö´¦£ºbilibili
	
	//¹Ø±ÕJTAGµÄPB3 PB4 PA15µÄ¹¦ÄÜ£¬×÷ÎªÆÕÍ¨I/O¿ÚÊ¹ÓÃ£¬²»Ó°ÏìSWDµÄÏÂÔØµ÷ÊÔ¡£ ×÷Õß£º´´¿Í°¢¿á https://www.bilibili.com/read/cv23389778/ ³ö´¦£ºbilibili


	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);´ò¿ª´ËÖ¸Áîºó£¬PA15¾Í²»ÉÁË¸ÁË£¬£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡added by sjw
	//Ô­Òò²Î¿¼ÒÔÏÂÎÄÕÂ£º   https://blog.csdn.net/weixin_46528483/article/details/113940390
	//ÒòÎªÖ´ÐÐÖ¸ÁîGPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);ºó»¹ÊÇ²»ÄÜÓÃPA15£¡£¡£¡added by sjw
	
	
	//µ¥¶À¹Ø±ÕPB4µÄJTAG¹¦ÄÜ£¬½«PB4×öÎªÆÕÍ¨I/OÊ¹ÓÃ¡£ ×÷Õß£º´´¿Í°¢¿á https://www.bilibili.com/read/cv23389778/ ³ö´¦£ºbilibili
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);       //ÊÍ·ÅJTAG½Å×÷ÎªÆÕÍ¨IO¿Ú, ¸Ä±äÖ¸¶¨¹Ü½ÅµÄÓ³Éä GPIO_Remap_SWJ_Disable SWJ ÍêÈ«½ûÓÃ£¨JTAG+SW-DP£©
}



void LedBsZm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO,ENABLE );
	//PWR_BackupAccessCmd( ENABLE );/* ÔÊÐíÐÞ¸ÄRTCºÍºó±¸¼Ä´æÆ÷*/
	//RCC_LSEConfig( RCC_LSE_OFF ); /* ¹Ø±ÕÍâ²¿µÍËÙÊ±ÖÓ,PC14¡¢PC15¿ÉÒÔÓÃ×÷ÆÕÍ¨IO*/
	//BKP_TamperPinCmd(DISABLE);  /* ¹Ø±ÕÈëÇÖ¼ì²â¹¦ÄÜ,PC13¿ÉÒÔÓÃ×÷ÆÕÍ¨IO ×÷Õß£º´´¿Í°¢¿á https://www.bilibili.com/read/cv23389778/ ³ö´¦£ºbilibili*/

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
	
	//PWR_BackupAccessCmd(DISABLE);/* ½ûÖ¹ÐÞ¸ÄRTCºÍºó±¸¼Ä´æÆ÷*/
    //BKP_ITConfig(DISABLE);       /* ½ûÖ¹TAMPER ÖÐ¶Ï*/ ×÷Õß£º´´¿Í°¢¿á https://www.bilibili.com/read/cv23389778/ ³ö´¦£ºbilibili
	
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
	
	
	 MP3_RESET_STATUS(1);//±ä¸ßºóVS1003Ð¡°å¸´Î»½áÊø£¡£¡  added by  sjw
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
*             LED Á÷Ë®µÆ
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
2£®4 Òº¾§ÏÔÊ¾Ä£¿é 
¡¡¡¡LCD3310Òº¾§ÊÇÒ»¸ö48ÐÐ84ÁÐµÄÒº¾§ÏÔÊ¾Æ÷¡£Æä´øÓÐµÍ¹¦ºÄPCD8544µÄCMOS LCD¿ØÖÆÇý¶¯Æ÷£¬´®ÐÐÊäÈëËÙ¶È×î¸ß¿É´ï4£®O Mb£¯s¡£
ÎªÁËÈÃLCD3310Òº¾§ÄÜ¹»ÏÔÊ¾4ÐÐ12¡Á12µÄºº×Ö£¬ÏµÍ³¿ª±ÙÁËÒ»¸ö6¡Á84×Ö½ÚµÄ»º³åÇø¡£Ð´Òº¾§Ê±¾Í²»ÓÃÖ±½ÓÐ´ÈëLCD3310µÄ¾²Ì¬ DDRAMÁË£¬
¿ÉÒÔÏÈÐ´ÈëÏµÍ³ÎªËü¿ª±ÙµÄÊý¾Ý»º³åÇø£¬×îºóÔÙË¢ÐÂÐÞ¸ÄµÄ²¿·Ö¾Í¿ÉÒÔÏÔÊ¾³öÒªÏÔÊ¾µÄÄÚÈÝ¡£LCD3310µÄ½Ó¿Ú²ÉÓÃSPIÄ£Ê½£¬ÆäµçÂ·ÈçÍ¼6 ËùÊ¾¡£ 

3 Èí¼þÉè¼Æ 
¡¡¡¡Í¼7ÊÇMP3²¥·ÅÆ÷µÄÈí¼þÁ÷³Ì¡£ÏµÍ³Æô¶¯ºó£¬ÏÈ³õÊ¼»¯Ó²¼þÄ£¿é¡£ÓÉµ¥Æ¬»úÍ¨¹ýFAT32ÎÄ¼þÏµÍ³½Ó¿Ú¶ÁÈ¡SD¿¨µÄÒ»Ð©»ù±¾ÐÅÏ¢£¬
ÈçÈÝÁ¿¡¢ÉÈÇø´óÐ¡¡¢FAT ±íÒÔ¼°¸ùÄ¿Â¼ËùÔÚµÄÆðÊ¼ÉÈÇøµÈ¡£Í¨¹ýÕâÐ©ÐÅÏ¢¾Í¿ÉÒÔÕÒ³öSD¿¨ÊÇ·ñÓÐ¿ÉÒÔ²¥·ÅµÄÒôÀÖÎÄ¼þ¡£
ÈôÓÐ£¬µ¥Æ¬»úÍ¨¹ýSPI×ÜÏß·½Ê½¶Á³öÒôÆµÐÅÏ¢£¬²¢½«¸èÇúµÄÂëÁ÷ÐÅÏ¢ËÍÈëµ½VS1003Ð¾Æ¬ÖÐ£¬
Í¨¹ýVS1003½âÂëÐ¾Æ¬¼°ÆäÄÚº¬µÄ¸ßÖÊÁ¿Á¢ÌåÉùDACºÍ¶ú»úÇý¶¯µçÂ·£¬ÊµÏÖMP3¸èÇúµÄ²¥·Å¹¦ÄÜ¡£
ÔÚ°´¼üµÄ¿ØÖÆÏÂ£¬Í¨¹ý LCD3310ÖÐ²Ëµ¥Ñ¡ÏîµÄÑ¡Ôñ£¬ÊµÏÖ¶Ô¸èÇúÑ¡Ôñ¼°ÒôÁ¿¿ØÖÆµÈ¹¦ÄÜ£»
ÔÚ²¥·ÅµÄÍ¬Ê±£¬LCD3310ÉÏÏÔÊ¾µÄÐÅÏ¢³ý¸èÇúÃû³ÆÍâ£¬»¹°üÀ¨½ø¶ÈºÍÒôÁ¿µÈ¡£ 


¡¡¡¡¾­¹ýÔËÐÐ²âÊÔ£¬ÏµÍ³¿ÉÒÔÕý³£Á÷³©µØ²¥·Å³ö320 kb£¯sµÄ¸ßÒôÖÊMP3ÒôÀÖÎÄ¼þ£¬
¶øÇÒÔÚÊ¹ÓÃ500 mAï®µç³ØµÄÇé¿öÏÂ£¬¿ÉÒÔÁ¬ÐøÕý³£µØ²¥·Å³¤´ï10¸öÐ¡Ê±¡£¿É¼û£¬Æä¹¦ºÄ±È½ÏµÍ¡£ 

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
//	PWR_BackupAccessCmd(ENABLE);//ÔÊÐíÐÞ¸ÄRTC ºÍºó±¸¼Ä´æÆ÷ 
//    RCC_LSEConfig(RCC_LSE_OFF);//¹Ø±ÕÍâ²¿µÍËÙÍâ²¿Ê±ÖÓÐÅºÅ¹¦ÄÜ ºó£¬PC13 PC14 PC15 ²Å¿ÉÒÔµ±ÆÕÍ¨IOÓÃ¡£ 
//    PWR_BackupAccessCmd(DISABLE);//½ûÖ¹ÐÞ¸Äºó±¸¼Ä´æÆ÷ 
	

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
*¹¦ÄÜ£º¿ª»ú²ÎÊýÉèÖÃ
*ÊäÈë£º
*********************************/

static	void GPIO_I2C_Config(void)
{
	struct tm now;
	
	 iic_sw_init();
	// get_iic_setting();//¶ÁÈ¡×ÓÖÓÊ±¼ä¡¢±¨Ê±¿ª¹ØÉè¶¨µÄÐ¡Ê±¡¢±¨Ê±Ç°×à¼°ÖÓÉùºÍÕÕÃ÷¿ª¹ØµÄÉè¶¨£¡£¡added by sjw
	

	
}








static	void GPIO_Key_Config(void)
{
	
	EXTI_InitTypeDef EXTI_InitStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;//½«PE10°ó¶¨ÔÚEXTI_Line10ÉÏ×÷ÎªPPSÐÅºÅµÄÊäÈë£¬ÏÂÑØÑØÓÐÐ§!!added by sjw
	
	
	
	
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE );  //PE10ÎªÊäÈëÖÐ¶Ï£¡£¡
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
  GPIO_InitTypeDef GPIO_InitStructure;//½«PA11×÷ÎªppsÐÅºÅµÄÊäÈë¶Ë!   added by sjw
	
	
	
	
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );  //PA11ÎªÊäÈëÖÐ¶Ï£¡£¡
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







//Ö±½Ó½»»»ÁËµØÖ·ÀïÃæµÄÄÚÈÝ£¬Ò²¾ÍÊÇÖµ£¡£¡
//ÔÚº¯ÊýÄÚ²¿È·Êµ½»»»ÁËÊý¾ÝÄÚÈÝ£¬ÍË³öº¯Êýºó£¬Ã»ÓÐ½»»»£¡£¡
void MainSwapValue(INT16U *p1,INT16U *p2)
{
	INT16U value;
	value=*p1;
	*p1=*p2;
	*p2=value;
}

//Ö±½Ó½»»»ÁËµØÖ·ÀïÃæµÄÄÚÈÝ£¬Ò²¾ÍÊÇÖµ£¡£¡
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

void MainSwapAddr(INT16U **p1,INT16U **p2)//Òª½»»»ÄÚÈÝ£¬¼ä½ÓÓÃ½»»»µØÖ·À´ÊµÏÖ¡£
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
			//return i;//»òÕß¸ÃÓï¾äÒ²¿ÉÒÔ£¡
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

/*Êä³ö¸ñÊ½ÈçÏÂ£º

²úÆ·ÄÚ²¿Flash´óÐ¡Îª£º512K×Ö½Ú£¡ 	 www.armjishu.com

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
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
°æÈ¨ÉùÃ÷£º±¾ÎÄÎªCSDN²©Ö÷¡¸shaohui973¡¹µÄÔ­´´ÎÄÕÂ£¬×ñÑ­CC 4.0 BY-SA°æÈ¨Ð­Òé£¬×ªÔØÇë¸½ÉÏÔ­ÎÄ³ö´¦Á´½Ó¼°±¾ÉùÃ÷¡£
Ô­ÎÄÁ´½Ó£ºhttps://blog.csdn.net/shaohui973/article/details/109627989
hamming weight algorithm(ººÃ÷Ëã·¨)ÒÔ¼°kernelµÄÊµÏÖ
https://blog.csdn.net/shaohui973/article/details/109627989

ººÃ÷¾àÀëÊÇÊ¹ÓÃÔÚÊý¾Ý´«Êä²î´í¿ØÖÆ±àÂëÀïÃæµÄ£¬ººÃ÷¾àÀëÊÇÒ»¸ö¸ÅÄî
¶ÔÁ½¸ö×Ö·û´®½øÐÐÒì»òÔËËã£¬²¢Í³¼Æ½á¹ûÎª1µÄ¸öÊý£¬ÄÇÃ´Õâ¸öÊý¾ÍÊÇººÃ÷¾àÀë¡£
ººÃ÷ÖØÁ¿ÊÇ×Ö·û´®Ïà¶ÔÓÚÍ¬Ñù³¤¶ÈµÄÁã×Ö·û´®µÄººÃ÷¾àÀë£¬Ò²¾ÍÊÇËµ£¬ËüÊÇ×Ö·û´®ÖÐ·ÇÁãµÄÔªËØ¸öÊý£º
¶ÔÓÚ¶þ½øÖÆ×Ö·û´®À´Ëµ£¬¾ÍÊÇ 1 µÄ¸öÊý£¬ËùÒÔ 11101 µÄººÃ÷ÖØÁ¿ÊÇ 4¡£
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
	//ÅäÖÃÐÞ¸Ä²ÎÊýÈçÏÂ:::
	 /*
	 1.½«ÎÄ¼þffconf.hµÄµÚ40ÐÐ  _USE_MKFS         ÉèÖÃÎª  1
	 2.	½«ÎÄ¼þffconf.hµÄµÚ36ÐÐ_USE_STRFUNC	      ÉèÖÃÎª  1
	 
	 3. ½«ÎÄ¼þffconf.hµÄµÚ48ÐÐ_USE_LABEL		      ÉèÖÃÎª  1	
	 
	 4.½«ÎÄ¼þffconf.hµÄµÚ122ÐÐ _FS_RPATH         ÉèÖÃÎª  1	
	 5.½«ÎÄ¼þffconf.hµÄµÚ148ÐÐ	_MULTI_PARTITION	ÉèÖÃÎª  1	
	 
	 7.½«ÎÄ¼þdemo_nand_fatfs.hµÄµÚ27ÐÐ  #define BUF_SIZE				(4*1024)   ÐÞ¸Ä³É(2*1024)
	 
	 8.½«ÎÄ¼þinteger.hµÄµÚ7ÐÐ Ìí¼ÓÉÏ  #define _WIN32             added by sjw
	 9.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ101ÐÐ #define NAND_MAX_ZONE  ÐÞ¸ÄÎª102ÐÐÉÏ£¡
	 10.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ97ÐÐ #define NAND_PAGE_SIZE  ÐÞ¸ÄÎª98ÐÐÉÏ£¡
	 
	 11.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ105ÐÐÆÁ±Î
	 12.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ97ÐÐ#define NAND_PAGE_SIZE             ((uint16_t)0x0800) ÐÞ¸ÄÎª0x0200
	 
	 13.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ99ÐÐ#define NAND_BLOCK_SIZE            ((uint16_t)0x0040) ÐÞ¸ÄÎª0x20
	 
	 14.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ100ÐÐ	#define NAND_ZONE_SIZE           ((uint16_t)0x0400) ÐÞ¸ÄÎª0x1000(4096¸ö¿é)
	 15.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ101ÐÐ#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0040) ÐÞ¸ÄÎª0x10
	 
	 16.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ112ÐÐ#define NAND_ADDR_5					       1ÐÞ¸ÄÎª0
	 17.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ125ÐÐ#define NAND_BLOCK_COUNT			   1024 // ¿é¸öÊý ÐÞ¸Ä³É4096¸ö¿é
   18.½«ÎÄ¼þfamc_nand.hµÄµÚ56ÐÐ#define FLASH_MAX_ADDR 0x7FFFFFF±äÎª0x4000000 ÕâÊÇ64M
	 19.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ108ÐÐ#define NAND_MAX_ZONE       ±äÎª       ((uint16_t)0x0004)
	 20.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ133ÐÐ#define BI_OFFSET				    0		¿éÄÚµÚ1¸öpage±¸ÓÃÇøµÄµÚ1¸ö×Ö½ÚÊÇ»µ¿é±êÖ¾  ±äÎª6
   21.½«ÎÄ¼þbsp_nand_flash.cµÄµÚ1651ÐÐµ½1655ÐÐÆÁ±Î£¡
	 22.½«ÎÄ¼þfamc_nand.hµÄµÚ59ÐÐ#define FLASH_BLOCK_SIZE 0x20000  128k---->16K
	 23.½«ÎÄ¼þbsp_nand_flash.hµÄµÚ137ÐÐ#define VALID_SPARE_SIZE		4±äÎª6		 Êµ¼ÊÊ¹ÓÃµÄ±¸ÓÃÇø´óÐ¡,ÓÃÓÚº¯ÊýÄÚ²¿ÉùÃ÷Êý¾Ý»º³åÇø´óÐ¡ 


	 
	 //K9F1208U0M 64M nand flash ÊÖ²áÔÄ¶ÁÒÔ¼°Ïà¹ØÇý¶¯³ÌÐò·ÖÎö
   //https://blog.csdn.net/hfdghjh/article/details/86776939
	  

	
	//https://blog.csdn.net/xiaoluoshan/article/details/51695121
	//Nandflash K9F1208U0BÑ§Ï°   ´Ë×ÊÁÏ·Ç³£ÊµÓÃ£¡£¡
	
	STM32 IOÄ£Äânand flashµÄ¸ßÊÖÇë½ø
	https://bbs.csdn.net/topics/380034182
	
	
	NAND FLASH´æ´¢Æ÷ÊµÏÖÔÚÏµÍ³ÖÐµÄ¶ÁÐ´ºÍ¿ØÖÆ Ò²¼ä½Ó½éÉÜÁËÄ£Äâgpio¶Ë¿ÚµÄ²Ù×÷Ê±Ðò£¡£¬Ò²Í¦ºÃµÄÁË
	https://www.elecfans.com/d/744442.html
	
	
	//LUT²éÕÒ±íÊµÏÖ¸÷ÖÖRAM¼°ROMÔ­Àí¾«½²
	//https://blog.csdn.net/weiaipan1314/article/details/104327009
	
	//Stm32ÎÄ¼þÏµÍ³FATFS£¨¿ªÊ¼ÓÚ2021-09-09£©
	//https://blog.csdn.net/weixin_51915497/article/details/120201305?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~aggregatepage~first_rank_ecpm_v1~rank_v31_ecpm-7-120201305.pc_agg_new_rank&utm_term=fatfs+fdisk%E4%B8%8Esfd%E7%9A%84%E5%8C%BA%E5%88%AB&spm=1000.2123.3001.4430
	 
	
	
	//https://blog.csdn.net/hanchaoman/article/details/102660884
	//STM32-ÒÆÖ²FATFSµÄNANDFLASHÇý¶¯
	//Ê¹ÓÃÔ­À´°å¿¨×Ô´øµÄ´æ´¢Ð¾Æ¬DF2M8HM£¨ÀïÃæÒÑ¾­ÓÐmp3±¨Ê±ÎÄ¼þÁË£©£¬ÓÃÐÂ103ve²Ù×÷£¬¸ñÊ½»¯Ê§°Ü£¬²¹íE³É¹¦£¡ÏÔÊ¾FR_NOT_READY£¬
	//·ÂÕæ²âÊÔ,·¢ÏÖ1024¸ö¿éÈ«²¿Îª»µ¿é£¬ÒòÎªµ×²ãÎÒÃ»ÓÐ²Ù×÷ÕýÈ·£¡
	//FatFsÑ§Ï°(1)¡ª¡ªÃ¶¾Ù£º·µ»ØÖµFRESULT            https://blog.csdn.net/qq_38318207/article/details/108554207 
	//ÈýÐÇµÚÒ»¸öÄÚ´æÐ¾Æ¬¸ö¸ñÊ½»¯µÄÊ±ºò£¬ºÃ¿éÎª0x0183¸öblock
	/*
		µÚ¸öÄÚ´æÐ¾Æ¬¸ö¸ñÊ½»¯µÄÊ±ºò£¬ºÃ¿éÎª0x18c¸öblock                             µÚ2¸öÄÚ´æÐ¾Æ¬¸ö¸ñÊ½»¯µÄÊ±ºò£¬ºÃ¿éÎª0x3ea¸öblock
		

	
	//https://www.zhihu.com/question/62799132
	//Ò»¸öºÏ¸ñµÄÇ¶ÈëÊ½Èí¼þ¿ª·¢¹¤³ÌÊ¦ÒªÕÆÎÕÄÄÐ©ÖªÊ¶£¿
	
	
	//¡¾ÎÄ¼þÏµÍ³½«¶ÔÎÄ¼þµÄ¿éµÄ²Ù×÷×ª»»Îª¶ÔÎïÀí´æ´¢Æ÷ÉÈÇøµÄ¸÷ÖÖ²Ù×÷¡¿
	//https://blog.csdn.net/hanchaoman/article/details/86607456
	 
	 
	 https://bbs.elecfans.com/jishu_1096766_1_1.html
	 
	 ÔÚµ¥²½µ÷ÊÔÊ±£¬ÕÒµ½´íÎóÎ»ÖÃÊ×ÏÈ£¬½øÈëf_open£¬ÔÚf_openÖÐÓÐfind_volumeº¯Êý£¬
	 ÔÚÕâ¸öº¯ÊýÖÐ£¬´Ó0ÉÈÇø¶ÁÈ¡fatËùÕ¼ÉÈÇø´óÐ¡¡¢Ã¿¸öÉÈÇø×Ö½ÚÊý¡¢fat¸öÊý¡¢¸ùÄ¿Â¼Î»ÖÃµÈÓÐ¹ØÐÅÏ¢£¬²¢ÇÒÈç¹û¸Ãº¯Êý·µ»ØÖµ²»ÊÇFR_OK£¬½«Ö±½ÓÍË³öf_openº¯Êý£»

½øÈëfind_volumeº¯Êý£¬ÔÚfind_volumeº¯ÊýÖÐÓÐÕâÑùÒ»ÐÐ´úÂë£º
fmt = check_f( fs, bsect );²¢ÇÒ¸ù¾Ý·µ»ØÖµ£¬Ò²¾ÍÊÇfmtµÄÖµ£¬À´È·¶¨ÊÇ·ñÎªfatÎÄ¼þÏµÍ³£»

È»ºó½øÈëcheck_fsº¯Êý£¬·¢ÏÖÏÈ½øÐÐmove_window²Ù×÷£¬È»ºóÅÐ¶Ï½áÎ²ÊÇ·ñÎª0XAA55£¬¿ªÍ·µÄÌø×ªÖ¸ÁîÊÇ·ñÊÇ0XEB 0X** 0X90£¬È»ºóÅÐ¶ÏÊÇ·ñÕÒµ½FAT»òÊÇFAT3×ÖÑù£»

ÔÚmove_windowº¯ÊýÖÐ£¬Ö÷ÒªÊµÏÖÁËfs->win[]ÖÐµÄÊý¾Ý»ØÐ´£¬È»ºóÖØÐÂ¶ÁÈ¡Ö¸¶¨ÉÈÇøµÄÄÚÈÝ£¬
½á¹û£¬ÎÊÌâ¾Í³öÀ´ÕâÀï£¬ÔÚ¶ÁÈ¡0ÉÈÇøµÄÄÚÈÝÊ±£¬¶ÁÈ¡µÄÄÚÈÝ´íÎó£¬Òò´Ë¾Íµ¼ÖÂÁËÔÚcheck_fsº¯ÊýÖÐÅÐ¶ÏÉÈÇø½áÎ²ÊÇ·ñÊÇ0XAA55Ê±£¬·¢ÉúÁË´íÎó£¬·´»ØÁË2£¬
È»ºóÔÚfind_volumeº¯ÊýÖÐ£¬ÅÐ¶ÏfmtÊ±£¬·µ»ØÁËFR_NO_FILESYSTEM£»
	 

stm32f2ÏµÁÐ£º»ùÓÚNAND FLASHÖ®ÉÏµÄFatfsµÄÒÆÖ²   ´ËÎÄË¼Ïë¿ÉÒÔ½è¼ø added by sjw
http://blog.sina.com.cn/s/blog_c5c2bd470102v2p2.html
	 
	 
	 
	
		
		
		STM32 USB²¿·ÖÖÐ¶Ïº¯Êý¼òÒª·ÖÎö
		https://blog.csdn.net/yxfabcdefg/article/details/52336070?locationNum=4&fps=1
		
		
		
		
		http://www.elecfans.com/emb/arm/20171106575725.html
		
		
		stm32f103 usbÇý¶¯µçÄÔÎÞ·¨Ê¶±ð½â¾ö°ì·¨£º
¡¡¡¡1¡¢usbËùÊ¹ÓÃµÄIO¿ÚÔÚÉèÖÃÎªusbºó×Ô¶¯·ÖÅä¹¦ÄÜ£¬²»ÐèÒªÔÙÉèÖÃ£¬Ò»¶¨ÒªÉèÖÃµÄ»°»á±»ºöÂÔ£¬ËùÒÔÒ²Ã»Ê²Ã´Ó°Ïì¡£

¡¡¡¡2¡¢usbÊ±ÖÓÅäÖÃÖ»ÓÐÁ½ÖÖ¿ÉÓÃ£ºÖ÷Æµ72M£¬usbÊ±ÖÓ1.5·ÖÆµ£»Ö÷Æµ48M£¬usbÊ±ÖÓ1·ÖÆµ¡£

¡¡¡¡3¡¢PA12£¨USBP / D+£©Ò»¶¨Òª½Ó1.5kµÄÉÏÀ­µç×è£¬ÓÃÓÚµçÄÔÊ¶±ðÉè±¸£¬¹Ù·½¿âÊ¹ÓÃÁËlO¿Ú¿ØÖÆÁËÉÏÀ­£¬
       ÕâÑù·½±ãÈí¼þ¿ØÖÆ¶Ï¿ªÓëÖØÐÂÁ¬½Ó£¬Ö±½ÓÉÏÀ­µ½µçÔ´Ò²ÊÇ¿ÉÒÔµÄ£¬²»¹ýÐèÒª¶Ï¿ªºÍÖØÐÂÁ¬½ÓÊ±Ö»ÄÜÊÖ¶¯²å°Î¡£

¡¡¡¡4¡¢stm32f103µÄcanºÍusb²»ÄÜÍ¬Ê±Ê¹ÓÃ£¬canµÄÊ±ÖÓ´ò¿ªºó£¬µçÄÔ¾Í»áÊ¶±ð²»³öusbÉè±¸£¬
        ËùÒÔÁ½¸ö¹¦ÄÜ¶¼ÒªÓÃµ½µÄ»°£¬»¹ÊÇ»»³Éf105»òf107£¬ÕâÁ½ÖÖÐÍºÅÊÇ¿ÉÒÔÍ¬Ê±Ê¹ÓÃµÄ¡£
		
		
	
	
	
	
		
		»ùÓÚSTM32µÄUSBÃ¶¾Ù¹ý³ÌÑ§Ï°±Ê¼Ç£¨×ª£©
		https://www.cnblogs.com/erhu-67786482/p/10790814.htm	
		
		
		
		
		
		https://blog.csdn.net/qq236106303/article/details/8177568
		»ùÓÚSTM32µÄUSBÃ¶¾Ù¹ý³ÌÑ§Ï°±Ê¼Ç(¶þ)
		½ÓÏÂÀ´½éÉÜUSBÉè±¸µÄÃ¶¾Ù£¬Ã¶¾Ù¾ÍÊÇ´ÓÉè±¸¶ÁÈ¡¸÷ÖÖÃèÊö·ûÐÅÏ¢£¬ÕâÑùÖ÷»ú¾Í¿ÉÒÔ¸ù¾ÝÕâÐ©ÐÅÏ¢À´¼ÓÔØºÏÊÊµÄÇý¶¯£¬´Ó¶øÖªµÀÊÇÊ²Ã´ÑùµÄÉè±¸£¬ÈçºÎ½øÐÐÍ¨ÐÅ¡£
		Ã¶¾Ù¹ý³ÌÊ¹ÓÃµÄÊÇ¿ØÖÆ´«Êä¡£¿ØÖÆ´«Êä¿ÉÒÔ±£Ö¤Êý¾ÝµÄÕýÈ·ÐÔ¡£¿ØÖÆ´«Êä·ÖÈý¸ö¹ý³Ì£º½¨Á¢¹ý³Ì£¬¿ÉÑ¡Êý¾Ý¹ý³Ì¼°×´Ì¬¹ý³Ì
		
				
		STM32-USBÑ§Ï°±Ê¼Ç£¨Ò»£© USB»ù´¡
		https://www.doc88.com/p-505935487642.html

		STM32 USB²¿·ÖÖÐ¶Ïº¯Êý¼òÒª·ÖÎö
		https://blog.csdn.net/yxfabcdefg/article/details/52336070

		https://www.pianshen.com/article/97651154818/

		»ùÓÚSTM32µÄUSBÃ¶¾Ù¹ý³ÌÑ§Ï°±Ê¼Ç(¶þ)
		https://blog.csdn.net/qq236106303/article/details/8177568   ºÍ
		http://www.360doc.com/content/17/1025/06/6889381_697883568.shtml
		http://www.360doc.com/content/17/1025/06/6889381_697884130.shtml


		»ùÓÚSTM32µÄUSBÃ¶¾Ù¹ý³ÌÑ§Ï°±Ê¼Ç(Èý)
		https://blog.csdn.net/qq236106303/article/details/8179005


		»ùÓÚSTM32µÄUSBÃ¶¾Ù¹ý³ÌÑ§Ï°±Ê¼Ç(ËÄ)
		https://blog.csdn.net/qq236106303/article/details/8181336?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_default&utm_relevant_index=2

    
		USBÃ¶¾Ù¹ý³Ì·ÖÎö
		https://blog.csdn.net/duan_xiaosu/article/details/68930643
		ÔÚÕâ¸öÍøÕ¾µÄÄÚÈÝ¿ÉÒÔ°ïÖúÎÒ½«usbÃ¶¾ÙµÄ¸÷¸ö×Ö¶ÎÀí½âÍ¸ÇÐ£¡·Ç³£²»´íµÄºÃÎÄÕÂ£¡
		
		

	 
	
	 
	 	
  		bDeviceState È«¾Ö±äÁ¿ÔÚusb_pwr.cÖÐ¶¨Òå£¬ÓÃÓÚ±íÊ¾USB DeviceµÄ×´Ì¬ 
	  typedef enum _DEVICE_STATE
		{
			UNCONNECTED,
			ATTACHED,
			POWERED,
			SUSPENDED,
			ADDRESSED,
			CONFIGURED
		} DEVICE_STATE;
  	
  	  	
  	//»¹ÓÐÒ»¸öUSB¿ª¹Ø
  	// Enable the SDIO AHB Clock 
		
	*/
	
	
	 




