#include <cstdio>

int main(){
    int k;
    scanf("%d",&k);
    double sum = 0,kk = k;
    int i;
    for (i=1;1;i++){
        sum += 1.0/i;
        if( sum > k){
            printf("%d",i);
            return 0;
        }
    }
    return 0;
}
