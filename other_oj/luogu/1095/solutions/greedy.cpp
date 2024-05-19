#include <cstdio>
int m,s,t;

int main(){
    scanf("%d%d%d",&m,&s,&t);
    int nt=t,nm=m,ns=s;
    while( nt >0 && ns>0){
        if(nm >=10){
             nt--;
             ns-=60;
             nm-=10;
        }else if( nm ==0 && nt >=7 && ns >119){
            nt--;nm+=4;
        } else if( nm ==1 && nt >=7 && ns >119){
            nt--;nm+=4;
        } else if( (nm>=2 && nm<=5) && nt >= 3 && ns>41){
            nt--;nm+=4;
        }else if( (nm>=6 && nm<=9)&& nt >= 2 && ns>34){
            nt--;nm+=4;
        } else { // 直接走
            nt--;
            ns-=17;
        }
    }

    if(ns <=0 && nt >=0){ //走完了
        printf("Yes\n");
        printf("%d",t-nt);
    }

    if(nt <=0 && ns >0){
        printf("No\n");
        printf("%d",s-ns);
    }
    return 0;
}


