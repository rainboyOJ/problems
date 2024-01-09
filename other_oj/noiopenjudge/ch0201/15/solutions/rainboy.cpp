#include <bits/stdc++.h>
using namespace std;

int n;

int weight[500]; //每个coin的重量

/* 结构体 存每一次比较 */
struct compare_ {
    char left[100];
    char right[100];
    int res; // 0 even 1 up 2 down
};

compare_ cmp[5]; // 数组 存每一次比较
bool compare_function(int idx){ // 第 idx 次比较是否正确
    int w_l =0,w_r=0;
    int len,i,res;
    len = strlen(cmp[idx].left+1);
    for(i=1;i<=len;i++){
        w_l += weight[ cmp[idx].left[i] ] ;
    }
    len = strlen(cmp[idx].right+1);
    for(i=1;i<=len;i++){
        w_r += weight[ cmp[idx].right[i] ] ;
    }
    if( w_l == w_r)
        res = 0;
    else if( w_l < w_r)
        res = 2;
    else
        res = 1;
    if( res == cmp[idx].res)
        return 1;
    return 0;
}

/* 数据读取 */
void init(){
    int i;
    char tmp[100];
    for (i=1;i<=3;i++){
        scanf("%s",cmp[i].left+1);
        scanf("%s",cmp[i].right+1);
        scanf("%s",tmp);
        if( tmp[0] == 'e')
            cmp[i].res =0;
        else if ( tmp[0] == 'u')
            cmp[i].res =1;
        else
            cmp[i].res =2;
    }
}
int main(){
    scanf("%d",&n);
    while (n--) {
        init();
        char i;
        // 枚举 weight
        for(i='A';i<='L';i++){
            memset(weight,0,sizeof(weight));
            weight[i] = -1; // 轻
            if( compare_function(1)&&
                    compare_function(2)&&
                    compare_function(3) ) {
                printf("%c is the counterfeit coin and it is light.\n",i);
                break;
            }

            weight[i] = 1; //重
            if( compare_function(1)&&
                    compare_function(2)&&
                    compare_function(3) ) {
                printf("%c is the counterfeit coin and it is heavy.\n",i);
                break;
            }

        }
    }
    return 0;
}
