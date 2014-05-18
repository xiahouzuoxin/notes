[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

### 环境

- 操作系统：Win7, 64bit
- IDE：CCS V3.3
- 仿真器：SEED XDS510PLUS
- DSP型号：TMS320C6713

### 出现问题


### 检查原因

- 请检查电源供电是否正常（核心电压是否为1.2V，IO口电压是否稳定为3.3V）
- 使用示波器检查供电的纹波，TMS320C6713数据手册的99页有纹波的范围要求

![][wenbo]

- 如果是用电池供电，检查电池电压，电池电压过低会造成连接失败
- 检查上电复位是否正常（上电时有复位脉冲，上电后复位引脚为高电平）。一般复位引脚有上拉电阻
- 检查时钟输出是否正常。包括ECLKIN（晶振）和ECLKOUT（TMS320C6713中Default=ECLKIN/2）
- 





[wenbo]:../images/DSP连接不上CCS3.3的问题讨论/wenbo.png