#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e5+5;
int n,I,h,r;

int d[maxn]; //差分数组

void sub_range(int x,int y) {
    if( x > y) swap(x,y);
    if( x +1 == y) return;
    if( y <= I) {
        y--;
        d[y] -= 1;
        d[x] += 1;
    }
    else if( x >= I) {
        x++;
        d[x] -= 1;
        d[y] += 1;
    }
}

int t[maxn];

typedef std::pair<int ,int > node;

node range[maxn];

int main() {
    std::cin >> n >> I >> h >> r;
    for(int i = 1;i <= r ;++i ) // i: 1->r
    {
        int l,r;
        std::cin >> l >> r;
        range[i] = std::make_pair(l,r);
        // sub_range(l,r);
    }

    std::sort(range+1,range+1+r);

    for(int i = 1;i <= r ;++i ) // i: 1->r
    {
        int l = range[i].first;
        int r = range[i].second;
        if( l == range[i-1].first && r == range[i-1].second)
        {
            continue;
        }

        sub_range(l,r);
    }

    t[I] = h;
    for(int i =I-1; i>=1;i--)
    {
        t[i] = t[i+1] + d[i];
    }
    for(int i =1;i<I;i++)
        cout << t[i] << "\n";
    cout << h << "\n";
    int s  = h;
    for(int i = I+1;i<=n;i++) {
        s+= d[i];
        cout << s << "\n";
    }

    return 0;
}
