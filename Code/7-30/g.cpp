
#include <bits/stdc++.h>
using namespace std;

const int maxn = 111111;
int T, n, cnt, x, y, rt, deg[maxn], adj[maxn];
long long ans[maxn], sum[maxn];
long long final_ans;

struct edge {
	int nxt, v;
} e[maxn * 2];

void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

int dfs(int u, int father) {
	if (deg[u] == 1) return 1;
	sum[u] = 0;
	for (int p = adj[u]; p; p = e[p].nxt) {
		int v = e[p].v;
		if (v == father) continue;
		int tmp = dfs(v, u);
		//cout << u << " " << v << " " << tmp << endl;
		sum[u] += tmp;
		ans[u] += ans[v];
	}
	ans[u] += sum[u];
	return 2 - sum[u] % 2;
}

void redfs(int u, int father, int tans, int tsum) {
	if (deg[u] == 1) return;
	//cout << u << " " << final_ans << endl;
	final_ans = min(final_ans, ans[u] + tans + tsum);
	for (int p = adj[u]; p; p = e[p].nxt) {
		int v = e[p].v;
		if (v == father) continue;
		redfs(v, u, tans + ans[u] - ans[v] - (2 - sum[v] % 2) + tsum, 2 - (tsum + sum[u] - (2 - sum[v] % 2)) % 2);
	}
}

int main() {
	scanf("%d", &T);
	for (int Q = 1; Q <= T; ++Q) {
		scanf("%d", &n);
		memset(deg, 0, sizeof(*deg) * (n + 1));
		memset(adj, 0, sizeof(*adj) * (n + 1));
		memset(sum, 0, sizeof(*sum) * (n + 1));
		memset(ans, 0, sizeof(*ans) * (n + 1));
		cnt = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			deg[x]++, deg[y]++;
			addedge(x, y);
			addedge(y, x);
		}
		
		if (n == 1) {
			printf("0\n"); continue;
		}
		if (n == 2) {
			printf("1\n"); continue;
		}
		for (int i = 1; i <= n; ++i)
			if (deg[i] > 1) rt = i;
		dfs(rt, 0);
		final_ans = ans[rt];
//for (int i = 1; i <= n; ++i) cout << i << " " << ans[i] << " " << sum[i] << endl;
		redfs(rt, 0, 0, 0);
		cout << final_ans << endl;
	}
}
