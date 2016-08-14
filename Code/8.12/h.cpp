#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXD = 100000;
const int MAXN = 111111;
const int MAXNODE = 4000000;
int n, cnt, DFN, val[MAXN], id[MAXN], L[MAXN], fa[MAXN], R[MAXN], rt[MAXN], size[MAXN], f[MAXN][2], adj[MAXN];
LL c[MAXN], ans, preans;

struct edge {
	int v, nxt;
} e[MAXN * 2];

struct Segmenttree {
	int lc, rc, sum;
} tr[MAXNODE];

inline void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

inline void predfs(int u) {
	L[u] = ++DFN; size[u] = 1; id[DFN] = u;
	for (int p = adj[u]; p; p = e[p].nxt) {
		predfs(e[p].v);
		size[u] += size[e[p].v];
	}
	R[u] = DFN;
}

inline int getnode() {
	tr[++cnt].sum = 0;
	tr[cnt].lc = tr[cnt].rc = 0;
	return cnt;
}

inline void addnumber(int &u, int v, int l, int r, int x) {
	u = getnode();
	tr[u].sum = tr[v].sum + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	if (x > mid) {
		tr[u].lc = tr[v].lc;
		addnumber(tr[u].rc, tr[v].rc, mid + 1, r, x);
	} else {
		tr[u].rc = tr[v].rc;
		addnumber(tr[u].lc, tr[v].lc, l, mid, x);
	}
}

inline int query(int u, int v, int l, int r, int K) {
	if (tr[u].sum - tr[v].sum < K) return MAXD;
	if (l == r) return l;
	int mid = l + r >> 1, temp = tr[tr[u].lc].sum - tr[tr[v].lc].sum;
	if (temp >= K) return query(tr[u].lc, tr[v].lc, l, mid, K);
	else return query(tr[u].rc, tr[v].rc, mid + 1, r, K - temp);
}

inline int lowbit(int k) {
	return k & (-k);
}

inline void modify(int k, LL x) {
	for (; k; k -= lowbit(k)) c[k] += x;
}

LL query(int k) {
	LL ret = 0;
	for (; k <= MAXD; k += lowbit(k)) ret += c[k];
	return ret;
}

inline void dfs(int u) {
	modify(f[u][0], (LL)f[u][1] - f[u][0]);
	//cout << u << " " << ans << " " << query(val[u]) << endl;
	ans = max(ans, preans + query(val[u]));
	for (int p = adj[u]; p; p = e[p].nxt) dfs(e[p].v);
	modify(f[u][0], (LL)f[u][0] - f[u][1]);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(adj, 0, sizeof(*adj) * (n + 1));
		for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
		cnt = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d", &fa[i + 1]);
			addedge(fa[i + 1], i + 1);
		}
		
		cnt = DFN = 0;
		predfs(1);
		rt[0] = tr[0].sum = tr[0].lc = tr[0].rc = 0;
		for (int i = 1; i <= n; ++i)
			addnumber(rt[i], rt[i - 1], 1, MAXD, val[id[i]]);
		for (int i = 1; i <= n; ++i) {
			f[i][0] = query(rt[R[i]], rt[L[i] - 1], 1, MAXD, (size[i] + 1) / 2);
			f[i][1] = query(rt[R[i]], rt[L[i] - 1], 1, MAXD, (size[i] + 1) / 2 + 1);
			//cout << i << " " << f[i][0] << " " << f[i][1] << " " << size[i] << endl;
		}
		
		memset(c, 0, sizeof(c));
		preans = 0;
		for (int i = 1; i <= n; ++i) preans += f[i][0];
		ans = preans;
		dfs(1);
		cout << ans << endl;
	}
}
