#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int n=5;
int Rand()
{
	int x=rand();
	return x*rand()+rand();
}
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	printf("%d\n",n);
	for (int i=1; i<=n; ++i) printf("%d ",rand()%10);
}
