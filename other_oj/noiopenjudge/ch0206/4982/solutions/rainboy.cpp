#include <iostream>
using namespace std;
typedef  long long ll;
int n;

ll f[3][25][55][55];
// f[state][step][x][y]  表示到以state状态到达x,y,且走了step步

// 0 表示从下一层,x-1,到达这一层x层
// 1 表示从左边的点,来到
// 2 表示从右边的点来到

int sx = 1;
int sy = 22;
long long ans;

void print(int a,int b,int c,int d) 
{
    return;
    int t = f[a][b][c][d];
    if( t == 0) return;
    cout << "f[" << a << "]";
    cout << "[" << b << "]";
    cout << "[" << c << "]";
    cout << "[" << d << "]";
    cout << "=" << t << endl;
}


int main() {
    cin >> n;
    f[0][0][sx][sy]=1;

    int st= sy-n;
    int ed= sy+n;

    //i表示到达这一层
    for(int i = 1;i<=n;i++) {
        //枚举step
        for(int step = 1 ;step <= n;++step)
        {

            //枚举 这一层从下一层上来
            for(int j = st; j<=ed;j++) {
                f[0][step][i][j] += f[0][step-1][i][j] + f[1][step-1][i][j] + f[2][step-1][i][j];
                print(0,step,i,j);
            }

            //枚举从左边来
            for(int j = st; j <= ed;j++)
            {
                f[1][step][i][j] += f[0][step-1][i][j-1] + f[1][step-1][i][j-1];
                print(1,step,i,j);
            }
            //枚举从左边来
            for(int j = ed; j >= st;j--)
            {
                f[2][step][i][j] += f[0][step-1][i][j+1] + f[2][step-1][i][j+1];
                print(2,step,i,j);
            }

            for(int j = st; j <= ed;j++)
                if(step == n)
                {
                    ans += f[0][step][i][j];
                    ans += f[1][step][i][j];
                    ans += f[2][step][i][j];
                }
        }
    }
    cout << ans << endl;

    return 0;
}
