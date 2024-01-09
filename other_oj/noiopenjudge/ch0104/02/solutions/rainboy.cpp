#include <cstdio>

int main(){
    double a;
    scanf("%lf",&a);
    if( a < 0)
        a = -a;
    printf("%0.2lf",a);
    return 0;
}

