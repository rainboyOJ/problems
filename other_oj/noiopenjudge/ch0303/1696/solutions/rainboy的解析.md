---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


非递归的写法,需要使用栈来实现,

如果栈最上面的三个元素,分别是

- 操作符
- 数字a
- 数字b

就可以直接运算得到结果c,然后加入到栈内,但是不好写代码,因为栈内的元素的类型不一样.


如果使用递归来写,代码就会变得很简单,递归本质就是栈.


```cpp
<%- include("./dfs.cpp") _%>
```
