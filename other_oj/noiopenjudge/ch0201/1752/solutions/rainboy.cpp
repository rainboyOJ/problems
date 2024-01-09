#include <bits/stdc++.h>
using namespace std;


int n;

int main(){
    scanf("%d",&n);
    int _min = 0x7f7f7f7f;
    int _max=0;

    /* 坑点 */
    if( n % 2 != 0){
        printf("%d %d\n",0,0);
        return 0;
    }

    int i,j;
    int max_chicken= n /2;
    int max_rabit = n/4;

    for(i=0;i<= max_chicken;i++){
        for (j=0;j<=max_rabit;j++){
            if(i * 2 + j * 4 == n){
                _min = min(_min,i+j);
                _max = max(_max, i+j);
            }
        }
    }
    printf("%d %d\n",_min,_max);
    return 0;
}
