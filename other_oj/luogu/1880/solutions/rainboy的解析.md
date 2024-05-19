---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析1: $O(n^3)$

这是一个经典的区间DP问题,可以很轻松的写出状态转移方程,设$f(i,j)$表示区间$[i,j]$的最值

$$
f(i,j) = minmax\{f(i,k) + f(k+1,j)\} + \sum_i^j a[i] \quad i \leqslant k < j
$$


具体看代码

::: fold

```cpp
<%- include("./t1.cpp") _%>
```
:::
