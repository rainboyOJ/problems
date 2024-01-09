#include <bits/stdc++.h>
using namespace std;

int split(int i){
    int res =0;
    while( i ){
        int t = i % 10;
        res = (res | (1<<t));
        i /=10;
    }
    return (res>>1);
}

bool check(int i,int j,int k){
    int t=0;
    t |= split(i);
    t |= split(j);
    t |= split(k);
    if( t == ( 1<<9)-1)
         return 1;
    return 0;
}

int main(){
    int i,j,k;
    int ans=0;
    for(i=123;i<=999;i++){
        j = 2*i;
        k = 3*i;
        if( k <=999) {
            if(check(i, j,k))
                printf("%d %d %d\n",i,j,k);
        }
    }
    return 0;
}
