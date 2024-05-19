#include <iostream>
using namespace std;
typedef  long long ll;
int n,r;

ll f(int n,int m) {
    if( m < 1 || n < m)
        return 0;
    if( n == m)
        return 1;
    return f(n-1,m-1) + m*f(n-1,m);
}

int main() {
    std::cin >> n >> r;
    ll ans = f(n,r);
    ll fac = 1;

    for(int i= 2; i<=r;i++)
        fac *= i;
    cout << ans * fac << endl;

    return 0;
}
