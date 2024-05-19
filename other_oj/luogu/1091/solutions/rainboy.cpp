#include<cstdio>
using namespace std;
int n,max1,max2;
int t[110];
int f[110]; //从左到右开始求 上升的长度.
int f2[110];//从右到左求 上升的长度

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t[i]);
		f[i]=1;
		f2[i]=1;
	}
	
    // 求f
	for(int i=2;i<=n;i++)
	{
		
		for(int j=1;j<=i-1;j++)
		{
			if(t[j]<t[i] && f[i]<f[j]+1)
			f[i]=f[j]+1;
		}
	}

    //求f2
	for(int i=n-1;i>=1;i--)
	{
		for(int j=n;j>=i+1;j--)
		{
			if(t[j]<t[i] &&f2[i]<f2[j]+1)
			f2[i]=f2[j]+1;
		}
	}
    //求符合要求的队列的最长长度
	int ans = -1;
	for(int i=1;i<=n;i++)
	    if( ans < f[i]+f2[i]-1)
            ans = f[i]+f2[i]-1;
	
	printf("%d",n-ans);
	return 0;
}
