//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-05 10:53:42
//二进制子集枚举
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];

bool is_1(int a,int pos) {
    return a & (1<<pos);
}

void print(int t) {
    for(int i = n-1;i>=0;i--) 
    {
        if( is_1(t,i))
            std::cout << '1' ;
        else
            std::cout << '0' ;
    }
    std::cout << "\n";
}

int main (int argc, char *argv[]) {
    std::cin >> n;
    int t = (1<<n)-1; // n 3
    int s = t;

    for( ;t != 0 ; t = (t-1) & s) {
        print(t);
    }
    print(0);
    return 0;
}
