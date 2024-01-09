#include <bits/stdc++.h>
using namespace std;
int n,m;
typedef  bitset<30> bit30;

vector<bit30> a,b;

int cnt=0;

void init(){
    scanf("%d%d",&n,&m);
    int i,t;
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        a.push_back(t);
    }

    for (i=1;i<=m;i++){
        scanf("%d",&t);
        b.push_back(t);
    }

}
int main(){
    init();
    for( auto i : a){
        for( auto j : b){
            bit30 x = i ^ j;
            if( x.count() == 2)
                cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
