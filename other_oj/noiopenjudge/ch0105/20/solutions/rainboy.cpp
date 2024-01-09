#include <cstdio>
int main(){
    double h;
    scanf("%lf",&h);
    double sum = -h;
    double fang = 0;
    int i;
    for (i=1;i<=10;i++){
        sum += 2*h;
        h = h /2;
    }
    printf("%g\n",sum);
    printf("%g",h);
    return 0;
}
