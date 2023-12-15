#include<cstdio>
const int MXN = 100000;
int n, m;
int a[MXN];
int check () {
	int t, ans;
	t = 0;
	ans = 1;
	for (int i = 0; i < n; i++) {
		if (t + a[i] <= m)
			t += a[i];
		else {
			t = a[i];
			ans ++;
		}
	}
	return ans;
}
int main() {
	freopen("divide_a4.in", "r", stdin);
	freopen("divide_a4.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf ("%d", &a[i]);
	printf ("%d\n", check());
}
