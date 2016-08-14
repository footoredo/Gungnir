#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 111111;
int adj[MAXN], L[MAXN], R[MAXN], dep[MAXN], fa[MAXN], n, Q, cnt, DFN, u;
pair<int, int> tr[MAXN << 2];
char str[111];

struct edge {
	int v, nxt;
} e[MAXN << 2];

inline void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

inline int getnode(int l, int r) {
	return (l + r) | (l != r);
}

inline void buildtree(int l, int r) {
	int k = getnode(l, r);
	tr[k] = make_pair(1, 1);
	if (l == r) return;
	int mid = l + r >> 1;
	buildtree(l, mid);
	buildtree(mid + 1, r);
}

inline void modify(int l, int r, int a, int b, pair<int, int> x) {
	int k = getnode(l, r);
	if (l == a && b == r) {
		tr[k] = max(tr[k], x);
		return;
	}
	int mid = l + r >> 1;
	if (a > mid) modify(mid + 1, r, a, b, x);
	else
		if (b <= mid) modify(l, mid, a, b, x);
		else {
			modify(l, mid, a, mid, x);
			modify(mid + 1, r, mid + 1, b, x);
		}
}

inline pair<int, int> query(int l, int r, int pos) {
	int k = getnode(l, r);
	if (l == r) return tr[k];
	int mid = l + r >> 1;
	pair<int, int> tmp = (pos > mid) ? query(mid + 1, r, pos) : query(l, mid, pos);
	return max(tmp, tr[k]);
}

inline void dfs(int u) {
	L[u] = ++DFN; dep[u] = dep[fa[u]] + 1;
	for (int p = adj[u]; p; p = e[p].nxt) dfs(e[p].v);
	R[u] = DFN;
}

int main() {
	while (scanf("%d%d", &n, &Q), n && Q) {
		memset(adj, 0, sizeof(*adj) * (n + 1));
		cnt = 0;
		for (int i = 2; i <= n; ++i) {
			scanf("%d", &fa[i]);
			addedge(fa[i], i);
		}
		
		buildtree(1, n);
		DFN = dep[0] = fa[1] = 0;
		dfs(1);
		LL ans = 0;
		for (; Q; --Q) {
			scanf("%s%d", str, &u);
			if (str[0] == 'Q') {
				ans += query(1, n, L[u]).second;
			} else {
				modify(1, n, L[u], R[u], make_pair(dep[u], u));
			}
		}
		cout << ans << endl;
	}
}
