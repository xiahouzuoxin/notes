<!---title:基于AR谱特征的声目标识别-->
<!---keywords:AR谱,SVM-->
<!---date:2014-11-06-->

本文第一部分先解释AR谱，但并不会给出太多的细节，第二部分介绍几种常见的语音中的特征，有些在之前的博文中已经用过，诸如过零率。第三部分给出实际操作的过程及识别的效果。本文的目标是通过对DSP采集的声音信号提取特征，识别卡车和飞机。

## 关于AR谱

AR模型全称Auto-Regression Model，是通过参数计算信号功率谱的一种方法。在Matlab中计算AR谱很简单：假设有一个1024个点的车辆信号x，

```matlab
y = pyulear(x, 256, 128);
```

![ARspectrum]

AR谱的计算有2个重要的参数：系数阶数、FFT反变换的点数。AR谱是一种递推模型，即用前p个时刻的时域值估计当前第n时刻的值：

<img src="http://www.forkosh.com/mathtex.cgi? x(n)=-\sum_{k=1}^{p}a_kx(n-k)+u(n)">

其中u(n)是噪声输入，系数阶数就是上式中的p。牵扯到FFT，是因为功率谱的计算中可以使用FFT进行快速计算，因此就有离散FFT在单位圆上抽样点数的问题，功率谱的计算公式是：

<img src="http://www.forkosh.com/mathtex.cgi? P_x(e^{jw})=\frac{\sigma^2}{|1+\sum_{k=1}^pa_ke^{-jwk}}|^2=\frac{\sigma^2}{|\sum_{k=0}^{N-1}a_ke^{-jwk}}|^2">

上式中转化后有a0=1，将FFT计算扩充到N点后有a(p+1)...a(N-1)=0，FFT点数就是指的这里用于FFT计算的长度N。

AR谱是一个什么样的概念呢，首先我对功率谱的理解就是：不同频率处的能量值的大小，这个大小并不一定是真实的能量值，但不同频率的能量谱值的相对大小关系却接近真实值，因此不同频率处功率谱值的相对关系比其真实的谱值更重要。比如，车辆在远处的时候能量相对较小，在近处的时候能量较大，但对于平稳的信号，虽然能量值不同，但都具有相似的谱包络，因此我们更关注的是谱在不同频率上的分布大小，就像概率一样，看在哪个频率值（或段）的功率谱大。

通过观察AR谱，我们能清晰的知道：主要的能量都集中在什么频率段，从而对信号进行分析主要关注这些频率段就行了。

AR谱的细节参见胡广书编著《数字信号处理》一书，其C实现参考我的[Github项目](https://github.com/xiahouzuoxin/ar_model)，关于AR的基本理论参见之前的博文“[现代数字信号处理——AR模型](http://blog.csdn.net/xiahouzuoxin/article/details/9904147)”

## 音频信号特征提取

### 1 短时平均能量(Short Time Energy, STE)

<img src="http://www.forkosh.com/mathtex.cgi? STE=\sum_{n=1}^Nx(n)^2">

其中N表示一帧的长度。短时平均能量可用于判断静音帧，静音帧的短时能量小，这比直接通x(n)的最高幅值进行判断稳定性要高。对于静音帧，应该在后续的处理之前去除。通常，语音比音乐含有更多的静音（人说话没有音乐那样着腔带调），因此，语音的平均能量的变化要比音乐中大很多。

### 2 短时过零率(Short Time Zero-Corssing Rate, ZCR)

短时过零率是在一个音频帧内，离散采样信号值由负到正或由正到负的变换次数。

<img src="http://www.forkosh.com/mathtex.cgi? ZCR=\frac{1}{N}\sum_{m=0}^{N-1}|sgn[x_n(m+1)]-sgn[x_n(m)]|">

从某种程序上讲，过零率表达了信号的跳变速度，是频率的一种简单度量。过零率与平均能量结合能用于语音端点检测。在博文[自适应含噪信号过零率算法](../html/自适应含噪信号过零率算法.html)中也曾尝试改进过零率用于震动信号的识别。

### 3 子带能量比（Sub-band energy ratio, SER)

子带能量用于描述主要能量的频域分布特征，其过程就是将频域等间隔划分成B个子带，在AR谱图上，对每个子带范围进行积分就可求出子带能量Ei，则子带能量比就是

<img src="http://www.forkosh.com/mathtex.cgi? \frac{E_i}{E_{all}},i=1,...B">

不同音频信号的能量分布不同，通过子带能量能区分能量的主要分布频带。子带能量比是一个很好参数，用于识别频率能量分布不同的目标。当然类似的思想也可以用到FFT频谱图上。

### 4 谱频率重心（Spectrum Centroid, SC）

将AR谱的幅值看做权值w，则谱频率重心的计算是：

<img src="http://www.forkosh.com/mathtex.cgi? SC=\frac{w_k*f_k}{\sum{w_k}},k=1,...N/2">

谱频率重心是通过谱峰统计的中心，并不会（当然也可能等于）等于AR谱主峰对应的频率。

### 5 带宽（Band Width, BW）

带宽指信号谱值下降到中心频率谱值的0.707处的高低频率差BW=fH-fL。

## 基于支持向量机的识别

卡车和飞机的主频位置可能存在不同，所以使用声音信号AR谱的最高峰值对应的频率Fmax作为一个特征维度；另外使用谱频率重心和子带能量比分别作为特征的另两个维度。因此，最后组合特征为{Fmax,SC,SER}。

值得注意的是，本文使用的谱频率重心不是简单的对所有频域进行统计计算，而是：

1.	先对频谱org_psd进行从高到低排序，排序后的psd以及对应的频率索引为idx

2.	选择部分具有高的谱值（这些谱值的和占整个频域谱值和的0.707）进行频谱重心计算，这样能避免一些高频噪声的影响。

识别使用支持向量机（SVM）模型，关于支持向量机，对于没太多基础的可以参考July的博文[支持向量机通俗导论（理解SVM的三层境界）](http://blog.csdn.net/v_july_v/article/details/7624837)，有一点基础的可以看看[林智仁老师的讲义](http://download.csdn.net/detail/xiahouzuoxin/5778927)，这里使用的工具箱就是林智仁的LibSVM，可以从软件主页 <http://www.csie.ntu.edu.tw/~cjlin/libsvm/index.html> 中下载到。

实际操作通过自己设计的DSP+FPGA控制AD7606采集声音信号，将声音信号上传到PC的matlab上进行训练，提取特征。很重要的一点是：使用分类算法（比如这里的LibSVM支持向量机或其它的如神经网络等）进行分类的前提是数据本身可分，如下为卡车和飞机的特征可视化结果，从图中可以看出，两类样本使用上面构造的特征可分，因此才可以接着做识别的工作。

![特征]

使用LibSVM训练，核函数使用RBF，效果一般比其它的要好一些，这里大部分参数默认（主要有gamma和C参数）。要使用LibSVM获得好的效果，请参考我的另一篇博文“[LibSVM笔记系列（2）——如何提升LibSVM分类效果](http://blog.csdn.net/xiahouzuoxin/article/details/9372805)”，主要是一些关于如何搜索获得最佳参数的方法。

实验总共数据1400组，卡车和飞机各选200组用于训练（代码为实际代码的一部分，由于其它原因，暂时无法公开代码），

```
n_trian = 200;

label_car = zeros(length(car_feat),1);
label_plane = ones(length(plane_feat),1);

instance = [car_feat(idx,1:n_trian) plane_feat(idx,1:n_trian)];   % idx表示第idx维的特征
instance = instance';
label = [label_car(1:n_trian); label_plane(1:n_trian)];
model = svmtrain(label, instance, '-s 0 -t 2');  % SVM训练结果为model模型，这个模型将用于下面的预测
```

其余的1000组用于测试，

```
tests = [car_feat(idx,(n_trian+1):end) plane_feat(idx,(n_trian+1):end)];
test_label = [label_car((n_trian+1):end); label_plane((n_trian+1):end)];
tests = tests';
pd_label = svmpredict(test_label, tests, model);
fprintf('\n识别正确率%.4f\n', length(pd_label(test_label==pd_label))/length(test_label));
```

最后的预测结果如下：

![识别结果]

预测正确率达到86.50%，能使用到到实际当中。



[ARspectrum]:../images/基于AR谱特征的车辆识别/ARspectrum.jpg
[特征]:../images/基于AR谱特征的车辆识别/特征.jpg
[识别结果]:../images/基于AR谱特征的车辆识别/识别结果.jpg

