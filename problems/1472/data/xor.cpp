#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int u=100010;
int val[u*32],a[u*32][2],f[u];
int n,tot,i,ans,x,y,z;
inline int getint()
{
	char c;
	while ((c = getchar()) < '0' || c > '9');
	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}
void ins(int x,int y,int temp)
{
	if(y<0) {val[x]=temp; return;}
	int z=(temp>>y)&1;
	if(!a[x][z]) a[x][z]=++tot;
	ins(a[x][z],y-1,temp);
} 

int get(int x,int y,int temp)
{
	if(y<0) return val[x];
	int z=(temp>>y)&1;
	if(a[x][z^1]) return get(a[x][z^1],y-1,temp);
	else return get(a[x][z],y-1,temp);
}

int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	n=getint();
	tot=1;
	for(i=1;i<=n;i++)
	{
		f[i]=getint();
		if (i>1) ans=max(ans,f[i]^get(1,30,f[i]));
		ins(1,30,f[i]);
	}
	cout<<ans<<endl;
	return 0;
}
