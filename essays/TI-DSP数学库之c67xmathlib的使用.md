[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

正如TI描述的：

	The C67x FastRTS library is an optimized floating-point math function library for C programmers using TMS320C67x devices

上面说的C67x FastRTS library就是本文使用的c67xmathlib，在dsp中使用C标准的math.h总感觉是一种资源浪费（没测试过，只是感觉，若有测试过的希望一起交流）。而在工程中难免要用到一些数学函数，如log2在FFT算法中就很好用，sin/cos函数在解三角形的算法中不可避免，当时为提高速度，一般使用查表的方式。然而，查表的弊端就是——太耗存储空间了，而且精度有限，某些情况下不得已还在查表法基础上进行插值计算。C67x FastRTS library恰好提供了一些优化的数学函数支持，推荐使用！

## 去官网下载

http://www.ti.com.cn/tool/cn/mathlib

下载完是个可执行程序，估计就是一个大包，因为安装完后就是一些.c/h文件，其目录结构如下：

```
 +--mathlib_v2.0.0.1
     |
     +--docs                Library documentation
     |
     +--src                 Source code with example projects
     |   |
     |   + dp              Example projects for Double precision kernels
     |   + sp              Example projects for Single precision kernels
     |
     |--include            Header file containing kernel interface
     |                         header files
     |
     |--lib                   Precompiled Library  (COFF and ELF)
     |
     |--build               Provided project to rebuild library
     |
     |--README.txt          Top-level README file
     |
     |--Rules.make     Rules.make file for setting paths to dependencies in Linux
     |
     |--Top level make file
```

## 使用

正统的是使用软件包的方法是：lib目录下的静态链接库加include目录下的.h头文件。然而，因为src目录下已经给了源代码，我宁愿将我需要用到的函数源码复制到工程中编译。

比如：使用float类型的sin函数——拷贝./src/sp/sinsp/sinsp_c.c及./src/sp/sinsp/sinsp_c.h到工程中编译即可使用。

每个函数模块都提供几个文件：

1.	基于C语言函数的实现（在*_c.c/h文件中）
2.	基于inline的实现（在*_i.h头文件中）
3.	基于向量/多个输入的实现（在*_v.c文件中）
4.	用于验证的main函数（*_d.c文件）

另外值得注意的一点是，在使用前最好使用CCS的仿真器验证下函数的正确性！当然你足够相信TI的话就当我没说过这话。


