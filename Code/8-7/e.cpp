#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1111;
const int MOD = 1e9 + 7;
int dp[MAXN][MAXN], sb[MAXN], sf[MAXN];
char ch[MAXN];

int main() {
	while (scanf("%s", ch + 1) != EOF) {
		int l = strlen(ch + 1);
		for (int i = 0; i <= l + 1; ++i)
			for (int j = 0; j <= l + 1; ++j)
				dp[i][j] = 0;	
		dp[0][1] = 1;
		for (int i = 1; i <= l; ++i) {
			sf[0] = 0; sb[l + 1] = 0;
			for (int j = 1; j <= l + 1; ++j) sf[j] = (sf[j - 1] + dp[i - 1][j]) % MOD;
			for (int j = l; j; --j) sb[j] = (sb[j + 1] + dp[i - 1][j]) % MOD;
			for (int j = 1; j <= i + 1; ++j) {
				if (ch[i] == 'I') dp[i][j] = sf[j - 1];
				if (ch[i] == 'D') dp[i][j] = sb[j];
				if (ch[i] == '?') dp[i][j] = (sf[j - 1] + sb[j]) % MOD;
			}
		}
		int ans = 0;
		for (int i = 1; i <= l + 1; ++i) ans = (ans + dp[l][i]) % MOD;
		printf("%d\n", ans);
	}
}
