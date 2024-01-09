#include <cstdio>

int main(){
    int n;
    int sum = 0;
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        sum +=t;
    }
    printf("%d ",sum);
    printf("%0.5lf",sum*1.0/n);
    return 0;
}
