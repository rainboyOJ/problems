#include <cstdio>

int main(){
    int r,m,y;
    scanf("%d%d%d",&r,&m,&y);
    double lilv = 1+ r*0.01;
    double result = m;
    int i;
    for (i=1;i<=y;i++){
        result = result*lilv;
    }
    printf("%d\n",(int)result);
    return 0;
}
