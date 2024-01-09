/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 07月 22日 星期一 12:24:19 GMT
* problem:  luogu-P1098
*----------------*/
#include <bits/stdc++.h>
using namespace std;

int p1,p2,p3;
char str[1000];
char tmp[500];
int idx = 0;


int main(){
    
    scanf("%d%d%d",&p1,&p2,&p3);
    scanf("%s",str+1);
    int len = strlen(str+1);
    int i,j,k;
    for (i=1;i<=len;i++){
        char c = str[i];
        if(c == '-'){
            if(!((str[i-1] >='a' && str[i+1]<='z') || (str[i-1] >='0' && str[i+1]<='9')) ){
                printf("-");
                continue;
            }
            if( str[i-1]  >= str[i+1]){
                printf("%c",c);
            }
            else if( str[i-1]  +1 == str[i+1])
                continue;
            else {
                idx = 0;
                memset(tmp,0,sizeof(tmp));
                for(j=str[i-1]+1 ;j<str[i+1];j++){
                    for (k=1;k<=p2;k++){
                        if( p1 == 1)
                            tmp[idx++] = tolower(j);
                        else if( p1 == 2)
                            tmp[idx++] = toupper(j);
                        else 
                            tmp[idx++] = '*';
                    }
                }
                if( p3 == 1) {
                    printf("%s",tmp);
                } else {
                    int l = strlen(tmp);
                    for(k=l-1;k>=0;k--){
                        printf("%c",tmp[k]);
                    }
                }
            }
        }
        else
            printf("%c",c);

    }
    return 0;
}
