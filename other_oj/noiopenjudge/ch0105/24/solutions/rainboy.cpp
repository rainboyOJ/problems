#include <cstdio>
int main(){
    int n,a,b,c = 0,max = -1;
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d%d",&a,&b);
        if( a  < 90 || a > 140 || b <60 || b > 90){
            if( max < c )
                max = c;
            c = 0;
        }
        else {
            c++;
        }
    }
    if( max < c )
        max = c;
    printf("%d\n",max);
    return 0;
}
