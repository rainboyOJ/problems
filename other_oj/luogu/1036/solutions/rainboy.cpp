/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 08月 06日 星期四 16:54:43 CST */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int n,m;
int a[100];
int ans=0;

bool isPrime(int x){
    for(int i = 2;i<=sqrt(x);i++){ 
        if( x % i  == 0) return 0;
    }
    return 1;
}

void dfs(int dep,int sum,int pre){
    if( dep == m+1){
        //cout << endl;
        if( isPrime(sum) ) ans++;
        return;
    }
    for(int i = pre+1;i<=n;i++){
        //cout << a[i] << " ";
        dfs(dep+1,sum+a[i],i);
    }
    //if( pre+1 > n) cout << endl;
}

int main(){
    cin >> n >> m;
    int i,j;
    for(i=1;i<=n;++i){
        cin >> a[i];
    }
    dfs(1,0,0);
    cout << ans;

    return 0;
}

