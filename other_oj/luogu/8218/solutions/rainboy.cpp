#include <iostream>
using namespace std;

const int maxn = 1e5+5;

int n;
int m;
int a[maxn];

int main() {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t ;
        std::cin >> t;
        a[i] = t+a[i-1];
    }
    std::cin >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int l,r;
        std::cin >> l >> r;
        cout << a[r] - a[l-1] << endl;
    }


    return 0;
}
