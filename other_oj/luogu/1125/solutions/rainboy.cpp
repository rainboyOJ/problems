#include <iostream>
using namespace std;

int n;

//标准判断a是否是素数的函数
//这个一定要会,在比赛中,这个函数就像1+1一样
bool prime(int a){
    if(a < 2) return 0;
    for(int i =2;i*i <= a;i++)
    {
        if( a % i == 0)
            return 0;
    }
    return 1;
}
int main() {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;

        if( prime(t))
            cout << t<< " ";
    }

    return 0;
}

