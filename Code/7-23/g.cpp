#include <bits/stdc++.h>
#define stack STACK123
using namespace std;

const int maxn = 211111;
const int maxh = 20;
int head[maxn], vis[maxn], son[maxn], dfn[maxn], low[maxn], F[maxn], f[maxn], dep[maxn], fa[maxn][maxh + 1], stack[maxn], col[maxn], b[maxn];
int n, m, Q, x, y, u, v, Time, top, tot, root, rootsum, cnt, sum;

vector<int> tr[maxn];

struct edge {
	int from, to, front;
} e[maxn * 10];

void addedge(int x, int y) {
	e[++cnt].to = y; e[cnt].from = x; e[cnt].front = head[x]; head[x] = cnt;
	e[++cnt].to = x; e[cnt].from = y; e[cnt].front = head[y]; head[y] = cnt;
}

void tarjan1(int k) {
	low[k] = ++Time; dfn[k] = Time; vis[k] = 1; son[k]++;
	cout << k << " " << dfn[k] << " " << low[k] << endl;
	for (int p = head[k]; p != -1; p = e[p].front) {
		int v = e[p].to;
		cout << k << " " << v << endl;
		if (!vis[v]) {
			tarjan1(v);
			if (low[v] < low[k]) low[k] = low[v];
			if (k == root) {
				rootsum++;
				if (rootsum > 1) F[root] = ++sum;
			} else {
				if (low[v] >= dfn[u]) F[k] = ++sum;
			}
		}
	}
	cout << k << " " << dfn[k] << " " << low[k] << endl;
}

void tarjan2(int k, int from) {
	low[k] = ++Time; dfn[k] = Time; vis[k] = 1;
	for (int p = head[k]; p != -1; p = e[p].front) {
		int v = e[k].to;
		if (p == from ^ 1) continue;
		if (vis[v] == 1) low[k] = min(low[k], dfn[v]);
		else {
			stack[++top] = p;
			tarjan2(v, p);
			low[k] = min(low[k], low[v]);
			if (low[v] >= dfn[k]) {
				++sum; 
				int size = 0;
				int x, y;
				while (stack[top] != p) {
					x = e[stack[top]].from, y = e[stack[top]].to;
					b[++size] = x; b[++size] = y;
					--top;
				}
				x = e[stack[top]].from, y = e[stack[top]].to;
				b[++size] = x; b[++size] = y;
				--top;
				for (int i = 1; i <= size; ++i) {
					if (F[b[i]]) {
						tr[F[b[i]]].push_back(sum);
						tr[sum].push_back(F[b[i]]);
					}
					f[b[i]] = sum;
				}
			}
		}
	}
}

void dfs(int k, int father) {
	fa[k][0] = father; dep[k] = dep[father] + 1;
	for (int h = 1; h < maxh; ++h) fa[k][h] = fa[fa[k][h - 1]][h - 1];
	for (int i = 0; i < tr[k].size()	; ++i) {
		if (tr[k][i] != father) dfs(tr[k][i], k);
	}
}

int lca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	for (int h = 0; h < maxh; ++h)
		if ((dep[v] - dep[u]) & (1 << h)) v = fa[v][h];
	for (int h = maxh - 1; h >= 0; --h)
		if (fa[u][h] != fa[v][h]) u = fa[u][h], v = fa[v][h];
	if (u != v) return fa[u][0]; else return u;
}

int main() {
	while (1) {
		scanf("%d%d", &n, &m);
		if (n == 0) return 0;
		memset(head, -1, sizeof(head));
		for (int i = 1; i <= n * 2; ++i) tr[i].clear();
		cnt = -1;
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			addedge(x, y);
		}
		
		memset(son, 0, sizeof(son));
		memset(vis, 0, sizeof(vis));
		memset(low, 0, sizeof(low));
		memset(dfn, 0, sizeof(dfn));
		memset(F, 0, sizeof(F));
		sum = 0; 
		for (int i = 1; i <= 1; ++i) {
			if (vis[i]) continue;
			if (head[i] == -1) {
				F[i] = ++sum;
				continue;
			}
			root = i; Time = 0; rootsum = 0;
			tarjan1(i);
			//cout << "Ruck" << endl;
		}
		
		for (int i = 1; i <= n; ++i) cout << F[i] << " "; cout << endl;
		for (int i = 1; i <= n; ++i) cout << i << " " << dfn[i] << " " << low[i] << endl;
		
		memset(vis, 0, sizeof(vis));
		memset(low, 0, sizeof(low));
		memset(dfn, 0, sizeof(dfn));
		memset(col, 0, sizeof(col));
		memset(f, 0, sizeof(f));
		tot = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i]) continue;
			Time = 0; top = 0;
			tarjan2(i, -1);
		}
		
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= sum; ++i)
			if (!vis[i]) dfs(i, 0);
			
		scanf("%d", &Q);
		for (; Q; --Q) {
			scanf("%d%d", &u, &v);
			int x = lca(f[u], f[v]);
			printf("%d\n", dep[f[u]] + dep[f[v]] - dep[x] * 2);
		}
	}
}