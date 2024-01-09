#include <cstdio>
int n;
int age[205]={0};
int main(){
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        age[t]++;
    }
    int a,b,sum;
    a = 0,b=18,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    a = 19,b=35,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    a = 36,b=60,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    a = 61,b=200,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    return 0;
}
