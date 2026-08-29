### 题目描述

给你一个长度为 $n$ 的，仅由 $A$ 和 $B$ 构成的字符串 $S$ ，每一次操作你可以将一个 $A$ 变成一个 $B$ ，也可以将一个 $B$ 变成一个 $A$ 。请你求出最少多少次操作后，可以将这个字符串变成一个非递减的字符串？

非递减是指不存在一对 $(i,j)$ ，满足 $i<j$ 且 $S_i=B,S_j=A$ 。

### 输入格式

一行一个字符串 $S$ 。

### 输出格式

输出一个数字，表示最少的操作次数。

### 数据范围

对于 20% 的数据，$n\leq 20$ 。

对于 40% 的数据，$n\leq 100$ 。

对于 60% 的数据，$n\leq 2000$ 。

对于 100% 的数据，$1\leq n\leq 10^6,S_i={A,B}$

### 输入输出样例

#### 输入样例1

    AABBA

#### 输出样例1

    1

#### 输入/输出样例2

见下发文件。

<!-- roj:downloads:start -->
## 下发数据

- [下载 string2.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20026/down/string2.in)
- [下载 string2.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20026/down/string2.out)
<!-- roj:downloads:end -->
