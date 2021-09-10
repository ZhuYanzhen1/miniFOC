//
// Created by Lao·Zhu on 2021/8/20.
//

#ifndef MINIFOC_MAIN_H_
#define MINIFOC_MAIN_H_

//////////////// System ////////////////
#include "gd32f1x0.h"
#include "system.h"
#include "config.h"

/////////////// Hardware ///////////////
#include "led.h"
#include "uart.h"
#include "timer.h"
#include "spi.h"
#include "flash.h"

/////////////// Algorithm ///////////////
#include "foc.h"
#include "encoder.h"
#include "fast_math.h"
#include "filter.h"
#include "pid.h"

#endif  // MINIFOC_MAIN_H_
