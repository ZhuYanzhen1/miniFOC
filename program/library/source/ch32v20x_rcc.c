/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v20x_rcc.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file provides all the RCC firmware functions.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/ 
#include "ch32v20x_rcc.h"

/* RCC registers bit address in the alias region */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)

/* BDCTLR Register */
#define BDCTLR_OFFSET             (RCC_OFFSET + 0x20)

/* RCC registers bit mask */

/* CTLR register bit mask */
#define CTLR_HSEBYP_Reset           ((uint32_t)0xFFFBFFFF)
#define CTLR_HSEBYP_Set             ((uint32_t)0x00040000)
#define CTLR_HSEON_Reset            ((uint32_t)0xFFFEFFFF)
#define CTLR_HSEON_Set              ((uint32_t)0x00010000)
#define CTLR_HSITRIM_Mask           ((uint32_t)0xFFFFFF07)

#define CFGR0_PLL_Mask              ((uint32_t)0xFFC0FFFF) 

#define CFGR0_PLLMull_Mask          ((uint32_t)0x003C0000)
#define CFGR0_PLLSRC_Mask           ((uint32_t)0x00010000)
#define CFGR0_PLLXTPRE_Mask         ((uint32_t)0x00020000)
#define CFGR0_SWS_Mask              ((uint32_t)0x0000000C)
#define CFGR0_SW_Mask               ((uint32_t)0xFFFFFFFC)
#define CFGR0_HPRE_Reset_Mask       ((uint32_t)0xFFFFFF0F)
#define CFGR0_HPRE_Set_Mask         ((uint32_t)0x000000F0)
#define CFGR0_PPRE1_Reset_Mask      ((uint32_t)0xFFFFF8FF)
#define CFGR0_PPRE1_Set_Mask        ((uint32_t)0x00000700)
#define CFGR0_PPRE2_Reset_Mask      ((uint32_t)0xFFFFC7FF)
#define CFGR0_PPRE2_Set_Mask        ((uint32_t)0x00003800)
#define CFGR0_ADCPRE_Reset_Mask     ((uint32_t)0xFFFF3FFF)
#define CFGR0_ADCPRE_Set_Mask       ((uint32_t)0x0000C000)

/* RSTSCKR register bit mask */
#define RSTSCKR_RMVF_Set            ((uint32_t)0x01000000)

/* CFGR2 register bit mask */
#define CFGR2_PREDIV1SRC            ((uint32_t)0x00010000)
#define CFGR2_PREDIV1               ((uint32_t)0x0000000F)
#define CFGR2_PREDIV2               ((uint32_t)0x000000F0)
#define CFGR2_PLL2MUL               ((uint32_t)0x00000F00)
#define CFGR2_PLL3MUL               ((uint32_t)0x0000F000)

/* RCC Flag Mask */
#define FLAG_Mask                   ((uint8_t)0x1F)

/* INTR register byte 2 (Bits[15:8]) base address */
#define INTR_BYTE2_ADDRESS          ((uint32_t)0x40021009)

/* INTR register byte 3 (Bits[23:16]) base address */
#define INTR_BYTE3_ADDRESS          ((uint32_t)0x4002100A)

/* CFGR0 register byte 4 (Bits[31:24]) base address */
#define CFGR0_BYTE4_ADDRESS         ((uint32_t)0x40021007)

/* BDCTLR register base address */
#define BDCTLR_ADDRESS              (PERIPH_BASE + BDCTLR_OFFSET)


static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

/*********************************************************************
 * @fn      RCC_DeInit
 *
 * @brief   Resets the RCC clock configuration to the default reset state.
 *          Note-
 *          HSE can not be stopped if it is used directly or through the PLL as system clock.
 * @return  none
 */
void RCC_DeInit(void)
{
  RCC->CTLR |= (uint32_t)0x00000001;
  RCC->CFGR0 &= (uint32_t)0xF8FF0000;  
  RCC->CTLR &= (uint32_t)0xFEF6FFFF;
  RCC->CTLR &= (uint32_t)0xFFFBFFFF;
  RCC->CFGR0 &= (uint32_t)0xFF80FFFF;
  RCC->INTR = 0x009F0000;
}

/*********************************************************************
 * @fn      RCC_HSEConfig
 *
 * @brief   Configures the External High Speed oscillator (HSE).
 *
 * @param   RCC_HSE -
 *            RCC_HSE_OFF - HSE oscillator OFF.
 *            RCC_HSE_ON - HSE oscillator ON.
 *            RCC_HSE_Bypass - HSE oscillator bypassed with external clock.
 *            Note-
 *            HSE can not be stopped if it is used directly or through the PLL as system clock.
 * @return  none
 */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
  RCC->CTLR &= CTLR_HSEON_Reset;
  RCC->CTLR &= CTLR_HSEBYP_Reset;

  switch(RCC_HSE)
  {
    case RCC_HSE_ON:
      RCC->CTLR |= CTLR_HSEON_Set;
      break;
      
    case RCC_HSE_Bypass:
      RCC->CTLR |= CTLR_HSEBYP_Set | CTLR_HSEON_Set;
      break;
      
    default:
      break;
  }
}

/*********************************************************************
 * @fn      RCC_WaitForHSEStartUp
 *
 * @brief   Waits for HSE start-up.
 *
 * @return  READY - HSE oscillator is stable and ready to use.
 *          NoREADY - HSE oscillator not yet ready.
 */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
	
  ErrorStatus status = NoREADY;
  FlagStatus HSEStatus = RESET;
  
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
  {
    status = READY;
  }
  else
  {
    status = NoREADY;
  }  
	
  return (status);
}

/*********************************************************************
 * @fn      RCC_AdjustHSICalibrationValue
 *
 * @brief   Adjusts the Internal High Speed oscillator (HSI) calibration value.
 *
 * @param   HSICalibrationValue - specifies the calibration trimming value.
 *                    This parameter must be a number between 0 and 0x1F.
 *
 * @return  none
 */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CTLR;
  tmpreg &= CTLR_HSITRIM_Mask;
  tmpreg |= (uint32_t)HSICalibrationValue << 3;
  RCC->CTLR = tmpreg;
}

/*********************************************************************
 * @fn      RCC_HSICmd
 *
 * @brief   Enables or disables the Internal High Speed oscillator (HSI).
 *
 * @param   NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_HSICmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->CTLR |= (1<<0);
	}
	else{
		RCC->CTLR &= ~(1<<0);		
	}
}

/*********************************************************************
 * @fn      RCC_PLLConfig
 *
 * @brief   Configures the PLL clock source and multiplication factor.
 *
 * @param   RCC_PLLSource - specifies the PLL entry clock source.
 *            RCC_PLLSource_HSI_Div2 - HSI oscillator clock divided by 2
 *        selected as PLL clock entry.
 *            RCC_PLLSource_PREDIV1 - PREDIV1 clock selected as PLL clock
 *        entry.
 *          RCC_PLLMul - specifies the PLL multiplication factor.
 *            This parameter can be RCC_PLLMul_x where x:[2,16].
 *              RCC_PLLMul_2
 *              RCC_PLLMul_3
 *              RCC_PLLMul_4
 *              RCC_PLLMul_5
 *              RCC_PLLMul_6
 *              RCC_PLLMul_7
 *              RCC_PLLMul_8
 *              RCC_PLLMul_9
 *              RCC_PLLMul_10
 *              RCC_PLLMul_11
 *              RCC_PLLMul_12
 *              RCC_PLLMul_13
 *              RCC_PLLMul_14
 *              RCC_PLLMul_15
 *              RCC_PLLMul_16
 *              RCC_PLLMul_18
 *
 * @return  none
 */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;

  tmpreg &= CFGR0_PLL_Mask;
  tmpreg |= RCC_PLLSource | RCC_PLLMul;
  RCC->CFGR0 = tmpreg;
}

/*********************************************************************
 * @fn      RCC_PLLCmd
 *
 * @brief   Enables or disables the PLL.
 *          Note-The PLL can not be disabled if it is used as system clock.
 *          
 *
 * @param   NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_PLLCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->CTLR |= (1<<24);
	}
	else{
		RCC->CTLR &= ~(1<<24);		
	}
}

/*********************************************************************
 * @fn      RCC_SYSCLKConfig
 *
 * @brief   Configures the system clock (SYSCLK).
 *
 * @param   RCC_SYSCLKSource - specifies the clock source used as system clock.
 *            RCC_SYSCLKSource_HSI - HSI selected as system clock.
 *            RCC_SYSCLKSource_HSE - HSE selected as system clock.
 *            RCC_SYSCLKSource_PLLCLK - PLL selected as system clock.
 *
 * @return  none
 */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_SW_Mask;
  tmpreg |= RCC_SYSCLKSource;
  RCC->CFGR0 = tmpreg;
}

/*********************************************************************
 * @fn      RCC_GetSYSCLKSource
 *
 * @brief   Returns the clock source used as system clock.
 *
 * @return  0x00 - HSI used as system clock.
 *          0x04 - HSE used as system clock.
 *          0x08 - PLL used as system clock.
 */
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR0 & CFGR0_SWS_Mask));
}

/*********************************************************************
 * @fn      RCC_HCLKConfig
 *
 * @brief   Configures the AHB clock (HCLK).
 *
 * @param   RCC_SYSCLK - defines the AHB clock divider. This clock is derived from
 *        the system clock (SYSCLK).
 *            RCC_SYSCLK_Div1 - AHB clock = SYSCLK.
 *            RCC_SYSCLK_Div2 - AHB clock = SYSCLK/2.
 *            RCC_SYSCLK_Div4 - AHB clock = SYSCLK/4.
 *            RCC_SYSCLK_Div8 - AHB clock = SYSCLK/8.
 *            RCC_SYSCLK_Div16 - AHB clock = SYSCLK/16.
 *            RCC_SYSCLK_Div64 - AHB clock = SYSCLK/64.
 *            RCC_SYSCLK_Div128 - AHB clock = SYSCLK/128.
 *            RCC_SYSCLK_Div256 - AHB clock = SYSCLK/256.
 *            RCC_SYSCLK_Div512 - AHB clock = SYSCLK/512.
 *
 * @return  none
 */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_HPRE_Reset_Mask;
  tmpreg |= RCC_SYSCLK;
  RCC->CFGR0 = tmpreg;
}

/*********************************************************************
 * @fn      RCC_PCLK1Config
 *
 * @brief   Configures the Low Speed APB clock (PCLK1).
 *
 * @param   RCC_HCLK - defines the APB1 clock divider. This clock is derived from
 *        the AHB clock (HCLK).
 *            RCC_HCLK_Div1 - APB1 clock = HCLK.
 *            RCC_HCLK_Div2 - APB1 clock = HCLK/2.
 *            RCC_HCLK_Div4 - APB1 clock = HCLK/4.
 *            RCC_HCLK_Div8 - APB1 clock = HCLK/8.
 *            RCC_HCLK_Div16 - APB1 clock = HCLK/16.
 *
 * @return  none
 */
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_PPRE1_Reset_Mask;
  tmpreg |= RCC_HCLK;
  RCC->CFGR0 = tmpreg;
}

/*********************************************************************
 * @fn      RCC_PCLK2Config
 *
 * @brief   Configures the High Speed APB clock (PCLK2).
 *
 * @param   RCC_HCLK - defines the APB2 clock divider. This clock is derived from
 *        the AHB clock (HCLK).
 *            RCC_HCLK_Div1 - APB2 clock = HCLK.
 *            RCC_HCLK_Div2 - APB2 clock = HCLK/2.
 *            RCC_HCLK_Div4 - APB2 clock = HCLK/4.
 *            RCC_HCLK_Div8 - APB2 clock = HCLK/8.
 *            RCC_HCLK_Div16 - APB2 clock = HCLK/16.
 * @return  none
 */
void RCC_PCLK2Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_PPRE2_Reset_Mask;
  tmpreg |= RCC_HCLK << 3;
  RCC->CFGR0 = tmpreg;
}

/*********************************************************************
 * @fn      RCC_ITConfig
 *
 * @brief   Enables or disables the specified RCC interrupts.
 *
 * @param   RCC_IT - specifies the RCC interrupt sources to be enabled or disabled.
 *            RCC_IT_LSIRDY - LSI ready interrupt.
 *            RCC_IT_LSERDY - LSE ready interrupt.
 *            RCC_IT_HSIRDY - HSI ready interrupt.
 *            RCC_IT_HSERDY - HSE ready interrupt.
 *            RCC_IT_PLLRDY - PLL ready interrupt.
 *          NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    *(__IO uint8_t *) INTR_BYTE2_ADDRESS |= RCC_IT;
  }
  else
  {
    *(__IO uint8_t *) INTR_BYTE2_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

/*********************************************************************
 * @fn      RCC_USBCLKConfig
 *
 * @brief   Configures the USB clock (USBCLK).
 *
 * @param    RCC_USBCLKSource: specifies the USB clock source. This clock is
 *        derived from the PLL output.
 *             RCC_USBCLKSource_PLLCLK_Div1 - PLL clock selected as USB clock source(48Mhz).
 *             RCC_USBCLKSource_PLLCLK_Div2 - PLL clock selected as USB clock source(96MHz).
 *             RCC_USBCLKSource_PLLCLK_Div3 - PLL clock selected as USB clock source(144MHz).
 *             RCC_USBCLKSource_PLLCLK_Div5 - PLL clock selected as USB clock source(240MHz).
 *
 * @return  none
 */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource)
{
    RCC->CFGR0 &= ~((uint32_t)3<<22);
    RCC->CFGR0 |= RCC_USBCLKSource<<22;
}

/*********************************************************************
 * @fn      RCC_ADCCLKConfig
 *
 * @brief   Configures the ADC clock (ADCCLK).
 *
 * @param   RCC_PCLK2 - defines the ADC clock divider. This clock is derived from
 *        the APB2 clock (PCLK2).
 *          RCC_PCLK2_Div2 - ADC clock = PCLK2/2.
 *          RCC_PCLK2_Div4 - ADC clock = PCLK2/4.
 *          RCC_PCLK2_Div6 - ADC clock = PCLK2/6.
 *          RCC_PCLK2_Div8 - ADC clock = PCLK2/8.
 *
 * @return  none
 */
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_ADCPRE_Reset_Mask;
  tmpreg |= RCC_PCLK2;
  RCC->CFGR0 = tmpreg;
}

/*********************************************************************
 * @fn      RCC_LSEConfig
 *
 * @brief   Configures the External Low Speed oscillator (LSE).
 *
 * @param   RCC_LSE - specifies the new state of the LSE.
 *            RCC_LSE_OFF - LSE oscillator OFF.
 *            RCC_LSE_ON - LSE oscillator ON.
 *            RCC_LSE_Bypass - LSE oscillator bypassed with external clock.
 *
 * @return  none
 */
void RCC_LSEConfig(uint8_t RCC_LSE)
{
  *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_OFF;
  *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_OFF;
	
  switch(RCC_LSE)
  {
    case RCC_LSE_ON:
      *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_ON;
      break;
      
    case RCC_LSE_Bypass:
      *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_Bypass | RCC_LSE_ON;
      break;            
      
    default:
      break;      
  }
}

/*********************************************************************
 * @fn      RCC_LSICmd
 *
 * @brief   Enables or disables the Internal Low Speed oscillator (LSI).
 *          Note-
 *          LSI can not be disabled if the IWDG is running.
 *
 * @param   NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_LSICmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->RSTSCKR |= (1<<0);
	}
	else{
		RCC->RSTSCKR &= ~(1<<0);		
	}	
}

/*********************************************************************
 * @fn      RCC_RTCCLKConfig
 *
 * @brief   Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
 *
 * @param   RCC_RTCCLKSource - specifies the RTC clock source.
 *            RCC_RTCCLKSource_LSE - LSE selected as RTC clock.
 *            RCC_RTCCLKSource_LSI - LSI selected as RTC clock.
 *            RCC_RTCCLKSource_HSE_Div128 - HSE clock divided by 128 selected as RTC clock.
 *         Note-   
 *           Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
 * @return  none
 */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  RCC->BDCTLR |= RCC_RTCCLKSource;
}

/*********************************************************************
 * @fn      RCC_RTCCLKCmd
 *
 * @brief   This function must be used only after the RTC clock was selected
 *        using the RCC_RTCCLKConfig function.
 *
 * @param   NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->BDCTLR |= (1<<15);
	}
	else{
		RCC->BDCTLR &= ~(1<<15);		
	}	
}

/*********************************************************************
 * @fn      RCC_GetClocksFreq
 *
 * @brief   The result of this function could be not correct when using
 *        fractional value for HSE crystal.
 *
 * @param   RCC_Clocks - pointer to a RCC_ClocksTypeDef structure which will hold
 *        the clocks frequencies.
 *
 * @return  none
 */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

    tmp = RCC->CFGR0 & CFGR0_SWS_Mask;

    switch (tmp)
    {
      case 0x00:
        RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
        break;

      case 0x04:
        RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
        break;

      case 0x08:
        pllmull = RCC->CFGR0 & CFGR0_PLLMull_Mask;
        pllsource = RCC->CFGR0 & CFGR0_PLLSRC_Mask;

        pllmull = ( pllmull >> 18) + 2;

        if(pllmull == 17) pllmull = 18;


        if (pllsource == 0x00)
        {
          if(EXTEN->EXTEN_CTR & EXTEN_PLL_HSI_PRE){
              RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE) * pllmull;
          }
          else{
              RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >>1) * pllmull;
          }
        }
        else
        {
#if defined (CH32V20x_D8W)
          if((RCC->CFGR0 & (3<<22)) == (3<<22))
          {
              RCC_Clocks->SYSCLK_Frequency = ((HSE_VALUE>>1)) * pllmull;
          }
          else
#endif
          if ((RCC->CFGR0 & CFGR0_PLLXTPRE_Mask) != (uint32_t)RESET)
          {
#if defined (CH32V20x_D8) || defined (CH32V20x_D8W)
              RCC_Clocks->SYSCLK_Frequency = ((HSE_VALUE>>2) >> 1) * pllmull;
#else
            RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE >> 1) * pllmull;
#endif
          }
          else
          {
#if defined (CH32V20x_D8) || defined (CH32V20x_D8W)
              RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE>>2) * pllmull;
#else
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE * pllmull;
#endif

          }
        }

        break;

      default:
        RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
        break;
    }

    tmp = RCC->CFGR0 & CFGR0_HPRE_Set_Mask;
    tmp = tmp >> 4;
    presc = APBAHBPrescTable[tmp];
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
    tmp = RCC->CFGR0 & CFGR0_PPRE1_Set_Mask;
    tmp = tmp >> 8;
    presc = APBAHBPrescTable[tmp];
    RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    tmp = RCC->CFGR0 & CFGR0_PPRE2_Set_Mask;
    tmp = tmp >> 11;
    presc = APBAHBPrescTable[tmp];
    RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    tmp = RCC->CFGR0 & CFGR0_ADCPRE_Set_Mask;
    tmp = tmp >> 14;
    presc = ADCPrescTable[tmp];
    RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

/*********************************************************************
 * @fn      RCC_AHBPeriphClockCmd
 *
 * @brief   Enables or disables the AHB peripheral clock.
 *
 * @param   RCC_AHBPeriph - specifies the AHB peripheral to gates its clock.
 *            RCC_AHBPeriph_DMA1.
 *            RCC_AHBPeriph_DMA2.
 *            RCC_AHBPeriph_SRAM.
 *            RCC_AHBPeriph_CRC.
 *            RCC_AHBPeriph_OTG_FS
 *          Note-
 *          SRAM  clock can be disabled only during sleep mode.
 *          NewState: ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->AHBPCENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBPCENR &= ~RCC_AHBPeriph;
  }
}

/*********************************************************************
 * @fn      RCC_APB2PeriphClockCmd
 *
 * @brief   Enables or disables the High Speed APB (APB2) peripheral clock.
 *
 * @param   RCC_APB2Periph - specifies the APB2 peripheral to gates its clock.
 *            RCC_APB2Periph_AFIO.
 *            RCC_APB2Periph_GPIOA.
 *            RCC_APB2Periph_GPIOB.
 *            RCC_APB2Periph_GPIOC.
 *            RCC_APB2Periph_GPIOD.
 *            RCC_APB2Periph_GPIOE
 *            RCC_APB2Periph_ADC1.
 *            RCC_APB2Periph_ADC2
 *            RCC_APB2Periph_TIM1.
 *            RCC_APB2Periph_SPI1.
 *            RCC_APB2Periph_TIM8
 *            RCC_APB2Periph_USART1.
 *          NewState - ENABLE or DISABLE
 *
 * @return  none
 */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB2PCENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2PCENR &= ~RCC_APB2Periph;
  }
}

/*********************************************************************
 * @fn      RCC_APB1PeriphClockCmd
 *
 * @brief   Enables or disables the Low Speed APB (APB1) peripheral clock.
 *
 * @param   RCC_APB1Periph - specifies the APB1 peripheral to gates its clock.
 *            RCC_APB1Periph_TIM2.
 *            RCC_APB1Periph_TIM3.
 *            RCC_APB1Periph_TIM4.
 *            RCC_APB1Periph_TIM5
 *            RCC_APB1Periph_WWDG.
 *            RCC_APB1Periph_SPI2.
 *            RCC_APB1Periph_USART2.
 *            RCC_APB1Periph_USART3.
 *            RCC_APB1Periph_UART4
 *            RCC_APB1Periph_I2C1.
 *            RCC_APB1Periph_I2C2.
 *            RCC_APB1Periph_USB.
 *            RCC_APB1Periph_CAN1.
 *            RCC_APB1Periph_BKP.
 *            RCC_APB1Periph_PWR.
 *          NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB1PCENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1PCENR &= ~RCC_APB1Periph;
  }
}

/*********************************************************************
 * @fn      RCC_APB2PeriphResetCmd
 *
 * @brief   Forces or releases High Speed APB (APB2) peripheral reset.
 *
 * @param   RCC_APB2Periph - specifies the APB2 peripheral to reset.
 *            RCC_APB2Periph_AFIO.
 *            RCC_APB2Periph_GPIOA.
 *            RCC_APB2Periph_GPIOB.
 *            RCC_APB2Periph_GPIOC.
 *            RCC_APB2Periph_GPIOD.
 *            RCC_APB2Periph_GPIOE
 *            RCC_APB2Periph_ADC1.
 *            RCC_APB2Periph_ADC2
 *            RCC_APB2Periph_TIM1.
 *            RCC_APB2Periph_SPI1.
 *            RCC_APB2Periph_TIM8
 *            RCC_APB2Periph_USART1.
 *          NewState - ENABLE or DISABLE
 *
 * @return  none
 */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB2PRSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2PRSTR &= ~RCC_APB2Periph;
  }
}

/*********************************************************************
 * @fn      RCC_APB1PeriphResetCmd
 *
 * @brief   Forces or releases Low Speed APB (APB1) peripheral reset.
 *
 * @param   RCC_APB1Periph - specifies the APB1 peripheral to reset.
 *            RCC_APB1Periph_TIM2.
 *            RCC_APB1Periph_TIM3.
 *            RCC_APB1Periph_TIM4.
 *            RCC_APB1Periph_TIM5
 *            RCC_APB1Periph_WWDG.
 *            RCC_APB1Periph_SPI2.
 *            RCC_APB1Periph_USART2.
 *            RCC_APB1Periph_USART3.
 *            RCC_APB1Periph_UART4
 *            RCC_APB1Periph_I2C1.
 *            RCC_APB1Periph_I2C2.
 *            RCC_APB1Periph_USB.
 *            RCC_APB1Periph_CAN1.
 *            RCC_APB1Periph_BKP.
 *            RCC_APB1Periph_PWR.
 *          NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB1PRSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1PRSTR &= ~RCC_APB1Periph;
  }
}

/*********************************************************************
 * @fn      RCC_BackupResetCmd
 *
 * @brief   Forces or releases the Backup domain reset.
 *
 * @param   NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_BackupResetCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->BDCTLR |= (1<<16);
	}
	else{
		RCC->BDCTLR &= ~(1<<16);		
	}		
}

/*******************************************************************************
* Function Name  : RCC_ClockSecuritySystemCmd
* Description    : Enables or disables the Clock Security System.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/	
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->CTLR |= (1<<19);
	}
	else{
		RCC->CTLR &= ~(1<<19);		
	}		
}

/*********************************************************************
 * @fn      RCC_MCOConfig
 *
 * @brief   Selects the clock source to output on MCO pin.
 *
 * @param   RCC_MCO - specifies the clock source to output.
 *            RCC_MCO_NoClock - No clock selected.
 *            RCC_MCO_SYSCLK - System clock selected.
 *            RCC_MCO_HSI - HSI oscillator clock selected.
 *            RCC_MCO_HSE - HSE oscillator clock selected.
 *            RCC_MCO_PLLCLK_Div2 - PLL clock divided by 2 selected.
 *
 * @return  none
 */
void RCC_MCOConfig(uint8_t RCC_MCO)
{
  *(__IO uint8_t *) CFGR0_BYTE4_ADDRESS = RCC_MCO;
}

/*********************************************************************
 * @fn      RCC_GetFlagStatus
 *
 * @brief   Checks whether the specified RCC flag is set or not.
 *
 * @param   RCC_FLAG - specifies the flag to check.
 *            RCC_FLAG_HSIRDY - HSI oscillator clock ready.
 *            RCC_FLAG_HSERDY - HSE oscillator clock ready.
 *            RCC_FLAG_PLLRDY - PLL clock ready.
 *            RCC_FLAG_PLL2RDY - PLL2 clock ready.
 *            RCC_FLAG_PLL3RDY - PLL3 clock ready.
 *            RCC_FLAG_LSERDY - LSE oscillator clock ready.
 *            RCC_FLAG_LSIRDY - LSI oscillator clock ready.
 *            RCC_FLAG_PINRST - Pin reset.
 *            RCC_FLAG_PORRST - POR/PDR reset.
 *            RCC_FLAG_SFTRST - Software reset.
 *            RCC_FLAG_IWDGRST - Independent Watchdog reset.
 *            RCC_FLAG_WWDGRST - Window Watchdog reset.
 *            RCC_FLAG_LPWRRST - Low Power reset.
 *
 * @return  FlagStatus - SET or RESET.
 */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
	
  FlagStatus bitstatus = RESET;
  tmp = RCC_FLAG >> 5;
	
  if (tmp == 1)            
  {
    statusreg = RCC->CTLR;
  }
  else if (tmp == 2)       
  {
    statusreg = RCC->BDCTLR;
  }
  else                    
  {
    statusreg = RCC->RSTSCKR;
  }

  tmp = RCC_FLAG & FLAG_Mask;
	
  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*********************************************************************
 * @fn      RCC_ClearFlag
 *
 * @brief   Clears the RCC reset flags.
 *          Note-   
 *          The reset flags are: RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST,
 *          RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
 * @return  none
 */
void RCC_ClearFlag(void)
{
  RCC->RSTSCKR |= RSTSCKR_RMVF_Set;
}

/*********************************************************************
 * @fn      RCC_GetITStatus
 *
 * @brief   Checks whether the specified RCC interrupt has occurred or not.
 *
 * @param   RCC_IT - specifies the RCC interrupt source to check.
 *            RCC_IT_LSIRDY - LSI ready interrupt.
 *            RCC_IT_LSERDY - LSE ready interrupt.
 *            RCC_IT_HSIRDY - HSI ready interrupt.
 *            RCC_IT_HSERDY - HSE ready interrupt.
 *            RCC_IT_PLLRDY - PLL ready interrupt.
 *            RCC_IT_PLL2RDY - PLL2 ready interrupt.
 *            RCC_IT_PLL3RDY - PLL3 ready interrupt.
 *            RCC_IT_CSS - Clock Security System interrupt.
 *
 * @return  ITStatus - SET or RESET.
 */

ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;

  if ((RCC->INTR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*********************************************************************
 * @fn      RCC_ClearITPendingBit
 *
 * @brief   Clears the RCC's interrupt pending bits.
 *
 * @param   RCC_IT - specifies the interrupt pending bit to clear.
 *            RCC_IT_LSIRDY - LSI ready interrupt.
 *            RCC_IT_LSERDY - LSE ready interrupt.
 *            RCC_IT_HSIRDY - HSI ready interrupt.
 *            RCC_IT_HSERDY - HSE ready interrupt.
 *            RCC_IT_PLLRDY - PLL ready interrupt.
 *            RCC_IT_PLL2RDY - PLL2 ready interrupt.
 *            RCC_IT_PLL3RDY - PLL3 ready interrupt.
 *            RCC_IT_CSS - Clock Security System interrupt.
 *
 * @return  none
 */
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  *(__IO uint8_t *) INTR_BYTE3_ADDRESS = RCC_IT;
}

/*********************************************************************
 * @fn      RCC_ADCCLKADJcmd
 *
 * @brief   Enable ADC clock duty cycle adjustment.
 *
 * @param   NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void RCC_ADCCLKADJcmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->CFGR0 |= (1<<31);
  }
  else
  {
    RCC->CFGR0 &= ~(1<<31);
  }
}

/*********************************************************************
 * @fn      RCC_ETHDIVConfig
 *
 * @brief   Configures the ETH clock.
 *
 * @param   RCC_ETHPRE_Div - defines the USBHS clock divider.
 *            RCC_ETHCLK_Div1 - ETH clock = AHB/1.
 *            RCC_ETHCLK_Div2 - ETH clock = AHB/2.
 *
 * @return  none
 */
void RCC_ETHDIVConfig(uint32_t RCC_ETHPRE_Div)
{
    RCC->CFGR0 &= ~((uint32_t)1<<28);
    RCC->CFGR0 |= RCC_ETHPRE_Div<<28;
}



