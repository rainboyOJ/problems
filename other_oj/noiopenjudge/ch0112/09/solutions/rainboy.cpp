#include <cstdio>
#include <cstring>

int map[200][200];
int map_bak[200][200];
char str[1000];
int m,n;

void _swap(int &a,int &b){
    int t = a; a = b; b = t;
}

void clock(){
    int i,j;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++){
            map_bak[j][m-i+1]= map[i][j];
        }
    memcpy(map,map_bak,sizeof(map));
    _swap(n,m);
}
void anti_clock(){
    int i,j;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++){
             map_bak[n-j+1][i]= map[i][j];
        }
    memcpy(map,map_bak,sizeof(map));
    _swap(n,m);
}

void left_right(){
    int i,j;
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            map_bak[i][n-j+1]= map[i][j];
        }
    }
    memcpy(map,map_bak,sizeof(map));
}

void up_down(){
    int i,j;
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            map_bak[m-i+1][j]= map[i][j];
        }
    }
    memcpy(map,map_bak,sizeof(map));
}
int main(){
    scanf("%d%d",&m,&n);
    int i,j;
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&map[i][j]);
        }
    }
    scanf("%s",str);
    int len  = strlen(str);
    for (i=0;i<len;i++){
        char c = str[i];
        if( c == 'A')
            clock();
        else if( c == 'B')
            anti_clock();
        else if( c == 'C')
            left_right();
        else if( c == 'D')
            up_down();
    }
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    return 0;
}
