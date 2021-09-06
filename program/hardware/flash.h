//
// Created by Lao·Zhu on 2021/9/5.
//

#ifndef MINIFOC_HARDWARE_FLASH_H_
#define MINIFOC_HARDWARE_FLASH_H_

void fmc_erase_pages(void);
void fmc_program(unsigned int addr, unsigned int data);
unsigned int fmc_readword(unsigned int addr);

#endif //MINIFOC_HARDWARE_FLASH_H_
