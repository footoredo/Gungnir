#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 55;
const int MOD = 1e9 + 7;
int invc[MAXN][MAXN], c[MAXN][MAXN], from[MAXN][MAXN], size[MAXN], invF[MAXN], dp[MAXN][MAXN][MAXN], G[MAXN][MAXN][MAXN][MAXN], son[MAXN], F[MAXN], ans[MAXN];
int n, x, y, rt;

vector<int> vec[MAXN];

vector<int> tr[MAXN];

int Fpow(int x, int K, int MOD) {
	int ret = 1;
	for (; K; K >>= 1) {
		if (K & 1) ret = (LL)ret * x % MOD;
		x = (LL)x * x % MOD;
	}
	return ret;
}

void pre() {
	for (int i = 0; i < MAXN; ++i) {
		c[i][i] = c[i][0] = 1;
		for (int j = 1; j < i; ++j) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
		for (int j = 0; j <= i; ++j) invc[i][j] = Fpow(c[i][j], MOD - 2, MOD);
	}
	for (int l1 = 1; l1 < MAXN; ++l1)
		for (int l2 = 1; l2 < MAXN && l1 + l2 < MAXN; ++l2)
			for (int p1 = 1; p1 <= l1; ++p1)
				for (int p2 = 1; p2 <= l2; ++p2) {
					G[l1][l2][p1][p2] = ((LL)G[l1][l2][p1][p2 - 1] + (LL)c[p1 + p2 - 2][p2 - 1] * c[l2 - p2 + 1 + l1 - p1][l1 - p1]) % MOD;
				}
}

inline void dfs(int u, int fa) {
	size[u] = 0; from[u][u] = u; F[u] = 1;
	for (int i = 0; i < tr[u].size(); ++i)
		if (tr[u][i] != fa) {
			int v = tr[u][i];
			dfs(v, u);
			size[u] += size[v];
			F[u] = (LL)F[u] * F[v] % MOD * c[size[u]][size[v]] % MOD;
			for (int j = 1; j <= n; ++j)
				if (from[v][j]) from[u][j] = v;
		}
	invF[u] = Fpow(F[u], MOD - 2, MOD);
	size[u]++;
	if (size[u] == 1) {
		dp[u][u][1] = 1;
		return;
	}
	for (int i = 1; i <= n; ++i) {
		if (!from[u][i]) continue;
		if (u == i) {
			dp[u][u][size[u]] = F[u];
			continue;
		}
		int v = from[u][i];
		int oriF = (LL)F[u] * invF[v] % MOD * invc[size[u] - 1][size[v]] % MOD; 
		for (int k = 1; k < size[u]; ++k)
			for (int p = 1; p <= size[v] && p <= k; ++p) {
				int tmp = (LL)dp[v][i][p] * c[k - 1][p - 1] % MOD * c[size[u] - 1 - k][size[v] - p] % MOD;
				dp[u][i][k] = ((LL)tmp * oriF + dp[u][i][k]) % MOD;
			}
	}
}

void redfs(int u, int fa) {
	for (int i = 0; i < tr[u].size(); ++i)
		if (tr[u][i] != fa) {
			redfs(tr[u][i], u);
			int v = tr[u][i];
			int oriF = (LL)F[u] * invF[v] % MOD * invc[size[u] - 1][size[v]] % MOD; 
			ans[u] = ((LL)ans[tr[u][i]] * c[size[u] - 1][size[tr[u][i]]] % MOD * oriF + ans[u]) % MOD;
		}
	int cnt = 0;
	for (int i = 0; i < tr[u].size(); ++i)
		if (tr[u][i] != fa) son[++cnt] = tr[u][i];
	vec[u].clear();
	for (int i = 1; i <= n; ++i)
		if (from[u][i]) vec[u].push_back(i);
//cout << u << endl;
//for (int i = 1; i <= n; ++i) cout << from[u][i] << " "; cout << endl;
	if (!cnt) return;
	for (int i = u + 1; i <= n; ++i)
		if (from[u][i]) ans[u] = (F[u] + ans[u]) % MOD;
//cout << u << " " << F[u] << " " << ans[u] << " " << endl;
//return;
	for (int i = 1; i <= cnt; ++i)
		for (int j = 1; j <= cnt; ++j) {
			if (i == j) continue;
			int s1 = son[i], s2 = son[j];
			//cout << s1 << " " << s2 << endl;
			int l1 = size[s1], l2 = size[s2], tmpF = 1, s = 0;
			for (int k = 1; k <= cnt; ++k)
				if (k != i && k != j) {
					s += size[son[k]];
					tmpF = (LL)tmpF * c[s][size[son[k]]] % MOD * F[son[k]] % MOD;
				}
			for (int t1 = 0; t1 < vec[s1].size(); ++t1)
				for (int t2 = 0; t2 < vec[s2].size(); ++t2) {
					int v1 = vec[s1][t1], v2 = vec[s2][t2];
					int tmpans = ans[u];
					if (v1 < v2) continue;
					for (int p1 = 1; p1 <= l1; ++p1)
						for (int p2 = 1; p2 <= l2; ++p2)
							ans[u] = ((LL)tmpF * G[l1][l2][p1][p2] % MOD * c[size[u] - 1][l1 + l2] % MOD * dp[s1][v1][p1] % MOD * dp[s2][v2][p2] + ans[u]) % MOD;
					//cout << v1 << " " << v2 << " " << tmpF << " " << ans[u] - tmpans << endl;
				}
		}
}

int main() {
	pre();
	while (scanf("%d%d", &n, &rt) != EOF) {
		memset(dp, 0, sizeof(dp));
		memset(from, 0, sizeof(from));
		for (int i = 1; i <= n; ++i) tr[i].clear();
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			tr[x].push_back(y);
			tr[y].push_back(x);
		}
		
		dfs(rt, 0);
/*for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
		for (int k = 1; k <= size[i]; ++k)
			if (from[i][j]) printf("Dp[%d, %d, %d] = %d\n", i, j, k, dp[i][j][k]);*/
		//cout << F[rt] << endl;
		memset(ans, 0, sizeof(ans));
		redfs(rt, 0);
		printf("%d\n", ans[rt]);
	}
}
