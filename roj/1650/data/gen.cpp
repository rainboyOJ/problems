#include<cstdio>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
int pri[]={17,97,193,257,23068673,104857601,167772161,469762049,469762049,469762049};
int T=100,N=1e9;
int Rand()
{
	int x=rand();
	return (x*rand()+rand())%N+1;
}
int main()
{
	freopen("data10.in","w",stdout);
	srand(time(0));
	printf("%d\n",T);
	while (T--){
		int p=pri[rand()%10];
		int n=Rand(), m=rand()%min(10000,min(n,p-1))+1;
		printf("%d %d %d\n",n,m,p);
	}
//	printf("%d %d %d",Rand(),Rand(),Rand());
}

