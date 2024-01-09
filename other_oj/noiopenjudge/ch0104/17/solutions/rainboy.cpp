#include <cstdio>
int main(){
	int a,b,c;
	scanf("%d",&a);
	if(  a % 4 == 0){
		if( a % 100 ==0 && a % 400 != 0 )
			printf("N");
		else
			printf("Y");
	}
	else
		printf("N");
	return 0;
}