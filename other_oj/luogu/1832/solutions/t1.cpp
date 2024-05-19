//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-21 14:52:31
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];
bool is_prime(int a) {
    for(int i =2;i *i <= a;i++)
        if( a % i == 0) 
            return 0;
    return 1;
}
int cnt;
int p[maxn]; //存所有的素数
int pc[maxn]; //存p[i]最多有多少个
long long f[2500][1005];
int w[maxn]; //每个物品的重量

int main (int argc, char *argv[]) {
    std::cin >> n;
    f[0][0] = 1; // 边界
    for(int i = 2;i <= n;++i ) // i: 2->1000
    {
        if( is_prime(i)) {
            cnt++;
            p[cnt] = i;
            pc[cnt] = n/ i;
            // cout << i << " ";
        }
    }

    for(int i =1;i<=cnt;i++) { //枚举物品
        for(int j = 0 ;j<=n;j++) //枚举容量
        {
            f[i][j] = f[i-1][j]; //不选
            //其它可能性,要么选1 个,要么选2个,....
            for(int k =1;k<=pc[i];k++) { 
                int w = k *p[i];
                if( w <= j)
                    f[i][j] += f[i-1][j-w];
            }
        }
    }
    cout << f[cnt][n] << endl;

    // for(int i =1;i<=cnt;i++) { //枚举物品
    //     for(int j = 0 ;j<=n;j++) //枚举容量
    //     {
    //         cout << f[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }


    return 0;
}
