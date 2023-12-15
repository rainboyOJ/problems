#include<bits/stdc++.h>
#define int long long
using namespace std;
int Read() {
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-')  f = -1; ch = getchar();}
	while(isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
	return x * f;
}
int first[200005], nxt[200005], to[200005], tot = 0;
void Add(int x, int y) {nxt[++tot] = first[x]; first[x] = tot; to[tot] = y;}
int fa[100005], b[100005], a[100005], d[100005], hh[100005], val[100005], HH[100005], Val[100005], tim[100005];
int vis[100005], sc[100005];
int ffa[500005];
int findfa(int x) {return (ffa[x] == x) ? x : ffa[x] = findfa(ffa[x]);}
void fight(int x) {
	//cout << x << endl;
	b[1] -= (a[x] - d[1]) * hh[x];
	d[1] += val[x];
}
void dfs(int u, int F) {
	fa[u] = F;
	for(int e = first[u]; e; e = nxt[e]) {
		int v = to[e];
		if(v == F)  continue;
		dfs(v, u);
	}
}
vector<int> Nxt[100005];
void Do(int u) {
	fight(u); sc[u] = 1;
	for(int i = 0; i < Nxt[u].size(); i++) {
		Do(Nxt[u][i]);
	}
}
signed main() {
	priority_queue<pair<double, int> > q;
	int n; scanf("%lld", &n);
	for(int i = 1; i < n; i++) {
		int x, y;
		scanf("%lld%lld", &x, &y);
		Add(x, y); Add(y, x);
	}
	dfs(1, 0);
    scanf("%lld%lld%lld", &b[1], &a[1], &d[1]);
	for(int i = 2; i <= n; i++) {
        scanf("%lld%lld%lld%lld", &b[i], &a[i], &d[i], &val[i]);
		hh[i] = b[i] / (a[1] - d[i]);  HH[i] = hh[i]; Val[i] = val[i];
		if(b[i] % (a[1] - d[i]) == 0)  --hh[i], --HH[i];
		q.push(make_pair(1.0 * val[i] / hh[i], i));
	}
	sc[1] = 1;
	for(int i = 1; i <= n; i++)  ffa[i] = i;
	while(!q.empty()) {
		int u = q.top().second; q.pop();
		if(vis[u])  continue;  vis[u] = 1;
		if(sc[fa[u]])  {Do(u); continue;}
		HH[findfa(fa[u])] += HH[u], Val[findfa(fa[u])] += Val[u];
		Nxt[ffa[fa[u]]].push_back(u);
		ffa[u] = ffa[fa[u]];
		q.push(make_pair(1.0 * Val[ffa[fa[u]]] / HH[ffa[fa[u]]], ffa[fa[u]]));
	}
	cout << b[1] << endl;
	return 0;
}