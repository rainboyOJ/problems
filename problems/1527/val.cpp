#include "testlib.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	registerValidation();

	inf.readInt(1, 2, "t");
	inf.readEoln();
	int n = inf.readInt(1, 100000, "n");
	inf.readSpace();
	int m = inf.readInt(0, 200000, "m");
	inf.readEoln();

	for (int i = 1; i <= m; i++)
	{
		inf.readInt(1, n, "v[i]");
		inf.readSpace();
		inf.readInt(1, n, "u[i]");
		inf.readEoln();
	}

	inf.readEof();
}
