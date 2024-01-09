#include <cstdio>
#include <cstring>

int n;
char str[50][5000];
int cnt[50] = {0};
int len[50] = {0};
bool is_print[50] = {0};

bool is_num(char c){
    if( c >='0' && c <= '9'){
        return 1;
    }
    return 0;
}
int to_num(char c){
    return c-'0';
}
int next_cnt(int i){
    int &idx = cnt[i];
    int &l =  len[i];
    int ret = 0;

    while(!is_num(str[i][idx]) && idx < l){
        idx++;
    }
    if( idx == l) return -1;

    while( is_num(str[i][idx])){
        char  n = str[i][idx++];
        ret = ret*10+to_num(n);
    }
    return ret;
}
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%s",str[i]);
        len[i] = strlen(str[i]);
    }
    int max = -1;
    for (i=1;i<=n;i++){
        while(1){
            int r = next_cnt(i);
            if( r == -1) break;
            if( max < r)
                max = r;
        }
    }
    bool is_first = true;
    memset(cnt,0,sizeof(cnt));
    printf("%d\n",max);
    
    for (i=1;i<=n;i++){
        while(1){
            int r = next_cnt(i);
            if( r == -1) break;
            if( max  == r && !is_print[i]){
                is_print[i] = 1;
                if( is_first){
                    printf("%d",i);
                    is_first = 0;
                }
                else {
                    printf(",%d",i);
                }
            }
        }
    }
    return 0;
}
