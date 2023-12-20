---
title: "rainboy的解析"
date: "2023-12-20 11:08"
update: "2023-12-20 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

本质考的是:

- `c++`的乘法
- `c++`的整除,整数除以整数得到整数


## 代码1

```cpp
<%- include("./rainboy.cpp") _%>
```

## 代码2

使用`scanf,printf`

```cpp
#include <cstdio>

int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    int c = a*10+b;
    printf("%d",c / 19);
    return 0;
}
```
