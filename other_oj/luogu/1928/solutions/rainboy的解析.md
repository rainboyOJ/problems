---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

先脑暴 🧠

```
[2CB] --> CBCB

[2[2CB]] --> [2CBCB] --> CBCBCB

还有这种数据,题目没有说
[2A[2C]] --> [2ACC] --> ACCACC

还有这样的数据,题目也没有说清楚

[2A[2B]C] --> [2ABBC]-->ABBCABBC

竟然还有这样的数据
D[2A[2B]CC[3X]F]EE
-->
DABBCCXXXFABBCCXXXFEE
```

🤢🤢🤢🤢🤢🤢,这个题目很恶心,因为叙述不清楚,导致我写了很长时间.

应该多给几个样例.


只要遇到`[`就 

1. 读取数字
2. 读取字符串
3. 返回重复之后的字符串

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


