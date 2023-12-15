#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1000500;
struct Edge
{
	int a,b;
}edge[N];
int last[N];
int tot[N];
bool inva[N];
int n,m;
bool cmp(Edge x,Edge y)
{
	if(x.a<y.a)	return 1;
	if(x.a>y.a)	return 0;
	return (x.b<y.b);
}
int main()
{
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		edge[i].a=a;
		edge[i].b=b;
	}
	sort(edge+1,edge+m+1,cmp);
	int cc=0;
	for(i=1;i<=m;i++)
	{
		cc++;
		edge[cc]=edge[i];
		while(i<m && edge[i].a==edge[i+1].a && edge[i].b==edge[i+1].b)
			i++;
	}
	m=cc;
	for(i=1;i<=m;i++)
	{
		tot[edge[i].b]++;
		last[edge[i].b]=max(last[edge[i].b],edge[i].a);
	}
	for(i=n;i>=1;i--)
	{
		if(last[i])
		{
			if(tot[i]>tot[last[i]])
				inva[last[i]]=1;
		}
	}
	int ans=0;
	for(i=1;i<=n;i++)
	{
		if(!inva[i])
			ans++;
	}
	printf("%d\n",ans);
	return 0;
}
