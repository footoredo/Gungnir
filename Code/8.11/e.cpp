#include <bits/stdc++.h>

const int N = 111, M = 55;
int score[M][M];
int a[N], f[N][M];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T --; ) {
		int n, m; std::cin >> n >> m;
		for (int i = 1; i <= m; ++ i)
			for (int j = 1; j <= m; ++ j)
				std::cin >> score[i][j];
		for (int i = 1; i <= n; ++ i)
			std::cin >> a[i];

		memset(f[0], -1, sizeof(*f[0])*(m + 2));
		f[0][0] = 0;
		for (int i = 1; i <= n; ++ i) {
			memset(f[i], -1, sizeof(*f[i])*(m + 2));
			for (int j = 0; j <= m; ++ j) if (~f[i - 1][j]) {
				if (a[i] > 0) f[i][a[i]] = std::max(f[i][a[i]], f[i - 1][j] + score[j][a[i]]);
				else for (int k = 1; k <= m; ++ k) {
					f[i][k] = std::max(f[i][k], f[i - 1][j] + score[j][k]);
				}
			}
		}

		int ans = 0;
		for (int j = 1; j <= m; ++ j)
			if (f[n][j] > ans) ans = f[n][j];
		std::cout << ans << std::endl;
	}

	return 0;
}
