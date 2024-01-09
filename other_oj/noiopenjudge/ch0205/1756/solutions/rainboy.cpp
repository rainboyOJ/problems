//八皇后
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int _map[10][10]={0};

int col[8];
int x1[100],x2[100];
int a[10];
int b[100]={0};
int cnt=0;
int idx = 0;

void save(){
    cnt++;
    b[cnt] =0;
    int i;
    for(i=1;i<=8;i++){
        b[cnt] = b[cnt]*10 + a[i];
    }
}

void set(int x,int y){
    _map[x][y] = 1;
    col[y] = 1;
    x1[x+y] = 1;
    x2[x-y+8] = 1;
}

void unset(int x,int y){
    _map[x][y] = 0;
    col[y] = 0;
    x1[x+y] = 0;
    x2[x-y+8] = 0;
}

bool is_ok(int x,int y){
    if( !col[y] && !x1[x+y] && !x2[x-y+8])
        return 1;
    return 0;
}

void dfs(int dep){
    if( dep == 8+1){
        save();
        return;
    }
    int i;
    for(i=1;i<=8;i++){
        if( is_ok(dep,i)){
            set(dep,i);
            a[dep] = i;
            dfs(dep+1);
            unset(dep,i);
        }
    }
}

int main(){
    dfs(1);
    sort(a+1,a+92+1);
    int n,i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        printf("%d\n",b[t]);
    }

    return 0;
}
