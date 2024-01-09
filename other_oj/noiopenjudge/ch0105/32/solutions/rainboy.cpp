#include <cstdio>


int main(){
    int n;
    scanf("%d",&n);
    double p = 1,q = 2;
    double sum = 0;
    int i;
    for (i=1;i<=n;i++){
        sum += q/p;
        double tq = q;
        q = q+p;
        p = tq;
    }
    printf("%0.4lf\n",sum);
    return 0;
}
