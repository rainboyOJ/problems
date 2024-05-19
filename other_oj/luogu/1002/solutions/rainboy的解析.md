---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

设$f(x,y)$表示从起点到$(x,y)$的路径数目。

```
 ┌───────────────────┐A
 │                   │ 
 │                   │ 
 │                   │ 
 │                   ▼ 
 │                   │ 
 └────────────────► ─┘ 
B                     C 
```


与走楼梯类似,c点,一定是由A,B两个点来的,设$x,y$表示C点的坐标,那么$f(x,y)$表示到达c点的路径数目

所有得到公式:
$$
f(x,y) = \left\{
    \begin{array}{cr}
        f(x-1,y+1) + f(x,y-1) & x > 0 \land y > 0 \\
        1 & x = y = 0 \\
        0 & x < 0 \lor y < 0 \\
        0 & \text{x,y 点是马可以到达的点}
    \end{array}
\right.
$$

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


