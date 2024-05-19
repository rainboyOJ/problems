---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


这个题目的考点是

1. 后缀表达式 如何使用栈 来进行计算

计算过程

1. 如果读取了一个数字,就加入(push)栈中
2. 如果读取的是一个运算符号,如`-`
  1. 从栈中先后取出$b,a$两个数字
  2. 运算得到$c = a-b$
  3. 将结果$c$加入栈中
3. 最后栈中只有一个结果,就是整个公式的结果

```cpp
<%- include("./rainboy.cpp") _%>
```


