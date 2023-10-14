//
// Created by LaoZhu on 2023/10/15.
//

#include "flash.h"
#include "system.h"

#define USER_PARAMETER_START_ADDRESS 0x0800FC00UL  // Start at 63kb

void flash_write64word(uint32_t* buffer) {
    FLASH_Enhance_Mode(DISABLE);
    FLASH_Unlock_Fast();
    FLASH_ErasePage_Fast(USER_PARAMETER_START_ADDRESS);
    FLASH_ProgramPage_Fast(USER_PARAMETER_START_ADDRESS, buffer);
    FLASH_Lock_Fast();
    FLASH_Lock();
    FLASH_Enhance_Mode(ENABLE);
}

void flash_read64word(uint32_t* buffer) {
    for (uint32_t counter = 0; counter < 64; counter++)
        buffer[counter] = *(uint32_t*)(USER_PARAMETER_START_ADDRESS + 4 * counter);
}
