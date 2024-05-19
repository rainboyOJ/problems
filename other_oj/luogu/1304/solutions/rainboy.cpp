#include <iostream>
using namespace std;

int n;

bool prime(int a) {
    if(a <= 1) return 0;
    for(int i =2;i * i <= a;i++)
    {
        if( a % i == 0) return 0;
    }
    return 1;
}

//函数, 分解a
void work(int a) {
    // cout << a << endl;
    for(int i =2 ;i <= a;i++)
    {
        // cout << i << " " << a -i << endl;
        if( prime(i) && prime(a-i))
        {
            cout << a << "=";
            cout << i << "+";
            cout << a-i<< endl;
            return ;
        }
    }
}

int main() {
    std::cin >> n;
    // 想一想,为什么 i += 2
    for(int i = 4;i<= n;i += 2)
    {
        work(i);
    }
    return 0;
}
