#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str_7[100];
char str_9[100];
int tran_to(int n,char a[],int base){
    int i,idx = 0;
    while( n != 0){
        int ret = n % base;
        a[idx++] = ret+'0';
        n = n / base;
    }
    for(i=0;i<idx/2;i++){
        swap(a[i],a[idx-i-1]);
    }
    return idx;
}

bool compare(){
    int i;
    for(i=0;i<3;i++){
        if( str_7[i] != str_9[2-i])
            return 0;
    }
    return 1;
}

int main(){
    int i;
    for(i=248;i<=999;i++){
        memset(str_7,0,sizeof(str_7));
        memset(str_9,0,sizeof(str_9));
        int len_7 = tran_to(i,str_7,7);
        if(len_7 != 3)
            continue;
        int len_9 = tran_to(i,str_9,9);
        if(len_9 != 3)
            continue;
        if( compare()){
            printf("%d\n",i);
            printf("%s\n",str_7);
            printf("%s",str_9);
            break;
        }
    }
    return 0;
}
