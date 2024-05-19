//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-19 10:55:27
#include <bits/stdc++.h>
using namespace std;
const int maxn = 21;
int n,m;
int w[maxn][maxn];
int f[1<<21][21];
const int inf = 0x7f7f7f7f;

//s的p位置是否是1
bool pos_is_1(int s,int p) {
    return (s & ( 1<< p));
}

//去除 s的里的p位置的1
int remove(int s,int p)
{
    return s & ~(1<<p);
}


int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 0;i < n ;++i ) // i: 0->n
    {
        for(int j = 0;j < n ;++j ) // j: 0->n
        {
            cin >> w[i][j];
        }
    }
    memset(f,0x7f,sizeof(f));
    f[1][0] = 0; //起点状态

    //开始dp
    int final_state = (1<<n) - 1;

    //枚举状态
    for( int state = 1 ; state <= final_state; state++ )
    {
        // 枚举j值,和state组合成f(state,j)
        for(int j =  0;j < n;j++)
        {
            if( !pos_is_1(state,j)) continue;

            // 枚举前一个点
            for(int s = 0 ; s < n ; s++) {
                //没有连接
                if( w[s][j] == 0) continue;
                //如果state 里 没有s,也不合法
                if( !pos_is_1(state,s) ) continue;
                //前一个状
                int k = remove(state,j);
                //这个状态不存在
                if( f[k][s] == inf) continue;
                f[state][j] = min(f[state][j],f[k][s] + w[s][j]);
            }
        }
    }
    std::cout << f[final_state][n-1] << "\n";

    return 0;
}
