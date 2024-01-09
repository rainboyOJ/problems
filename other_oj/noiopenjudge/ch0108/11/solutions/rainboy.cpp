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
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
             b[j][n-i+1]= a[i][j];
        }
    }
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }

    return 0;
}
