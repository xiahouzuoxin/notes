[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

## 统计代码行数

统计单个文件直接使用`wc -l file`命令即可，统计某个目录下所有某类型文件的行数：

```
find . -name *.[ch] | xargs wc -l | sort -n
```

表示统计当前目录下.c与.h文件的行数，并按行数大小排序.

