#include<bits/stdc++.h>
#define maxn 120000
int mod; 
using namespace std;
int beat[105];
string s="";
map<string,int> vis;
vector<string> ans;
int tot=0;
int n,m,k;
void dfs(string s,int len)
{
	if (vis[s]==0)
	{
		vis[s]=1;
		ans.push_back(s);
		tot++;
	}
	else return;
	if (len==n) return;
	for (int i=0;i<n;i++)
	if (s[i]=='0')
	{
		string t=s;
		char c='0';
		for (int j=0;j<i;j++)
			c=max(c,s[j]);
		t[i]=c+1;
		dfs(t,len+1);
	}
	return;
}
string S[maxn];
map<string,int> ID;
int num=0;
long long cnt[maxn];
void init()
{
	for (int i=0;i<tot;i++)
	{
		s=ans[i];
		char c='0';
		for (int j=0;j<n;j++) if (s[j]=='0') {s[j]=c+1; c++;} else c=max(c,s[j]);
		c='0';
		for (int j=0;j<n;j++) c=max(c,s[j]);
		if (c>='0'+k) {S[++num]=ans[i]; ID[ans[i]]=num;}
	}
	
	for (int i=1;i<=num;i++)
		for (int j=0;j<n;j++)
		if (S[i][j]!='0')
			cnt[i]|=(1<<j);
	
	return;
}

long long C[550][550];
long long fact[550];
void init2()
{
	fact[0]=1;
	for (int i=1;i<=530;i++) fact[i]=fact[i-1]*i%mod;
	C[0][0]=1;
	for (int i=1;i<=530;i++)
	for (int j=0;j<=i;j++)
	{
		if (j==0 || i==1) C[i][j]=1;
		else {C[i][j]=C[i-1][j]+C[i-1][j-1]; C[i][j]%=mod;}
	}
	return;
}

void add(long long &x,long long y) {x+=y; x%=mod; return;}
long long dp[17][maxn];
string now,nxt;

void modify(string &s,int pos)
{
	char c='0';
	for (int i=0;i<pos;i++) c=max(c,s[i]);
	s[pos]=c+1;
	return;
}

void work()
{
	dp[0][1]=1;
	for (int i=0;i<m;i++)
		for (int j=1;j<=num;j++)
		if (dp[i][j])
		{
			add(dp[i+1][j],dp[i][j]);
			now=S[j];
			for (int k=0;k<n;k++)
			if (now[k]=='0' && beat[i]>=(cnt[j]+(1<<k)+1))
			{
				nxt=now;
				modify(nxt,k);	
				add(dp[i+1][ID[nxt]],dp[i][j]*C[beat[i]-cnt[j]-2][(1<<k)-1]%mod*fact[1<<k]);
			}
		}
	long long ans=0;
	for (int j=1;j<=num;j++) if (cnt[j]==((1<<n)-1)) add(ans,dp[m][j]);
	for (int i=1;i<=n;i++)
		 add(ans,ans);
	cout<<ans<<endl;
	return;
}

int main()
{
	cin>>n>>m>>k>>mod;
	for (int i=0;i<m;i++) cin>>beat[i]; sort(beat,beat+m);
	for (int i=1;i<=n;i++) s=s+'0';
	dfs(s,0);
	init();
	init2();
	work();
	return 0;
}