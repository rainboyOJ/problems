#include <bits/stdc++.h>
using namespace std;
int main()
{
    double a,b;
    cin >> a >> b;
    int k = a / b;
    double r = a - k*b;
    cout << r << endl;

    return 0;
}
