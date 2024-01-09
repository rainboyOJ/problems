#include <cstdio>
#include <cmath>

int main(){
    double xa,ya,xb,yb;
    scanf("%lf%lf%lf%lf",&xa,&ya,&xb,&yb);
    double ans = sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
    printf("%0.3lf\n",ans);

    return 0;
}

