#include <cstdio>

int main(){
    int a;
    scanf("%d",&a);
    double b;
    if( a <= 150 ){
        b = a * 0.4463;
    }
    else if( a <= 400){
        b = 150 * 0.4463 + (a-150) * 0.4663;
    }
    else {
        b = 150 * 0.4463 + (400-150) * 0.4663 + (a-400)*0.5663;
    }
    printf("%0.1lf",b);
    return 0;
}

