[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

## 设置通信帧格式

SPI通信的配置那只是基本的底层，要保证通信做得漂亮，设计通信的帧格式将大大降低错误概率。比如，因为我暂时最多传输一个字（16bit）的数据，设计如下7字节的帧格式：

![Frame]

将帧格式对应到数据结构就是一个结构体：

```c
struct st_msg_user {
    uint8_t header;
    uint8_t type;
    uint8_t low_byte;
    uint8_t high_byte;
    uint8_t rsvd0;
    uint8_t rsvd1;
    uint8_t checkout;   // low_byte ^ high_byte 
};
```

然后，所有对帧的操作都归结到对上面结构体的操作，如：

```
extern struct st_msg_user assemble_frame(uint8_t type, uint16_t data);  // 将数据组成一帧
extern void msg_printf(struct st_msg_user *msg);                        // 将帧发送出去
extern uint16_t unpack_frame(struct st_msg_user msg);                   // 解出帧中的数据
```

## SPI主从机配置注意事项

首先考虑硬件上要注意的：

1.	必需设置1个MCU为主机，另1个为从机，两者接线是CLK、MISO、MOSI、SEL一一对应连接。注意是一一对接，也就是说主机MISO就接到从机的MISO、主机MOSI就接到从机的MOSI

2.	除了要接SPI的4根线意外，还必须连接地线（共地），提供参考电势

软件配置上：

1.	CLK永远是由主机发出，因此必须使用全双工模式，在读数据的时候同时写一个数据提供总线时钟

2.	时钟的空闲状态和时钟的采样沿的主从机配置要保持一致

3.	我使用的是TMS320C6713与STM32进行SPI通信，DSP为主机，ARM为从机，则两端的配置如下：

	- ARM端
	
	![ARM]

	其中影响通信数据的段包括：Datasize；CPOL和CPHA分别表示时钟空闲状态和时钟采样边沿，主从机必须一致；FisrtBit也很重要，否则接收到的数据是倒转的，因为我的DSP是MSB格式，所以ARM端也设成MSB。
	
	- DSP端

	DSP端使用McBSP模拟SPI主机功能，其寄存器配置如下：

	```c
	/*
	 * Config SPI
	 * devNum -- Choose from 0~1 for McBSP0/McBSP1
	 */
	void SPI_Config(MCBSP_Handle *hMcbsp_ch, int devNum)
	{
		*hMcbsp_ch = MCBSP_open(devNum, MCBSP_OPEN_RESET);
		MCBSP_reset(*hMcbsp_ch);

		/* Configure using structure @SPI_McbspConfig which defined above */
	    SPI_McbspConfig.spcr = MCBSP_SPCR_DEFAULT 
	        | (0 << _MCBSP_SPCR_DLB_SHIFT )      // 回环测试
	        | (3 << _MCBSP_SPCR_CLKSTP_SHIFT);   // CLK_STP=11
	    SPI_McbspConfig.rcr  = MCBSP_RCR_DEFAULT // (1)Single phase frame (2)Frame len=8bit 
	        | (1 << _MCBSP_RCR_RFIG_SHIFT     )  // ignore first pulse 
	        | (1 << _MCBSP_RCR_RDATDLY_SHIFT  ); // must be 1 
	    SPI_McbspConfig.xcr = MCBSP_XCR_DEFAULT  // (1)Single phase frame (2)Frame len=8bit 
	        | (1 << _MCBSP_XCR_XFIG_SHIFT     )  // ignore first pulse
	        | (1 << _MCBSP_XCR_XDATDLY_SHIFT  ); // must be 1
	    SPI_McbspConfig.srgr = MCBSP_SRGR_DEFAULT
	        | (1 << _MCBSP_SRGR_CLKSM_SHIFT   )  // Sample-rate generator clock <- CPU clock
	        & (~(1 << _MCBSP_SRGR_FSGM_SHIFT )) // DXR-to-XSR copy will generate FSX
	        | (MCBSP_SRGR_CLKGDV_OF(24)   << _MCBSP_SRGR_CLKGDV_SHIFT  ); // (CPU/2) / (24+1) = 4MHz
	    SPI_McbspConfig.mcr = MCBSP_MCR_DEFAULT; /* Using default value of MCR register */
	    SPI_McbspConfig.rcer = MCBSP_RCER_DEFAULT;
	    SPI_McbspConfig.xcer = MCBSP_XCER_DEFAULT;
	    SPI_McbspConfig.pcr = MCBSP_PCR_DEFAULT
	        | (1 << _MCBSP_PCR_FSXM_SHIFT     )  // FSXM driverd by FSGM bit in SRGR.
	        | (1 << _MCBSP_PCR_FSRM_SHIFT     )  // Frame-synchronization signal is generated internally by the sample-rate generator 
	        | (1 << _MCBSP_PCR_CLKXM_SHIFT    )  // Master
	        | (1 << _MCBSP_PCR_CLKRM_SHIFT    )  // CLKR is output, driverd by Sample-rate generate
	        | (1 << _MCBSP_PCR_FSXP_SHIFT     )  // SPI/SS is low active 
	        & (~(1 << _MCBSP_PCR_CLKRP_SHIFT ))  // receive at falling edge, CLKRP=0
	        & (~(1 << _MCBSP_PCR_CLKXP_SHIFT )); // transmit at rising edge, CLKXP=0  

		MCBSP_config(*hMcbsp_ch, &SPI_McbspConfig);	 
		
		SPI_Start(g_hMcbsp0);   
	}
	```

	主要配置好时钟频率，空闲状态、采样边沿，帧长。

4.	另外，考虑到主从机间时钟采样可能存在的问题，在使用SPI发送帧的时候，最后帧的每个发送字节间存在短暂的时延，避免通信错误的发送，如下，我Delay了5us，

	```c
	void SPI_Write_Str(MCBSP_Handle hMcbsp_ch, const char *str, int32_t n)
	{
	    while (n > 0) {
	        while (!MCBSP_xrdy(hMcbsp_ch));
	        MCBSP_write(hMcbsp_ch, (Uint32)(*str++));    
	        n--;
			Delay_us(5);
	    }
	}
	```


## 逻辑分析仪采集SPI总线数据图

共1帧的数据：

![img1]

前4个字节：

![img2]

后3个字节：

![img3]

[img1]:../images/基于SPI的双MCU通信/img1.png
[img2]:../images/基于SPI的双MCU通信/img2.png
[img3]:../images/基于SPI的双MCU通信/img3.png
[ARM]:../images/基于SPI的双MCU通信/ARM.jpg
[Frame]:../images/基于SPI的双MCU通信/Frame.jpg
