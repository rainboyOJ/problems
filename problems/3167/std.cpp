#include<bits/stdc++.h>
using namespace std;
#define init() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);//读入优化
const int maxn=105,maxt=20086,hh=10000;//hh是我们的下标转移常数
int n,t,f[maxn][maxt],a[maxn],ans[maxn];
void dp()
{
    f[1][a[1]+hh] = 1;//a[1]必然是正数
    f[2][a[1]-a[2]+hh]=-1;//a[2]必然是
    for(int i=3; i<=n; i++)
        for(int j=-10000+hh; j<=10000+hh; j++)
        {
            if(f[i-1][j])//可以转移
            {
                f[i][a[i]+j]=1;//+号
                f[i][j-a[i]]=-1;//-号
            }
        }
}
void out()
{
    int s=hh+t;
    for(int i=n; i>=2; i--)//回溯走路径,确定+,-号
    {
        ans[i]=f[i][s];
        if(ans[i]==1)
            s-=a[i];
        else if(ans[i]==-1)
            s+=a[i];
    }
    int cnt=0;
    for(int i=2; i<=n; i++)
        if(ans[i]==1)//是时候减操作了.
        {
            cout<<i-cnt-1<<endl;
            cnt++;
        }
    for(int i=2; i<=n; i++)
        if(ans[i]==-1)//寻找
            cout<<1<<endl;
}
int main()
{
    init();
    cin>>n>>t;
    for(int i=1; i<=n; i++)
        cin>>a[i];
    dp();
    out();
    return 0;
}
