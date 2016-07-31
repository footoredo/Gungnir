#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <bits/stdc++.h>
#define left LEFT123
#define right RIGHT123
using namespace std;

typedef long long LL;

const int maxn = 111111;
const int maxm = 4000000;
const int inf = 1e9;
int left[maxn], right[maxn], adj[maxn], rt[maxn], dis[maxn], id[maxn], fa[maxn], size[maxn], seq[maxn], n, Q, cnt, x, y, dfs_clock, K, P, type;

struct segmenttree {
	int lc, rc, tag, mind, maxd;
	LL sumd;
	inline segmenttree () {};
	inline segmenttree(int a, int b, int c, int d, int e, LL f): lc(a), rc(b), tag(c), mind(d), maxd(e), sumd(f) {};
} tr[maxm];

struct tree {
	int v, nxt;
} e[maxn >> 1];

struct line {
	int l, r;
} lin[maxn];

inline bool cmp_line(const line &p, const line &q) {
	return p.l < q.l;
}

inline void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

inline int getnode() {
	tr[++cnt] = segmenttree(0, 0, 0, inf, 0, 0LL);
	return cnt;
}

inline void update(int u, int l, int r) {
	int lc = tr[u].lc, rc = tr[u].rc;
	tr[u].sumd = tr[lc].sumd + tr[rc].sumd + (LL)tr[u].tag * (r - l + 1);
	tr[u].maxd = max(tr[lc].maxd, tr[rc].maxd) + tr[u].tag;
	tr[u].mind = min(tr[lc].mind, tr[rc].mind) + tr[u].tag;
}

inline void buildtree(int &u, int l, int r) {
	u = getnode();
	if (l == r) {
		tr[u].maxd = tr[u].mind = tr[u].sumd = dis[id[l]];
		return;
	}
	int mid = l + r >> 1;
	buildtree(tr[u].lc, l, mid);
	buildtree(tr[u].rc, mid + 1, r);
	update(u, l, r);
}

inline int query_min(int u, int l, int r, int a, int b, int sumtag) {
	if (l == a && b == r) return tr[u].mind + sumtag;
	int mid = l + r >> 1;
	sumtag += tr[u].tag;
	if (a > mid) return query_min(tr[u].rc, mid + 1, r, a, b, sumtag);
	if (b <= mid) return query_min(tr[u].lc, l, mid, a, b, sumtag);
	return min(query_min(tr[u].lc, l, mid, a, mid, sumtag), query_min(tr[u].rc, mid + 1, r, mid + 1, b, sumtag));
}

inline int query_max(int u, int l, int r, int a, int b, int sumtag) {
	if (l == a && b == r) return tr[u].maxd + sumtag;
	int mid = l + r >> 1;
	sumtag += tr[u].tag;
	if (a > mid) return query_max(tr[u].rc, mid + 1, r, a, b, sumtag);
	if (b <= mid) return query_max(tr[u].lc, l, mid, a, b, sumtag);
	return max(query_max(tr[u].lc, l, mid, a, mid, sumtag), query_max(tr[u].rc, mid + 1, r, mid + 1, b, sumtag));
}

inline LL query_sum(int u, int l, int r, int a, int b, int sumtag) {
	if (l == a && b == r) return tr[u].sumd + (LL)sumtag * (r - l + 1);
	int mid = l + r >> 1;
	sumtag += tr[u].tag;
	if (a > mid) return query_sum(tr[u].rc, mid + 1, r, a, b, sumtag);
	if (b <= mid) return query_sum(tr[u].lc, l, mid, a, b, sumtag);
	return query_sum(tr[u].lc, l, mid, a, mid, sumtag) + query_sum(tr[u].rc, mid + 1, r, mid + 1, b, sumtag);
}

inline void modify(int &u, int v, int l, int r, int a, int b, int delta) {
	u = getnode();
	tr[u] = tr[v];
	if (l == a && b == r) {
		tr[u].tag += delta;
		tr[u].maxd += delta;
		tr[u].mind += delta;
		tr[u].sumd += (LL)delta * (r - l + 1);
		return;
	}
	int mid = l + r >> 1;
	if (a > mid) modify(tr[u].rc, tr[v].rc, mid + 1, r, a, b, delta);
	else {
		if (b <= mid) modify(tr[u].lc, tr[v].lc, l, mid, a, b, delta);
		else {
			modify(tr[u].lc, tr[v].lc, l, mid, a, mid, delta);
			modify(tr[u].rc, tr[v].rc, mid + 1, r, mid + 1, b, delta);
		}
	}
	update(u, l, r);
}

void bfs() {
	int h = 1, t = 1;
	seq[1] = 1; fa[1] = 0; size[1] = 1; dis[1] = 0;
	for (; h <= t; ++h) {
		int u = seq[h];
		for (int p = adj[u]; p; p = e[p].nxt) {
			int v = e[p].v;
			if (v == fa[u]) continue;
			seq[++t] = v;
			size[v] = 1;
			fa[v] = u;
			dis[v] = dis[u] + 1;
		}
	}
	for (int i = n; i > 1; --i) size[fa[seq[i]]] += size[seq[i]];
	left[1] = 1; right[1] = n; id[1] = 1;
	for (int i = 1; i <= n; ++i) {
		int u = seq[i];
		if (size[u] == 1) continue;
		int nowdfn = left[u] + 1;
		for (int p = adj[u]; p; p = e[p].nxt) {
			int v = e[p].v;
			if (v == fa[u]) continue;
			left[v] = nowdfn;
			right[v] = left[v] + size[v] - 1;
			id[left[v]] = v;
			nowdfn += size[v];
		}
	}
	
	buildtree(rt[1], 1, n);
	for (int i = 1; i <= n; ++i) {
		int u = seq[i];
		for (int p = adj[u]; p; p = e[p].nxt) {
			int v = e[p].v;
			if (v == fa[u]) continue;
			modify(rt[v], rt[u], 1, n, 1, n, 1);
			modify(rt[v], rt[v], 1, n, left[v], right[v], -2);
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &Q) != EOF) {
		memset(adj, 0, sizeof(*adj) * (n + 1));
		cnt = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			addedge(x, y);
			addedge(y, x);
		}
		
		cnt = rt[1] = 0;
		tr[0] = segmenttree(0, 0, 0, inf, 0, 0LL);
		bfs();
		long long lastans = -1, ans;
		int mxr;
		for (; Q; --Q) {
			lastans = max(0LL, lastans);
			scanf("%d%d%d", &K, &P, &type);
			P = (lastans + P) % n + 1;
			for (int i = 1; i <= K; ++i) {
				scanf("%d", &x);
				lin[i].l = left[x], lin[i].r = right[x];
			}
			sort(lin + 1, lin + K + 1, cmp_line);
			lin[++K].l = n + 1;
			bool flag = false;
			if (type == 1) {
				ans = mxr = 0;
				for (int i = 1; i <= K; ++i) {
					if (mxr < lin[i].l - 1) {
						flag = true;
						ans += query_sum(rt[P], 1, n, mxr + 1, lin[i].l - 1, 0);
					}
					mxr = max(mxr, lin[i].r);
				}
				if (!flag) ans = -1;
			}
			if (type == 2) {
				ans = inf, mxr = 0;
				for (int i = 1; i <= K; ++i) {
					if (mxr < lin[i].l - 1) {
						flag = true;
						ans = min(ans, (LL)query_min(rt[P], 1, n, mxr + 1, lin[i].l - 1, 0));
					}
					mxr = max(mxr, lin[i].r);
				}
				if (!flag) ans = -1;
			}
			if (type == 3) {
				ans = 0, mxr = 0;
				for (int i = 1; i <= K; ++i) {
					if (mxr < lin[i].l - 1) {
						flag = true;
						ans = max(ans, (LL)query_max(rt[P], 1, n, mxr + 1, lin[i].l - 1, 0));
					}
					mxr = max(mxr, lin[i].r);
				}
				if (!flag) ans = -1;
			}
			printf("%lld\n", lastans = ans);
		}
	}
}
