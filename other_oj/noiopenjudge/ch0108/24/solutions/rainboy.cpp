#include <cstdio>

int m,n;
int map[200][200];
int idx=0;
           //down   up
int fx[] = {1,-1};
int fy[] = {-1,1};

bool in_map(int x,int y){
    if( x >=1 && x <=n && y >=1 &&  y <= n)
        return 1;
    return 0;
}

void set_num(int x,int y,int dir){
    while( in_map(x, y)){
        map[x][y] = ++idx;
        x += fx[dir];
        y += fy[dir];
    }
}
void get_start(int num,int &x,int &y){
    if( num % 2 == 0){
        if( num <= n){
            x = 1;
            y = num;
            return;
        }
        y = n;
        x = ( num % n)+1;
        return ;
    }

    if( num <=n ){
        y = 1;
        x = num;
        return;
    }
    x = n;
    y = ( num % n)+1;
}

int main(){
    scanf("%d",&n);
    int i,j,k,l;
    int x,y;
    for (i=1;i<2*n;i++){
        get_start(i, x, y);
        set_num(x, y, i % 2);
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    return 0;
}



