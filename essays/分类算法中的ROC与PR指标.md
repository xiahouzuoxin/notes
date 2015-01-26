<!---title:分类算法中的ROC与PR指标-->
<!---keywords:ROC,PR-->
<!---date:2015-01-26-->

做过图像识别、机器学习或者信息检索相关研究的人都知道，论文的实验部分都要和别人的算法比一比。可怎么比，人多嘴杂，我说我的方法好，你说你的方法好，各做各的总是不行——没规矩不成方圆。于是慢慢的大家就形成了一种约定，用ROC曲线和PR曲线来衡量算法的优劣。关于ROC曲线和PR曲线的详细介绍可参考资料：

1.	[ROC Analysis and the ROC Convex Hull](http://home.comcast.net/~tom.fawcett/public_html/ROCCH/index.html)
2.	Tom Fawcett,[An introduction to ROC analysis](https://cours.etsmtl.ca/sys828/REFS/A1/Fawcett_PRL2006.pdf)
3.	Jesse Davis,Mark Goadrich. [The Relationship Between Precision-Recall and ROC Curves.](https://www.biostat.wisc.edu/~page/rocpr.pdf)，还有一份与这篇文章对应的[PPT讲稿](http://www.ke.tu-darmstadt.de/lehre/archiv/ws0708/ml-sem/Folien/Wen_Zhang.pdf)

有这3份资料足以，应用分析和理论分析都讲得很不错。

## 基本概念

1.	True Positives,TP：预测为正样本，实际也为正样本的特征数
2.	False Positives,FP：预测为正样本，实际为负样本的特征数（错预测为正样本了，所以叫False）
3.	True Negatives,TN：预测为负样本，实际也为负样本的特征数
4.	False Negatives,FN：预测为负样本，实际为正样本的特征数（错预测为负样本了，所以叫False）

接着往下做做小学的计算题：

- TP+FP+FN+FN：特征总数(样本总数)
- TP+FN：实际正样本数
- FP+TN：实际负样本数
- TP+FP：预测结果为正样本的总数
- TN+FN：预测结果为负样本的总数

有些绕，为做区分，可以这样记：相同的后缀（P或N）之和表示__预测__正样本/负样本总数，前缀加入T和F；实际样本总数的4个字母完全不同，含TP（正正得正）表示实际正样本，含FP（负正得负）表示实际负样本。

## ROC曲线和PR曲线

True Positive Rate(TPR)和False Positive Rate(FPR)分别构成ROC曲线的y轴和x轴。

1.	TPR=TP/(TP+FN)，实际正样本中被预测正确的概率
2.	FPR=FP/(FP+TN)，实际负样本中被错误预测为正样本的概率

实际学习算法中，预测率100%的话，TPR=100%和FPR=0，所以TPR越大而FPR越小越好。仅用其中一个作为衡量指标可以吗？考虑这么一种情况，一幅图片假如600x480个像素，其中目标（正样本）仅有100个像素，假如有某种算法，预测的目标为包含所有像素600x480，这种情况下TPR的结果是TPR=100%，但FPR却也接近于100%。明显，TPR满足要求但结果却不是我们想要的，因为FPR太高了。

Precision和Recall（有人中文翻译成召回率）则分别构成了PR曲线的y轴和x轴。

1.	Precision=TP/(TP+FP)，预测结果为有多少正样本是预测正确了的
2.	Recall=TP/(TP+FN)，召回率很有意思，这个其实就=TPR，相对于Precision只不过参考样本从预测总正样本数结果变成了实际总正样本数。

同理，Precision和Recall同时考虑才能确定算法好坏。好了，原来一切尽在尽在下图中，

![图：Confusion Matrix](../images/分类算法中的ROC与PR指标/ConfusionMatrix.png)

既然ROC和PR都是同时要考虑两个指标，一个我好一个你好，到底谁好？画到ROC空间一看便知，如下图，将TPR和FPR分别画在两个坐标轴上，则沿着对角线的方向，离右上角越近，算法效果越好。（由于ROC和PR类似，以下仅讨论ROC空间和ROC曲线。）

![图：ROC空间](../images/分类算法中的ROC与PR指标/ROC-space.png)

一个分类算法，找个最优的分类效果，对应到ROC空间中的一个点。通常分类器的输出都是Score，比如SVM、神经网络，有如下的预测结果：

|no.     | True     | Hyp     | Score   |
| ------ | -------- | ------- | ------- |
|1       | p        | Y       | 0.99999 |
|2       | p        | Y       | 0.99999 |
|3       | p        | Y       | 0.99993 |
|4       | p        | Y       | 0.99986 |
|5       | p        | Y       | 0.99964 |
|6       | p        | Y       | 0.99955 |
|7       | n        | Y       | 0.68139 |
|8       | n        | Y       | 0.50961 |
|9       | n        | N       | 0.48880 |
|10      | n        | N       | 0.44951 |

Table: __TABLE__ 一般分类器的结果都是Score表

True表示实际样本属性，Hyp表示预测结果样本属性，第4列即是Score，Hyp的结果通常是设定一个阈值，比如上表就是0.5，Score>0.5为正样本，小于0.5为负样本，这样只能算出一个ROC值，为更综合的评价算法的效果，通过取不同的阈值，得到多个ROC空间的值，将这些值描绘出ROC空间的曲线，即为ROC曲线。

![图：ROC曲线绘制](../images/分类算法中的ROC与PR指标/ROC曲线绘制.png)

我们只要明白这个基本的点，详细的ROC曲线绘制已经有很多代码了，资料1就提供了Prel直接根据Score绘制ROC曲线的代码，Matlab也有，下载链接：

1.	[Local: prec_rec.m](../codes/分类算法中的ROC与PR指标/prec_rec.zip)
2.	[Mathworks: prec_rec.m](http://www.mathworks.com/matlabcentral/fileexchange/21528-precision-recall-and-roc-curves/content//prec_rec/prec_rec.m)

有了ROC曲线，更加具有参考意义的评价指标就有了，在ROC空间，算法绘制的ROC曲线越凸向西北方向效果越好，有时不同分类算法的ROC曲线存在交叉，因此很多文章里用AUC（即Area Under Curve曲线下的面积）值作为算法好坏的评判标准。关于这里的凸理论可参考文章开头的[资料2]。

与ROC曲线左上凸不同的是，PR曲线是右上凸效果越好，下面是两种曲线凸向的简单比较：

![图：算法在ROC空间与PR空间的不同比较](../images/分类算法中的ROC与PR指标/算法在ROC空间与PR空间的不同比较.png)

作为衡量指标，选择ROC或PR都是可以的。但是资料3显示，ROC和PR虽然具有相同的出发点，但并不一定能得到相同的结论，在写论文的时候也只能参考着别人已有的进行选择了。

