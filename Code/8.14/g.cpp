#include <bits/stdc++.h>
#define count COUNT123	
using namespace std;

typedef long long LL;

const int MOD = 772002;
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int MAXN = 6;
const int MAXS = (1 << 10) + 10;
int mp[MAXN][MAXN], raw_mp[MAXN][MAXN], X[100], Y[100], vis[MAXN][MAXN], dp[MAXS][30], c[111][111], sum[MAXS], count[MAXS];
int n, m, ans, rawcnt;	
char str[1111];

inline bool check(int x, int y) {
	for (int dir = 0; dir < 8; ++dir) {
		int tx = dx[dir] + x, ty = dy[dir] + y;
		if (tx && ty && tx <= n && ty <= m && mp[tx][ty] == 1) return false;
	}
	return true;
}

#define work FUCK
//////////////////////////////////////////
inline void work() {
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (mp[i][j]) {
				X[cnt] = i; Y[cnt] = j; ++cnt;
			}
	for (int S = 0; S < 1 << cnt; ++S) {
		count[S] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				vis[i][j] = 0;
		for (int i = 0; i < cnt; ++i) {
			if (S & (1 << i)) continue;
			vis[X[i]][Y[i]] = 1;
			for (int dir = 0; dir < 8; ++dir) {
				int tx = X[i] + dx[dir], ty = Y[i] + dy[dir];
				if (tx && ty && tx <= n && ty <= m) vis[tx][ty] = 1;
			}
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (!vis[i][j]) count[S]++;
	}
	for (int S = 0; S < 1 << cnt; ++S)
		for (int k = 1; k <= n * m; ++k)
			dp[S][k] = 0;
	dp[0][0] = 1;
	for (int mask = 0; mask < 1 << cnt; ++mask) {
		for (int k = sum[mask]; k <= n * m; ++k) {
			for (int i = 0; i < cnt; ++i)
				if (mask & (1 << i)) dp[mask][k] = (dp[mask][k] + dp[mask ^ (1 << i)][k - 1]) % MOD;
			dp[mask][k] = ((LL)(count[mask] - k + 1) * dp[mask][k - 1] + dp[mask][k]) % MOD;
			//cout << mask << " " << k << " " << dp[mask][k] << endl;
		}
	}
	int nowans = 0;
	nowans = dp[(1 << cnt) - 1][n * m];
	//cout << mp[1][1] << " " << mp[1][2] << " " << mp[1][3] << endl;
	//cout << nowans << " " << cnt << endl;
	std::cout << "FUCK" << std::endl;
	if ((cnt - rawcnt) % 2 == 0) ans = (ans + nowans) % MOD;
	else ans = (ans - nowans) % MOD;
}

void dfs(int x, int y) {
	if (y > m) x++, y = 1;
	if (x > n) {
		work();
		return;
	}
	for (int i = 0; i < 2; ++i) {
		if (raw_mp[x][y] == 1 && i == 0) continue;
		mp[x][y] = i;
		if (!i || check(x, y)) dfs(x, y + 1);
		mp[x][y] = -1;
	}
}

int main() {
	int cs = 0;
	for (int i = 0; i <= 50; ++i) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
		}
	}
	while (scanf("%d%d", &n, &m) != EOF) {
		rawcnt = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str + 1);
			for (int j = 1; j <= m; ++j)
				if (str[j] == 'X') {
					raw_mp[i][j] = 1;
					rawcnt++;
				} else raw_mp[i][j] = 0;
		}
		
		ans = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
			 	mp[i][j] = -1;
		dfs(1, 1);
		if (ans < 0) ans += MOD;
		printf("Case #%d: %d\n", ++cs, ans);
	}
}
