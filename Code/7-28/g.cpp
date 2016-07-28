#include <bits/stdc++.h>
#define stack STACK123
typedef long long LL;
using namespace std;

const int maxn = 222222;
int rt[maxn], head[maxn], last[maxn], deg[maxn], stack[maxn], vis[maxn], dfn[maxn], low[maxn], wei[maxn], fa_edge[maxn], size[maxn], seq[maxn], f[maxn], tot[maxn];
int x, y, w, n, m, cnt, top, dfs_clock, sum, T, h, t;
LL s[maxn]; 

struct edge {
	int to, front, w;
	bool boo;
} e[maxn * 2];

struct tree {
	int to, x, y, front;
	LL w;
} tr[maxn * 2];

inline void addedge(int x, int y, int w) {
	e[++cnt].to = y; e[cnt].boo = false; e[cnt].w = w; e[cnt].front = head[x]; head[x] = cnt;
}

inline void addedge_tree(int x, int y, int pre_x, int pre_y, int w) {
	tr[++m].to = y; tr[m].x = pre_x; tr[m].y = pre_y; tr[m].w = w; tr[m].front = last[x]; last[x] = m; deg[x]++;
}

void tarjan(int u, int from) {
	dfn[u] = low[u] = ++dfs_clock; vis[u] = 1; stack[++top] = u;
	for (int p = head[u]; p; p = e[p].front) {
		if ((p ^ 1) == from) continue;
		int v = e[p].to;
		if (vis[v] > 0) {
			if (vis[v] == 2) continue;
			low[u] = min(low[u], dfn[v]);
		} else {
			tarjan(v, p);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) e[p].boo = e[p ^ 1].boo = true;
		}
	}
	if (dfn[u] != low[u]) return;
	++sum; tot[sum] = 1;
	while (stack[top] != u) {
		f[stack[top]] = sum;
		vis[stack[top]] = 2;
		tot[sum]++;
		--top;
	}
	f[stack[top]] = sum;
	vis[stack[top]] = 2;
	--top;
}

void dfs(int k, int fa) {
	size[k] = tot[k]; seq[++t] = k; vis[k] = 1;
	for (int p = last[k]; p; p = tr[p].front) {
		if (vis[tr[p].to]) continue;
		fa_edge[tr[p].to] = p ^ 1;
		rt[tr[p].to] = rt[k];
		dfs(tr[p].to, k);
		size[k] += size[tr[p].to];
	}
}

bool check(LL mid) {
	for (int i = 1; i <= n; ++i) s[i] = (LL)wei[i];
	for (int i = 1; i <= sum; ++i) {
		int u = seq[i];
		if (fa_edge[u] == 0) continue;
		int p = fa_edge[u];
		int v = tr[p].to;
		int x = tr[p].x, y = tr[p].y;
		if (f[x] != u) swap(x, y);
		if (s[x] + tr[p].w <= mid) {
			s[x] += tr[p].w;
		} else {
			if (s[y] + tr[p].w <= mid) s[y] += tr[p].w;
			else return false;
		}
	}
	for (int i = 1; i <= n; ++i)
		if (s[i] > mid) return false;
	return true;
}

int main() {
	scanf("%d", &T);
	for(int Q = 1; Q <= T; ++Q) {
		scanf("%d%d", &n, &m);
		cnt = 1;
		memset(head, 0, sizeof(*head) * (n + 1));
		memset(vis, 0, sizeof(*vis) * (n + 1));
		memset(last, 0, sizeof(*last) * (n + 1));
		memset(deg, 0, sizeof(*deg) * (n + 1));
		memset(dfn, 0, sizeof(*dfn) * (n + 1));
		for (int i = 1; i <= n; ++i) scanf("%d", &wei[i]);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d", &x, &y, &w);
			addedge(x, y, w);
			addedge(y, x, w);
		}
		
		sum = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i]) continue;
			dfs_clock = 0; top = 0; 
			tarjan(i, -1);
		}
		m = 1;
		for (int i = 2; i <= cnt; ++i)
			if (e[i].boo) addedge_tree(f[e[i ^ 1].to], f[e[i].to], e[i ^ 1].to, e[i].to, e[i].w);
		
		memset(vis, 0, sizeof(vis));
		h = 1, t = 0;
		for (int i = 1; i <= sum; ++i) {
			if (vis[i]) continue;
			rt[i] = i; fa_edge[i] = 0;
			dfs(i, 0);
			//cout << i << " " << rt[i] << " " << size[i] << endl;
		}
		reverse(seq + 1, seq + sum + 1);
		for (int i = 2; i <= m; ++i) {
			int u = tr[i].to, v = tr[i ^ 1].to;
			if (size[u] > size[v]) swap(u, v);
			tr[i].w = (LL)tr[i].w * size[u] * (size[rt[u]] - size[u]);
		}
		
		LL left = 0, right = 1e18;
		while (left < right) {
			LL mid = left + right >> 1;
			if (check(mid)) right = mid; else left = mid + 1;
		}
		cout << "Case " << Q << ": " << left << endl;
	}
}
/*
4 4 4 3 1 2 
1 2 0
2 1 0
2 3 0
3 2 0
1 3 0
3 1 0
1 4 1
4 1 1
1 5 1
5 1 1
4 6 1
6 4 1
4 3 1 4 6
3 4 4 1 6
4 1 1 5 6
1 4 5 1 6
3 2 4 6 2
2 3 6 4 2
Case 1: 60

*/
