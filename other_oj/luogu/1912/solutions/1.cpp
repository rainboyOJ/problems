//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-17 11:15:06
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
typedef  long long ll;
int a[maxn];
string sentence[maxn];
int n,L,P;
int len[maxn];


ll _pow(ll a) {
    if( a < 0) a = -a;
    ll ret = 1;
    for(int i = 1;i <= P ;++i ) // i: 1->P
    {
        ret *= a;
    }
    return ret;
}





int main (int argc, char *argv[]) {
    int T;
    cin >> T;
    std::cin >> n >> L >> P;
    std::getline(std::cin,sentence[0]);
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        // cin >> sentence[i];
        // cin.getline(sentence[i]);
        std::getline(std::cin,sentence[i]);
        std::cout << sentence[i] << "\n";
        len[i] = sentence[i].length();
    }
    ll ans = 0;
    std::cout << P << "\n";
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << len[i] - L << " ";
        cout << _pow(len[i] - L);
        cout << endl;
        ans += _pow(len[i] - L);
    }
    std::cout << ans << "\n";

    

    return 0;
}
