#include <cstdio>

int main(){
    int k;
    int a=1,b=1,c;
    int i;
    scanf("%d",&k);
    if( k==1 || k == 2){
        printf("1");
        return 0;
    }

    for (i=3;i<=k;i++){
        c = a +b;
        a = b;
        b = c;
    }
    printf("%d\n",c);
    return 0;
}
