#include <cstdio>

int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	int i,sum = 0;
	for(i=m;i<=n;i++){
		if( i % 2 == 1)
			sum += i;
	}
	printf("%d",sum);
	return 0;
}