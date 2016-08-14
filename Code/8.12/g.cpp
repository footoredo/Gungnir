#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 11111;
short vis[6][2][20][MAXN];
int tmp[111], table[6][MAXN * 10], K, limit, dfn, len;
LL dp[6][2][20][MAXN], L, R;

LL dfs(int first, int less, int d, int S) {
	if (vis[first][less][d][S] == dfn) return dp[first][less][d][S];
	if (d == 0) return 1;
	vis[first][less][d][S] = dfn;
	int x = (less == 0) ? tmp[d] : 9;
	LL ret = 0;
	for (int i = 0; i <= x; ++i) {
		if (!first && !i) {
			ret += dfs(first, 1, d - 1, S);
			continue;
		}
		int newf = min(first + 1, K), newl, newd = d - 1, newS = S * 10 + i;
		if (less == 0 && i == x) newl = 0; else newl = 1;
		//if (d == 2) cout << "F: " << S << " " << i << " " << newf << " " << newl << " " << newd << " " << newS << " " << dfs(newf, newl, newd, newS % limit) << endl;
		if (table[newf][newS]) ret += dfs(newf, newl, newd, newS % limit);
	}
	return dp[first][less][d][S] = ret;
}

LL calc(LL n, LL K) {
	if (!n) return 1;
	len = 0; limit = 1; dfn++;
	for (int i = 1; i < K; ++i) limit *= 10;
	for (; n; n /= 10) tmp[++len] = n % 10;
	return dfs(0, 0, len, 0);
}

void pre() {
	int used[10], temp[111];
	for (int d = 1; d <= 5; ++d) {
		limit = 1;
		for (int i = 1; i <= d; ++i) limit *= 10;
		for (int i = 0; i < limit; ++i) {
			int tmp = i;
			memset(used, 0, sizeof(used));
			bool flag = true;
			for (int j = 1; j <= d; ++j) {
				temp[j] = tmp % 10;
				if (used[temp[j]]) {
					flag = false;
					break;
				}
				used[temp[j]] = 1;
				tmp /= 10;
			}
			table[d][i] = flag;
		}
	}
}

int main() {
	pre();
	dfn = 0;
	while (cin >> L >> R >> K) {
		cout << calc(R, K) - calc(L - 1, K) << endl;
	}
}
