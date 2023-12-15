#include<cstdio>
using namespace std;
int a,b,m;
int Ksm(int x,int d)
{
	int res=1;
	for (; d; d/=2,x=1ll*x*x%m)
	if (d%2) res=1ll*res*x%m;
	return res;
}
int main()
{
	freopen("data10.in","r",stdin);
	freopen("data10.out","w",stdout);
	scanf("%d%d%d",&a,&b,&m);
	printf("%d",Ksm(a,b));
}
