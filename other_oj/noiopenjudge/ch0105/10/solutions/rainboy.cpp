#include <cstdio>

int main(){
    int m,n;
    scanf("%d%d",&m,&n);
    int i,sum = 0;
    for(i=m;i<=n;i++){
        if( i % 17 == 0)
            sum += i;
    }
    printf("%d\n",sum);
    return 0;
}

