[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

在虚拟机上装了个CentOS，可是控制台分辨率太小了，如果想放大控制台分辨率，则修改文件/boot/grub/grub.conf的kernel项。

添加参数vga=791

```
title CentOS (2.6.18-238.19.1.el5)
root (hd0,0)
kernel /vmlinuz-2.6.18-238.19.1.el5 ro root=/dev/VolGroup00/LogVol00 vga=791
initrd /initrd-2.6.18-238.19.1.el5.img
```

791是VESA定制的值，指的是1024X768 16-bit分辨率。

当不确定1024x768的vga值时，可设

```
vga=ask
```

重启系统，系统会要求选择分辨率（请记住你的选择，假设选择了317）。系统启动后若分辨率满足要求，则重新设置

```
vga=791 
```

启动时要求用户选择的分辨率为16进制，而vga=右端为十进制，十六进制值371转化为十进制后为791。

