#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
 
int change(int i)//大小写转换 
{
	return (i>='A'&&i<='Z')?i+'a'-'A':i;
}
 
 
int main()
{
	char key[120];
	char miwen[1200];
	int miwen_x[1200];//密文大小写 1小写 2大写 
	scanf("%s %s",key,miwen);
	int len=strlen(key);
	for(int i=0;i<=len-1;i++)
		key[i]=change(key[i]);
	for(int i=0;i<=strlen(miwen)-1;i++)
	{
		if(miwen[i]>='A'&&miwen[i]<='Z')
			miwen_x[i]=2;
		else
			miwen_x[i]=1;
		miwen[i]=change(miwen[i]);
	}
	
	char ans[1200];
	int j=0;
	for(int i=0;i<=strlen(miwen)-1;i++)
	{
		if(miwen[i]>=key[j])
			ans[i]=miwen[i]-key[j]+'a';
		else
			ans[i]='z'-(key[j]-miwen[i]-1);
		if(miwen_x[i]==2)
			ans[i]=ans[i]-('a'-'A');
		j++;
		if(j==len)
			j=0;
	}
	ans[strlen(miwen)]=0;
	printf("%s",ans);
	
			
	return 0;
}
