#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n;

char _map[300][300];
int color[300];
int cnt;

void init(){
	scanf("%d",&n);
	cnt = 1;
	memset(color,0,sizeof(color));
	memset(_map,0,sizeof(_map));
	char t[100];
	int i,j;
	for( i =1;i<=n;i++){
		scanf("%s",t+1);
		int len = strlen(t+1);
		for(j=3;j<=len;j++){
			int x  = ++_map['A'+i-1][0] ;
			_map['A'+i-1][x] = t[j];
		}
	}
}

bool is_color_ok(char u,int c) {
	int i;
	for(i=1;i<=_map[u][0];i++){
		if( color[ _map[u][i] ] == c)
			return 0;
	}
	return 1;
}
void dfs(char u){
	if( color[u] != 0)
	 	return ;
	int i;
	for( i =1;i<=n;i++){
		if( is_color_ok(u,i) ){
			cnt = max(cnt,i);
			color[u] = i;
			break;
		}
	}
	
	for( i =1;i< _map[u][0] ;i++){
		dfs(_map[u][i]);
	}
}
int main(){
	//freopen("c:\in","r",stdin);
	while(1){
		init();
		if( n== 0) break;
		char i;
		for( i='A';i<='A'+n-1;i++){
			if( color[i] == 0)
				dfs(i);
		}
		if( cnt == 1)
			printf("1 channel needed.\n");
		else
			printf("%d channels needed.\n",cnt);
	}
	return 0;
}