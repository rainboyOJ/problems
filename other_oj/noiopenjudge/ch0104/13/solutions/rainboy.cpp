#include <cstdio>
int main(){
    double x;
    scanf("%lf",&x);
    if (  x < 5){
        printf("%0.3lf",-x+2.5);
    }
    else if( x < 10)
        printf("%0.3lf",2-1.5*(x-3)*(x-3));
    else 
        printf("%0.3lf",x/2-1.5);
    return 0;
}
