<!---title:CentOS更新yum源的方法-->
<!---keywords:CentOS,yum-->
<!---date:old-->

操作环境：CentOS 6.5 64bit 宽带外网

## 国内的yum源都在哪里

1.	上海交大：<http://ftp.sjtu.edu.cn/centos/>，地理位置在北方，教育网中较快
2.	中国科大：<http://centos.ustc.edu.cn/>，地理位置在合肥，南方
3.	网易163：<http://mirrors.163.com/centos>，外网推荐
4.	搜狐镜像：<http://mirrors.sohu.com/>，山东联通网络


## 如何替换原有的yum源

本文将替换原来CentOS官方的yum为163的yum源：

```shell
su root
cd /etc/yum.repos.d
mv CentOS-Base.repo CentOS-Base.repo.bak                 # 备份原有的yum源
wget http://mirrors.163.com/.help/CentOS6-Base-163.repo  # 获取163的yum源文件
mv CentOS6-Base-163.repo CentOS-Base.repo                # 使用163的yum源作为默认的yum源
yum clean all && yum makecache && yum update -y          # yum更新
```

网易613提供了yum源的CentOS-Base.repo文件，而上海交大和中科大的yum源可能需要自己写，相对来说，使用163的yum更新更方便些。

## Fedora的更新源

```
cd /etc/yum.repos.d
wget http://mirrors.163.com/.help/fedora-163.repo
wget http://mirrors.163.com/.help/fedora-updates-163.repo
wget http://mirrors.sohu.com/help/fedora-sohu.repo
wget http://mirrors.sohu.com/help/fedora-updates-sohu.repo
yum makecache
```