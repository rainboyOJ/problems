## 题目描述
有一种奇怪的语言叫做“二五语言”.它的每个单词都由 A～Y这 25个字母各一个组成.合法的二五语言单词必须满足这样一个条件:把它的 25 个字母排成一个 5*5 的矩阵,它的每一行和每一列

都必须是递增的.比如单词 ACEPTBDHQUFJMRWGKNSXILOVY,它排成的矩阵如下所示:

```
A C E P T
B D H Q U
F J M R W
G K N S X
I L O V Y
```

它每行每列都是递增的,是一个合法的单词.而 YXWVUTSRQPONMLKJIHGFEDCBA 则不合法.
由于单词太长存储不便,需要给每一个单词编一个码.编码方法如下:写出单词中字母 A 在矩阵中的
行号和列号,再写出 B 的行号和列号……依此类推.得到的序列叫做行列序列.如上面的合法单词的
行列序列是:11 21 12 22 13 31 41 23 51 32 42 52 33 43 53 14 24 34 44 15 25 54 35 45 55.
然后把所有合法单词的行列序列排序.一个单词的行列序列排序后的位置,就是这个单词的编码.比
如,单词 ABCDEFGHIJKLMNOPQRSTUVWXY 的编码为 1,而单词 ABCDEFGHIJKLMNOPQRSUTVWXY 的编码为 2.
现在,你需要编一个程序,完成单词与编码间的转换.

## INPUT FORMAT

第一行为一个字母 N 或 W.N 表示把编码转换为单词,W 表示把单词转换为编码.

若第一行为 N,则第二行为一个整数,表示单词的编码.若第一行为 W,则第二行为一个合法的单词.

## SAMPLE INPUT #1(file twofive.in)

```
N
2
```

**SAMPLE INPUT #2**

```
W
ABCDEFGHIJKLMNOPQRSUTVWXY
```

## OUTPUT FORMAT

每行一个整数或单词.

## SAMPLE OUTPUT #1(file twofive.out)

```
ABCDEFGHIJKLMNOPQRSUTVWXY
```

**SAMPLE OUTPUT #2**
```
2 
```
