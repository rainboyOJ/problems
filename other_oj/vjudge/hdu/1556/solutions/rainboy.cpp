#include <iostream>
#include <cstring>
using namespace std;

const int maxn= 1e5+5;
int d[maxn];// 差分数组

int n;
int main() {

    while (1) {
        std::cin >> n;
        if( n == 0) break;
        memset(d,0,sizeof(d));
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            int a,b;
            std::cin >> a >> b;
            d[a] += 1;
            d[b+1] -= 1;
        }
        int sum = 0;
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            sum += d[i];
            cout << sum << " ";
        }
        cout <<endl;
    }

    return 0;
}
