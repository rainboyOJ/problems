#include <cstdio>
#include <cstring>

int n;
int s[2000];
int main(){
    scanf("%d",&n);
    int i,cnt=1,max=1;
    for (i=1;i<=n;i++){
        scanf("%d",&s[i]);
    }
    for (i=2;i<=n;i++){
        if(s[i] == s[i-1]){
            cnt++;
        }
        else {
            if( max < cnt) max = cnt;
            cnt = 1;
        }
    }
    if( max < cnt) max = cnt;
    printf("%d\n",max);
    return 0;
}
