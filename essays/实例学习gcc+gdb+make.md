# 1 小侃GCC

在正式使用gcc之前，我们先来侃侃gcc是啥玩意儿？

### 历史

现在的GCC是GNU Compiler Collection的简称，既然是Collection，就是指一些工具链的集合。

最初的GCC（当时还只有C编译器，GCC还是GNU C Comiler的简写）是由Richard Stallman开发的，Stallman也是GNU工程的首创者，那时还是在1984年。

随着程序设计语言的发展，GCC逐渐开始支持C语言之外的语言，如C++、Objective-C、Java、Fortran以及Ada等，详细可访问GCC主页[http://gcc.gnu.org/][GCC]

GNU工具链包括：

1. GNU Compiler Collection(GCC)：这里GCC纯指编译器，包括链接等其它操作
2. GNU Make：编译和构建工程的自动化工具，即Makefile
3. GNU Binutils：二进制工具，包括链接器和汇编器
4. GNU Debugger(GDB)：著名的gcc下调试工具
5. GNU Autotools：可以构建Makefile
6. GNU Binson

本文主要讨论gcc，gdb和Makefile的使用。

另外，这里指的gcc还包括了用于编译c++的工具，我们实际使用的g++命令其编译过程调用的是与C语言gcc相同的工具，只不过链接过程有所不同。如无特殊说明，gcc命令的使用g++命令上也都适用。

### 安装

GCC版本比较多，还有应用在嵌入式ARM、AVR等平台的交叉编译工具，在RHEL/CentOS Linux下，只要使用
```Shell
yum install gcc
yum install g++
yum install gdb
``` 
默认情况下一般是安装好的。

在Window下，可选择的gcc安装方式包括[MinGW][MinGW]和[Cygwin][Cygwin]。本文的操作环境就基于Cygwin，Cygwin是一个Window下模拟Linux环境的开源软件，除了能使用gcc、gdb等工具外，还能使用其它许多Shell命令，操作方式与Linux下的终端无太大区别。本文后面讲述到的所有操作都是基于终端的。


### 版本及帮助

安装好了工具后，使用
```Shell
gcc --version
gdb --version
```
可分别查看gcc和gdb的版本信息，

![][gcc-v]

你可使用下面的，
```Shell
gcc --help
gdb --help
g++ --help
```
或下面的命令获得关于gcc以及gdb的帮助信息。在使用gcc时偶尔会忘掉一两个参数，这几个命令就非常有用。
```Shell
man gcc
man gdb 
man g++ 
```
如果在你看来，上网不是那么麻烦的话，则[http://linux.die.net/man/1/gcc][gcc-man]也可以获得gcc的帮助信息。


# 2 GCC的使用

好吧，我们现在开始第一个例子（我只熟悉C语言，我们这里讨论的例子都是C语言的例子）。

又遇到学习C语言时的第1个例子——Hello, world!，只不过这次我们更应该说Hello, GCC。
```C
#include <stdio.h>
int main(void)
{
    printf("Hello, world.\n");
    printf("Hello, GCC.\n");

    return 0;
}
```
我们就将上面的程序存储到main.c的文件中，下面请跟着我敲命令吧，
```Shell
gcc main.c
ls
```
在敲ls命令后你看到了什么？main.c目录下多了个a.exe的程序（Linux下可执行程序是a.out）。好吧，既然你是exe格式，运行吧，
```Shell
./a.out
```
看到什么，没错：Hello, GCC.

> NOTES:    
> 在Linux/Cygwin下执行程序使用"./可执行文件名"。默认不设置时可执行文件名为a.out或a.exe。

到此，你就该说，我已经会使用gcc了，然而，其实你还差远了：

1. 你知道怎么生成汇编文件吗？
2. 你知道怎么编译c++文件吗？
3. 你知道怎么查看预处理之后的结果吗？
4. 你看VC++，人家都会编译生成*.obj的文件，你知道怎么使用gcc编译得到吗？
5. 你知道怎么编译多个文件吗？
6. 你知道怎样才能调试吗？
7. ……

如果你有哪项不知道，不着急，请Go on！

在这之前，你必须了解C代码生成可执行文件的过程，共4步：预处理、编译、汇编、链接。

![][gcc-process]

### gcc生成可执行文件的过程

还是Hello, GCC的例子，请跟着敲命令，
```Shell
gcc main.c -o main
```
**-o** 选项表示生成目标文件名为main.exe。

```Shell
gcc -E main.c -o main.i
```
**-E** 选项表示预处理操作，预处理就是将宏定义展开，头文件展开。预处理之后的目标文件保存在main.i，这时，你可以查看main.i的预处理结果，
```Shell
cat _main.c
```

```Shell
gcc -S main.c -o main.s
```
**-S** 选项表示编译操作，其结果将生成汇编文件（*.s文件，这里使用-o选项定义目标文件为main.s）。我们也可以查看分析上述Hello代码的汇编代码，
```C
	.file	"main.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "Hello, world.\12\0"
LC1:
	.ascii "Hello, GCC.\12\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	call	__alloca
	call	___main
	movl	$LC0, (%esp)
	call	_printf
	movl	$LC1, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
```
在DSP、ARM等嵌入式平台上，使用gcc编译得到汇编，再根据汇编代码进行优化是一种常用的方法。

> NOTES:	
> 生成汇编文件（包含汇编代码的文件）的过程是编译，不是汇编，汇编是将汇编代码转换成目标文件*.obj的过程。
> 从这点上理解，汇编文件生成可执行文件的过程是没有编译操作的。

```Shell
gcc -c main.c -o main.obj  
```
**-c** 选项将源文件生成目标文件main.obj，main.obj其实已经是一种近似可执行文件了，通过链接操作链接相应的库就可以执行了。


第4步的链接直接使用gcc main.c -o main就可以完成。

### gcc是工具的集合

从下面的命令你将更加直观的看到：gcc其实是一套从预处理、编译、汇编到链接工具的集合。
```Shell
rm main.i main.s main.obj 
cpp main.c > main.i
gcc -S main.i
as main.s -o main.o
```
上面分别使用了cpp预处理、gcc编译、as汇编。链接可以使用ld命令，不过操作复杂些。

因此，gcc只是帮我们将多个复杂的操作放在一个命令中，是我们的软件开发过程变得更加高效自动化。

### gcc的一些其它选项

* -C 只能配合-E使用，告诉预处理器不要丢弃注释.
```Shell
gcc -E -C main.c -o main.i  
```
* -M 告诉预处理器输出一个适合make的规则,用于描述各目标文件的依赖关系.
```Shell
gcc -M main.c -o main_makerule
cat main_makerule
```
```
main.o: main.c /usr/include/stdio.h /usr/include/_ansi.h \
  /usr/include/newlib.h /usr/include/sys/config.h \
  /usr/include/machine/ieeefp.h /usr/include/sys/features.h \
  /usr/include/cygwin/config.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stddef.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdarg.h \
  /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
  /usr/include/machine/_types.h /usr/include/machine/_default_types.h \
  /usr/include/sys/lock.h /usr/include/sys/types.h \
  /usr/include/machine/types.h /usr/include/cygwin/types.h \
  /usr/include/sys/sysmacros.h /usr/include/stdint.h \
  /usr/include/endian.h /usr/include/bits/endian.h \
  /usr/include/byteswap.h /usr/include/sys/stdio.h \
  /usr/include/sys/cdefs.h
```
* -w 禁止各种类型的警告，不推荐使用
* -Wall 显示各种类型的警告，推荐使用，这可以让自己的程序变得更加规范化
* -v 显示编译过程的详细信息，Verbos简称
* -llibrary  连接名为library的库文件.
* -Idir  在头文件的搜索路径列表中添加dir目录
* -Ldir  在`-llibrary'选项的搜索路径列表中添加dir目录. 

> NOTES:    
> 在大工程编译链接过程中，很多类似于“Undefined ...”的错误都是由-llibrary、-Idir或-Ldir的设置错误造成的。

* -Dname 宏定义某个name宏，这个宏是全局的，在控制程序上很有帮助
比如有如下main.c源程序，通过_DEBUG宏可以控制是否打印结果，
```c
	#include <stdio.h>
	int main(void)
	{
	    int a = 2;
	    int b = 3;
	    int c = a + b;

	#ifdef _DEBUG
	    printf("c=%d\n", c);
	#endif
	    return 0;
	}
```
对比下面使用和不使用-D_DEBUG的运行结果
```
	gcc -D_DEBUG main.c -o main 
	./main 
	gcc main.c -o main 
	./mian
```
* -O/O1 代码优化，对于大函数，优化编译占用稍微多的时间和相当大的内存
* -O2 多优化一些.除了涉及空间和速度交换的优化选项,执行几乎所有的优化工作.例如不进行循环展开(loopunrolling)和函数内嵌(inlining).和-O选项比较,这个选项既增加了编译时间,也提高了生成代码的 运行效果.
* -O3 优化的更多.除了打开-O2所做的一切,它还打开了-finline-functions选项.

* -g 以操作系统的本地格式(stabs,COFF,XCOFF,或DWARF)产生调试信息. 只有使用了-g才能使用gdb工具进行调试
```
gcc -g main.c -o main 
gdb main 
```
有关gdb的操作有很多，将专门详述。

### 多文件编译

_main.c_
```C
#include <stdio.h>
#include "add.h"

int main(void)
{
    int a = 2;
    int b = 3;
    int c = add(a,b);

#ifdef _DEBUG
    printf("c=%d\n", c);
#endif
    return 0;
}
```

_add.c_
```C
int add(int a, int b)
{
    return (a+b);
}
```

_add.h_
```C
#ifndef _ADD_H
#define _ADD_H

extern int add(int a, int b);

#endif
```

使用gcc编译多文件的方法是将多个源文件添加到gcc编译选项中，
```Shell
gcc -D_DEBUG main.c add.c -o main 
./main 
```
显示如下执行结果，

![][prog-2]

> NOTES:  
> 上面未将add.h添加到编译文件中是因为：C语言的编译是以.c文件为单位的，每个.c文件都会编译对应到一个.s和.obj文件，而.h文件不会。在上面的例子中，我们只要保
> 证在main.c在编译的时候能够找到add函数，这是通过#include "add.h"实现的。在链接的时候，main.obj会自动找到到add.obj中的add符号，这都是链接器的功劳。


### 共享库与静态库

库时编译好的目标文件的一个打包，在链接时被加载到程序中，分为共享库和静态库。如之前使用到的printf定义就在库libc中，我们只要包含stdio.h就能使用了（其实还要在gcc中使用-llibray选项，只不过gcc默认包含了该选项）。

* 静态库：在Linux下是.a文件，在Windows下是.lib文件。__在链接时将用户程序中使用到外部函数机器码拷贝到程序可执行区__。
* 共享库：在Linux下是.so文件，在Windows下是.dll文件。在链接时，只在程序可执行区建立一个索引表，而不拷贝机器代码。__在程序执行时，才根据索引表加载外部函数的机器码__。共享库相对于静态库的优点是减少了可执行程序代码量的大小，同时共享库可同时被多个运行程序调用，也能减少内存空间。

	![][lib]

无论是静态库还是共享库，在gcc选项中都要使用-l和-L分别制定库名和库路径。

仍以上个add程序为例，说说静态库和共享库的创建和使用，先添加sub函数，
_sub.c_
```C
int sub(int a, int b)
{
    return (a-b);
}
```

_sub.h_
```C
#ifndef _SUB_H
#define _SUB_H

extern int sub(int a, int b);

#endif
```

_main.c_
```C
#include <stdio.h>
#include "add.h"
#include "sub.h"

int main(void)
{
    int a = 2;
    int b = 3;
    int c = add(a,b);
    int d = sub(a,b);

#ifdef _DEBUG
    printf("c=%d\n", c);
    printf("d=%d\n", d);
#endif
    return 0;
}
```

* 静态库的生成需要使用到gcc和ar工具

```
gcc -c add.c sub.c
ar -r libmymath.a add.o sub.o
```

![][static-lib]

这样，我们只要将.a文件和.h文件打包，add和sub就可以在任意地方使用了。

> NOTES:    
> 请注意上图给出的在编译main.c时如何链接到静态库的？（-lmymath -static选项）

之前说过，静态库链接的代码量将比共享库链接要大，我们且先看看静态链接后的代码量，稍后做比较
![][size-static]

* 共享库的生成需要使用到gcc工具

```
gcc -shared -fPIC add.c sub.c -o libmymath.so 
ln -s libmymath.so libmymath.dll   # Windows下才需要
gcc main.c -lmymath -L./ -o main 
```

-shared 表示共享库，-fPIC 表示生成与位置无关的代码。

![][share-lib]

> NOTES:    
> 在Linux下，共享库链接的的可执行程序_执行时_还是会出现找不到库问题，这时有两种方法：
>> 1. 可以把当前路径加入/etc/ld.so.conf中然后运行ldconfig，或者以当前路径为参数运行ldconfig（要有root权限）
>> 2. 把当前路径加入环境变量LD_LIBRARY_PATH 中

同样，来看看使用共享库生成的可执行文件大小，

![][size-share]

诶，0x9d4，人家静态库总大小才0x990字节，你怎么说静态库要比共享库大呢？

第一，静态库生成代码量比共享库大指的是——代码量，代码存储在text段，明显嘛，共享库代码段大小1712要比静态库的1728小；

第二， 前面说过，共享库在链接成可执行文件的时候不是直接拷贝目标文件机器码，而是生成符号表。对，符号表！从上面的结果来看，符号表应该存储在data段，所以共享库的data段比静态库要大。因为我们这里的add.c和sub.c的代码量生成的机器码都非常小，使用共享库生成符号表的方法反而使可执行文件占用的磁盘空间更大了。只是一般情况下，使用共享库的可执行文件占用的磁盘空间将比静态库的小.


### 库路径、文件路径与环境变量

之前已经说过，通过-I可以指定头文件路径，-L指定库路径，-l指定库名。从上一节也看到了它们的使用。

那么系统默认的头文件路径和库路径是在哪呢？

```
cpp -v
```

可以查看默认的头文件路径.

```
gcc -v main.c -lmymath -L. -o main
```

添加-v选项，就可以查看默认的头文件路径.

gcc提供几个默认的环境变量：

1. PATH：可执行文件和动态库（.so, .dll）的搜索路径
2. CPATH：头文件搜索路径
3. LIBRARY_PATH：库搜索路径，包括动态库和静态库


### 几个有用查看目标文件的工具

* file

	显示目标文件格式和运行环境的体系结构（ARM还是x86）

* nm

	列出目标文件的符号表

* ldd

	列出可执行文件在运行时所需要的共享库

* size

	列出目标文件中节的名称和大小。上面已经使用过该工具。

* readelf

	显示elf目标文件的完整结构，包括elf头中的编码信息，包括size和nm功能。最常用的方法是参数是-d和-h参数。

* objdump

	所有二进制工具之母，最大作用是反汇编.text节中的二进制信息。最常用的格式是objdump -D -S filename，显示反汇编信息。若要反汇编与源码同时显示，则在gcc编译时要使用-g选项。


> NOTES:
> 上面所有的工具都可以通过 [toolname] --help获得相关的参数帮助信息。


# 3 GDB的使用



# 4 使用Makefile构建工程




# 参考资源
1. GCC Manual "Using the GNU Compiler Collection (GCC)" @ http://gcc.gnu.org/onlinedocs.
2. GNU 'make' manual @ http://www.gnu.org/software/make/manual/make.html.
3. GCC and Make http://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
4. Robert Mecklenburg, "Managing Projects with GNU Make", 3rd Edition, 2004.










[GCC]:http://gcc.gnu.org/
[MinGW]:http://www.mingw.org/
[Cygwin]:http://www.mingw.org/
[gcc-man]:http://linux.die.net/man/1/gcc


[gcc-v]:../images/实例学习gcc+gdb+make/gcc-v.png
[gcc-process]:../images/实例学习gcc+gdb+make/GCC_CompilationProcess.png
[prog-2]:../images/实例学习gcc+gdb+make/prog-2.png
[static-lib]:../images/实例学习gcc+gdb+make/static-lib.png
[share-lib]:../images/实例学习gcc+gdb+make/share-lib.png
[size-static]:../images/实例学习gcc+gdb+make/size-static.png
[size-share]:../images/实例学习gcc+gdb+make/size-share.png