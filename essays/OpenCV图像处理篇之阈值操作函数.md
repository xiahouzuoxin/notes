<!---title:OpenCV图像处理篇之阈值操作函数-->
<!---keywords:OpenCV-->
<!---date:2014-11-12-->

## 阈值操作类型

这5种阈值操作类型保留opencv tutorials中的英文名称，依次为：

1.	Threshold Binary：即二值化，将大于阈值的灰度值设为最大灰度值，小于阈值的值设为0。
2.	Threshold Binary, Inverted：将大于阈值的灰度值设为0，大于阈值的值设为最大灰度值。
3.	Truncate：将大于阈值的灰度值设为阈值，小于阈值的值保持不变。
4.	Threshold to Zero：将小于阈值的灰度值设为0，大于阈值的值保持不变。
5.	Threshold to Zero, Inverted：将大于阈值的灰度值设为0，小于阈值的值保持不变。

OpenCV提供了`threshold`函数专门用于阈值操作，其实实现起来很简单，为什么非得调用函数呢？一是熟悉了调用函数很方便，如果一行代码能搞定的事为什么非得用几个循环呢？二是对于新手，自己实现未必敢保证运行效率上未必能达到opencv那样好。

## 程序分析

```c
/*
 * FileName : filter_and_threshold.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Sat 20 Sep 2014 07:04:29 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat src,gray,dst;

const char *wn = "Demo";
int th_val = 0;
int th_type = 3;
int const max_val = 255;
int const max_type = 4;
int const max_BINARY_val = 255;

static void Thresh(int, void *)
{
	/*
	 * 0: Binary
	 * 1: Binary Inverted
	 * 2: Threshold Truncated
	 * 3: Threshold to Zero
	 * 4: Threshold to Zero Inverted
	 */
	
	threshold(gray, dst, th_val, max_BINARY_val, th_type);

	imshow(wn, dst);
}

/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout<<"Usage: ./threshold [file name]"<<endl;
        return -1;
    }

	// read image as GRAYSCALE
	src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!src.data) {
        cout<<"Error: read data"<<endl;
        return -1;
    }

	// window to display
	namedWindow(wn);
	createTrackbar("Value", wn, &th_val, max_val, Thresh);  /* bar */
	createTrackbar("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted", 
            wn, &th_type, max_type, Thresh);

    cvtColor(src, gray, CV_RGB2GRAY);

	// Init by Calling Thresh
	Thresh(0, 0);

	// wait if ESC be pressed
	while(1)
	{
		char c = waitKey(20);

		if(c == 27)         /* ESC */
		{
			break;
		}
	}
}
```

1.	整个程序就一句话是关键：

	```c
	threshold(gray, dst, th_val, max_BINARY_val, th_type);
	```

	threshold的参数依次是原灰度图、输出阈值操作后的图、阈值、最大灰度值以及阈值类型。其中，最大灰度值并不一定就是255，在上面提到的阈值操作1和2中提到，“设为最大灰度值”，如果你觉得不像让图像的最大灰度值大于200，那就设为200就好了。阈值类型取值为0~4，按顺序依次对应前面提到的5种阈值操作类型。

2.	`createTrackbar`是创建滑动条的gui函数。以`createTrackbar("Value", wn, &th_val, max_val, Thresh);`为例，该滑动条值与变量`th_val`的值关联，一旦`th_val`改变，自动调用回调函数Thresh，`createTrackbar`使用的回调函数格式必需是程序中的`void Thresh(int, void *)`，即返回void，参数含`int`和`void *`类型。

## 效果

![原图-林依晨]
![结果-使用阈值操作2]

林依晨的的图片被我P一下就成那样了！上面的第二幅图片使用的是阈值操作2。

![原图-未知美女一枚]
![结果-使用阈值操作3]

这回是未知美女一枚，使用阈值操作方法3后的结果如右图，感觉没什么差别，有木有？确实差别不大，谁叫人家头发本来就那么黑那么靓丽呢！细看还是能看出来眉毛变细了，发丝变黑了。


[原图-林依晨]:../images/OpenCV图像处理篇之阈值操作函数/原图-林依晨.png
[结果-使用阈值操作2]:../images/OpenCV图像处理篇之阈值操作函数/结果-使用阈值操作2.png
[原图-未知美女一枚]:../images/OpenCV图像处理篇之阈值操作函数/原图-未知美女一枚.png
[结果-使用阈值操作3]:../images/OpenCV图像处理篇之阈值操作函数/结果-使用阈值操作3.png


