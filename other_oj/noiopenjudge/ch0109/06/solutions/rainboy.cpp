/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 05月 07日 星期二 14:42:03 CST
* problem: luogu-1125
*----------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

char word[200];
int cnt[255] = {0};

bool isprime(int n){
    int i;
    if( n <2)
        return false;
    for(i=2;i<=sqrt(n);i++)
        if( n % i ==0)
            return false;
    return true;
}

int main(){
    scanf("%s",word);
    int _min = 0x7f7f7f7f,_max = 1;

    int len = strlen(word);
    int i;
    for (i=0;i<len;i++){
        cnt[ word[i] ]++;
    }

    for(i='a';i<='z';i++)
    {
        if( cnt[i] !=0)
            _min = min( cnt[i],_min);
        _max = max(_max,cnt[i]);
    }
    int a = _max - _min;
    if( isprime(a)){
        printf("Lucky Word\n");
        printf("%d\n",_max-_min);
    }
    else {
        printf("No Answer\n");
        printf("0");
    }

    return 0;
}