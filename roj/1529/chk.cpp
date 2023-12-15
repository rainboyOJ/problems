#include "testlib.h"
#include <iostream>
#include <cstdio>
using namespace std;

const int MaxM = 200000;

int t, n, m;
int ev[MaxM + 1], eu[MaxM + 1];

inline int getEV(int i)
{
	if (t == 1)
		return i > 0 ? ev[abs(i)] : eu[abs(i)];
	else
		return ev[i];
}
inline int getEU(int i)
{
	if (t == 1)
		return i > 0 ? eu[abs(i)] : ev[abs(i)];
	else
		return eu[i];
}

int main(int argc, char **argv)
{
	registerTestlibCmd(argc, argv);

	t = inf.readInt(1, 2, "t");
	n = inf.readInt(1, 100000, "n");
	m = inf.readInt(0, 200000, "m");

	for (int i = 1; i <= m; i++)
		ev[i] = inf.readInt(1, n, "v[i]"), eu[i] = inf.readInt(1, n, "u[i]");

	string jp = ans.readString(), pp = ouf.readString();
	if (jp != pp)
		expectedButFound(_wa, jp, pp);
	if (jp == "NO")
		quitf(_ok, "no solution");

	static bool book[MaxM + 1];
	static int p[MaxM];
	for (int i = 0; i < m; i++)
	{
		p[i] = ouf.readInt();
		if (t == 1)
		{
			if (!(1 <= abs(p[i]) && abs(p[i]) <= m))
				quitf(_wa, "invalid p[i]");
		}
		else
		{
			if (!(1 <= p[i] && p[i] <= m))
				quitf(_wa, "invalid p[i]");
		}

		if (book[abs(p[i])])
			quitf(_wa, "invalid euler tour");
		book[abs(p[i])] = true;
	}

	for (int i = 0; i < m; i++)
		if (getEU(p[i]) != getEV(p[(i + 1) % m]))
			quitf(_wa, "invalid euler tour");

	quitf(_ok, "correct");
}
