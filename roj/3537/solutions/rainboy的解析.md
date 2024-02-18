---
title: "rainboy的解析"
date: "2024-01-20 11:08"
update: "2024-01-20 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析

本质考的是: 桶思想

注意时间复杂度的计算

## 代码1

```cpp
#include <iostream>
using namespace std;
const int maxn= 1e5+5;
int b[maxn]; // 桶 bucket
int n,m;
int sum;

int main()
{
    cin >> n >> m; //n个树,m个操作
    for (int j = 0; j < m; j++) // 进行m个操作
    {
        int t1,t2;
        cin >> t1 >> t2; // 操作的起点,终点
        for(int i = t1;i<=t2;i++) { // 桶为1,表示删除
            b[i] = 1;
        }
    }
    for (int i = 0; i <= n; i++) // 统计为0的数量
    {
        if( b[i] == 0) sum++;
    }
    cout << sum; // 输出统计
    return 0;
}
 
```
