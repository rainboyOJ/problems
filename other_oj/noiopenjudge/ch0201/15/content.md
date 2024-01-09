## 描述


Sally Jones has a dozen Voyageur silver dollars. However, only eleven of the coins are true silver dollars; one coin is counterfeit even though its color and size make it indistinguishable from the real silver dollars. The counterfeit coin has a different weight from the other coins but Sally does not know if it is heavier or lighter than the real coins. Happily, Sally has a friend who loans her a very accurate balance scale. The friend will permit Sally three weighings to find the counterfeit coin. For instance, if Sally weighs two coins against each other and the scales balance then she knows these two coins are true. Now if Sally weighs one of the true coins against a third coin and the scales do not balance then Sally knows the third coin is counterfeit and she can tell whether it is light or heavy depending on whether the balance on which it is placed goes up or down, respectively. By choosing her weighings carefully, Sally is able to ensure that she will find the counterfeit coin with exactly three weighings. 

## 输入


The first line of input is an integer n (n > 0) specifying the number of cases to follow. Each case consists of three lines of input, one for each weighing. Sally has identified each of the coins with the letters A--L. Information on a weighing will be given by two strings of letters and then one of the words ``up'', ``down'', or ``even''. The first string of letters will represent the coins on the left balance; the second string, the coins on the right balance. (Sally will always place the same number of coins on the right balance as on the left balance.) The word in the third position will tell whether the right side of the balance goes up, down, or remains even. 

## 输出


For each case, the output will identify the counterfeit coin by its letter and tell whether it is heavy or light. The solution will always be uniquely determined. 

## 样例输入


```
1 
ABCD EFGH even 
ABCI EFJK up 
ABIJ EFGH even 
```


## 样例输出


```
K is the counterfeit coin and it is light. 
```


## 来源


East Central North America 1998

