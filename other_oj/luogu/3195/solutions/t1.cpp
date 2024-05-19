//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-18 15:43:43
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
typedef  long long ll;
int n,L;
int a[maxn];
//前缀和
ll pre_sum[maxn];
ll f[maxn];
ll p[maxn];

ll val(int j,int i) {
    ll len = i-(j+1)+pre_sum[i] - pre_sum[j];
    len -=L;
    return len * len;
}

void init() {
    std::cin >> n >> L;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        pre_sum[i] = pre_sum[i-1];
        pre_sum[i] += a[i];
    }
}
void debug_f() {
    cout << "f[i]: ";
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << f[i] << " ";
    }
    cout << endl;

    cout << "p[i]: ";
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << p[i] << " ";
    }
    cout << endl;
}


int main (int argc, char *argv[]) {
    init();
    f[0] = 0;
    for(int i = 1;i <= n ;++i ) // 前i个元素
    {
        f[i] = 0x7f7f7f7f7f7f7f7f;
        for(int j = 0 ;j < i;j++)
        {
            ll t = f[j] + val(j,i);
            if( f[i] >= t) {
                f[i] = t;
                p[i] = j;
            }
        }
    }
    cout << f[n] << endl;

    #ifdef DEBUG
    debug_f();
    #endif


    return 0;
}
