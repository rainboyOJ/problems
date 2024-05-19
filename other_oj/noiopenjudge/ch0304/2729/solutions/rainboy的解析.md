---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

经过普通队列输出数据后,发现普通队列不正正确

```
1 3 4 7 10 9
```

发现由$4$生成的$9$比较$3$生成的$10$要大,根据做题目的经验,这个题目肯定有数学规律,
进一步输出数据,找规律.

根据数据范围,知道,最终的代码一定是$O(n)$的,$O(nlogn)$都不行,所以不能使用优先队列,这暗示我们,产生的数据可以按某种方式有序,不需要进行比较.

1. 每一次产生的两个数$a < b$ 一定成立
2. 每一次都应该由最小的数首开两个新的数$a,b$

每一次产生的两新的数,和原来的已经产生的数,有什么关系,


使用数学归纳法证明

```
a b
. .
. .
. .
x y
```

设$x \geqslant a,y \geqslant b$,且取$t = min(a,b)$,且$t \leqslant z$,$z$ 是生成$x,y$的元素


$$
x = 2 \times z +1 \\
y = 3 \times z +1 \\
$$

现在取$t$,得到$A = 2 \times t + 1, B = 3\times t +1$,显然

$$
A  \leqslant x \Rightarrow 2\times t + 1 \leqslant 2\times z +1 \\
B  \leqslant y \Rightarrow 3\times t + 1 \leqslant 3\times z +1
$$

显然成立

这就说明如果原来的双队列成立(单个队列都是单调的),则从取双队列头的最小值,产生新的值,然后把值各自加入到队列尾部,
得到的新的双队列也成立.


```cpp
<%- include("./rainboy.cpp") _%>
```

## 错误的代码


使用优先队列,超时.

```cpp
<%- include("./pq.cpp") _%>
```
