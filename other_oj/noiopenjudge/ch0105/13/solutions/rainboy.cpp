#include <cstdio>

int main(){
    int a,n;
    scanf("%d%d",&a,&n);
    int i;
    int ans = 1;
    for (i=1;i<=n;i++){
        ans = ans *a;
    }
    printf("%d\n",ans);
    return 0;
}
