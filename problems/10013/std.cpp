#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll a,m,b,n;
    while(cin>>a>>m>>b>>n) {
        ll x = a * (n * b) / __gcd(a, n * b);
        ll c1 = x / a;
        ll y = a * b / __gcd(a, b);
        ll c2 = x / y * (y / b - 1);
        cout << c1 + c2 << '\n';
    }
    return 0;
}
