//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-13 21:45:56
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int x,y; //表示坐标

// direction up
int up_x = -1;
int up_y = 1;

int down_x = 1;
int down_y = -1;

int main (int argc, char *argv[]) {
    cin >> n;
    x = 1;
    y = 1;

    //fx 表示上一个点的方向
    int fx = up_x;
    int fy = up_y;
    for(int i =2;i <=n;i++) {
        x += fx;
        y += fy;

        if( x == 0 || y == 0) {
            if( x == 0) x = 1;
            if( y == 0) y = 1;

            //表明原来的方向是up
            if( fx == -1) {
                fx = down_x;
                fy = down_y;
            }
            else { //原来是down
                fx = up_x;
                fy = up_y;
            }
        }
    }
    cout << x  << "/" << y << endl;

    return 0;
}
