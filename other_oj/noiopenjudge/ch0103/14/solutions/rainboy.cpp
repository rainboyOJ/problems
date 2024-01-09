#include <bits/stdc++.h>
using namespace std;
int main()
{
    int h,r;
    cin >> h >> r;
    double pi = 3.14159;
    double v = pi *r *r *h;
    int a = 20000 / v;
    if( a * v < 20000)
        a = a +1;
    cout << a;

    return 0;
}
