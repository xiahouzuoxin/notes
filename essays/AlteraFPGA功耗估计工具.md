[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

注：以下资料来自网络摘录，由于水平有限，自己尚未测试过，请去粗取精！

## 早期功耗估算

从Altera的官方网站<http://www.altera.com.cn/support/devices/estimator/pow-powerplay.jsp>可以下载到Altera的早期功耗估算工具，该工具是使用Excel制作。“早期”指的是在设计电路之前，通过系统需要完成的功能、需要使用的FPGA资源估算FPGA的功耗，从而确定电源及外围模块的设计。

![PowerPlay]

在Input Parameter中设置FPGA型号、封装、温度等信息。

重点在Thermal Power中的参数，这需要开发者提前对系统需要用到的FPGA功能进行划分、对资源进行预估：

1.	按功能进行系统模块划分，依次估计每个模块所需的Logic、RAM、Multiplier、I/O、PLL等，如：

	```
	            Usart   SPI     ADC      Flash
	
	LUT         xx      xx
	
	FF          xx
	
	RAM         xx
	
	Multiplier  xx
	
	I/O
	
	PLL
	```

	既然是预估，就不要求那么精确，具体每个模块的资源使用需要有一定的FPGA开发经验，Quartus ii编译后都会有一个资源使用表，看得多了，也就有写个概念了。

2.	Logic子界面，Logic所需的LUT和FF总数量参考Datasheet中的最大值，各模块的使用之和为FPGA的最大值，“宁可高估不可低估”。


## 后期功耗估算

在完成大部分甚至全部的Verilog代码设计后，此时功能甚至门电路逻辑都已经很清晰，因此肯定会有一个更加精确的功耗估算工具。

Quartus ii中执行菜单`Processing->PowerPlay Power Analyzer`就可以启动基于门电路级别的功耗估算，或者也可以从Quartus ii软件的左侧Task栏进行操作。

![PowerPlayAnalyzer]

PowerPlayAnalyzer需要提供一个输入Input（如上图），这个输入是由Modelsim的门级仿真产生的：

1.	执行Quartus ii左侧Task栏的`EDA Netlist Writer`
2.	执行门级仿真，`Tools->Run EDA Simulation Tool->EDA Gate Level Simulation`.



[PowerPlay]:../images/AlteraFPGA功耗估计工具/PowerPlay.png
[PowerPlayAnalyzer]:../images/AlteraFPGA功耗估计工具/PowerPlayAnalyzer.png

