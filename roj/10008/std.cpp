#include <bits/stdc++.h>
using namespace std;

const int A = 1e5 + 5;
int n, m;
struct node {
  int val, id;
  string x;
  inline void reverse() {
    int len = x.size() - 1;
    for (int i = 0; i <= len / 2; i++) swap(x[i], x[len - i]);
    return;
  }
} a[A];
int w[A];

inline bool cmp1(node u, node v) { return u.x < v.x; }

inline bool cmp2(node u, node v) {
  if (u.val != v.val) return u.val > v.val;
  return u.id < v.id;
}

signed main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].val;
    a[i].id = i;
    a[i].reverse();
  }
  sort(a + 1, a + 1 + n, cmp1);
  for (int i = 1; i <= n; i++) {
    w[a[i].x[0] - 'a'] = i;
    if (a[i].x[0] != a[i - 1].x[0]) {
      int pos = i;
      while (a[pos + 1].x[0] == a[pos].x[0]) pos++;
      sort(a + i, a + pos + 1, cmp2);
      i = pos;
    }
  }
  w[26] = n + 1;
  for (int i = 26; ~i; i--)
    if (!w[i]) w[i] = w[i + 1];
  for (int i = 1; i <= n; i++) a[i].reverse();
  while (m--) {
    char x;
    cin >> x;
    int k;
    cin >> k;
    int num = x - 'a';
    if (w[num + 1] - w[num] < k)
      puts("Orz YYR tql");
    else
      cout << a[w[num] + k - 1].x << '\n';
  }
  return 0;
}