//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-05 10:47:17
// 直接枚举二进制
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];


// 数值a的pos位置 是否是1
bool is_1(int a,int pos) {

    return a & (1<<pos);

}

int main (int argc, char *argv[]) {
    std::cin >> n;
    m = (1<<n) - 1;

    for(int i = 0;i <= m ;++i ) // i: 0->m
    {
        // std::cout << i  << ": ";
        for(int j = n-1;j >= 0 ;--j ) // j: 0->n
        {
            if( is_1(i,j) )
                std::cout << 'Y';
            else
                std::cout << 'N';
        }
        std::cout << "\n";
    }

    return 0;
}
