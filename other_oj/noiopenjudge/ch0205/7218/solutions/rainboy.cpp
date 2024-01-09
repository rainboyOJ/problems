#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

int t,r,c;
int sx,sy,tx,ty;
char m[210][210] = {0};

struct _node {
    int x,y;
    int step;
};

_node node[210*210];
int head = 0,tail =0;

void push(int x,int y,int s){
    node[tail].x = x;
    node[tail].y = y;
    node[tail].step = s;
    tail++;
}

void pop(){
    head++;
}

bool empty(){
    return tail == head;
}

int fx[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };

bool vis[210][210] = {0};

bool in_map(int x,int y){
    if( x>= 1 && x <= r && y>=1 && y <=c)
        return true;
    return false;
}
void bfs(){
    head = 0; tail = 0;
    memset(vis,0,sizeof(vis));
    //加入起点
    push(sx,sy,0);

    while( empty() == false){
        
        int x = node[head].x;
        int y = node[head].y;
        int s = node[head].step;
        pop();

        int i;
        for(i=0;i<4;i++){
            int nx = x + fx[i][0];
            int ny = y + fx[i][1];
            
            if( nx == tx && ny == ty){
                cout << s+1 << endl;
                return;
            }


            if(in_map(nx,ny) && vis[nx][ny]==0 && m[nx][ny] == '.'){
                vis[nx][ny] = 1;
                push(nx,ny,s+1);
            }

        }
    }
    cout << "oop!" << endl;
}


int main(){
    cin >> t;
    
    int i,j,k;
    for(i=1;i<=t;i++){
        
        cin >> r >> c;
        for(k=1;k<=r;k++)
            for(j=1;j<=c;j++){
                cin >> m[k][j];
                if( m[k][j] == 'S'){
                    sx = k;
                    sy =j;
                }
                else if( m[k][j] == 'E'){
                    tx = k;
                    ty =j;
                }
            }
        bfs();
        
    }
    return 0;
}
