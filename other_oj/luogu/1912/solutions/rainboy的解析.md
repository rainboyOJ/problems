---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


1. 计算是否可以样例了1,为什么是108

设$w(i,j)$ 表示第$i$行到第$j$合并成一行的不协调度.

显然得到公式.

$$
f(i) = min\{f(j),w(j+1,i)\}  \quad  1 \leqslant j \leqslant i
$$

边界$f(0) = 0$

写出一下如下的朴素DP代码

```cpp
<%- include("./r1.cpp")%>
```


整体时间复杂度为$n^2$,只能过前三个点,拿$30$分.显然这个题目的难度不可能让你写这么简单的代码拿满分的.

观察$w(i,j)$,显然有具有单调性(大包小),

$$
w(i,j) = |\sum_{k=1}^j st[k] + (j-i) - L|^P
$$



证明: "交错和" 小于 "大小和"

$$
w(i,j) + w(i+1,j+1) \leqslant w(i+1,j) + w(i,j+1) \tag 2
$$

显然当$i+1=j$时,是成立的

当$P=1$,显然$(2)$式成立.

因为

要证明$a^P + b^P > c^P + d^P$，其中$a > 0, b > 0, c > 0, d > 0, a + b > c + d, P > 0$，我们可以利用不等式的性质和数学归纳法来证明。

首先，我们知道$a + b > c + d$。我们可以将$a$和$b$表示为$c + x$和$d + y$，其中$x > 0$和$y > 0$。

现在我们来证明$(c + x)^P + (d + y)^P > c^P + d^P$。

根据二项式定理，我们可以展开$(c + x)^P$和$(d + y)^P$：

$$
(c + x)^P = c^P + \binom{P}{1}c^{P-1}x + \binom{P}{2}c^{P-2}x^2 + \ldots + x^P
$$

$$
(d + y)^P = d^P + \binom{P}{1}d^{P-1}y + \binom{P}{2}d^{P-2}y^2 + \ldots + y^P
$$

由于$P > 0$，所以$(c + x)^P > c^P$和$(d + y)^P > d^P$成立。

因此，根据$a = c + x$和$b = d + y$，我们得出结论$a^P + b^P > c^P + d^P$。


