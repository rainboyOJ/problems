#include <iostream>
using namespace std;
const int maxn = 1e5+5;
int n;
char a[maxn];

// 输出n个 char
void print_n(int n,char a) {
    for(int i =1;i<=n;i++) cout << a;
}


// 输出n个 o*
void print(int n) {
    for(int i =1;i<=n;i++) cout << "o*";
}

// dep 表示此时 有多少个o,多少个*

void dfs(int dep) {
    if( dep == 4) {
        cout << "oooo****--";
        print(n-4); cout << endl;
        cout << "ooo--***o*";
        print(n-4); cout << endl;
        cout << "ooo*o**--*";
        print(n-4); cout << endl;

        cout << "o--*o**oo*";
        print(n-4); cout << endl;

        cout << "o*o*o*--o*";
        print(n-4); cout << endl;

        cout << "--o*o*o*o*";
        print(n-4); cout << endl;
        return ;
    }

    int tail = n-dep; //剩余的,已经弄好的o*
    // 类似 oooo****__o*o* 
    print_n(dep,'o'); print_n(dep,'*');print_n(2,'-');print(tail);
    cout << "\n";

    // 类似 ooo__*** o*o*o* 
    print_n(dep-1,'o'); print_n(2,'-');print_n(dep-1,'*');print(tail+1);
    cout << "\n";

    // 类似 ooo***__o*o*o* 
    // print_n(dep-1,'o'); print_n(dep-1,'*');print_n(2,'-');print(tail+1);
    // cout << "\n";
    dfs(dep-1);

}

int main() {
    std::cin >> n;
    dfs(n);

    return 0;
}


