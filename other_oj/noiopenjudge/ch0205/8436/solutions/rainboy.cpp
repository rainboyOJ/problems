/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 26日 星期六 14:23:55 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

//二进制表示蛇的状态

char mg[105][105];
int snake_tot=0; // total;
int sx,sy,tx,ty;
struct state {
    int x,y,s,k,step;
};
bool vis[105][105][105][15];

/* 顺时针-4个方向 */
int fx[][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

// 1 << 0 1 000001
// 5 -> 101
bool is_killed_snake(int S,int snake_id){
    return (1 << snake_id)  & S;
}

int kill_snake(int S,int snake_id){
    return (1<<snake_id) | S;
    // 000010
    // xxxxxx
    // xxxx1x
}

void __read(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%s",mg[i]+1);
        for(int j=1;j<=n;++j){
            if( mg[i][j] == 'S' ){
                mg[i][j] = snake_tot;
                ++snake_tot; // 1
            }
            else if( mg[i][j] == 'K' ){
                sx = i,sy  = j;
                mg[i][j] = '.';
            }
            else if( mg[i][j] == 'T' ){
                tx = i,ty  = j;
                mg[i][j] = '.';
            }
        }
    }
    memset(vis,0,sizeof(vis));
}

bool in_mg(int x,int y){
    return x>=1 && x <=n && y >=1 && y<=n;
}


int bfs(){
    queue<state> q;
    q.push({sx,sy,0,0,0});
    vis[sx][sy][0][0] = 1;

    while ( q.empty() == false ) {
        state h = q.front();
        q.pop();
        char t = mg[h.x][h.y];
        //printf("==> %d %d %d %d %d\n",h.x,h.y,h.s,h.k,h.step);
        if( h.x == tx && h.y == ty && h.k == m){
            return h.step;
        }

        if(  t >=0 && t<= 9 && is_killed_snake(h.s, t) == false ){
            int new_s = kill_snake(h.s, t);
            if( vis[h.x][h.y][new_s][h.k] ==0) {
                q.push({h.x,h.y,new_s,h.k,h.step+1});
                vis[h.x][h.y][new_s][h.k] = 1;
                //continue; // 加在这里错了 ,应该有可能new_s这个状态已经出现过了
                //  面对下面的数据
                //3 2 
                //.1K 
                //2ST 
                //S#. 
                //0 0 
            }
                continue; // 应该加在这里
        }
        else
        for(int i=0;i<=3;++i){
            int nx  = h.x + fx[i][0];
            int ny  = h.y + fx[i][1]; // ctrl+a add ctrl+x
            char c = mg[nx][ny];
            if( in_mg(nx,ny) && c != '#') {
                int key = h.k;
                if( c >= '1' && c <='9' && c == key+'0'+1) key++;
                if( vis[nx][ny][h.s][key] == 0){
                    q.push({nx,ny,h.s,key,h.step+1});
                    vis[nx][ny][h.s][key] = 1;
                }
            }
        }

    }

    return -1;
}

int main(int argc,char * argv[]){
    while ( 1 ) {
        snake_tot = 0;
        __read();
        if( n ==  0 && m == 0 ) break;
        int ans = bfs();
        if( ans == -1)
            printf("impossible\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}
