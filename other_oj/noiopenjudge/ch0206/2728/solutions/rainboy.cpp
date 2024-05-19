#include <iostream>
using namespace std;

int n,m;
int T;

int a[105][105];

void init() {
    cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= m ;++j ) // j: 1->m
        {
            cin >> a[i][j];
        }
    }
}

void work() {
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= m ;++j ) // j: 1->m
        {
            int t = a[i-1][j];
            if( t < a[i][j-1])
                t = a[i][j-1];
            a[i][j] +=t;
        }
    }

}

int main() {
    std::cin >> T;
    while(T--){
        init();
        work();
        cout << a[n][m]<< endl;
    }

    return 0;
}
