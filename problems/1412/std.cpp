#include<iostream>
using namespace std;
bool judge(int x);

int main()
{
	int a=0,b=0;
	int i;

	for(i=1;i<=1000;i++)//枚举1-1000的数
		if(judge(i))//若i是A类数
			a++;
		else//若i是B类数
			b++;
	cout<<a<<" "<<b<<endl;
	return 0;
}

bool judge(int x)
{
	int a=0,b=0;
	while(x>0)//将一个数化为二进制数,并判断是A类数还是B类数
	{
		if(x%2)
			a++;//a统计1的个数
		else
			b++;//b统计0的个数
		x/=2;
	}

	return a>b;//
}