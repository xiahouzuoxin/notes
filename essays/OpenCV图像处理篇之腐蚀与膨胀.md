<!---title:OpenCV图像处理篇之腐蚀与膨胀-->
<!---keywords:OpenCV-->
<!---date:2014-09-19-->

## 腐蚀与膨胀

腐蚀和膨胀是图像的形态学处理中最基本的操作，之后遇见的开操作和闭操作都是腐蚀和膨胀操作的结合运算。腐蚀和膨胀的应用非常广泛，而且效果还很好：

1.	腐蚀可以分割(isolate)独立的图像元素，膨胀用于连接(join)相邻的元素，这也是腐蚀和膨胀后图像最直观的展现
2.	去噪：通过低尺寸结构元素的腐蚀操作很容易去掉分散的椒盐噪声点
3.	图像轮廓提取：腐蚀操作
4.	图像分割
5.	等等...（在文后给出一则简单实用膨胀操作提取车牌数字区域的例子）

_结构元素_是形态学操作中最重要的概念，

![erode_show]  ![dilate_show]

如上图，B为结构元素。

腐蚀操作描述为：扫描图像的每一个像素，用结构元素与其覆盖的二值图像做“与”操作：如果都为1，结果图像的该像素为1，否则为0。

膨胀操作描述为：扫描图像的每一个像素，用结构元素与其覆盖的二值图像做“与”操作：如果都为0，结果图像的该像素为0，否则为1。

以上都是关于二值图像的形态学操作，对于灰度图像：

1.	腐蚀操作

	<img src="http://www.forkosh.com/mathtex.cgi? \Large g(x,y)=erode[f(x,y),B]=\min{\{f(x+dx,y+dy)-B(dx,dy)|(dx,dy)\in{D_B}\}}">

	其中，g(x,y)为腐蚀后的灰度图像，f(x,y)为原灰度图像，B为结构元素。腐蚀运算是由结构元素确定的邻域块中选取图像值与结构元素值的差的最小值。

2.	膨胀操作

	<img src="http://www.forkosh.com/mathtex.cgi? \Large g(x,y)=dilate[f(x,y),B]=\min{\{f(x-dx,y-dy)+B(dx,dy)|(dx,dy)\in{D_B}\}}">

	其中，g(x,y)为腐蚀后的灰度图像，f(x,y)为原灰度图像，B为结构元素。 膨胀运算是由结构元素确定的邻域块中选取图像值与结构元素值的和的最大值。

在灰度图的形态学操作中，一般选择“平摊”的结构元素，即结构元素B的值为0，则上面对灰度图的形态学操作可简化如下：

<img src="http://www.forkosh.com/mathtex.cgi? \Large g(x,y)=erode[f(x,y),B]=\min{\{f(x+dx,y+dy)|(dx,dy)\in{D_B}\}}">

<img src="http://www.forkosh.com/mathtex.cgi? \Large g(x,y)=dilate[f(x,y),B]=\min{\{f(x-dx,y-dy)|(dx,dy)\in{D_B}\}}">

好了，这就是基本的形态学操作——腐蚀和膨胀，下面是使用OpenCV对图像进行腐蚀和膨胀的程序，还是秉承我们一贯的原则：搁下理论，先直观地感觉图像处理算法的效果，实际项目需要时再深入挖掘！

## 程序分析

```c
/*
 * FileName : eroding_and_dilating.cpp
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : Fri 19 Sep 2014 07:42:12 PM CST
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "cv.h" 
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

#define TYPE_MORPH_RECT      (0)
#define TYPE_MORPH_CROSS     (1)
#define TYPE_MORPH_ELLIPSE   (2)

#define MAX_ELE_TYPE         (2)
#define MAX_ELE_SIZE         (20)

Mat src, erode_dst, dilate_dst;

const char *erode_wn  = "eroding demo";
const char *dilate_wn = "dilating demo";

int erode_ele_type;
int dilate_ele_type;
int erode_ele_size;
int dilate_ele_size;

static void Erosion(int, void *);
static void Dilation(int, void *);

/*
 * @brief   
 * @inputs  
 * @outputs 
 * @retval  
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout<<"Usage: ./eroding_and_dilating [file name]"<<endl;
        return -1;
    }

    src = imread(argv[1]);
    if (!src.data) {
        cout<<"Read image failure."<<endl;
        return -1;
    }

    // Windows
    namedWindow(erode_wn, WINDOW_AUTOSIZE);
    namedWindow(dilate_wn, WINDOW_AUTOSIZE);

    // Track Bar for Erosion
    createTrackbar("Element Type\n0:Rect\n1:Cross\n2:Ellipse", erode_wn, 
            &erode_ele_type, MAX_ELE_TYPE, Erosion);  // callback @Erosion
    createTrackbar("Element Size: 2n+1", erode_wn, 
            &erode_ele_size, MAX_ELE_SIZE, Erosion);

    // Track Bar for Dilation
    createTrackbar("Element Type\n0:Rect\n1:Cross\n2:Ellipse", dilate_wn, 
            &dilate_ele_type, MAX_ELE_TYPE, Dilation);  // callback @Erosion
    createTrackbar("Element Size: 2n+1", dilate_wn, 
            &dilate_ele_size, MAX_ELE_SIZE, Dilation);

    // Default start
    Erosion(0, 0);
    Dilation(0, 0);

    waitKey(0);

    return 0;
}

/*
 * @brief   腐蚀操作的回调函数
 * @inputs  
 * @outputs 
 * @retval  
 */
static void Erosion(int, void *)
{
    int erode_type;

    switch (erode_ele_type) {
    case TYPE_MORPH_RECT:
       erode_type = MORPH_RECT; 
       break;
    case TYPE_MORPH_CROSS:
       erode_type = MORPH_CROSS;
       break;
    case TYPE_MORPH_ELLIPSE:
       erode_type = MORPH_ELLIPSE;
       break;
    default:
       erode_type = MORPH_RECT;
       break;
    }

    Mat ele = getStructuringElement(erode_type, Size(2*erode_ele_size+1, 2*erode_ele_size+1), 
            Point(erode_ele_size, erode_ele_size));

    erode(src, erode_dst, ele);

    imshow(erode_wn, erode_dst);
}

/*
 * @brief   膨胀操作的回调函数
 * @inputs  
 * @outputs 
 * @retval  
 */
static void Dilation(int, void *)
{
    int dilate_type;

    switch (dilate_ele_type) {
    case TYPE_MORPH_RECT:
       dilate_type = MORPH_RECT; 
       break;
    case TYPE_MORPH_CROSS:
       dilate_type = MORPH_CROSS;
       break;
    case TYPE_MORPH_ELLIPSE:
       dilate_type = MORPH_ELLIPSE;
       break;
    default:
       dilate_type = MORPH_RECT;
       break;
    }

    Mat ele = getStructuringElement(dilate_type, Size(2*dilate_ele_size+1, 2*dilate_ele_size+1), 
            Point(dilate_ele_size, dilate_ele_size));

    dilate(src, dilate_dst, ele);

    imshow(dilate_wn, dilate_dst);
}
```

1.	膨胀和腐蚀操作的函数分别是`erode`和`dilate`，传递给他们的参数也都依次是原图像、形态学操作后的图像、结构元素ele。本程序中给出了3种结构元素类型，分别是

	```
	#define TYPE_MORPH_RECT      (0)  // 矩形
	#define TYPE_MORPH_CROSS     (1)  // 十字交叉型
	#define TYPE_MORPH_ELLIPSE   (2)  // 椭圆型
	```
	
	再通过OpenCV提供的`getStructuringElement`函数创建Mat类型的结构元素。

	`getStructuringElement`的参数依次是结构元素类型（OpenCV中提供了宏定义MORPH_RECT、MORPH_CROSS和MORPH_ELLIPSE表示）、结构元素大小。

2.	这里我们首次接触了`createTrackbar`函数（声明在`highgui.hpp`中），该函数的功能是给窗口添加滑动条。其原型是：

	```
	CV_EXPORTS int createTrackbar( const string& trackbarname, const string& winname,
                               int* value, int count,
                               TrackbarCallback onChange=0,
                               void* userdata=0);
	```
	
	`trackbarname`为滑动条的名称，将会显示在滑动条的前面，参见结果中的图片显示；
	`winname`为窗口名；
	`value`为滑动条关联的变量，如上面程序中第一个滑动条关联到`erode_ele_type`，表示——当滑动条滑动变化时，erode_ele_type的值发生响应的变化；
	`count`表示滑动条能滑动到的最大值；
	`TrackbarCallback onChange`其实是这个函数的关键，是滑动条变化时调用的回调函数。当滑动条滑动时，value值发生变化，系统立刻调用`onChange`函数，执行相关的操作，回调函数的定义形式是固定的：

	```c
	void onChange(int, void *)
	```

	程序中的回调函数`Erosion`和`Dilation`函数的定义都遵循该形式：

	```
	static void Erosion(int, void *);
	static void Dilation(int, void *);
	```

## 结果及实际应用

对“黑白小猪”进行膨胀操作的变化（随着结构元素大小的变化）如下图：

![dilating_demo]

对“黑白小猪”进行腐蚀操作的变化（随着结构元素大小的变化）如下图：

![eroding_demo]

膨胀与腐蚀在图像处理中具有广泛的用途，比如提取车牌过程中，可以通过膨胀运算确定车牌的区域。如下图为通过sobel算子提取边缘后的车牌，

![car_plate]

为去掉边界，确定车牌在图中的位置，可以通过膨胀操作，结果如下：

![car_plate_dilate]

上图中的红线区域就是膨胀后能用于确定车牌的连通区域，再通过对连通区域的搜索及“车牌的矩形特性”即可确定含有车牌数字在图片中的位置。



[erode_show]:../images/OpenCV图像处理篇之腐蚀与膨胀/erode_show.png
[dilate_show]:../images/OpenCV图像处理篇之腐蚀与膨胀/dilate_show.png
[dilating_demo]:../images/OpenCV图像处理篇之腐蚀与膨胀/dilating_demo.gif
[eroding_demo]:../images/OpenCV图像处理篇之腐蚀与膨胀/eroding_demo.gif
[car_plate]:../images/OpenCV图像处理篇之腐蚀与膨胀/car_plate.png
[car_plate_dilate]:../images/OpenCV图像处理篇之腐蚀与膨胀/car_plate_dilate.png




