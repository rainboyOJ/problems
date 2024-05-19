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

void find() {
  int i,j;
  i = j = 10;
  //从开头取两个数
  //相当于放到另一个数组里
  long long t1 = dec_on_b(a,10);
  long long t2 = dec_on_b(b,10);
  while(1) {
    if( t1 == t2) {
      cout << i << " " << j << endl;
      return;
    }

    //比较小的那个元素,继续取
    if(t1 < t2) t1 = dec_on_b(a,++i);
    else        t2 = dec_on_b(b,++j);
  }
}

int main () {

  cin >> n;
  while(n--){ //循环n次
    read(a);
    read(b);
    find();
  }
  return 0;
}
