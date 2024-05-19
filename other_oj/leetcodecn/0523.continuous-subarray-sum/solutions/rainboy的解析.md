---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

最朴素的想法,使用前缀和数组a来存前缀和,然后通过二层for来枚举区间和,时间$O(n^2)$,但是这样应该会超时,因为数组长度为$10^5$


题目的数据暗示我们可以用`O(n)`或`O(nlogn)`的算法来实现


```

presum: . . . . . . b . . . . . a
```

$$
\begin{aligned}
 z = 0 &= (a - b) \mod k \\
&= (a \mod k)  - (b \mod k)
\end{aligned}
$$

接下来变成了一个数学问题

- 已知$a \mod k$的值和$z$的值,那么$b \mod k$的值可能是多少呢?

由拼木棍求取余的思想,可以知道$b \mod k$ 一定为$a \mod k$的值


发现k非常大,不能使用桶,那么需要找到一种数据结构,可以存$10^5$的数据,且可以快速查询,那就是二分查找树,这里直接使用`std::map`,可以节省手写的时间


细节,当有多少位置的前缀和的mod值一样时,记录第一个位置,因为这样可以和后面相同的mod拉的尽可能长.

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


