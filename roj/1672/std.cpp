#include <cstdio>
#include <cstring>

int mi=0x7f7f7f7f,ma=-1;

int m,n;
int main(){

    int i,j;
    int t;
    scanf("%d%d",&m,&n);
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++){
            scanf("%d",&t);
            if( mi > t) mi = t;
            if( ma < t) ma = t;
        }
    printf("%d",ma-mi);
    return 0;
}
