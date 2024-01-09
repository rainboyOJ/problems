#include <cstdio>

int n;
int a[1005][1005];
int w,h;

int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if( a[i][j] == 0){
                w = 1;
                h = 1;
                int pos = j;
                for(j=j+1;j<=n;j++){
                    if(a[i][j] == 0)
                        w++;
                    else
                        break;
                }
                for(j=i+1;j<=n;j++){
                    if( a[j][pos] == 0)
                        h++;
                    else
                        break;
                }

                int ans = w*h -( (w-2)*2+(h-2)*2+4);
                printf("%d\n",ans);

                return 0;
            }
        }
    }
    printf("0");
    return 0;
}
