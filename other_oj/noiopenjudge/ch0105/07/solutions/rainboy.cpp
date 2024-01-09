#include <cstdio>

int main(){
    int n;
    int sum = 0;
    int i;
    int a=0,b=0,c=0;
    int t1,t2,t3;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        a += t1;
        b += t2;
        c += t3;
    }
    printf("%d %d %d %d\n",a,b,c,a+b+c);
    return 0;
}
