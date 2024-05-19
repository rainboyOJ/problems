//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-17 14:54:21
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;

typedef  long long ll;

ll a,b,mod;

//口决: 是1就乘,base增增
template<typename  T =long long>
T quick_pow(T base, T b ,T mod) {
    T ans = 1 % mod;
    for(; b; b>>=1)
    {
        if(b & 1)
            ans = ans * base % mod;
        base = base * base % mod;
    }
    return ans;
}



int main (int argc, char *argv[]) {
    cin >> a >> b>> mod;
    cout  << quick_pow<ll>(a,b,mod) << endl;

    return 0;
}
