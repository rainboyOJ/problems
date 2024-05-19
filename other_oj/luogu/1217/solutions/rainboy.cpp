#include <iostream>
using namespace std;

// is prime 是不是素数
// 判断x是否为素数
bool is_prime(int x){
    for(int i =2;i * i <= x ;i++)
        if( x % i == 0) return 0;
    return 1;
}

int s,t;// s- >> start ,t -> stop


int a[20];
//
// dep 表示第几个人来构造
// len 
void dfs(int dep,int len) {
    int stop = (len +1) / 2; 

    if( dep > stop ) {
        for(int i = 1;i<= stop ;i++)
            a[len-i+1] = a[i];
        int num = 0;
        for(int i =1;i<=len;i++)
            num = num * 10 + a[i];
        if( num < s || num > t || num == 1)
            return ;
        if( is_prime(num))
            cout << num << "\n";
        return ;
    }

    int step = 1;
    int start= 0;
    if(dep == 1)  // 构造个位数
    {
        step = 2;
        start = 1;
    }
    for(int i =start ;i <= 9 ;i+=step)
    {
        a[dep] = i;
        dfs(dep+1,len);
    }

}

// 求一个数的长度
int num_len(int x) {
    int cnt = 0;
    while( x != 0 )
    {
        cnt ++;
        x /= 10;
    }
    return cnt;
}

// snippets
int main(){

    cin >> s >> t;
    int l1 = num_len(s);
    int l2 = num_len(t);
    if( s <= 2)
        cout << 2 << endl;
    for(int i =l1;i<=l2;i++)
        dfs(1,i);

    return 0;
}
