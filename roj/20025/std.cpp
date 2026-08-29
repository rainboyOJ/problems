#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

const int mod = 998244353;
const int N = 1e6+5;
int f[N][2],g[N][2];
int n,a[N],stk[N],top;

int M(int x){
	return (x%mod+mod)%mod;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	f[0][0]=1;f[0][1]=0;
	g[0][0]=1;g[0][1]=0;
	for(int i=1;i<=n;i++){
		while(top && a[stk[top]] >= a[i]) top--;
		int cur = top?stk[top]:0;
		stk[++top]=i;
		if(!cur){
			f[i][0]=M(g[i-1][1]*a[i]);
			f[i][1]=M(g[i-1][0]*a[i]);
		}
		else{
			f[i][0]=M(f[cur][0]+M(M(M(g[i-1][1]-g[cur-1][1]))*a[i]));
			f[i][1]=M(f[cur][1]+M(M(M(g[i-1][0]-g[cur-1][0]))*a[i]));
		}
		g[i][0] = M(g[i-1][0] + f[i][0]);
		g[i][1] = M(g[i-1][1] + f[i][1]);
	}
	if(n&1) cout<<(M(f[n][1]-f[n][0]))<<'\n';
	else cout<<(M(f[n][0]-f[n][1]))<<'\n';
	return 0;
}
