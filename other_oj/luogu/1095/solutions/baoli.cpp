#include <bits/stdc++.h>
using namespace std;

int M,S,T;

int ans_time = 0x7fffffff;
int ans_len = -1;

int idx;

void dfs(int m,int s,int t) {
    if( s <=0 || t == 0) {
        int walk_len = S - s;
        if( s <=0 ) { //succed
            if( ans_time > T-t) ans_time = T-t;
        }
        if( walk_len > ans_len) ans_len = walk_len;

        // cout << ++ idx  << ":  ";
        // cout << m << " ";
        // cout << s << " ";
        // cout << t << "\n";
        return ;
    }
    if( m >= 10) dfs(m-10,s-60,t-1);
    dfs(m,s-17,t-1);
    dfs(m+4,s,t-1);
}

int main(int argc, char const *argv[])
{
    cin >> M >> S >> T;
    dfs(M,S,T);
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
