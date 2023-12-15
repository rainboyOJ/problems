#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;

int main()
{
	string word,sentence;
	int len1,len2;
	int i,j;
	int ans=0,direction;

    getline(cin,word);//输入单词
	getline(cin,sentence);//输入句子
	len1=word.size();//记录单词的长度
	len2=sentence.size();//记录句子的长度

	for(i=0;i<len2;i++)
	{
		for(j=0;j<len1;j++)
		{
			if(toupper(sentence[i+j])!=toupper(word[j]))	break;//若字符不匹配退出循环，再从第i+1个开始判定
			/*toupper()为将字符从小写转为大写的库函数*/
			if(i>0&&sentence[i-1]!=' ')	break;//若第i个字符不是文章首且前一个字符不是空格，则不是独立单词，退出循环
		}
		if(j==len1&&(sentence[i+j]==' '||j+i==len2))//若循环判定通过，且该单词词尾为文章尾或后有空格
		{
			ans++;//累加满足条件单词数
			if(ans==1)//若第一次出现
				direction=i;//记录位置
		}
	}
	if(ans)	cout<<ans<<" "<<direction<<endl;
	else	cout<<"-1"<<endl;

    return 0;
}