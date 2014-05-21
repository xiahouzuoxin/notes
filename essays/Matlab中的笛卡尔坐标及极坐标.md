[<font size=4>←返回主目录<font>](../README.md)
</br></br></br>

## 基于plot的笛卡尔坐标

- 绘制笛卡尔坐标

```
x = -pi:pi/10:pi;
y = tan(sin(x)) - sin(tan(x));
plot(x,y,'--rs','LineWidth',2,...
                'MarkerEdgeColor','k',...
                'MarkerFaceColor','g',...
                'MarkerSize',10)
```

- 图片背景透明

```
set(gcf,'color','none');  %图形背景设为无色
set(gca,'color','none');  %坐标轴背景设为无色，这条更重要，通常图形背景的白色实际为坐标轴背景色
```

plot后默认的背景是白色的，若在写文章时要使图片背景透明，则很有用。

- 修改坐标轴

```
xlabel('\fontname{Arial}time/s', 'fontsize', 11);   % 设置横坐标为time，11号Arial字体
ylabel('\fontname{Arial}cost(uJ)', 'fontsize', 11); % 设置纵坐标为cost，11号Arial字体
xlim([xmin xmax]);  % 设置x轴范围为[xmin xmax]
ylim([ymin ymax]);  % 设置y轴范围为[ymin ymax]
axis([xmin xmax ymin ymax]);  % 同时设置xy的坐标范围
axis on;    % 显示坐标轴
axis off;   % 不显示坐标轴
```

- 标题和图注

```
title('string');   % 标题为string
legend('string1','string2',...);  % 图例标注
```


## 基于polar的极坐标

- 绘制极坐标

```
t = 0:0.01:2*pi;
polar(t, sin(2*t) .* cos(2*t), '--r');
```

其中t为弧角，sin(2*t).*cos(2*t)为弧长。

- 修改弧角的间隔

打开polar.m文件，修改下面一行，默认间隔为pi/6。

```
th = (1 : 6) * 2 * pi / 12;
```

