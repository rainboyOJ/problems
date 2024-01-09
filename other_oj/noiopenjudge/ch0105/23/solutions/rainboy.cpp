#include <cstdio>
int main(){
	int m,n,a,i,cnt = 0;
	scanf("%d%d",&m,&n);
	for(i = 1;i<=n;i++){
		scanf("%d",&a);
		if( a > m )
			cnt++;
		else
			m = m - a;
	}
	printf("%d",cnt);
	return 0;
} 