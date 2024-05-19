//随机数据生成
#include <bits/stdc++.h>
using namespace std;


std::random_device rd;
std::default_random_engine __rnd(rd());

//生成[l,r]之间的随机整数
int rnd(int l,int r) {
    return __rnd() % (r-l+1) + l;
}

int main (int argc, char *argv[]) {
    int n = 5;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << char(rnd('a','f')) ;
    }
    cout << endl;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << char(rnd('a','f')) ;
    }
    cout << endl;
    return 0;
}
