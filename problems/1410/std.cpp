#include<iostream>
#include<cmath>
using namespace std;
bool judge(int x);

int main()
{
	int m,n;
	int i,j;
		
	cin>>m>>n;
	for(i=m;i<=n;i++)//从m枚举到n
		for(j=i;j>=2;j--)//从小到大找每个数的最大质因子
			if( (i%j==0) && judge(j) )//找到最大质因子
			{
				cout<<j;
				if(i!=n)
					cout<<",";
				break;
			}
	cout<<endl;
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