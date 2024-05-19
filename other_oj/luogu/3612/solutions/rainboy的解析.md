---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


题目的意思是很简单的,显然,我们不可能生成最后的那个字符串,因为太大,一定存不下来.


怎么才能哪最后的那字符是什么呢?没有思路了吗,暴力!!!!,先在纸上算,一会就有思路了



```
pre                   now
12345...N   --next-> 12345...NN12345...N-1
                                 ^
                                 |
                                need
```

所以可以知道

- 如果`now`的长为是$len$,上一个长度是$len / 2$
- `need`位置$\leqslant len/2$,则在`pre`的`need`位置
- `need`位置$> len/2$,
  - 在`pre`的N,也就是$len/2$
  - 在`pre`的$(need-len/2)-1 =$

## 视频

<%- onedrive_video("RainboyVideo/roj/luogu/P3612.mp4") %>


## 代码


具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


