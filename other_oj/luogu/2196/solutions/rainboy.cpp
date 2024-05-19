/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 08月 05日 星期三 16:37:42 CST */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int n,m;
int a[30],f[30],pre[30];
int g[40][40];
// g[i][j]= 1 表示第i个 地窖和第j个地窖相连
//
int t[40],tcnt;


int main(){
    cin >> n;
    int i,j;
    for(i=1;i<=n;++i){
        cin >> a[i];
    }
    for(i=1;i<=n-1;++i){
        for(j=i+1;j<=n;j++)
            cin >> g[i][j];
    }
    f[1] = a[1];
    int ans = -1;
    int end;
    for(i=2;i<=n;i++){
        f[i] = a[i];
        for(j=1;j<i;j++){ //前面的地窖
            if( g[j][i]==1 ){
                if( f[i] < f[j]+a[i]){
                    f[i] = f[j]+a[i];
                    pre[i] = j;
                }
            }
        }
        if( ans < f[i]){
            ans = f[i];
            end = i;
        }
    }
    while( end !=0 ){
        t[++tcnt] = end;
        end = pre[end];
    }
    for( i =tcnt;i>=1;i--)
        cout << t[i] << " ";
    cout << endl;

    cout << ans;

    return 0;
}

