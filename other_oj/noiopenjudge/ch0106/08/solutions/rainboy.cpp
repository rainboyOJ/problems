#include <cstdio>

int n,na,nb;
int a[105],b[105];

int main(){
    scanf("%d%d%d",&n,&na,&nb);
    int i,j;
    for (i=1;i<=na;i++){
        scanf("%d",&a[i]);
    }

    int idx = 1;
    for(i=na+1;i<=n;i++){
        a[i] = a[idx];
        idx++;
    }
    for (i=1;i<=nb;i++){
        scanf("%d",&b[i]);
    }

    idx = 1;
    for(i=nb+1;i<=n;i++){
        b[i] = b[idx];
        idx++;
    }
    int win_a = 0,win_b =0;
    for(i=1;i<=n;i++){
        if( (a[i] == 0 && b[i] == 2) || (a[i] == 2 && b[i] == 5) || (a[i] == 5 && b[i] == 0 ))
            win_a++;
        else if( (b[i] == 0 && a[i] == 2) || (b[i] == 2 && a[i] == 5) || (b[i] == 5 && a[i] == 0 ))
            win_b++;
    }
    if( win_a == win_b)
        printf("draw");
    else if( win_a > win_b)
        printf("A");
    else 
        printf("B");
    return 0;
}
