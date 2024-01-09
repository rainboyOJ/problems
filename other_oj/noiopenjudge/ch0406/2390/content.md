## 描述


At Bessie's recent birthday party, she received N (2 <= N <= 100,000; N%2 == 0) pearls, each painted one of C different colors (1 <= C <= N).Upon observing that the number of pearls N is always even, her creative juices flowed and she decided to pair the pearls so that each pair of pearls has two different colors.Knowing that such a set of pairings is always possible for the supplied testcases, help Bessie perform such a pairing. If there are multiple ways of creating a pairing, any solution suffices.

## 输入


* Line 1: Two space-separated integers: N and C* Lines 2..C + 1: Line i+1 tells the count of pearls with color i: C_i

## 输出


* Lines 1..N/2: Line i contains two integers a_i and b_i indicating that Bessie can pair two pearls with respective colors a_i and b_i.

## 样例输入


```
8 3
2
2
4
```


## 样例输出


```
1 3
1 3
2 3
3 2
```


## 提示


INPUT DETAILS:There are 8 pearls and 3 different colors. Two pearls have color I; two have color II; four have color III.OUTPUT DETAILS:Bessie pairs each pearl of color III with one of color I and II.

## 来源


USACO March 2008 Gold

