---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

严格的按题目的来写,如果使用两个队列来实现一各LIFO,结构.

```
    head
     V
q1:  1 2 3 4
q2:
```

在队列`q1`中,如果想到取元素,那取的应该是最后一个元素4.

1. push(1)

```
q1 : 1
q2 :
```

2. push(2)

把q1的元素依次pop出来,然后push到q2

```
q1 : 
q2 : 1
```


把q1.push(2)

```
q1 : 2
q2 : 1
```

把q0的元素依次pop出来,然后push到q1

```
q1 : 2 1
q2 : 
```

这个时候的队列q1,就是LIFO



3. push(3)

把q1的元素依次pop出来,然后push到q2

```
q1 : 
q2 : 2 1
```


把q1.push(3)

```
q1 : 3
q2 : 2 1
```

把q0的元素依次pop出来,然后push到q1

```
q1 : 3 2 1
q2 : 
```

这个时候的队列q1,就是LIFO

4. push(4)

自己想一想

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```


## 参考

- [algorithm-baseanimation-simulation栈和队列225.用队列实现栈.md at main · chefyuanalgorithm-base](https://github.com/chefyuan/algorithm-base/blob/main/animation-simulation/%E6%A0%88%E5%92%8C%E9%98%9F%E5%88%97/225.%E7%94%A8%E9%98%9F%E5%88%97%E5%AE%9E%E7%8E%B0%E6%A0%88.md)
