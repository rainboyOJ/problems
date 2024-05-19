//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-14 16:53:39
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m; //m是钱
int v[maxn]; // 第个菜的钱

int f[105][1005];

int main (int argc, char *argv[]) {
    cin >>n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> v[i];
    }
    f[0][0] = 1;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 0;j<=m;j++){
            f[i][j] = f[i-1][j]; //不吃这个第i个菜
            if( j >= v[i]) {
                f[i][j] += f[i-1][j-v[i]];
            }
            // cout << f[i][j] << " ";
        }
        // cout << endl;
    }
    cout << f[n][m];


    return 0;
}
