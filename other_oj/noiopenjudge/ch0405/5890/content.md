## 描述


John Doe, a skilled pilot, enjoys traveling. While on vacation, he rents a small plane and starts visiting beautiful places. To save money, John must determine the shortest closed tour that connects his destinations. Each destination is represented by a point in the plane pi = < xi,yi >. John uses the following strategy: he starts from the leftmost point, then he goes strictly left to right to the rightmost point, and then he goes strictly right back to the starting point. It is known that the points have distinct x-coordinates.Write a program that, given a set of n points in the plane, computes the shortest closed tour that connects the points according to John's strategy.

## 输入


The program input is from a text file. Each data set in the file stands for a particular set of points. For each set of points the data set contains the number of points, and the point coordinates in ascending order of the x coordinate. White spaces can occur freely in input. The input data are correct.The number of points of each data set is at most 50, and each coordinate does not exceed 20000 by an absolute value.

## 输出


For each set of data, your program should print the result to the standard output from the beginning of a line. The tour length, a floating-point number with two fractional digits, represents the result. An input/output sample is in the table below. Here there are two data sets. The first one contains 3 points specified by their x and y coordinates. The second point, for example, has the x coordinate 2, and the y coordinate 3. The result for each data set is the tour length, (6.47 for the first data set in the given example).

## 样例输入


```
3
1 1
2 3
3 1
4
1 1
2 3
3 1
4 2
```


## 样例输出


```
6.47
7.89
```


