#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
ll n;
ll cnt;
ll len;
char a[1000005];

void dfs(ll l,ll n) {
    if( l <=  len ) {
        cout << a[n];
        return;
    }
    if( n > l/2) {
        if( n == l/2 +1)
            n = l/2;
        else
            n = n-l/2- 1;
    }
    dfs(l/2 ,n);
}

int main () {
    cin >> a+1;
    cin >> n;
    len = strlen(a+1);
    ll t = len;
    while(t < n) {
        cnt++;
        t *= 2;
    }
    // cout << cnt;
    dfs(t,n);

    return 0;
}
