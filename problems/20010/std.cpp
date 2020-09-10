/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 04月 30日 星期二 15:00:52 CST
* problem:  poj-1700
*----------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int t;
int n,tail;
int a[1005];

void init(){
    scanf("%d",&n);
    tail = n;
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+n);
}

int ans = 0;

void job(){

    while( tail > 3){

        if( a[1] + a[tail-1] < (a[2]<<1))
            ans += a[tail-1] + a[1] + a[tail] +a[1];
        else
            ans += a[2] +a[1] + a[tail] + a[2];
        tail -=2;
    }
   
    if(tail == 2)
        ans += max(a[1],a[2]);
    else if( tail == 3)
        ans += a[1]+ a[2]+ a[3];
    printf("%d\n",ans);
}

int main(){
    init();
    ans=0;
    if( n== 1)
        printf("%d\n",a[1]);
    else if(n == 2)
        printf("%d\n",max(a[1],a[2]));
    else if( n == 3)
        printf("%d\n",a[1]+a[2]+a[3]);
    else {
        job();
    }
    return 0;
}
