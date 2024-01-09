#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int n,a[maxn];
int choose[maxn],vis[maxn],cnt=0;

string s;
char s2[10000]; //s2[i] 第i个小朋友手里是什么


void dfs(int d){
    int i;
    if( d == n+1){
        for(int i=1;i<=n;++i) std::cout << s2[i];
        std::cout << std::endl;
    }
    for(i=1;i<=n;++i){
        if( choose[i] == 1) continue;
        s2[d] = s[i-1];
        choose[i] = 1;
        dfs(d+1);
        choose[i] = 0;
     }
}

int main(){
    cin >> s;
    n = s.length();
    dfs(1);
    return 0;
}
