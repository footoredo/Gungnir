#include <bits/stdc++.h>
using namespace std;

const int maxn = 10;
const int maxm = 55;
const int maxs = 1e5;
const double inf = 1e10;
int T, n, m, K, x, D, maxS, tag, pw[maxn], f[maxm], tmp[maxn], vis[maxm][maxs][2];
double dp[maxm][maxs][2], p[maxn][maxm];

double dfs(int k, int S, int j) {
	if (vis[k][S][j] == tag) return dp[k][S][j];
	vis[k][S][j] = tag;
	int mn = 1e9, mx = 0, tmp[n + 1];
	for (int temp = S, j = 1; j <= n; ++j, temp = temp / D) {
		tmp[j] = temp % D;
		mx = max(mx, tmp[j]);
		mn = min(mn, tmp[j]);
	}
	//cout << k << " " << S << " " << j << " " << dp[k][S][j] << endl;
	if (k > m) {
		if (mx - mn <= 1) dp[k][S][j] = 0.0;
		else dp[k][S][j] = -inf;
		return dp[k][S][j];
	}
	dp[k][S][j] = -inf;
	for (int i = 1; i <= n; ++i) {
		/*if (k == 1) {
			cout << k << " " << S << " " << j << " " << i << " " << tmp[i] << " " << n << endl;
		}*/
		if (tmp[i] == D - 1) continue;
		if (f[k] && j == 0) dp[k][S][0] = max(dp[k][S][0], dfs(k + 1, S + pw[i], 0));
		else dp[k][S][j] = max(dp[k][S][j], (1 - p[i][k]) * dfs(k + 1, S + pw[i], 0) + p[i][k] * (dfs(k + 1, S + pw[i], 1) + 1));
	}
	//cout << k << " " << S << " " << j << " " << dp[k][S][j] << endl;
	return dp[k][S][j];
}

int main() {
	scanf("%d", &T);
	for (tag = 1; tag <= T; ++tag) {
		scanf("%d%d%d", &n, &m, &K);
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= K; ++i) {
			scanf("%d", &x);
			f[x] = 1;
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%lf", &p[i][j]);
		
		D = (m - 1) / n + 2, maxS = 0;
		pw[1] = 1;
		for (int i = 2; i <= n; ++i) pw[i] = pw[i - 1] * D;
		for (int i = 1; i <= n; ++i) maxS = maxS * D + D - 1;
		/*dp[m + 1][0][0] = dp[m + 1][0][1] = 0.0;
		for (int i = m; i; --i) {
			for (int S = 0; S <= maxS; ++S) {
				int total = 0;
				for (int temp = S, j = 1; j <= n; ++j, temp = temp / D) {
					tmp[j] = temp % D;
					total += tmp[j];
				}
				dp[i][S][0] = dp[i][S][1] = 0.0;
				if (total != m - i + 1) continue;	
				for (int k = 1; k <= n; ++k) {
					if (!tmp[k]) continue;
					if (f[i]) {
						dp[i][S][0] = max(dp[i][S][0], dp[i + 1][S - pw[k]][0]);
						dp[i][S][1] = max(dp[i][S][1], (1 - p[k][i]) * dp[i + 1][S - pw[k]][0] + p[k][i] * (dp[i + 1][S - pw[k]][1] + 1));
					} else {
						dp[i][S][0] = dp[i][S][1] = max(dp[i][S][1], (1 - p[k][i]) * dp[i + 1][S - pw[k]][0] + p[k][i] * (dp[i + 1][S - pw[k]][1] + 1));
					}
				}
			}
		}
		
		double ans = 0.0;
		for (int i = 1; i <= m + 1; ++i)
			for (int S = 0; S <= maxS; ++S) {
				int total = 0, mn = 1e9, mx = 0;
				for (int temp = S, j = 1; j <= n; ++j, temp = temp / D) {
					tmp[j] = temp % D;
					total += tmp[j];
					mn = min(mn, tmp[j]);
					mx = max(mx, tmp[j]);
				}
				if (mx - mn <= 1 && total == m && i == 1) ans = max(ans, max(dp[i][S][1], dp[i][S][0]));
				dp[i][S][0] = dp[i][S][1] = 0.0;
			}*/
		double ans = 0.0;
		//for (int i = 1; i <= n; ++i) ans = max(ans, dfs(1, pw[i], 1));
		ans = dfs(1, 0, 1);
		printf("Case %d: %.4f\n", tag, ans + 1e-6);
	}
}
