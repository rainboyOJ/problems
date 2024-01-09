/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 12月 05日 星期日 10:53:29 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;

char biao[200][200];

void init(){ 

    for(int i='a';i<='z';++i){ //行
        char start = i;
        for(int j='a';j<='z';++j){
            biao[i][j] = start;
            start++;
            if( start >'z')
                start = 'a';
        }
    }

    //for(int i='a';i<='z';++i){ //行
        //for(int j='a';j<='z';++j){
            //std::cout << biao[i][j] ;
        //}
        //std::cout << std::endl;
    //}

}

char mishi[10000];
char miwen[10000];
int len1,len2;

char to_lower(char c){
    if( c >='A' && c <='Z')
        return c-'A' +'a';
    return c;
}

// mishi miwen
char myfind(char a,char b){
    bool isBig = b >='A' && b <='Z';
    a = to_lower(a);
    b = to_lower(b);
    char duiying;
    for(int i = 'a' ;i<='z';i++){
        if( biao[i][a] == b){
            duiying = i;
            break;
        }
    }
    if(isBig)
        return duiying -'a' +'A';
    return duiying;
}

int main(int argc,char * argv[]){
    init();
    cin >> mishi;
    cin >> miwen;
    len1 = strlen(mishi);
    len2 = strlen(miwen);

    if( len1 < len2){ //copy
        for(int i =len1 ;i< len2;i++){
            mishi[i]= mishi[i-len1];
        }
    }
    for(int i=0;i<=len2-1;++i){
        std::cout << myfind( mishi[i], miwen[i]) ;
    }
    return 0;
}
