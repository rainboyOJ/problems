#include<iostream>
#include<cstdio>
using namespace std;

int A[105][105];
int B[105][105];
int m, n, r, s;

void init() {

    scanf("%d%d",&m,&n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d",&A[i][j]);
    scanf("%d%d",&r,&s);
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= s; j++)
            scanf("%d",&B[i][j]);
}

int _abs(int a){
    return a<0 ? -a:a;
}

int check(int x,int y){
    int sum = 0;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= s; j++)
            sum += _abs(B[i][j] - A[x+i-1][y+j-1]);
    return sum;
}

int main() {

    init();

    int x, y, max_ = 10000000,maxx,maxy;
    for (y = 1; y <= m-r+1; y++)
        for (x = 1; x <= n-s+1; x++) { //meiju
            int t = check(y,x);
            if ( t < max_) {
                max_ = t;
                maxx = y;
                maxy = x;
            }
        }

    for(int i =maxx;i <= maxx+r-1  ;i++){
        for(int j = maxy;j <=maxy+s-1;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    return 0;
}
