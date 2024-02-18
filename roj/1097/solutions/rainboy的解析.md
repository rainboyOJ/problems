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
int n, m;
char c;
int k;
int main()
{
    cin >> n >> m; // n行m列
    cin >> c >> k; // 字符,是否空心

    for (int i = 1; i <= m; i++) // 输出第一行,一定是n个c
        cout << c;
    cout << endl;
    for (int i = 1; i <= n - 2; i++) //输出中间n-2行
    {
        cout << c; // 每行的第一个字符
    // 中间的m-2个字符
        for (int j = 1; j <= m - 2; j++)
        {
            if (k == 0) //如果k为0,应该输出空格
                cout << " ";
            else
                cout << c; // 不空心,输出字符c
        }
        cout << c << endl; //每行的最后一个字符
    }

    for (int i = 1; i <= m; i++)// 输出最后一行,一定是n个c
        cout << c;
    cout << endl;
    return 0;
}
```
