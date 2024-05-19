---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


这个题目的难度比较高,本质是考: **如果对中缀表达式进行计算**

根据编译原理所学的知识,按下面的步骤来做

- 字符串转化成`token`流
- `token`流根据运算符号的优先级转化成表达式树(核心)
- 对表达式树进行遍历,就可以得到前缀表达式,或,后缀表达式

难点就在于,转化成表达式树,很难操作,需要掌握

- 指针
- 树相关知识
- 递归

比较简单的方式,是把中缀表达式转成后缀表达式,

难点在于理解,


具体操作方式如下,

> 利用辅助栈

> 从左到右遍历中缀表达式的每个操作数和操作符。当读到操作数时，立即把它输出，即成为后缀表达式的一部分；若读到操作符，判断该符号与栈顶符号的优先级，若该符号优先级高于栈顶元素，则将该操作符入栈，否则就一次把栈中运算符弹出并加到后缀表达式尾端，直到遇到优先级低于该操作符的栈元素，然后把该操作符压入栈中。如果遇到”(”，直接压入栈中，如果遇到一个”)”，那么就将栈元素弹出并加到后缀表达式尾端，但左右括号并不输出。最后，如果读到中缀表达式的尾端，将栈元素依次完全弹出并加到后缀表达式尾端。

查看这里 [前缀、中缀、后缀表达式转换详解-CSDN博客](https://blog.csdn.net/iteye_4185/article/details/82574934)




1. 如何读取一行字符串

1. 使用c风格的`getline`函数, [getline, getwline, getdelim, getwdelim - cppreference.com](https://en.cppreference.com/w/c/experimental/dynamic/getline)
2. 使用`c++`风格的`std::getline` [stdgetline - cppreference.com](https://en.cppreference.com/w/cpp/string/basic_string/getline)
3. 使用`c++`,`cin.getline` [stdbasic_istreamCharT,Traitsgetline - cppreference.com](https://en.cppreference.com/w/cpp/io/basic_istream/getline)

```
char str[100];
cin.getline(str,100);
```

```cpp
<%- include("./rainboy.cpp") _%>
```

## 参考

- [前缀、中缀、后缀表达式转换详解-CSDN博客](https://blog.csdn.net/iteye_4185/article/details/82574934)
- [布尔表达式 - 华山青竹 - 博客园](https://www.cnblogs.com/huashanqingzhu/p/7240987.html)
