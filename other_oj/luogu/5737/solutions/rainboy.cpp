#include <iostream>
using namespace std;

int n;

int main()
{
    cin >> n;
    // 想一想,中间为什么是1?
    for(int i =2 ; 1 ;i++) {
        if( n % i == 0)
        {
            cout << n / i;
            return 0;
        }
    }
    return 0;
}
