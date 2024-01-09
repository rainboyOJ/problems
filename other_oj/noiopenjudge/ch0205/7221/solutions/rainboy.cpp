#include <bits/stdc++.h>
using namespace std;

int n,m,cnt;
int all_stone;
char str[205][205];
bool vis[205][205][35];
int sx,sy,tx,ty;
int fx[4][2] = { 0,1, 0,-1, 1,0, -1,0 };

struct node {
    int x,y,stone,step;
};

vector<node> trans;

void init(){
    scanf("%d%d%d",&n,&m,&cnt);
    all_stone = (1<<cnt)-1;
    trans.clear();
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%s",str[i]+1);
        for (j=1;j<=m;j++){
            char &at = str[i][j];
            if( at == 'S')
                sx = i,sy = j;
            else if ( at == 'E')
                tx = i,ty = j;
            else if (at == '$'){
                trans.push_back({i,j,0,0});
            }
        }
    }
}

bool in_map(int x,int y){
    return ( x >=1 && x <=n && y >=1 && y <=m);
}

int stone_num(char c){
    return (1<<(c-'0'));
}

bool stone_ok(int num){
    return (num & all_stone) == all_stone;
}

int bfs(){
    memset(vis,0,sizeof(vis));
    queue<node> q;
    q.push({sx,sy,0,0});
    vis[sx][sy][0] = 1;

    while( !q.empty()){
        node h = q.front();
        q.pop();
        int i;
        for(i=0;i<4;i++){
            int nx = h.x + fx[i][0];
            int ny = h.y + fx[i][1];

            if( nx == tx && ny == ty && stone_ok(h.stone))
                return h.step+1;

            char &at = str[nx][ny];
            if( in_map(nx,ny) && at != '#' ){
                int stone = h.stone;
                if( at >= '0' && at <='4'){
                    stone = stone | stone_num(at);
                    if( vis[nx][ny][stone] == 0){
                        vis[nx][ny][stone] = 1;
                        q.push({nx,ny,stone,h.step+1});
                    }
                }
                else if( at == '$'){
                    for( auto _node : trans){
                        int nnx = _node.x;
                        int nny = _node.y;
                        if( vis[nnx][nny][stone] == 0){
                            vis[nnx][nny][stone] = 1;
                            q.push({nnx,nny,stone,h.step+1});
                        }
                    }
                }
                else if( at == '.'){
                    if( vis[nx][ny][stone] == 0){
                        vis[nx][ny][stone] = 1;
                        q.push({nx,ny,stone,h.step+1});
                    }
                }

            }

        }
    }
    return -1;
}



int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        init();
        int ans = bfs();
        if( ans == -1)
            printf("oop!\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}
