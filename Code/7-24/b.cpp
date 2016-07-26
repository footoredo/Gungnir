#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int D = 8;
const LL inf = 1e18;
const int maxn = 100000;
const int MOD = 1e9 + 7;
LL backup[maxn][1 << D], ds[1 << D][1 << D], dp[maxn];
int T, n, opt, x, a[maxn], b[maxn];
char ch[5];

vector<int > tr[maxn];

inline int calc(int opt, int a, int b) {
	if (opt == 0) return a & b;
	else return (opt == 1) ? (a ^ b) : (a | b);
}

void dfs(int u) {
	dp[u] = 0;
	for (int s = 0; s < 1 << D; ++s)
		if (ds[s][b[u]] >= 0) dp[u] = max(dp[u], ds[s][b[u]] + (calc(opt, s, a[u]) << D));
	for (int s = 0; s < 1 << D; ++s) {
		backup[u][s] = ds[a[u]][s];
		ds[a[u]][s] = max(ds[a[u]][s], dp[u] + calc(opt, b[u], s));
	}
	for (int i = 0; i < tr[u].size(); ++i) dfs(tr[u][i]);
	for (int s = 0; s < 1 << D; ++s) ds[a[u]][s] = backup[u][s];
}

int main() {
	for (int i = 0; i < 1 << D; ++i)
		for (int j = 0; j < 1 << D; ++j)
			ds[i][j] = -inf;
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d%s", &n, &ch);
		if (ch[0] == 'A') opt = 0; else opt = (ch[0] == 'X') ? 1 : 2;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &x);
			a[i] = x >> D;
			b[i] = x & ((1 << D) - 1);
			tr[i].clear();
		}
		for (int i = 2; i <= n; ++i) {
			scanf("%d", &x);
			tr[x].push_back(i);
		}

		dfs(1);
		LL ans = 0;
		for (int i = 1; i <= n; ++i) ans = (LL(dp[i] % MOD + (a[i] << D) + b[i]) * i + ans) % MOD;
		cout << ans << endl;
	}
}
