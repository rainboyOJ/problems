---
title: rainboy的解析
author: rainboy
date: "2023-12-20 11:08"
update: "2023-12-20 11:08"
home: https://github.com/rainboylvx
top: true
---

## 解析


转成求最多能保留多少个点,那不就和lis类似吗

设$f[i]$ 表示一定能保留第i个时,最多保留多少个元素

$$
f[i] = max\{1,f[j]+1\} ,j \leqslant i , abs(a[i]-a[j]) \neq 0
$$

```cpp
<%- include("../std.cpp")%>
```

