#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

bool v[30];

int main()
{
	freopen("decode9.in","w",stdout);
	srand(time(0));
	int N=rand()%10000+1;
	for (int i=0; i<N; ++i)
	{
		int x=rand()%27;
		if (x<26) printf("%c",x+'A');
		else printf(" ");
	}
	printf("\n");
	for (int i=0; i<26; ++i)
	{
		int x=rand()%26;
		while (v[x]) x=rand()%26;
		v[x]=1;
		printf("%c",x+'A');
	}
	printf("\n");
	return 0;
}