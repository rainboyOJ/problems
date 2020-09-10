#include "testlib.h"

int main()
{
    registerValidation();
    int n = inf.readInt(2, 1e6 - 1); inf.readSpace();
    inf.readInt(1, n - 1); inf.readSpace();
    inf.readInt(1, 1e9 - 1); inf.readSpace();
    inf.readInt(1, n); inf.readEoln();
    inf.readEof();
    return 0;
}

