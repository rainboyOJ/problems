### 题目描述

考古学家在探索一座 $n \times n$ 的古代遗迹遗址时，试图在其中布置一个正方形的考古发掘区。然而，遗址中有 $T$ 块区域已经被标记为危险区，无法进行发掘。

你的任务是帮他们确定：在不包含任何危险区域的前提下，考古发掘区（正方形）的最大可能边长是多少。

### 输入格式

第一行一个整数 $n$，表示遗址的边长。

第二行一个整数 $T$，表示有多少个危险区域。

接下来 $T$ 行，每行两个整数 $x, y$，表示第 $x$ 行第 $y$ 列是一个危险区域。

### 输出格式

一行一个整数，表示可以布置的最大正方形发掘区的边长。

### 数据范围

对于 20% 的数据，$1\leq n\leq 50,T=1$ 。

对于 40% 的数据，$1\leq n\leq 50,1\leq T\leq 10$ 。

对于 70% 的数据，$1\leq n\leq 5\times 10^5,1\leq T\leq 10$ 。

对于 100% 的数据，$1\leq n\leq 5\times 10^5,1\leq T\leq 100$ 。

### 输入输出样例

#### 输入样例1

    5
    1
    2 4

#### 输出样例1

    3

#### 输入样例2

    15
    8
    4 7
    4 1
    14 11
    10 6
    13 4
    4 10
    10 3
    9 14

#### 输出样例2

    7

#### 输入/输出样例3

见下发文件，满足 $1\leq n\leq 50,1\leq T\leq 10$ 。

#### 输入/输出样例4

见下发文件。

<!-- roj:downloads:start -->
## 下发数据

- [下载 discover3.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20029/down/discover3.in)
- [下载 discover3.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20029/down/discover3.out)
- [下载 discover4.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20029/down/discover4.in)
- [下载 discover4.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20029/down/discover4.out)
<!-- roj:downloads:end -->
