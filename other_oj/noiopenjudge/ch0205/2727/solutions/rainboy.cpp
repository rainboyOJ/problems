/*============================================================================
* Title : noi 2727 仙岛求药
* Author: Rainboy
* Time  : 2016-07-31 19:05
* update: 2016-07-31 19:05
* © Copyright 2016 Rainboy. All Rights Reserved.
*=============================================================================*/

/*  1.走最短的路
 *  2.明显的BFS走迷宫
 *
 * */

#include <cstdio>
#include <cstring>

int fx[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

/* 迷宫数据 */
char map[40][40];
bool vis[40][40];


struct _node {
    int x,y;
    int step;
};

_node s,t;//起,终点
int m,n;

/* 队列 */
_node queue[10000];
int tail,head;


bool isRight(int x,int y){
    if(x>0 && x<=m && y>0 && y<=n && map[x][y]=='.')
        return true;
    return false;
}

/* 迷宫初始化 */
void maze_init(){
    int i,j;
    for (i=1;i<=m;i++){
        scanf("%s",&map[i][1]);

        for (j=1;j<=n;j++){
            if(map[i][j] == '@')
                s.x=i,s.y=j;
            if(map[i][j] == '*')
                t.x=i,t.y=j;
        }
    }
}


bool bfs(){
    memset(vis,0,sizeof(vis));
    head=tail=0;
    tail++;
    //queue[tail].x=s.x,queue[tail].y=s.y;
    queue[tail]=s;
    queue[tail].step=1;

    while(head !=tail){
        head++;
        int x= queue[head].x;
        int y= queue[head].y;
        int step= queue[head].step;
        int i;
        for (i=0;i<4;i++){
            int nx = x+fx[i][0];
            int ny = y+fx[i][1];
            int n_step = step+1;
            if(nx == t.x && ny == t.y){//边界
                printf("%d\n",step);
                return true;
            }
            
            if(isRight(nx,ny) && vis[nx][ny] ==0){
                tail++;
                queue[tail].x= nx;
                queue[tail].y= ny;
                queue[tail].step= n_step;
                vis[nx][ny]=1;
            }
        }
    }
    printf("-1\n");
    return false;
}

int main(){
    while(1){
        scanf("%d%d",&m,&n);
        if( m==0 && n==0 ) return 0;
        maze_init();
        bfs();
    }
    return 0;
}

