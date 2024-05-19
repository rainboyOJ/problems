---
title: rainboy的解析
author: rainboy
date: "2023-12-20 11:08"
update: "2023-12-20 11:08"
home: https://github.com/rainboylvx
top: true
---

## 解析

题目大意: 


根据做题目的经验,显然要先让所有的工匠按$S_i$进行排序,这样才能让我们按线性的思路一个一个的考虑每个工匠做的工作.

```cpp
struct node {
    int l,p,s;
};
node a[maxn];

int main() {
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        cin >> a[i].l;
        cin >> a[i].p;
        cin >> a[i].s;
    }
    std::sort(a+1,a+1+m,[](node &a,node &b){
        return a.s < b.s;
    });
    return 0;
}
```

设$f(i,j)$表示前$i$个工匠在前$j$个木板下的能获得的最多报酬.

考虑最后一个工匠的工作,他可以:

- 显然,最简单的就是什么也不做,$f(i-1,j)$,也就是让前$i-1$工匠去工作,第$i$个工匠不工作
- 要不然不要刷第$j$个木板,$f(i,j-1)$
- 要不然第$i$个工匠刷某些木板,设这个范围为$[k,j]$,注意这里显然有有条件限制,

这里仔细的讨论一下这些限制条件

1. 必须包含$S_i$这个木板,所以$k \leqslant S_i \leqslant j$
2. 工作的区间总长度不能超过$l_i$,那么$j-k+1 \leqslant l_i$
    1. 也就是说$k \geqslant j-l_i+1$
    2. 同时$k \leqslant S_i$
    3. 综上,得到k的范围$j-l_i +1 \leqslant k \leqslant S_i$

其时,最重要就是得到这个$k$的范围,你只要画图就可以得到这个范围.用公式去推反而不好去思考.

写出完整的状态转移方程,这个方程不难写:

设$val(i,j)$表示第$i$工匠粉刷$j$个木板得到的报酬,$val(i,j) = P_i \times j$

$$
f(i,j) = \max \left\{ 
\begin{array}{ll}
f[i-1,j] \\
f[i,j-1] \\
f[i-1,k-1] +  val(i,j-k+1) \quad  \text{j,k满足上面的限制} 
\end{array}
\right.
\tag 1
$$

根据写题目的经验,如果需要对代码进行优化(使用各种优化原理),你需要先把原始的朴素的代码写出来,如下:



我们按个方程,可以写一个一个三层循环的代码.

这个代码的时间复杂度$O(n^2 \times m)$,这个代码可以过50分.

```cpp
<%- include("./t2.cpp")%>
```

上面的代码显然需要优化.

显然我们应该重点关注第3个式子.把第三个式子写完整

$$
\begin{align*}
&max\{f[i-1,k-1] +  val(i,j-k+1) \}\\
&=max\{f[i-1,k-1] +  P_i \times (j-k+1) \}\\
&=max\{f[i-1,k-1] +  P_i \cdot j- P_i \cdot k  + P_i) \}\\
&= P_i \cdot j + P_i + max\{f[i-1,k] - P_i \cdot k) \}\\
\end{align*}
$$

发现了吗? 
- 当$j$固定时,k的变化是有范围的.
- 那就是求公式$f[i-1,k]-P_i \cdot k$在$k \in [ j-l+1,s_i]$这个区间内的最值
- $!!!$,当$j$增加$1$时,**决策区间有重复!!!!**
- 决策区间有重复就可以使用单调队列.

需要查找这个函数$val2(i,k) = f[i-1,k]  - P_i \cdot k$,最值,它的区间变化是

- 上界$S_i$ 不变
- 下界$j-l+1$向右移动

```

---- [ k1 ] [ k2 ] [ k3 ] -------
```

下面的操作就很简单了啊. 显然的单调队列.


```cpp
<%- include("./t3.cpp")%>
```
