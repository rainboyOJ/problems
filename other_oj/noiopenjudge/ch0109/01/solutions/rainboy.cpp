#include <cstdio>
using namespace std;

int n,x;
int a[10005];
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&x);
    for (i=1;i<=n;i++){
        if( a[i] == x){
            printf("%d\n",i);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
