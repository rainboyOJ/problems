#include <cstdio>


int main(){
    int n;
    scanf("%d",&n);
    int sum=0,i,s = 1;
    for (i=1;i<=n;i++){
        s = s*i;
        sum += s;
    }
    printf("%d\n",sum);

    return 0;
}
