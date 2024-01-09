#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a,b;
char str[100];
LL len;
char z[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

vector<char> v;
/* n 进制  -> 10 进制 */
LL toDec(){
    LL sum = 0;
    LL t = 1;
    int i;
    for(i=len;i>=1;i--){
        sum +=  (str[i]*t);
        t *= a;
    }
    //printf("%lld\n",sum);
    return sum;
}
/* 10 进制  -> n 进制 */
void toN(LL x){
    while( x ){
        int t = x % b;
        v.push_back(z[t]);
        x /=b;
    }
}
int main(){
    scanf("%lld",&a);
    scanf("%s",str+1);
    len = strlen(str+1);
    if( len == 1 && str[1] == '0'){
        printf("0");
        return 0;
    }
    scanf("%lld",&b);
    int i;
    for(i=1;i<=len;i++){
        char &c = str[i];
        if( c >='0' && c<='9')
            str[i] -='0';
        else if( c >='a' && c <='z')
            str[i] -=('a'-10);
        else if( c >='A' && c <='Z')
            str[i] -=('A'-10);
    }
    toN(toDec());
    reverse(v.begin(),v.end());
    for (const auto& e : v) {
        printf("%c",e);
    }

    return 0;
}
