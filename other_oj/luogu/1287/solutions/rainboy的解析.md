---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


这个题目不能使用暴力枚举的方法来做,这是个排列组合的数学题目


设有$n$个不同的球，分别用$1,2,\cdots ,n$表示,放到$m$个相同的盒子里。

比如,3个球放两个盒子里


```
[1],[2,3]
[1,2],[3]
[1,3],[2]
```

从中取出一个球$n$，$n$的放法有以下两种：


1. n独自占一个盒子；那么剩下的球只能放在m-1个盒子中，方案数为：$f(n-1, m-1)$
2. n与别的球共占一个盒子；那么可以事先将$1,2, \cdots, n-1$这$n-1$个球放入$m$个盒子中，然后再将球$n$可以放入其中一个盒子中，方案数为 :$m \times f(n-1,m)$


$$
\begin{array}{cr}
0 & n < m \lor m < 1\\
1 & n = m \\
f(n-1,m-1) + m*f(n-1,m)

\end{array}
\right.
f(n,m) = \left\{
\begin{array}{cr}
0 & n < m \lor m < 1\\
1 & n = m \\
f(n-1,m-1) + m*f(n-1,m)

\end{array}
\right.
$$

第二步,考虑到,把球分好组后,可以这r组,看成r个不同的球,于是真正的结果就是$f(n,m) \times r!$

为了简单,直接写递归.

```cpp
<%- include("./rainboy.cpp") _%>
```


