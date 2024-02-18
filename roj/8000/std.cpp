#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;

int n;

int sp,sn; //正数与负数的和

int main() {

    cin >> n;
    for(int i = 1;i <= n ;++i) // i: 1->n
    {
        int t;
        std::cin >> t;
        if( t > 0)
            sp += t;
        else
            sn += -t;
    }

    cout<< max(sp,sn);

    return 0;
}
