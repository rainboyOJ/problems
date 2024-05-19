//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-04 10:35:58
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
char a[maxn];
int len;

/*
..#. ..#. ..*. ..#. .
.#.# .#.# .*.* .#.# .
#.A. #.B. *.C. *.D. #
.#.# .#.# .*.* .#.# .
..#. ..#. ..*. ..#. .
*/

//输出第一行
void print_line_1() {
    for(int i = 1;i <= len ;i++ ) // i: 1->len
    {
        if( i % 3 == 0)
            cout << "..*.";
        else
            cout << "..#.";
    }
    cout <<"."<<endl;;
}
//输出第2行
void print_line_2() {
    for(int i = 1;i <= len ;i++ ) // i: 1->len
    {
        if( i % 3 == 0)
            cout << ".*.*";
        else
            cout << ".#.#";
    }
    cout <<"."<<endl;;
}

//输出第3行
void print_line_3() {
    char b[10];
    for(int i =0;i<5;i++) b[i] = '.';
    b[4] = '\0'; //结尾用
    for(int i = 1;i <= len ;i++ ) // i: 1->len
    {
        b[2] = a[i];
        if( i == 1) {
            b[0] = '#';
        }
        else if(i % 3 == 0 || (i-1) % 3 == 0){
            b[0] = '*';
        }
        else b[0] = '#';
        cout << b;
    }
    if( len % 3 == 0)
        cout <<"*"<<endl;
    else
        cout <<"#"<<endl;
}


int main (int argc, char *argv[]) {
    cin >> a+1;
    len = strlen(a+1);
    print_line_1();
    print_line_2();
    print_line_3();
    print_line_2();
    print_line_1();
    

    return 0;
}
