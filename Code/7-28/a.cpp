#include <bits/stdc++.h>
#define foreach(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++ it)
#define recycle(a) (__typeof(a))(a).swap(a)

const int MODN = 1e9 + 9;
int n, P, len;
std::vector<std::vector<int> > digit;
int f[60][1<<8], g[60][9][20][1<<8];

__inline void add(int &g0, int g) {
	g0 = (g0 + g) % MODN;
}

int solve(int i, int e) {
	if (~f[i][e]) return f[i][e];
	if (i == len) return f[i][e] = 1;
	f[i][e] = 0;
	memset(g[i], 0, sizeof g[i]);
	g[i][0][0][e] = 1;
	for (int j = 0; j < n; ++ j)
		for (int sum = 0; sum < P; ++ sum)
			for (int ee = e; ; ee = (ee - 1) & e) {
				if (g[i][j][sum][ee]) {
					assert((ee >> j & 1) == (e >> j & 1));
					int lim = ee >> j & 1 ? digit[j][i] : P;
					for (int d = 0; d < lim && d + sum < P; ++ d) {
						add(g[i][j + 1][sum + d][ee & (-1 ^ (1 << j))],
								g[i][j][sum][ee]);
					}
					if ((ee >> j & 1) && sum + lim < P) {
						add(g[i][j + 1][sum + lim][ee],
								g[i][j][sum][ee]);
					}
				}
				if (!ee) break;
			}

	for (int sum = 0; sum < P; ++ sum)
		for (int ee = e; ; ee = (ee - 1) & e) {
			if (g[i][n][sum][ee]) {
				add(f[i][e], 1LL * solve(i + 1, ee) * g[i][n][sum][ee] % MODN);
			}
			if (!ee) break;
		}
	return f[i][e];
}

int calc(const std::vector<long long>& lim) {
	len = 0;
	digit.clear(); // recycle(digit);
	foreach(it, lim) {
		if (*it < 0) return 0;
		std::vector<int> tmp(0);
		for (long long cur = *it; cur; cur /= P)
			tmp.push_back(cur % P);
		digit.push_back(tmp);
		len = std::max(len, (int)tmp.size());
	}
	foreach(it, digit) {
		it->resize(len);
		std::reverse(it->begin(), it->end());
	}
	memset(f, -1, sizeof f);
	return solve(0, (1 << n) - 1);
}

long long X[8], Y[8];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T; std::cin >> T;
	for (int curT = 1; curT <= T; ++ curT) {
		std::cin >> n >> P;
		for (int i = 0; i < n; ++ i) std::cin >> X[i];
		for (int i = 0; i < n; ++ i) std::cin >> Y[i];

		int ans = 0;
		for (int mask = 0; mask < 1 << n; ++ mask) {
			std::vector<long long> lim(0);
			for (int i = 0; i < n; ++ i)
				if (mask >> i & 1) lim.push_back(X[i] - 1);
				else lim.push_back(Y[i]);
			add(ans, calc(lim) * (__builtin_popcount(mask) & 1 ? -1 : 1));
		}

		std::cout << "Case " << curT << ": " << (ans + MODN) % MODN << std::endl;
	}
	return 0;
}
