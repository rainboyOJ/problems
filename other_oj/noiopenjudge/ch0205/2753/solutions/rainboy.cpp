#include <cstdio>
#include <queue>
using namespace std;

int n,m;
char maze[50][50];
bool vis[50][50];
struct pos{
	int x,y,step;
};

int fx[][2] = {1,0,0,1,-1,0,0,-1};

bool init(){
	scanf("%d%d",&n,&m);
	int i,j;
	for(i=1;i<=n;i++){
		scanf("%s",maze[i]+1);
	}
}
bool in_map(int x,int y){
	if( x >=1 && x<=n && y>=1 && y <=m)
		return 1;
	return 0;
}
int bfs(){
	queue<pos> q;
	q.push({1,1,1});
	vis[1][1] = 1;
	while( !q.empty() ){
		pos h = q.front();
		q.pop();
		int i;
		for(i=0;i<4;i++){
			int nx = h.x + fx[i][0];
			int ny = h.y + fx[i][1];
			
			if( nx == n && ny == m){
				return h.step+1;
			}
			if( in_map(nx,ny) && !vis[nx][ny] && maze[nx][ny] == '.'){
				q.push({nx,ny,h.step+1});
				vis[nx][ny] = 1;
			}
			
		}
	}
	return -1;
}
int main(){
	init();
	if ( n == 1 && m == 1){
		printf("1");
	}
	else {
		int ans = bfs();
		printf("%d",ans);
	}
	return 0;
}