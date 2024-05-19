#include <iostream>
using namespace std;

int n;

long long f[100][100];
int sx = 1;
int sy = 40;

struct node {
    int x,y;
};

node p[1000];
int cnt;

void push(int x,int y) {
    ++cnt;
    p[cnt].x = x;
    p[cnt].y = y;
}

int abs(int a) {
    if( a < 0) return -a;
    return a;
}

//ｘ，ｙ到起点ｓｘ，ｓｙ的距离
int mhd_dis(int x,int y){
    return abs(x-sx) + abs(y-sy);
}





int main() {
    cin >> n;

    //先存走１步能到的点，再存走两步能到的点
    for(int s =1;s<=20;s++) {
        for(int i = sx ; i<=sx+20;i++)
        {
            for(int j = sy-20 ;j<= sy+20;j++) {
                if( mhd_dis(i,j) == s){
                    push(i,j);
                }
            }
        }
    }

    // for(int i =1;i<=cnt;i++)
    // {
    //     cout<< p[i].x << " " << p[i].y << endl;
    // }
    
    f[sx][sy] = 1;
    long long ans = 0;
    for(int i =1;i<=cnt;i++) {
        int x = p[i].x;
        int y = p[i].y;

        if( mhd_dis(x,y) > n) break;

        int tx,ty;

        tx = x-1;
        ty = y;
        f[x][y] += f[tx][ty];

        tx = x;
        ty = y-1;
        f[x][y] += f[tx][ty];

        tx = x;
        ty = y+1;
        f[x][y] += f[tx][ty];

        cout << x << " " << y;
        cout << " " << f[x][y] << endl;
        // cout << x << " " << y << " " << f[x][y] << endl;
        if( mhd_dis(x,y) == n){
            ans += f[x][y];
        }
    }
    cout << ans << endl;
    return 0;
}
