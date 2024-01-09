/* 
 *
 *  1
 *  2 3
 *  4 5 6
 *  7 8 9 10
 *  11 12 13 14 15
 * */
#include <cstdio>

int main(){
    int sum = 0;
    int n;
    scanf("%d",&n);
    int i,j,idx=0;
    for (i=1;1;i++){
       for(j=1;j<=i;j++){
           sum += i;
           idx++;
           if( idx == n){
               printf("%d\n",sum);
               return 0;
           }
       }
    }
    return 0;
}

