#include<bits/stdc++.h>
using namespace std;
const int N=500+7,mod=998244353;
int f[N],a[N];
int g(int u){
	if(f[u]==u) return u; return f[u]=g(f[u]);
}
int pows(long long u,int v){
	long long ans=1;
	while(v>0){
		if(v&1) ans=ans*u%mod; u=u*u%mod,v=v>>1;
	}
	return ans;
}
int main(){
	int n,ans=0,D=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],D|=a[i];
	//33=2^5+2^0
	//2^1
	for(int j=0;j<(1<<15);j++){
		if((D&j)!=j) continue; 
		for(int k=1;k<=n;k++) f[k]=k;//并查集初始化 
		for(int k=0;k<=14;k++){
			if(!(j&(1<<k))) continue;
			//(1<<k)这一位上为1
			//所有这一位上为1的数都要放到一个并查集里 
			int j=0;
			//所有满足 (1<<k)这一位上为1的数里面的第一个值 
			for(int c=1;c<=n;c++){
				if(a[c]&(1<<k)){
					if(!j) j=c;
					f[g(j)]=g(c);
					//j,c放到一个并查集里 
				}
			}
		}
		int s=0;
		for(int k=1;k<=n;k++) if(g(k)==k) s++;
		//求解j在二进制下有多少个1
		// +1
		// -1
		if(__builtin_popcount(j)%2==0) ans=(ans+pows(2,s))%mod;
		else ans=(ans-pows(2,s)+mod)%mod;
	}
	cout<<ans<<endl;
    return 0;
}

