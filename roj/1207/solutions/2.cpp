#include <iostream>
using namespace std;

int main() {
    int a,b;
    std::cin >> a >> b;
    int ans = 1;
    while( b != 0 ) {
        int c = b;
        b = a % b;
        a = c;
    }
    cout << a;

    return 0;
}
