#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int,int> PII;
const int N = 16010, M = 105;

struct painter
{
    int si,pi,li;
}per[M];
int n,m,f[M][N];

bool cmp(painter a,painter b)
{
    return a.si<b.si;
}

int main()
{
//  freopen("123.txt","r",stdin);
    cin >> n >> m; 
    for(int i = 1;i<=m;i ++)
        scanf("%d%d%d",&per[i].li,&per[i].pi,&per[i].si);
    sort(per+1,per+1+m,cmp);

    for(int i=1;i<=m;i++)
    {
        deque<PII> q1;
        for(int j=0;j<=n;j++)
        {
            f[i][j]=max(f[i-1][j],f[i][j-1]);
            if(j>=per[i].si)
            {
                while(q1.size() && q1.front().second<j-per[i].li)q1.pop_front();
                if(q1.size())f[i][j]=max(f[i][j],q1.front().first+per[i].pi*j);
            }
            else 
            {
                while(q1.size() && q1.back().first<=f[i-1][j]-per[i].pi*j)q1.pop_back();
                q1.push_back({f[i-1][j]-per[i].pi*j,j});
            }
        }
    }
    cout<<f[m][n];
}
//这里填你的代码^^
//注意代码要放在两组三个点之间，才可以正确显示代码高亮哦~
