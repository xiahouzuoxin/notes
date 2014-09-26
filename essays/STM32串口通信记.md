
[<font size=4>←返回主目录<font>](../README.md)</br>

<div align="right"><a href="../index.html" target="_self" title="返回主页"><img src="../images/Home.png"></a> <a href="#bottom" target="_self" title="跳转底部"><img src="../images/bottom.png"></a></div>

__文题__：STM32串口通信记</br>

__作者__：xiahouzuoxin</br>

__日期__：2011-10-04 16:01，整理于2014-09-25</br>

_转载请注明出处：<http://xiahouzuoxin.github.io/notes>_

-----------------------------------

这是一篇旧文，早在上大二的时候，在地下室（当时实验室在防空地下室）顺手在word上写的，当时STM32正刚刚开始蓬勃发展，如今时隔3年，整理到这里！

接着刚才的NVIC简单记录下串口通信吧。何为串口通信？两个人之间互发短信见过吧，这叫串口通信，假如群发短信就是并口通信了。

在STM32的串口通信操作中，作为应用者可以从两方面来操纵，一方面是寄存器直接操作，另一方面则是库函数操作。两种方法比较，前一种是智者的技巧，后一种则是傻瓜的聪慧。下面亮一下代码先。

1.	智者的技巧：寄存器直接操作

	```
	RCC->APB2ENR|=1<<2;       //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;      //使能串口时钟 
	GPIOA->CRH=0X444444B4;    //IO状态设置
		  
	RCC->APB2RSTR|=1<<14;     //复位串口1
	RCC->APB2RSTR&=~(1<<14);  //停止复位	   	   
	//波特率设置
 	USART1->BRR=uBound;       // 波特率设置	 
	USART1->CR1|=0X200C;      //1位停止,无校验位
	```

2.	傻瓜的智慧：库函数操作

	```
    /*第一步:使能端口时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/*第二步:配置RXD和TXD端口*/
	GPIO_Usart_InitStructure.GPIO_Pin = USART1_TXD;
	GPIO_Usart_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Usart_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Usart_InitStructure);

	GPIO_Usart_InitStructure.GPIO_Pin = USART1_RXD;
	GPIO_Usart_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_Usart_InitStructure);

	/*第三步:使能串口时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	/*第四步：串口配置*/
	Usart_InitStruct.USART_BaudRate = uBound;
	Usart_InitStruct.USART_WordLength = USART_WordLength_8b;
	Usart_InitStruct.USART_StopBits = USART_StopBits_1;
	Usart_InitStruct.USART_Parity = USART_Parity_No;
	Usart_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	Usart_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &Usart_InitStruct);
	
	/*第五步：使能串口*/
	USART_Cmd(USART1, ENABLE);
	```

图个方便，贴个代码而不赘述，以上代码全部测试通过，有兴趣朋友可以自己研究。

在这说明点，“傻瓜的智慧”虽然傻点，但结构明晰，操作方便；而“智者的技巧”虽然简单精炼，但看上去意思难辨。傻瓜并不傻，智者也不是可以顾及无边，因此操作STM32时可权衡自己能力和喜好选择自己的操作方式。


<div align="right"><a href="../index.html" target="_self" title="返回主页"><img src="../images/Home.png"></a> <a href="#top" target="_self" title="返回顶部"><img src="../images/top.png"></a></div>
<a name="bottom"></a>
[<font size=4>←返回主目录<font>](../README.md)</br>

<!-- 

本模板为转成Html后需要修改的地方:
1. 修改README.md为README.html，共2处
2. 修改Github样式目录
3. 添加一键分享功能，源码在stylesheets目录下mystyle.md
4. 添加评论功能，并修改评论中的标题项等，源码在stylesheets目录下mystyle.md
5. 修正其它可能不正确的链接 

-->



