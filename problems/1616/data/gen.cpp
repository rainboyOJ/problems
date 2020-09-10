#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int N=1e9;
int Rand()
{
	int x=rand();
	return (x*rand()+rand())%N+1;
}
int main()
{
	freopen("data10.in","w",stdout);
	srand(time(0));
	printf("%d %d %d",Rand(),Rand(),Rand());
}

