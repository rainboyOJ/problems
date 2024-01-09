## 描述


We have received an order from Pizoor Communications Inc. for a special communication system. The system consists of several devices. For each device, we are free to choose from several manufacturers. Same devices from two manufacturers differ in their maximum bandwidths and prices. By overall bandwidth (B) we mean the minimum of the bandwidths of the chosen devices in the communication system and the total price (P) is the sum of the prices of all chosen devices. Our goal is to choose a manufacturer for each device to maximize B/P.

## 输入


The first line of the input file contains a single integer t (1 ≤ t ≤ 10), the number of test cases, followed by the input data for each test case. Each test case starts with a line containing a single integer n (1 ≤ n ≤ 100), the number of devices in the communication system, followed by n lines in the following format: the i-th line (1 ≤ i ≤ n) starts with mi (1 ≤ mi ≤ 100), the number of manufacturers for the i-th device, followed by mi pairs of positive integers in the same line, each indicating the bandwidth and the price of the device respectively, corresponding to a manufacturer.

## 输出


Your program should produce a single line for each test case containing a single number which is the maximum possible B/P for the test case. Round the numbers in the output to 3 digits after decimal point.

## 样例输入


```
1
3
3 100 25 150 35 80 25
2 120 80 155 40
2 100 100 120 110
```


## 样例输出


```
0.649
```


## 来源


Tehran 2002, First Iran Nationwide Internet Programming Contest

