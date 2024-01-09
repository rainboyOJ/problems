/*============================================================================
* Title : openjudge 
* Author: Rainboy
* Time  : 2017-03-19 09:18
* update: 2017-03-19 09:18
* © Copyright 2017 Rainboy. All Rights Reserved.
*=============================================================================*/

#include <cstdio>
int m,n,x;

int fight_up(int n,int m){
    return m / n;
}

int use_x(int n,int m){
    int ans = m / n;
    if( m %n != 0 )
        ans++;
    return ans;
}

int main(){
    scanf("%d%d%d",&m,&n,&x);
    while(1){ // 能量元素不用完
        
        //1.使用x
        x -= use_x(n,m);
        if(x <0)
            break;
        //2. n上升
        n +=fight_up(n,m);
    }
    printf("%d",n);
    return 0;
}
