#include <iostream>
#include <iomanip>
using namespace std;
const int maxn = 1e6+5;

typedef long long ll;
const int mod = 100000;

ll f[maxn];
ll s[maxn];

int main (int argc, char *argv[]) {
    int n;
    cin >> n;
    f[1] = 1;
    s[1] = 1;
    for(int i =2;i<=n;i++) {
        f[i] += s[i/2];
        f[i]+=1;
        f[i] %= mod;
        s[i] = s[i-1]  + f[i];
        s[i] %= mod;
    }
    cout << f[n] << endl;
    return 0;
}

