#include <cstdio>
using namespace std;

#define inf 0x7f7f7f7f

int n;
int min = inf;
int max= -inf;

int main(){
    int n;
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( min  > t) 
            min = t;
        if( max < t)
            max = t;
    }
    printf("%d",max-min);
    return 0;
}
