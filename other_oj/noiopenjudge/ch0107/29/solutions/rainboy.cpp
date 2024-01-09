#include <cstdio>
#include <cstring>

char str[500];
int sum = 0;
int main(){
    scanf("%s",str+1);

    sum += (str[1] -'0')*1;
    sum += (str[3] -'0')*2;
    sum += (str[4] -'0')*3;
    sum += (str[5] -'0')*4;
    sum += (str[7] -'0')*5;
    sum += (str[8] -'0')*6;
    sum += (str[9] -'0')*7;
    sum += (str[10] -'0')*8;
    sum += (str[11] -'0')*9;

    int ans =sum % 11;
    if ( ans == str[13] - '0')
        printf("Right");
    else if( ans == 10 && str[13] == 'X')
        printf("Right");
    else {
        if(ans == 10)
            str[13] = 'X';
        else
            str[13] = ans+'0';
        printf("%s",str+1);
    }

    return 0;
}


