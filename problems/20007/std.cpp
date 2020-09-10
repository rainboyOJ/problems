#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
struct ANTS {
	int num;
	int pos;
	char dir;
};
int cmp(ANTS a, ANTS b) {
	return a.pos < b.pos;
}
ANTS ants[10005], antsb[10005];
int kep[10005];
int main() {
	int m, cnt = 1;
	m=1;
	while (m--) {
		int L, T, n, tempi;
		char tempc;
		scanf("%d %d %d", &L, &T, &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %c\n", &tempi, &tempc);	
			ants[i].num = 0;
			antsb[i].num = i;
			ants[i].pos = antsb[i].pos = tempi;
			ants[i].dir = antsb[i].dir = tempc;
		}
		sort(antsb + 1, antsb + n + 1, cmp);
		for (int i = 1; i <= n; i++) {
			kep[antsb[i].num] = i;
		}
		for (int i = 1; i <= n; i++) {
			if (ants[i].dir == 'R') {
				ants[i].pos += T;
			}
			else ants[i].pos -= T;
		}
		sort(ants + 1, ants + n + 1, cmp);
		for (int i = 1; i < n; i++) {
			if (ants[i].pos == ants[i + 1].pos) {
				ants[i].dir = ants[i + 1].dir = 'T';
			}
		}
		for (int i = 1; i <= n; i++) {
			int a = kep[i];
			if (ants[a].pos < 0 || ants[a].pos > L) {
				printf("Down\n");
				continue;
			}
			if (ants[a].dir == 'T') {
				printf("%d Same\n", ants[a].pos);
				continue;
			}
			else printf("%d %c\n", ants[a].pos, ants[a].dir);
		}
	}
	return 0;
}
