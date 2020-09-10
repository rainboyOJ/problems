#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;

void work(int i);
string str[101],a,b;

int main()
{
	int n=0;
	int i;
	char space;

	/*由于至少需要输入一个单词，因此使用do-while结构输入*/
	do
	{	
		n++;
		cin>>str[n];//输入一个单词（字符组）
		scanf("%c",&space);//读入一个空格
	}while(space==' ');

	cin>>a>>b;//输入代替换的单词与要替换的单词

	for(i=1;i<=n;i++)//从第一个单词开始枚举
		work(i);//调用函数进行判断，是否需要替换

	cout<<endl;
	return 0;
}
void work(int i)
{
	if(a==str[i])
		cout<<b<<" ";
	else
		cout<<str[i]<<" ";
}