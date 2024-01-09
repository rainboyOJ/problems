#include <cstdio>

int m,n;
int map[200][200];

int main(){
    int i,j;
    scanf("%d%d",&m,&n);
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&map[i][j]);
        }
    }
    int t,cnt=0;
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&t);
            if( map[i][j] == t)
                cnt++;
        }
    }

    double ans = cnt*100.0/(m*n);
    printf("%.2lf\n",ans);
    return 0;
}



