#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 2500000;
const int MOD = 1e9 + 7;
int mu[MAXN + 10], prime[MAXN], flag[MAXN + 10], tot, T, n, inv2, inv6, inv5;

int Fpow(int x, int K, int MOD) {
	int ret = 1;
	while (K) {
		if (K & 1) ret = (LL)ret * x % MOD;
		x = (LL)x * x % MOD;
		K /= 2;
	}
	return ret;
}

int calcmu(int d) {
	if (d <= MAXN) return mu[d];
	int ret = 1;
	for (int i = 1; i <= tot && (LL)prime[i] * prime[i] <= d; ++i) {
		if (d % prime[i]) continue;
		if (d % (prime[i] * prime[i]) == 0) return 0;
		d /= prime[i];
		ret = -ret;
	}
	if (d > 1) ret = -ret;
	return ret;
}

int calc(int d) {
	int m = n / d;
	int t1 = (LL)m * (m + 1) % MOD;
	int tmp1 = (LL)t1 * (m - 1) % MOD * (m - 2) % MOD * (m + 2) % MOD * inv5 % MOD;
	int tmp2 = (LL)t1 * t1 % MOD * inv2 % MOD;
	int sum = ((LL)tmp1 + tmp2 + (LL)t1 * (m * 2 + 1) % MOD * inv6 % MOD - t1) % MOD;
	return (LL)d * d % MOD * d % MOD * d % MOD * calcmu(d) * sum % MOD;
}

int main() {
	tot = 0;
	mu[1] = 1;
	for (int i = 2; i <= MAXN; ++i) {
		if (!flag[i]) {
			prime[++tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= tot && (LL)i * prime[j] <= MAXN; ++j) {
			flag[i * prime[j]] = 1;
			if (i % prime[j]) mu[i * prime[j]] = -mu[i];
			else mu[i * prime[j]] = 0;
		}
	}
	
	inv5 = Fpow(5, MOD - 2, MOD), inv2 = Fpow(2, MOD - 2, MOD), inv6 = Fpow(6, MOD - 2, MOD);
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d", &n);
		int ans = 0;
		for (int i = 1; i * i <= n; ++i) {
			if (n % i) continue;
			ans = (ans + calc(i)) % MOD;
			if (i * i < n) ans = (ans + calc(n / i)) % MOD;
		}
		if (ans < 0) ans += MOD;
		printf("%d\n", ans);
	}
}
