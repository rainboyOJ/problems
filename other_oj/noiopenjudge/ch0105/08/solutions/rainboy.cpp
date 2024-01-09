#include <cstdio>

int main(){
    int n;
    int sum = 0;
    int i;
    int a=0,b=0,c=0;
    int t1,t2,t3;
    scanf("%d",&n);
    for (i=1;i<n;i++){
        scanf("%d",&t1);
        a += t1;
    }
    b = (n-2)*180;
    printf("%d\n",b-a);
    return 0;
}
