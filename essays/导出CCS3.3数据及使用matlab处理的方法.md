[<font size=4>←返回主目录<font>](./README.md)
</br></br></br>

CCS3.3是一款DSP的集成开发环境（IDE）。在做DSP开发时，为验证算法，常常需要使用matlab进行算法验证，验证算法就需要数据。因此，一种交互的方法是：

1. 使用DSP开发板连接CCS
2. 用CCS3.3菜单中的“File->Data->Save..”功能导出DSP内存中的数据到PC的.dat文件中
3. 使用Matlab读取.dat文件，进行数据处理

下面给出使用Matlab读取CCS导出的dat文件的方法：

```
% =========================================================================
% Read *dat file of CCS3.3
% xiahouzuoxin
% 2014.04.21
% =========================================================================

% clc;clear all;close all;

% 对话框选择*.dat文件
[fname,pname]=uigetfile(...
    {'*.dat';'*.*'},'Input *.dat File');

fid = fopen(fullfile(pname,fname));
fseek(fid, 21,-1);  % 去文件头, 21字节，如 1651 1 80000006 0 100

% 按指定格式读取解析
fm = 4;
switch (fm)
    case 4  % 按4Byte格式读，如 0x 80000000
        x = textscan(fid, '%2s %8s');  
        z(:,1) = hex2dec(x{2});        
    case 2 % 按2Byte格式读，如 0x 8000 0000
        x = textscan(fid, '%2s %4s %4s');  
        z(:,1) = hex2dec(x{3});
        z(:,2) = hex2dec(x{2});
    case 1 % 按1Byte格式读，如 0x 80 00 00 00
        x = textscan(fid, '%2s %2s %2s %2s %2s');  
        z(:,1) = hex2dec(x{5});
        z(:,2) = hex2dec(x{4});
        z(:,3) = hex2dec(x{3});
        z(:,4) = hex2dec(x{2});
    otherwise
        z = [];
end

if ~isempty(z)
    % 将数据处理代码放在这里
    
end

fclose(fid);
```

程序中默认DSP内存中数据的存储格式为整数类型，而对于浮点型DSP如TMS320C6713B，常常在内存中是float或double格式存储的，

![][float-double]

这时，我们还需要一个转化为浮点数的操作，因此我写了一个转化为float类型的函数，

```
function y = integer2float(x, ishex)
% =========================================================================
% 有些数据y原本是float类型，在内存中是按float格式存储
% 而现在按整数将其从内存中读出变成了x
% 这个函数就是用于将按整数格式读出的x转变成y
% ishex~=0表示输入为十六进制格式
% 注：要完成该函数，你必须了解IEEE浮点数的格式
%
% xiahouzuoxin
% 2014.04.21
% =========================================================================

if nargin == 2
    if (ishex)
        x = hex2dec(x);
    end
end

[h w] = size(x);
y = zeros(h,w);

for i = 1:h
    for j = 1:w
        sign = bitget(x(i,j),32);
        exponent = bitget(x(i,j),24:31) * 2.^(0:7).';
        fraction = bitget(x(i,j),1:23) * 2.^(-23:-1).';
        y(i,j) = (-1)^sign * (1+fraction) * 2^(exponent-127);
    end
end
```

根据不同的输入情况（可以为十六进制的字符串表示或十进制数，但必须≤8Bytes），使用方法举个例子：

```
>> x='4565A012'
>> y=integer2float(x,1);

>> x = 23974881923;
>> y = integer2float(x)
```

后来发现，Matlab已经早有对应的方法了，

```
y = typecast(uint32(z),'single');
```

可以直接把z转化为解析为单精度浮点数，具体使用请参见

```
>> help typecast
```


[float-double]:../images/导出CCS3.3数据及使用matlab处理的方法/float-double.png

