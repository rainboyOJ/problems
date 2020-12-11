/* author: Rainboy email: rainboylvx@qq.com  time: 2020年 12月 02日 星期三 15:40:26 CST */
//#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

#ifndef DEBUG  /*----------------------------------*/
#define log(...)
#endif		   /*----------------------------------*/

const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
int n,m;
vector<int>   v;

int work(){
    int h=0,t=v.size()-1;
    int sum=0;
    while ( 1 ) {
        if(h == t) {
            sum += v[h];
            break;
        }
        if( t-h+1== 2) {
            sum += max(v[h],v[t]);
            break;
        }
        if( t-h+1==3 ) {
            sum+= v[h] + v[h+1] + v[t];
            break;
        }

        int a = v[h];
        int b = v[h+1];
        int c = v[t-1];
        int d = v[t];
        if( 2*b < a+c){
            sum += d +2*b+a;
            t-=2;
        }
        else {
            sum += d+a;
            t--;
        }
    }
    return sum;

}
int main(){
    //scanf("%d",&n);
    //for(int i=1;i<=n;++i){
        int t;
        v.clear();
        scanf("%d",&m);
        for(int i=1;i<=m;++i){
            scanf("%d",&t);
            v.push_back(t);
        }
        sort(v.begin(),v.end());
        int ans = work();
        printf("%d\n",ans);
    //}

    return 0;
}
