---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


这个题目读起来,怎么那么难受?🙃

有n个数,

- 相邻的两个数,要花费$A_i$
- $C_i$买这段路的卡,以后只要话费$B_i$元

想法,计算出每一段路的走的次数,那不就是区间加1吗,使用差分

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


