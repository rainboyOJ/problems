#include <cstdio>

int n,m;
int a[200][200];
int cnt=0;
int fx[4][2] = { 0,-1, -1,0, 1,0, 0,1 };

void init(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
    }
}

bool is_cancer(int x,int y){
    if( a[x][y] <=50)
        return 1;
    return 0;
}

bool in_map(int x,int y){
    if( x >=1 && x <= n && y >=1 && y <=n)
        return 1;
    return 0;
}

bool is_cancer_bound(int x,int y){
    if( is_cancer(x,y)){
        int i;
        for (i=0;i<4;i++){
            int nx = x + fx[i][0];
            int ny = y + fx[i][1];
            if( !is_cancer(nx,ny) || !in_map(nx, ny))
                return 1;
        }
        return 0;
    }
    return 0;
}
int main(){
    init();
    int i,j;
    int cnt_1 = 0;
    int cnt_2 = 0;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
                if( is_cancer(i, j))
                    cnt_1++;
                if( is_cancer_bound(i, j))
                    cnt_2++;
        }
    }
    printf("%d %d",cnt_1,cnt_2);
    return 0;
}
