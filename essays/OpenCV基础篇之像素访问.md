[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

## 程序及分析

```c
/*
 * FileName : get_pixels.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sun 01 Jun 2014 06:40:54 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Usage: ./get_pixels [imag name]" << endl;
        return -1;
    }

    Mat img;
    
    img = imread(argv[1], 1);
    

    /*
     * Reverse pixels
     */
    Mat out1 = img.clone();  // change dst will not affect img

    long n_rows = out1.rows;
    long n_cols = out1.cols * out1.channels();

    /*
     * Row pointer
     */
    uchar *p;
    for (long i=0; i<n_rows; i++) {
        p = out1.ptr<uchar>(i);
        for (long j=0; j<n_cols; j++) {
            p[j] = 255 - p[j];
        }
    }

    /*
     * Element pointer
     */
    Mat out2;
    out2.create(img.size(), img.type());  // reserve size and type but alloc new space

    n_rows = out2.rows;
    n_cols = out2.cols * out2.channels();

    p = out2.data;
    double c = 0.5;
    double b = 30;
    for (long i=0; i<n_rows*n_cols; i++) {
       *(p+i) = (uchar)(255 * 0.5 * ((double)(img.data[i]) / 255) + b);
    }

    /*
     * Display
     */
    namedWindow("src_image", CV_WINDOW_NORMAL);
    imshow("src_image", img);
    namedWindow("reverse_image", CV_WINDOW_NORMAL);
    imshow("reverse_image", out1);
    namedWindow("mici_image", CV_WINDOW_NORMAL);
    imshow("mici_image", out2);

    waitKey(0);

    return 0;
}
```

1.	基于元素指针的像素访问：根据Mat的数据结构，按理我们可以通过Mat.data访问像素数据的指针，再根据指针访问到像素数据，这是最直接的方法，一般图片数据在内存中都是连续存储（一般应该使用is_continues()进行判断，注意上面程序中没有，因为大部分情况是连续存储的，所以没有考虑），这种访问像素方式的一般格式是：

	```
	uchar *p;  // 定义一个像素索引指针
	p = image.data;  // image为Mat对象，将对象的数据指针赋值给p
	for (long i=0; i < image.rows*image.cols*image.channels(); i++) {
		*p++ = ..;  // 通过索引指针操作数据
	}
	```

	上面程序通过元素指针的方法给出了一个幂次变换的例子：

	```
	*(p+i) = (uchar)(255 * 0.5 * ((double)(img.data[i]) / 255) + b);
	```

	幂次变换是一种很好用的图像增强的方法，我的Github上还有一个Matlab写的用幂次变换处理外出爬山风景照片的例子（https://github.com/xiahouzuoxin/zx_photo）

2.	基于行指针的访问：OpenCV中定义了一个ptr方法，是一个模板：

	```
	// returns pointer to the matrix element
	// idx – rows,you should use @isContinues() before decided it
	template<int n> uchar* ptr(const Vec<int, n>& idx);
	```
	通过ptr<uchar>(i)直接获得Mat对象的第i行的指针，跟二维数组的行指针有些类似，继而可以通过ptr<uchar>(i)[j]得到第i行第j列的像素值。

	上面程序给出了使用行指针进行图像反转的例子。

3.	请注意一下其它的函数：img.clone()之前已经讲过——除了拷贝Mat数据结构的头和数据指针，连数据也一块拷贝，并将数据指针指向新拷贝的数据。


## 效果

![result]

左边是元素图片，中间是经过图片反转之后的图片，右边是使用幂次变换增强后的图片。

[result]:../images/OpenCV基础篇之像素访问/result.png