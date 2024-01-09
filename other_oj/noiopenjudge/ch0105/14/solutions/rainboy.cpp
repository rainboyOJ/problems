#include <cstdio>

int main(){
    double a;
    int n;
    int i;
    scanf("%lf",&a);
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        a = a*1.001;
    }
    printf("%0.4lf",a);
    return 0;
}
