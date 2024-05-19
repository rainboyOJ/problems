#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n,m;
struct node {
    int l,p,s;
};
node a[maxn];

int main() {
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        cin >> a[i].l;
        cin >> a[i].p;
        cin >> a[i].s;
    }
    std::sort(a+1,a+1+m,[](node &a,node &b){
        return a.s < b.s;
    });

    #ifdef DEBUG
    for(int i = 1;i <= m ;++i ) // i: 1->n
    {
        cout << a[i].l << " ";
        cout << a[i].p << " ";
        cout << a[i].s << "\n";
    }
    #endif

    return 0;
}

