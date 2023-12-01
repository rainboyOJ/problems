#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int P = 1e9 + 7;
const int N = 1e6 + 50;
int n, m, mx, mi, cnt;
int a[N], fac[N], inv[N];

int read() {
	int x = 0, p = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') p = -1;
	for (; isdigit(ch); ch = getchar())
		x = x * 10 + ch - '0';
	return x * p;
}

struct Bit {
    int n; ll a[N];
    
    void init(int _n) {
        n = _n;
        memset(a, 0, sizeof a);
    }
    
    int lowbit(int x) {
        return x & -x;
    }
    
    void update(int pos, ll val) {
        for (int i = pos; i <= n; i += lowbit(i))
            a[i] += val;
    }
    
    ll query(int pos) {
        ll ret = 0;
        for (int i = pos; i; i -= lowbit(i))
            ret += a[i];
        return ret;
    }
};

struct Bit2 {
    Bit a, b;
    
    void init(int _n) {
        a.init(_n);
        b.init(_n);
    }
    
    void update(int pos, ll val) {
        a.update(pos, val);
        b.update(pos, val * pos);
    }
    
    void update(int l, int r, ll val) {
        update(l, val); update(r + 1, -val);
    }
    
    ll query(int pos) {
        return a.query(pos) * (pos + 1) - b.query(pos);
    }
    
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit, bit1, bit2;

int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
    n = read(); m = read();
    fac[1] = inv[1] = 1;
    for (int i = 2; i <= n * 2; i++) {
        fac[i] = 1LL * fac[i - 1] * i % P;
        inv[i] = 1LL * (P - P / i) * inv[P % i] % P;
    }
    for (int i = 2; i <= n * 2; i++)
        inv[i] = 1LL  * inv[i - 1] * inv[i] % P;
    bit.init(n * 2); bit1.init(n); bit2.init(n);
    for (int i = 1; i <= n * 2; i++) {
        a[i] = read();
        int t = (i + 1) / 2;
        bit.update(i, i, a[i]);
        if (i & 1) bit1.update(t, t, a[i]);
        else bit2.update(t, t, a[i]);
    }
    for (int opt, l, r, k, i = 1; i <= m; i++) {
        opt = read(); l = read(); r = read();
        if (!opt) {
            k = read();
            bit.update(l, r, k);
            int t1 = (l + 1) / 2;
            int t2 = (r + 1) / 2;
            if (l & 1) {
                bit1.update(t1, t2, k);
                bit2.update(t1, t2, k);
            } else {
                bit1.update(t1 + 1, t2, k);
                bit2.update(t1, t2 - 1, k);
            }
        }
        if (opt) {
            int t = (r - l + 1) / 2, t1 = (l + 1) / 2, t2 = (r + 1) / 2;
            mx = (bit.query(r - t + 1, r) - bit.query(l, l + t - 1)) % P;
            if (l & 1) mi = (bit2.query(t1, t2) - bit1.query(t1, t2)) % P;
            else mi = (bit1.query(t1 + 1, t2) - bit2.query(t1, t2 - 1)) % P;
            cnt = 1LL * fac[t * 2] * inv[t + 1] % P * inv[t] % P;
            printf("%d %d %d\n", mx, mi, cnt);
        }
    }
    return 0;
}

