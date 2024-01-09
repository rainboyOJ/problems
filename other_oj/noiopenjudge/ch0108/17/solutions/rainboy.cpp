#include <cstdio>

int n,m;
char grass[200][200];
int cnt=0;
int fx[4][2] = { 0,-1, -1,0, 1,0, 0,1 };

void init(){
    scanf("%d%d",&n,&m);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%s",grass[i]+1);
    }
}
int main(){
    init();
    int i,j,k;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            if( grass[i][j] == '#'){
                cnt++;
                for (k=0;k<=3;k++){
                    grass[ i+ fx[k][0] ][j + fx[k][1] ] = '.';
                }
            }
        }
    }
    printf("%d\n",cnt);
    return 0;
}
