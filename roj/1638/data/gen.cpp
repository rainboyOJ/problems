#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int T=5,N=9e8;
int Rand()
{
	int x=rand();
	return (x*rand()+rand())%N+3;
}
int main()
{
	freopen("data10.in","w",stdout);
	srand(time(0));
	printf("%d\n",T);
	while (T--){
		int n=Rand(),d=Rand()%(n-1)+1,x=Rand()%n,y=Rand()%n;
		printf("%d %d %d %d\n",n,d,x,y);
	}
}

