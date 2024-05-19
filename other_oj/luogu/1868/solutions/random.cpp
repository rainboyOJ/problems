//随机数据生成
#include <bits/stdc++.h>
using namespace std;
int n;

std::random_device rd;
std::default_random_engine __rnd(rd());

int rnd(int l,int r) {
    return __rnd() % (r-l+1) + l;
}

int main (int argc, char *argv[]) {
    n = rnd(3,5);
    cout << n << endl;
    
    int end =  100;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int l = rnd(1,end);
        int r = rnd(l,end);
        cout << l <<" " << r << endl;
    }

    return 0;
}
