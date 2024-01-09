#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;

int n,m,k;
bool _map[maxn][maxn];

void init(){
    scanf("%d%d%d",&n,&m,&k);
    int i,j,k;
    memset(_map,1,sizeof(_map));
}

bool in_map(int x,int y ){

    if( x>=1 && x <=n && y>=1 && y <=m)
        return 1;
    return 0;
}

void set_bomb(int x,int y,int p,int ok){
    int i,j;
    if( ok ){
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                if( !in_map(i,j)) continue;
                if( i >= x-p/2 && i <= x + p/2 && j >= y-p/2 && j <= y+p/2  ){
                    ;
                }
                else
                    _map[i][j] = 0;
            }
        }

    }
    else {
        for(i=x-p/2;i<=x+p/2;i++){
            for(j=y-p/2;j<=y+p/2;j++){
                if( !in_map(i,j)) continue;
                _map[i][j] = 0;
            }
        }

    }
}

int main(){
    init();
    int i,j;
    int x,y,p,ok;
    for(i=1;i<=k;i++){
        scanf("%d%d%d%d",&x,&y,&p,&ok);
        set_bomb(x,y,p,ok);
    }
    int cnt=0;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if( _map[i][j])
                cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
