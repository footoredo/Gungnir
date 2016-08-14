#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 1111;
const int MAXM = 1111111;
int n, m, testcase, cnt, maxflow, S, T, mx[MAXN], mx1[MAXN], mx2[MAXN], fro[MAXN], fro1[MAXN], fro2[MAXN], w[MAXN][MAXN], limit[MAXN], val[MAXN], adj[MAXN], mark[MAXN], seq[MAXN], cur[MAXN], choose[MAXN];

struct edge {
	int v, nxt, lim;
} e[MAXM];

inline void addedge(int x, int y, int lim) {
	if (!lim) return;
	if (lim > INF) lim = INF;
	e[++cnt].v = y; e[cnt].lim = lim; e[cnt].nxt = adj[x]; adj[x] = cnt;
	e[++cnt].v = x; e[cnt].lim = 0; e[cnt].nxt = adj[y]; adj[y] = cnt;
}

bool bfs() {
	memset(mark, 0, sizeof(*mark) * (T + 1));
	int h = 1, t = 1;
	mark[S] = 1; seq[1] = S;
	for (; h <= t; ++h) {
		int u = seq[h];
		cur[u] = adj[u];
		for (int p = adj[u]; p != -1; p = e[p].nxt) {
			int v = e[p].v;
			if (!mark[v] && e[p].lim) seq[++t] = v, mark[v] = mark[u] + 1;
		}
	}
	return mark[T];
}

void dinic(int u, int sum) {
	if (u == T) {
		maxflow += sum;
		return;
	}
	if (mark[u] == mark[T]) return;
	for (int p = cur[u]; p != -1 && sum; p = e[p].nxt) {
		int v = e[p].v;
		if (mark[v] == mark[u] + 1 && e[p].lim) {
			int flow = maxflow;
			dinic(v, min(sum, e[p].lim));
//cout << sum << " " << e[p].lim << endl;
			flow = maxflow - flow;
			e[p].lim -= flow;
			e[p ^ 1].lim += flow;
			sum -= flow;
		}
		cur[u] = p;
	}
}

void dfs(int u) {
	choose[u] = 1;
	for (int p = adj[u]; p != -1; p = e[p].nxt) {
		int v = e[p].v;
		if (!choose[v] && e[p].lim) dfs(v);
	}
}

int main() {
	scanf("%d", &testcase);
	for (; testcase; --testcase) {
		memset(adj, -1, sizeof(adj));
		memset(choose, 0, sizeof(choose));
		scanf("%d%d", &n, &m);
		int total = 0;
		cnt = -1; maxflow = 0; S = 1 << n; T = S + 1;
		for (int i = 0; i < 1 << n; ++i) scanf("%d", &limit[i]);
		for (int i = 0; i < 1 << n; ++i) scanf("%d", &val[i]);
		for (int i = 0; i < 1 << n; ++i) {
			mx[i] = mx1[i] = mx2[i] = -INF;
			fro[i] = fro1[i] = fro2[i] = -1;
			for (int j = 0; j < 1 << m; ++j) {
				scanf("%d", &w[i][j]);
				if (w[i][j] > mx[i]) mx[i] = w[i][j], fro[i] = j;
				if (j < limit[i] && w[i][j] > mx1[i]) mx1[i] = w[i][j], fro1[i] = j;
				if (j >= limit[i] && w[i][j] > mx2[i]) mx2[i] = w[i][j], fro2[i] = j;
			}
			total += mx[i];
		}
		for (int i = 0; i < 1 << n; ++i)
			for (int j = 0; j < 1 << n; ++j)
				if (__builtin_popcount(i) % 2 == 1 && __builtin_popcount(j) % 2 == 0 && __builtin_popcount(i ^ j) == 1) {
					total += (val[i] ^ val[j]);
					addedge(j, i, val[i] ^ val[j]);
				}
		for (int i = 0; i < 1 << n; ++i)
			if (__builtin_popcount(i) % 2 == 1) {
				addedge(S, i, mx[i] - mx1[i]);
				addedge(i, T, mx[i] - mx2[i]);
			} else {
				addedge(S, i, mx[i] - mx2[i]);
				addedge(i, T, mx[i] - mx1[i]);
			}
		
		//cout << 1 << endl;
		while (bfs()) {
			//cout << maxflow << endl;
			dinic(S, INF);
			//cout << maxflow << endl;
		}
		dfs(S);
		for (int i = 0; i < 1 << n; ++i) {
			if (i) printf(" ");
			int x;
			if (__builtin_popcount(i) % 2 == 1) {
				if (choose[i] == 0) x = fro1[i]; else x = fro2[i];
			} else {
				if (choose[i] == 0) x = fro2[i]; else x = fro1[i];
			}
			printf("%d", x);
		}
		puts("");
	}
}
