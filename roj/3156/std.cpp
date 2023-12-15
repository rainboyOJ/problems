#include <iostream>
using namespace std;
const int N = 1000001;
int n, m, p = 1, ans = 0, nxt[N];
int main() {
    scanf("%d%d", &m, &n);
    for (int i = 0, l, r; i < m; i++) 
        scanf("%d%d", &l, &r), nxt[l] = max(nxt[l], r);
    for (int i = 1; i <= n; i++) nxt[i] = max(nxt[i], nxt[i - 1]);
    while(p <= n && nxt[p] >= p) p = nxt[p] + 1, ans++;
    printf("%d\n", p <= n ? -1 : ans);
    return 0;
}

//作者：墨染空
//链接：https://www.acwing.com/solution/content/6640/
//来源：AcWing
//著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
