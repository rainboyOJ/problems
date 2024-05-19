//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-18 19:16:42
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int T,m;
int t[maxn]; //时间
int p[maxn]; //价格

int b[maxn] ;// 桶

int ans = 0;
//tot =total 得到一个对应的价格
int get_tot() {
    int s1 = 0;
    int s2 = 0;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        if( b[i] == 0) continue;
        s1 += t[i];
        s2 += p[i];
    }
    if( s1 > T) return -1;
    return s2;
}
void dfs(int dep) {
    if( dep > m) {
        // for(int i = 1;i <= m ;++i ) // i: 1->m
        // {
        //     cout << b[i] << " ";
        // }
        // std::cout  << "\n";
        int t = get_tot();
        if( ans < t) ans = t;
        return ;
    }
    for(int i = 0;i <= 1 ;++i ) // i: 0->1
    {
        b[dep] = i;
        dfs(dep+1);
    }

}

int main (int argc, char *argv[]) {
    cin >> T >> m;

    for(int i = 1;i <= m ;++i ) // i: 1->n
    {
        cin >> t[i] >> p[i];
    }

    //生成01序列
    dfs(1);
    std::cout << ans << "\n";

    return 0;
}
