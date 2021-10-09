/**************************************************************************//**
  \file     config.h
  \brief    used to place important parameter configurations for users
  \author   Lao·Zhu
  \version  V1.0.1
  \date     9. October 2021
 ******************************************************************************/

#ifndef MINIFOC__CONFIG_H_
#define MINIFOC__CONFIG_H_

/*! \brief bus voltage is 8.4V */
#define VBUS            8.4f
/*! \brief set BLDC polar pairs to 7 */
#define POLAR_PAIRS     7
/*! \brief SC60228 resolution is 2^8 = 4096 */
#define ENCODER_RESO    4096
/*! \brief set calibrate torque to 0.3 */
#define CALI_TORQUE     0.3f

/*! \brief set UART baud rate to 115200 */
#define UART_BAUDRATE   115200
/*! \brief set PWM frequency to 20kHz */
#define PWM_FREQUENCY   20
/*! \brief set FOC loop frequency to 8kHz */
#define TIM2_FREQUENCY  8
/*! \brief set speed/angle PID loop frequency to 100Hz */
#define TIM13_FREQUENCY 100
/*! \brief set speed update frequency to 200Hz */
#define SPEED_UP_FREQ   200
/*! \brief set SPI frequency to 72 / 16 = 4.5MHz */
#define SPI_PRESCALE    SPI_PSC_16

/*! \brief UART preemption priority set to 1 */
#define UART_PRIORITY   1
/*! \brief TIMER2 preemption priority set to 2 */
#define TIM2_PRIORITY   2
/*! \brief TIMER13 preemption priority set to 3 */
#define TIM13_PRIORITY  3

/*! \brief User flash space start address, 1KB user flash */
#define FMC_WRITE_START_ADDR    0x08007C00UL

#endif //MINIFOC__CONFIG_H_
