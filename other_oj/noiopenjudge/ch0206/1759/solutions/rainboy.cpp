/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 03日 星期四 14:19:40 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
int f[maxn];
vector<int> v;
int ans = 0;
int main(int argc,char * argv[]){
    std::cin >> n;
    v.push_back(0); //占位置
    for(int i=1;i<=n;++i){
        f[i] = 1;
        int t;
        std::cin >> t;
        v.push_back(t);
        for(int j = 1;j < i;j++){
            if( v[j] < t && f[j]+1 > f[i] )
                f[i] = f[j]+1;
        }
        ans = max(ans,f[i]);
    }
    std::cout << ans << std::endl;
    return 0;
}
