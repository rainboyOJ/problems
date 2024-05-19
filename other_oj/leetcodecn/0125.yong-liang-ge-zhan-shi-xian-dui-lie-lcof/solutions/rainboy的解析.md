---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

题目的意思,是有个栈,每一次只能从最上面取


如果不严格按题目的意思一写,直接写一个队列就可以了


如果严格的按题目的要求来写,就需要:**利用两个栈,来实现,每一次都能取到最早的还的书(最早加入队列的元素)**


```
   3
   2
   1
stack 1 :  stack 2
```

`stack 1`按顺序放了`1,2,3`3个元素,现在想要取出最开始的`1`,怎么做呢?

```
             1
             2
             3
stack 1 :  stack 2
```

把元素从`stack 1`取出,然后放入到`stack 2`里面,然后再从`stack 2`的栈顶取,就可以取到最早的元素


想到方法:


```
- push, 只push 到stack 1
- 取最新的元素pop,
  - 如果stack 2不空,就取
  - 否则,把stack 1中的所有元素弹出到 stack 2
```

如果证明这种方法是对的呢:

可以想到,总体上`s1`的元素都是`old`于`s2`的,且`s2`的元素的栈顶一定是`new`于下面的元素,
无论任何时候了,上面的条件都一定成立.

所以`stack 2`栈顶的元素就是最新的

具体看代码

```cpp
<%- include("./rainboy.cpp") _%>
```

## 参考
- [algorithm-baseanimation-simulation栈和队列剑指Offer09用两个栈实现队列.md at main · chefyuanalgorithm-base](https://github.com/chefyuan/algorithm-base/blob/main/animation-simulation/%E6%A0%88%E5%92%8C%E9%98%9F%E5%88%97/%E5%89%91%E6%8C%87Offer09%E7%94%A8%E4%B8%A4%E4%B8%AA%E6%A0%88%E5%AE%9E%E7%8E%B0%E9%98%9F%E5%88%97.md)
