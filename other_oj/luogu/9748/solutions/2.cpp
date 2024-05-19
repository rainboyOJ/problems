#include <bits/stdc++.h>
#include <cstring>
using namespace std;

int n,m;
int a1,a2;
bool apple[100]; // apple[i] = 0 表示这个苹果没有被拿走

//第一个没有被拿走的苹果
int first_apple(){
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( apple[i] == 0)
            return i;
    }
    return -1;
}

void work()
{
    memset(apple,0,sizeof(apple));

    int num = n;

    for(int i = 1;1;i++) { //天数
        int idx = first_apple();
        if( idx == -1) break;
        int cnt = 2; //略过的苹果数量
        for(int j =idx;j <=n;j++) {
            if( apple[j] == 1) continue;// 这个苹果拿过了
            if( cnt == 2) { //略过的苹果数量为2
                apple[j] = 1;
                cnt = 0;
                num--;
                // cout << j << " "; //调试用
                if( j == n) {
                    a2 = i; //记录拿取n的天数
                }
            }
            else cnt++; // 略过一个苹果
        }
        // cout << endl;
        if( num == 0) {
            a1 = i; //记录经过了多少天 拿完了所有的苹果
            break;
        }
    }
    cout << setw(4) << a1 << " ";
    cout << setw(4) << a2 << endl;
}

int main() {
    for(int i = 1;i <= 100 ;++i ) // i: 1->100
    {
        n = i;
        cout << ">>> " << setw(4) << n  << " ";
        work();
    }

    return 0;
}
