---
title: rainboy的解析
author: rainboy
date: "2023-12-20 11:08"
update: "2023-12-20 11:08"
home: https://github.com/rainboylvx
top: true
---

## 解析


$$
f(n) = 1+ f(1) + f(2) + \cdots + f(n/2)
$$

所以这个题目应该使用递推加前缀和来做


```cpp
<%- include("../std.cpp") _%>
```

