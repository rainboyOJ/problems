//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-17 15:23:56
#include <iostream>
using namespace std;
const int maxn = 1e6+5;
long long a,b,mod;

int z;

//口决: 是1就乘,base增增
template<typename  T>
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
    std::cin >> z;
    while(z--) {
        cin >> mod;
        int n;
        std::cin >> n;
        long long ans = 0;
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            std::cin >> a >> b;
            ans += quick_pow<long long>(a,b,mod);
            ans %= mod;
        }
        std::cout << ans << "\n";

    }
    
    return 0;
}
