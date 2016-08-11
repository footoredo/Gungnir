#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1111;
const int MAXM = 11111;
int n, m, fa[MAXN];

struct edge {
	int x, y, w;
} e[MAXM];

bool cmp(const edge &p, const edge &q) {
	return p.w < q.w;
}

int find(int k) {
	if (fa[k] == k) return k;
	return fa[k] = find(fa[k]);
}

int main() {
	while (scanf("%d%d", &n, &m), n) {
		for (int i = 1; i <= m; ++i) scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
		sort(e + 1, e + m + 1, cmp);
		int ans = -1, j = 1;
		for (int i = 1; i <= n; ++i) fa[i] = i;
		for (int i = 1; i <= n / 2; ++i) {
			while (find(e[j].x) == find(e[j].y)) j++;
			int u = find(e[j].x), v = find(e[j].y);
			fa[u] =  v;
			ans = e[j].w;
		}
		printf("%d\n", ans);
	}
}
