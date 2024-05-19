---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

就是数字金字塔

可以想到这里就是dfs走迷宫,于是上来就写一个dfs的代码,这个代码可以作为验证数据是否正确.

```cpp
<%- include("./dfs.cpp") _%>
```

## dp思想

dp第一步,就是分阶段,也就是确定 题目没有后效性,也就是不能"回头",也就是不能回到过去

针对这个题目,显然每上一层,就不能回到下一层了,从层上来说,就符合DP.

假如局限在这一行,显然这个点一旦向右走,就不能回头

```

  -->a-->b
     ^
     |
```


```cpp
<%- include("./rainboy.cpp") _%>
```

## 错误的代码

考虑的状态不对,没有考虑到,起点上面的格式,可以3步走到

```cpp
<%- include("./wrong.cpp") _%>
```
