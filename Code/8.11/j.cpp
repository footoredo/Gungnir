#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXS = 22222;
const int MOD = 1e9 + 7;
int n, T, sum[MAXN], pw[MAXN], mp[MAXN][MAXN], temp[MAXN], s[MAXS][MAXN], dp[MAXN][MAXS], ans[MAXN], tmp[MAXS];
char str[MAXN];

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str);
			for (int j = 0; j < n; ++j)
				mp[i][j + 1] = (str[j] == 'o');
		}
		
		sum[0] = 0; pw[0] = 1;
		for (int d = 1; d <= n; ++d) {
		//for (int d = 1; d < 2; ++d) {
			memset(dp, 0, sizeof(dp));
			int D = d, maxS = 1;
			for (int i = 1; i <= n + 1 - d; ++i) maxS = maxS * D, pw[i] = pw[i - 1] * D;
			//cout << pw[0] << " " << pw[1] << " " << pw[2] << " " << pw[3]  << endl;
			dp[0][0] = 1;
			for (int i = 0; i < n; ++i) {
				int tot = 0;
				for (int S = 0; S < 1 << n; ++S) {
					bool flag = true;
					for (int k = 0; k < n; ++k)
						if ((S & (1 << k)) && mp[i + 1][k + 1] == 0) {
							flag = false;
							break;
						}
					if (flag) {
						tmp[++tot] = S;
						s[tot][0] = 0;
						for (int k = 0; k < n; ++k) {
							s[tot][k + 1] = s[tot][k];
							if (S & (1 << k)) s[tot][k + 1]++;
						}
						//cout << S << " " << s[tot][0] << " " << s[tot][1] << " " << s[tot][2] << " " << s[tot][3] << endl;
					}
				}
//cout << i + 1 << " " << tot << endl;
				for (int mask = 0; mask < maxS; ++mask) {
					if (!dp[i][mask]) continue;
					int t = mask;
					for (int k = 1; k <= n - d + 1; ++k) {
						temp[k] = t % D;
						t /= D;
					}
					//cout << mask << " " << temp[0] << " " << temp[1] << " " << temp[2] << " " << temp[3] << endl;
					for (int k = 1; k <= tot; ++k) {
						bool flag = true;
						int S = tmp[k], newmask = 0;
						for (int j = 1; j <= n + 1 - d; ++j) {
							if (s[k][j + d - 1] - s[k][j - 1] != d) continue;
							int newh = temp[j] + 1;
							if (newh >= d) {
								flag = false;
								break;
							}
							newmask += pw[j - 1] * newh;
						}
						//cout << flag << " " << mask << " " << tmp[k] << " " << newmask << endl;
						if (!flag) continue;
						dp[i + 1][newmask] = (dp[i][mask] + dp[i + 1][newmask]) % MOD;
					}
				}
			}
			sum[d] = 0;
			for (int i = 0; i < maxS; ++i) sum[d] = (sum[d] + dp[n][i]) % MOD;
			//cout << d << " " << sum[d] << endl;
		}
		for (int i = 0; i < n; ++i) ans[i] = ((sum[i + 1] - sum[i]) % MOD + MOD) % MOD;
		ans[n] = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (mp[i][j] == 0) ans[n] = 0;
		for (int i = 0; i <= n; ++i) printf("%d\n", ans[i]);
	}
}
