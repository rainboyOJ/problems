---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
practice_rbook:
  - 01_seq
  - ball_and_box
  - subset_enum
---

## 解析


## 30 分代码


枚举子集,最简单的还是用 [[[rbook: 01_seq]]]


当然用这是些思想都可以

- [[[rbook: 01_seq]]]
- [[[rbook: ball_and_box]]]
- [[[rbook: subset_enum]]]


01序列的思想: 每个物品只有选或不选,认为0代表选,1代表不选,那么所有选或不选的可以性,可以形成
下面的01序列,如果只有2个物品,这本质是对所有可能结果的枚举

```
00
01
10
11
```

::: fold
```cpp
<%- include("./t1.cpp") _%>
```
:::
