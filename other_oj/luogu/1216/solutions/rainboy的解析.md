---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

具体看代码

dp转移方程

$$
dp[i][j] = max\{dp[i-1][j] ,dp[i-1][j-1] \} + a[i][j]
$$


$dp[i][j]$表示从起点,到达第i行,第j列这个点后能得到的最大值

```cpp
<%- include("./rainboy.cpp") _%>
```


