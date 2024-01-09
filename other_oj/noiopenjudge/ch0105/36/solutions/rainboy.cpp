#include <cstdio>


int main(){
    double x;
    int n;
    scanf("%lf",&x);
    scanf("%d",&n);
    double t =1;
    double ans = 1;
    int i;
    for (i=1;i<=n;i++){
        t *=x;
        ans += t;
    }
    printf("%.2lf\n",ans);
    return 0;
}
