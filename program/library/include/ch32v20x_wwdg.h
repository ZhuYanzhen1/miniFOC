/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v20x_wwdg.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file contains all the functions prototypes for the WWDG
 *                      firmware library.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#ifndef __CH32V20x_WWDG_H
#define __CH32V20x_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch32v20x.h"

/* WWDG_Prescaler */
#define WWDG_Prescaler_1    ((uint32_t)0x00000000)
#define WWDG_Prescaler_2    ((uint32_t)0x00000080)
#define WWDG_Prescaler_4    ((uint32_t)0x00000100)
#define WWDG_Prescaler_8    ((uint32_t)0x00000180)

void       WWDG_DeInit(void);
void       WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void       WWDG_SetWindowValue(uint8_t WindowValue);
void       WWDG_EnableIT(void);
void       WWDG_SetCounter(uint8_t Counter);
void       WWDG_Enable(uint8_t Counter);
FlagStatus WWDG_GetFlagStatus(void);
void       WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif
