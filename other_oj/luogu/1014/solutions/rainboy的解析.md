---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

1. 其实,按坐标来走的,(x,y)
2. 他的方向有两种, 上(up) ,下(down)
3. (x,y) 其中有一个变成0的时候,表示到达了墙,应该把0变成1,且改变下一次走的方向

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


