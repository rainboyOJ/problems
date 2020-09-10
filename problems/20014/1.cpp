// UVa1628 Pizza Delivery
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;

int kase, n;
int p[maxn], v[maxn];
int d[maxn][maxn][maxn][2];
int vis[maxn][maxn][maxn][2];

// already considered s~e, still need to delivery to cnt people. 
// pos = 0 means at s, pos = 1 means at e
int dp(int s, int e, int cnt, int pos) {
  if(cnt == 0) return 0;          //cnt==0 return 

  int &ans = d[s][e][cnt][pos];          //记忆化搜索 
  if(vis[s][e][cnt][pos] == kase) return ans;
  vis[s][e][cnt][pos] = kase;

  ans = 0;   
  //枚举的i与之前区间相间的部分默认为不会送餐 //比较得出max_ans 
  if(!pos) {                         //pos==s 
    for(int i = 0; i < s; i++)  //s->i  //i在区间的左边 
      ans = max(ans, v[i] - cnt * abs(p[i] - p[s]) + dp(i, e, cnt - 1, 0)); 
    //ans=max(ans,足够已知的未来价值+子问题价值) 
    for(int i = e + 1; i < n; i++) //s->i //i在区间的右边 
      ans = max(ans, v[i] - cnt * abs(p[i] - p[s]) + dp(s, i, cnt - 1, 1));
  }
  else {                             //pos==e 
    for(int i = 0; i < s; i++)  //e->i  //i在区间的左边 
      ans = max(ans, v[i] - cnt * abs(p[i] - p[e]) + dp(i, e, cnt - 1, 0));
    for(int i = e + 1; i < n; i++) //e->i  //i在区间的右边 
      ans = max(ans, v[i] - cnt * abs(p[i] - p[e]) + dp(s, i, cnt - 1, 1));
  }
  return ans;
}

//DP要枚举出所有具有最优可能性的情况 不能遗漏否则问题就可能不是最优 

int main() {
  int T=1;
  memset(vis, 0, sizeof(vis));
  for(kase = 1; kase <= T; kase++) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &p[i]);   //位置[] 
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);   //原利[] 

    int ans = 0;
    for(int k = 1; k <= n; k++)      //枚举送餐人数 
      for(int i = 0; i < n; i++)     //枚举给送餐的第一个人 
        ans = max(ans, v[i] - k * abs(p[i]) + dp(i, i, k - 1, 0));  //枚举比较 make_max 
    printf("%d\n",ans);
  }
  return 0;
}
