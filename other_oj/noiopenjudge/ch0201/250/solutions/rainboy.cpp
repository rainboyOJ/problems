#include <bits/stdc++.h>
using namespace std;


int qua;
char letters[100];
int len;
char choose[10];
char ans[10];
int vis[100] = { 0 };
bool is_get_ans;

/* 求 a^n */
int _pow(int a,int n){
	int base = a;
	int ret =1;

	for(; n ; n = n >> 1){
		if(n & 1)//取最低位, 是不是很像判断奇偶
			ret = ret * base; //是1就乘
		base = base*base;     //base增增
	}

	return ret;
}
#define TO_INT(C) (C-'A'+1)
#define L(I) (TO_INT(choose[I]))

int calc(){
    return L(1)-_pow(L(2),2)+_pow(L(3),3)-_pow(L(4),4)+_pow(L(5),5);
}
void dfs(int dep){
    if( dep == 6){
        if( calc() == qua){
            is_get_ans = 1;
            memcpy(ans,choose,sizeof(ans));
        }

        return ;
    }
    int i;
    for(i=1;i<=len;i++){
        if( !vis[i]){
            choose[dep] = letters[i];
            vis[i] = 1;
            dfs(dep+1);
            vis[i] = 0;
        }
    }

}

int main(){
    while(1){

        scanf("%d",&qua);
        scanf("%s",letters+1);
        if( qua == 0)
            return 0;
        len = strlen(letters+1);
        sort(letters+1,letters+len+1);
        memset(vis,0,sizeof(vis));
        is_get_ans = 0;
        dfs(1);
        if( is_get_ans)
            printf("%s\n",ans+1);
        else
            printf("no solution\n");

    }

    return 0;
}
