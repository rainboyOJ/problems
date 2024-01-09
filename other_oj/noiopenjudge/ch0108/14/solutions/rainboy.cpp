#include <cstdio>
#include <cstring>
int n,m;
int fx[8][2] = {
    1,0,
    0,1,
    -1,0,
    0,-1,
    1,1,
    1,-1,
    -1,-1,
    -1,1
};
char str[200][200];

void init(){
    scanf("%d%d",&n,&m);
    int i;
    for (i=1;i<=n;i++){
        scanf("%s",str[i]+1);
    }
}

int calc(int x,int y){
     int i;
     int sum = 0;
     for (i=0;i<8;i++){
         int nx = x + fx[i][0];
         int ny = y + fx[i][1];
         if( str[nx][ny] == '*')
             sum += 1;
     }
     return sum;
}
int main(){
    init();
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            if( str[i][j] == '*') continue;
            str[i][j] = calc(i, j) +'0';
        }
    }
    for (i=1;i<=n;i++){
        printf("%s\n",str[i]+1);
    }
    return 0;
}
