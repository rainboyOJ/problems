/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 13日 星期日 08:28:33 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */
int a[1005];
long long f[1005];
int main(int argc,char * argv[]){
    std::cin >> n;
    for(int i=1;i<=n;++i){
        std::cin >> a[i];
        f[i] = a[i];
    }
    
    int ans = a[1];
    for(int i=2;i<=n;++i){
        for(int j=1;j<=i-1;++j){
            if(a[j] < a[i] && f[i] < f[j]+a[i]){
                f[i] = f[j]+a[i];
            }
        }
        ans = max<ll>(ans,f[i]);
        //std::cout << f[i] << ' ' ;
    }
    //std::cout  << std::endl;
    std::cout << ans << std::endl;

    return 0;
}
