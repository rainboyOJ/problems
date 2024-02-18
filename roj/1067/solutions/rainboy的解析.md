---
title: "rainboy的解析"
date: "2024-01-20 11:08"
update: "2024-01-20 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

本质考的是: `for`与`if`的使用

## 代码1

```cpp
#include <iostream>
using namespace std;

int n;
int cnt1;
int cnt5;
int cnt10;
int main()
{
    cin >> n; // 读取数据的个数
    for (int i = 1; i <= n; i++) //循环n次
    {
        int t;
        cin >> t; // 读取一个数
        if (t == 1) // 如果是1
            cnt1++;
        if (t == 5)// 如果是5
            cnt5++;
        if (t == 10)// 如果是10
            cnt10++;
    }

  //输出答案
    cout << cnt1 << endl;
    cout << cnt5 << endl;
    cout << cnt10 << endl;
    return 0;
}

```
