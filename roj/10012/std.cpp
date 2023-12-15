#include <bits/stdc++.h>
using namespace std;

int main()
{
    int h, m;
    scanf("%d:%d", &h, &m);
    m = h * 60 + m;
    m += 3 * 60 + 30;
    m %= 24 * 60;
    h = m / 60, m = m % 60;
    printf("%02d:%02d\n", h, m);
    return 0;
}