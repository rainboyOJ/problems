#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int fx[][3] = {
	{0,0,1},
	{0,1,0},
	{0,0,-1},
	{0,-1,0},
	{1,0,0},
	{-1,0,0}
};

char maze[35][35][35];
int vis[35][35][35];
int sx,sy,sz,tx,ty,tz;
int l,r,c;
struct sta {
	int z,x,y,step;
};
void init(){
	memset(maze,0,sizeof(maze));
	memset(vis,0,sizeof(vis));
	scanf("%d%d%d",&l,&r,&c);
	int i,j,k;
	for( i =1;i<=l;i++) {
		for( j = 1;j<=r;j++){
			scanf("%s",maze[i][j]+1);
			
			for(k=1;k<=c;k++ ){
				char &t = maze[i][j][k];
				if( t == 'S')
					sx = j,sy=k,sz=i;
				else if( t == 'E')
					tx = j,ty=k,tz=i;
			}
		}
	}
}

bool in_map( int z,int x,int y) {
	if(
		z >= 1 && z <= l &&
		x >=1  && x <= r &&
		y >=1  && y <= c  
	)
		return 1;
	return 0;
}
int bfs(){
	queue<sta> q;
	q.push({sz,sx,sy,0});
	vis[sz][sx][sy] = 1;
	
	while( !q.empty()){
		
		sta h = q.front();
		q.pop();
		
		int i;
		for( i =0;i< 6 ;i++){
			int nz = h.z+fx[i][0];
			int nx = h.x+fx[i][1];
			int ny = h.y+fx[i][2];
			if( nz == tz && nx == tx && ny == ty)
				return h.step +1;
			if( in_map(nz,nx,ny) && !vis[nz][nx][ny] && maze[nz][nx][ny] == '.'){
				q.push({nz,nx,ny,h.step+1});
				vis[nz][nx][ny] = 1;	
			}
		}
	}
	return -1;	
}
int main(){
	//freopen("c:\in","r",stdin);
	while(1){
		init();
		if( l == 0 && r == 0 && c == 0) break; 
		int ans = bfs();
		if( ans != -1)
			printf("Escaped in %d minute(s).\n",ans);
		else
			printf("Trapped!\n");
	}
	return 0;
}