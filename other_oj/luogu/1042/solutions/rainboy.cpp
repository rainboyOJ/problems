#include <cstdio>
#include <cstring>


int cnt=0;
int vec[2500*25+5];  //存分数
int W,L;
char str[50];
int abs(int a){
    if( a < 0)
        return -a;
    return a;
}

void init(){
    bool end_flag = 0;
    while(1){
        scanf("%s",str+1);
        int len = strlen(str+1);
        int i;
        for(i=1;i<=len;i++){
            if( str[i] == 'E') {
                end_flag = 1;
                break;
            }
            vec[++cnt] = str[i] == 'W' ? 1 : 0;
        }
        if( end_flag) break;
    }
}
/* 是否一局结束 */
bool is_end(int w,int l,int f){
    if( ( w >= f || l >= f) && abs(w-l) >= 2)
        return 1;
    return 0;
}
int main(){
    init();
    //特判
    if( cnt == 0){
        printf("0:0\n");
        printf("\n");
        printf("0:0\n");
        return 0;
    }
    int i;
    W = L =0;
    for(i=1;i<=cnt;i++){
        if( vec[i] == 1)
            W++;
        else
            L++;
        if( is_end(W, L, 11)){
            printf("%d:%d\n",W,L);
            W = L = 0;
        }
    }
    printf("%d:%d\n",W,L);
    printf("\n");
    W = L =0;
    for(i=1;i<=cnt;i++){
        if( vec[i] == 1)
            W++;
        else
            L++;
        if( is_end(W, L, 21)){
            printf("%d:%d\n",W,L);
            W = L = 0;
        }
    }
    printf("%d:%d\n",W,L);
    return 0;
}


