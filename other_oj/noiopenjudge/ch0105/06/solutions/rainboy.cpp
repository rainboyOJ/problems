#include <cstdio>

int main(){
    int n;
    int sum = 0;
    int min = 99999999;
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( sum < t)
            sum = t;
        if( min > t)
            min  =t;
    }
    printf("%d\n",sum-min);
    return 0;
}
