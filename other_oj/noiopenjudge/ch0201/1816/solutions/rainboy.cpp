#include <bits/stdc++.h>
using namespace std;
char opts[100][100] = { "ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI" };

/* 每个操作影响那些时钟 */
vector<int> opt_effect[10];
/* 每种操作的次数 */
int opt_cnt[10];

int clock_state[10];
void init(){
    int i,j;
    for(i=1;i<=9;i++){
        scanf("%d",&clock_state[i]);
    }
    for(i=0;i<9;i++){
        int len = strlen(opts[i]);
        for(j=0;j<len;j++){
            opt_effect[i+1].push_back(opts[i][j]-'A'+1);
        }
    }
}

/* 是否可以 */
bool check(int effects[]){
    int i;
    for(i=1;i<=9;i++){
        if( (clock_state[i] + effects[i]) % 4 !=0)
            return 0;
    }
    return 1;
}


bool dfs(int dep){
    if( dep == 10){
        int clock_effect[10] = {0};
        /* 对每个时钟的影响 */
        int i;
        for(i=1;i<=9;i++){ // 遍历: 每一种操作
            if( !opt_cnt[i] )
                continue;

            for( auto x : opt_effect[i]){
                clock_effect[x] += opt_cnt[i];
            }
        }
        if( check(clock_effect)){
            int j;
            for(i=1;i<=9;i++){
                for(j=1;j<=opt_cnt[i];j++){
                    printf("%d ",i);
                }
            }
            return 1;
        }

        return 0;
    }
    int i;
    for(i=0;i<4;i++){
        opt_cnt[dep] = i;
        if(dfs(dep+1))
            return 1;
    }
    return 0;
}
int main(){
    init();
    dfs(1);
    return 0;
}
