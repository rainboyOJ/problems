//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-07 19:29:49
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];


//在a数组里删除x位置的值
void remove_idx(int x) {
    for(int i = x;i<=n;i++) {
        a[i] = a[i+1];
    }
    n--; //总体长度减一
}

//第k次跳多长
int jump_len(int k) {
    int ret=1;
    for(int i = 1;i <= 3 ;++i ) // i: 1->3
    {
        ret *= k;
        ret %= 5;
    }
    return ret+1;
}

//从s位置开始向上跳len
//返回值: 跳到的位置
int judge(int s,int len) {
    int end = s + len;
    if( end > n) {
        s = 1;
        end = s + len;
    }
    return end;
}

int main (int argc, char *argv[]) {
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        a[i] = i;
    }

    int s=1; //起始的位置
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int len = jump_len(i);
        s = judge(s,len);
        // cout << i << " " << a[s] << endl;
        if( i == m) {
            cout << a[s] << endl;
            break;
        }
        remove_idx(s);
    }

    return 0;
}
