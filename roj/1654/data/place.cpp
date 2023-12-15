#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
using namespace std;
const int MXN = 2002;
int a, b, c, d, k;
long long C[MXN][MXN];
long long P[MXN][MXN];
long long ans;
long long calc(int n, int m, int k) {
    //if (k > n || k > m) return 0;
    return C[n][k] * P[m][k] % 100003;
}
int main() {
    freopen("10.in", "r", stdin);
    freopen("10.out", "w", stdout);
    memset(C, 0, sizeof(C));
    memset(P, 0, sizeof(P));
    for(int i = 0; i < MXN; i++)
        for(int j = 0; j <= i; j++) {
            if(j == 0 || j == i) {
                C[i][j] = 1;
            } else {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % 100003;
            }
        }
        
    for(int i = 0; i < MXN; i++) {
        P[i][0] = 1;
        for(int j = 1; j <= i; j++)
            P[i][j] = P[i][j - 1] * (i - j + 1) % 100003;
    }
    cin >> a >> b >> c >> d >> k;
    ans = 0;
    for (int i = 0; i <= min(min(a, b), k); i++)
        ans += calc(a, b, i) * calc(a + c - i, d, k - i) % 100003;
    ans %= 100003;
    cout << ans << endl;
}
