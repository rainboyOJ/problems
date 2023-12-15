#include<iostream>
using namespace std;
int calculate(int x,char z,int y);

int main()
{
	int x,y;
	char z;

	cin>>x>>z>>y;//x、y为运算数，z为运算符
	cout<<calculate(x,z,y)<<endl;//根据z进行计算，输出结果
	return 0;
}

int calculate(int x,char z,int y)
{
	if(z=='+')	return x+y;
	if(z=='-')	return x-y;
	if(z=='*')	return x*y;
	if(z=='/')	return x/y;
	if(z=='%')	return x%y;
}