#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
int n;
char s[2000];
int cnt_1[2000];
char check_fbi(int l,int r){
    int len = r-l+1;
    int cnt = cnt_1[r] - cnt_1[l-1];
    if( cnt == len)
        return 'I';
    else if( cnt == 0)
        return 'B';
    return 'F';
}
void dfs(int l,int r){
    if( l == r){
        printf("%c", s[l] =='0' ? 'B' :'I');
        return;
    }
    int m = (l+r)>>1;
    dfs(l,m);
    dfs(m+1,r);
    printf("%c",check_fbi(l, r));
}

int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    int i,j;
    for(i=1;i<=(1<<n);++i){
        if( s[i] == '1')
            cnt_1[i]= cnt_1[i-1]+1;
        else
            cnt_1[i]= cnt_1[i-1];
    }
    dfs(1,1<<n);
    return 0;
}




