## 描述


Alice and Bob decide to play a funny game. At the beginning of the game they pick n(1 <= n <= 106) coins in a circle, as Figure 1 shows. A move consists in removing one or two adjacent coins, leaving all other coins untouched. At least one coin must be removed. Players alternate moves with Alice starting. The player that removes the last coin wins. (The last player to move wins. If you can't move, you lose.)Figure 1Note: For n > 3, we use c1, c2, ..., cn to denote the coins clockwise and if Alice remove c2, then c1 and c3 are NOT adjacent! (Because there is an empty place between c1 and c3.)Suppose that both Alice and Bob do their best in the game. You are to write a program to determine who will finally win the game. 

## 输入


There are several test cases. Each test case has only one line, which contains a positive integer n (1 <= n <= 106). There are no blank lines between cases. A line with a single 0 terminates the input.

## 输出


For each test case, if Alice win the game,output "Alice", otherwise output "Bob".

## 样例输入


```
1
2
3
0

```


## 样例输出


```
Alice
Alice
Bob
```


## 来源


POJ Contest,Author:Mathematica@ZSU

