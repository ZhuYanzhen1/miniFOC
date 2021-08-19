![LOGO](https://raw.githubusercontent.com/ZhuYanzhen1/miniFOC/main/image/LOGO.png)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![Version](https://img.shields.io/badge/Version-1.0.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[English](https://github.com/ZhuYanzhen1/miniFOC/blob/main/README.md) / 中文

&nbsp;&nbsp;&nbsp;&nbsp;你还在买十几块钱一个的直流有刷电机的驱动模块吗？你还在为有刷电机的高噪声、低响应速度和低寿命而烦恼吗？来看看这个项目吧，一个20块钱就能搞定的FOC无刷电机控制方案！**miniFOC**内置了力矩闭环控制器，为你提供一个通过3线串口就能控制的无刷电机控制器。本项目计划于2021年8月底完成基本功能的开发，软件及硬件设计完全遵循AGPL-3.0开源协议。

***

### 简介
&nbsp;&nbsp;&nbsp;&nbsp;本开源项目旨在实现一种在国内（中国）就可以以及低成本实现的FOC (Field Oriented Control) 方案，示例电路中选用的元件均为国产芯片。FOC在控制BLDC (Brushless Direct Current)电机上有诸多的好处，主要有如下几点优势：

1. FOC则完全没有转速的限制，不论在什么转速下都可以实现精确的控制。
2. FOC的换向性能极其优秀，最高转速下正反转切换可以非常顺畅。
3. FOC还可以以能量回收的形式进行刹车控制。
4. FOC可以实现力矩、速度、位置三个闭环控制。
5. FOC驱动器的噪音会比电调小很多，效率也比电调高很多。

&nbsp;&nbsp;&nbsp;&nbsp;但是由于FOC的计算量大、原理复杂，所以需要很高成本的控制器，这也使得FOC在很多场景下都没有得到推广和使用。在经过了半年的研究和迭代之后，本人将FOC涉及大量计算的代码进行了深度优化，也重新根据国内的供应链进行了选型，希望本开源项目能够帮助国内的广大开发者们用上有优秀性能的BLDC电机，为开源社区贡献一份力量。

***

### 开源方案对比

|     开源方案     |   **miniFOC**    | [simpleFOC](https://github.com/simplefoc/Arduino-SimpleFOCShield) | [ODrive](https://github.com/odriverobotics/ODrive) |
| :--------------: | :----------: | :----------------------------------------------------------: | :------------------------------------------------: |
|     主控制器     | GD32F130G6U6 |                          ATmega328P                          |                   STM32F405RGT6                    |
|     驱动芯片     |    EG2133    |                            L6234                             |                      DRV8301                       |
|     闭环频率     |    10kHz     |                            830Hz                             |                        8kHz                        |
|   是否有电流环   |      否      |                              否                              |                         是                         |
|     驱动功率     |     90W      |                             120W                             |                        960W                        |
| 成本价格（大约） |     20¥      |                             100¥                             |                        300¥                        |

&nbsp;&nbsp;&nbsp;&nbsp;从上表格中可以看出，**miniFOC**所采用的方案可以实现在低成本下达到较高的性能。同时由于重新根据国内的供应链进行了选型，所以在器件的选择上没有那么局限，提供了很多替代方案。在2021年芯片供应紧缺的情况下能将FOC的成本降至约20元，这也证明了本项目在成本上的优化程度和巨大潜力。

***

### 性能参数

+ 输入电压范围：5V~18V（你可以根据这里的教程修改电路以适应更高的电压）。
+ 最大驱动电流：5A（你可以根据这里的教程修改电路以实现更大的驱动电流）。
+ FOC详细参数：无电流环控制，采用SVPWM (Space Vector Pulse Width Modulation)。
+ 通信参数：UART串口通信波特率115200，采用[中容量数传协议](https://github.com/ZhuYanzhen1/CDTP/blob/master/Mid%20Capacity/README_CN.md)进行数据传输。
+ 微控制器参数：Cortex-M3内核，48MHz主频，32KB Flash，4KB  SRAM。

***

### 开发环境

+ EDA工具：[立创EDA](https://lceda.cn/)（采用标准版免费许可证，无LICENSE纠纷）。
+ 编译工具链：gcc-arm-none-eabi 10-2020-q4-major
+ 烧录工具：OpenOCD 0.11.0-1
+ 集成开发工具：CLion 2021.2 #212.4746.93
+ 操作系统及工具链：
  + Win10 + MinGW + CLion + gcc-arm-none-eabi + OpenOCD
  + Ubuntu20.04 + make + cmake + gcc-arm-none-eabi + OpenOCD

***

### 入门指南

入门请参考本项目的[wiki页面](https://github.com/ZhuYanzhen1/miniFOC/wiki)。

我们还提供了[国内镜像](https://gitee.com/zhuyanzhen1/mini-foc)地址。

***

### BUG报告 & 功能需求

请使用[Issue Tracker](https://github.com/ZhuYanzhen1/miniFOC/issues)报告错误和需求功能，并遵循以下要求：

1.在不同选项卡上突出显示选项卡。
2.如果窗口未聚焦，不要让更新消失。

***

### 许可证

源代码根据[AGPL-3.0许可证](https://github.com/ZhuYanzhen1/miniFOC/blob/main/LICENSE)发布。

**组织：AcmeTech <br>
作者：朱彦臻<br>
维护人：朱彦臻, 2208213223@qq.com**

该产品已经在Windows 10、Ubuntu 18.04和20.04下进行了测试。这是一个研究代码，希望它经常更改，并且不承认任何特定用途的适用性。