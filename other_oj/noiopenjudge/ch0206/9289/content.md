## 描述


Bessie was poking around the ant hill one day watching the ants march to and fro while gathering food. She realized that many of the ants were siblings, indistinguishable from one another. She also realized the sometimes only one ant would go for food, sometimes a few, and sometimes all of them. This made for a large number of different sets of ants!Being a bit mathematical, Bessie started wondering. Bessie noted that the hive has T (1 <= T <= 1,000) families of ants which she labeled 1..T (A ants altogether). Each family had some number Ni (1 <= Ni <= 100) of ants.How many groups of sizes S, S+1, ..., B (1 <= S <= B <= A) can be formed?While observing one group, the set of three ant families was seen as {1, 1, 2, 2, 3}, though rarely in that order. The possible sets of marching ants were:3 sets with 1 ant: {1} {2} {3}5 sets with 2 ants: {1,1} {1,2} {1,3} {2,2} {2,3}5 sets with 3 ants: {1,1,2} {1,1,3} {1,2,2} {1,2,3} {2,2,3}3 sets with 4 ants: {1,2,2,3} {1,1,2,2} {1,1,2,3}1 set with 5 ants: {1,1,2,2,3}Your job is to count the number of possible sets of ants given the data above.

## 输入


* Line 1: 4 space-separated integers: T, A, S, and B* Lines 2..A+1: Each line contains a single integer that is an ant type present in the hive

## 输出


*  Line 1: The number of sets of size S..B (inclusive) that can be  created. A set like {1,2} is the same as the set {2,1} and should not be  double-counted. Print only the LAST SIX DIGITS of this number, with no  leading zeroes or spaces.

## 样例输入


```
3 5 2 3
1
2
2
1
3
```


## 样例输出


```
10
```


## 提示


INPUT DETAILS:Three types of ants (1..3); 5 ants altogether. How many sets of size 2 or size 3 can be made?OUTPUT DETAILS:5 sets of ants with two members; 5 more sets of ants with three members 

