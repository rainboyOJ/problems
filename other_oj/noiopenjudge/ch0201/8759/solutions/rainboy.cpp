#include <bits/stdc++.h>
using namespace std;

int a,n,m,x;    

int up[20]; // 上车人数
int save[20];// 剩余人数

// t 2站上车的人数
int check(int t){
    up[1] = a;
    save[1] = a;
    save[2] = a;
    up[2] = t;
    int i;
    for(i=3;i<n;i++){
        up[i] = up[i-1]+up[i-2];
        save[i] = save[i-1] + up[i] - up[i-1];
    }
    if( save[n-1] == m)
        return 1;
    return 0;
}
int main(){
    scanf("%d%d%d%d",&a,&n,&m,&x);

    int i;
    for(i=0;1;i++){
        if( check(i)){
            printf("%d\n",save[x]);
            break;
        }
    }

    return 0;
}
