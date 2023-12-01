#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 105;
int n,m;
long double p;
long double val[N];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	double t;
	scanf("%d%d%lf",&n,&m,&t);
	p=t;
	if(p<0.5)
	{
		swap(n,m);
		p=1-p;
	}
	val[0]=1.0;
	int i;
	long double v=(1-p)/p;
	for(i=1;i<=n+m;i++)
		val[i]=val[i-1]*v;
	long double sum=0.0;
	for(i=0;i<=n+m;i++)
		sum+=val[i];
	long double ans=sum;
	ans/=val[n];
	double ansx=ans;
	printf("%.10f\n",ansx);
	return 0;
}
