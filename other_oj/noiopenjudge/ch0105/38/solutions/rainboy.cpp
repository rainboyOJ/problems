#include <cstdio>
#include <cmath>

int main(){
    int t,n,i,c;
    t=1;
    while(t--){
        scanf("%d",&n);
        for (i=n;i>=1;i--){
            scanf("%d",&c);
            c *= i;
            printf("%d ",c);
        }
        scanf("%d",&c);
        if( n == 0){
            printf("0");
        }
        printf("\n");
    }
    return 0;
}
