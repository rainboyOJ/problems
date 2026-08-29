#include<bits/stdc++.h>
using namespace std;
int n,s,f[250005];
struct node{
	int a,b;
}t[505];
bool cmp(node x,node y){
	return x.b>y.b;
}
int main(){
	freopen("meal10.in","r",stdin);
	freopen("meal10.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>t[i].a>>t[i].b;
	sort(t+1,t+n+1,cmp);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		s+=t[i].a;
		for(int j=s;j>=0;j--){
            f[j]=max(f[j],s-j+t[i].b);
			if(j>=t[i].a)f[j]=min(f[j],max(j+t[i].b,f[j-t[i].a]));
		}
	}
	int ans=1e9;
	for(int i=0;i<=s;i++)ans=min(ans,f[i]);
	cout<<ans;
}