## 描述


Farmer John's cows are getting restless about their poor telephone service; they want FJ to replace the old telephone wire with new, more efficient wire. The new wiring will utilize N (2 <= N <= 100,000) already-installed telephone poles, each with some height_i meters (1 <= height_i <= 100). The new wire will connect the tops of each pair of adjacent poles and will incur a penalty cost C * the two poles' height difference for each section of wire where the poles are of different heights (1 <= C <= 100). The poles, of course, are in a certain sequence and can not be moved.Farmer John figures that if he makes some poles taller he can reduce his penalties, though with some other additional cost. He can add an integer X number of meters to a pole at a cost of X^2.Help Farmer John determine the cheapest combination of growing pole heights and connecting wire so that the cows can get their new and improved service.

## 输入


* Line 1: Two space-separated integers: N and C* Lines 2..N+1: Line i+1 contains a single integer: height_i

## 输出


* Line 1: The minimum total amount of money that it will cost Farmer John to attach the new telephone wire.

## 样例输入


```
5 2
2
3
5
1
4
```


## 样例输出


```
15
```


## 提示


INPUT DETAILS:There are 5 telephone poles, and the vertical distance penalty is $2/meter. The poles initially have heights of 2, 3, 5, 1, and 4, respectively.OUTPUT DETAILS:The best way is for Farmer John to raise the first pole by 1 unit and the fourth pole by 2 units, making the heights (in order) 3, 3, 5, 3, and 4. This costs $5. The remaining wiring will cost $2*(0+2+2+1) = $10, for a total of $15.

## 来源


USACO November 2007 Gold

