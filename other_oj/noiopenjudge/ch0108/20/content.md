## 描述


Mo和Larry发明了一种信息加密方法。他们首先决定好列数，然后将信息（只包含字母）从上往下依次填入各列，并在末尾补充一些随机字母使其成为一个完整的字母矩阵。例如，若信息是“There's no place like home on a snowy night”并且有5列，Mo会写成：t o i o yh p k n ne l e a ir a h s ge c o n hs e m o tn l e w x注意Mo只会填入字母，且全部是小写形式。在这个例子中，Mo用字母“x”填充了信息使之成为一个完整的矩阵，当然他使用任何字母都是可以的。Mo根据这个矩阵重写信息：首先从左到右写下第一行，然后从右到左写下第二行，再从左到右写下第三行……以此左右交替地从上到下写下各行字母，形成新的字符串。这样，例子中的信息就被加密为：toioynnkpheleaigshareconhtomesnlewx。你的工作是帮助Larry从加密后的信息中还原出原始信息（包括填充的字母）。

## 输入


第一行包含一个整数（范围2到20），表示使用的列数。第二行是一个长度不超过200的字符串。

## 输出


一行，即原始信息。

## 样例输入


```
5
toioynnkpheleaigshareconhtomesnlewx
```


## 样例输出


```
theresnoplacelikehomeonasnowynightx
```


## 来源


East Central North America 2004

