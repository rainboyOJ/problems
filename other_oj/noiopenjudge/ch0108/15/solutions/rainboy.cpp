#include <cstdio>
#include <cstring>

int a[5][10][10];
int m,n;
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

void init(){
    scanf("%d%d",&m,&n);
    a[0][5][5] = m;
}

void g(int x,int i,int j,int cnt){
    int i1,i2;
    for (i1=0;i1<8;i1++){
        int nx = i +fx[i1][0];
        int ny = j +fx[i1][1];
        a[x][nx][ny] += cnt;
    }
    a[x][i][j] +=2*cnt;
}

void zeng(int x){
    int i,j;
    for (i=1;i<=9;i++){
        for (j=1;j<=9;j++){
            if( a[x-1][i][j]){
                g(x,i,j,a[x-1][i][j]);
            }
        }
    }
}
int main(){
    init();
    int i,j;
    for(i=1;i<=n;i++){
        zeng(i);
    }
    
    for (i=1;i<=9;i++){
        for (j=1;j<=9;j++){
            printf("%d ",a[n][i][j]);
        }
        printf("\n");
    }
    return 0;
}
