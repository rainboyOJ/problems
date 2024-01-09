/**
 * 解析:
 * f[i] 表示有 有i个东西的吃法
 * f[i] = f[i-1] + f[i-2]
 */
/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 03日 星期四 14:24:45 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */
int f[maxn];
int main(int argc,char * argv[]){
    std::cin >> n;
    f[1] = 1;
    f[0] = 1;
    for(int i=2;i<=n;++i){
        f[i] = f[i-1] + f[i-2];
    }
    std::cout << f[n] << std::endl;
    return 0;
}
