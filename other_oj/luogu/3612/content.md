## 题目




### 题目描述

The cows are experimenting with secret codes, and have devised a method for creating an infinite-length string to be used as part of one of their codes.

Given a string $s$, let $F(s)$ be $s$ followed by $s$ "rotated" one character to the right (in a right rotation, the last character of $s$ rotates around and becomes the new first character). Given an initial string $s$, the cows build their infinite-length code string by repeatedly applying $F$; each step therefore doubles the length of the current string.


Given the initial string and an index $N$, please help the cows compute the character at the $N$th position within the infinite code string.





### 输入格式
The input consists of a single line containing a string followed by $N$. The string consists of at most 30 uppercase characters, and $N \leq 10^{18}$.

Note that $N$ may be too large to fit into a standard 32-bit integer, so you may want to use a 64-bit integer type (e.g., a "long long" in C/C++).





### 输出格式

Please output the $N$th character of the infinite code built from the initial string. The first character is $N=1$.






### 样例


输入/输出 # 1

::: line
```
COW 8
```

```
C
```
:::





### 说明/提示
In this example, the initial string COW expands as follows:


COW -> COWWCO -> COWWCOOCOWWC

12345678





## 来源

- [luogu P3612](https://www.luogu.com.cn/problem/P3612)
