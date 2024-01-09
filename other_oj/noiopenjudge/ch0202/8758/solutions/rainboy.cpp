#include <bits/stdc++.h>
using namespace std;

/**
 * 把一个数 n 转成二进制存到c数组里
 */
int tobin(int n ,bool c[]){
    int cnt = 0;
    while ( n ) {
        c[cnt++] = n % 2;
        n /= 2;
    }
    return cnt; //转后有多少位
}

/**
 * 对num进行这种拆分
 */
void dfs(int num){
    if( num == 0){
        printf("0");
        return ;
    }
    if(num == 1){  //边界 
        printf("2(0)");
        return;
    }
    else if ( num == 2){
        printf("2");
        return;
    }

    bool c[20]; // n最大为20000,转成bin 只要15位 20一定够用
    int cnt = tobin(num ,c);

    int last; //最后一个位置的1
    for(int i=0;i<=cnt-1;++i){
        if( c[i] ){
            last = i;
            break;
        }
    }
    //从高位到低位遍历
    for(int i = cnt - 1;i>=0;--i){ 
        if( !c[i]) continue; //是0 什么也不做
        if( i == 1)
            printf("2"); //边界
        else {
            printf("2(");
            dfs(i);
            printf(")");
        }
        if( i != last)
            printf("+");
    }
    
}
int main(){
    int n;
    scanf("%d",&n);
    dfs(n);
    return 0;
}
