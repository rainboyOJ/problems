#include "testlib.h"

long long usr[10],ar[10],ua,ub=1,x;
int arpt,a,b;

long long gcd(long long a,long long b){return !b?a:gcd(b,a%b);}

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	a=inf.readInt();b=inf.readInt();
	x=gcd(a,b);a/=x;b/=x;
	while (!ans.seekEof()) ar[++arpt]=ans.readInt();
	for (int i=1;i<=arpt;i++) usr[i]=ouf.readInt();
	if (!ouf.seekEof())
	{
		quitf(_wa, "Your sequence is longer than the standard answer!QAQ");
	}
	else
	{
		if (usr[arpt]!=ar[arpt])
		{
			quitf(_wa, "The biggest one of your answer is worse than the standard answer!QAQ");
		}
		else
		{
			for (int i=1;i<=arpt;i++)
			{
				ua=usr[i]*ua+ub;ub*=usr[i];
				x=gcd(ua,ub);ua/=x;ub/=x;
			}
			if (ua!=a||ub!=b)
			{
				quitf(_wa, "The sum of fractions is not equal to the standard one!QAQ");
			}
			else
			{
				quitf(_ok ,"Your answer is acceptable!^ ^");
			}
		}
	}
	return 0;
}