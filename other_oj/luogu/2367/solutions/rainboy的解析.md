---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

同样$40\%$的数据可以暴力.时间复杂为了$O(n^2)$


观察到这个题目的特点

- 多次修改,一次查询
- 每次修改一个连续区间且增减的数值一样

于是,可以使用差分的方法来做,时间为

- 一次修改$O(1)$,总体为$O(n)$
- 查询$O(n)$

```cpp
<%- include("./rainboy.cpp") _%>
```


