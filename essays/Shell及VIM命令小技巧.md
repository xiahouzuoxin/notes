<!---title:Shell及VIM命令小技巧-->
<!---keywords:工具-->
<!---date:old-->

说明：

1.	命令中的大写字母一般要求是Shift的组合，如J表示按下Shift+J

## Shell命令小技巧

### 统计代码行数

统计单个文件直接使用`wc -l file`命令即可，统计某个目录下所有某类型文件的行数：

```
find . -name *.[ch] | xargs wc -l | sort -n
```

表示统计当前目录下.c与.h文件的行数，并按行数大小排序.

### grep命令

使用格式为grep [-acinvr] [--color=auto] '搜寻字符串' filename

	选项与参数：

	-a ：将 binary 文件以 text 文件的方式搜寻数据
	-c ：计算找到 '搜寻字符串' 的次数
	-i ：忽略大小写的不同，所以大小写视为相同
	-n ：顺便输出行号
	-v ：反向选择，亦即显示出没有 '搜寻字符串' 内容的那一行！
	-r : 递归目录，这个在一个源码工程中查找某个tag出现的位置很有用
	--color=auto ：可以将找到的关键词部分加上颜色的显示喔！

grep结合正则表达式以及管道（如统计代码行数）会很实用！

如在驱动开发中，常会使用`dmesg`命令查看系统核心产生的信息，然后使用`dmesg | grep 'eth'`就可从信息中过滤出网卡那一行了.


## VIM命令小技巧

###	关键词补全

首选是`Ctrl + P`，当然还有其它Ctrl+X的组合：

1. `Ctrl + X` 和 `Ctrl + D` 宏定义补齐
2. `Ctrl + X` 和 `Ctrl + ]` 是Tag 补齐
3. `Ctrl + X` 和 `Ctrl + F` 是文件名补齐
4. `Ctrl + X` 和 `Ctrl + I` 也是关键词补齐，但是关键词后会有个文件名，告诉你这个关键词在哪个文件中
5. `Ctrl + X` 和 `Ctrl +V` 是表达式补齐
6. `Ctrl + X` 和 `Ctrl +L` 这可以对整个行补齐

### 多行并成一行

好吧，使用`v`进入Visual模式，选择多行，直接`J`就可以了

### 字符相关

1.	使用`v`进入Visual模式，选择要转换的字符串，`u`转小写，`U`转大写
2.	`ga`查看光标处字符的ascii码，很好用
3.	`g8`查看光标处字符的utf-8编码
4.	`gf`打开光标处的文件，我常用来打开C中包含的头文件
5.	`*`或`#`在当前文件中搜索当前光标所在字符

### 软链接

`ln -s [Src] [Dst]`

在多版本gcc共存的时候`ln -s`命令很有用，

```
sudo ln -s /usr/bin/gcc-4.1 /usr/bin/gcc    " 建立GCC到gcc-4.1的软链接
```






## 参考

[1] [酷壳：简明Vim练级攻略](http://coolshell.cn/articles/5426.html)

[2] [鸟哥：Linux私房菜基础篇](http://vbird.dic.ksu.edu.tw/linux_basic/linux_basic.php)