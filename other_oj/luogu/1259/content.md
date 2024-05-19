## 题目




### 题目描述

有 $2n$ 个棋子排成一行，开始为位置白子全部在左边，黑子全部在右边，如下图为 $n=5$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/dzfwand6.png)

移动棋子的规则是：每次必须同时移动相邻的两个棋子，颜色不限，可以左移也可以右移到空位上去，但不能调换两个棋子的左右位置。每次移动必须跳过若干个棋子（不能平移），要求最后能移成黑白相间的一行棋子。如 $n=5$ 时，成为：

![](https://cdn.luogu.com.cn/upload/image_hosting/yus9ph6d.png)

任务：编程打印出移动过程。



### 输入格式

一个整数 $n$。



### 输出格式

若干行，表示初始状态和每次移动的状态，用 $\verb!o!$ 表示白子，$\verb!*!$ 表示黑子，$\verb!-!$ 表示空行。




### 样例


输入/输出 # 1

::: line
```
7
```

```
ooooooo*******--
oooooo--******o*
oooooo******--o*
ooooo--*****o*o*
ooooo*****--o*o*
oooo--****o*o*o*
oooo****--o*o*o*
ooo--***o*o*o*o*
ooo*o**--*o*o*o*
o--*o**oo*o*o*o*
o*o*o*--o*o*o*o*
--o*o*o*o*o*o*o*

```
:::





### 说明/提示
 $ 4\leq n\leq 100$ 


## 来源

- [luogu P1259](https://www.luogu.com.cn/problem/P1259)
