#include <bits/stdc++.h>
#define stack STACK123
using namespace std;

const int MAXN = 111111;
const int MAXL = 111111;
const int MAXH = 20;
int fa[MAXN][MAXH], adj[MAXN], dep[MAXN], stack[MAXN], node[MAXN][2], L[MAXN], R[MAXN], seq[MAXN];
int Q, n, m, cnt, DFN, maxd, Node;
char str1[MAXL], str2[MAXL];

struct edge {
	int v, nxt;
} e[MAXN * 2];

map<string, int> mp;
vector<int> vec[MAXN], v[MAXN], d[MAXN];

inline bool cmp_dfs(int u, int v) {
	return L[u] < L[v];
}

inline void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

inline void dfs(int u, int father) {
	fa[u][0] = father; dep[u] = dep[father] + 1; L[u] = ++DFN;
	for (int h = 1; h < MAXH; ++h) fa[u][h] = fa[fa[u][h - 1]][h - 1];
	for (int p = adj[u]; p; p = e[p].nxt)
		if (e[p].v != father) dfs(e[p].v, u);
	R[u] = DFN;
}

inline int getlca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	if (dep[u] != dep[v]) {
		for (int h = MAXH - 1; h >= 0; --h)
			if ((dep[v] - dep[u]) & (1 << h)) v = fa[v][h];
	}
	for (int h = MAXH - 1; h >= 0; --h)
		if (fa[u][h] != fa[v][h]) u = fa[u][h], v = fa[v][h];
	return u == v ? u : fa[u][0];
}

inline void dfs2(int u, int fa, int dep) {
	if (dep > maxd) maxd = dep, Node = u;
	for (int i = 0; i < v[u].size(); ++i)
		if (v[u][i] != fa) dfs2(v[u][i], u, dep + d[u][i]);
}

int main() {
	while (scanf("%d%d", &n, &Q) != EOF) {
		memset(adj, 0, sizeof(*adj) * (n + 1));
		for (int i = 1; i <= n; ++i) vec[i].clear();
		mp.clear(); m = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str1);
			if (!mp.count(string(str1))) {
				mp[string(str1)] = ++m;
				vec[m].push_back(i);
			} else vec[mp[str1]].push_back(i);
		}
		
		cnt = DFN = 0;
		for (int i = 1; i < n; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			addedge(x, y);
			addedge(y, x);
		}
		dfs(1, 0);
		
		for (int i = 1; i <= m; ++i) {
			if (vec[i].size() == 1) {
				node[i][0] = node[i][1] = vec[i][0];
				continue;
			}
			cnt = 0;
			for (int j = 0; j < vec[i].size(); ++j) seq[++cnt] = vec[i][j];
			sort(seq + 1, seq + cnt + 1, cmp_dfs);
			int top = cnt;
			for (int j = 1; j < top; ++j) seq[++cnt] = getlca(seq[j], seq[j + 1]);
			sort(seq + 1, seq + cnt + 1, cmp_dfs);
			cnt = unique(seq + 1, seq + cnt + 1) - seq - 1;
			for (int j = 1; j <= cnt; ++j) v[seq[j]].clear(), d[seq[j]].clear();
			top = 1; stack[1] = seq[1];
			for (int j = 2; j <= cnt; ++j) {
				while (top > 0 && (L[stack[top]] > L[seq[j]] || L[seq[j]] > R[stack[top]])) --top;
				if (top) {
					v[seq[j]].push_back(stack[top]);
					d[seq[j]].push_back(dep[seq[j]] - dep[stack[top]]);
					v[stack[top]].push_back(seq[j]);
					d[stack[top]].push_back(dep[seq[j]] - dep[stack[top]]);
					stack[++top] = seq[j];
				}
			}
			Node, maxd = 0;
			dfs2(seq[1], 0, 0);
			node[i][0] = Node;
			Node = maxd = 0;
			dfs2(node[i][0], 0, 0);
			node[i][1] = Node;
		}
		
		for (; Q; --Q) {
			scanf("%s%s", str1, str2);
			if (!mp.count(string(str1)) || !mp.count(string(str2))) {
				puts("-1"); continue;
			}
			int x = mp[string(str1)], y = mp[string(str2)];
			int ans = 0;
			for (int i = 0; i < 2; ++i)
				for (int j = 0; j < 2; ++j) {
					ans = max(ans, 1 + dep[node[x][i]] + dep[node[y][j]] - dep[getlca(node[x][i], node[y][j])] * 2);
				}
			printf("%d\n", ans);
		}
	}
}
