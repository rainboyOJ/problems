#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

int n,m,x,y,z,g[MAXN][MAXN];
bool f=true;
char usrans[MAXN],stdans[MAXN];
int usrseq[MAXN],stdseq[MAXN],pta,ptb,stdl,usrl;

int main(int argc, char * argv[])
{
	memset(g,0x7f,sizeof g);
	FILE *fi = fopen("input", "r"), *fo = fopen("user_out", "r"), *fa = fopen("answer", "r");
	fscanf(fi,"%d%d",&n,&m);
	for (int i=1;i<=n;i++) g[i][i]=0;
	for (int i=1;i<=m;i++)
	{
		fscanf(fi,"%d%d%d",&x,&y,&z);
		g[x][y]=g[y][x]=min(g[x][y],z);
	}
	fscanf(fa,"%s",stdans);
	if (stdans[0]=='N')
	{
		fscanf(fo,"%s",usrans);
		if (usrans[0]!='N'||usrans[1]!='o')
		{
			fprintf(stderr, "Format Wrong!QAQ\n");
			fprintf(stdout, "0\n");
			return 0;
		}
		fscanf(fo,"%s",usrans);
		if (usrans[0]!='s'||
			usrans[1]!='o'||
			usrans[2]!='l'||
			usrans[3]!='u'||
			usrans[4]!='t'||
			usrans[5]!='i'||
			usrans[6]!='o'||
			usrans[7]!='n'||
			usrans[8]!='.'
			)
		{
			fprintf(stderr, "Format Wrong!QAQ\n");
			fprintf(stdout, "0\n");
			return 0;
		}
		if (fscanf(fo,"%s",usrans)!=-1)
		{
			fprintf(stderr, "Format Wrong!QAQ\n");
			fprintf(stdout, "0\n");
			return 0;
		}
		fprintf(stderr, "Your answer is acceptable!^ ^\n");
		fprintf(stdout, "100\n");
		return 0;
	}
	else
	{
		do{
			int n=strlen(stdans),x=0;
			for (int i=0;i<n;i++) x=(x<<3)+(x<<1)+stdans[i]-'0';
			if (n) stdseq[++pta]=x;
		}while (fscanf(fa,"%s",stdans)!=-1);
		do{
			int n=strlen(usrans),x=0;
			for (int i=0;i<n;i++) x=(x<<3)+(x<<1)+usrans[i]-'0';
			if (n) usrseq[++ptb]=x;
		}while (fscanf(fo,"%s",usrans)!=-1);
		if (ptb<3)
		{
			fprintf(stderr, "The ring's length should be bigger than 3!QAQ\n");
			fprintf(stdout, "0\n");
			return 0;
		}
		stdseq[++pta]=stdseq[1];usrseq[++ptb]=usrseq[1];
		for (int i=1;i<=ptb;i++)
			if (usrseq[i]>n||usrseq[i]<1)
			{
				fprintf(stderr, "The number is out of range!QAQ\n");
				fprintf(stdout, "0\n");
				return 0;
			}
		for (int i=2;i<=pta;i++) stdl+=g[stdseq[i]][stdseq[i-1]];
		for (int i=2;i<=ptb;i++) usrl+=g[usrseq[i]][usrseq[i-1]];
		if (usrl==stdl)
		{
			fprintf(stderr, "Your answer is acceptable!^ ^\n");
			fprintf(stdout, "100\n");
			return 0;
		}
		else
		{
			fprintf(stderr, "Your answer is worse than the standard answer!QAQ\n");
			fprintf(stdout, "0\n");
			return 0;
		}
	}
	return 0;
}