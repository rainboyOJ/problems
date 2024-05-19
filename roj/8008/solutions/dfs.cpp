#include <bits/stdc++.h>
using namespace std;
const int maxn = 15000;

int n;
char s[100];
int a[5];
int b[5];

//把对应的数转成基数b下的十进制数字
long long dec_on_b(int a[],int b){
  long long ans = 0;
  ans = a[3] * b*b + a[2] *b + a[1];
  return ans;
}

//读取这三位置到数组a里
void read(int a[]) {
  cin >> s+1;
  //注意返回过来存,a[1] 是个位数
  a[3] = s[1] - '0';
  a[2] = s[2] - '0';
  a[1] = s[3] - '0';
}

void dfs(int i,int j) {
  long long t1 = dec_on_b(a,i);
  long long t2 = dec_on_b(b,j);
  if( t1 == t2) {
    //输出答案结果,注意,一定有答案
    cout << i << " " << j << endl; 
    return;
  }
  //这不可能发生
  if( i > maxn || j > maxn) {
    cout << -1 << " " << -1 << endl; 
    return;
  }
  if( t1 < t2) dfs(i+1,j);
  else dfs(i,j+1);
}

int main () {

  cin >> n;
  while(n--){ //循环n次
    read(a);
    read(b);
    dfs(10,10);
  }
  return 0;
}
