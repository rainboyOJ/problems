#include <cstdio>
#include <algorithm>
using namespace std;

int n,t;
int a[1000];
int cnt = 0;

int main(){
	scanf("%d",&n);
	int i;
	for(i=1;i<=n;i++){
		scanf("%d",&t);
		if( t % 2 == 1){
			cnt++;
			a[cnt] = t;
		}
	}
	sort(a+1,a+cnt+1);
	printf("%d",a[1]);
	for(i=2;i<=cnt;i++)
		printf(",%d",a[i]);
	

	return 0;
}