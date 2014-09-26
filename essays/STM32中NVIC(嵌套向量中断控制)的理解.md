
[<font size=4>←返回主目录<font>](../README.md)</br>

<div align="right"><a href="../index.html" target="_self" title="返回主页"><img src="../images/Home.png"></a> <a href="#bottom" target="_self" title="跳转底部"><img src="../images/bottom.png"></a></div>

__文题__：STM32中NVIC(嵌套向量中断控制)的理解</br>

__作者__：xiahouzuoxin</br>

__日期__：2011-10-04，整理于2014-09-25</br>

_转载请注明出处：<http://xiahouzuoxin.github.io/notes>_

-----------------------------------

这是一篇旧文，早在上大二的时候，在地下室（当时实验室在防空地下室）顺手在word上写的，当时STM32正刚刚开始蓬勃发展，如今时隔3年，整理到这里！

两日被些许琐事所牵，身心俱累，本无心记录，但回想前几天的点滴收获，无录甚是可惜，于是身倚椅，旁敲键盘记之，唯慰藉自己及共享同道仁友。废言不再多，就此入题。

NVIC，中文名嵌套中断向量控制器，是Cortex-M3系列控制器内部独有集成单元，与CPU结合紧密，降低中断延迟时间并且能更加高效处理后续中断。举个例子，比如火车站买票，那些火车站的规章制度就是NVIC，规定学生和军人有比一般人更高优先级，它们则给你单独安排个窗口，同学与同学之间也有区别，那就是你也得排队，也就是你的组别（抢断优先级）和你的排队序号（响应优先级）决定你何时能买到票。

抢断优先级，顾名思义，能再别人中断是抢占别人中断，实现中断嵌套。响应优先级则只能排队，不能抢在前面插别人的对，即不能嵌套。

STM32中指定优先级的寄存器为4位，其定义如下：

> 第0组：所有4位用于指定响应优先级

> 第1组：最高1位用于指定抢占式优先级，最低3位用于指定响应优先级

> 第2组：最高2位用于指定抢占式优先级，最低2位用于指定响应优先级

> 第3组：最高3位用于指定抢占式优先级，最低1位用于指定响应优先级

> 第4组：所有4位用于指定抢占式优先级

以上定义也称作中断优先级分组，相关内容在STM32固件库的misc.h文件中有详细定义。

基础了解了就可以对中断进行操作了：

1.	使用`void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)`函数对优先级分组配置。`NVIC_PriorityGroup`可以配置为

	NVIC_PriorityGroup_0 => 选择第0组
	
	NVIC_PriorityGroup_1 => 选择第1组
	
	NVIC_PriorityGroup_2 => 选择第2组
	
	NVIC_PriorityGroup_3 => 选择第3组
	
	NVIC_PriorityGroup_4 => 选择第4组 
	
	例如：NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0)配置为0组。

2.	中断初始化结构体配置，结构体类型定义如下：

	```c
	typedef struct
	{
	  uint8_t NVIC_IRQChannel;                  
	  uint8_t NVIC_IRQChannelPreemptionPriority;  //抢断优先级
	  uint8_t NVIC_IRQChannelSubPriority;  //响应优先级       
	  FunctionalState NVIC_IRQChannelCmd;       
	} NVIC_InitTypeDef;
	```

	例如：STM32外部中断0配置如下：

	```
    EXTI_NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	EXTI_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级别(0~1)
	EXTI_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;  //响应优先级别(0~7)
	EXTI_NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	```

3.	中断初始化结构体初始化操作如下

	```
	NVIC_Init(&EXTI_NVIC_InitStructure);
	```

4.	开关总中断操作。在STM32中是通过改变CPU优先级来允许和禁止中断的。

	- 下面两个函数等效关闭总中断
	
		```c
		void NVIC_SETPRIMASK(void)； 
		void NVIC_SETFAULTMASK(void)；
		```

	- 下面两个函数等效开放总中断
	
		```c
		void NVIC_RESETPRIMASK(void)； 
		void NVIC_RESETFAULTMASK(void)；
		```
		
	- 常用操作是先关后开中断

		```c
		NVIC_SETPRIMASK();     // Disable Interrupts 
		NVIC_RESETPRIMASK();   // Enable Interrupts
		```
		
	两种类型函数要成对使用。



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



