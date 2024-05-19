//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-01 15:05:20
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;

//a[1] 表示 d 的状态
//a[2] 表示 g 的状态
//a[3] 表示 z 的状态
int a[10];

//c对应的数字是哪一个
int find(char c) {
    if( c == 'D') return 1;
    if( c == 'G') return 2;
    return 3;
}


int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        char c1,c2;
        std::cin >> c1 >> c2;
        int t1 = find(c1);
        int t2 = find(c2);
        a[t1] +=1;
        a[t2] -= 1;
    }
    cout << "D " << a[1] << endl;
    cout << "G " << a[2] << endl;
    cout << "Z " << a[3] << endl;

    return 0;
}
