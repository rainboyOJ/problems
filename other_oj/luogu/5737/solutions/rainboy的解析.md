---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

看完题目的第一个想法：

- 求最小的那个质数，那么另一个质数一定是$b = n \div a$

又可以想到，如果一个数$n$等于两个质数$a,b$的乘积，那么这个数$n$,只能分解成这两个数$a,b$的乘积,因为a和b都不能再分解了.

所以根本不需要判断这个数$n$的分解的$a,b$是不是质数,也就是调用$prime(int n)$进行判断.因为根据题目前提,$n$符合前面所说.

```
for i : 2 -> n
    if n % i == 0
        输出 n/i
```
上面代码的意思是: 一个一个尝试i能否除尽n,如果找到了,就输出$n/i$,就是所求

那么时间复杂度是多少呢?根据题目$n = 2 \times 10^9$,难道$O(n) = 2 \times 10^9$

可以想到$a$,最大到$\sqrt(2 \times 10^9) \approx 44721.3$(用python3计算),因为$a \times b$,设$a$是较小的那个数,$a \leqslant b$

所以这个题目本质是一个数学(数论)题目.

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


