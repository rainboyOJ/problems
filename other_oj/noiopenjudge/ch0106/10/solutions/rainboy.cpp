#include <cstdio>
#include <cstring>


char num_1[300];
char num_2[300];
int num_3[300] = {0};

int main(){
    scanf("%s",num_1);
    scanf("%s",num_2);
    int len_1 = strlen(num_1);
    int len_2 = strlen(num_2);
    int i,j;

    for(i=0;i<len_1/2;i++){
        char t = num_1[i];
        num_1[i] = num_1[len_1 -i -1];
        num_1[len_1 -i -1] = t;
    }
    for(i=0;i<len_2/2;i++){
        char t = num_2[i];
        num_2[i] = num_2[len_2 -i -1];
        num_2[len_2 -i -1] = t;
    }
    for (i=0;i<len_1;i++){
        num_1[i] -= '0';
    }

    for (i=0;i<len_2;i++){
        num_2[i] -= '0';
    }

    int max_len = len_1;
    if( max_len < len_2){
        max_len = len_2;
    }
    for (i=0;i<max_len;i++){
        num_3[i+1] = (num_3[i]+num_1[i]+num_2[i]  ) / 10;
        num_3[i] = (num_3[i]+num_1[i]+num_2[i]  ) % 10;
    }

    bool is_begin_0 = true;
    for(i = max_len ;i>=0;i--){
        if( is_begin_0 && num_3[i] == 0) continue;
        is_begin_0 = 0;
        printf("%d",num_3[i]);
    }
    if( is_begin_0 )
        printf("0");

    return 0;
}
