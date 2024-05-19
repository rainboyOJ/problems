//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-21 14:41:09
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];

void print(int cnt,int num) {
    for(int i = 1;i <= cnt ;++i ) // i: 1->cnt
    {
        cout << num<< " ";
    }
}
int main (int argc, char *argv[]) {
    std::cin >> n;
    if( n > 10) {
        cout << 100 <<endl;
        return 0;
    }
    int cnt = 0;
    for(int i =0;i<=5;i++) { //2
        for(int j = 0;j <= 3 ;++j ) // 3
        {
            for(int k = 0;k <= 2 ;++k ) // 5
            {
                for(int l = 0;l <= 1 ;++l ) // 7
                {
                    if( i*2 + j *3 + k*5 + l *7 == n)
                    {
                        print(i,2);
                        print(j,3);
                        print(k,5);
                        print(l,7);
                        std::cout  << "\n";

                        cnt++;
                    }
                }
            }
        }
    }
    std::cout << cnt << "\n";


    return 0;
}
