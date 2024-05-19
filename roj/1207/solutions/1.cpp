#include <iostream>
using namespace std;

int main() {
    int a,b;
    std::cin >> a >> b;
    int ans = 1;
    int c = a;
    if( c > b) c = b;
    // c是a,b中的最 小值

    for(int i = 1;i <= c ;++i ) // i: 1->c
    {
        if( a % i == 0 && b % i == 0)
            ans = i;
    }
    cout << ans ;

    return 0;
}
