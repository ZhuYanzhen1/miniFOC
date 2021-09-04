//
// Created by Lao·Zhu on 2021/8/24.
//

#ifndef MINIFOC__CONFIG_H_
#define MINIFOC__CONFIG_H_

#define VBUS            12.0f       // Bus voltage is 12V
#define POLAR_PAIRS     7           // BLDC motor has 7 polar pairs
#define ENCODER_RESO    2048        // Encoder resolution is 2^7=2048

#define UART_BAUDRATE   115200      // UART baudrate set to 115200
#define PWM_FREQUENCY   20          // PWM frequency set to 20kHz
#define TIM2_FREQUENCY  5           // timer2 interrupt frequency set to 5kHz
#define TIM13_FREQUENCY 1           // timer13 interrupt frequency set to 1kHz
#define SPI_PRESCALE    SPI_PSC_16  // SPI frequency is 72 / 16 = 4.5MHz

#define UART_PRIORITY   1           // UART preemption priority set to 1
#define TIM2_PRIORITY   2           // TIMER2 preemption priority set to 3
#define TIM13_PRIORITY  3           // TIMER13 preemption priority set to 2

#endif //MINIFOC__CONFIG_H_
