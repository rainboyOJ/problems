### 问题描述

给定长度为 $n$ 的非负整数序列 $a$，要求将序列 $a$ 分成 $2$ 个可重集合 $A,B$，满足每个元素在 $A$ 集合或 $B$ 集合，恰有 $2^n$ 种划分方式，现在额外要求集合 $A$ 中所有元素或运算的权值与集合 $B$ 中所有元素或运算的权值相同，特别地，当集合为空时，定义其所有元素的或运算权值为 $0$，请求满足条件的方案数，答案对 $998244353$ 取模。

### 输入格式

第一行包含 $1$ 个正整数 $n$。

第二行包含 $n$ 个整数，表示 $a_i$。

### 输出格式

输出共 $1$ 行，输出 $1$ 个整数，表示最终答案，答案对 $998244353$ 取模。

### 样例输入1

    4
    4 5 6 7

### 样例输出1

    4

### 样例解释

合法的 $A$ 集合有 $(4,5,6),(5,6),(7),(4,7)$ 四种情况，对应的 $B$ 集合为 $(7),(4,7),(4,5,6),(5,6)$。

### 样例输入2

    7
    4 5 6 7 2 3 4

### 样例输出2

    84

### 样例输入3,4,5

见下发文件。

### 样例输出3,4,5

见下发文件。

### 评测数据规模

对于 $30%$ 的数据，$n \leq 20$​。

对于另外 $30%$ 的数据，$0 \leq a_i < 4$。

对于所有测评数据，$1 \leq n \leq 200,0 \leq a_i < 2^{15}$。

<!-- roj:downloads:start -->
## 下发数据

- [下载 partition3.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20020/down/partition3.in)
- [下载 partition3.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20020/down/partition3.out)
- [下载 partition4.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20020/down/partition4.in)
- [下载 partition4.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20020/down/partition4.out)
- [下载 partition5.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20020/down/partition5.in)
- [下载 partition5.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20020/down/partition5.out)
<!-- roj:downloads:end -->
