### 时空限制

时间限制 $2\text{s}$，内存限制 $1024\text{MB}$。

### 题目描述

圣诞节到了，小 Z 在圣诞树上挂满了彩球。

圣诞树一共有 $n$ 个节点，由 $n-1$ 条边进行连接，小 Z 在圣诞树的每个节点上都挂上了恰好一个彩球，其中第 $i$ 个节点上挂的彩球的美丽值为 $a_i$。

小 Z 的幸运数字是 $k$，因此小 Z 想把整棵圣诞树分成若干部分，每部分为树上的一个联通块，把其中每个彩球美丽值之和恰好为 $k$ 的联通块当作礼物送给他的朋友们。

小 Z 想知道他至多可以送出多少份礼物。

以下给出一份形式化的题意：

给定一棵 $n$ 个点的树和定值 $k$，第 $i$ 个点的点权为 $a_i$。

选出尽可能多的联通块，使得每个联通块之间的点不存在交集，且每个联通块内所有点的点权和恰为 $k$。

输出可以选择的最多的联通块个数。

### 输入描述

第一行一个正整数 $T$，表示数据组数，之后对于每组数据：

第一行给定两个整数 $n,k$。

第二行给定 $n$ 个非负整数 $a_1,a_2,...,a_n$。

之后 $n-1$ 行，每行给定两个整数 $u,v$，表示树上的一条边。

### 输出格式

输出 $T$ 行，每行一个整数，表示答案。

### 样例输入1

    4
    7 5
    1 2 1 2 2 1 2
    1 2
    2 3
    3 4
    3 5
    5 6
    5 7
    2 2
    1 0
    1 2
    1 1
    1
    1 2
    1

### 样例输出1

    2
    0
    1
    0

### 样例解释1

对于第一组数据，选择的联通块分别为 ${5,6,7},{2,3,4}$。

### 样例输入2,3

见下发文件。

### 样例输出2,3

见下发文件。

### 数据范围

对于 $30%$ 的数据，$1 \leq \sum_{i=1}^T n_i \leq 200,1 \leq n \leq 20$。

对于 $60%$ 的数据，$1 \leq \sum_{i=1}^T n_i \leq 10^4,1 \leq n \leq 1000$。

对于 $100%$ 的数据，$1 \leq \sum_{i=1}^T n_i \leq 10^6,1 \leq k \leq 10^6,0 \leq a_i \leq 2$。

<!-- roj:downloads:start -->
## 下发数据

- [下载 tree2.ans](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20015/down/tree2.ans)
- [下载 tree2.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20015/down/tree2.in)
- [下载 tree3.ans](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20015/down/tree3.ans)
- [下载 tree3.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20015/down/tree3.in)
<!-- roj:downloads:end -->
