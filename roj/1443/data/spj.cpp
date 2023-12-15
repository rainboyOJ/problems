#include "testlib.h"
#define MAXN 110

int a[MAXN],n,m,stdm,wa;bool ok;

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);

	while (!inf.eof())
	{
		m=stdm=0;n=inf.readInt();
		if (!n) break;
		while (!ouf.seekEoln()) a[++m]=ouf.readInt(1,n);
		while (!ans.seekEoln()) ans.readInt(),++stdm;
		if (m!=stdm){wa=1;break;}
		for (int i=1;i<=m;i++) if (a[i]<=a[i-1]) {wa=2;break;}
		if (wa) break;
		if (a[1]!=1||a[m]!=n){wa=5;break;}
		for (int k=2;k<=m;k++)
		{
			ok=false;
			for (int i=1;i<=k-1&&!ok;i++)
				for (int j=1;j<=k-1&&!ok;j++)
					if (a[k]==a[i]+a[j]) ok=true;
			if (!ok){wa=3;break;}
		}
		if (wa) break;
	}
	while (!ouf.eof()&&!wa)
	{
		char x=ouf.readChar();
		if (x>=33) wa=4;
	}
	if (wa==1) quitf(_wa,"Your sequence is longer or shorter than the standard one! QAQ");
	else if (wa==2) quitf(_wa,"Your sequence is not a monotone increasing sequence! QAQ");
	else if (wa==3) quitf(_wa,"Your sequence does not satisfy the requirement: for EACH k, ak=ai+aj! QAQ");
	else if (wa==5) quitf(_wa,"Your sequence does not satisfy the requirement: a0=1 ,am=n! QAQ");
	else if (wa==4) quitf(_wa,"Your output is more than the standard output! QAQ");
	else quitf(_ok,"Your output is acceptable! ^ ^");
	return 0;
}