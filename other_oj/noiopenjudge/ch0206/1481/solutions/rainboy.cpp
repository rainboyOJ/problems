/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 08月 01日 星期日 19:02:32 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50000+100,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

ll a[maxn];
ll lf[maxn],rf[maxn]; //left 以i为结尾的连续最大和
ll lm[maxn],rm[maxn]; //left 1->i 之间的最大 lf 值

void init(){
    scanf("%d",&n);
    lf[0] = rf[n+1] = -9999999;
    lm[0] = rm[n+1] = -9999999;
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=1;i<=n;++i){
        lf[i] = a[i];
        if( lf[i-1] > 0)
            lf[i] += lf[i-1];
        lm[i] = max(lm[i-1],lf[i]);
    }
    for(int i=n;i>=1;--i){
        rf[i] = a[i];
        if( rf[i+1] > 0)
            rf[i] += rf[i+1];
        rm[i] = max(rm[i+1],rf[i]);
    }
    ll ans = -999999999;
    //枚举 分界线
    for(int i=1;i<=n-1;++i){
        ans = max(ans,lm[i]+rm[i+1]);
        //printf("%d: %lld\n",i,lm[i]+rm[i+1]);
    }
    printf("%lld\n",ans);
}

int main(){
    int T;
    scanf("%d",&T);
    while ( T-- ) {
        init();
    }
    return 0;
}
