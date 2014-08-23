[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

终于到了要写写论文的时候了，回想一年前本科毕业（大四）的时候——静心尽力做了一年的图像分割和识别，毕业的时候搜检一下那一年看过的论文，打印的纸质版摞一起居然有好几本书厚，而且还都是英文的。这一直令我感到自豪，这得非常感谢那个时候为我导航的刘老师，让我的大学在做了2年嵌入式后领略到另一番风味。如今又到准备论文的时候了，我这个爱折腾开源软件的拥趸，也打算好好用用Latex这个工具了。

操作环境：CentOS 6.5 64bit

## 安装

先配置好CentOS的yum源，参考[CentOS更新yum源的方法](./CentOS更新yum源的方法.md)，配置好后，执行

```
yum install texlive*
```

安装texlive相关的包及其依赖，等待下载安装完成，基本的Latex环境就配置好了。texlive默认安装到`/usr/share/texmf/`目录下.

这个时候不妨使用来写一小段文字，文件命名为`Hello.tex`

```
\documentclass{article}

\author{xiahouzuoxin}
\title{Signal Processing}

\begin{document}
    \maketitle
    First ducument I write use Latex.  % coments
\end{document}
```

Latex就想一门编程语言，写完后需要编译，编译上述文档的命令为：`xelatex hello.tex`. 则输出文件中会有一个hello.pdf的文件，打开后效果：

![hello]

## 中文字体支持

使用xelatex命令编译不像之前的latex命令编译一样，自己生成字体，xelatex编译可以使用系统字体，简化了字体安装。因此首先要为系统安装中文字体，CentOS安装中文字体的方法参见[CentOS安装中文字体](./CentOS安装中文字体.md)。

我从Windows中拷贝安装了`黑体`、`宋体`、`华文中宋`、`华文楷体`、`幼圆`、`隶书`等中文字体。

为方便安装的中文字体在Latex中的使用，不妨使用下面的中文字体宏包（这里的宏与C语言中的宏定义是类似的概念，Latex中宏包的文件后缀名为.sty）：

```
% Filename: zhfontcfg.sty
% xetex/xelatex 字体设定宏包

\ProvidesPackage{zhfontcfg}
\usepackage[cm-default]{fontspec} %[cm-default]选项主要用来解决使用数学环境时数学符号不能正常显示的问题

\usepackage{xunicode,xltxtra}
\defaultfontfeatures{Mapping=tex-text} %如果没有它，会有一些 tex 特殊字符无法正常使用，比如连字符。

% 中文断行
\XeTeXlinebreaklocale "zh"
\XeTeXlinebreakskip = 0pt plus 1pt minus 0.1pt

%将系统字体名映射为逻辑字体名称，主要是为了维护的方便
\newcommand\fontnamehei{SimHei}              % 黑体
\newcommand\fontnamesong{SimSun}             % 宋体
\newcommand\fontnamezhsong{STZhongSong}      % 华文中宋
\newcommand\fontnamekai{STKaiti}             % 华文楷体
\newcommand\fontnameyouyuan{YouYuan}         % 幼圆
\newcommand\fontnameLi{LiSu}                 % 隶书
\newcommand\fontnamemono{DejaVu Sans Mono}  
\newcommand\fontnameroman{Times New Roman}

%%设置常用中文字号，方便调用
\newcommand{\erhao}{\fontsize{22pt}{\baselineskip}\selectfont}
\newcommand{\xiaoerhao}{\fontsize{18pt}{\baselineskip}\selectfont}
\newcommand{\sanhao}{\fontsize{16pt}{\baselineskip}\selectfont}
\newcommand{\xiaosanhao}{\fontsize{15pt}{\baselineskip}\selectfont}
\newcommand{\sihao}{\fontsize{14pt}{\baselineskip}\selectfont}
\newcommand{\xiaosihao}{\fontsize{12pt}{\baselineskip}\selectfont}
\newcommand{\wuhao}{\fontsize{10.5pt}{\baselineskip}\selectfont}
\newcommand{\xiaowuhao}{\fontsize{9pt}{\baselineskip}\selectfont}
\newcommand{\liuhao}{\fontsize{7.5pt}{\baselineskip}\selectfont}

%设置文档正文字体为宋体
\setmainfont[BoldFont=\fontnamehei]{\fontnamesong}
\setsansfont[BoldFont=\fontnamehei]{\fontnamekai}
\setmonofont{\fontnamemono}

%楷体
\newfontinstance\KAI {\fontnamekai}
\newcommand{\kai}[1]{{\KAI#1}}

%黑体
\newfontinstance\HEI{\fontnamehei}
\newcommand{\hei}[1]{{\HEI#1}}

%英文
\newfontinstance\ENF{\fontnameroman}
\newcommand{\en}[1]{\,{\ENF#1}\,}
```

在.tex的Latex文件中使用usepackage{zhfontcfg}即可使用上面的宏包文件，下面是一个使用zhfontcfg宏包书写中英文混合的实例：

```
% FileName: main.tex

\documentclass{article}

\usepackage{zhfontcfg}
\usepackage[colorlinks,linkcolor=black]{hyperref}

\title{latex多字体简易示例}
\author{夏侯佐鑫}

\begin{document}
\maketitle
  \section{楷体}
  \kai{楷体}
  \section{黑体}
  \hei{黑体}

  我是北京科技大学的学生.    % 这里是默认的正文宋体
  
  \section{英文}
  \en{English Times New Roman}
\end{document}
```

使用`xelatex main.tex`编译后的结果为：

![zhfontcfg]

到这里，貌似我们已经能够使用Latex开始书写了！

注意：要使用xelatex编译的文件格式必须是UTF-8，VIM中使用命令`：set filetype=utf-8`即可，Windows下使用CTex则另存为选择UTF-8格式。当然，Windows下使用中文字体有更方便的方法：

```
\usepackage{xeCJK}
\usepackage{fontspec}
\setCJKmainfont{SimSun}
\setCJKmonofont{SimSun}
\setmainfont{Times New Roman}
```

其中的\\setCJKmainfont{SimSun}就是用于设置宋体为中文主字体。而且上面的配置在中英混合的文章中好看。



## Latex语法


## Latex模板




## 参考文献

1.	[一份不太简短的LATEX2ε介绍中文版](http://hhtao.weebly.com/uploads/3/3/7/2/3372398/lshort-zh-cn.pdf). 版本 4.20，二○○七年九月.
2.	[The Not So Short Introduction to LATEX 2ε](http://mirror.neu.edu.cn/CTAN/info/lshort/english/lshort.pdf). Version 5.03, April 25, 2014.
3.	LaTeX新人教程——30分钟从完全陌生到基本入门.


[hello]:../images/Latex入门/hello.png
[zhfontcfg]:../images/Latex入门/zhfontcfg.png

