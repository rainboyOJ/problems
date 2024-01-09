#include <cstdio>
#include <cstring>
#include <algorithm>

char str1[110];
int str1_cnt[30];
char str2[110];
int str2_cnt[30];

void cnt(char a[],int b[],int len){
    int i;
    for(i=0;i<len;i++)
        b[ a[i]-'A']++;
    std::sort(b,b+26);
}

bool judge(){
    int i;
    for(i=0;i<26;i++)
        if( str1_cnt[i] != str2_cnt[i])
            return false;
    return true;
}
int main(){
    scanf("%s%s",str2,str1); // %s 会略过空格 换行符\n 等不可见的字符,所以不用"%s\n%s"这样写
    memset(str1_cnt,0,sizeof(str1_cnt));
    memset(str2_cnt,0,sizeof(str2_cnt));
    int len_str1 = strlen(str1);
    int len_str2 = strlen(str2);
    if( len_str1 != len_str2){
        printf("NO");
        return 0;
    }

    //统计字符
    cnt(str1,str1_cnt,len_str1);
    cnt(str2,str2_cnt,len_str2);
    if( judge()){
        printf("YES");
        return 0;
    }

    //加密1
    int i,j;
    //多次加密
    for(j=1;j<=26;j++){
        for(i=0;i<len_str1;i++){
            if(str1[i] == 'Z')
                str1[i] ='A';
            else
                str1[i]++;
        }
        memset(str1_cnt,0,sizeof(str1_cnt));
        memset(str2_cnt,0,sizeof(str2_cnt));
        cnt(str1,str1_cnt,len_str1);
        cnt(str2,str2_cnt,len_str2);
        if( judge()){
            printf("YES");
            return 0;
        }
    }
    
    printf("NO");
    return 0;
}
