#include "testlib.h"
#define MAXN 100010
using namespace std;

int n,k,stdk,usr[MAXN];
bool not_prime[MAXN],f;

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	n = inf.readInt();
	k = ouf.readInt();
	stdk = ans.readInt();
	if (k!=stdk)
	{
		quitf(_wa, "Your solution is worse than the standard one!QAQ");
	}
	else
	{
		for (int i=2;i<=n+1;i++) usr[i]=ouf.readInt(1,k);
		for (int i=2;i<=n+1&&!f;i++)
		{
			if (not_prime[i]) continue;
			for (int j=(i<<1);j<=n+1&&!f;j+=i)
			{
				not_prime[j]=true;
				if (usr[i]==usr[j]) f=true;
			}
		}
		if (f) quitf(_wa, "Wrong Answer!QAQ");
		else quitf(_ok, "Your solution is acceptable!^ ^");
	}
	return 0;
}