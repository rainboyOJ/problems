---
title: "rainboy的解析"
date: "2024-02-10 11:08"
update: "2023-02-10 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

考点,如何求最低分与最高分

- 最高分,定义变量`int _max = -1`,只要读取的分数t比_max大,则`_max = t`
- 最低分,定义变量`int _min = 11`,只要读取的分数t比_min小,则`_min = t`
- 如何求所得到的分:总分减去_max与_min


具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


