---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

到达n点的路径,前一个点只能是 $n-1$,$n-2$

很容易想到,下面的代码

```cpp
<%- include("./t1.cpp") _%>
```

这个代码肯定会超时,又想到这个数,应该类似于fabnaci数列,且很大,于是使用高精度加递推

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


