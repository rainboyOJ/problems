#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int N=1e5;
int Rand()
{
	int x=rand();
	return x*rand()+rand();
}
int main()
{
	freopen("data10.in","w",stdout);
	srand(time(0));
	printf("%d\n",N);
	for (int i=1; i<=N; ++i) printf("%d %d\n",Rand()%(N*2),Rand()%N);
}

