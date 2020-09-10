#include <iostream>
#include <ctime>
using namespace std;

#define MaxN 1000000

char s[MaxN+5];
int main()
{
    srand(time(NULL));
    freopen("power.in", "w", stdout);
    int n = rand()%8+1;
    for (int i=1; i<=n; i++)
    {
        int m = (rand()*rand())%MaxN+1;
        int p = (rand()*rand())%MaxN+1;
        while (p>m/8) p = (rand()*rand())%MaxN+1;
        for (int j=1; j<=p; j++) s[j] = rand()%26+'a';
        for (int j=1; j<=m/p; j++)
            for (int k=1; k<=p; k++) putchar(s[k]);
        puts("");
    }
    printf(".\n");
    return 0;
}
