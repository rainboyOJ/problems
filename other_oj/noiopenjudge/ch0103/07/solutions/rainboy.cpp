// talk is cheap,show me your code
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    double x,a,b,c,d;
    std::cin >> x >> a >> b >> c >> d;
    double answer = a*x*x*x +b*x*x+c*x+d;
    cout << fixed << setprecision(7) << answer;
    return 0;
}
