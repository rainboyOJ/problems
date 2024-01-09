#include <cstdio>

struct ren {
	char name[100];
	int c;
};
ren a[20];
int n;
int main(){
	scanf("%d",&n);
	int i,j;
	for(i = 1;i<=n;i++){
		scanf("%s",a[i].name);
		scanf("%d",&a[i].c);
	}
	for(i=1;i<=n-1;i++)
		for(j=1;j<=n-i;j++){
			if( a[j].c > a[j+1].c){
				ren t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	for(i=n;i>=1;i--){
		printf("%s %d\n",a[i].name,a[i].c);
	}
	return 0;
}