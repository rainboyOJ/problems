//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-20 18:42:27
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int a[maxn];
long long cnt,x;
int n;
int main (int argc, char *argv[]) {
    std::cin >> x >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( x == 6 || x ==7){

        }
        else {
            cnt++;
        }
        x++;
        if(x == 8)
            x = 1;
    }
    cout << cnt * 250 <<endl;

    return 0;
}
