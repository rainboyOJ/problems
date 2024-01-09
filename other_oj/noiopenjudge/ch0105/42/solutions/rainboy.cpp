#include <cstdio>


int main(){
    int h,w,flag;
    char c;
    scanf("%d%d",&h,&w);
    scanf("%c",&c);
    scanf("%c",&c);
    scanf("%d",&flag);
    int i,j,k;

    // line 1
    for (i=1;i<=w;i++){
        printf("%c",c);
    }
    printf("\n");


    for (i=1;i<=h-2;i++){
        printf("%c",c);
        for (j=1;j<=w-2;j++){
            if(flag)
                printf("%c",c);
            else 
                printf(" ");
        }
        printf("%c\n",c);
    }




    // line last
    for (i=1;i<=w;i++){
        printf("%c",c);
    }
    return 0;
}
