#include<iostream>
#include<cmath>
using namespace std;
bool prime(int x);

int main()
{
	int x,y;
	int ans=0;
	int i;
	
	cin>>x>>y;
	for(i=x;i<=y;i++)//从x枚举到y
		if( prime(i) )//分别判断i是否是素数
			ans++;
	cout<<ans<<endl;
	return 0;
}

bool prime(int x)//判断素数
{
	int i=2;
	if(x==1||x==0)	return false;
	while( i<=floor(sqrt(x)) && (x%i!=0) )
		i++;
	if(i>floor(sqrt(x)))
		return true;
	return false;
}
