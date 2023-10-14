#ifndef MINIFOC_SYSTEM_SYSTEM_H_
#define MINIFOC_SYSTEM_SYSTEM_H_

#include "ch32v20x.h"
#include "config.h"

void system_config(void);
void delayus(uint32_t xus);
void delayms(uint32_t xms);

#endif  // MINIFOC_SYSTEM_SYSTEM_H_
