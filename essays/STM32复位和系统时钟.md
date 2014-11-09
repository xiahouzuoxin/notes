<!---title:STM32复位和系统时钟-->
<!---keywords:ARM-->
<!---date:2011-10-17，整理于2014-09-25-->

这是一篇旧文，早在上大二的时候，在地下室（当时实验室在防空地下室）顺手在word上写的，当时STM32正刚刚开始蓬勃发展，如今时隔3年，整理到这里！

系统复位后，首先使用内部RC时钟源，由于内部时钟精度不高且不能倍频到较高频率，所以实际应用中一般使用外接晶振（8M）,下面是建立系统时钟的步骤：

1.	将所有RCC外设寄存器重设为默认值
2.	启用外部高速晶振
3.	等待，直到外部晶振稳定
4.	设置欲取址缓存使能和代码延时值
5.	设置AHB时钟(HCLK)=系统时钟
6.	设置高速APB2时钟（PCLK2）为系统时钟
7.	设置低速APB1时钟（PCLK1）为系统时钟1/2，最高36MHz
8.	设置PLL时钟源及倍频系数，使能PLL。PLL最高72MHz
9.	等待PLL初始化成功
10.	设置PLL为系统时钟源
11.	等待PLL成功作为系统时钟源

```c
/*******************************************************************/
/* function : Sysclk configuration
/* author   : 夏侯佐鑫
/* data     : 2011-10-17
/*******************************************************************/
void SysclkInit(void)
{
    ErrorStatus HSEStartUpStatus;
    //重设默认值
    RCC_DeInit();
    //HSE
    RCC_HSEConfig(RCC_HES_ON);
    //等待HSE稳定
    HSEStratUpStatus = RCC_WaitForHSEStartUp();
    if(HSEStratUpStatus == SUCCESS)
    {
        //预取址缓存使能
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        //设置代码延时值,2延时周期
        FLASH_SetLatency(FLSAH_Latency_2);
        //AHB
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        //APB2
        RCC_PCLK2Config(RCC_SYSCLK_Div1); 
        //APB1
        RCC_PCLK1Config(RCC_SYSCLK_Div2);
        //PLLCLK = 8MHz * 9
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        //Enable PLL
        RCC_PLLCmd(ENABLE);
        //Wait PLL Init successed
        while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
        //SYSCLK = PLL clk
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        //Wait PLL be SYSCLK
        while(RCC_GetSYSCLKSource() != 0x08);    
    }        
}
```

