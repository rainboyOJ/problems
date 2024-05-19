#include <cstdio>
#include <cstring>


#define N 1005

char map1[200][200]; //表1，代表原始的密码表
char map2[200][200]; //表2，i：加密后，j:key map2[i][j] 加密前的字符

char key[N];
int len_ken;
char jiami[N];
int len_jiami;

char UP(char t){
    if( t >='a' && t<='z')
        return 'A' +(t-'a');
    return t;
}

bool isUp(char t ){
    if( t>='A' && t<='Z') return true;
    return false;
}

bool isLower(char t ){
    if( t>='a' && t<='z') return true;
    return false;
}

char lower(char t){
    if( t >='A'&& t<='Z'){
        return 'a' + (t-'A');
    }
    return t;
}

void init(){
    int i,j,k,l;
    //生成map1
    for (i='A';i<='Z';i++){
        map1[i]['A'] = i;
        for (j='B';j<='Z';j++){
            char tc = map1[i][j-1]+1;
            if( tc > 'Z')
                tc = 'A';
            map1[i][j] = tc;
        }
    }

    //生成map2
    for(i='A';i<='Z';i++)
        for(j='A';j<='Z';j++){
            char tc = map1[i][j];
            map2[tc][i] = j;
        }

    //读取数据
    scanf("%s",&key[1]);
    scanf("%s",&jiami[1]);
    
    len_ken = strlen(&key[1]);
    len_jiami= strlen(&jiami[1]);

    for(i=len_ken+1;i<=len_jiami;i++){
        key[i] = key[i-len_ken];
    }

}


int main(){
    init();
    int i;
    for(i=1;i<=len_jiami;i++){
        char tk = UP(key[i]);

        bool islower = isLower(jiami[i]);
        char tj = UP(jiami[i]);

        if(islower){
            printf("%c",lower( map2[ tj ][ tk ]));
        }
        else{
            printf("%c",map2[ tj ][ tk ]);
        }

    }
    return 0;
}

