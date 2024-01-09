## 描述


When a radio station is broadcasting over a very large area, repeaters are used to retransmit the signal so that every receiver has a strong signal. However, the channels used by each repeater must be carefully chosen so that nearby repeaters do not interfere with one another. This condition is satisfied if adjacent repeaters use different channels.Since the radio frequency spectrum is a precious resource, the number of channels required by a given network of repeaters should be minimised. You have to write a program that reads in a description of a repeater network and determines the minimum number of channels required.

## 输入


The input consists of a number of maps of repeater networks. Each map begins with a line containing the number of repeaters. This is between 1 and 26, and the repeaters are referred to by consecutive upper-case letters of the alphabet starting with A. For example, ten repeaters would have the names A,B,C,...,I and J. A network with zero repeaters indicates the end of input.Following the number of repeaters is a list of adjacency relationships. Each line has the form:A:BCDHwhich indicates that the repeaters B, C, D and H are adjacent to the repeater A. The first line describes those adjacent to repeater A, the second those adjacent to B, and so on for all of the repeaters. If a repeater is not adjacent to any other, its line has the formA:The repeaters are listed in alphabetical order.Note that the adjacency is a symmetric relationship; if A is adjacent to B, then B is necessarily adjacent to A. Also, since the repeaters lie in a plane, the graph formed by connecting adjacent repeaters does not have any line segments that cross. 

## 输出


For each map (except the final one with no repeaters), print a line containing the minumum number of channels needed so that no adjacent channels interfere. The sample output shows the format of this line. Take care that channels is in the singular form when only one channel is required.

## 样例输入


```
2
A:
B:
4
A:BC
B:ACD
C:ABD
D:BC
4
A:BCD
B:ACD
C:ABD
D:ABC
0
```


## 样例输出


```
1 channel needed.
3 channels needed.
4 channels needed. 
```


## 来源


Southern African 2001

