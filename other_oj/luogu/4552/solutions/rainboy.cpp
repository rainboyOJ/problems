#include <iostream>
using  namespace std;
typedef  long long ll;

ll sub[100000+5];
ll n;

ll _abs(ll a){
    return a <0 ? -a : a;
}

int main () {
    cin >> n;
    ll pre = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        ll t;
        cin >>t;
        sub[i] = t-pre;
        pre =t;
    }

    ll neg_sum = 0;
    ll sum = 0;
    for(int i = 2;i <= n ;++i ) // i: 1->n
    {
        if( sub[i] < 0)
            neg_sum += sub[i];
        else
            sum += sub[i];
    }

    cout << std::max(_abs(neg_sum),sum) << "\n";
    cout << _abs(_abs(neg_sum)-sum) + 1 << "\n";


    return 0;
}

