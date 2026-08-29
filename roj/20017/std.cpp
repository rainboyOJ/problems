#include<bits/stdc++.h>
using namespace std;

const int X[]={1,0,-1,0};
const int Y[]={0,1,0,-1};
const int X2[]={1,-1,-1,1};
const int Y2[]={1,1,-1,-1};
string s;
int n,m,ans;
char a[105][105];

void dfs(int dep,int x,int y,int hd,bool f=0)
//f=0±íÊ¾»¹Ã»ÓĞ×ªÍä
//f=1±íÊ¾ÒÑ¾­×ªÍä¹ıÁË 
{
	if(dep==s.size())
	{
		//cerr<<x<<' '<<y<<endl;
		ans++;//ç´¯åŠ ç­”æ¡ˆï¼Œä¸‹åŒ
		return;
	}
	//²»×ªÍä
	//×ªÍä 
	int x_=x+X[hd],y_=y+Y[hd];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&a[x_][y_]==s[dep]) dfs(dep+1,x_,y_,hd,f);//æ­£å¸¸èµ°ï¼Œä¸‹åŒ
	x_=x+X[(hd+1)%4];
	y_=y+Y[(hd+1)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs(dep+1,x_,y_,(hd+1)%4,1);//å³è½¬ 90Â°ï¼Œä¸‹åŒ
	x_=x+X[(hd+3)%4];
	y_=y+Y[(hd+3)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs(dep+1,x_,y_,(hd+3)%4,1);//å·¦è½¬ 90Â°ï¼Œä¸‹åŒ
}

void dfs2(int dep,int x,int y,int hd,bool f=0)
{
	if(dep==s.size())
	{
		//cerr<<x<<' '<<y<<endl;
		ans++;
		return;
	}
	int x_=x+X2[hd],y_=y+Y2[hd];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&a[x_][y_]==s[dep]) dfs2(dep+1,x_,y_,hd,f);
	x_=x+X2[(hd+1)%4];
	y_=y+Y2[(hd+1)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs2(dep+1,x_,y_,(hd+1)%4,1);
	x_=x+X2[(hd+3)%4];
	y_=y+Y2[(hd+3)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs2(dep+1,x_,y_,(hd+3)%4,1);
}

int main()
{
	cin>>s>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==s[0])//ç›¸ç­‰æ—¶å†æœ
			{
				dfs(1,i,j,0);
				dfs(1,i,j,1);
				dfs(1,i,j,2);
				dfs(1,i,j,3);
				dfs2(1,i,j,0);
				dfs2(1,i,j,1);
				dfs2(1,i,j,2);
				dfs2(1,i,j,3);
			}
		}
	}
	cout<<ans;
 	return 0;
}
