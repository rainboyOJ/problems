---
title: rainboy的解析
author: rainboy
date: "2023-12-20 11:08"
update: "2023-12-20 11:08"
home: https://github.com/rainboylvx
practice_rbook:
  - Quadrangle_Inequality_Optimization
top: true
---

## 解析

利用 [[[rbook: Quadrangle_Inequality_Optimization]]]的知识

先写状态转移方程

$$
f(i,j) = min\{ f(i,k) + f(k+1,j) + sum(i,j) \}
$$

核心在时间复杂度的证明.


::: fold

```cpp
<%- include("./rainboy.cpp")%>
```
:::

注意上面的代码是一个三层循环,但是时间不是$O(n^3)$,因为:

总的执行次数为:

$$
\sum_{len=2}^n \sum_{i=1}^{n-len+1}
(p[i+1][j] - p[i][j-1]+1)
$$

因为$j = i+len-1$ 所以,

$$
\begin{aligned}
&\sum_{len=2}^n \sum_{i=1}^{n-len+1}
(p[i+1][i+len-1] - p[i][i+len-2]+1) \\
&=  \sum_{len=2}^n 
\left\{
\begin{array}{rclc|l}
p[2][len] & - & p[1][len-1] &+ 1 & i=1 \\
p[3][len+1] & - & p[2][len] &+ 1 & i=2 \\
p[4][len+2] & - & p[3][len+1] &+ 1 & i=3 \\
\cdots \\
p[n-len+2][n] & - & p[n-len+1][n-1] & + 1 & i=n-len+1 \\
\end{array}
\right. \\
&= \sum_{len=2}^n(p[n-len+2][n]-p[1][len-1] + n-len+1) \\
& \leqslant  \sum_{len=2}^n (n-1 + n-len+1) \\
&= \sum_{len=2}^n (2n-len) \\
& \approx O(n^2)
\end{aligned}
$$
