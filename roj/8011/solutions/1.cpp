//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-01 14:24:46
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int d,h,m;

int main (int argc, char *argv[]) {
    std::cin >> d >> h >> m;

    long long end = (d-11)*24*60 + h *60 + m;
    long long start = 11*60 + 11;
    long long sub = end - start;
    if( sub < 0) 
        cout << -1;
    else
        cout << sub;
    return 0;
}
