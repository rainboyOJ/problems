//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-17 15:39:46
// 注意: 这个代码只算出来了结果值,没有输出最后排序的诗
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5;
typedef  long long ll;
int a[maxn];
string sentence[maxn];
int n,L,P;
int len[maxn];
ll f[maxn];
ll pre[maxn]; //前缀和 

const ll hard = 1e18;



ll _pow(ll a) {
    if( a < 0) a = -a;
    ll ret = 1;
    for(int i = 1;i <= P ;++i ) // i: 1->P
    {
        ret *= a;
    }
    return ret;
}

ll w(int i,int j) {
    ll a = pre[j] - pre[i-1];
    ll len = j - i;
    return _pow(a+len - L);
}

int main (int argc, char *argv[]) {
    int T;
    cin >> T;
    while( T-- ) {
        std::cin >> n >> L >> P;
        std::getline(std::cin,sentence[0]);
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            std::getline(std::cin,sentence[i]);
            // std::cout << sentence[i] << "\n";
            len[i] = sentence[i].length();
            pre[i] = pre[i-1];
            pre[i] += len[i];
        }
        ll ans = 0x7f7f7f7f7f7f7f7f;
        // memset(f,0,sizeof(f));
        f[0] = 0;
        for(int i = 1;i<=n;i++) { // 枚举前i个元素在一起
            f[i] = 0x7f7f7f7f7f7f7f7f;
            for(int j = 1;j<= i;j++) { //枚举后面的长度
                ll t= f[j-1] + w(j,i);
                if( f[i] > t )
                    f[i] = t;
            }
            // std::cout << i << " " << f[i] << "\n";
        }
        if( f[n] > hard)
            cout << "Too hard to arrange" <<endl;
        else
            std::cout << f[n] << "\n";
    }

    return 0;
}
