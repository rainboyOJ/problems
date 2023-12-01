#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int M = 105;
const int N = 2e4 + 50;
ll m, ans, cnt, f[N];
int n, p[M][M];

struct Data {
	int x, y;
	
	Data(int _x = 0, int _y = 0): x(_x), y(_y) {}
	
	bool operator < (const Data &t) const {
		int flag = x * t.y - y * t.x;
		if (flag == 0) return x < t.x;
		return flag < 0;
	}
} a[M];

int main() {
	freopen("backpack.in", "r", stdin);
	freopen("backpack.out", "w", stdout);
	scanf("%d%I64d", &n, &m);
	for (int x, y; n--; ) {
		scanf("%d%d", &x, &y);
		p[x][y] = 1;
	}
	n = 0;
	for (int x = 1; x <= 100; x++) {
		for (int y = 100; y >= 1; y--) {
			if (p[x][y]) {
				a[++n] = Data(x, y);
				break;
			}
		}
	}
	for (int i = 2; i <= n; i++)
		if (a[i] < a[1]) swap(a[i], a[1]);
	cnt = m / a[1].x - 100;
	ans = cnt * a[1].y;
	m -= cnt * a[1].x;
	for (int i = 1; i <= n; i++)
		for (int j = a[i].x; j <= m; j++)
			f[j] = max(f[j], f[j - a[i].x] + a[i].y);
	printf("%I64d\n", ans + f[m]);
	return 0;
}

