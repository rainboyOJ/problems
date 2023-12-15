#include<iostream>  
#include<cstring>  
#include<cmath>  
#include<cstdio>  
#include<algorithm>  
using namespace std;  
typedef long long ll;  
const int N=2000005;
ll sum[N];
int p[N],d[N],que[N],ok[N];
int n;
inline int getint()
{
	char c;
	while ((c = getchar()) < '0' || c > '9');
	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}
void DP1()
{
	int q1=1,q2=0;
	for (int i=1; i<=n; ++i){
		while (q1<=q2 && sum[que[q2]]>=sum[i]) --q2;
		que[++q2]=i;
	}
	for (int i=n+1; i<=n*2; ++i){
		while (q1<=q2 && sum[que[q2]]>=sum[i]) --q2;
		que[++q2]=i;
		while (q1<=q2 && que[q1]<=i-n) ++q1;
		if (sum[que[q1]]>=sum[i-n]) ok[i-n]=1;	
	}
}
void DP2()
{
	int q1=1,q2=0;
	for (int i=n*2; i>n; --i){
		while (q1<=q2 && sum[que[q2]]>=sum[i]) --q2;
		que[++q2]=i;
	}
	for (int i=n; i; --i){
		while (q1<=q2 && sum[que[q2]]>=sum[i]) --q2;
		que[++q2]=i;
		while (q1<=q2 && que[q1]>=i+n) ++q1;
		if (sum[que[q1]]>=sum[i+n]) ok[i]=1;		
	}
}
int main()  
{  
	freopen("data10.in","r",stdin);
	freopen("data10.out","w",stdout);
 	n=getint();
 	for (int i=1; i<=n; ++i){
		p[i+n]=p[i]=getint(), d[i+n]=d[i]=getint();
		sum[i]=sum[i-1]+p[i-1]-d[i-1];
 	}
 	for (int i=n+1; i<=n*2; ++i)sum[i]=sum[i-1]+p[i-1]-d[i-1];
 //	for (int i=1; i<=n*2; ++i) printf("%lld ",sum[i]);
 //	printf("\n");
 	DP1();
 	for (int i=n*2; i; --i) sum[i]=sum[i+1]+p[i+1]-d[i];
 //	for (int i=1; i<=n*2; ++i) printf("%lld ",sum[i]);
 	DP2();
 	for (int i=1; i<=n; ++i) printf("%s\n",ok[i]?"TAK":"NIE");
}  
