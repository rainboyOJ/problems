#include <cstdio>

int n;
struct _a{
    int x1,y1,x2,y2;
}a[10005];
int x,y;
int main(){
    scanf("%d",&n);
    int i,j;

    int ans = -1;
    for(i=1;i<=n;i++){
        scanf("%d%d%d%d",&a[i].x1,&a[i].y1,&a[i].x2,&a[i].y2);
    }
    scanf("%d%d",&x,&y);
    for(i=n;i>=1;i--){
        if(a[i].x1 <= x && (a[i].x1+ a[i].x2) >= x && a[i].y1 <= y && (a[i].y1+a[i].y2)>= y){
            ans = i;
            break;
        }
    }


    printf("%d",ans);
    return 0;
}