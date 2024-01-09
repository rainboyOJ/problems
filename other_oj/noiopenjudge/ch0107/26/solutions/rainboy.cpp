#include <cstdio>
#include <cstring>

char str[500];

char s[5][500];
int idx_1= 1,idx_2=1;
int main(){
    char t;
    while( scanf("%c",&t) != EOF){
        if( t == '\n' || t == '\r')
            break;
        if( t == ','){
            idx_1++;
            idx_2=1;
            continue;
        }
        s[idx_1][idx_2++] = t;
    }

    int point_1_int;
    char * point_1 = strstr(s[1]+1,s[2]+1);
    if( point_1 == NULL){
        printf("-1");
        return 0;
    }
    else 
        point_1_int = point_1 - (s[1]+1);
    //printf("%d\n",point_1_int);
    //reverse
    int len1 = strlen(s[1]+1);
    int len2 = strlen(s[3]+1);
    int i;
    if( strstr(s[1]+1,s[3]+1) == NULL){
        printf("-1");
        return 0;
    }

    for(i = len1;i >= 1;i--){
        char * point_2 = strstr(&s[1][i],s[3]+1);
        if( point_2 != NULL){
            len2 = strlen(s[2]+1);
            //printf("%s\n",s[3]+1);
            //printf("%s\n",point_2);
            //printf("%d\n",point_2-&s[1][1]);
            int ans;
            if( point_2 >= point_1+len2)
                ans = point_2- point_1 -len2;
            else {
                printf("-1");
                return 0;
            }

            printf("%d",ans);
            break;
        }
    }
    return 0;
}


