#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
#define pb push_back
int sg[N],a[N] , n;
int SG(int x){
    if(sg[x] != -1) return sg[x];
    unordered_map<int,int>vis;
    vector<int>v;
    for(int i = 1; i <= sqrt(x) ; i ++){
        if(x % i == 0){
            v.pb(i);
            v.pb(x/i);
        }
    }
    sort(v.begin() , v.end());
    v.erase(unique(v.begin() , v.end()), v.end());
    v.pop_back();
//    cout << x << endl;
    for(int i = 0 ;i < v.size() ;i ++){
//            printf("%d " , v[i]);
        int ans = 0;
        for(int j = 0 ; j < v.size() ; j ++){
            if(i == j) continue;
            ans ^= SG(v[j]);
        }
        vis[ans] = 1;
    }
//    puts("");
    sg[x] = 0;
    while(vis.count(sg[x])) sg[x] ++ ;
    return sg[x];
}


int main(){

    memset(sg,  -1, sizeof sg);
    sg[1] = 0;
    while(~scanf("%d" , &n)){
        for(int i = 1;i <= n ;i ++){
            scanf("%d" , &a[i]);
        }
        int ans = 0;
        for(int i = 1;i <= n ;i ++){
//            if(a[i] == 1) continue;
            ans ^= SG(a[i]);
//            cout<<',' <<sg[a[i]] << endl;
        }
        if(ans) puts("freda");
        else puts("rainbow");

    }
}
