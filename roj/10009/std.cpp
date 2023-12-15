#include<bits/stdc++.h>
#define int long long
using namespace std;
int Read() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-')  f = -1; ch = getchar();}
    while(isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int tong[5005], ans;
int gcd(int a, int b) {return (a % b == 0) ? b : gcd(b, a % b);}
signed main() {
    int n = Read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            ++tong[gcd(i, j)];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            ans += tong[i] * gcd(i, j);
    cout << ans << endl;
    return 0;
}