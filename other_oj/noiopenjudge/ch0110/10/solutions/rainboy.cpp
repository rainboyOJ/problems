#include <cstdio>
#include <cstring>

#define cpy(a,b) memcpy(a,b,sizeof(a));


char word[200][100];
int cnt=0;
void init(){
    char t[100];
    int i;
    while( scanf("%s",t) != EOF){
        bool find_flag = false;
        for(i=1;i<=cnt;i++){
            int cmp = strcmp(t,word[i]);
            if(cmp == 0){
                find_flag = 1;
                break;
            }
        }
        if( find_flag)
            continue;

        cnt++;
        memcpy(word[cnt], t, sizeof(t));
    }
}

// >=
bool greater(char s1[],char s2[]){
    int ans = strcmp(s1, s2);
    if( ans == 0) return 1;
    if( ans > 0)
        return 1;
    return 0;
}

void xchg( char s1[],char s2[]){
    char t[100];
    memcpy(t, s1, sizeof(t));
    memcpy(s1, s2, sizeof(t));
    memcpy(s2, t, sizeof(t));
}

void quick_sort(int l,int r){
    if( l >= r) return ;

    char key[100];
    cpy(key,word[l]);
    int i = l,j = r;

    while(i != j){
        while( i < j && greater(word[j], key))
            j--;
        while( i < j && greater( key,word[i]))
            i++;
        if( i < j)
            xchg(word[i],word[j]);
    }
    cpy(word[l],word[i]);
    cpy(word[i],key);

    quick_sort(l, i-1);
    quick_sort(i+1, r);

}


int main(){
    init();
    quick_sort(1, cnt);
    int i;
    for (i=1;i<=cnt;i++){
        printf("%s\n",word[i]);
    }
    return 0;
}
