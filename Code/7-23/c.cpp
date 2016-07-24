#include <bits/stdc++.h>
using namespace std;

const int L = 1000003;
int adj[L], nxt[L*5], v[L*5], e;
int rec[L*5], cr = 0;

__inline bool fd(int x) {
	int y = x % L;
	for (int e = adj[y]; ~e; e = nxt[e])
		if (v[e] == x) return 1;
	return 0;
}

__inline void ins(int x) {
	int y = x % L;
	v[e] = x; nxt[e] = adj[y]; adj[y] = e++;
	rec[cr++] = y;
}

__inline int elim(int x, int y, int z) {
	int t = x * 1001 * 1001 + y * 1001 + z;
	if (fd(t)) return 0;
	else ins(t);
	return 1;
}

__inline void recover() {
	for (; cr; ) adj[rec[--cr]] = -1;
	e = 0;
}

int main() {
	int T; scanf("%d", &T);
	memset(adj, -1, sizeof adj);
	for (; T--; ) {
		//S.clear();
		recover();
		int n, m; scanf("%d%d", &n, &m);
		int ans = 0;
		for (int i = 0; i < m; i++) {
			char a1, a2; int a, b;
			scanf(" %c=%d,%c=%d", &a1, &a, &a2, &b);
			if (a <= 0 || b <= 0 || a > n || b > n) continue;
			if (a1 > a2) { swap(a1, a2); swap(a, b); }
			//printf("%c %d %c %d\n", a1, a, a2, b);
			if (a1 != 'X' && a2 != 'X') {	
				for (int j = 1; j <= n; j++)
					ans += elim(j, a, b);
			}
			else if (a1 != 'Y' && a2 != 'Y') {	
				for (int j = 1; j <= n; j++)
					ans += elim(a, j, b);
			}
			else if (a1 != 'Z' && a2 != 'Z') {	
				for (int j = 1; j <= n; j++)
					ans += elim(a, b, j);
			}
		}
		printf("%d\n", ans);
	}
	
	return 0;
}