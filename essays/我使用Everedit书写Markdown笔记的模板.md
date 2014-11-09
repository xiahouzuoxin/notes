<!---title:我使用Everedit书写Markdown笔记的模板-->
<!---keywords:Everedit-->
<!---date:2014-09-06-->

Everedit是一款非常棒的编辑器，短小精悍，功能上虽然比上不足（Sublime Text），但比下有余（Notepad等），而且打开速度非常快，支持Markdown。我就经常用其写Markdown博客，这一系列文章也都在它上面完成的。这里记录一下使用我使用它的“代码片段”功能组织自己的文档模板，主要方便自己查阅。

## 标题信息等

```
@名称:MarkdownText
@触发文本:MarkdownText
@代码片段:请在下一行开始输入内容!
[<font size=4>←返回主目录<font>](../README.md)</br>

<div align="right"><a href="../index.html" target="_self" title="返回主页"><img src="../images/Home.png"></a> <a href="#bottom" name="bottom" target="_self" title="跳转底部"><img src="../images/bottom.png"></a></div>

__文题__：[文题]</br>
__作者__：xiahouzuoxin</br>
__日期__：[日期]</br>

-----------------------------------


<div align="right"><a href="../index.html" target="_self" title="返回主页"><img src="../images/Home.png"></a> <a href="#top" target="_self" title="返回顶部"><img src="../images/top.png"></a></div>

[<font size=4>←返回主目录<font>](../README.md)</br>
```

主要功能包括：返回主页、返回顶部等。

## 一键分享

```
<div class="bdsharebuttonbox"><a href="#" class="bds_more" data-cmd="more"></a><a href="#" class="bds_qzone" data-cmd="qzone" title="分享到QQ空间"></a><a href="#" class="bds_tsina" data-cmd="tsina" title="分享到新浪微博"></a><a href="#" class="bds_tqq" data-cmd="tqq" title="分享到腾讯微博"></a><a href="#" class="bds_renren" data-cmd="renren" title="分享到人人网"></a><a href="#" class="bds_weixin" data-cmd="weixin" title="分享到微信"></a></div>
<script>window._bd_share_config={"common":{"bdSnsKey":{},"bdText":"","bdMini":"2","bdMiniList":false,"bdPic":"","bdStyle":"0","bdSize":"16"},"share":{},"image":{"viewList":["qzone","tsina","tqq","renren","weixin"],"viewText":"分享到：","viewSize":"16"},"selectShare":{"bdContainerClass":null,"bdSelectMiniList":["qzone","tsina","tqq","renren","weixin"]}};with(document)0[(getElementsByTagName('head')[0]||body).appendChild(createElement('script')).src='http://bdimg.share.baidu.com/static/api/js/share.js?v=89860593.js?cdnversion='+~(-new Date()/36e5)];</script>
```

## MathJax脚本支持

```
@名称:MathJax
@触发文本:MathJax
@代码片段:请在下一行开始输入内容!
<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>
```

## 插入公式

```
@名称:Equation
@触发文本:Equation
@代码片段:请在下一行开始输入内容!

<img src="http://www.forkosh.com/mathtex.cgi? \Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}">

```