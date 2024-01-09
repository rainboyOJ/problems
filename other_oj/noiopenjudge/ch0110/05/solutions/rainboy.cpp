#include <cstdio>

int n ,m;
struct _s {
    int id;
    int val;
};

_s s[5005];

// >=
bool greater(_s &a, _s &b){
    if( a.id == b.id)
        return 1;
    if( a.val > b.val )
        return 1;
    else if ( a.val == b.val && a.id < b.id)
        return 1;
    return 0;
}
void xchg(_s &a,_s &b){
    _s t = a;
    a = b;
    b = t;
}

void quick_sort(int l,int r){
    if( l >= r) return ;

    int i = l,j = r;
    _s key = s[l];

    while( i != j){
        while(greater(key,s[j]) && i<j )
            j--;
        while( greater(s[i],key) && i < j)
            i++;
        if( i < j){
            xchg(s[i], s[j]);
        }
    }
    s[l] = s[i];
    s[i] = key;
    quick_sort(l, i-1);
    quick_sort(i+1,r);
}

void init(){
    scanf("%d%d",&n,&m);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d%d",&s[i].id,&s[i].val);
    }
    m = (int)(m * 1.5);
}


int main(){
    init();
    quick_sort(1, n);
    int i;
    int fen = s[m].val;

    for (i=m+1;i<=n;i++){
        if( fen == s[i].val)
            m++;
    }
    printf("%d %d\n",s[m].val,m);
    for (i=1;i<=m;i++){
        printf("%d %d\n",s[i].id,s[i].val);
    }
    return 0;
}
