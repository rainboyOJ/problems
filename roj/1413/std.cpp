#include<iostream>
using namespace std;
int judge(int x,int B);

int main()
{
	int a,b,c;
	int i;
	
	cin>>a>>b>>c;
	for(i=2;i<=40;i++)//枚举2-40进制
		if(judge(a,i)*judge(b,i)==judge(c,i))//找到使a*b=c成立的最小进制B
		{
			cout<<i<<endl;
			return 0;
		}
	cout<<0<<endl;
	return 0;
}

int judge(int x,int B)
{
	int value=1,num=0;
	while(x!=0)//将一个数化为B进制数
	{
		if((x%10)>=B)//B进制下不可能出现大于等于B的数位
			return 99999;
		num+=((x%10)*value);
		value*=B;
		x/=10;
	}
	return num;
}