# miniFOC

![Version](https://img.shields.io/badge/Version-1.0.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-GPL-blue.svg)

[English](https://github.com/ZhuYanzhen1/miniFOC/blob/main/README.md)/中文

***

### 简介
&nbsp;&nbsp;&nbsp;&nbsp;本开源项目旨在实现一种在国内（中国）就可以以及低成本实现的FOC (Field Oriented Control) 方案。FOC在控制BLDC (Brushless Direct Current)电机上有诸多的好处，主要有如下几点优势：

1. FOC则完全没有转速的限制，不论在什么转速下都可以实现精确的控制。
2. FOC的换向性能极其优秀，最高转速下正反转切换可以非常顺畅。
3. FOC还可以以能量回收的形式进行刹车控制。
4. FOC可以实现力矩、速度、位置三个闭环控制。
5. FOC驱动器的噪音会比电调小很多，效率也比电调高很多。

&nbsp;&nbsp;&nbsp;&nbsp;但是由于FOC的计算量大、原理复杂，所以需要很高成本的控制器，这也使得FOC在很多场景下都没有得到推广和使用。在经过了半年的研究和迭代之后，本人将FOC设计大量计算的代码进行了深度优化，也重新根据国内的供应链进行了选型，希望本开源项目能够帮助国内的广大开发者们用上有优秀性能的BLDC电机，为开源社区贡献一份力量。

***

### BUG报告 & 功能需求

请使用[Issue Tracker](https://github.com/ZhuYanzhen1/miniFOC/issues)报告错误和需求功能，并遵循以下要求：

1.在不同选项卡上突出显示选项卡。
2.如果窗口未聚焦，不要让更新消失。

***

### 许可证

源代码根据[GPL3.0许可证](https://github.com/ZhuYanzhen1/miniFOC/blob/main/LICENSE)发布。

**组织：AcmeTech <br>
作者：朱彦臻<br>
维护人：朱彦臻, 2208213223@qq.com**

该产品已经在Windows 10、Ubuntu 18.04和20.04下进行了测试。这是一个研究代码，希望它经常更改，并且不承认任何特定用途的适用性。