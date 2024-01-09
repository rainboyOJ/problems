#include <cstdio>


int main(){
    int n;
    scanf("%d",&n);
    double i,s = 1;
    double sum=1;
    for (i=1;i<=n;i++){
        s = s*i;
        sum += 1.0/s;
    }
    printf("%0.10f\n",sum);

    return 0;
}
