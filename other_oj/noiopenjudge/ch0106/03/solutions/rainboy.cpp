#include <cstdio>

double a[] = {0, 28.9 , 32.7 , 45.6, 78 , 35 , 86.2 , 27.8, 43 , 56 , 65 };
double sum = 0;

int main(){
    int i,t;
    for(i=1;i<=10;i++){
        scanf("%d",&t);
        sum += t*a[i];
    }
    printf("%0.1lf\n",sum);
    return 0;
}
