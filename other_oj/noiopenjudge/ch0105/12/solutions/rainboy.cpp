#include <cstdio>

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int i,a,cnt=0;
    for (i=1;i<=n;i++){
        scanf("%d",&a);
        if ( a== m)
            cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
