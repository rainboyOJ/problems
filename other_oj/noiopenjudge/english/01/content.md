## 描述


Given edges of a graph with N nodes. There are three colors that can be used for coloring nodes. Determine the color of each node so that the colors of nodes of each edge should be different.

## 输入


First line: one positive integer N (N <= 20).Next N lines: an N*N 0/1 matrix A={a[i][j]} indicating whether there exists an edge (a[i][j]=1) between Node i and Node j or not (a[i][j]=0).

## 输出


N lines, the i-th line contains one integer c[i] indicating the color of the i-th node (c[i] = 1, 2, or 3).

## 样例输入


```
4
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0

```


## 样例输出


```
1
2
1
2

```


