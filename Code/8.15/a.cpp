#include <bits/stdc++.h>

const int MODN = 1e9 + 7 + 1e-9;
__inline int pw(int x, int p) {
	int ret = 1;
	for (; p; p >>= 1, x = 1LL * x * x % MODN) 
		if (p & 1) {
			ret = 1LL * ret * x % MODN;
		}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (int curT = 1; curT <= T; ++ curT) {
		int n, m; std::cin >> n >> m;
		int up = pw(m, n + 1) - 1;
		int down = m - 1;
		std::cout << (1LL * up * pw(down, MODN - 2) % MODN + MODN) % MODN << std::endl;
	}

	return 0;
}
