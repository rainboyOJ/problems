#include <cstdio>

char id[200][100];

int n;
struct _p {
    int id,age,ord;
};
_p p[200];
void init(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%s",id[i]);
        scanf("%d",&p[i].age);
        p[i].id = i;
        p[i].ord = i;
    }
}

// >=
bool greater(_p &a,_p &b){

    if(a.ord == b.ord) return 1;
    if( a.age >=60 && b.age < 60)
        return 1;

    if( a.age >=60 &&  b.age >=60 ){
        if( a.age > b.age)
            return 1;
        else if ( a.age == b.age)
            return a.ord < b.ord;
    }

    if( a.age < 60 && b.age < 60){
        return a.ord < b.ord;
    }

    return 0;
}

void xchg( _p &a, _p &b){
    _p t = a;
    a = b;
    b = t;
}
void quick_sort(int l,int r){
    if( l >= r ) return;

    _p key = p[l];
    int i= l,j = r;

    while(i!= j){
        while( i < j && greater(p[j],key))
            j--;
        while( i < j && greater(key,p[i]))
            i++;
        if( i < j)
            xchg(p[i], p[j]);
    }
    p[l] = p[i];
    p[i] = key;
    quick_sort(l, i-1);
    quick_sort(i+1, r);
}

int main(){
    init();
    quick_sort(1, n);
    int i;
    for(i = n;i>=1;i--)
        printf("%s\n",id[ p[i].id ]);
    return 0;
}

