#include <bits/stdc++.h>
using namespace std;

vector<int> opt_list;
const int INF = 0x7fffffff;
int ans = INF;
vector<int> ans_stack(20);
int max_height;
int n;

int wall[20];

void init(){
    scanf("%d",&n);
    if( n == 0) return;
    char str[100];
    int i,j;
    for(i=1;i<=n;i++){
        scanf("%s",str+1);
        int res=0,t = 0;
        for(j=1;j<=n;j++){
            res <<=1;
            if( str[j] == 'y' )
                res |= 1;
        }
        wall[i] = res;

        /* 输出测试 */
        //bitset<15> tmp(wall[i]);
        //cout << tmp << endl;
    }
    /* 生成 opt_list */
    int max_state = (1<<n)-1;
    for(i=max_state;i >0;i = (i-1) &max_state){ // 枚举子集
        opt_list.push_back(i);
    }
    opt_list.push_back(0);

    max_height = (1<<n)-1;
}

/* 计算1的数量 */

int bin_count(int x){
    int cnt = 0;
    x &= max_height;
    for( ; x; x = (x-1) &x){
        cnt++;
    }
    return cnt;
}


void dfs(int dep){

    if( dep == n+1){
        if( (wall[dep-1] & max_height) == max_height ){
            /* 计算结果 */
            int t = 0;
            int i;
            for(i=1;i<=n;i++){
                t += bin_count(ans_stack[i]);
            }
            ans = min(ans,t);
        }
        return ;
    }

    /* 记录 3 行的状态 */
    int up = wall[dep-1];
    int now = wall[dep];
    int down = wall[dep+1];

    /* 推算出操作 */
    int opt = 0;
    int i;
    for(i=0;i<n;i++){
        if( ( (1<<i) & up ) == 0 ){
            opt |= (1<<i);
        }
    }
    opt &= max_height;

    int _up = max_height;
    int _now = ((((opt<<1)^now) ^opt) ^(opt>>1) ) & max_height;
    int _down = ( down ^ opt) & max_height;

    ans_stack[dep] = opt;
    wall[dep-1] = _up;
    wall[dep] = _now;
    wall[dep+1] = _down;
    dfs(dep+1);
    wall[dep-1] = up;
    wall[dep] = now;
    wall[dep+1] = down;

}



int main(){
    init();
    if( n== 0){
        printf("inf");
        return 0;
    }
    /* 枚举第一行的操作 */
    int line_1 = wall[1];
    int line_2 = wall[2];
    reverse(opt_list.begin(), opt_list.end());
    for( auto x : opt_list){
        ans_stack[1] = x;
        wall[1] = ((((x<<1)^line_1 ) ^x) ^(x>>1) ) & max_height;
        wall[2] = (line_2 ^x) & max_height;
        dfs(2);
    }
    if( ans != INF)
        printf("%d",ans);
    else
        printf("inf");
    return 0;
}
