//八皇后
#include <cstdio>
#include <iostream>
using namespace std;

int _map[10][10]={0};
int idx = 0;

int col[8];
int x1[100],x2[100];

void print__map(){
	//if( idx >10) return;
    //printf("8o. %d\8",++idx);
    cout << "No. "<<(++idx) << endl;
    int i,j;
    for(i=1;i<=8;i++){
        for(j=1;j<=8;j++)
            cout << _map[j][i] << " ";
        cout << endl;
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
        print__map();
        return;
    }
    int i;
    for(i=1;i<=8;i++){
        if( is_ok(dep,i)){
            set(dep,i);
            dfs(dep+1);
            unset(dep,i);
        }
    }
}

int main(){
    dfs(1);
    return 0;
}
