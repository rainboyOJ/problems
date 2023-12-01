#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
const int MAXN=100005;
int n,a[MAXN],k,d[MAXN],top1,top2;
pair<int,int>stk_max[MAXN],stk_min[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        while(top1&&stk_max[top1].first<=a[i])--top1;
        while(top2&&stk_min[top2].first>=a[i])--top2;
        stk_max[++top1]=make_pair(a[i],i);
        stk_min[++top2]=make_pair(a[i],i);
        int nowmax=a[i],nowmin=a[i];
        int pin1=top1-1,pin2=top2-1;
        int nowl=i;
        while(pin1||pin2)
        {
            if(pin1&&pin2)
            {
                if(stk_max[pin1].second>=stk_min[pin2].second)
                {
                    d[i-nowl+1]+=nowmax*nowmin;
                    d[i-stk_max[pin1].second+1]-=nowmax*nowmin;
                    nowl=stk_max[pin1].second;
                    nowmax=stk_max[pin1].first;
                    --pin1;
                }
                else
                {
                    d[i-nowl+1]+=nowmax*nowmin;
                    d[i-stk_min[pin2].second+1]-=nowmax*nowmin;
                    nowl=stk_min[pin2].second;
                    nowmin=stk_min[pin2].first;
                    --pin2;
                }
            }
            else if(pin1)
            {
                d[i-nowl+1]+=nowmax*nowmin;
                d[i-stk_max[pin1].second+1]-=nowmax*nowmin;
                nowl=stk_max[pin1].second;
                nowmax=stk_max[pin1].first;
                --pin1;
            }
            else
            {
                d[i-nowl+1]+=nowmax*nowmin;
                d[i-stk_min[pin2].second+1]-=nowmax*nowmin;
                nowl=stk_min[pin2].second;
                nowmin=stk_min[pin2].first;
                --pin2;
            }
        }
        d[i-nowl+1]+=nowmax*nowmin;
        d[i+1]-=nowmax*nowmin;
    }
    for(int i=1;i<=n;++i)
    {
        d[i]+=d[i-1];
        printf("%d%c",d[i],i==n?'\n':' ');
    }
    return 0;
}
