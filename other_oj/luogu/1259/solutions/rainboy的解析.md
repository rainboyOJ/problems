---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

根据做题目的经验,做题目的步骤基本是不变的

- 看题题,不要看错
- 弄样例
- 脑暴,🧠
- 分析规律
- 写代码验证
- 测试
- 再写代码
- 再测试
- 重复直到写出来


看完样例后,显然发现有规律

```plantext
ooooooo*******-- 开始
oooooo--******o*

oooooo******--
ooooo--*****o*

ooooo*****--
oooo--****o*

oooo****--

ooo--***[o*]o*o*o* 有变化
ooo[*o]**--*o*o*o*

o--*o**oo*o*o*o*
o*o*o*--o*o*o*o*
--o*o*o*o*o*o*o*
```


$$
\underbrace{ooooooo\boxed o}_{n} \;
\underbrace{\boxed{*}******}_{n} \; \_\;\_ \\
\underbrace{ooooooo}_{n-1}\_ \;
\_\underbrace{******}_{n-1} \; \boxed{o}\;\boxed{*} \\
\underbrace{ooooooo}_{n-1} \;
\underbrace{******}_{n-1} \_\;\_\; \; \boxed{o}\;\boxed{*} \\
$$

可以想像出来,只要按上面的操作,一定可以操作出来$f(n)$转变成$f(n-1)$

当$n=4$时,他的操作是固定的.

于是可以写出如下的一个递归,代码,当然,你也递推也可以.

```cpp
<%- include("./rainboy.cpp")%>
```
