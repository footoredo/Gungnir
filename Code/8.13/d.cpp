#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500;
const int MAXM = 1000000;
const int INF = 1e9;
int adj[MAXN], mark[MAXN], seq[MAXN], id_h[MAXN], id_w[MAXN], id_c[MAXN], id_m[MAXN], cur[MAXN];
int cnt, x, y, H, W, C, M, num_w, num_c, num_m, T, S, Nm, Nc, Nw, maxflow, N;

struct edge {
	int v, nxt, lim;
} e[MAXM];

inline void addedge(int x, int y, int limit) {
	e[++cnt].v = y; e[cnt].lim = limit; e[cnt].nxt = adj[x]; adj[x] = cnt;
	e[++cnt].v = x; e[cnt].lim = 0; e[cnt].nxt = adj[y]; adj[y] = cnt;
}

inline bool bfs() {
	memset(mark, 0, sizeof(mark));
	int h = 1, t = 1;
	seq[1] = S; mark[S] = 1;
	for (; h <= t; ++h) {
		int u = seq[h];
		cur[u] = adj[u];
		for (int p = adj[u]; p > -1; p = e[p].nxt) {
			int v = e[p].v;
			if (e[p].lim && !mark[v]) {
				mark[v] = mark[u] + 1;
				seq[++t] = v;
			}
		}
	}
	return mark[T] > 0;
}

inline void dinic(int u, int sum) {
	if (u == T) maxflow += sum;
	if (mark[u] == mark[T]) return;
	for (int p = cur[u]; p > -1 && sum; p = e[p].nxt) {
		int v = e[p].v;
		if (e[p].lim && mark[v] == mark[u] + 1) {
			int flow = maxflow;
			dinic(v, min(sum, e[p].lim));
			flow = maxflow - flow;
			e[p].lim -= flow;
			e[p ^ 1].lim += flow;
			sum -= flow;
		}
		cur[u] = p;
	}
}

int main() {
	while (scanf("%d%d%d%d%d%d%d", &H, &W, &C, &M, &Nw, &Nc, &Nm), H > -1) {
		memset(adj, -1, sizeof(adj));
		maxflow = N = 0;
		cnt = -1;
		for (int i = 1; i <= H; ++i) id_h[i] = ++N;
		for (int i = 1; i <= W; ++i) id_w[i] = ++N;
		for (int i = 1; i <= C; ++i) id_c[i] = ++N;
		for (int i = 1; i <= M; ++i) id_m[i] = ++N;
		S = N * 2 + 1; T = S + 1; num_w = T + 1; num_c = num_w + 2; num_m = num_c + 2;
		for (int i = 1; i <= N; ++i) addedge(i, i + N, 1);
		addedge(num_w, num_w + 1, Nw);
		addedge(num_c, num_c + 1, Nc);
		addedge(num_m, num_m + 1, Nm);
		for (int i = 1; i <= H; ++i) addedge(S, id_h[i], 1);
		for (int i = 1; i <= M; ++i) addedge(id_m[i] + N, T, 1);
		for (int i = 1; i <= H; ++i)
			for (int j = 1; j <= C; ++j) {
				addedge(id_h[i] + N, num_w, 1);
				addedge(num_w + 1, id_c[j], 1);
			}
		for (int i = 1; i <= W; ++i)
			for (int j = 1; j <= M; ++j) {
				addedge(id_w[i] + N, num_c, 1);
				addedge(num_c + 1, id_m[j], 1);
			}
		for (int i = 1; i <= C; ++i) {
			addedge(id_c[i] + N, num_m, 1);
			addedge(num_m + 1, T, 1);
		}
		for (int i = 1; i <= W; ++i) {
			scanf("%d", &x);
			for (int j = 1; j <= x; ++j) {
				scanf("%d", &y);
				addedge(id_h[y] + N, id_w[i], 1);
			}
		}
		for (int i = 1; i <= C; ++i) {
			scanf("%d", &x);
			for (int j = 1; j <= x; ++j) {
				scanf("%d", &y);
				addedge(id_w[y] + N, id_c[i], 1);
			}
		}
		for (int i = 1; i <= M; ++i) {
			scanf("%d", &x);
			for (int j = 1; j <= x; ++j) {
				scanf("%d", &y);
				addedge(id_c[y] + N, id_m[i], 1);
			}
		}
		while (bfs()) dinic(S, INF);
		printf("%d\n", maxflow);
	}
}
