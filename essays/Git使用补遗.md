[<font size=4>←返回主目录<font>](./README.md)
</br></br></br>


## 删除错误提交

噢，My God，不小心把含有私有密码信息的版本提交了，还提交到了Github………没问题：

```
git log                        # 查看要回退的版本
git reset --hard <commit-id>   # 回退到commit-id>版本
git push origin HEAD --force   # 远程版本回退
```


