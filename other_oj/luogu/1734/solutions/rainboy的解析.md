---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

注意:和加起不不超过$S$的数

所以,那些数字$a$,可以看成一个物品,那么它的重量为$a$,本身数字的大小,价值为自己约数的和

这样就变成了标准的01背包

1. 先预处理,求出1000内的每个数的约数和
2. 然后按01背包来做
3. 时间为$O(n)$



## 二维代码 

```cpp
<%- include("./rainboy2.cpp") _%>
```



## 一维代码 

我这里写的是01背包一维写法,你可以用二维写法
```cpp
<%- include("./rainboy.cpp") _%>
```


