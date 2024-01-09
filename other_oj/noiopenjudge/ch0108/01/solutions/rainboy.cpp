#include <cstdio>

int a[10][10];

int main(){
    int i,j;

    for (i=1;i<=5;i++){
        for (j=1;j<=5;j++){
            scanf("%d",&a[i][j]);
        }
    }
    int t1,t2;
    scanf("%d%d",&t1,&t2);
    for (i=1;i<=5;i++){
        int t;
        t = a[t1][i];
        a[t1][i] = a[t2][i];
        a[t2][i] = t;
    }

    for (i=1;i<=5;i++){
        for (j=1;j<=5;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
