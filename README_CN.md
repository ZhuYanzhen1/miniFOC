![LOGO](./docs/image/LOGO.png)

&nbsp;&nbsp;&nbsp;&nbsp;![Version](https://img.shields.io/badge/Version-2.0.2-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[English](./README.md) / 中文

&nbsp;&nbsp;&nbsp;&nbsp;你还在买十几块钱一个的直流有刷电机的驱动模块吗？你还在为有刷电机的高噪声、低响应速度和低寿命而烦恼吗？来看看这个项目吧，一个20块钱就能搞定的FOC无刷电机控制方案！**miniFOC**内置了力矩闭环控制器，为你提供一个通过3线UART口就能控制的无刷电机控制器。本项目的软件及硬件设计完全遵循AGPL-3.0开源协议。

**注：此分支还在开发阶段，目前硬件电路已经完成设计并测试稳定，固件仍在开发中。此分支开发完成后，将提供电流环和无感FOC功能，同时1.x.x版本将达到寿命终期（EOL），不再维护且2.x.x版本不再提供对1.x.x版本的任何兼容**

***

### 简介
&nbsp;&nbsp;&nbsp;&nbsp;本开源项目旨在实现一种在国内（中国）就可以以及低成本实现的FOC (Field Oriented Control) 方案，示例电路中选用的元件均为国产芯片。FOC在控制BLDC (Brushless Direct Current)电机上有诸多的好处，主要有如下几点优势：

1. FOC则完全没有转速的限制，不论在什么转速下都可以实现精确的控制。
2. FOC的换向性能极其优秀，最高转速下正反转切换可以非常顺畅。
3. FOC可以以能量回收的形式进行刹车控制。
4. FOC可以实现力矩、速度、位置三个闭环控制。
5. FOC驱动器的噪音会比电调小很多，效率也比电调高很多。

&nbsp;&nbsp;&nbsp;&nbsp;但是由于FOC的计算量大、原理复杂，所以需要很高成本的控制器，这也使得FOC在很多场景下都没有得到推广和使用。在经过了半年的研究和迭代之后，本人将FOC涉及大量计算的代码进行了深度优化，也重新根据国内的供应链进行了选型，希望本开源项目能够帮助国内的广大开发者们用上有优秀性能的BLDC电机，为开源社区贡献一份力量。

&nbsp;&nbsp;&nbsp;&nbsp;由于miniFOC 1.X.X版本推出的时间较早（2021年9月），在经过了两年的时间后，许多元件供应链发生了变化，使得miniFOC 1.X.X的硬件不再适应新需求。因此本人重新根据国内的供应链进行了选型，并且在之前的基础上增加电流环和无感FOC功能。

***

### 开源方案对比

|     开源方案     |   **miniFOC v2**   | [simpleFOC v2.0.4](https://github.com/simplefoc/Arduino-SimpleFOCShield) | [ODrive v3.5](https://github.com/odriverobotics/ODrive) | [FpOC](https://github.com/WangXuan95/FpOC) |
| :--------------: | :----------: | :----------------------------------------------------------: | :------------------------------------------------: | :------------------------------------------------: |
|     主控制器     | CH32V203C8T6 |                          ATmega328P                          |                   STM32F405RGT6                    |                   FPGA                |
|     驱动芯片     |    BDR2L00    |                            L6234                             |                      DRV8301                       |                      MP6540                 |
|     闭环频率     | 20kHz (typical) |                        1kHz (typical)                        |                        8kHz (typical)                        |                        18kHz (typical)                        |
|   是否有电流环   |      是      |                              是                              |                         是                         |                         是                         |
|     驱动功率     |     400W     |                             120W                             |                        960W                        |                        90W                        |
| 成本价格（大约） |     20¥      |                             [115¥](https://www.simplefoc.com/simplefoc_shield_product)                             |                        [1890¥](https://odriverobotics.com/shop/odrive-v36)                        |                        150¥                        |

&nbsp;&nbsp;&nbsp;&nbsp;从上表格中可以看出，**miniFOC**所采用的方案可以实现在低成本下达到较高的性能。同时由于重新根据国内的供应链进行了选型，因此在器件的选择上没有那么局限，提供了很多替代方案。在驱动功率达到400W的情况下能将FOC的成本降至约20元，这也证明了本项目在成本上的优化程度和巨大潜力。

***

### 性能参数

+ 输入电压范围：6V~24V（你可以根据[这里]()的教程修改电路以适应更高的电压）。
+ 最大驱动电流：30A（你可以根据[这里]()的教程修改电路以实现更大的驱动电流）。
+ FOC详细参数：电流环闭环控制，采用SVPWM (Space Vector Pulse Width Modulation)。
+ 通信参数：UART串口通信波特率115200，采用[中容量数传协议](https://github.com/ZhuYanzhen1/CDTP/blob/master/mdtp/README_CN.md)进行数据传输。
+ 微控制器参数：RV32IMACXW内核，144MHz主频，64KB Flash，20KB  SRAM。

***

### 功能特性

+ [x] 采用空间矢量脉冲宽度调制方法
+ [x] 实现无电流传感器力矩控制
+ [x] 实现转动速度闭环控制
+ [x] 实现转动角度闭环控制
+ [x] 实现自动相序检测和相序矫正
+ [ ] 实现电流环闭环控制
+ [ ] 实现无感FOC算法

***

### 开发环境

+ EDA工具：KiCAD 7.0.8 (VC++ 1936, 64bit)
+ 编译工具链：riscv-none-elf-gcc 12.2.0 或 riscv-none-embed-gcc 8.2.0
+ 烧录工具：OpenOCD 0.11.0+dev-gfad123a16- (2023-07-03-15:11)
+ 集成开发环境：CLion 2023.2.2 #CL-232.9921.42
+ 上位机开发工具：Qt 5.14.2 (MinGW 7.3.0 64bit)
+ 操作系统及工具链：
  + Win10 + MinGW + CLion + riscv-none-elf-gcc + OpenOCD
  + Ubuntu22.04 + make + cmake + riscv-none-embed-gcc + OpenOCD

***

### 入门指南

+ 你可以访问本项目的[Wiki页面](https://github.com/ZhuYanzhen1/miniFOC/wiki)以获取入门指南。
+ 你可以访问[Github Page](https://zhuyanzhen1.github.io/miniFOC/)页面以了解代码中的函数及变量的用法等信息。
+ 你可以访问[Release](https://github.com/ZhuYanzhen1/miniFOC/releases)页面以获取最新的固件、上位机监视器工具以及编译工具链。

***

### BUG报告 & 功能需求

请使用[Issue Tracker](https://github.com/ZhuYanzhen1/miniFOC/issues)报告错误和需求功能，并遵循以下要求：

1. 发布Issue前请先检查现有的Issue中是否含有你的问题或请求。若有，请根据Issue中的解决方法优先尝试解决。
2. 发布Issue时，请提供您的运行环境并详细写出复现方法。
3. 非运行BUG的讨论，请在[Discussion](https://github.com/ZhuYanzhen1/miniFOC/discussions)中展开，不要提交到Issue中。

***

### 许可证

源代码根据[AGPL-3.0许可证](./LICENSE)发布。

**组织：AcmeTech <br>
作者：朱彦臻<br>
维护人：朱彦臻, 2208213223@qq.com**

&nbsp;&nbsp;&nbsp;&nbsp;该项目已经在Windows 10、Ubuntu 22.04 LTS下进行了测试。这是一个研究代码，希望它经常更改，并且不承认任何特定用途的适用性。