#include <bits/stdc++.h>
const int MODN = 1e9 + 7 + 1e-9;

bool is_prime(int x) {
	if (x == 1) return false;
	for (int i = 2; i * i <= x; ++ i)
		if (x % i == 0) return false;
	return true;
}

const int N = 333;
int p[N], cp, p_index[2222];
int n;
std::bitset<N> eq[N];

int solve() {
	int ret = 0;
	for (int i = 0; i < n; ++ i) {
		for (int j = i - ret; j < cp; ++ j)
			if (eq[j][i]) {
				std::swap(eq[j], eq[i - ret]);
				break;
			}
		if (!eq[i - ret][i]) {
			++ ret;
//			std::cout << "xx " << i << std::endl;
		}
		else {
			for (int j = i - ret + 1; j < cp; ++ j)
				if (eq[j][i])
					eq[j] ^= eq[i - ret];
		}
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (int i = 1; i <= 2000; ++ i)
		if (is_prime(i)) {
			p_index[i] = cp;
			p[cp ++] = i;
		}

	int T; std::cin >> T;
	for (int curT = 1; curT <= T; ++ curT) {
		std::cin >> n;
		for (int i = 0; i < cp; ++ i) eq[i] = 0;
		for (int i = 0; i < n; ++ i) {
			long long x; std::cin >> x;
			int j;
			for (j = 0; j < cp && p[j] * p[j] <= x; ++ j) {
				bool k = 0;
				while (x % p[j] == 0) k = !k, x /= p[j];
//				std::cout << i << " " << p[j] << " " << k << std::endl;
				eq[j][i] = k;
			}
			if (x <= 2000 && is_prime(x)) {
				eq[p_index[x]][i] = 1;
			}
		}

		int m = solve(), ans = 1;
		for (int i = 0; i < m; ++ i)
			ans = ans * 2 % MODN;
		std::cout << "Case #" << curT << ":" << std::endl;
		std::cout << (ans + MODN - 1) % MODN << std::endl;
	}

	return 0;
}
