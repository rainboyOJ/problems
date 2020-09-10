/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 05月 01日 星期三 15:25:08 CST
* problem:  online judge-_id 
*----------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n ,m;
int a[1000010];


int main(){
    scanf("%d%d",&n,&m);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int ans=0;

    sort(a+1,a+1+n);
    int s = 1;
    for(i =n;i>=s;i--){
        if( a[i]+a[s] <=m){
            ans++;
            s++;
        }
        else{
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
