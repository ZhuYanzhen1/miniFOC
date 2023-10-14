//
// Created by LaoZhu on 2023/10/13.
//

#ifndef MINIFOC_HARDWARE_SPI_H_
#define MINIFOC_HARDWARE_SPI_H_

#include "stdint.h"

void spi2_config(void);
void spi2_send_data(uint16_t data);

#endif  //MINIFOC_HARDWARE_SPI_H_
