//
// Created by Lao·Zhu on 2021/9/5.
//

#ifndef MINIFOC_HARDWARE_FLASH_H_
#define MINIFOC_HARDWARE_FLASH_H_

void fmc_erase_page(void);
void fmc_program_word(unsigned int addr, unsigned int data);
unsigned int fmc_read_word(unsigned int addr);

#endif //MINIFOC_HARDWARE_FLASH_H_
