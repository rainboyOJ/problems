#include <bits/stdc++.h>
using namespace std;

int A,B,C;
bool vis[105][105] = {0};
char opts[10][100] = { "FILL(1)", "FILL(2)", "DROP(1)", "DROP(2)", "POUR(1,2)", "POUR(2,1)" };

struct sta {
    int a,b,step;
};

struct _NOW {
    int opt;
    int pre_a,pre_b;
} pre[105][105];


void init(){
    memset(pre,-1,sizeof(pre));
    scanf("%d%d%d",&A,&B,&C);
} 
sta do_opt(int idx,sta now){
    int a = now.a;
    int b = now.b;
    if( idx == 0){
        return sta{A,b};
    }
    else if ( idx == 1){
        return sta{a,B};
    }
    else if ( idx == 2){
        return sta{0,b};
    }
    else if ( idx == 3){
        return sta{a,0};
    }
    else if ( idx == 4){
        int sheng = B - b;
        if( a <= sheng){
            b += a;
            a = 0;
        }
        else {  // a > sheng
            b = B;
            a -= sheng;
        }
        return sta{a,b};
    }
    else {
        int sheng = A - a;
        if( b <= sheng){
            a += b;
            b = 0;
        }
        else { // b > sheng
            a = A;
            b -= sheng;
        }
        return sta{a,b};
    }
}
int end_a,end_b;

int bfs(){
    queue<sta> q;
    q.push({0,0,0});
    vis[0][0] = 1;
    while( !q.empty()){
        sta h = q.front(); q.pop();
        int i;
        for(i = 0 ;i < 6;i++){
            sta now = do_opt(i, h);
            if( now.a == C ||  now.b == C){
                pre[now.a][now.b] = { i,h.a,h.b };
                end_a = now.a;
                end_b = now.b;
                return h.step +1;
            }
            if( vis[now.a][now.b] == 0){
                pre[now.a][now.b] = { i,h.a,h.b };
                now.step = h.step+1;
                vis[now.a][now.b] = 1;
                q.push(now);
            }
        }
    }
    return -1;
}


int main(){
    init();
    int ans = bfs();
    if( ans == -1){
        printf("impossible");
        return 0;
    }
    printf("%d\n",ans);
    vector<int>  v;
    while (end_a !=0 || end_b != 0){
        v.push_back( pre[end_a][end_b].opt);
        int a  = pre[end_a][end_b].pre_a;
        int b  = pre[end_a][end_b].pre_b;
        end_a = a;
        end_b = b;
    }
    int i;
    for(i= v.size()-1;i>=0;i--){
        printf("%s\n", opts[v[i]]);
    }

    return 0;
}
