#include<iostream>
#include<cstdio>
using namespace std;
int calculate(int x);

int main()
{
	int n,a;
	int i;
	double sum=0;

	cin>>n;//输入当月发送短信总次数n
	for(i=1;i<=n;i++)
	{
		cin>>a;//输入每次发送短信的字数
		sum+=calculate(a);//累加每次短信的资费
	}
	printf("%.1lf\n",sum/10.0);//将以角为单位的数转为以元为单位的数，输出结果
	return 0;
}

int calculate(int x)
{
	if(x%70==0)
		return x/70;
	else
		return x/70+1;
}
