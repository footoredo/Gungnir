#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 211111;
const LL INF = 1e18 + 11;
int deg[MAXN], adj[MAXN], c[MAXN], n, cnt, tot;
LL val[MAXN], lim[MAXN], K, T, rt, table[MAXN], ans;

struct edge {
	int v, nxt;
} e[MAXN * 2 + 1];

inline void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt; deg[y]++;
}

inline int lowbit(int k) {
	return k & (-k);
}

inline void modify(int k, int x) {
	for (; k <= tot; k += lowbit(k)) c[k] += x;
}

inline int query(int k) {
	int ret = 0;
	for (; k; k -= lowbit(k)) ret += c[k];
	return ret;
}

inline void dfs(int k) {
	ans += query(lim[k]);
	modify(val[k], 1);
	for (int p = adj[k]; p; p = e[p].nxt) dfs(e[p].v);
	modify(val[k], -1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> T;
	for (; T; --T) {
		cin >> n >> K;
		ans = tot = cnt = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> val[i];
			lim[i] = (val[i]) ? K / val[i] : INF;
			table[++tot] = val[i];
			table[++tot] = lim[i];
			deg[i] = 0; adj[i] = 0;
		}
		rt = 0;
		for (int i = 1; i < n; ++i) {
			int x, y;
			cin >> x >> y;
			addedge(x, y);
		}
		for (int i = 1; i <= n; ++i)
			if (!deg[i]) rt = i;
		sort(table + 1, table + tot + 1);
		tot = unique(table + 1, table + tot + 1) - table - 1;
		for (int i = 1; i <= n; ++i) {
			val[i] = lower_bound(table + 1, table + tot + 1, val[i]) - table;
			lim[i] = lower_bound(table + 1, table + tot + 1, lim[i]) - table;
		}
		
		memset(c, 0, sizeof(c));
		dfs(rt);
		cout << ans << endl;
	}
}
