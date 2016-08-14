#include <bits/stdc++.h>

const int N = 111;
int f[N][N], T, n;
int t[N], M[N];

__inline void update(int &f0, int f) {
	if (!~f0 || f0 > f) f0 = f;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (; std::cin >> T, T; ) {
		for (int i = 0; i < T; ++ i) std::cin >> t[i];
		for (int i = 1; i <= 100; ++ i) M[i] = 23;
		std::cin >> n;
		for (int i = 0; i < n; ++ i) {
			int dd, mm; std::cin >> dd >> mm;
			M[dd] = std::min(M[dd], mm);
		}
		memset(f, -1, sizeof f); f[1][1] = 0;
		int ans = -1;
		for (int i = 2; i <= 100; ++ i) {
			for (int j = 1; j < i; ++ j)
				if (~f[i - 1][j]) {
					if (t[(i - j) % T] <= M[i])
						update(f[i][j], f[i - 1][j]);
					update(f[i][i], f[i - 1][j] + 1);
				}
		}
		for (int j = 1; j <= 100; ++ j) if (~f[100][j]) update(ans, f[100][j]);
		std::cout << ans << std::endl;
	}

	return 0;
}
