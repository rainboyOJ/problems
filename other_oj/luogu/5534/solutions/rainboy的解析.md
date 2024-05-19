---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

### 解法1

计算差值,然后使用for循环一个一个计算,然后加起来 

```cpp
<%- include("./rainboy.cpp") _%>
```

### 解法2,数学公式

等差数列求和公式, 设

- 第一个元素$a_1$
- 差值为$d$

则前$n$项的和,为


$$
\begin{aligned}
S_n &= a_1 + (a_1 + d) + (a_1+2*d) + \cdots + (a_1+(n-1)*d) \\
    &= n \times a_1 + (1+2+3\cdots+(n-1)) \times d
\end{aligned}
$$

又因为

$$
\begin{aligned}
\underbrace{1+2+\cdots + n}_{n} = \frac{n(n+1)}{2}  \tag 1
\end{aligned}
$$

根据$(1)$(错位相加法),得到

$$
\begin{aligned}
S_n &= a_1 + (a_1 + d) + (a_1+2*d) + \cdots + (a_1+(n-1)*d) \\
    &= n \times a_1 + \frac{n(n-1)}{2} \times d
\end{aligned}
$$


```cpp
<%- include("./2.cpp") _%>
```

### 解法3

设问题为: $f(n)$ 前$n$项目的和,显然第$n$项为: $a_1 + (n-1) \times d$

那么

$$
f(n) = \left\{
\begin{aligned}
 &a_1 + (n-1)\times d + f(n-1) & n > 1 \\
 &a_1 & n = 1
\end{aligned}
\right.
$$


```cpp
<%- include("./3.cpp") _%>
```