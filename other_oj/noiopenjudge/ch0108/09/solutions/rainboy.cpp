#include <cstdio>

int n,m,k;
int a[200][200];
int b[200][200];
int c[200][200];
int main(){
    int i,j;
    scanf("%d%d%d",&n,&m,&k);
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for (i=1;i<=m;i++){
        for (j=1;j<=k;j++){
            scanf("%d",&b[i][j]);
        }
    }
    int x,y;
    for (i=1;i<=n;i++){
        for (j=1;j<=k;j++){
            for(x=1;x<=m;x++){
                c[i][j] += a[i][x]*b[x][j];
            }
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
