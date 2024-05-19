#include <iostream>
using namespace std;

typedef long long ll;
ll a,b,n;
ll d; //差值
int main() {
    std::cin >> a >> b >> n;
    d = b - a;
    ll sum = n*a + n*(n-1)/2*d;
    cout << sum;

    return 0;
}
