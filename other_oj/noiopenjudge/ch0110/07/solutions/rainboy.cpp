#include <cstdio>
int n;
double boy[100];
int boy_cnt = 0;

double girl[100];
int girl_cnt = 0;

int push(double x,bool is_boy){
    if(is_boy)
        boy[++boy_cnt] = x;
    else
        girl[++girl_cnt] = x;
}

void init(){
    scanf("%d",&n);
    int i;
    double t;
    char str[100];
    for (i=1;i<=n;i++){
        scanf("%s",str);
        scanf("%lf",&t);
        push(t,str[0] == 'm');
    }
}

void xchg(double &a,double &b){
    double t = a; a = b; b =t;
}
void quick_sort_boy(int l,int r){
    if( l >= r) return ;
    double key = boy[l];
    int i = l,j = r;

    while( i != j ){
        while( i< j && key <= boy[j])
            j--;
        while( i <j && key >= boy[i])
            i++;
        if( i < j){
            xchg(boy[i],boy[j]);
        }
    }
    boy[l] = boy[i];
    boy[i] = key;
    quick_sort_boy(l,i-1);
    quick_sort_boy(i+1,r);
}

void quick_sort_girl(int l,int r){
    if( l >= r) return ;
    double key = girl[l];
    int i = l,j = r;

    while( i != j ){
        while( i< j && key >= girl[j])
            j--;
        while( i <j && key <= girl[i])
            i++;
        if( i < j){
            xchg(girl[i],girl[j]);
        }
    }
    girl[l] = girl[i];
    girl[i] = key;
    quick_sort_girl(l,i-1);
    quick_sort_girl(i+1,r);
}

int main(){
    init();
    quick_sort_boy(1,boy_cnt);
    quick_sort_girl(1,girl_cnt);
    int i;
    for (i=1;i<=boy_cnt;i++){
        printf("%.2lf ",boy[i]);
    }
    for (i=1;i<=girl_cnt;i++){
        printf("%.2lf ",girl[i]);
    }
    return 0;
}
