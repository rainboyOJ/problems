#include <bits/stdc++.h>
using namespace std;

char str[105];
int len;

struct node {
    char str[101];
    int cnt;
    bool operator==(const char s[]){
        if( strcmp(s,str) == 0)
            return 1;
        return 0;
    }
    bool operator<(node &b){
        if( strcmp(str,b.str) < 0)
            return 1;
        return 0;
    }
};
vector<node> v;

int main(){
    scanf("%s",str+1);
    len = strlen(str+1);
    int i,j;
    char tmp[200];
    for(i=1;i<=len;i++){ //起始位置
        for(j=i;j<=len;j++){ //结束位置
            memset(tmp,0,sizeof(tmp));
            strncpy(tmp,str+i,j-i+1);
            auto x = find(v.begin(),v.end(),tmp);
            if( x != v.end()){
                (x->cnt)++;
            }
            else {
                node t;
                memcpy(t.str,tmp,sizeof(t.str));
                t.cnt = 1;
                v.push_back(t);
            }
        }
    }
    sort(v.begin(),v.end());
    for (const auto& e : v) {
        if( e.cnt > 1)
            printf("%s %d\n",e.str,e.cnt);
    }
    return 0;
}
