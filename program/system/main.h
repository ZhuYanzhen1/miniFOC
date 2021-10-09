/**************************************************************************//**
  \file     main.h
  \brief    main function Header File
  \author   Lao·Zhu
  \version  V1.0.1
  \date     9. October 2021
 ******************************************************************************/

#ifndef MINIFOC_MAIN_H_
#define MINIFOC_MAIN_H_

//////////////// System ////////////////
#include "gd32f1x0.h"
#include "system.h"
#include "config.h"
#include "error.h"

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
#include "report.h"

#endif  // MINIFOC_MAIN_H_
