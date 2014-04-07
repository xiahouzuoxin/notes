[<font size=4>←返回主目录<font>](./README.md)
</br></br></br>

由于已经对git使用比较熟悉了，此篇关于git分支和版本的的管理将不会详细记录每一个细节。如果你还不熟悉git，请先参看：

[1] http://blog.csdn.net/xiahouzuoxin/article/details/9393119

[2] http://blog.csdn.net/xiahouzuoxin/article/details/9398629

[3] http://blog.csdn.net/xiahouzuoxin/article/details/18076043

## 本地的分支管理

创建分支，你可以使用

```
git branch dev
```

这就创建了一个dev（development之意），更好的，选择使用下面的方法创建两个分支——dev，创建后会自动切换到新创建的分支，

```
git checkout -b dev
```

要切回master分支怎么办？使用

```
git checkout master
```

当然你也可以使用

````
git checkout dev 
```

再次切换到dev分支。

好了，现在有两个分支：master和dev了。比如切来切去，突然暂停手下的活要先撸一把，撸完回过头不知道现在在哪个分支了，怎么办？

```
git branch
```

![git-branch]

搞定，git branch可以查看当前已有的分支信息，并在将当前所在分支高亮，当前分支前还有个*号。


某天要调试某个新算法，又不能保证能调好，又怕打乱了原有的程序，怎么办？建一个新分支：

```
git checkout -b debug
```

在debug分支中慢慢玩，master分支和dev分支毫不受影响。这时就有两种情况：

- 悲剧的最后还是没调出来，我又有强迫症，debug分支一直放在那总是不爽，删了


```
git branch -d debug
```


- 恭喜，算法调试成功，我要合并到master中


```
git checkout master   // 切换到master
git merge debug       // 合并debug到master 
```

这时如果你很幸运，直接合并成功。悲伤的事情总是时有发生，“合并发生冲突”是常有的事，因此一旦出现类似下面的提示

```
CONFLICT (content): Merge conflict in ...
Automatic merge failed; fix conflicts and then commit the result.
```

就得自己动手解决冲突了，git会用 


```
<<<<<<<HEAD
 master原有的内容
=======
 debug分支中冲突的内容
>>>>>>>debug
```

这样的格式提醒你，只要修改保留实际需要的内容后即可解决冲突，解决冲突后就可以执行git commit。

好了，我们合并了master和debug，做IT的人总会偷个腥，想看看git是怎么记录合并的，没问题，

```
git log --graph --pretty=oneline --abbrev-commit
```

就可以直接看到分支合并的过程。我这有个大点的工程合并效果的例子，

![example]


最后，反正debug我玩完了，删除debug分支

```
git branch -d debug
```

## 远程的分支管理

我们所有的开发工作都在dev上进行，一旦有了大的突破，则合并到master。

- 既然有了dev分支，我也要把它推送到github上

如果不在dev，切换到dev，

```
git branch
git checkout dev 
```

还记得我们之前推送master分支到远程origin吗？

```
git push -u origin master
```

推送dev也是一样的，只要指定分支名为dev就可以了，

```
git push -u origin dev 
```

- 同学A开头写了个项目，老板让我也跟着做，同学A说，你到github上图clone我的代码吧

```
git clone git@github.com:....
```

这是，你用git branch看看，这只是clone了master分支，dev呢？这可是费劲苦心，要在同学A的dev分支上开发，就必须创建远程的dev分支到本地

```
git checkout -b dev origin/dev 
```

再用git branch看看？有了吧。

- 在同学A的基础上我又添了新功能，老板催着，赶紧提交

```
git checkout dev 
git pull origin dev 
```

- 老板某天突然和我说：你看同学A，又修改了好多Bug，还不下下来学学

```
git pull origin dev  
```

可能出现冲突，解决后才能进行下一次的提交。

极少的场合，要不就是老板的老婆月经乱了，要不就是。。。哎，不说了，非要删除远程dev分支，也是有办法的，

```
git push oringin :dev 
```

## 本地Tag管理

哇，第一个里程碑式的突破，有木有，这时你可小小的庆幸一下，打个标签（Tag），表示这是个可靠的可发布版本，

```
git tag -a v1.0 -m "第一个里程碑的突破"
```

当然，注释别向上面一样（"第一个里程碑的突破"）写得那么没有营养。起个好名字很重要。默认的标签将打在最新的commit上。

查看打了哪些标签使用

```
git tag 
```

查看某个标签的信息用

```
git show v1.0
```

好了，好马也有失前蹄的时候，标签打错也是正常的，

```
git tag -d v1.0
```

果断删了v1.0标签。


## 远程Tag管理

我想要把v1.0推送到远程，

```
git push origin v1.0
```

把所有的标签一次推送到远程更爽，

```
git push origin --tags
```

删除远程的标签，你可以到github上删除，也可以，

- 先删除本地的

```
git tag -d v1.0
```

- 删除远程的

```
git push origin :refs/tags/v1.0
```

## 结尾及参考

好了，告一段落了，接着就是使用git策马奔腾吧！

[1] [廖雪峰Git教程](http://www.liaoxuefeng.com)


[git-branch]:../images/Git版本和分支管理/git-branch.png
[example]:../images/Git版本和分支管理/example.png