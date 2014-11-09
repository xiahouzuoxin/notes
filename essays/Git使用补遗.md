<!---title:Git使用补遗-->
<!---keywords:工具-->
<!---date:old-->

## 删除错误提交

噢，My God，不小心把含有私有密码信息的版本提交了，还提交到了Github………没问题：

```
git log                        # 查看要回退的版本
git reset --hard <commit-id>   # 回退到commit-id>版本
git push origin HEAD --force   # 远程版本回退
```

## 暂时保存而不提交当前工作

现在正在进行debug分支的工作，突然发现，之前软件存在一个严重的错误，因此急需对dev分支中该错误进行修改，这时，你使用

```
git checkout dev
```

想要切换。但系统却提示你“debug分支没有提交，无法切换分支”，然而，当前的debug正在开发，可能压根编译都无法通过，如果提交会产生大量的日志信息，这不是我想要的。

这种情况下就可以使用到git stash命令暂时保存。

```
git stash 
```

与压栈的效果一样，将保存当前工作区和暂存区的内容。可以多次进行git stash操作，最新一次的git stash存储在栈的顶层。

同样的，要恢复栈中的内容，使用

```
git pop
```

恢复栈顶的工作空间和暂存空间。当然，查询功能是必需的

```
git stash list
```

可查看栈空间的内容。

```
git stash drop [stash]
```

删除一个栈顶最新的存储，[stash]参数为git stash list中显示的编号。要一次删除栈中所有的内容也是可以的，

```
git stash clear
```

## 比较修改

`git diff`查看更改但未使用git add暂存的内容与git add的暂存区内容的差异。

`git diff --cached`查看git add暂存区的内容与上次提交HEAD之间的差异。

`git diff`与`git diff --cached`和在一起就包含了所有未提交的更改。当然，这也可以直接通过`git diff HEAD`一条命令直接查看工作区更改与上次提交的差异。

`git diff dev..master` 比较dev分支与master分支最新提交的diff。

`git diff dev...master` 比较dev分支与master分支自从分开开发以来master分支的所有改变。

`git diff sha1 sha2` 比较两次不同提交sha1和sha2之间的差别。

如果只是要比较某个文件而不是所有的变化，则在响应的命令后添加文件名即可，如`git diff README.md`。


## 放弃工作区的修改

`git checkout [filename]`可以放弃工作区（没有使用git add.命令添加到暂存区）的修改。

放弃的修改无法找回，谨慎使用！

## 放弃本地修改，强制更新

```
git fetch --all
git reset --hard origin/master
```

`git fetch`命令只是从远程下载而不进行merge，之后的`git reset`命令直接将HEAD指向刚刚下载的最新版本。

## git add时的中文问题

在cygwin中，使用git add添加要提交的文件的时候，如果文件名是中文，会显示形如`274\232\350\256\256\346\200\273\347\273\223.png`的乱码。

在bash下输入

```
git config --global core.quotepath false
```

core.quotepath设为false的话，就不会对0×80以上的字符进行quote。中文显示正常。









