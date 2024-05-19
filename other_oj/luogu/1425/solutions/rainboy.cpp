#include <iostream>
using namespace std;

int main () {
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    int e = (c * 60 +d) - (a*60+b); 
    cout << e/60<< " " << e % 60;
    return 0;
}

