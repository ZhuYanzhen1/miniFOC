![LOGO](https://raw.githubusercontent.com/ZhuYanzhen1/miniFOC/main/docs/image/LOGO.png)

&nbsp;&nbsp;&nbsp;&nbsp;![Version](https://img.shields.io/badge/Version-1.1.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;English / [中文](https://github.com/ZhuYanzhen1/miniFOC/blob/main/README_CN.md)

&nbsp;&nbsp;&nbsp;&nbsp;Are you still buying a DC brush motor drive module in about 3<span>$</span>? Are you still worried about the high noise in addition to the already low response speed and life? Allow me to present you our project, miniFOC---- a FOC brushless motor control scheme that can get you the most bang for your buck, for just 3 <span>$</span>!  **miniFOC** has a built-in torque closed-loop controller so that you can control a brushless motor with a 3-wire UART port. The software and hardware design are fully compliant with the AGPL-3.0 open source license.

** Note: miniFOC V2 version is under development to support current loop and sensorless FOC algorithm, please look forward to it. **

***

### Brief Introduction

&nbsp;&nbsp;&nbsp;&nbsp;This open-source project aims to accomplish a FOC(Field Oriented Control) scheme that is operatable with minimum costs in China. The components selected in the example circuit are all manufactured in China. FOC possesses various advantages when it comes to controlling BLCD (Brushless Direct Current) motor; some of the benefits are as follows:

1. FOC has no speed limit at all and can be accurately controlled at any speed
2. FOC excels at its reversing performance, ensuring the smoothness of forward and reverse switching even when running at its highest speed
3. FOC can also perform braking control in the form of energy recovery.
4. FOC can achieve three closed-loop control of torque, speed, and position.
5. FOC has significantly lower noise but much higher efficiency compared that of electric regulation

&nbsp;&nbsp;&nbsp;Although FOC has many advantages, its large amount of calculation and complex principles requires an expensive controller, which made FOC unpopular. After half a year’s research and iteration, I deeply optimized the part of the code that implements mass calculations and re-selected its components to fit the domestic supply chain. I hope this open-source project can help domestic developers use BLDC motors with excellent performance and contribute to the open-source community.

***

### Comparison Of Open Source Solutions

|    Open source solution    |   **miniFOC**    | [simpleFOC](https://github.com/simplefoc/Arduino-SimpleFOCShield) | [ODrive](https://github.com/odriverobotics/ODrive) | [FpOC](https://github.com/WangXuan95/FpOC) |
| :------------------------: | :----------: | :----------------------------------------------------------: | :------------------------------------------------: | :------------------------------------------------: |
|      Microcontroller       | GD32F130G6U6 |                          ATmega328P                          |                   STM32F405RGT6                    |               FPGA |
|        Driver chip         |    EG2133    |                            L6234                             |                      DRV8301                       |                      MP6540                 |
|     PID loop frequency     |    30kHz (max)    |                           830Hz (max)                        |                        8kHz (typical)                        |                        18kHz (typical)                        |
| Whether have current loop |      No      |                              No                              |                        Yes                         |                        Yes                      |
|       Driving power        |     90W      |                             120W                             |                        960W                        |                        90W                        |
|    Cost price (approx.)    |     20¥      |                             100¥                             |                        300¥                        |                        150¥                        |

&nbsp;&nbsp;&nbsp;&nbsp;As can be seen from the table above, the scheme adopted by **miniFOC** can achieve high performance at low cost. At the same time, due to the re-selection according to the domestic supply chain, the selection of devices is not so limited, and there are many alternatives. amid the chip shortage in 2021, the cost of FOC still can be controlled at about 3$, which further proves the degree of cost optimization and the great potential of the project.

***

### Performance Parameter 

+ Input voltage range: 5V ~ 18V (you can modify the circuit according to the tutorial here to adapt to higher voltage).
+ Maximum driving current: 5A (you can modify the circuit according to the tutorial here to achieve greater driving current).
+ Detailed parameters of FOC: no current loop control, SVPWM (Space Vector Pulse Width Modulation) is adopted.
+ Communication parameters: UART baud rate is 115200, and [Mid Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/mdtp/README.md) is used for data transmission.
+ Microcontroller parameters: Cortex-M3 core, 72MHz frequency, 32KB FLASH, 4KB SRAM. 

***

### Function Features

+ [x] Using space vector pulse width modulation
+ [x] Torque control without current sensor
+ [x] Rotational speed closed loop control
+ [x] Rotation angle closed loop control
+ [x] Automatic phase sequence detection and correction

***

### Development Environment 

+ EDA Tool: [EasyEDA](https://easyeda.com/) (the standard free license is adopted, and there is no license dispute).
+ Compiler tool chain: gcc-arm-none-eabi 10-2020-q4-major
+ Programming tool: OpenOCD 0.11.0-1
+ Integrated development tools: CLion 2021.2.3 #212.5457.51
+ Software development tools: Qt 5.14.2 (MinGW 7.3.0 64bit)
+ Operating system and tool chain: 
  + Win10 + MinGW + CLion + gcc-arm-none-eabi + OpenOCD
  + Ubuntu20.04 + make + cmake + gcc-arm-none-eabi + OpenOCD

***

### Getting Started

Please refer to the [wiki page](https://github.com/ZhuYanzhen1/miniFOC/wiki) of this project for getting started.
<br>
We also provide the [domestic image](https://gitee.com/zhuyanzhen1/mini-foc) address.
<br>
You can visit [Github Page](https://zhuyanzhen1.github.io/miniFOC/) to learn about the usage of functions and variables in the code.
<br>
**Note:** Since the main development and deployment are carried out on Github, Gitee is only used as a domestic mirror warehouse to store the code, and there will be problems such as wiki and issue that are not updated in time. You can visit the Github source repository [here](https://github.com/ZhuYanzhen1/miniFOC).

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

&nbsp;&nbsp;&nbsp;&nbsp;The product has been tested under Windows 10 and Ubuntu 18.04 and 20.04. This is research code, expect that it changes often and any fitness for a particular purpose is disclaimed.
