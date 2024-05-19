---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


这里用到了差分与前缀和一一对应的关系: 


设存在一个数组为$s$(同时也是前缀和数组),

如果对$s$进行区间加$1$这一操作,对就的对s的差分数组$d$上,只相当于操作了两个点

且我们知道, **原数组与对应的差分数组是一一对应的**



```cpp
<%- include("./rainboy.cpp") _%>
```


