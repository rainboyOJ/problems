#include <cstdio>
#include <cstring>

int n;
char a[1000];

int main(){
    scanf("%d",&n);
    int i,j;
    
    for (i=1;i<=n;i++){
        scanf("%s",a);
        int len = strlen(a);
        int sum = 0;
        for(j=0;j<len;j++){
            if(a[j] == '0') sum++;
        }

        if(sum /2 ==1)
            printf("Win\n");
        else
            printf("Lost\n");
    }
    return 0;
}
