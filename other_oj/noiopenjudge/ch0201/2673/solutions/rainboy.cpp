#include <bits/stdc++.h>
using namespace std;

int _rank[]  ={0,1,2,3,4,5};

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5


/* 第i名选手是不是正确 */
bool isright(int i){
    int a = _rank[i];
    if( a == 1){
        return _rank[1] == E;
    }
    else if ( a == 2){
        return _rank[2] == B;
    }
    else if( a == 3){
        return _rank[5] == A;
    }
    else if( a == 4){
        return _rank[1] != C;
    }
    else 
        return _rank[1] ==D;
}

/* 挑选A,B ... 的名次 */
int pick(int a){
    int i;
    for(i=1;i<=5;i++){
        if( _rank[i] == a)
            return i;
    }
    return -1;
}

int main(){
    
    do {
        if(
                ( _rank[2] != E && _rank[3] !=E) &&
                ( isright(1) ) &&
                ( isright(2) ) &&
                ( isright(3) == false ) &&
                ( isright(4) == false ) &&
                ( isright(5) == false ) 
                ){
            int i;
            for(i=1;i<=5;i++){
                printf("%d\n",pick(i));
            }
        }

    }
    while( next_permutation(_rank+1, _rank+6));
    return 0;
}
