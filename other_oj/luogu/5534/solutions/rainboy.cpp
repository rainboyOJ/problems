#include <iostream>
using namespace std;

typedef long long ll;
ll a,b,n;
ll d; //差值
int main() {
    std::cin >> a >> b >> n;
    d = b - a;
    ll sum = a+b;
    for(int i = 3;i<= n;i++) {
        b += d; //计算现在的这个数
        sum += b;
    }
    cout << sum << endl;

    return 0;
}
