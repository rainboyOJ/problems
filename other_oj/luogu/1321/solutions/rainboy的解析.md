---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

思路,一个一个的检查字符,如果某个位置i的字符是

- `b`,可能就是一个`boy`,`bucket[i]=1`
- `o`,可能就是一个`boy`,`bucket[i]=1`,但如果前面的字符是`b`,则`bucket[i-1]=0`
- `y`,`bucket[i]=1`,前面的连续的`bo`都要把`bucket`改成0

同理,`girl`设为2

最后统计`bucket`中1和2的数量


具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


