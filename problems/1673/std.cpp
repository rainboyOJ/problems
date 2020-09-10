#include <cstdio>
#include <cstring>


char str[1000];

int main(){
    scanf("%s",&str[1]);

    int i,j;
    for (i=1;i<=16;i++){
        for (j=i+1;j<=16;j++){
            if( str[i] == str[j]){
                printf("%d %d\n",i,j);
                return 0;
            }
        }
    }
    printf("different");
    return 0;
}
