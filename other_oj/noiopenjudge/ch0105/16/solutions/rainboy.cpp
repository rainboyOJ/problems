#include <cstdio>

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    int i;
    double lilv = 1+k*0.01;
    double fangjia= 200;
    for (i=1;i<=20;i++){
        if( n*i*1.0 >= fangjia){
            break;
        }
        fangjia = fangjia * lilv;
    }
    if( i <= 20){
        printf("%d",i);
    }
    else
        printf("Impossible");
    return 0;
}
