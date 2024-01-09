#include <bits/stdc++.h>
using namespace std;

#define dir_up 0
#define dir_down 1

struct _dir {
    int x,y;
}dir[2] = {
    { -1,1},
    { 1,-1},
};

int main(){

    

    int n;
    scanf("%d",&n);
    int a=1,b=1;
    int i;



    int pre_dir = dir_up;
    bool turn_dir_flag =0;
    for(i=2;i<=n;i++){
        //printf("%d/%d\n",a,b);
        if( a == 1 && !turn_dir_flag){
            pre_dir = dir_down;
            turn_dir_flag = true;
            b++;
            continue;
        }
        else if( b == 1 && !turn_dir_flag){
            turn_dir_flag = true;
            a++;
            pre_dir = dir_up;
            continue;
        }
            turn_dir_flag = 0;
        a += dir[pre_dir].x;
        b += dir[pre_dir].y;
    }
    printf("%d/%d\n",a,b);
    return 0;
}
