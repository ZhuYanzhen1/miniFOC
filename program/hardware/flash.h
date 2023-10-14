//
// Created by LaoZhu on 2023/10/15.
//

#ifndef MINIFOC_HARDWARE_FLASH_H_
#define MINIFOC_HARDWARE_FLASH_H_

#include "stdint.h"

void flash_write64word(uint32_t* buffer);
void flash_read64word(uint32_t* buffer);

#endif  //MINIFOC_HARDWARE_FLASH_H_
