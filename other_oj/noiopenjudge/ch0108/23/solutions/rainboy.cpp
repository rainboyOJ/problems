#include <cstdio>
int n,m,a[1010][1010];
void init(){
    scanf("%d%d",&n,&m);
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
}

int main(){
    init();
    int i,j;
    int r1=1,r2=n,c1=1,c2=m;
    while( r1 <= r2 && c1 <= c2){

        for(j=c1;j<=c2;j++)
            printf("%d\n",a[r1][j]);

        for(i=r1+1;i<=r2;i++)
            printf("%d\n",a[i][c2]);

        if( r1 != r2)
            for(j = c2-1;j>=c1;j--)
                printf("%d\n",a[r2][j]);

        if(c1!=c2)
            for(int i=r2-1;i>r1;i--)
                printf("%d\n",a[i][c1]);
        r1++;
        r2--;
        c1++;
        c2--;
    }
    return 0;
}
