#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N=1000050;
const int inf=1e9+7;
struct info{
	int cnt[3];
	int sum;
	int mnOne;

	info(){
		cnt[0]=0;
		cnt[1]=0;
		cnt[2]=0;
		sum=0;
		mnOne=inf;
	}
};

info operator + (const info& a,const info& b){
	info ans=info();
	ans.sum=a.sum+b.sum;
	ans.mnOne=min(a.mnOne, b.mnOne);
	for(int i=0;i<3;i++)ans.cnt[i]=a.cnt[i]+b.cnt[i];
	return ans;
}

vector<int> E[N];
int c[N],n,k;
int ans;

bool Check(info tmp){
	if(tmp.sum<k)return false;
	if(tmp.sum-tmp.mnOne+1>=k){
		return true;
	}
	if(tmp.cnt[1]%2==k%2){
		return true;
	}
	return false;
}

info DFS(int u,int p){
	info tmp=info();
	for(int v:E[u]){
		if(v!=p){
			info sub=DFS(v,u);
			tmp=tmp+sub;
		}
	}
	tmp.cnt[c[u]]++;
	tmp.sum+=c[u];
	if(c[u]==1){
		tmp.mnOne=min(tmp.mnOne,tmp.sum);
	}
	if(Check(tmp)){
		tmp=info();
		ans++;
	}
	return tmp;
}
int main(){
	int t;
	scanf("%i",&t);
	while(t--){
		scanf("%i %i",&n,&k);
		for(int i=1;i<=n;i++)scanf("%i",&c[i]);
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%i %i",&u,&v);
			E[u].pb(v);
			E[v].pb(u);
		}

		ans=0;
		DFS(1,0);
		printf("%i\n",ans);

		for(int i=1;i<=n;i++){
			E[i].clear();
		}
	}
	return 0;
}

