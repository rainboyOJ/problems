#include <cstdio>

int  main(){
	long long n;
	scanf("%lld",&n);
	while( n != 1) {
		long long  ans;
		if( n % 2 == 1){
			ans = n*3+1;
			printf("%lld*3+1=%lld\n",n,ans);
		}
		else {
			ans =n /2;
			printf("%lld/2=%lld\n",n,ans);
		}
		n = ans;
	}
	printf("End");
	return 0;
}