### 【题目描述】

译自 BalticOI 2011 Day1 T3「Switch the Lamp On」

有一种正方形的电路元件，在它的两组相对顶点中，有一组会用导线连接起来，另一组则不会。

有 N×M 个这样的元件，你想将其排列成 N 行 M 列放在电路板上。电路板的左上角连接电源，右下角连接灯泡。

![](pic/1448.jpg)

试求：至少要旋转多少个正方形元件才能让电源与灯泡连通，若无解则输出 NO SOLUTION。

Casper is designing an electronic circuit on a N×M rectangular grid plate. There are N×M square tiles that are aligned to the grid on the plate. Two (out of four) opposite corners of each tile are connected by a wire.

A power source is connected to the top left corner of the plate. A lamp is connected to the bottom right corner of the plate. The lamp is on only if there is a path of wires connecting power source to lamp. In order to switch the lamp on, any number of tiles can be turned by

90° (in both directions).

In the picture above the lamp is off. If any one of the tiles in the second column from the right is turned by 90° , power source and lamp get connected, and the lamp is on.

Write a program to find out the minimal number of tiles that have to be turned by 90° to switch the lamp on.

### 【输入】

第一行有两个整数 N 和 M。

在接下来的 N 行中，每行有 M 个字符。每个字符均为 "\\" 或 "/"，表示正方形元件上导线的连接方向。

The first line of input contains two integer numbers N and M, the dimensions of the plate. In each of the following N lines there are M symbols – either  \\ or / – which indicate the direction of the wire connecting the opposite vertices of the corresponding tile.

### 【输出】

输出共一行，若有解则输出一个整数，表示至少要旋转多少个正方形元件才能让电源与灯泡连通；若无解则输出 NO SOLUTION。

There must be exactly one line of output. If it is possible to switch the lamp on, this line must contain only one integer number: the minimal number of tiles that have to be turned to switch on the lamp. If it is not possible, output the string: NO SOLUTION

### 【输入样例】

```
3 5
\\\\/\\
\\\\///
/\\\\\\\\
```

### 【输出样例】

```
1
```

### 【提示】

对于 40% 的数据，1≤N≤4,1≤M≤5。

对于所有数据，1≤N,M≤500。


 ### 【来源】

 一本通在线评测 