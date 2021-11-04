/**************************************************************************//**
  \file     flash.h
  \brief    this is the header file of flash.c.
  \author   Lao·Zhu
  \version  V1.0.1
  \date     10. October 2021
 ******************************************************************************/

#ifndef MINIFOC_HARDWARE_FLASH_H_
#define MINIFOC_HARDWARE_FLASH_H_

void flash_write_parameters(unsigned char flag);
void flash_read_parameters(void);
void flash_erase_page(void);
void flash_program_word(unsigned int addr, unsigned int *data, unsigned short counter);
unsigned int flash_read_word(unsigned int addr);

#endif //MINIFOC_HARDWARE_FLASH_H_
