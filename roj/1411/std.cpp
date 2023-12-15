#include<iostream>
#include<cmath>
using namespace std;
bool judge(int x);
int inverted(int n);
int a[100000];

int main()
{
	int m,n;
	int i;
	int k=0;
	bool flag=false;
	
	cin>>m>>n;
	for(i=m;i<=n;i++)//从m枚举到n
		if( judge(i) && judge(inverted(i)) )//分别判断i以及i变换后是否是素数
		{
			k++;
			a[k]=i;
			flag=true;
		}
	if(flag)
	{
		for(i=1;i<k;i++)
			cout<<a[i]<<",";
		cout<<a[k]<<endl;
	}
	else
		cout<<"No"<<endl;
	return 0;
}

bool judge(int x)//判断素数
{
	int i=2;
	if(x==0||x==1)	return false;
	while( i<=floor(sqrt(x)) && (x%i!=0) )
		i++;
	if(i>floor(sqrt(x)))
		return true;
	return false;
}

int inverted(int n)//求倒序数
{
	int sum=0;
	while(n>0)
	{
		sum=sum*10+n%10;
		n/=10;
	}
	return sum;
}