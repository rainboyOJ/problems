#include <iostream>
using namespace std;

int n;
long long f[5005];

long long fib(int dep) {
    if( dep == 0 || dep == 1)
        return 1;
    if( f[dep] != 0) //记忆化
        return f[dep];
    f[dep] = fib(dep-1) + fib(dep-2);
    return f[dep];
}

int main() {
    std::cin >> n;
    cout << fib(n) << endl;
    return 0;
}
