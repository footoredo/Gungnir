#include <bits/stdc++.h>
using namespace std;

const int N = 222, M = N * N * 10;

char s[N];
int a[10], b[10], w[N][N], S, T, cc, n;

int nxt[M], f[M], adj[N], e, cur[N];
int v[M];
__inline void ins(int u0, int v0, int w0, int w1) {
	if (!w0 && !w1) return;
	//printf("%d %d %d %d\n", u0, v0, w0, w1);
	v[e] = v0; nxt[e] = adj[u0]; f[e] = w0; adj[u0] = e++;
	v[e] = u0; nxt[e] = adj[v0]; f[e] = w1; adj[v0] = e++;
}

void clear() {
	memset(adj, -1, sizeof(*adj) * cc); e = 0;
}

int Q[N], d[N], p[N], cp;
int bfs(int S, int T) {
	memset(d, -1, sizeof(*d) * cc);
	int l = 0, r = 0; Q[r++] = S; d[S] = 0;
	for (; l < r; ) {
		int u = Q[l++]; cur[u] = adj[u];
		for (int e = adj[u]; ~e; e = nxt[e]) if (f[e]) {
			if (!~d[v[e]]) {
				d[v[e]] = d[u] + 1;
				Q[r++] = v[e];
			}
		}
	}
	return d[T];
}

__inline int min(const short& x, const int& y) {
	return x < y ? x : y;
}
 
int dfs(int u, int ext) {
	if (u == T) return ext;
	int ret = 0;
	for (int &e = cur[u]; ~e; e = nxt[e]) {
		if (ext == 0) break;
		if (d[v[e]] == d[u] + 1 && f[e]) {
			int flow = dfs(v[e], min(f[e], ext));
			if (flow > 0) {
				f[e] -= flow; f[e^1] += flow;
				ret += flow, ext -= flow;
			}
		}
	}
	if (!~cur[u]) d[u] = -1;
	return ret;
}

int dinic(int S, int T) {
	int ret = 0;
	for (; ~bfs(S, T); ) {
		ret += dfs(S, 1000000000);
	}
	//printf("%d\n", ret);
	return ret;
}

int node[10];

int solve() {
	//printf("%d %d\n", S, T);	
	int ans = 0; e = 0;
	memset(adj, -1, sizeof adj);
	for (int i = 0; i < 10; i++) {
		node[i] = cc++;
		ins(node[i], T, (b[i] - a[i]) * 2, 0);
		//ans -= (b[i] - a[i]) * 2;
	}
	//clear();
	//printf("%d\n", cc);
	for (int i = 0; i < n; i++) {
		ins(i, node[s[i] - '0'], 10000000, 0);
		ins(i, T, a[s[i] - '0'] * 2, 0);
		int sum = 0;
		for (int j = 0; j < n; j++) if (i != j) {
			sum += w[i][j] + w[j][i]; ans += w[i][j] + w[j][i];
			//if (mask == 17) printf("%d %d\n", i, j);
			if (i > j) ins(i, j, w[i][j] + w[j][i], w[i][j] + w[j][i]);
		}
		ins(S, i, sum, 0);
	}
	//puts("done");
	
	//if (mask == 17) puts("xxx"); 
	//printf("%d\n", ans);
	ans -= dinic(S, T);
	//if (mask == 34) printf("%d\n", ans);
	assert(!(ans & 1));
	//cout << bitset<10>(mask) << endl;
	return ans / 2;
}

int main() {
	int TT; scanf("%d", &TT);
	for (int ca = 1; ca <= TT; ca++) {
		scanf("%d", &n);
		scanf("%s", s); cc = n; S = cc++; T = cc++;
		int mask0 = 0;
		for (int i = 0; i < n; i++) mask0 |= 1<<s[i]-'0';
		for (int i = 0; i < 10; i++) scanf("%d %d", &a[i], &b[i]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &w[i][j]);
		
		int ans = 0;
		ans = max(ans, solve());
		
		printf("Case #%d: %d\n", ca, ans);
	}
	
	return 0;
}
