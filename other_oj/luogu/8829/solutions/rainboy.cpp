//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-04 18:19:34
#include <bits/stdc++.h>
using namespace std;
int n,m;
char a[50];
char b[] = "GMKB"; //分别代表GB MB 
long long num = 0;

//查找c在b[]中的位置
int find_pos(char c) {
    for(int i = 0;i < 4;i++)
        if( b[i] == c) 
            return i;
    return 0;
} 

//进行转换
double trans(char a,char b) {
    int pos_a = find_pos(a);
    int pos_b = find_pos(b);
    int len = pos_a - pos_b;
    double ans = 0;
    if( len < 0) // 大转小
    {
        len = -len;
        ans = num *1.0 * (1<<(len * 10));
    }
    else { //小转大
        ans = num *1.0  / ( 1<<(len * 10));
    }
    // cout << fixed << setprecision(6) << num * 1.0<<endl;
    cout << fixed << setprecision(6) << ans <<endl;
    return 0;
}

int main (int argc, char *argv[]) {
    cin >> a+1;
    int la = strlen(a+1);
    //得到数字
    for(int i =1;i<=la;i++)
    {
        if( a[i] >= '0' && a[i] <='9')
            num = num*10 + a[i] - '0';
    }
    //找到最后一个数字的位置
    int last_num = 0;
    for(int i =1;i<=la;i++)
    {
        if( a[i] >= '0' && a[i] <='9')
            last_num = i;
    }
    //前面的单位
    char t1  = a[last_num+1];


    //问好的位置
    int question = 0;
    for(int i =1;i<=la;i++)
    {
        if( a[i] == '?')
        {
            question= i;
            break;
        }
    }


    //后面的位置
    char t2 = a[question+1];
    trans(t1,t2);
    // cout << fixed << setprecision(6) << num * 1.0<<endl;
    return 0;

    return 0;
}

