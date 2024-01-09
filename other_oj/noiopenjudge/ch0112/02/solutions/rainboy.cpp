#include <cstdio>
int n;
double sum = 0;

void init(){
    scanf("%d",&n);
}

double calc(int len){
    int a = len / 70;
    if( len % 70 != 0 )
        a++;
    return a*0.1;
}
int main(){
    init();
    int i,t;
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        sum += calc(t);
    }
    printf("%0.1lf\n",sum);
    return 0;
}
