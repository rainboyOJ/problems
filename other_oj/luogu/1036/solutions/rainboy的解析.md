---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
practice_rbook:
  - 01_seq
  - ball_and_box
top: true
---

## 解析 1


用到的知识: [[[rbook: 01_seq]]]


时间为$n \times 2^n = 20 \times 2^{20}=20971520 \approx 2 \times 10^7$ 能过

::: fold
```cpp
<%- include("./1.cpp")%>
```
:::


## 解析2 

用到的知识 :[[[rbook: ball_and_box]]]

这个题目显然用到的是组合的知识,从n个数里选m个数


::: fold
```cpp
<%- include("./rainboy.cpp") _%>
```
:::
