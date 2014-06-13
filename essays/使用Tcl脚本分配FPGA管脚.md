[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

## 自动生成Tcl文件

```
Project -> Generate Tcl File for Project...
```

弹出如下对话框，设置脚本路径。

![][Create-Tcl]

## 编辑引脚

使用`set_location_assignment`分配管脚如下：

![][Tcl]

第一次配制时，没有`set_location_assignment`语句，自已在`set_global_assignment`语句下一行添加即可。

## 执行Tcl脚本

```
Tools -> Tcl Scripts...
```

![][Run-Tcl]

选中刚新建的Tcl文件，点击Run运行即可！

## 答疑解惑

1\. 为什么Tcl中没有为每个引脚分配输入输出属性，也能保证引脚属性正确？

因为引脚输入输出属性都已经在Verilog语言的module中或原理图中设置了，如下图，

![Pin2]
![Pin1]




[Create-Tcl]:../images/使用Tcl脚本分配FPGA管脚/Create-Tcl.png
[Tcl]:../images/使用Tcl脚本分配FPGA管脚/Tcl.png
[Run-Tcl]:../images/使用Tcl脚本分配FPGA管脚/Tcl-Run.jpg
[Pin1]:../images/使用Tcl脚本分配FPGA管脚/Pin1.png
[Pin2]:../images/使用Tcl脚本分配FPGA管脚/Pin2.png

