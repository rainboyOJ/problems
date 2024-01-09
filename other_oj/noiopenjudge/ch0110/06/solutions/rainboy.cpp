#include <cstdio>

int odd[100];
int odd_cnt = 0;

int eve[100];
int eve_cnt = 0;


int push(int x){
    if( x % 2 == 1)
        odd[++odd_cnt] = x;
    else
        eve[++eve_cnt] = x;
}

void init(){
    int i,t;
    for (i=1;i<=10;i++){
        scanf("%d",&t);
        push(t);
    }
}

void xchg(int &a,int &b){
    int t = a; a = b; b =t;
}
void quick_sort_odd(int l,int r){
    if( l >= r) return ;
    int key = odd[l];
    int i = l,j = r;

    while( i != j ){
        while( i< j && key >= odd[j])
            j--;
        while( i <j && key <= odd[i])
            i++;
        if( i < j){
            xchg(odd[i],odd[j]);
        }
    }
    odd[l] = odd[i];
    odd[i] = key;
    quick_sort_odd(l,i-1);
    quick_sort_odd(i+1,r);
}

void quick_sort_eve(int l,int r){
    if( l >= r) return ;
    int key = eve[l];
    int i = l,j = r;

    while( i != j ){
        while( i< j && key <= eve[j])
            j--;
        while( i <j && key >= eve[i])
            i++;
        if( i < j){
            xchg(eve[i],eve[j]);
        }
    }
    eve[l] = eve[i];
    eve[i] = key;
    quick_sort_eve(l,i-1);
    quick_sort_eve(i+1,r);
}

int main(){
    init();
    quick_sort_odd(1,odd_cnt);
    quick_sort_eve(1,eve_cnt);
    int i;
    for (i=1;i<=odd_cnt;i++){
        printf("%d ",odd[i]);
    }
    for (i=1;i<=eve_cnt;i++){
        printf("%d ",eve[i]);
    }
    return 0;
}
