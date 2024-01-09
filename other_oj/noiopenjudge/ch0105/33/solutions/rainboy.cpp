#include <cstdio>


int main(){
    int n;
    scanf("%d",&n);
    double sum = 0;
    int flag = 1;
    int i;
    for (i=1;i<=n;i++){
        sum += flag*1.0/i;
        flag *= -1;
    }
    printf("%0.4lf\n",sum);

    return 0;
}
