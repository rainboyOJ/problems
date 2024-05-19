#include <bits/stdc++.h>
using namespace std;

int n;
char a[100];

//字符串
char str[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

int main(){
    std::cin >> n;
    int i,j;
    std::cin >> a;
    int len = strlen(a);
    for(i=0;i<len;i++){
        char c = a[i];
        int p  = c - 'a';
        p += n;
        p %= 26; // 取余数
        cout << str[p];
    }

    return 0;
}


