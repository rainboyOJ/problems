#include <cstdio>

int main(){
    int n;
    int sum = 0;
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( sum < t)
            sum = t;
    }
    printf("%d\n",sum);
    return 0;
}
