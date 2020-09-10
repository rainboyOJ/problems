#include<iostream>
#include<cmath>
using namespace std;
bool prime(int x);
int palindrome(int n);

int main()
{
	int n;
	int ans=0;
	int i;
	
	cin>>n;
	for(i=11;i<=n;i++)//从11枚举到n
		if( prime(i) && palindrome(i)==i )//分别判断i是否是素数以及回文数
			ans++;
	cout<<ans<<endl;
	return 0;
}

bool prime(int x)//判断素数
{
	int i=2;
	while( i<=floor(sqrt(x)) && (x%i!=0) )
		i++;
	if(i>floor(sqrt(x)))
		return true;
	return false;
}

int palindrome(int n)//判断回文数
{
	int sum=0;
	while(n>0)
	{
		sum=sum*10+n%10;
		n/=10;
	}
	return sum;
}