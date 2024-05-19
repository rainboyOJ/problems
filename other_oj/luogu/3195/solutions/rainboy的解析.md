---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
practice_rbook:
  - decision_mono
---

## 解析

和诗人小G很像啊

先写出状态转移方程,设$f(i)$表示前i个玩具可以达到的最小值


$$
f(i) = \min\{f(j) + val(j+1,i)\}
$$

其中$val(j,i)$表示$[j,i]$区间内的所有的玩具放到一个容器内的时候得到的值

$$
val(j,i) = ( i-j + \sum_{k=j}^{i}C_k  - L)^2
$$


轻松写出一下朴素的$n^2$的算法如下

::: fold

```cpp
<%- include("./t1.cpp")%>
```

:::

显然要优化的:

## 决策单调性

这个状态转移方程有决策单调性.下面证明

我们先把题目转化成一个数学问题.

设在一个数轴上有这几个点$a < b < x < y$

```
-------a--------b----------x----------y---------
```

设
- $g(a,x)$ 表示从$a$转移到$x$的值
- $sum(i)$ 表示前缀和$\sum_{1}^iC_i$
- $S_i = sum(i)+i$
- $L_1 = L+1$

于是得到$g(a,x)$

$$
\begin{aligned}
g(a,x)  &= f(a) + val(a+1,x) \\
&= f(a) + (\sum_{k=a+1}^{x}C_k + x-(a+1) - L)^2 \\
&= f(a) + (sum(x) - sum(a) + x-a-1 - L)^2 \\
&= f(a) + (sum(x)+x - (sum(a) +a ) -(L+1))^2 \\
&= f(a) + (S_x - S_a -L_1)^2
\end{aligned}
\tag 1
$$

同理,可以得到$g(b,x)$

$$
g(b,x) =  f(b) + (S_x - S_b -L_1)^2 \tag 2
$$

那么先假定$g(b,x) < g(a,x)$成立,那么问题变成证明

$$
g(b,x) < g(a,x) \Rightarrow g(b,y) < g(a,y)
$$

上式恒成立.


同样得到$g(a,y),g(b,y)$

$$
g(a,y) =  f(a) + (S_y - S_a -L_1)^2 \tag 3
$$

$$
g(b,y) =  f(b) + (S_y - S_b -L_1)^2 \tag 4
$$

观察发现$(3),(4)$式对于$(1),(2)$式来说,只有$S_y,S_y$不同.根据题意,显然$S_y > S_x > 0$,那么就设$S_y = S_x+v, v> 0$,那么得到新的式子


$$
\begin{align}
g(a,y) =  f(a) + (S_x+v - S_a -L_1)^2  \tag 5 \\
g(b,y) =  f(b) + (S_x+v - S_b -L_1)^2  \tag 6 \\
\end{align}
$$

根据数学直觉,若想知道$(5),(6)$式的在小关系,那么只需要知道对于$(1),(2)$式之间的增量之间的大小关系.


$$
\begin{aligned}
g(a,y) &=  f(a) + (S_x+v - S_a -L_1)^2 \\
&= f(a) + (v+(S_x - S_a -L_1))^2  \\
&= f(a) + v^2+2v(S_x - S_a -L_1) +(S_x - S_a -L_1)^2  \\
\end{aligned}
$$

那么增加的量就是$v^2+2v(S_x - S_a -L_1)$.同理$(6)$式的增量就是$v^2+2v(S_x - S_b -L_1)$.比较两者之间的大小

$$
\begin{aligned}
&v^2+2v(S_x - S_a -L_1) - ( v^2+2v(S_x - S_b -L_1)) \\
&= 2v( S_x - S_a -L_1 -S_x + S_b -L_1) \\
&= 2v(S_b - S_a) > 0
\end{aligned}
$$

因为$S_b > S_a$一定成立.

所以题目的状态转移方程是满足**决策单调性**

然后根据[[[rbook: decision_mono]]]可以写出来下的代码


::: fold
```cpp
<%- include("./decision_mono.cpp")%>
```
:::

## slope 


```cpp
<%- include("./slope.cpp")%>
```
