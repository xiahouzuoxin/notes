<!---title:Quartus_ii中使用Testbench仿真的方法-->
<!---keywords:FPGA-->
<!---date:old-->

## 设置Modelsim路径

执行`Tools -> Options -> General -> EDA Tool Options`，设置Modelsim路径如下：

![ModelsimPath]

一般设置好一次以后就不用设置了。

## 编写Testbench

1.	使用模板：

	执行`Processing -> Start -> Start Testbench Template Writer`生成Testbench模板文件，
	
	使用`File->Open`打开在工程simulation目录下的Testbench文件进行编辑

2.	手动编写：

	`File -> New...`，选择Verilg HDL File，Testbench文件命名后缀最好使用*_tst.vt，在新建的文件中编写逻辑，如下例所示：

	![TestbenchEx]



## 仿真设置

执行`Assigments -> Settings -> EDA Tool Settings -> Simulation`设置仿真参数

![ModelsimArgs]

![TestbenchSetting]

一路OK，执行`Tools->Run Simulation Tools->RTL simulation`则弹出Modelsim的仿真界面，就可以进行仿真分析了。




[ModelsimPath]:../images/Quartus_ii中使用Testbench仿真的方法/ModelsimPath.jpg
[ModelsimArgs]:../images/Quartus_ii中使用Testbench仿真的方法/ModelsimArgs.png
[TestbenchSetting]:../images/Quartus_ii中使用Testbench仿真的方法/TestbenchSetting.png
[TestbenchEx]:../images/Quartus_ii中使用Testbench仿真的方法/TestbenchEx.png
