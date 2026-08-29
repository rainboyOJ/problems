#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    freopen("lab3.in","r",stdin);
    freopen("lab3.out","w",stdout);
	int n;
	cin>>n;
	int mxx=-1e9, mxy=-1e9, minx=1e9, miny=1e9;
	for(int i=1;i<=n;i++)
	{
		int x, y;
		cin>>x>>y;
		mxx=max(mxx,x);
		minx=min(minx,x);
		mxy=max(mxy,y);
		miny=min(miny,y);
	}
	cout<<minx-1<<" "<<miny-1<<"\n"<<mxx+1<<" "<<mxy+1;
}
