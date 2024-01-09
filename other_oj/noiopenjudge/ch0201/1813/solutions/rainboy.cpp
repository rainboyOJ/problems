#include <bits/stdc++.h>
using namespace std;

vector<int> opt_list;
vector<int> ans(10);

int lamb[10];

void init(){
    int i,j;
    int n = 5;
    for(i=1;i<=n;i++){
        int res=0,t = 0;
        for(j=1;j<=n+1;j++){
            scanf("%d",&t);
            res <<=1;
            if( t )
                res |= 1;
        }
        lamb[i] = res;
    }
    /* 生成 opt_list */
    n = (1<<6)-1;
    for(i=n;i >0;i = (i-1) &n){ // 枚举子集
        opt_list.push_back(i);
    }
    opt_list.push_back(0);
}


const int max_height = (1<<6)-1;
bool dfs(int dep){

    if( dep == 5+1){
        if( (lamb[dep-1] & max_height) == 0 ){
            /* 输出结果 */
            int i,j;
            for(i=1;i<=5;i++){
                int t = ans[i];
                for(j=5;j>=0;j--){
                    printf("%d ",(t & (1<<j))? 1 :0 );
                }
                printf("\n");
            }

            return 1;
        }

        return 0;
    }

    /* 记录 3 行的状态 */
    int up = lamb[dep-1];
    int now = lamb[dep];
    int down = lamb[dep+1];

    for(auto x : opt_list){
        int _up = (up^x) & max_height ;
        if( dep == 1 || _up == 0){
            int _down = (down ^x) & max_height;
            int _now = ((((x<<1)^now ) ^x) ^(x>>1) ) & max_height;

            lamb[dep-1] = _up;
            lamb[dep] = _now;
            lamb[dep+1] = _down;
            ans[dep] = x;
            if( dfs(dep+1) )
                return 1;
            lamb[dep-1] = up;
            lamb[dep] = now;
            lamb[dep+1] = down;
        }
    }
    return 0;
}



int main(){
    init();
    bool bol = dfs(1);
    //printf("%d\n",bol);
    return 0;
}
