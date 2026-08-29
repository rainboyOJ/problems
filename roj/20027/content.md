### 题目描述

小 B 和他的朋友们住在一个数轴上，每个人有一个初始坐标 $x_i$ 和移动速度 $v_i$ 。现在，他们想找一个地方聚会，并且想让聚会尽量早开始。现在他们想让你选一个位置，使得让所有人都到达那个位置的时间尽可能少，位置不一定是整数坐标点，也有可能是小数。

### 输入格式

第一行一个整数 $n$ 。

第二行 $n$ 个整数，第 $i$ 个整数 $x_i$ 表示第 $i$ 个人的初始位置。

第三行 $n$ 个整数，第 $i$ 个整数 $v_i$ 表示第 $i$ 个人的速度。

### 输出格式

一个浮点数，四舍五入保留 5 位小数。

### 数据范围

对于 20% 的数据，$n \leq 5, x_i \leq 5$ 。

对于 40% 的数据，$n\leq 10$ 。

对于 70% 的数据，$n\leq 1000$ 。

对于 100% 的数据，$2\leq n\leq 10^5,1\leq x_i,v_i\leq 10^7$ 。

### 输入输出样例

#### 输入样例1

    3
    7 1 3
    1 2 1

#### 输出样例1

    2.00000

#### 输入样例2

    10
    2 3 5 7 11 13 17 19 23 29
    6 5 4 3 2 1 2 3 4 5

#### 输出样例2

    2.75000

#### 输入/输出样例3

见下发文件。

<!-- roj:downloads:start -->
## 下发数据

- [下载 meeting3.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20027/down/meeting3.in)
- [下载 meeting3.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20027/down/meeting3.out)
<!-- roj:downloads:end -->
