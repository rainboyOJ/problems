---
title: "rainboy的解析"
date: "2024-01-09 09:47"
update: "2024-01-09 09:47"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 代码

本题目就是lis,所以没有什么好讲的

$$
f[i] = max(f[j]+1,1) \; j < i \land a_j < a_i
$$

注意正反算两次

```cpp
<%- include("./rainboy.cpp") _%>
```
