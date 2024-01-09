#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;


char maze[100][100];
bool vis[100][100];
int n,m;
int sx,sy;
int key_num[200]; //钥匙的数量
int key_get[200]; //得到钥匙的数量
bool is_get_key = 0;
int fx[4][2] = {1,0,0,1,-1,0,0,-1};

struct pos{
    int x,y;
};

bool is_key(char c){
    return (c >='a' && c<='e');
}
bool is_door(char c){
    return (c >='A' && c<='E');
}

void init(){
    memset(key_num,0,sizeof(key_num));
    memset(key_get,0,sizeof(key_get));
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%s",maze[i]+1);
    }
    for (i=1;i<=n;i++){
       for (j=1;j<=m;j++){
           char &at = maze[i][j];
           if( is_key(at))
               key_num[at]++;
           else if( at == 'S')
               sx = i,sy =j;
       }
    }
}

bool in_map(int x,int y){
    return (x>=1 && x<=n && y >=1 && y <=m);
}

bool bfs(){
    memset(vis,0,sizeof(vis));
    vis[sx][sy] = 1;
    queue<pos> q;
    q.push({sx,sy});

    while( !q.empty()){
        pos h = q.front(); q.pop();
        int i;
        for (i=0;i<4;i++){
            int nx = h.x+fx[i][0];
            int ny = h.y+fx[i][1];
            if( in_map(nx,ny) && !vis[nx][ny] && maze[nx][ny] != 'X' &&!is_door(maze[nx][ny])){
                char &at = maze[nx][ny];
                if( at == 'G')
                    return 1;
                if( is_key(at)){
                    is_get_key = 1;
                    key_get[at]++;
                    at = '.';
                }
                vis[nx][ny] = 1;
                q.push({nx,ny});
            }
        }
    }
    return 0;
}

void clear_door(char door){
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            char &at = maze[i][j];
            if( at == door){
                at = '.';
            }
        }
    }
}

void print_maze(){
    int i,j;
    for (i=1;i<=n;i++){
        printf("%s\n",maze[i]+1);
    }
    printf("============\n");
}

bool Find_way(){
    while(1){
        is_get_key = 0;
        bool ret = bfs();
        if( ret) return 1;
        if( !is_get_key)
            return 0;

        /* deal door  */
        int i;
        for(i='a' ;i<= 'e';i++){
            if( key_num[i] != 0 && (key_num[i] == key_get[i])){
                clear_door(i+'A'-'a');
                key_num[i] = 0;
            }
        }

    }
    return 0;
}


int main(){
    while(1){
        scanf("%d%d",&n,&m);
        if( n == 0 || m == 0) return 0;
        init();
        if( Find_way())
            printf("YES\n");
        else 
            printf("NO\n");
    }
    return 0;
}
