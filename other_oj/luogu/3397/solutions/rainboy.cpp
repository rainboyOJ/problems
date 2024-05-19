#include <iostream>
using namespace std;

const int maxn = 1e3+5;

int n,m;

int d[maxn][maxn];
int s[maxn][maxn];

void set_d(int i,int j,int v) {
    d[i][j] += v;
}

void matrix_add(int xi,int yi,int xj,int yj,int v) {
    set_d(xi,yi,v);
    set_d(xj+1,yj+1,v);
    set_d(xi,yj+1,-v);
    set_d(xj+1,yi,-v);
}

int main() {
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int a,b,c,d;
        std::cin >> a >> b >> c >> d;
        matrix_add(a,b,c,d,1);
    }

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= n ;++j ) // j: 1->n
        {
            s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + d[i][j];
            cout << s[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
