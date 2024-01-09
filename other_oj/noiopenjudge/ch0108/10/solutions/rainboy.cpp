#include <cstdio>

int n,m,k;
int a[200][200];
int b[200][200];
int c[200][200];
int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }

    for (j=1;j<=m;j++){
        for (i=1;i<=n;i++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
