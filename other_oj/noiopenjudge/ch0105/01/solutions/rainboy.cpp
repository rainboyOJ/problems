#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    std::cin >> n;
    int sum = 0;
    for(int i=1;i<=n;++i){
        int t;
        std::cin >> t;
        sum += t;
    }
    double ans = sum * 1.0 / n;
    std::cout <<fixed <<  std::setprecision(2) << ans << std::endl;
    return 0;
}

