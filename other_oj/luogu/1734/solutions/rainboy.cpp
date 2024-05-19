/* author: Rainboy email: rainboylvx@qq.com  time: 2023年 03月 04日 星期六 09:22:38 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

//每个数的约数和
int sum[1005];

void init() {
    for(int i = 1 ;i<=1000;i++){
        int t = 0;
        for(int j=1;j<i;++j){
            if( i % j == 0 )
                t+=j;
        }
        sum[i] = t;
    }
    std::cin >> n;
    // for(int i=1;i<=11;++i){
    //     std::cout << i << " " << sum[i] << "\n" ;
    // }
}

int f[1005];

int main(int argc,char * argv[]){
    init();
    for(int i =1;i<=n;i++){
        for(int j = n;j>=i;j--){
            if( f[j] < f[j-i] + sum[i])
                f[j] = f[j-i] + sum[i];
        }
    }
    cout << f[n];
    return 0;
}
