//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-01 15:49:28
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];

//f[i] 表示一定保留 第i个元素的时候
// 最多能保留多少个
int f[maxn];

int sub(int i,int j) {
    int t = a[i] - a[j];
    if( t < 0)
        t = -t;
    return t;
}

int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
    int Max = 0;
    for(int i = 1;i <= n ;++i ) // i: 2->n
    {
        f[i] = 1;
        for(int j =1;j< i;j++) {
            if( sub(i,j) != 1)
            {
                int t = f[j] +1;
                f[i] = max(f[i],t);
                Max = max(Max,f[i]);
            }
        }
        // cout << i << " " <<  a[i] << " " << f[i] <<endl;
    }
    std::cout << n-Max << "\n";
    

    return 0;
}
