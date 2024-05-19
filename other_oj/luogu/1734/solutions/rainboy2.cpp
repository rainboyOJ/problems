//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-14 15:10:45
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];

// f[i][j] 前i个物品,在容量j的条件下的最大值 
int f[1005][1005];


void pre_work()
{
    // 10^6
    for(int i = 1;i <= 1000 ;++i ) // i: 1->1000
    {
        for(int j = 1;j < i ;++j ) // j: 1->i
        {
            if( i % j == 0)
                a[i] += j;
        }
    }
}

//01背包
void kn01() {
    for(int i =1;i<=n;i++) { //物品
        for(int j =1;j<=n;j++) { //容量
            f[i][j] = f[i-1][j]; // 不选第i个物品

            if( j >= i){//可以放下来
                if( f[i][j] < f[i-1][j-i] + a[i])
                    f[i][j] = f[i-1][j-i] + a[i];
            }
            // cout << f[i][j] << " ";
        }
        // cout << endl;
    }
}


int main (int argc, char *argv[]) {
    cin >> n;
    pre_work();
    kn01();
    cout << f[n][n] << endl;

    return 0;
}
