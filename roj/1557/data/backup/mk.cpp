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
#include "windows.h"
#define min(a,b)	((a)<(b)?(a):(b))
#define max(a,b)	((a)>(b)?(a):(b))
#define abs(a)	((a)<0?-(a):(a))
#define inf 214748364
#define pi 3.141592653589793
using namespace std;
typedef long long ll;
#define maxn 2000001
bool vis[maxn];
int no[maxn],noo[maxn];
int fa[maxn];
int n,m,lim;
int qn=0,q[maxn];
int main(int c,char *s[])
{
	Sleep(1000);
	srand(time(0));
//	srand(0);
	freopen("tree.in","w",stdout);
	if(s[1][0]=='0')
		n=10,m=10,lim=10;else
	if(s[1][0]=='1')
		n=10,m=10,lim=20;else
	if(s[1][0]=='2')
		n=1000,m=1000,lim=2000;
	else
		n=40000,m=40000,lim=40000;
	if('6'<=s[1][0]&&s[1][0]<='9')
	{
		printf("%d\n",n);
		printf("1 -1\n");
		for(int i=2;i<=n;++i)
			printf("%d %d\n",i,i-1);
		printf("%d\n",m);
		if(s[1][0]=='9')
		{
			for(int i=1;i<=m;++i)
				printf("1 %d\n",n);
		}else
		{
			for(int l=1,r=n;l<=n;++l,--r)
				printf("%d %d\n",l,r);
		}
		return 0;
	}
	fa[1]=-1;
	for(int i=2;i<=n;++i)
		fa[i]=rand()%(i-1)+1;
	for(int i=1;i<=n;++i)
		noo[i]=i;
	if(n!=lim)
	{
		for(int i=1;i<=n;++i)
		{
			no[i]=rand()%lim+1;
			while(vis[no[i]])
				no[i]=rand()%lim+1;
			vis[no[i]]=1;
		}
	}else
	{
		for(int i=1;i<=n;++i)
			no[i]=i;
	}
	
	for(int i=1;i<=n;++i)
	{
		swap(noo[rand()%n+1],noo[rand()%n+1]);
		if(n==lim)
			swap(no[rand()%n+1],no[rand()%n+1]);
	}
	printf("%d\n",n);
	for(int i=1;i<=n;++i)
	{
		int p=noo[i];
		if(fa[p]==-1)
			printf("%d -1\n",no[p]);
		else
			printf("%d %d\n",no[p],no[fa[p]]);
	}
	printf("%d\n",m);
	for(int i=1;i<=m;++i)
	{
		int p=rand()%n+1,qq=rand()%n+1;
		while(p==qq)
			p=rand()%n+1,qq=rand()%n+1;
		int typ=rand()%3;
		if(typ==0)
			printf("%d %d\n",no[qq],no[p]);
		else
		{
			int a=rand()%n+1;
			int aa=a;
			qn=0;
			while(fa[a]!=-1)
				q[++qn]=a=fa[a];
			if(!qn)
				printf("%d %d\n",no[p],no[qq]);
			else
			{
				if(rand()%2)
					printf("%d %d\n",no[aa],no[q[rand()%qn+1]]);
				else
					printf("%d %d\n",no[q[rand()%qn+1]],no[aa]);
			}
		}
	}
	return 0;
}

