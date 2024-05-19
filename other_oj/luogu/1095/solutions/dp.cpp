#include <bits/stdc++.h>
using namespace std;

int M,S,T;

const int maxn = 3e5+5;
int ans_time = 0x7fffffff;
int ans_len = -1;

int f[maxn][20]; // f[t][m] time,magic



int main(int argc, char const *argv[])
{
    cin >> M >> S >> T;

    int time_spend = 0 ;
    int walk_len= 0;
    // int magic_left = M;
    //不停的使用magic
    while( M >= 10) {
        M -= 10;
        S -= 60;
        walk_len += 60;
        time_spend += 1;
        if( S <= 0) {
            cout << "Yes" <<endl;
            cout << time_spend << endl;
            return 0;
        }
        if( time_spend >= T) {
            cout << "No" <<endl;
            cout << walk_len << endl;
            return 0;
        }
    }
    ans_len = walk_len;
    //这就变成了一个新的问题 
    // 在S路长下,初始magic 为 M ,剩余时间为 T - time_spend
    // f[t][i] 表示,时间为t,魔法为i的状态下最长走的路径的长度

    memset(f,-1,sizeof(f)); // -1 表示不可能
    f[0][M] = 0; // 起始状态
    for(int t = 0 ;t <= T - time_spend; t++)
    {
        for(int i = 0; i<= 13;i++) {
            if( f[t][i] == -1) continue;
            if( f[t][i] >= S) {
                if( ans_time > t + time_spend)  {
                    // cout << ">> "  <<  t   << " ";
                    // cout << f[t][i] << endl;
                    ans_time = t + time_spend;
                }
            }
            else ans_len = max(ans_len, f[t][i]+walk_len);
            if( i < 10 ) {
                f[t+1][i+4] = max(f[t+1][i+4], f[t][i]);
                f[t+1][i] = max(f[t+1][i], f[t][i] + 17);
            } 
            else {
                f[t+1][i-10] = max(f[t+1][i-1],f[t][i]+60);
            }
        }
    }


    if( ans_time == 0x7fffffff)
    {
        cout << "No" << endl;
        cout << ans_len << endl;
    }
    else {
        cout << "Yes" << endl;
        cout << ans_time << endl;
    }
    return 0;
}
