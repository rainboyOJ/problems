#include<bits/stdc++.h>
#define maxn 1010
#define INF 0X7f7f7f7f
using namespace std;

int n;
double v,x;
double sum[maxn];
double dp[maxn][maxn][2];

struct pt
{
    double x,c,d;
    bool operator < (const pt& rhs)const
    {
        return x<rhs.x;
    }
}PT[maxn];

inline double cost(int l,int r)
{
    return sum[n]-sum[r]+sum[l-1];
}

int main()
{
    while(scanf("%d %lf %lf", &n, &v, &x) == 3 && n)
    {
        for(int i=1;i<=n;i++)
            scanf("%lf %lf %lf",&PT[i].x,&PT[i].c,&PT[i].d);
        n++;
        PT[n].x=x;PT[n].c=PT[n].d=0;
        sort(PT+1,PT+1+n);
        for(int i=1;i<=n;i++)
            sum[i]=sum[i-1]+PT[i].d;
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                dp[i][j][0]=dp[i][j][1]=INF;
        for(int i=1;i<=n;i++)
            if(PT[i].x==x)
            {
                dp[i][i][0]=dp[i][i][1]=0;
                break;
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j+i-1<=n;j++)
            {
                int l=j;
                int r=j+i-1;
                if(l>=2)
                {
                    double t=(PT[l].x-PT[l-1].x)/v;
                    dp[l-1][r][0]=min(dp[l-1][r][0],dp[l][r][0]+cost(l,r)*t+PT[l-1].c);
                    t=(PT[r].x-PT[l-1].x)/v;
                    dp[l-1][r][0]=min(dp[l-1][r][0],dp[l][r][1]+cost(l,r)*t+PT[l-1].c);
                }
                if(r<n)
                {
                    double t=(PT[r+1].x-PT[r].x)/v;
                    dp[l][r+1][1]=min(dp[l][r+1][1],dp[l][r][1]+cost(l,r)*t+PT[r+1].c);
                    t=(PT[r+1].x-PT[l].x)/v;
                    dp[l][r+1][1]=min(dp[l][r+1][1],dp[l][r][0]+cost(l,r)*t+PT[r+1].c);
                }
            }
        printf("%.lf\n",floor(min(dp[1][n][0],dp[1][n][1])));
    }
    return 0;
}
