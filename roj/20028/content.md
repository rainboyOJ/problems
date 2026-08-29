### 题目描述

小 N 在一个神秘的国度旅行。这个国度有 $n$ 个城市，$m$ 条单向道路。小 N 计划从某个城市开始，游览尽量多的城市，并回到原本的城市（可以游览重复的城市）。正巧这个国度的国王非常高兴小 N 的到来，计划为他专门给一条现有的单向道路修建一个回程（可以与现有道路重合）。小 N 想知道，在最好情况下，他最多可以游览多少个不同的城市。

### 输入格式

输入第一行两个正整数 $n,m$ ，表示城市数量和道路数量。

接下来 $m$ 行，每行两个正整数 $u,v$ ，表示一条从 $u$ 到 $v$ 的单向道路。

### 输出格式

一行一个整数，表示最多能游览的不同城市数量。

### 数据范围

对于 30% 的数据，$n,m\leq 200$ 。

对于 50% 的数据，$m\leq 4000$ 。

对于 100% 的数据，$1\leq n \leq 2000,0\leq m\leq 40000,1\leq u,v\leq n,u\neq v$ 。

### 输入输出样例

#### 输入样例1

    6 10
    4 2
    6 1
    5 3
    5 1
    4 3
    3 6
    4 3
    4 2
    3 6
    5 1

#### 输出样例1

    4

#### 样例解释

添加道路 $(1,5)$ 后，可以选 $1$ 为起点，游览 $5,3,6$ 后回到 $1$ 。

#### 输入/输出样例2

见下发文件。

<!-- roj:downloads:start -->
## 下发数据

- [下载 travel2.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20028/down/travel2.in)
- [下载 travel2.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20028/down/travel2.out)
<!-- roj:downloads:end -->
