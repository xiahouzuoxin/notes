[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

其实该注意的地方很早就整理出来了，一直放在硬盘里，今天无意中翻到，整理出来，以备下次安装的不时之需。

## 准备

1. 准备Win7系统
2. 下载CentOS6.3
3. 下载EasyBCD并安装

## 硬盘安装步骤

1\. 腾出一个或者重新划分一个E盘，大小定义为10G就可以了，注意一定要小于32G。用FAT32格式化这个盘。

2\. 下载DVD镜像文件centos6.3***-dvd.iso，放入E盘，把里面的ioslinux文件夹中的vmlinuz和initrd.img文件，以及images文件夹提取出来，解压到和CentOS镜像文件相同的目录。解压完后E盘应该有4个文件：

	- iso
	- vmlinz
	- initrd.img
	- images


3\. 打开EasyBCD，Add New Entry –> NeoGrub — > Install –> Configure， 这时会弹出一个txt文件，在其中输入

```
title install centos6.3

kernel (hd0,4)/vmlinuz

initrd (hd0,4)/initrd.img

```

>> 因为我装windows7的时候系统自带分了一个100M的启动分区，代号为hd0，那么C盘代号就为hd0,1了。以此类推，我的Win 7分成了C盘系统盘和D盘，那么E盘为逻辑分区第一个分区，那么就是hd0,4了。


4\. 关闭，重启后选择centos启动项

选择centos6.3***-dvd.iso文件所在的目录，然后出现安装菜单的时候一定要选择“Install or upgrade an existing system”，windows7显卡驱动可能对安装界面有影响。剩下的就参考光盘安装步骤。

5\. 分盘事项

选择Create Custom Layout

	/boot ext4 100MB
	/swap swap 2~4GB(3GB)
	/     ext4 剩余空间

/boot和/swap一般是必需的，一般用户，根据需要，可能还会划分/home（如果你把大部分资料放在home中的话，/home最好大一些）

6\. 选择引导盘

分完盘后会弹出安装引导程序框，记住将引导程序最好安装到系统硬盘上（我习惯直接安装到和Linux系统相同磁盘下）
