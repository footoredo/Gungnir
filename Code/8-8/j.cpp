#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int MAXM = 1111111;
const int INF = 1000000000;
int adj[MAXN], deg[MAXN], head[5], tail[5], seq[3][MAXN], kind[MAXN], n, m, cnt, x, y, T;

struct edge {
	int v, nxt, boo;
} e[MAXM];

inline void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

int solve(int type) {
	memset(deg, 0, sizeof(*deg) * (n + 1));
	for (int i = 1; i <= cnt; ++i) {
		deg[e[i].v]++;
		e[i].boo = 0;
	}
	head[1] = head[2] = 1;
	tail[1] = tail[2] = 0;
	for (int i = 1; i <= n; ++i)
		if (!deg[i]) seq[kind[i]][++tail[kind[i]]] = i;
	int nowans = 0, sum = 0;
	for (;; type = 3 - type) {
		for (int i = head[type]; i <= tail[type]; ++i) {
			int u = seq[type][i];
			sum++;
			for (int p = adj[u]; p; p = e[p].nxt) {
				int v = e[p].v;
				if (!e[p].boo && kind[v] == kind[u]) {
					e[p].boo = 1;
					deg[v]--;
					if (!deg[v]) seq[type][++tail[type]] = v;
				} 
			}
		}
		if (sum == n) break;
		nowans++;
		for (int i = head[type]; i <= tail[type]; ++i) {
			int u = seq[type][i];
			for (int p = adj[u]; p; p = e[p].nxt) {
				int v = e[p].v;
				if (!e[p].boo && kind[v] != type) {
					e[p].boo = 1;
					deg[v]--;
			//cout << "EDF: " << u << " " << v << " " << deg[v] << endl;
					if (!deg[v]) seq[3 - type][++tail[3 - type]] = v;
				}
			}
		}
		head[type] = tail[type] + 1;
	}
	return nowans;
}

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d", &kind[i]);
		memset(adj, 0, sizeof(*adj) * (n + 1));
		cnt = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			addedge(x, y);
		}
		
		int s[3];
		s[1] = s[2] = 0;
		for (int i = 1; i <= n; ++i) s[kind[i]]++;
		if (!s[1] || !s[2]) {
			printf("0\n");
			continue;
		}
		
		int ans = INF;
		for (int type = 1; type <= 2; ++type) ans = min(ans, solve(type));
//cout << solve(1) << endl;
		printf("%d\n", ans);
	}
}
