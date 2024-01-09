#include <cstdio>
int n;
int cnt = 0;
int a[1200] = {0};
int main(){
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( a[t] == 0){
            cnt++;
            a[t] = 1;
        }
    }

    printf("%d\n",cnt);
    for (i=1;i<=1000;i++){
        if( a[i] == 1)
            printf("%d ",i);
    }
    return 0;
}
