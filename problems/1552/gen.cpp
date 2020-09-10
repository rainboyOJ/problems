#include <cstdio>  
#include <algorithm> 
#include <vector>  
#include <ctime>  
#include <cstdlib>  
using namespace std;
int n=1e5,m=1e5;
int Rand()
{
	int x=rand();
	return x*rand()+rand();
}
int main()
{
	freopen("test9.in","w",stdout);
	srand(time(0));
	printf("%d\n",n);
	for (int i=2; i<=n; ++i) printf("%d %d\n",i-1,i);
	printf("%d\n",m);
	for (int i=1; i<=m; ++i) {
		int l=Rand()%n+1,r=Rand()%n+1;
		printf("%d %d\n",l,r);
	}
}
