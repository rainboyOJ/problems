#include <cstdio>

int main(){
    double t,sum = 0;
    int i;
    for(i=1;i<=12;i++){
        scanf("%lf",&t);
        sum += t; // => sum = sum +t
    }
    printf("$%0.2lf",sum / 12);
    return 0;
}
