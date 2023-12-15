#include<iostream>
#include<cmath>
using namespace std;
bool judge(int x);

int main()
{
	int n;
	int i;
	bool flag=true;
		
	cin>>n;
	for(i=2;i<=n-2;i++)//从2遍历到n-2
		if( judge(i+2) && judge(i) )//若存在素数对则输出
		{
			cout<<i<<" "<<i+2<<endl;;
			flag=false;
		}
	if(flag)//不存在素数对则输出empty
		cout<<"empty"<<endl;
	return 0;
}

bool judge(int x)//判断素数
{
	int i=2;
	for(i=2;i<=sqrt(x);i++)
		if(x%i==0)
			return false;
	return true;
}