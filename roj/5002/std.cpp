#include <cstdio>
#include <cstring>

int n,m;
int a[100];

int main(){
    scanf("%d%d",&n,&m);
    int i;
    for (i=1;i<=n+1;i++){ //读取距离
        scanf("%d",&a[i]);
    }

    int count =0;
    int sum = 0;
    int oil =  m;

    for(i=1;i<=n+1;i++){
        if( oil >= a[i]){
            oil -= a[i];
        }
        else {
            sum += (m - oil);
            oil = m;
            oil -= a[i];
            count++;
        }
    }
    printf("%d %d",count,sum);
    return 0;
}
