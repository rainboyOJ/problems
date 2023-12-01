#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
map<long long,int> cnt;
long long a[MAXN],p[MAXN];
int ans,T,n,m;
bool flag[MAXN];
long long rebuild(long long x)
{
    for(int i=1;i<=m;++i)
    {
        while(x%p[i]==0)
        {
            x/=p[i];
        }
        if(p[i]>x)
        {
            break;
        }
    }
    return x;
}
int main()
{
    for(long long i=2;i<=1260;++i)
    {
        if(!flag[i])
        {
            p[++m]=i*i*i;
            for(long long j=i*i;j<=1260;j+=i)
            flag[j]=true;
        }

    }
    ans=0;
    cnt.clear();
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]=rebuild(a[i]);
        cnt[a[i]]++;

    }
    for(map<long long,int>::iterator i=cnt.begin();i!=cnt.end();++i)
    {
        if(i->first==1)
        {
            ++ans;
            continue;
        }
        else
        {
            int Pair=rebuild((i->first)*(i->first));
            ans+=max(i->second,cnt[Pair]);
            cnt[Pair]=0;
            i->second=0;
        }
    }
    printf("%d\n",ans);
    return 0;
}
