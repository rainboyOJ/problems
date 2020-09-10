#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <set>
#include <ctime>
#include <algorithm>
#define min(a,b)	((a)<(b)?(a):(b))
#define max(a,b)	((a)>(b)?(a):(b))
#define abs(a)	((a)<0?-(a):(a))
#define inf 214748364
#define pi 3.141592653589793
#define maxn 100011
using namespace std;
typedef long long ll;
vector<int > e[maxn];
int fir[maxn],nex[maxn],t[maxn],typ[maxn],q[maxn];
int con;
int n,m,qa[maxn],qb[maxn];
int root;
int bin[maxn],res[maxn];
inline void addline(int st,int en,int inpq)
{
	nex[++con]=fir[st],fir[st]=con;
	t[con]=en,typ[con]=2,q[con]=inpq;
	nex[++con]=fir[en],fir[en]=con;
	t[con]=st,typ[con]=1,q[con]=inpq;
}
inline void dfs(int p)
{
	bin[p]=1;
	for(int i=fir[p];i;i=nex[i])
	if(bin[t[i]])
		res[q[i]]=typ[i];
	for(vector<int >::iterator i=e[p].begin();i!=e[p].end();++i)
		dfs(*i);
	bin[p]=0;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int st,en;
		scanf("%d%d",&st,&en);
		if(en==-1)
			root=st;else
			e[en].push_back(st);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&qa[i],&qb[i]);
		addline(qa[i],qb[i],i);
	}
	dfs(root);
	for(int i=1;i<=m;++i)
		printf("%d\n",res[i]);
	return 0;
}

