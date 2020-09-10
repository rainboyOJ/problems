## 题目描述

对于一给定的素数集合 S = {p1, p2, ..., pK},来考虑那些质因数全部属于 S 的数的集合.这个集合包括,p1, p1p2, p1p1, 和 p1p2p3 (还有其它).

这是个对于一个输入的 S 的丑数集合.

注意:我们不认为 1 是一个丑数.

你的工作是对于输入的集合 S 去寻找集合中的第 N 个丑数.longint(signed 32-bit)对于程序是足够的.


## INPUT FORMAT

 - 第 1 行: 二个被空间分开的整数:K 和 N , 1<= K<=100 , 1<= N<=100,000.
 - 第 2 行: K 个被空间分开的整数:集合 S 的元素

## SAMPLE INPUT (file humble.in)

```
4 19
2 3 5 7
```
## OUTPUT FORMAT

单独的一行,写上对于输入的 S 的第 N 个丑数.

## SAMPLE OUTPUT (file humble.out)
```
27
```
