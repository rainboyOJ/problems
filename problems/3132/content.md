FOTILE得到了一个长为N的序列A，为了拯救地球，他希望知道某些区间内的最大的连续XOR和。

即对于一个询问，你需要求出max(Ai xor A\[i+1\] xor A\[i+2\] … xor Aj)，其中l<=i<=j<=r。

为了体现在线操作，对于一个询问(x,y)：

l = min ( ((x+lastans) mod N)+1 , ((y+lastans) mod N)+1 )  
r = max ( ((x+lastans) mod N)+1 , ((y+lastans) mod N)+1 )

其中lastans是上次询问的答案，一开始为0。

#### 输入格式

第一行两个整数N和M。

第二行有N个正整数，其中第i个数为$A\_i$。

后M行每行两个整数x,y表示一对询问。

#### 输出格式

共M行，每行输出一个正整数，第i行的正整数表示第i个询问的结果。

#### 数据范围

$N=12000，M=6000，0 < x,y,Ai < 2^{31}$

#### 输入样例：

```
3 3
1 4 3
0 1
0 1
4 3
```

#### 输出样例：

```
5
7
7
```

## 来源 
- 《算法竞赛进阶指南》
- [acwing](https://www.acwing.com/problem/content/271/) 可能含有视频讲解