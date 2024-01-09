/* 
 * noi 2.5  	7834	分成互质组
 *  基本思想: 贪心
 *      如果一个数字a能和其他数字在一个组,那就的一个组,否则自己一组
 * */
#include <bits/stdc++.h>
using namespace std;
int n,ans=0;
int a[20];
bool vis[20]={0};


int gcd(int a,int b){
    if( b == 0) return a;
    return gcd(b , a % b);
}

void init(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
}
int main(){
    int i,j;
    init();
    for (i=1;i<=n;i++){
        if( vis[i] ) continue;

        vector<int> v;
        v.push_back(a[i]);
        vis[i] = 1;

        for(j=i+1;j<=n;j++){
            if( vis[j]) continue;
            bool flag = true;
            for(auto x:v){
                if( gcd(x, a[j]) != 1){
                    flag = false;
                    break;
                }
            }

            if( flag){
                v.push_back(a[j]);
                vis[j] = 1;
            }
        }
        //for( auto x : v){
            //printf("%d ",x);
        //}
        //printf("\n");

        ans++;
    }
    printf("%d\n",ans);
    return 0;
}
