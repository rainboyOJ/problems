### 题目描述

在一次藏宝游戏中，你得到了一张藏宝图。这张图是一个由大写字母组成的矩形网格。某些藏宝线索藏在这张图中，线索以某个单词的形式隐藏在特定的位置中。

藏宝线索的字母在网格中总是**按照顺序连续**地出现，可能沿着**横向、纵向或对角线方向**隐藏。有两种情况：

- 所有字母都在一条直线上；
- 字母从某一点开始，其中一部分字母在一条直线上，接着剩下的字母在与之垂直的第二条直线上，两个方向形成一个直角拐弯。

现在，你得到了一张藏宝图和一个需要寻找的线索单词。你的任务是统计这个单词在藏宝图中出现了多少次。

### 输入格式

第一行是一个由不同大写英文字母组成的字符串 $W$，表示你要寻找的藏宝线索单词，长度至少为 2。

第二行是一个整数 $R\ (1 \leq R \leq 100)$，表示藏宝图的行数。

第三行是一个整数 $C\ (1 \leq C \leq 100)$，表示藏宝图的列数。

接下来的 $R$ 行，每行包含 $C$ 个用空格隔开的大写英文字母，组成整张藏宝图。

### 输出格式

输出一个整数，表示单词在藏宝图中出现次数。

### 数据范围

对于 20% 的数据，单词在水平线上。

对于另外 20% 的数据，单词在水平或竖直线上。

对于另外 20% 的数据，单词在水平、竖直或斜着的线上。

对于 100% 的数据，单词在一条或两条互相垂直的线上。

### 输入输出样例

#### 输入样例1

```
MENU
5
7
F T R U B L K
P M N A X C U
A E R C N E O
M N E U A R M
M U N E M N S
```

#### 输出样例1

```
3
```

#### 输入样例2

```
NATURE
6
9
N A T S F E G Q N
S A I B M R H F A
C F T J C U C L T
K B H U P T A N U
D P R R R J D I R
I E E K M E G B E
```

#### 输出样例2

```
4
```

#### 输入/输出样例3

见下发文件，满足单词在水平、竖直或斜着的线上。

#### 输入/输出样例4

见下发文件。

<!-- roj:downloads:start -->
## 下发数据

- [下载 treasure3.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20017/down/treasure3.in)
- [下载 treasure3.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20017/down/treasure3.out)
- [下载 treasure4.in](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20017/down/treasure4.in)
- [下载 treasure4.out](https://raw.githubusercontent.com/rainboyOJ/problems/master/roj/20017/down/treasure4.out)
<!-- roj:downloads:end -->
