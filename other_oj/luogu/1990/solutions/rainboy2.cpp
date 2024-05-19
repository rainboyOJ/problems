#include <iostream>
using namespace std;
const int maxn = 1e6+5;

int n;
int f[maxn];
int pre_sum[maxn];

int main() {
    std::cin >> n;
    f[0] = 1;
    f[1] = 1;
    pre_sum[0] = 1;
    pre_sum[1] = 2;

    for(int i =2;i<=n;i++) {
        f[i] = f[i-1] + f[i-2];
        f[i] %= 10000;
        if( i-3 >= 0)
        {
            f[i] += 2*pre_sum[i-3];
            f[i] %= 10000;
        }
        pre_sum[i] = pre_sum[i-1] +f[i];
        pre_sum[i] %= 10000;

        // cout << i << " " << f[i] <<endl;
    }
    cout << f[n] <<endl;
    

    return 0;
}

