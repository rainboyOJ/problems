#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int P = 1e9 + 7;
const int N = 65;
const int M = 60;
ll l, r, k;
int ans;

struct Matrix {
	int a[N][N];
	
	void init(int x) {
		memset(a, 0, sizeof a);
		for (int i = 0; i < M; i++)
			a[i][i] = x;
	}
	
	Matrix operator * (const Matrix &t) const {
		Matrix ret;
		ret.init(0);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < M; j++)
				for (int k = 0; k < M; k++)
					ret.a[i][j] = (ret.a[i][j] + 1LL * a[i][k] * t.a[k][j]) % P;
		return ret;
	}
	
	Matrix operator *= (const Matrix &t) {
		return *this = *this * t;
	}
	
	Matrix operator ^ (ll t) {
		Matrix ret;
		ret.init(1);
		for (Matrix tmp = *this; t; tmp *= tmp, t >>= 1)
			if (t & 1) ret *= tmp;
		return ret;
	}
} f, g;

int main() {
	freopen("digit.in", "r", stdin);
	freopen("digit.out", "w", stdout);
	scanf("%I64d%I64d%I64d", &l, &r, &k);
	f.init(0);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++)
			f.a[j][i] = (k / M) % P;
		for (int j = 0; j < k % M; j++)
			f.a[(i + j) % M][i] = (f.a[(i + j) % M][i] + 1) % P;
	}
	g = f ^ r;
	for (int i = 0; i < M; i++)
		if (i % 4 == 0 || i % 5 == 0 || i % 6 == 0)
			ans = (ans + g.a[i][0]) % P;
	g = f ^ (l - 1);
	for (int i = 0; i < M; i++)
		if (i % 4 == 0 || i % 5 == 0 || i % 6 == 0)
			ans = (ans - g.a[i][0] + P) % P;
	printf("%d\n", ans);
	return 0;
}

