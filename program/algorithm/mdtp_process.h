//
// Created by LaoZhu on 2023/10/15.
//

#ifndef MINIFOC_ALGORITHM_MDTP_PROCESS_H_
#define MINIFOC_ALGORITHM_MDTP_PROCESS_H_

#include "stdint.h"

void mdtp_data_transmit(uint8_t pid, const uint8_t* data);
void mdtp_callback_handler(uint8_t pid, uint8_t* buffer);

#endif  //MINIFOC_ALGORITHM_MDTP_PROCESS_H_
