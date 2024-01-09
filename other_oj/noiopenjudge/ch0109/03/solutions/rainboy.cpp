#include <cstdio>

int main(){
    int a,b;
    
    int c =0;
    int max = -1;
    int i;
    for(i=1;i<=7;i++){
        scanf("%d%d",&a,&b);

        if( a+b > 8){
            if( a+b -8 > max){
                max= a+b-8;
                c=i;
            }
        }
    }
	printf("%d",c);
    return 0;
}