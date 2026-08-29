### 时间限制：1000ms

### 内存限制：512MB

### 问题描述

初始时给定一个长度为 $n$ 的正整数序列 $a_i$​，序列下标为 $[0,n-1]$，现有一个二维数组 $b$，执行以下函数

    void init(){
        for(int i=0;i<n;i++) b[0][i]=a[i];
        for(int i=1;i<n;i++)
            for(int j=0;j<n-i;j++) b[i][j]=b[i-1][j]^b[i-1][j+1];
    }

现给出 $q$ 次询问，每次询问给定非负整数 $x,y$，保证有 $0 \leq x+y \leq n-1$，试给出 $b[x][y]$​ 的权值大小。

提示：组合数 $C_a^b \bmod 2=[a & b = b]$

### 输入格式

第一行包含 $2$ 个正整数 $n,q$​。

第二行给定长度为 $n$ 的正整数序列 $a$​。

之后 $q$ 行，每行给出 $2$ 个参数 $x,y$，表示一次询问。

### 输出格式

输出 $q$ 行，每行输出 $1$ 个整数，表示最终答案。

### 样例输入1

    4 4
    9 5 9 2
    1 2
    0 0
    0 2
    3 0

### 样例输出1

    11
    9
    9
    7

### 样例解释

$b$ 序列的形态为

    9 5 9 2
    12 12 11
    0 7
    7

### 样例输入2

见下发文件，数据保证每组询问的 $x,y$ 为所有可能的询问中等概率生成的。

### 样例输出2

见下发文件。

### 评测数据规模

对于 $20%$ 的数据，$1 \leq n \leq 5000$。

对于 $40%$ 的数据，数据保证每组询问的 $x,y$ 为所有可能的询问中等概率生成的。

对于所有测评数据，$1 \leq n,q \leq 10^5,0 \leq a_i \leq 10^9$。

<!-- roj:downloads:start -->
## 下发数据

- [下载 xor.ans](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20030/down/xor.ans)
- [下载 xor.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20030/down/xor.in)
<!-- roj:downloads:end -->
