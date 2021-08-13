# miniFOC

![Version](https://img.shields.io/badge/Version-1.0.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-GPL-blue.svg)

English/[中文](https://github.com/ZhuYanzhen1/miniFOC/blob/main/README_CN.md)

***

### Brief Introduction

&nbsp;&nbsp;&nbsp;&nbsp;The open source project aims to realize a FOC (Field Oriented Control) scheme that can be implemented at home (China) and at low cost. FOC has many advantages in controlling BLDC (Brushless Direct Current) motor, mainly including the following advantages:

1. FOC has no speed limit at all, and can realize accurate control at any speed.
2. The reversing performance of FOC is extremely excellent, and the forward and reverse switching can be very smooth at the highest speed.
3. FOC can also perform braking control in the form of energy recovery.
4. FOC can realize three closed-loop control of torque, speed and position.
5. The noise of FOC driver will be much lower and the efficiency will be much higher than that of electric regulation.

&nbsp;&nbsp;&nbsp;&nbsp;However, due to the large amount of calculation and complex principle of FOC, a high-cost controller is required, which also makes FOC not popularized and used in many scenarios. After half a year's research and iteration, I deeply optimized a large number of calculation codes of FOC design, and re selected according to the domestic supply chain. I hope this open source project can help domestic developers use BLDC motors with excellent performance and contribute to the open source community.

***

### License

The source code is released under a [GPL3.0 License](https://github.com/ZhuYanzhen1/miniFOC/blob/main/LICENSE).

**Affiliation：AcmeTech<br>
Author: Zhu Yanzhen<br>
Maintainer：YanzhenZhu, 2208213223@qq.com**

The product has been tested under Windows 10 and Ubuntu 18.04 and 20.04. This is research code, expect that it changes often and any fitness for a particular purpose is disclaimed.