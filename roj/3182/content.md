给定 $n$ 个变量和 $m$ 个不等式。其中 $n$ 小于等于26，变量分别用前 $n$ 的大写英文字母表示。

不等式之间具有传递性，即若 A>B 且 B>C ，则 A>C。

请从前往后遍历每对关系，每次遍历时判断：

-   如果能够确定全部关系且无矛盾，则结束循环，输出确定的次序；
-   如果发生矛盾，则结束循环，输出有矛盾；
-   如果循环结束时没有发生上述两种情况，则输出无定解。

#### 输入格式

输入包含多组测试数据。

每组测试数据，第一行包含两个整数n和m。

接下来m行，每行包含一个不等式，不等式全部为小于关系。

当输入一行0 0时，表示输入终止。

#### 输出格式

每组数据输出一个占一行的结果。

结果可能为下列三种之一：

1.  如果可以确定两两之间的关系，则输出 `"Sorted sequence determined after t relations: yyy...y."`,其中`'t'`指迭代次数，`'yyy...y'`是指升序排列的所有变量。
2.  如果有矛盾，则输出： `"Inconsistency found after t relations."`，其中`'t'`指迭代次数。
3.  如果没有矛盾，且不能确定两两之间的关系，则输出 `"Sorted sequence cannot be determined."`。

#### 数据范围

$2 \le n \le 26$，变量只可能为大写字母A~Z。

#### 输入样例1：

```
4 6
A
```

````**#### 输出样例1：

```
Sorted sequence determined after 4 relations: ABCD.
Inconsistency found after 2 relations.
Sorted sequence cannot be determined.
```

#### 输入样例2：

```
6 6
A
```

``#### 输出样例2：

```
Inconsistency found after 6 relations.
```

#### 输入样例3：

```
5 5
A
```

`**#### 输出样例3：

```
Sorted sequence determined after 4 relations: ABCDE.
```**` ``**````

## 来源 
- 《算法竞赛进阶指南》
- [acwing](https://www.acwing.com/problem/content/345/) 可能含有视频讲解