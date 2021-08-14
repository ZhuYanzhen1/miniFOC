# miniFOC

![Version](https://img.shields.io/badge/Version-1.0.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-GPL-blue.svg)

English/[中文](https://github.com/ZhuYanzhen1/miniFOC/blob/main/README_CN.md)

***

### Brief Introduction

&nbsp;&nbsp;&nbsp;&nbsp;This open source project aims to realize a FOC (Field Oriented Control) scheme that can be implemented in China and at low cost. The components selected in the example circuit are domestic chips. FOC has many advantages in controlling BLDC (Brushless Direct Current) motor, mainly including the following advantages:

1. FOC has no speed limit at all, and can realize accurate control at any speed.
2. The reversing performance of FOC is extremely excellent, and the forward and reverse switching can be very smooth at the highest speed.
3. FOC can also perform braking control in the form of energy recovery.
4. FOC can realize three closed-loop control of torque, speed and position.
5. The noise of FOC driver will be much lower and the efficiency will be much higher than that of electric regulation.

&nbsp;&nbsp;&nbsp;&nbsp;However, due to the large amount of calculation and complex principle of FOC, a high-cost controller is required, which also makes FOC not popularized and used in many scenarios. After half a year's research and iteration, I deeply optimized the code involving a large number of calculations in FOC, and re selected it according to the domestic supply chain. I hope this open source project can help domestic developers use BLDC motors with excellent performance and contribute to the open source community.

***

### Comparison Of Open Source Solutions

|    Open source solution    |   miniFOC    | [simpleFOC](https://github.com/simplefoc/Arduino-SimpleFOCShield) | [ODrive](https://github.com/odriverobotics/ODrive) |
| :------------------------: | :----------: | :----------------------------------------------------------: | :------------------------------------------------: |
|           MCU(s)           | GD32F130G6U6 |                          ATmega328P                          |                   STM32F405RGT6                    |
|        Driver chip         |    EG2133    |                            L6234                             |                      DRV8301                       |
|     PID loop frequency     |    10kHz     |                            830Hz                             |                        8kHz                        |
| Wheather have current loop |      No      |                              No                              |                        Yes                         |
|       Driving power        |     90W      |                             120W                             |                        960W                        |
|    Cost price (approx.)    |     20¥      |                             100¥                             |                        300¥                        |

***

### Performance Parameter 

1. Input voltage range: 5V ~ 18V (you can modify the circuit according to the tutorial here to adapt to higher voltage).
2. Maximum driving current: 5A (you can modify the circuit according to the tutorial here to achieve greater driving current).
3. Detailed parameters of FOC: no current loop control, SVPWM (Space Vector Pulse Width Modulation) is adopted.
4. Communication parameters: serial communication baud rate is 115200, and [Mid Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/Mid%20Capacity/README.md) is used for data transmission

***

### Bugs & Feature Requests

Please report bugs and request features using the [Issue Tracker](https://github.com/ZhuYanzhen1/miniFOC/issues) and follow these request:

1. Tab highlight when on different tab.
2. Don’t let the update disappear if the window is not in focus.

***

### License

The source code is released under a [GPL3.0 License](https://github.com/ZhuYanzhen1/miniFOC/blob/main/LICENSE).

**Affiliation：AcmeTech<br>
Author: Zhu Yanzhen<br>
Maintainer：YanzhenZhu, 2208213223@qq.com**

The product has been tested under Windows 10 and Ubuntu 18.04 and 20.04. This is research code, expect that it changes often and any fitness for a particular purpose is disclaimed.