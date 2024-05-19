//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-16 15:03:35
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5005;
int n,m;
int p[maxn][maxn]; //记录最优决策点 
int f[maxn][maxn];
int sum[maxn];

const int inf = 0x7fffffff;


//区间和
int w(int i,int j) { return sum[j] - sum[i-1]; }

int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;
        sum[i] = sum[i-1] + t;
    }

    //初始化p值
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        p[i][i] = i;
    }

    //枚举长度
    for(int len = 2;len <= n ;++len ) // i: 2->n
    {
        //枚举起点
        for(int i = 1;i<= n-len+1;i++)
        {
            int j = i+len-1; //终点
            f[i][j] = inf;

            int k1 = p[i][j-1];
            int k2 = p[i+1][j];

            for(int k = k1 ;k<= k2;k++)
            {
                int t = f[i][k] + f[k+1][j] + w(i,j);
                if ( f[i][j] > t) {
                    f[i][j] = t;
                    p[i][j] = k;
                }
            }
            // printf("f[%d][%d] = %d\n",i,j,f[i][j]);
        }
    }
    cout << f[1][n] << endl;


    return 0;
}
