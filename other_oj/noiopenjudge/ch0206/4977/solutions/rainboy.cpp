/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 03日 星期四 14:19:40 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
int n,m;
int f1[maxn]; 
int a[maxn];

int main() {
    int t;
    cin>>t;
    while (t--) {
        std::cin >> n;
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            cin >> a[i];
        }
        int ans = 0;
        //从左向右
        for(int i =1;i<=n;i++) {
            f1[i] = 1;
            for(int j =1;j<i;j++) {
                if( a[j] > a[i] && f1[j] + 1 > f1[i])
                {
                    f1[i] = f1[j]+1;
                    ans = max(ans,f1[i]);
                }
            }
        }
        //从右向左
        for(int i =n;i>=1;i--){
            f1[i] = 1;
            for(int j =n;j>i;j--){
                if( a[j] > a[i] && f1[j] + 1 > f1[i])
                {
                    f1[i] = f1[j]+1;
                    ans = max(ans,f1[i]);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
