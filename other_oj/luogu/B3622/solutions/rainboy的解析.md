---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
practice_rbook:
  - 01_seq
  - subset_enum
  - ball_and_box
  - subset_enum
top: true
---

## 解析

这个题目有多种写法, 下面我把每一种写法写出来

## 01_序列

根据[[[rbook: 01_seq]]]

::: fold
```cpp
<%- include("./2.cpp")%>
```
:::

## 组合

根据[[[rbook: ball_and_box]]]的组合的内容

::: fold
```cpp
<%- include("./1.cpp")%>
```
:::

## 全组合

根据rbook上的[[[rbook: ball_and_box]]]的全组合,我们可以写出这样的代码

## 二进制枚举

因为每个元素选或不选,那么造成的01序列就是二进制,所以可以直接枚举二进制

::: fold
```cpp
<%- include("./3.cpp")%>
```
:::

## 子集枚举

根据[[[rbook: subset_enum]]]

::: fold
```cpp
<%- include("./4.cpp")%>
```
:::
