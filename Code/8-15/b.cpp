#include <bits/stdc++.h>
const int MODN = 110119;
int p[MODN], invp[MODN];
__inline int pw(int x, int p) {
	int ret = 1;
	for (; p; p >>= 1, x = 1LL * x * x % MODN)
		if (p & 1) ret = 1LL * ret * x % MODN;
	return ret;
}

int C(long long n, long long m) {
	if (n < m) return 0;
	if (n < MODN && m < MODN) {
		return 1LL * p[n] * invp[m] * invp[n - m] % MODN;
	}
	else return 1LL * C(n / MODN, m / MODN) * C(n % MODN, m % MODN) % MODN;
}

int f(long long n, long long m) {
	if (n < 0 || m < 0) return 0;
	long long all = n + m;
	if (all % 3 != 0) return 0;
	long long step = all / 3;
	n -= step; m -= step;
	if (n < 0 || m < 0) return 0;
	return C(n + m, n);
}

const int N = 111;
int g[N], r;
long long n, m;
std::pair<long long, long long> ob[N];

int main() {
	p[0] = 1; for (int i = 1; i < MODN; ++ i) p[i] = 1LL * i * p[i - 1] % MODN;
	invp[MODN - 1] = pw(p[MODN - 1], MODN - 2);
	for (int i = MODN - 2; i >= 0; -- i) invp[i] = 1LL * (i + 1) * invp[i + 1] % MODN;
//	std::cout << C(2, 1) << std::endl;

	for (int curT = 1; std::cin >> n >> m >> r; ++ curT) {
		for (int i = 0; i < r; ++ i)
			std::cin >> ob[i].first >> ob[i].second;
		ob[r ++] = std::make_pair(1, 1);
		std::sort(ob, ob + r); std::reverse(ob, ob + r);
		for (int i = 0; i < r; ++ i) {
			g[i] = f(n - ob[i].first, m - ob[i].second);
//			std::cout << g[i] << std::endl;
			for (int j = 0; j < i; ++ j)
				g[i] = (g[i] - 1LL * g[j] * f(ob[j].first - ob[i].first, ob[j].second - ob[i].second)) % MODN;
		}
		std::cout << "Case #" << curT << ": ";
		std::cout << (g[r - 1] % MODN + MODN)%MODN << std::endl;
	}

	return 0;
}
