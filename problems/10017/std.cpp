#include <iostream>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;
#define ll long long
ll F[maxn], Finv[maxn], inv[maxn];
void init(){
    inv[1] = 1;
    for(int i = 2; i < maxn; i ++){
        inv[i] =(mod - mod / i) * 1ll * inv[mod % i] % mod;
    }
    F[0] = Finv[0] = 1;
    for(int i = 1; i < maxn; i ++){
        F[i] = F[i-1] * 1ll * i % mod;
        Finv[i] = Finv[i-1] * 1ll * inv[i] % mod;
    }
}
ll comb(int n, int m){
    if(m < 0 || m > n) return 0;
    return F[n] * 1ll * Finv[n - m] % mod * Finv[m] % mod;
}
ll cal(int n, int m){
	if(n & 1 && !(m & 1))	return 0;
	m = (m + 1) / 2;
	n = (n + 1) / 2;
	ll now = comb(n - 1, m - 1);
	if(m % 2 == 0)
		return now * -1;
	return now;
}
int main(){
	init();
	int n;
	cin >> n;
	ll a, ans = 0;
	for(int i = 1; i <= n; i++){
		cin >> a;
		ans = (ans + a * cal(n, i)) % mod;
	}
	cout << (ans + mod) % mod<< endl;
}

