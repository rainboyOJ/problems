## 题目描述
有时候程序员有很奇怪的方法来隐藏他们的口令.Billy"Hacker"Geits 会选择一个字符串
S（由 L 个小写字母组成,5<=L<=100,000）,然后他把 S 顺时针绕成一个圈,每次取一个做开头字母并顺时针依次取字母而组成一个字符串.这样将得到一些字符串,他把它们排序后取出第一个字符
串.把这个字符串的第一个字母在原字符串中的位置-1 做为口令.

如字符串 alabala,按操作的到 7 个字符串,排序后得:

```
aalabal
abalaal
alaalab
alabala
balaala
laalaba
labalaa
```

第一个字符串为 aalabal,这个 a 在原字符串位置为 7,7-1=6,则 6 为口令.

## INPUT FORMAT

第一行:一个数:L

第二行:字符串:S

## SAMPLE INPUT (file hidden.in)
```
7
alabala
```

## OUTPUT FORMAT

一行,为得到的口令

## SAMPLE OUTPUT (file hidden.out)
```
6
```
