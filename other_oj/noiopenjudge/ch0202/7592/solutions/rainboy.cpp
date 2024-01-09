#include <iostream>
using namespace std;

//gcd 求最大公约数的算法, 辗转相除法
int gcd(int a, int b)
{
    if( b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    long long a, b; // c++ long int -> int
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}