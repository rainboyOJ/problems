#include <iostream>
using namespace std;
const int maxn = 1e6+5;

int n;
int f[maxn];

int main() {
    std::cin >> n;
    f[0] = 1;
    f[1] = 1;

    for(int i =2;i<=n;i++) {
        f[i] = f[i-1] + f[i-2];
        f[i] %= 10000;
        for(int j = i-3 ;j>=0;j--)
        {
            f[i] += 2 * f[j];
            f[i] %= 10000;
        }
        // cout << i << " " << f[i] <<endl;
    }
    cout << f[n] <<endl;
    

    return 0;
}

