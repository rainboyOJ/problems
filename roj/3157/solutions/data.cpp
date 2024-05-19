//随机数据生成
#include <bits/stdc++.h>
using namespace std;

std::random_device rd;
std::default_random_engine __rnd(rd());

//生成[l,r]之间的随机整数
int rnd(int l,int r) {
    return __rnd() % (r-l+1) + l;
}

int main() {
    int n = rnd(4,7);//生成一个[4,7]之间的随机数
    int m = 4;
    std::cout << n << " ";
    cout << m << endl;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int l = rnd(1,n);
        int p = rnd(1,4);
        int s = rnd(1,n);
        cout << l << " ";
        cout << p << " ";
        cout << s << "\n";
    }

    return 0;
}

