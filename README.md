![LOGO](https://raw.githubusercontent.com/ZhuYanzhen1/miniFOC/main/image/LOGO.png)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![Version](https://img.shields.io/badge/Version-1.0.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;English / [中文](https://github.com/ZhuYanzhen1/miniFOC/blob/main/README_CN.md)

&nbsp;&nbsp;&nbsp;&nbsp;Are you still buying a DC brushless motor drive module for more than 10￥? Are you still worried about the high noise, low response speed and low life of brush motor? Let's take a look at this project, a FOC brushless motor control scheme that can be done for 20￥!  **miniFOC** has built-in torque closed-loop controller to provide you with a brushless motor controller that can be controlled through 3-wire serial port. The project is planned to complete the development of basic functions by the end of August 2021. The software and hardware design fully comply with the AGPL-3.0 License.

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

|    Open source solution    |   **miniFOC**    | [simpleFOC](https://github.com/simplefoc/Arduino-SimpleFOCShield) | [ODrive](https://github.com/odriverobotics/ODrive) |
| :------------------------: | :----------: | :----------------------------------------------------------: | :------------------------------------------------: |
|      Microcontroller       | GD32F130G6U6 |                          ATmega328P                          |                   STM32F405RGT6                    |
|        Driver chip         |    EG2133    |                            L6234                             |                      DRV8301                       |
|     PID loop frequency     |    10kHz     |                            830Hz                             |                        8kHz                        |
| Wheather have current loop |      No      |                              No                              |                        Yes                         |
|       Driving power        |     90W      |                             120W                             |                        960W                        |
|    Cost price (approx.)    |     20¥      |                             100¥                             |                        300¥                        |

&nbsp;&nbsp;&nbsp;&nbsp;As can be seen from the above table, the scheme adopted by **miniFOC** can achieve high performance at low cost. At the same time, due to the re selection according to the domestic supply chain, the selection of devices is not so limited, and there are many alternatives. In the case of chip supply shortage in 2021, the cost of FOC can be reduced to about 20¥, which also proves the cost optimization degree and great potential of the project.

***

### Performance Parameter 

+ Input voltage range: 5V ~ 18V (you can modify the circuit according to the tutorial here to adapt to higher voltage).
+ Maximum driving current: 5A (you can modify the circuit according to the tutorial here to achieve greater driving current).
+ Detailed parameters of FOC: no current loop control, SVPWM (Space Vector Pulse Width Modulation) is adopted.
+ Communication parameters: UART baud rate is 115200, and [Mid Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/Mid%20Capacity/README.md) is used for data transmission.
+  Microcontroller parameters: Cortex-M3 core, 48MHz frequency, 32KB FLASH, 4KB SRAM. 

***

### Development Environment 

+ EDA Tool: [EasyEDA](https://easyeda.com/) (the standard free license is adopted, and there is no license dispute).
+ Compiler tool chain: gcc-arm-none-eabi 10-2020-q4-major
+ Programming tool: OpenOCD 0.11.0-1
+ Integrated development tools: CLion 2021.2 #212.4746.93
+ Operating system and tool chain: 
  + Win10 + MinGW + CLion + gcc-arm-none-eabi + OpenOCD
  + Ubuntu20.04 + make + cmake + gcc-arm-none-eabi + OpenOCD

***

### Getting Start

Please refer to the [wiki page](https://github.com/ZhuYanzhen1/miniFOC/wiki) of this project for getting started。

We also provide the [domestic image](https://gitee.com/zhuyanzhen1/mini-foc) address.

***

### Bugs & Feature Requests

Please report bugs and request features using the [Issue Tracker](https://github.com/ZhuYanzhen1/miniFOC/issues) and follow these request:

1. Tab highlight when on different tab.
2. Don’t let the update disappear if the window is not in focus.

***

### License

The source code is released under a [AGPL-3.0 License](https://github.com/ZhuYanzhen1/miniFOC/blob/main/LICENSE).

**Affiliation：AcmeTech<br>
Author: Zhu Yanzhen<br>
Maintainer：YanzhenZhu, 2208213223@qq.com**

The product has been tested under Windows 10 and Ubuntu 18.04 and 20.04. This is research code, expect that it changes often and any fitness for a particular purpose is disclaimed.