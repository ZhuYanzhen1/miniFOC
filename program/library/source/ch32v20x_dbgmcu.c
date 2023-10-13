/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v20x_dbgmcu.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file provides all the DBGMCU firmware functions.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "ch32v20x_dbgmcu.h"

#define IDCODE_DEVID_MASK    ((uint32_t)0x0000FFFF)

/*********************************************************************
 * @fn      DBGMCU_GetREVID
 *
 * @brief   Returns the device revision identifier.
 *
 * @return  Revision identifier.
 */
uint32_t DBGMCU_GetREVID(void)
{
	return ((*(uint32_t *)0x1FFFF704) >> 16);
}

/*********************************************************************
 * @fn      DBGMCU_GetDEVID
 *
 * @brief   Returns the device identifier.
 *
 * @return  Device identifier.
 */
uint32_t DBGMCU_GetDEVID(void)
{
	return ((*(uint32_t *)0x1FFFF704) & IDCODE_DEVID_MASK);
}

/*********************************************************************
 * @fn      __get_DEBUG_CR
 *
 * @brief   Return the DEBUGE Control Register
 *
 * @return  DEBUGE Control value
 */
uint32_t __get_DEBUG_CR(void)
{
	uint32_t result;

	__asm volatile("csrr %0,""0x7C0" : "=r"(result));
	return (result);
}

/*********************************************************************
 * @fn      __set_DEBUG_CR
 *
 * @brief   Set the DEBUGE Control Register
 *
 * @param   value  - set DEBUGE Control value
 *
 * @return  none
 */
void __set_DEBUG_CR(uint32_t value)
{
	__asm volatile("csrw 0x7C0, %0" : : "r"(value));
}


/*********************************************************************
 * @fn      DBGMCU_Config
 *
 * @brief   Configures the specified peripheral and low power mode behavior
 *        when the MCU under Debug mode.
 *
 * @param   DBGMCU_Periph - specifies the peripheral and low power mode.
 *            DBGMCU_IWDG_STOP - Debug IWDG stopped when Core is halted
 *            DBGMCU_WWDG_STOP - Debug WWDG stopped when Core is halted
 *            DBGMCU_TIM1_STOP - TIM1 counter stopped when Core is halted
 *            DBGMCU_TIM2_STOP - TIM2 counter stopped when Core is halted
 *          NewState - ENABLE or DISABLE.
 *
 * @return  none
 */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
	uint32_t val;

	if(NewState != DISABLE)
	{
		__set_DEBUG_CR(DBGMCU_Periph);
	}
	else
	{
		val = __get_DEBUG_CR();
		val &= ~(uint32_t)DBGMCU_Periph;
		__set_DEBUG_CR(val);
	}

}
/*********************************************************************
 * @fn      DBGMCU_GetCHIPID
 *
 * @brief   Returns the CHIP identifier.
 *
 * @return Device identifier.
 *          ChipID List-
 *	CH32V203C8U6-0x203005x0
 * 	CH32V203C8T6-0x203105x0
 *  CH32V203K8T6-0x203205x0
 *  CH32V203C6T6-0x203305x0
 *  CH32V203K6T6-0x203505x0
 *  CH32V203G6U6-0x203605x0
 *  CH32V203G8R6-0x203B05x0
 *  CH32V203F8U6-0x203E05x0
 *  CH32V203F6P6-0x203705x0-0x203905x0
 *  CH32V203F8P6-0x203A05x0
 *  CH32V203RBT6-0x203405xC
 *  CH32V208WBU6-0x208005xC
 *  CH32V208RBT6-0x208105xC
 *  CH32V208CBU6-0x208205xC
 *  CH32V208GBU6-0x208305xC
 */
uint32_t DBGMCU_GetCHIPID( void )
{
	return( *( uint32_t * )0x1FFFF704 );
}
