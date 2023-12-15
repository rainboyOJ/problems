#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N=55;
int n,c;
int loc[N],p[N];
int dp[N][N][2];

int cal(int i,int j,int l,int r)
{
    return (loc[j]-loc[i])*(p[l]+p[n]-p[r-1]);
}

int main()
{
    cin>>n>>c;
    memset(p,0,sizeof(p));
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        loc[i]=a;
        p[i]=p[i-1]+b;
    }
    dp[c][c][1]=dp[c][c][0]=0;
    for(int j=c;j<=n;j++)
        for(int i=j-1;i>0;i--)
        {
            dp[i][j][0]=min(dp[i+1][j][0]+cal(i,i+1,i,j+1),dp[i+1][j][1]+cal(i,j,i,j+1));
            dp[i][j][1]=min(dp[i][j-1][0]+cal(i,j,i-1,j),dp[i][j-1][1]+cal(j-1,j,i-1,j));
        }
    cout<<min(dp[1][n][0],dp[1][n][1])<<endl;
    return 0;
}
