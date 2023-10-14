![LOGO](./docs/image/LOGO.png)

&nbsp;&nbsp;&nbsp;&nbsp;![Version](https://img.shields.io/badge/Version-2.0.2-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;English / [中文](./README_CN.md)

&nbsp;&nbsp;&nbsp;&nbsp;Are you still buying a DC brush motor drive module in about 3<span>$</span>? Are you still worried about the high noise in addition to the already low response speed and life? Allow me to present you our project, miniFOC---- a FOC brushless motor control scheme that can get you the most bang for your buck, for just 3 <span>$</span>!  **miniFOC** has a built-in torque closed-loop controller so that you can control a brushless motor with a 3-wire UART port. The software and hardware design are fully compliant with the AGPL-3.0 open source license.

**Note: This branch is still in the development stage. The hardware circuit has been designed and tested to be stable, yet the firmware is still under development. After the development of this branch is completed, it will provide current loop and non-inductive FOC features. At the same time, version 1.x.x will reach end of life (EOL) and will no longer be maintained. Version 2.x.x will no longer provide any compatibility with version 1.x.x**

***

### Brief Introduction

&nbsp;&nbsp;&nbsp;&nbsp;This open-source project aims to accomplish a FOC(Field Oriented Control) scheme that is operatable with minimum costs in China. The components selected in the example circuit are all manufactured in China. FOC possesses various advantages when it comes to controlling BLCD (Brushless Direct Current) motor; some of the benefits are as follows:

1. FOC has no speed limit at all and can be accurately controlled at any speed
2. FOC excels at its reversing performance, ensuring the smoothness of forward and reverse switching even when running at its highest speed
3. FOC can perform braking control in the form of energy recovery.
4. FOC can achieve three closed-loop control of torque, speed, and position.
5. FOC has significantly lower noise but much higher efficiency compared that of electric regulation

&nbsp;&nbsp;&nbsp;Although FOC has many advantages, its large amount of calculation and complex principles requires an expensive controller, which made FOC unpopular. After half a year’s research and iteration, I deeply optimized the part of the code that implements mass calculations and re-selected its components to fit the domestic supply chain. I hope this open-source project can help domestic developers use BLDC motors with excellent performance and contribute to the open-source community.

&nbsp;&nbsp;&nbsp;&nbsp;Since the miniFOC 1.X.X version was launched earlier (September 2021), after two years, many component supply chains have changed, making the miniFOC v1.X.X hardware no longer adaptable to new needs. Therefore, I re-selected based on the domestic supply chain, and added current loop and non-inductive FOC functions based on the previous one.

***

### Comparison Of Open Source Solutions

|    Open source solution    |   **miniFOC v2**   | [simpleFOC v2.0.4](https://github.com/simplefoc/Arduino-SimpleFOCShield) | [ODrive v3.6](https://github.com/odriverobotics/ODrive) | [FpOC](https://github.com/WangXuan95/FpOC) |
| :------------------------: | :----------: | :----------------------------------------------------------: | :------------------------------------------------: | :------------------------------------------------: |
|      Microcontroller       | CH32V203C8T6 |                          ATmega328P                          |                   STM32F405RGT6                    |               FPGA |
|        Driver chip         |    BDR2L00    |                            L6234                             |                      DRV8301                       |                      MP6540                 |
|     PID loop frequency     |    20kHz (typical)    |                   1kHz (typical)                        |                        8kHz (typical)                        |                        18kHz (typical)                        |
| Whether have current loop |      Yes      |                              Yes                              |                        Yes                         |                        Yes                      |
|       Driving power        |     400W     |                             120W                             |                        960W                        |                        90W                        |
|    Cost price (approx.)    |     3$     |                             [15$](https://www.simplefoc.com/simplefoc_shield_product)                             |                        [259$](https://odriverobotics.com/shop/odrive-v36)                        |                        20$                        |

&nbsp;&nbsp;&nbsp;&nbsp;As can be seen from the table above, the solution adopted by **miniFOC** can achieve high performance at low cost. At the same time, due to the re-selection based on the domestic supply chain, the selection of devices is not so limited and provides many alternatives. When the driving power reaches 400W, the cost of FOC can be reduced to about 3$, which also proves the degree of cost optimization and huge potential of this project.

***

### Performance Parameter 

+ Input voltage range: 6V ~ 24V (you can modify the circuit according to the tutorial [here]() to adapt to higher voltage).
+ Maximum driving current: 30A (you can modify the circuit according to the tutorial [here]() to achieve greater driving current).
+ Detailed parameters of FOC: Current loop close loop control, SVPWM (Space Vector Pulse Width Modulation) is adopted.
+ Communication parameters: UART baud rate is 115200, and [Mid Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/mdtp/README.md) is used for data transmission.
+ Microcontroller parameters: RV32IMACXW core, 144MHz frequency, 64KB FLASH, 20KB SRAM. 

***

### Function Features

+ [x] Using space vector pulse width modulation
+ [x] Torque control without current sensor
+ [x] Rotational speed closed loop control
+ [x] Rotation angle closed loop control
+ [x] Automatic phase sequence detection and correction
+ [ ] Current loop closed loop control
+ [ ] Sensorless FOC algorithm

***

### Development Environment 

+ EDA Tool: KiCAD 7.0.8 (VC++ 1936, 64bit)
+ Compiler tool chain: riscv-none-elf-gcc 12.2.0 or riscv-none-embed-gcc 8.2.0
+ Programming tool: OpenOCD 0.11.0+dev-gfad123a16- (2023-07-03-15:11)
+ Integrated development tools: CLion 2023.2.2 #CL-232.9921.42
+ Software development tools: Qt 5.14.2 (MinGW 7.3.0 64bit)
+ Operating system and tool chain: 
  + Win10 + MinGW + CLion + riscv-none-elf-gcc + OpenOCD
  + Ubuntu22.04 + make + cmake + riscv-none-embed-gcc + OpenOCD

***

### Getting Started

+ You can visit the [Wiki page](https://github.com/ZhuYanzhen1/miniFOC/wiki) of this project for a getting started guide.
+ You can visit [Github Page](https://zhuyanzhen1.github.io/miniFOC/) to learn about the functions and variable usage in the code.
+ You can visit the [Release](https://github.com/ZhuYanzhen1/miniFOC/releases) page to get the latest firmware, monitor tools, and compilation tool chains.

***

### Bugs & Feature Requests

Please report bugs and request features using the [Issue Tracker](https://github.com/ZhuYanzhen1/miniFOC/issues) and follow these request:

1. Before publishing an Issue, please check whether the existing Issue contains your question or request. If so, please try to solve it first according to the solution in the Issue.
2. When publishing an Issue, please provide your operating environment and write down the reproduction method in detail.
3. For discussions on non-operational bugs, please start them in [Discussion](https://github.com/ZhuYanzhen1/miniFOC/discussions) and do not submit them to Issues.

***

### License

The source code is released under a [AGPL-3.0 License](https://github.com/ZhuYanzhen1/miniFOC/blob/main/LICENSE).

**Affiliation：AcmeTech<br>
Author: Yanzhen Zhu<br>
Maintainer：YanzhenZhu, 2208213223@qq.com**

&nbsp;&nbsp;&nbsp;&nbsp;The project has been tested under Windows 10 and Ubuntu 22.04 LTS. This is research code, expect that it changes often and any fitness for a particular purpose is disclaimed.