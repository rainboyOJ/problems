#include <cstdio>
int n,m;
int ans;
void dfs(int dep,int pre,int sheng){
	if( dep == n){
		if( sheng >= pre) ans++;
		return;
	}
	int i;
	for(i=pre;i<=sheng;i++){
		dfs(dep+1,i,sheng-i);
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&m,&n);
		ans  =0;
		dfs(1,0,m);
		printf("%d\n",ans);
	}
	return 0;
}