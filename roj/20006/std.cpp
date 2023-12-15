#include <bits/stdc++.h>

using namespace std;

int main()
{
    char ch;
    int k=1;
    while(~scanf("%c",&ch))
    {
        if(ch=='"')
        {
            k&1?printf("``"):printf("''");
            k++;
        }
        else cout<<ch;
    }
    return 0;
}
