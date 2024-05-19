## 题目


### 题目背景 
强烈推荐[新用户必读帖](/discuss/show/241461)。

**不熟悉算法竞赛的选手请看这里：**

算法竞赛中要求的输出格式中，**不能有多余的内容**，**这也包括了“请输入整数 $\bm a$ 和 $\bm b$” 这一类的提示用户输入信息的内容**。若包含了这些内容，将会被认为是 `Wrong Answer`，即洛谷上的 `WA`。在对比代码输出和标准输出时，系统将忽略每一行结尾的空格，以及最后一行之后多余的换行符。

若因此类问题出现本机似乎输出了正确的结果，但是实际提交结果为错误的现象，请勿认为是洛谷评测机出了问题，而是你的代码中可能存在多余的输出信息。用户可以参考在题目末尾提供的代码。

此外，**请善用应用中的在线 IDE 功能**，以避免不同平台的评测产生差异。

最后，请不要在对应的题目讨论区中发布自己的题解，请发布到题解区域中，否则将处以删除或禁言的处罚。若发现无法提交题解则表明本题题解数量过多，仍不应发布讨论。若您的做法确实与其他所有题解均不一样，请联系管理员添加题解。



### 题目描述

输入两个整数 $a, b$，输出它们的和（$|a|,|b| \le {10}^9$）。

注意

1. Pascal 使用 `integer` 会爆掉哦！
2. 有负数哦！
3. C/C++ 的 main 函数必须是 `int` 类型，而且 C 最后要 `return 0`。这不仅对洛谷其他题目有效，而且也是 NOIP/CSP/NOI 比赛的要求！

好吧，同志们，我们就从这一题开始，向着大牛的路进发。

> 任何一个伟大的思想，都有一个微不足道的开始。




### 输入格式
两个以空格分开的整数。



### 输出格式

一个整数。



### 样例


输入/输出 # 1

::: line
```
20 30

```

```
50

```
:::





### 说明/提示
**广告**

洛谷出品的算法教材，帮助您更简单的学习基础算法。[【官方网店绝赞热卖中！】>>>](https://item.taobao.com/item.htm?id=637730514783)

[![](https://cdn.luogu.com.cn/upload/image_hosting/njc7dlng.png)](https://item.taobao.com/item.htm?id=637730514783)

**本题各种语言的程序范例：**

C
```c
#include <stdio.h>

int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d\n", a+b);
    return 0;
}
```
----------------

C++
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a,b;
    cin >> a >> b;
    cout << a+b << endl;
    return 0;
}
```
----------------

Pascal
```cpp
var a, b: longint;
begin
    readln(a,b);
    writeln(a+b);
end.
```
-----------------

Python2

```cpp
s = raw_input().split()
print int(s[0]) + int(s[1])
```
-----------------

Python3

```cpp
s = input().split()
print(int(s[0]) + int(s[1]))
```
-----------------

Java
```java
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String args[]) throws Exception {
        Scanner cin=new Scanner(System.in);
        int a = cin.nextInt(), b = cin.nextInt();
        System.out.println(a+b);
    }
}
```
-----------------

JavaScript （Node.js）

```javascript
const fs = require('fs')
const data = fs.readFileSync('/dev/stdin')
const result = data.toString('ascii').trim().split(' ').map(x => parseInt(x)).reduce((a, b) => a + b, 0)
console.log(result)
process.exit() // 请注意必须在出口点处加入此行
```

-----------------

Ruby

```ruby
a, b = gets.split.map(&:to_i)
print a+b
```

-----------------

PHP

```php
<?php
$input = trim(file_get_contents("php://stdin"));
list($a, $b) = explode(' ', $input);
echo $a + $b;
```

-----------------

Rust

```rust
use std::io;

fn main(){
    let mut input=String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s=input.trim().split(' ');

    let a:i32=s.next().unwrap()
               .parse().unwrap();
    let b:i32=s.next().unwrap()
               .parse().unwrap();
    println!("{}",a+b);
}
```

-----------------

Go

```go
package main

import "fmt"

func main() {
    var a, b int
    fmt.Scanf("%d%d", &a, &b)
    fmt.Println(a+b)
}
```

-----------------

C# Mono

```cs
using System;

public class APlusB{
    private static void Main(){
        string[] input = Console.ReadLine().Split(' ');
        Console.WriteLine(int.Parse(input[0]) + int.Parse(input[1]));
    }
}
```

------------------

Visual Basic Mono

```vb
Imports System

Module APlusB
    Sub Main()
        Dim ins As String() = Console.ReadLine().Split(New Char(){" "c})
        Console.WriteLine(Int(ins(0))+Int(ins(1)))
    End Sub
End Module
```

------------------

Kotlin

```kotlin
fun main(args: Array<String>) {
    val (a, b) = readLine()!!.split(' ').map(String::toInt)
    println(a + b)
}
```

------------------

Haskell

```haskell
main = do
    [a, b] <- (map read . words) `fmap` getLine
    print (a+b)
```

------------------

Lua

```lua
a = io.read('*n')
b = io.read('*n')
print(a + b)
```

------------------

OCaml

```ocaml
Scanf.scanf "%i %i\n" (fun a b -> print_int (a + b))
```

------------------

Julia

```julia
nums = map(x -> parse(Int, x), split(readline(), " "))
println(nums[1] + nums[2])
```

------------------

Scala

```scala
object Main extends App {
    println(scala.io.StdIn.readLine().split(" ").map(_.toInt).sum)
}
```

------------------

Perl

```perl
my $in = <STDIN>;
chomp $in;
$in = [split /[\s,]+/, $in];
my $c = $in->[0] + $in->[1];
print "$c\n";
```



## 来源

- [luogu P1001](https://www.luogu.com.cn/problem/P1001)
