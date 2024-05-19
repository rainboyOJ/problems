#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n;
int rcd[maxn];

int ans;
typedef std::pair<int,int> pa;
pa a[maxn];

//判断是否有重复
// 先把r值排序,
// 这里的核心,
/*

判断两个区间不相交: r1 < l2 一定不想交

证明: 排序后,A: 任意两个相邻的不相交, B :则不存在相交的区间

A to B
2. neg B \to neg A 这个证明完毕

所以只要证明2式,就可以了

假设a,b 两个区间相交,且不存存r < r2 r> r1 
那么排序后r1, r2 一定相邻

假设a,b 两个区间相交,存存r < r2 r> r1 
那么排序后r1, r2 一定相邻
那么一定能找到rx 与r2 中间没有r了,且rx一定与r2所在的区间相交

2 式证明完毕 
*/
bool check(int n) {
    for(int i =2;i<=n;i++)
    {
        int r = rcd[i]; //编号
        int l = rcd[i-1];
        if( a[l].first >= a[r].second)
            return 0;
    }
    return 1;
}
int get_val(int n) {
    int ret=0;
    for(int i =1;i<=n;i++)
    {
        int l = rcd[i];
        ret += a[l].first - a[l].second+1;
    }
    return ret;
}

// dep 深度,当前给哪个盒子选
void full_comb(int dep,int p){

    //每一次进入都输出
    if( check(dep-1))
    {
        /*
        for(int i =1 ;i<dep;i++)
        {
            // cout << rcd[i] << " ";
            int id = rcd[i];
            cout <<  "[ ";
            cout << a[id].second << " " ;
            cout << a[id].first << " " ;
            cout <<  "]  ";
        }
        cout << get_val(dep-1);
        cout << endl;
        */
        int t = get_val(dep-1);
        if( ans < t)
            ans = t;
    }
    for(int i = p+1;i <=n;i++)
    {
        rcd[dep] = i;
        full_comb(dep+1,i);
    }
}



int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> a[i].second; // second 其实是开头
        cin >> a[i].first; // first 其实是结尾
    }
    sort(a+1,a+1+n);//排序
    full_comb(1,0);
    cout << ans << endl;




    return 0;
}
