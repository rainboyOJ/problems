#include <cstdio>
#include <cmath>

double get_time(double x,double y){
    double len  = sqrt(x*x+y*y);
    return 2*len / 50;
}
double get_up_down_time(int num){
    return num +num*0.5;
}
int main(){
    int n;
    scanf("%d",&n);
    int i;
    double t1,t2;
    int t3;
    double time1 = 0;
    for (i=1;i<=n;i++){
        scanf("%lf%lf%d",&t1,&t2,&t3);
        time1 += get_time(t1,t2);
        time1 += get_up_down_time(t3);
        //printf("%lf\n",time1);
    }
        printf("%d\n",(int)ceil(time1));
    return 0;
}
