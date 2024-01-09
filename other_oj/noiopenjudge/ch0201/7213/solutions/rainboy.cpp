#include <bits/stdc++.h>
using namespace std;

int d,n;
int m[1200][1200];
int ans = 0;

bool in_map(int x,int y){
    if( x >=0 && x <=1024 && y >=0 && y <=1024)
        return 1;
    return 0;
}

int _set(int x,int y,int val){
    int i,j;
    int _max=0;

    for(i=x-d;i<=x+d;i++){
        for(j=y-d;j<=y+d;j++){
            if( in_map(i,j) ){
                m[i][j] += val;
                _max = max(_max,m[i][j]);
            }
        }
    }
    return _max;
}

void init(){
    scanf("%d%d",&d,&n);
    int i;
    for(i=1;i<=n;i++){
        int t1,t2,t3;
        scanf("%d%d%d",&t1,&t2,&t3);
        ans = max(ans,_set(t1,t2,t3));
    }
}

int main(){
    init();
    int i,j;
    int cnt=0;
    for(i=0;i<1025;i++){
        for(j=0;j<1025;j++){
            if( m[i][j] == ans)
                cnt++;
        }
    }
    

    printf("%d %d\n",cnt,ans);
    return 0;
}
