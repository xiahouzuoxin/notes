[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>


## 在MATLAB中配置C语言编译器

在这之前必须安装好编译器，可以是VC完整版，绿色版貌似不行啊，

1\.	`mex –setup`设置编译器选项，将入口函数为mexFunction的C/C++文件编译成mex(DLL)文件

```	
>> mex -setup
Please choose your compiler for building external interface (MEX) files: 
 
Would you like mex to locate installed compilers [y]/n? y
 
Select a compiler: 
[1] Microsoft Visual C++ 2008 SP1 in D:\Program Files\VS2008 
 
[0] None 
 
Compiler: 1
 
Please verify your choices: 
 
Compiler: Microsoft Visual C++ 2008 SP1  
Location: D:\Program Files\VS2008 
 
Are these correct [y]/n? y
 
*************************************************************************** 
  Warning: MEX-files generated using Microsoft Visual C++ 2008 require 
           that Microsoft Visual Studio 2008 run-time libraries be  
           available on the computer they are run on. 
           If you plan to redistribute your MEX-files to other MATLAB 
           users, be sure that they have the run-time libraries. 
*************************************************************************** 
 
Trying to update options file: C:\Users\Administrator\AppData\Roaming\MathWorks\MATLAB\R2010b\mexopts.bat 
From template:              D:\PROGRA~1\MATLAB\R2010b\bin\win64\mexopts\msvc90opts.bat 
 
Done . . . 
```

2\. `mbuild -setup`设置编译器选项，将入口函数为main的C/C++文件生成可以独立运行的C应用程序

```
>> mbuild -setup
Please choose your compiler for building standalone MATLAB applications: 
 
Would you like mbuild to locate installed compilers [y]/n? y
 
Select a compiler: 
[1] Microsoft Visual C++ 2008 SP1 in D:\Program Files\VS2008 
 
[0] None 
 
Compiler: 1
 
Please verify your choices: 
 
Compiler: Microsoft Visual C++ 2008 SP1  
Location: D:\Program Files\VS2008 
 
Are these correct [y]/n? y
 
**************************************************************************** 
  Warning: Applications/components generated using Microsoft Visual Studio   
           2008 require that the Microsoft Visual Studio 2008 run-time       
           libraries be available on the computer used for deployment.       
           To redistribute your applications/components, be sure that the    
           deployment machine has these run-time libraries.                  
**************************************************************************** 
 
Trying to update options file: C:\Users\Administrator\AppData\Roaming\MathWorks\MATLAB\R2010b\compopts.bat 
From template:              D:\PROGRA~1\MATLAB\R2010b\bin\win64\mbuildopts\msvc90compp.bat 
 
Done . . . 
```

## MATLAB调用C程序测试

1.	C代码如下，文件名为test.c，假设保存在E:/test下，

	```c
	#include "mex.h"
	#include <stdio.h>
	void mexFunction(int nlhs, mxArray *plhs[], 
	                 int nrhs, const mxArray *prhs[]) 
	{
	    printf("Hello, %d\n", add(2,3));
	}
	 
	int add(int a, int b)
	{
	    return (a+b);
	}
	```
	
2.	在MATLAB中运行`cd E:/test`转到存放C文件路径，使用`mex test.c`编译，然后运行test，则在Commond windows下输出Hello World, 5!

3.	在C/C++中引用常用头文件

	```
	#include "mex.h"
	#include "matrix.h"
	```

4.	在C/C++中常用与matlab操作相关的函数

	mexErrMsgTxt : 打印错误信息，会中断程序执行
	
	mxGetM/mxGetN：获取matlab中矩阵的行列
	
	mxGetPr : 获取输入矩阵的指针
	
	mxGetScale:如果传入的为单个值，则获取传入的值
	
	mxCreateNumericMatrix/mxCreateDoubleMatrix:创建输出矩阵

	```
	void
	mexFunction(int nout, mxArray *out[],
	            int nin, const mxArray *in[])
	{
		uint32 n_center;
		uint32 n_data;
		uint32 dims;
		uint32 *ids;
		datatype *data;
		datatype *center;
		optstype opts;
	
		enum {IN_CENTER=0, IN_DATA, IN_OPTS};
		enum {OUT_ASSIGN=0};
	
		/* check arguments and load data */
		if (nin < 2) {
			mexErrMsgTxt("At least two aguments required.");
	    } else if (nin < 3) {
	        opts = 1;
	    } else {
	        opts = mxGetScalar(in[IN_OPTS]);
	        if (opts > 1) {
	            mexErrMsgTxt("options must between [0:'l1' 1:'l2'].");
	        }
	    }
		if (nout > 1)
			mexErrMsgTxt("Too many output arguments.");
	
		/* load data */
		n_center = mxGetN(in[IN_CENTER]);
		dims = mxGetM(in[IN_CENTER]);
	    if (dims != mxGetM(in[IN_DATA])) {
	        mexErrMsgTxt("dimension of CENTER dismatch DATA.");
	    }
		center = mxGetPr(in[IN_CENTER]);
		n_data = mxGetN(in[IN_DATA]);	
		data = mxGetPr(in[IN_DATA]);
	
		/* output */
		out[OUT_ASSIGN] = mxCreateNumericMatrix(1, n_data, mxUINT32_CLASS, mxREAL);
		ids = (uint32 *)mxGetPr(out[OUT_ASSIGN]);
	
		kmeanspush(center, n_center, data, ids, n_data, dims, opts);
	}
	```

5.	MATLAB矩阵与C/C++数组之间的转换

	matlab中的元素索引从1开始，而C/C++则是从0开始。

	matlab中的矩阵索引顺序是从列开始的，因此matlab中的a(i,j)将转化为C/C++中的a[j'][i'] (其中j'=j-1, i'=i-1)


## C程序调用MATLAB测试

1.	编写C程序后后使用下面的编译选项
	mcc -B csharedlib:MyFunc MyFunc.m

2.	在C编译器中使用共享库来调用matlab程序
