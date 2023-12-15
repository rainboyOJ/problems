#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=1e3;
stack<int> q;
int n,tot=0,cnt=0,flag=0,ans[N];
void dfs(int now){
	//if(flag)return;
	if(tot==n){
		rep(i,1,n)cout<<ans[i];puts("");
		cnt++;
		return;
	}
	if(cnt==20){
		flag=1;
		return;
	}
	if(q.size()){
		int x=q.top(); q.pop();
		ans[++tot]=x;
		dfs(now);
		tot--;
		q.push(x);
	}
	if(now<=n){
		q.push(now);
		dfs(now+1);
		q.pop();
	}
	
}
int main(){
	scanf("%d",&n);
	dfs(1);
	return 0;
}

