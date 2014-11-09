<!---title:Markdown中插入数学公式的方法-->
<!---keywords:工具-->
<!---date:old-->

自从使用Markdown以来，就开始一直使用Markdown+Github在写文章，整理自己的所学所思。本文亦是通过这种方式完成的。

然而，Markdown自由书写的特性很好，唯独遇到数学公式时就要煞费苦心——每次都是先使用Latex书写(在线的Latex编辑器参考[1])，然后保存为图片，使用img标签进行引用，当公式很多的时候稍显复杂。

本文的方法使用html的语法，调用[1]的公式生成API，在线生成Latex数学公式，免去将公式保存为图片的麻烦。当然，弊端也是有的，公式太多，可能会造成刷新比一般的网页慢一些。

## 方法一：使用Google Chart的服务器

```
<img src="http://chart.googleapis.com/chart?cht=tx&chl= 在此插入Latex公式" style="border:none;">
```

一个例子，

```
<img src="http://chart.googleapis.com/chart?cht=tx&chl=\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}" style="border:none;">
```

公式显示结果为：

<img src="http://chart.googleapis.com/chart?cht=tx&chl=\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}" style="border:none;">

适用了下，Google Chart服务器的响应速度还可以，但据说可能复杂一些的Latex公式可能无法解析（参考[2]）。

## 方法二：使用forkosh服务器

forkosh上提供了关于Latex公式的一份简短而很有用的帮助，参考[1]和[3].

使用forkosh插入公式的方法是

```
<img src="http://www.forkosh.com/mathtex.cgi? 在此处插入Latex公式">
```

给个例子，

```
<img src="http://www.forkosh.com/mathtex.cgi? \Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}">
```

显示结果为：

<img src="http://www.forkosh.com/mathtex.cgi? \Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}">


因为网页插入公式的原理是调用“某某网站的服务器”动态生成的，所有保证公式正常显示的前提是该网址能一直存在着为我等小生做些小小的服务。forkosh我是用了快2年了，一直很好，推荐！

## 方法三：使用MathJax引擎

大家都看过[Stackoverflow](http://stackoverflow.com/)上的公式吧，漂亮，其生成的不是图片。这就要用到MathJax引擎，在Markdown中添加MathJax引擎也很简单，

```
<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>
```

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>

然后，再使用Tex写公式。`$$公式$$`表示行间公式，本来Tex中使用`\(公式\)`表示行内公式，但因为Markdown中`\`是转义字符，所以在Markdown中输入行内公式使用`\\(公式\\)`，如下代码：

```
$$x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}$$
\\(x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}\\)
```

分别显示结果（行间公式）：

$$x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}$$

行内公式：

\\(x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}\\)

不信，你可以试一下，在公式上还可以使用鼠标右键操作。

## 代码片段

我没有用过Sublime Text编辑器，听说其代码片段功能非常强大，然而我这宁愿推荐一款国产编辑器Everedit，小巧实用。它也支持Markdown，也有代码片段功能，我使用的是其免费版本2.几吧。

菜单项`查找->代码片段`，代码片段中右键`插入`，填写内容如下：

1.	使用forkosh服务器解析公式

```
@名称:Equation
@触发文本:Equation
@代码片段:请在下一行开始输入内容!

<img src="http://www.forkosh.com/mathtex.cgi? \Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}">

```

2.	使用MathJax解析公式

```
@名称:MathJax
@触发文本:MathJax
@代码片段:请在下一行开始输入内容!
<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>
```

完成之后，则多出叫Equation和MathJax的代码片段，每次添加公式时只需要双击该代码片段则自动添加上面的模板，方便省事！

## 参考

[1] <http://www.forkosh.com/mathtextutorial.html>

[2] <http://www.ruanyifeng.com/blog/2011/07/formula_online_generator.html>

[3] <http://www.forkosh.com/mathtex.html>
