[<font size=4>←返回主目录<font>](./README.md)
</br></br></br>


## 测试

下面是我在一个DSP+FPGA的系统（平台：TMS320C6713+EP2C8Q208CN）上测试。

测试方法为：FPGA将采集的同一路信号存放在FIFO1与FIFO2中，然后DSP通过EMIF分别读取FIFO1和FIFO两个通道的数据，两通道数据显示结果如图。


- EMIF时钟频率 100MHz


![][imag1]

__图1__

![][imag2]

__图2__

从图1中可以看出：读取通道2的数据时在某个时刻发生了丢点的现象。

从图2中可以看出：从FPGA中送出的应该是三角波，而出现某些值被采集到多次（2次）到的情况。


- EMIF时钟频率 50MHz


![][imag3]

__图3__

图3为降低EMIF的时钟频率后访问FPGA，读回的两通道数据完全一致，没有出现任何的数据丢失或重复。

## 分析
多次检查FPGA程序，没有发现有任何问题，而且降速后DSP读取正确，说明FPGA的程序不存在问题。因此，暂时将问题定位到：在PCB布线难以满足防信号干扰的前提下，DSP通过EMIF访问FPGA将可能导致读取数据出错。

因此，针对出现的问题，暂降低EMIF速率到50MHz，而代价就是访问SDRAM的速率也降低了，这对大量数据存储在外部SDRAM的情况，性能将下降一半。

若内部RAM满足存储要求的前提下，推荐将运算数据存储在内部RAM中，通过测试：计算1024个点的实数FFT，在内部RAM中的运算时间将比在外部SDRAM中快差不多5倍（系统倍频时钟为200MHz）。


[imag1]:../images/FPGA与DSP通信中的EMIF速率问题/imag1.png
[imag2]:../images/FPGA与DSP通信中的EMIF速率问题/imag2.png
[imag3]:../images/FPGA与DSP通信中的EMIF速率问题/imag3.png