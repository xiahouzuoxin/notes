### 夏侯佐鑫(男) 

__Email__：[xiahouzuoxin@163.com](mailto:xiahouzuoxin@163.com) __Job Objective__: 图像处理或机器学习

- 学校专业：北京科技大学 硕士（保送：计算机技术）、本科（电子信息工程）
- Blog: <http://blog.csdn.net/xiahouzuoxin> (CSDN博客专家,排名1400左右，访问量>50万) 
- Homepage: <http://xiahouzuoxin.github.io/notes/>
- GitHub: <https://github.com/xiahouzuoxin>

## <font color=red>== 专业技能 ==</font>

- 平台基础：C/C++、matlab、OpenCV、VLFeat、Caffe、Fedora、Shell、Qt、硬件（DSP、FPGA)……
- 图像处理：FFT、AR谱、FIR滤波、Kalman滤波、JPEG编解码、SIFT、BoW(Bag Of Word)、Textons纹理、超像素分割(QuickShift、SLIC)……
- 机器学习：KMeans、HIKM(层次整数KMeans)、SVM(支持向量机)、SGD(随机梯度下降)、Neural Network(神经网络)、CNN（卷积神经网络）、HMM(隐马尔科夫模型)、Linear/Logistic/Softmax Regression、GDA(高斯判别分析)、Naive Bayesian(朴素贝叶斯)、EM(期望最大化算法）、CRF/denseCRF(条件随机场)、Compressive Sensing(压缩感知)……
- 英语：CET6(448)、CET4(523)

## <font color=red>== 学术 ==</font>

1. Zuoxin Xiahou and Xiaotong Zhang, “[Adaptive Localization in Wireless Sensor Network through Bayesian Compressive Sensing](http://downloads.hindawi.com/journals/ijdsn/2015/438638.pdf),” International Journal of Distributed Sensor Networks, vol. 2015, Article ID 438638, 13 pages, 2015. doi:10.1155/2015/438638. (第一作者，SCI已发表)
2. Zuoxin Xiahou and Xiaotong Zhang, Sparse Multi-target Localization and Tracking in Wireless Sensor Network. Smart world congress,2015.(第一作者，EI录用)
3. Zhang, X., Zhang, X., Qi, Y., He, L., Xiahou, Z., & Li, C. (2014). Security Evaluation for Wireless Sensor Networks Based on Attack Test and Fuzzy Comprehensive Judgement. In Advanced Technologies in Ad Hoc and Sensor Networks (pp. 81-92). Springer Berlin Heidelberg. (第四作者，EI检索)
4. 计算机软件著作权，“基于Qt的图像采集处理平台V1.0”.（第一作者）

## <font color=red>== 实习 ==</font>

### 2015.05-2015.09，三星中国研究院（智能视觉小组），图像算法实习生

1. 背景：自拍视频的人目标Sematic Segmentation
2. 任务：
	- 图像和Label数据的Matlab/Python预处理（Mirror、Multiscale等），LMDB数据库生成
	- 基于Caffe+GPU平台，构建二类分割问题的[FCNN](http://www.cs.berkeley.edu/~jonlong/long_shelhamer_fcn.pdf)和[Deeplab](https://bitbucket.org/deeplab/deeplab-public/)的CNN网络
	- 结果优化：(1)denseCRF平滑；(2)分割（Grabcut、SLIC）后处理；(3)训练Multiscale的model
	- 研究CRF的end-to-end训练方式（参考Oxford最新Paper：CRF+RNN Framework）
	- 以OpenCV+Caffe为基础，C++实现项目演示Demo
	- 修改GoogleNet（ReLU->PReLU，卷积stride替代Pooling)，以期应用于嵌入式手机平台上
3. 成果：
	- 完成FCNN和Deeplab网络的训练与测试，C++[视频分割Demo-V1.0](http://blog.csdn.net/xiahouzuoxin/article/details/47789361)(去注释代码量约2000行)。
	- 利用denseCRF优化结果，自拍图片Test Dataset上的IoU指标如下：	
	
		|FCN | FCN-CRF | Deeplab | Deeplab-CRF |
		|----|----|----|----|
		|0.9561|0.9592|0.9513|0.9573|

### 2012.08-2012.10，亿阳通讯，音频编解码算法实习生

1. 背景：CK610平台的音频编解码算法移植（注：CK610是一款国产ARM9芯片）
2. 任务：
	- 研究[MP3中编码的实现](http://blog.csdn.net/xiahouzuoxin/article/details/7849249)
	- 研究[sbc开源代码](http://bluez.cvs.sourceforge.net/viewvc/bluez/utils/sbc/)实现：4子带和8子带滤波分析、scale_factor的子带量化、Bitstream形成
	- Visual Studio上sbc算法验证，嵌入式平台算法的裁剪
	- 替小组搭建C-SKY开发环境，并在上面进行算法仿真验证
3. 成果：
	- Visual Studio和C-SKY平台上算法验证通过
	- 实习表现优异，经理邀请参与后期的“基于Cortex-M4处理器的语音算法项目”

### 2011.07-2011.08，中国航天科工集团2院25所，Excel实习生

## <font color=red>== 项目 ==</font>

### 2014.09-2014.11，OpenCV+Qt的图像处理基础实验平台

1. 背景：业余独立完成，使用OpenCV+Qt，编写一个含有基本数字图像处理算法的平台
2. 任务：
	- 功能：图像采集(摄像头）、图像处理、图像载入和保存
	- 图像处理包括：人脸检测、幂次变换、边缘检测（又包括LOG和Canny检测）、Hough变换、形态学操作、滤波平滑（同态滤波、高斯滤波、中值滤波、双边滤波和导向滤波）以及直方图均衡化。
	- Linux(CentoS 6.5)，OpenCV 2.3.1，Qt4.8。OpenCV用于辅助完成图像处理算法，Qt设计界面。
3. 成果：[Github程序](https://github.com/xiahouzuoxin/opencv_study/tree/master/zximage)、软件使用说明书、申请软件著作权1项

### 2013.08-2014.12，基于无线传感网的声测向及声目标识别系统

1. 背景：用声音信号进行目标测向和识别，结果通过传感网节点（>100个）上传主控制台。主要用C/C++、matlab、Verilog等开发。3人。
2. 任务：
	- 项目组长，前期负责技术策划书中声测向和声识别部分的撰写，策划书的网络部分由一位老师完成
	- 由于缺乏对声音信号的认知，向中科院声学所、中科院电子所等单位做过技术咨询
	- 处理声信号：用到FFT、AR谱、Kalman滤波、LMS预测；算法在DSP上实现并优化（DMA、Cache优化等）
	- 声测向：互相关算法的设计、嵌入式DSP上的实现与优化
	- 识别：分析含噪声的数据（现场采集），改进神经网络model，提升实际场景识别性能（涉及数据噪声大，数据量少，欠拟合等问题）
	- 硬件设计上1人承担原理图设计、PCB设计（6层板1块+4层板1块+射频模块1块），涉及DSP与FPGA及内存的高速通信(100MHz)
	- DSP及FPGA上的驱动设计（中断、Timer、SPI、EMIF总线、串口、AD-16bit并口等）
	- 其它诸多技术细节：循环角度的均值计算问题、[Flash的启动烧写问题](http://blog.csdn.net/xiahouzuoxin/article/details/22621933)（原创方法）等。
	- 因为测试场地有要求，在外场实验（组员一起）达十多次，合计>40小时
3. 成果：凭技术策划书获得获得 __55万项目总经费__。 实际场景测向精度7°，识别率为86.7%。12月份通过中期验收。

### 2012.06-2013.05，支持向量机结合条件随机场的图像目标识别

1. 背景：老师指导下在graz-02数据上做Sematic Segmentation，时常1年，并顺便作为[本科毕设论文](http://xiahouzuoxin.github.io/notes/projects/基于支持向量机与条件随机场的图像目标识别/基于支持向量机与条件随机场的图像目标识别-正文.pdf)
3. 任务：
	- 熟悉工具（LibSVM、VLFeat、gco-v3.0）；参考论文，构建基于超像素的图像识别框架；
	- 对比SIFT、Textons、denseColor等特征，最终确定使用直方图融合多种特征；
	- 对比SLIC、QuickShift分割超像素的方法，最终由于SLIC分割区域的大小一致性好而作为首选方法
	- 使用K-Means形成bag of features；优化K-Means为HIKM；
	- Girdsearch对SVM进行参数寻优(主要是核函数的gamma以及惩罚项系数C)；
	- SVM分类器的输出作为CRF的Unary term输入，CRF平滑图像分割边缘
3. 成果：对graz-02数据库中cars的目标识别精度达到 __78.9%__ ，ICCV2009论文"Class Segmentation and Object Localization with Superpixel Neighborhoods"仅达到 __72.2%__， 提高6.7%。

### 2010.09-2013.09，机器人（电脑鼠）研发与制作

1. 背景：电脑鼠是一种自主走迷宫的机器人，团队成员共8人，为本科期间主项目。团队目的
	- 为北京科技大学计通学院提供暑期实习产品，为学校提供科技展示平台
	- 参加全国电脑鼠走迷宫竞赛，为学院提供学习环境
3. 任务（主车手、2013年领队）：
	- 主控芯片使用STM32F103RBT6(M3内核)和STM32F405RG(M4内核)，Cadence进行PCB设计
	- 红外信号处理：中值+低通滤波去脉冲噪声，样条插值对红外测距数据进行拟合
	- 直流电机控制：编码器的里程计数，PID闭环控制
	- 电子罗盘：使用一阶Kalman滤波，建立速度差（二次函数）连续转弯模型
	- 系统调试：不分昼夜地在Keil IDE上现场调试程序（持续3-4个月）
	- 另：机器人迷宫搜索算法由另外一名队员主要负责，主要涉及绝对方向与相对方向的坐标变换、DFS和BFS的搜索策略决策等
3. 成果：
	- 2011年，为北京科技大学暑期实习 __提供产品78套__
	- 2012年，4支机器人在参加2012年计算机学会主办的全国电脑鼠走迷宫竞赛中分获 __1特等奖，2一等奖，1二等奖__
	- 2012年获奖后在CCTV13报道，五四青年节展示被赤兔网采访报道，中学生暑期夏令营展示
	- 以队长身份组织以成果组织参加北京科技大学 __摇篮杯(挑战杯预选赛)获三等奖__。

### 2012.06-2012.07，基于支持向量机的图片分类

1. 背景：2012年暑期实习任务，机器学习课程设计
2. 任务：
	- 风景与建筑图片分类：（1）高斯平滑图像，计算梯度统计直方图作为特征；（2）比较并选择SVM优化函数（C-SVM/nu-SVM）；RBF核函数将特征高维映射，训练模型参数gamma；交叉验证。
	- 手写数字奇偶判别：（1）采集数据并进行预处理（加Label，resize等）；（2）先进行膨胀操作再计算手写数字图片的欧拉数(E=C-H)作为识别主特征。LibSVM训练识别。
3. 成果: 风景建筑图片分类精度（百分比）88.5%([Github](https://github.com/xiahouzuoxin/image_classification))；手写数字识别率89.7%。

### 2012.04-2012.06，JPEG图像编解码实现

1. 背景：数字图像处理课程设计
2. 任务：
	- Visual Studio用Windows系统接口读取bmp格式图片，准备压缩数据
	- C实现JPEG编码流程：分块DCT算法(简化标准jpeg的小波编码为DCT，8x8的分块大小，用8x8的DCT算法) ==> 量化压缩(存在信息损失) ==> 相邻块间的差分脉冲调制编码（DPCM） ==> Huffman编码 ==> 形成Bitstream
3. 成果：提交C程序和报告

### 2012.02-2012.02，宿舍温度监控节点

1. 背景：坐在宿舍没事，做个温度监控节点放在阳台上，在电脑旁就能看到宿舍的实时温度
2. 任务：
	- 搭建硬件，用8051单片机读取DS18B20温度传感器数据，串口输出，数码管显示
	- LabVIEW制作温度显示上位机；解决下位机数据通过串口到上位机的数据格式转换问题
3. 成果：搭建完整系统，写成[小报告](https://xiahouzuoxin.github.io/notes/pdf/基于计算机LabVIEW终端的温度监控系统.pdf)

## <font color=red>== 获奖/证书 ==</font>

|时间 | 名称| 级别 |
|----|----|----|
|2015年05月22日|AWSome Day认证证书||
|2012年05月01日|电脑鼠走迷宫大赛全国季军、北京市一等奖|国家级、省市级|
|2012年10月01日|美新杯物联网创新创业大赛北京市三等奖|省市级|
|2011年12月10日|智能车校内赛二等奖|院校级|
|2012年12月01日|校级三好学生|院校级|
|2012年12月01日|人民奖学金二等|院校级|
|2012年04月01日|摇篮杯(挑战杯预选赛)三等奖|院校级|
|2009年12月25日|《北科大青年》征文大赛三等奖|院校级|
