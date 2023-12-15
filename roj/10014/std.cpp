#include<iostream> 
#include<queue> 
#include<cstring>
using namespace std;
#define int long long
queue<int>q;
int deg[100001],deg1[100001];
int to[200001],nex[200001],st[100001],cnt;
int to1[200001],nex1[200001],st1[100001],cnt1;
int n,m,v[100001],ts[100001],id[100001],cntw,tsw[100001];
int l[100001],lw[100001],maxn[100001],tag1[100001],tag2[100001],tag3[100001];
int ans1,l1,r1;
void addedge(int x,int y)
{
	to[++cnt]=y;
	nex[cnt]=st[x];
	st[x]=cnt;
	deg[y]++;
}
void addedge1(int x,int y)
{
	to1[++cnt1]=y;
	nex1[cnt1]=st1[x];
	st1[x]=cnt1;
	deg1[y]++;
}
void topo()
{
	for(int i=1;i<=n;i++)
	{
		if(!deg[i])q.push(i);
	}
	while(!q.empty())
	{
		int w=q.front();
		q.pop();
		ts[++cntw]=w;
		id[w]=cntw;
		for(int i=st[w];i;i=nex[i])
		{
			deg[to[i]]--;
			if(!deg[to[i]])q.push(to[i]);
		}
	}
}
void topow()
{
	cntw=0;
	for(int i=1;i<=n;i++)
	{
		if(!deg1[i])q.push(i);
	}
	while(!q.empty())
	{
		int w=q.front();
		q.pop();
		tsw[++cntw]=w;
		for(int i=st1[w];i;i=nex1[i])
		{
			deg1[to1[i]]--;
			if(!deg1[to1[i]])q.push(to1[i]);
		}
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>v[i];
		maxn[i]=-1e9;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		addedge(x,y);
		addedge1(y,x);
	}
	topo();
	for(int i=1;i<=n;i++)
	{
		int w=ts[i];
		if(v[w]>maxn[w])maxn[w]=v[w],l[w]=w,lw[w]=w;
		for(int i=st[w];i;i=nex[i])
		{
			if(maxn[to[i]]<v[to[i]]+maxn[w])
			{
				maxn[to[i]]=v[to[i]]+maxn[w];
				l[to[i]]=l[w];
				lw[to[i]]=w;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		//cout<<i<<' '<<maxn[i]<<' '<<ans1<<endl;
		if(maxn[i]>ans1)
		{
			ans1=maxn[i];
			l1=l[i];
			r1=i;
		}
	}
	if(ans1<=0)
	{
		cout<<"0 0";
		return 0;
	}
	cout<<ans1<<' ';
	int ww=r1;
	while(lw[ww]!=ww)
	{
		tag2[ww]=1;
		ww=lw[ww];
	}
	tag2[ww]=1;
	for(int i=st[r1];i;i=nex[i])
	{
		tag1[to[i]]=1;
	}
	for(int i=1;i<=n;i++)
	{
		maxn[i]=-1e9;
	}
	for(int i=1;i<=n;i++)
	{
		int w=ts[i];
		if(!tag1[w])continue;
		if(tag2[w])continue;
		if(v[w]>maxn[w])maxn[w]=v[w];
		for(int j=st[w];j;j=nex[j])
		{
			if(tag2[to[j]])continue;
			tag1[to[j]]=1;
			if(maxn[to[j]]<v[to[j]]+maxn[w])
			{
				maxn[to[j]]=v[to[j]]+maxn[w];
			}
		}
	}
	
//	for(int i=1;i<=n;i++)
//	{
//		maxn[i]=-1e9;
//		//cout<<id[i]<<endl;
//	}
//	for(int i=1;i<=n;i++)
//	{
//		int w=ts[i];
//		if(id[w]<=id[r1])continue;
//		if(v[w]>maxn[w])maxn[w]=v[w];
//		for(int i=st[w];i;i=nex[i])
//		{
//			if(maxn[to[i]]<v[to[i]]+maxn[w])
//			{
//				maxn[to[i]]=v[to[i]]+maxn[w];
//			}
//		}
//	}
    int maxw=0;
//	for(int i=1;i<=n;i++)
//	{
//		//cout<<maxn[i]<<endl;
//		maxw=max(maxw,maxn[i]);
//	}
//	for(int i=1;i<=n;i++)
//	{
//		maxn[i]=-1e9;
//		//cout<<id[i]<<endl;
//	}
//	for(int i=1;i<=n;i++)
//	{
//		int w=ts[i];
//		if(id[w]>=id[l1])continue;
//		if(v[w]>maxn[w])maxn[w]=v[w];
//		for(int i=st[w];i;i=nex[i])
//		{
//			if(id[to[i]]>=id[l1])continue;
//			if(maxn[to[i]]<v[to[i]]+maxn[w])
//			{
//				maxn[to[i]]=v[to[i]]+maxn[w];
//			}
//		}
//	}
	for(int i=1;i<=n;i++)
	{
//		cout<<tag3[i]<<endl;
		maxw=max(maxw,maxn[i]);
	}
	topow();
	for(int i=1;i<=n;i++)
	{
		maxn[i]=-1e9;
	}
	for(int x=1;x<=n;x++)
	{
		for(int i=st[x];i;i=nex[i])
		{
			if(to[i]==l1)tag3[x]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int w=tsw[i];
		if(!tag3[w])continue;
		if(tag2[w])continue;
		if(v[w]>maxn[w])maxn[w]=v[w];
		for(int j=st1[w];j;j=nex1[j])
		{
			if(tag2[to1[j]])continue;
			tag3[to1[j]]=1;
			if(maxn[to1[j]]<v[to1[j]]+maxn[w])
			{
				maxn[to1[j]]=v[to1[j]]+maxn[w];
			}
		}
	}
	for(int x=1;x<=n;x++)
	{
		maxw=max(maxw,maxn[x]);
//		cout<<maxn[x]<<endl;
	}
	cout<<maxw;
}
