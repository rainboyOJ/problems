/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 01月 26日 星期三 19:11:02 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

string word[100];
string start;

bool vis[100]; //表示 第i个单词 有没有选
int ans = 0; //答案 最长长度
string __long; //


bool is_included(string& a){
    if(a.length() == __long.length())
        return a == __long;
    if( __long.length() > a.length() ){
        int start = __long.length() - a.length();
        string s(__long.begin()+start,__long.end());
        return s == a;
    }
    else { 
        string s(a.begin(),a.begin() + __long.length());
        return s == __long;
    }
}

int tail_common_length(string &a){
    int len = min(__long.length()-1,a.length()-1);
    for(int i= 1;i <= len;i++){
        string s1(__long.begin()+__long.length()-i,__long.end());
        string s2(a.begin(),a.begin()+i);
        if( s1 == s2 )
            return i;
    }
    return 0;
}
/**
 * 拼接,当成功时 返回拼的长度
 * 如果能把a拼到__long的后面
 */
int join(string& a){ //string 是一个类对象 用引用 运行速度快一点
    //if( is_included(a)){
        //return 0; //不行
    //}
    int len = tail_common_length(a);
    if( len == 0) {
        return 0;
    }
    __long += string(a.begin()+len,a.end());
    return len;
}

// 把 a 从__long的后面删除len个元素
void del(int len){
    for(int i=1;i<=len;++i){
        __long.pop_back();
    }
}

void dfs(int dep){
    ans = max<int>(ans,__long.length());
    if( dep ==1){
        for(int i =1;i<=n;i++){
            if( word[i][0] ==start[0] ){
                vis[i] = 1;
                __long = word[i];
                //std::cout << dep <<" "<< __long <<" "<< __long.length() << std::endl;
                dfs(dep+1);
                vis[i] = 0;
            }
        }
        return;
    }
    for(int i=1;i<=n;++i){
        if( vis[i] == 0 ){
            int len = join(word[i]);
            if( len == 0) continue;
            //std::cout << dep <<" "<< __long <<" "<< __long.length() << std::endl;
            vis[i] = 1;
            dfs(dep+1); // [abc]d
            del(word[i].length() - len);
            //std::cout << dep <<" after del "<< __long <<" "<< __long.length() << std::endl;
            vis[i] = 0;
        }
    }

}

int main(int argc,char * argv[]){
    std::cin >> n;
    for(int i=1;i<=n;++i){
        cin >> word[i];
    }
    for(int i=1;i<=n;++i){
        word[n+i] = word[i];
    }
    cin >> start;
    // 数据读取结束
    n = 2*n;
    dfs(1);
    std::cout << ans << std::endl;

    return 0;
}
