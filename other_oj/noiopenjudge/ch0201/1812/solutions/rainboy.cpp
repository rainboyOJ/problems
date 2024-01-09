#include <bits/stdc++.h>
using namespace std;

/* 求立方 */
int li(int a){
    return a*a*a;
}

int a,b,c,d;

int main(){
    scanf("%d",&a);
    int i,j,k,l;
    for (i=6;i<=a;i++){
        
        int li_a = li(i);
        for (j=2;j<a;j++){
            for(k=j;k<a;k++){
                for(l=k;l<a;l++){
                    if(li_a == li(j) + li(k)+ li(l)){
                        printf("Cube = %d, Triple = (%d,%d,%d)\n",i,j,k,l);
                    }
                }
            }
        }
    }
    return 0;
}
