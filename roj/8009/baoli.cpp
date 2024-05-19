//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-12 10:25:10
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];

char s1[maxn];
char s2[maxn];
char s3[maxn];
int l1,l2; //s1,s2的长度
int last[18]; //每个符号最后一次出现的位置
int last1[20];
int last2[20];
int num_len(int n) {
    int i = 0;
    while(n) {
        i++;
        n /= 10;
    }
    return i;
}

struct _info {
    //在这个位置前,包含这个位置,有a字符有多少个
    int cnt[18];
    int pre; //和当前符号相同的前一个符合的位置.
    _info & operator=(const _info & oth) {
        for(int i =0 ;i<18;i++)
            cnt[i] = oth.cnt[i];
        return *this;
    }

};

_info info1[maxn],info2[maxn];

// 字符a,b 是否可以
bool ok[100][100];
int ord(char a) { return a - 'a'; }
char chr(int a) { return 'a' + a; }


void pre_deal(char *s,int len,_info * info) {
    memset(last,-1,sizeof(last));

    char c = s[0];
    int nu = ord(c); //转换成数字
    info[0].cnt[nu]++;
    info[0].pre = last[nu];
    last[nu] = 0;
    for(int i =1;i<len;i++) {
        char c = s[i];
        int nu = ord(c); //转换成数字
        info[i] = info[i-1];
        info[i].cnt[nu]++;
        info[i].pre = last[nu];
        last[nu] = i;
    }
    info[len] = info[len-1];
}

//检查a,b是否可以符合
bool check(int a,int b) {

    //两个字符出现的次数不一样
    if( info1[l1].cnt[a] !=info2[l2].cnt[a]) return 0;
    if( info1[l1].cnt[b] !=info2[l2].cnt[b]) return 0;

    int lst1 = last1[b];
    int lst2 = last2[b];
    while(lst1 != -1 || lst2 != -1){
        if( info1[lst1].cnt[a] != info1[lst2].cnt[a])
            return 0;
        if( info1[lst1].cnt[b] != info1[lst2].cnt[b])
            return 0;
        lst1 = info1[lst1].pre;
        lst2 = info2[lst2].pre;
    }
    return 1;
}

string get1(char *ss,int len,char a,char b) {
    string s;
    for(int i = 0 ;i < len;i++)
        if( ss[i] == a || ss[i] == b)
            s += ss[i];
    return s;
}


int main (int argc, char *argv[]) {
    std::cin >> s1 >> s2;
    l1  = strlen(s1);
    l2  = strlen(s2);
    // memset(info1,-1,sizeof(info1));
    // memset(info2,-1,sizeof(info2));

    for(int i = 0 ;i< 18; i++)
    {
        for(int j = i+1;j < 18 ;++j ) // j: 1->18
        {
            char a = chr(i);
            char b = chr(j);
            string a1 = get1(s1,l1,a,b);
            string a2 = get1(s2,l2,a,b);
            bool ret = a1 == a2;
            cout << a << " " << b << " " << ret << endl;
        }
    }

    //预处理 
    std::cin >> n;

    return 0;
}
