#include<iostream>
#include<cmath>
#include<string>
using namespace std;
bool prime(int x);

int main()
{
	string str;
	int a[26]={0};
	int max=0,min=9999;
	int i;
	
	cin>>str;//输入字符串
	for(i=0;i<str.length();i++)//统计各字母出现次数
		a[str[i]-'a']+=1;
	for(i=0;i<26;i++)//统计最多、最少字母的出现次数
	{
		if(max<a[i])
			max=a[i];
		if(min>a[i]&&a[i]!=0)
			min=a[i];
	}
	if(prime(max-min))
		cout<<"Lucky Word"<<endl<<(max-min)<<endl;
	else
		cout<<"No Answer"<<endl<<0<<endl;
	return 0;
}

bool prime(int x)//判断素数
{
	int i;
	if(x<2)
		return false;
	else
		for(i=2;i<=sqrt(x);i++)
			if(x%i==0)
				return false;
	return true;
}