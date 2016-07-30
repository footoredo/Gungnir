#include <bits/stdc++.h>
using namespace std;

const int maxn = 111111;
const int inf = 1000000000;
int f[maxn][3][2], adj[maxn], deg[maxn], temp[3][2];
int T, n, x, y, rt, cnt;

struct edge {
	int v, nxt;
} e[maxn * 2];

void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt; deg[x]++;
}

void dfs(int u, int father) {
	if (deg[u] == 1) {
		f[u][1][0] = 0;
		return;
	}
	bool flag = false;
	//puts("---------");
	f[u][0][0] = 0;
	for (int p = adj[u]; p; p = e[p].nxt) {
		int v = e[p].v;
		if (v == father) continue;
		dfs(v, u);
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 2; ++k) {
				temp[j][k] = f[u][j][k];
				f[u][j][k] = inf;
			}
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 2; ++k) {
				for (int jj = 1; jj < 3; ++jj)
					for (int kk = 0; kk < 2 - k; ++kk) {
						int t = j + jj;
						if (t > 2) t -= 2;
						if (t > 2) t -= 2;
						f[u][t][k + kk] = min(f[u][t][k + kk], f[v][jj][kk] + temp[j][k] + jj);
					}
			}
		f[u][1][1] = min(f[u][1][1], f[u][2][0]);
		//cout << "middle: " << u << " " << f[u][0][0] << " " << f[u][0][1] << " " << f[u][1][0] << " " << f[u][1][1] << " " << f[u][2][0] << " " << f[u][2][1] << endl;
	}
	//f[u][1][1] = min(f[u][1][1], f[u][2][0]);
	
	//cout << "Final: " << u << " " << f[u][1][0] << " " << f[u][1][1] << " " << f[u][2][0] << " " << f[u][2][1] << endl;
}

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d", &n);
		cnt = 0;
		memset(deg, 0, sizeof(deg));
		memset(adj, 0, sizeof(adj));
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			addedge(x, y);
			addedge(y, x);
		}
		
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}
		if (n == 2) {
			cout << 1 << endl;
			continue;
		}
		for (int i = 1; i <= n; ++i)
			if (deg[i] > 1) rt = i;	
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 2; ++k)
					f[i][j][k] = inf;
		dfs(rt, 0);
		int u = rt;
		//cout << u << " " << f[u][1][0] << " " << f[u][1][1] << " " << f[u][2][0] << " " << f[u][2][1] << endl;
		
		int ans = inf, leaf = 0;
		for (int i = 1; i <= n; ++i) leaf += (deg[i] == 1);
		for (int i = 0; i <= leaf % 2; ++i)
			for (int j = 1; j < 3; ++j)
				ans = min(ans, f[rt][j][i]);
		cout << ans << endl;
	}
}
