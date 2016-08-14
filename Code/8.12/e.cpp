#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 2111111;
const int MOD = 1e9 + 7;
int f[2][MAXN], dp[MAXN], len, ch[MAXN];
pair<int, int> c[MAXN];
char str[MAXN];

void addinterval(int l, int r, int k, int b) {
//cout << l << " " << r << " " << k << " " << b << endl;
	LL tmp1 = k, tmp2 = (-(LL)k * l + k + b) % MOD;
	c[l] = make_pair((tmp1 + c[l].first) % MOD, (tmp2 + c[l].second) % MOD);
	c[r + 1] = make_pair((c[r + 1].first - tmp1) % MOD, (c[r + 1].second - tmp2) % MOD);
}

void getf() {
	ch[0] = -10; ch[len * 2 + 1] = -1; ch[len * 2 + 2] = -5;
	for (int i = 1; i <= len; ++i) ch[i * 2] = str[i] - 'a';
	for (int i = 1; i <= len; ++i) ch[i * 2 - 1] = -1;
	dp[0] = 1; 
	int p = 0, mx = 0;
	for (int i = 1; i <= len * 2; ++i) {
		int j = p * 2 - i;
		if (i <= mx) dp[i] = min(dp[j], mx - i + 1);
		else dp[i] = 1;
		while (ch[i - dp[i]] == ch[i + dp[i]]) dp[i]++;
		if (i + dp[i] - 1 > mx) mx = i + dp[i] - 1, p = i;
	}
	for (int i = 1; i <= len; ++i) c[i] = make_pair(0, 0);
	for (int i = 2; i <= len * 2; ++i) {
		int L, R;
		if (i % 2 == 1 && dp[i] == 1) continue;
		if (i % 2 == 0) {
			L = i / 2 - dp[i] / 2 + 1;
			R = i / 2 + dp[i] / 2 - 1;
			addinterval(L + (R - L) / 2, R, -1, L + (R - L) / 2 + 1);
		} else {
			L = i / 2 - dp[i] / 2 + 1;
			R = i / 2 + dp[i] / 2;
			addinterval((L + R + 1) >> 1, R, -1, (L + R + 1) / 2);
		}
		//cout << "getinterval: " << i << " " << dp[i] << " " << L << " " << R << endl;
	}
	pair<int, int> temp = make_pair(0, 0);
	for (int i = 1; i <= len; ++i) {
		//cout << c[i].first << " " << c[i].second << endl;
		temp = make_pair((temp.first + c[i].first) % MOD, (temp.second + c[i].second) % MOD);
		f[0][i] = ((LL)temp.first * i + temp.second) % MOD;
	}
	for (int i = 1; i <= len; ++i) c[i] = make_pair(0, 0);
	for (int i = 2; i <= len * 2; ++i) {
		int L, R;
		if (i % 2 == 1 && dp[i] == 1) continue;
		if (i % 2 == 0) {
			L = i / 2 - dp[i] / 2 + 1;
			R = i / 2 + dp[i] / 2 - 1;
			addinterval(L, L + (R - L) / 2, -1, R + 1);
			//addinterval(L + (R - L) / 2, R, -1, L + (R - L) / 2 + 1);
		} else {
			L = i / 2 - dp[i] / 2 + 1;
			R = i / 2 + dp[i] / 2;
			addinterval(L, (L + R + 1) / 2 - 1, -1, R + 1);
			//addinterval((L + R + 1) >> 1, R, -1, (L + R + 1) / 2 + 1);
		}
		//cout << "getinterval: " << i << " " << dp[i] << " " << L << " " << R << endl;
	}
	temp = make_pair(0, 0);
	for (int i = 1; i <= len; ++i) {
		temp = make_pair((temp.first + c[i].first) % MOD, (temp.second + c[i].second) % MOD);
		f[1][i] = ((LL)temp.first * i + temp.second) % MOD;
	}
	
}

int main() {
	while (scanf("%s", str + 1) != EOF) {
		len = strlen(str + 1);
		getf();
		int ans = 0;
//for (int i = 1; i <= len; ++i) cout << f[0][i] << " " << f[1][i] << endl;
		for (int i = 1; i < len; ++i) ans = ((LL)f[0][i] * f[1][i + 1] + ans) % MOD;
		if (ans < 0) ans += MOD;
		printf("%d\n", ans);
	}
}
