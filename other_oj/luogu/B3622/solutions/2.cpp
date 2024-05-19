//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-05 10:44:50
// dfs 枚举每个元素的选或不选
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];


void dfs(int dep) {
    if( dep > n) {
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            if( a[i] == 0) cout << 'N';
            else cout << 'Y';
        }
        std::cout  << "\n";
        return ;
    }
    for(int i = 0;i <= 1 ;++i ) // i: 0->1
    {
        a[dep] = i;
        dfs(dep+1);
    }
}


int main (int argc, char *argv[]) {
    std::cin >> n;
    dfs(1);
    return 0;
}
