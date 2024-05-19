---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---


## 解析

<%- onedrive_video("RainboyVideo/roj/luogu/luoguP1042.mp4") %>


1. 第一步: 看懂题目,在纸上算出样例的答案


2. 第二步: 发现"直到分差大于或者等于2"

一场比赛真正结束的时候为: 进行了至少11轮比赛且比赛之间的差值大于或等于2

😅,最后发现其实真正的结束条件是:

> 其中有一个的分数至少是11分且差值大于等于2

还有一个坑点

> 如果E(结束了比赛),哪怕前面的比赛是正常结束的,也要输出0:0

3. 写代码

4. 提交

5. 出现错误找错后提交

6. 重复做5,直到正确


## 代码

```cpp
<%- include("./rainboy2.cpp") %>
```
