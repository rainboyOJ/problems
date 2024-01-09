/**
 * f[i] 表示对于前i个店,且一定抢第i个店的最大值
 *
 * f[i] = max{f[j]} + a[i]   1<=j <=i-2 
 * O(n^2)
 * 所以超时
 *
 *
 * f[i] 表示对于前i个店最大值
 *
 * f[i] = max{f[i-2]+a[i],f[i-1]}
 *
 * O(n)
 * 边界 f[0] = 0
 * f[1] = a[1]
 *
 *
 */
/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 06日 星期日 11:09:48 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */
int f[maxn];

int main(int argc,char * argv[]){
    int T;
    std::cin >> T;
    while ( T-- ) {
        std::cin >> n;
        vector<int> v;
        v.push_back(0);

        int ans = -1;
        for(int i=1;i<=n;++i){
            int t;
            std::cin >> t;
            f[i]  = t;
            v.push_back(t);
        }

        ans = f[1];
        for(int i=2;i<=n;++i){
            f[i] = max(f[i-2]+v[i],f[i-1]);
            ans = max(f[i],ans);
        }
        std::cout << ans << std::endl;
    }
    return 0;
}

