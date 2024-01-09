/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 12月 05日 星期日 10:13:19 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;

char word[10000000+5];
char s[10000000+5];

void to_lower(char c[],int len){
    // char c[] -- > char *c
    // *(c+x)   <-> c[x]
    // c[0]
    // c[1]
    // c[1001]
    for(int i=0;i<len;++i){
        char &x = c[i];
        if( x >='A' && x<='Z')
            x = x-'A' +'a';
    }
}
int len1,len2;
bool isque(int i){
    for( int j= 0;j< len1;j++){
        if( s[i+j] != word[j]){
            return false;
        }
    }
    //   s: abc xvc vec
    //work:     xvc
    //             ^ 这里是空格或末尾
    if( s[i+len1] == ' ' || i+len1 == len2)
        return true;
    return false;
}



int main(int argc,char * argv[]){
    cin.getline(word,sizeof(word));
    cin.getline(s,sizeof(s));

    len1 = strlen(word);
    len2 = strlen(s);
    to_lower(word, len1);
    to_lower(s, len2);

    // abc
    // 01234567->8
    //      abc

    int cnt = 0;
    int first =-1 ;
    for(int i = 0 ;i <=len2-len1 ;i++){
        if( i == 0 || s[i-1] == ' '){
            if( isque(i) ){
                cnt++;
                if(first == -1) 
                    first = i;
            }
        }
    }

    if( first == -1)
        std::cout << -1 ;
    else
        std::cout << cnt <<" "<< first << std::endl;


    return 0;
}
