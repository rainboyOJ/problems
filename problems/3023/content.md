分形，具有以非整数维形式充填空间的形态特征。

通常被定义为“一个粗糙或零碎的几何形状，可以分成数个部分，且每一部分都（至少近似地）是整体缩小后的形状”，即具有自相似的性质。

现在，定义“盒子分形”如下：

一级盒子分形：

```
   X
```

二级盒子分形：

```
   X X
    X
   X X
```

如果用B(n - 1)代表第n-1级盒子分形，那么第n级盒子分形即为：

```
  B(n - 1)        B(n - 1)

          B(n - 1)

  B(n - 1)        B(n - 1)
```

你的任务是绘制一个n级的盒子分形。

#### 输入格式

输入包含几个测试用例。

输入的每一行包含一个不大于7的正整数n，代表要输出的盒子分形的等级。

输入的最后一行为-1，代表输入结束。

#### 输出格式

对于每个测试用例，使用“X”符号输出对应等级的盒子分形。

请注意’X’是一个大写字母。

每个测试用例后输出一个独立一行的短划线。

#### 输入样例：

```
1
2
3
4
-1
```

#### 输出样例

```
X
-
X X
 X
X X
-
X X   X X
 X     X
X X   X X
   X X
    X
   X X
X X   X X
 X     X
X X   X X
-
X X   X X         X X   X X
 X     X           X     X
X X   X X         X X   X X
   X X               X X
    X                 X
   X X               X X
X X   X X         X X   X X
 X     X           X     X
X X   X X         X X   X X
         X X   X X
          X     X
         X X   X X
            X X
             X
            X X
         X X   X X
          X     X
         X X   X X
X X   X X         X X   X X
 X     X           X     X
X X   X X         X X   X X
   X X               X X
    X                 X
   X X               X X
X X   X X         X X   X X
 X     X           X     X
X X   X X         X X   X X
-
```

## 来源 
- 《算法竞赛进阶指南》
- [acwing](https://www.acwing.com/problem/content/120/) 可能含有视频讲解