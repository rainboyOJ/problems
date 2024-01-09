#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    std::cin >> n;
    double sum = 0;
    for(int i=1;i<=n;++i){
        double a;
        std::cin >> a;
        sum += a;
    }
    std::cout << 
        fixed << setprecision(4)
        << sum / n
        << std::endl;


    return 0;
}
