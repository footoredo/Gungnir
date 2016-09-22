#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const long long INF = 1e18;
const int MAXN = 222;
int s[MAXN], sum_s[MAXN], n;
LL A, B, sum_r[MAXN], r[MAXN], dp[MAXN * 2][MAXN][MAXN];

int main() {
	while (cin >> n >> A >> B) {
		for (int i = 1; i <= n; ++i) cin >> r[i] >> s[i];
		
		sum_r[0] = 0; sum_s[n + 1] = 0;
		for (int i = 1; i <= n; ++i) sum_r[i] = sum_r[i - 1] + r[i];
		for (int i = n; i >= 0; --i) sum_s[i] = sum_s[i + 1] + s[i];
		
		for (int i = 0; i <= n * 2 + 3; ++i)
			for (int j = 0; j <= n; ++j)
				for (int k = 0; k <= sum_s[1]; ++k)
					dp[i][j][k] = INF;
		for (int i = n; i <= n * 2; ++i)
				dp[i][n][0] = 0;
		for (int i = n * 2; i >= 0; --i)
			for (int j = 0; j <= i && j < n; ++j)
				for (int k = sum_s[1]; k >= 0; --k) {
					if (k > sum_s[j + 1]) {
						dp[i][j][k] = INF;
					} else{
						LL T = A + B - (i - j) + sum_r[j];
						int kk = sum_s[j + 1] - k;
						if (k < sum_s[1]) dp[i][j][k] = min(dp[i][j][k], dp[i][j][k + 1]);
						if (kk < sum_s[1]) dp[i][j][k] = min(dp[i][j][k], T - dp[i + 1][j + 1][kk + 1] + 1);
						if (dp[i][j][k] > T / 2) {
							LL tmp = max(1 + dp[i + 2][j + 1][k], T / 2 + 1);
							dp[i][j][k] = min(dp[i][j][k], tmp);
						}
						if (dp[i][j][k] < 0) dp[i][j][k] = 0;
					}
				}
		
		int ans = 0;
		for (int k = 0; k <= sum_s[1]; ++k)
			if (dp[0][0][k] <= A) ans = max(ans, k);
		cout << ans << " " << sum_s[1] - ans << endl;
	}
}
