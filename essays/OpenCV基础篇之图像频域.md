<!---title:OpenCV基础篇之图像频域-->
<!---keywords:OpenCV-->
<!---date:2014-09-16-->

## 程序及分析

```c
/*
 * FileName : fft2.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Wed 30 Jul 2014 09:42:12 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout<<"Usage:./fft2 [image name]"<<endl;
        return -1;
    }

    // Read as grayscale image
    Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) {
        cout << "Read image error"<<endl;
        return -1;
    }

    Mat padded;
    int m = getOptimalDFTSize(image.rows);  // Return size of 2^x that suite for FFT
    int n = getOptimalDFTSize(image.cols);
    // Padding 0, result is @padded
    copyMakeBorder(image, padded, 0, m-image.rows, 0, n-image.cols, BORDER_CONSTANT, Scalar::all(0));

    // Create planes to storage REAL part and IMAGE part, IMAGE part init are 0
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);

    dft(complexI, complexI);

    // compute the magnitude and switch to logarithmic scale
    split(complexI, planes);
    magnitude(planes[0], planes[0], planes[1]);
    Mat magI = planes[0];

    // => log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))
    magI += Scalar::all(1);
    log(magI, magI);

    // crop the spectrum
    magI = magI(Rect(0, 0, magI.cols & (-2), magI.rows & (-2)));
    Mat _magI = magI.clone();
    normalize(_magI, _magI, 0, 1, CV_MINMAX);

    // rearrange the quadrants of Fourier image so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0,0,cx,cy));    // Top-Left
    Mat q1(magI, Rect(cx,0,cx,cy));   // Top-Right
    Mat q2(magI, Rect(0,cy,cx,cy));   // Bottom-Left
    Mat q3(magI, Rect(cx,cy,cx,cy));  // Bottom-Right

    // exchange Top-Left and Bottom-Right
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    
    // exchange Top-Right and Bottom-Left
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX);

    imshow("Input image", image);
    imshow("Spectrum magnitude before shift frequency", _magI);
    imshow("Spectrum magnitude after shift frequency", magI);
    waitKey();

    return 0;
}
```

本程序的作用是：将图像从空间域转换到频率域，并绘制频域图像。

1.	二维图像的DFT（离散傅里叶变换），

	<img src="http://www.forkosh.com/mathtex.cgi? \Large F(k,l)={\sum_{i=0}^{i=N-1}}{\sum_{j=0}^{j=N-1}}f(i,j)e^{-j2\pi{(\frac{ki}{N}+\frac{lj}{N}})}">

	图像的频域表示的是什么含义呢？又有什么用途呢？图像的频率是表征图像中灰度变化剧烈程度的指标，是灰度在平面空间上的梯度。图像的边缘部分是突变部分，变化较快，因此反应在频域上是高频分量；图像的噪声大部分情况下是高频部分；图像大部分平缓的灰度变化部分则为低频分量。也就是说，傅立叶变换提供另外一个角度来观察图像，可以将图像从灰度分布转化到频率分布上来观察图像的特征。

	频域在图像处理中，就我所知的用途主要在两方面：图像压缩和图像去噪。关于这两点将在下面给出图片DFT的变换结果后说明。

	有关DFT的更多性质请参考胡广书教授的《数字信号处理》教材。

2.	请注意读图片的函数与之前有所不同：

	```c
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	```

	`CV_LOAD_IMAGE_GRAYSCALE`参数表示将原图像转换为灰度图后读入，这是因为后面的DFT变换都是基于二维信号的，而彩色图像是三维信号。当然，也可以对RGB每一通道都进行DFT运算。

3.	DFT算法的原理要求输入信号的长度最好为2^n，这样可以使用快速傅里叶变换算法（FFT算法）进行加速。所以程序中使用

	```c
	copyMakeBorder(image, padded, 0, m-image.rows, 0, n-image.cols, BORDER_CONSTANT, Scalar::all(0));
	```
	
	填充0使横纵长度都为2^n。

	对于一维信号，原DFT直接运算的复杂度是O(N^2)，而快速傅里叶变换的复杂度降低到O(Nlog2(N))，假设N为512，足足提高了512/9≈57倍。

4.	由DFT的性质知，输入为实信号（图像）的时候，频域输出为复数，因此将频域信息分为幅值和相位。频域的幅值高的代表高频分量，幅值低的地方代表低频分量，因此程序中使用

	```c
    // => log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))
    magI += Scalar::all(1);
    log(magI, magI);

    // crop the spectrum
    magI = magI(Rect(0, 0, magI.cols & (-2), magI.rows & (-2)));
    Mat _magI = magI.clone();
    normalize(_magI, _magI, 0, 1, CV_MINMAX);
	```

	进行log幅值计算及归一化幅值（归一化目的主要是方便将频域通过图像的形式进行显示）。

5.	关于频域中心平移：将图像的高频分量平移到图像的中心，便于观测。

	```
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0,0,cx,cy));    // Top-Left
    Mat q1(magI, Rect(cx,0,cx,cy));   // Top-Right
    Mat q2(magI, Rect(0,cy,cx,cy));   // Bottom-Left
    Mat q3(magI, Rect(cx,cy,cx,cy));  // Bottom-Right

    // exchange Top-Left and Bottom-Right
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    
    // exchange Top-Right and Bottom-Left
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
	```

	其原理就是将左上角的频域和右下角的互换，右上角和左下角互换。

	请注意：频域点和空域点的坐标没有一一对应的关系，两者的关系只是上面的DFT公式所见到的。

6.	本程序因为使用到图像处理相关的函数，所以包含了头文件`imgproc/imgproc.hpp`，该文件位于opencv安装目录的include/opencv2/目录下，在编写Makefile时也要增加相关的头文件路径和库，本程序使用的Makefile如下：

	```c
	TARG=fft2
	SRC=fft2.cpp
	LIB=-L/usr/local/lib/
	INC=-I/usr/local/include/opencv/ -I/usr/local/include/opencv2
	CFLAGS=

	$(TARG):$(SRC)
		g++ -g -o $@ ${CFLAGS} $(LIB) $(INC) \
			-lopencv_core -lopencv_highgui -lopencv_imgproc \
			$^

	.PHONY:clean

	clean:
		-rm $(TARG) tags -f 
	```

	其中Makefile中的\表示换行（反斜杠后不能再有任何字符，包括空格），如上库增加了`-lopencv_imgproc`，头文件路径增加了`-I/usr/local/include/opencv2`。
	
## 效果

![dft]

1.	上图从左到右分别是：原始灰度图（我大爱的杨过啊）、频域平移前的频域图像、频域中心平移后的频域图像。

2.	提到图像频域变换的用途：压缩和去噪。压缩的原理就是在频域中，大部分频域的值为0（或接近0，可以进行有损压缩，如jpeg图像），只要压缩频域中的少数非0值即可达到图片压缩的目的。去噪则是通过频域的滤波实现，因为噪声大部分情况下体现为高频信号，使用低通滤波器即可滤除高频噪声（当然，也会带来损失，那就是边缘会变得模糊（之前说过，边缘也是高频信号））。


[dft]:../images/OpenCV基础篇之图像频域/dft.png


