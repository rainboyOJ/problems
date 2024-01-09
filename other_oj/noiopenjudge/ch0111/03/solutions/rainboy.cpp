/* 
 * 进行两次 二分 
 *  
 *  第一次 满足条件的左边小矩形的面积s
 *  第二次 第一次 >s 时的k值
 *
 * */

#include <bits/stdc++.h>
using namespace std;


int r;
int n;
struct _rect{
    int l,r,w,h;
    int m;
};

typedef long long ll;
_rect rect[10005];

void check(int k,ll &l, ll &r){
     r = 0;
     l = 0;
    
    int i;
    for(i=1;i<=n;i++){
        if( rect[i].l + rect[i].w <= k)
            l += rect[i].m;
        else if ( rect[i].l >= k)
            r += rect[i].m;
        else {
            l += (k- rect[i].l)* rect[i].h;
            r += (rect[i].l+ rect[i].w-k)* rect[i].h;
        }
    }
}

void init(){
    scanf("%d%d",&r,&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d%d%d%d",&rect[i].l,&rect[i].r,&rect[i].w,&rect[i].h);
        rect[i].m  = rect[i].w * rect[i].h;
    }
}

long long first_ge(int l,int r){
    ll left,right;
    while(l < r){
        int m = (l+r) >> 1;
        check(m, left, right);
        if( left < right){
            l = m+1;
        }
        else
            r = m;
    }
    check(l, left, right);
    return left;
}

int first_g(int l,int r,long long rect_m){
    ll left,right;

    while( l < r){
        int m = (l+r) >> 1;
        check(m,left,right);
        if( left <= rect_m)
            l = m+1;
        else
            r= m;
    }
    return l;
}
int main(){
    init();
    long long m;
    m = first_ge(0,r);
    //printf("%d\n",m);
    int k = first_g(0, r+1,m);
    if( k > 0)
        printf("%d",k-1);
    else
        printf("0");
    return 0;
}
