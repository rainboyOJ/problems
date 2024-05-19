/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 05月 09日 星期四 14:56:01 CST
* problem: noip2011-day1t2
*----------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,k,p;

int f[200005]; //f[i] 1->i-1之间的最后一个小于p的数字的位置,包括自己
int c[200005][55]; //c[i][k] 表示第i个数之前某种颜色的数量,包括i

int ans = 0;

void init(){
    scanf("%d%d%d",&n,&k,&p);
    int t1,t2;
    int i;
    for (i=1;i<=n;i++){
        scanf("%d%d",&t1,&t2);
        memcpy(c[i],c[i-1],sizeof(c[0]));

        c[i][t1]++;

        if( t2 <= p)
            f[i] = i;
        else
            f[i] = f[i-1];
    
        /* dp */
        int pre = f[i];
        if(pre == i)
            pre--;
        ans += c[pre][t1];

    }
}

int main(){
    init();
    printf("%d\n",ans);
    return 0;
}

