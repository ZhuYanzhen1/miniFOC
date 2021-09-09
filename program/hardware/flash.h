//
// Created by Lao·Zhu on 2021/9/5.
//

#ifndef MINIFOC_HARDWARE_FLASH_H_
#define MINIFOC_HARDWARE_FLASH_H_

void flash_write_parameters(void);
void flash_read_parameters(void);
void flash_erase_page(void);
void flash_program_word(unsigned int addr, unsigned int *data, unsigned short counter);
unsigned int flash_read_word(unsigned int addr);

#endif //MINIFOC_HARDWARE_FLASH_H_
