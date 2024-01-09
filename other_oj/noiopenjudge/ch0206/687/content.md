## 描述


A company producing toys has a complex system to paint its products. To obtain the desired color, the product must be painted by several colors in a specified order. A product is painted by moving through color tunnels. For each color there is at least one tunnel that paints with that color, but there may be more. The tunnels are distributed in the painting area and the product must be delivered from one tunnel to another in order to be painted with the given colors. The product is at a certain point in the production plant when painting process starts and must finally be delivered to the product warehouse.More formally, a finished uncolored product is at a certain given point (source point) and must be delivered to another given point (destination point) after being painted with different colors in a given order. There are several tunnels, each is assumed to be a line segment in the plain with a specific color. The colors of the tunnels are not necessarily distinct.   Let < c1, c2, ..., cn > be the sequence of n colors that the product is to be painted with. The product is required to pass through tunnels  < t1, t2, ... tn > such that the color of ti is ci. Note that it is possible to pass through a tunnel without being painted, so the mentioned < t1, t2, ... tn > may be in fact a subsequence of the tunnels which the product passes through. The direction in which the product passes a tunnel is not important. The goal is to find the shortest path from source to destination subject to the color constraints. The path may cross itself, or even cross a tunnel. Passing twice (or more) through a tunnel is also allowed. Note that two tunnels can cross or overlap but are different.

## 输入


The input file contains several test cases. The first line of the input consists of a single integer t (between 1 and 20), the number of test cases. Following the first line is the data for t test cases. The first line of each test case contains four real numbers xs, ys, xt, yt which are x and y coordinates of the source and destination respectively. The second line of the test case contains the color sequence: the first number is the length of the sequence (between 1 and 30), and the rest of the line is the sequence itself. Each color in the sequence is an integer in the range 1...100. The third line contains a single integer n in the range 1...60 which is the number of tunnels followed by n lines each containing five numbers. The first two numbers are the x and y coordinates of one end of the tunnel. The third and fourth numbers are the x and y coordinates of the other end. Coordinates are real numbers. The fifth number is an integer in the range 1...100 

## 输出


The output file must have t lines, each containing the minimum length of a path from source to destination subject to the constraints of the problem. The length will be compared to optimal length within a precision of three digits after decimal point.

## 样例输入


```
1
0 1.5 100 67
4 1 4 3 1
9
10 10 20 20 1
10 15 20.5 35.333 3
30 15 14.55 12.5 1
40 30 44 33 1
29 84 33 58 4
9 39 41 115 2
75 47 37 69 4
46 26 58 25 3
73 48 27 59 3

```


## 样例输出


```
240.60967918717043
```


## 来源


Tehran 2000

