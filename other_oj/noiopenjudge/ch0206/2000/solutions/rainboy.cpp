/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 06日 星期日 09:02:14 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */
ll a[maxn],b[maxn];

ll f[505][505]; // f[i][j]
ll k[505][505]; // k[i][j] 结尾的数字

int main(int argc,char * argv[]){
    std::cin >> n;
    for(int i=1;i<=n;++i) std::cin >> a[i];
    std::cin >> m;
    for(int i=1;i<=m;++i) std::cin >> b[i];

    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if( a[i] == b[j] && a[i] > k[i-1][j-1]){
                f[i][j] = f[i-1][j-1] + 1;
                k[i][j] = a[i];
            }
            else if ( f[i-1][j] > f[i][j-1]){
                f[i][j] = f[i-1][j];
                k[i][j] = k[i-1][j];
                //f[i][j] = max(f[i-1][j],f[i][j-1]);
            }
            else {
                f[i][j] = f[i][j-1];
                k[i][j] = k[i][j-1];
            }
        }
    }

    std::cout << f[n][m] << std::endl;

    return 0;
}
