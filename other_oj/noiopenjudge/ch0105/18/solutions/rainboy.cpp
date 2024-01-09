#include <cstdio>

int main(){
    int n;
    int a,b;
    scanf("%d",&n);
    scanf("%d%d",&a,&b);
    double rate_1 = b*1.0/a;
    int i;
    for (i=1;i<n;i++){
        scanf("%d %d",&a,&b);
        double rate_2 = b*1.0 / a;
        if( rate_1 - rate_2 > 0.05)
            printf("worse\n");
        else if ( rate_2 - rate_1 > 0.05)
            printf("better\n");
        else
            printf("same\n");
    }
    return 0;
}

