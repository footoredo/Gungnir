#include <bits/stdc++.h>

const int N = 1111;
const int MODN = 1e9 + 7 + 1e-9;
int f[N][N][3][3];
int a[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T; std::cin >> T;

	for (; T --; ) {
		int n, s; std::cin >> n >> s;
		for (int i = 1; i <= n; ++ i) std::cin >> a[i];
		memset(f, 0, sizeof f); f[0][0][0][0] = 1;
		int ans = 0;
		for (int i = 1; i <= n; ++ i)
			for (int j = 0; j <= s; ++ j) {
				for (int k = 0; k < 3; ++ k)
					for (int l = 0; l < 3; ++ l) {
						f[i][j][k][l] = (f[i][j][k][l] + f[i - 1][j][k][l]) % MODN;
						if (l) 
							f[i][j][k][l] = (f[i][j][k][l] + f[i - 1][j][k][l - 1]) % MODN;
						if (j >= a[i]) 
							f[i][j][k][l] = (f[i][j][k][l] + f[i - 1][j - a[i]][k][l]) % MODN;
						if (j >= a[i] && k) 
							f[i][j][k][l] = (f[i][j][k][l] + f[i - 1][j - a[i]][k - 1][l]) % MODN;
					}
				if (i == n && j) ans = (ans + f[i][j][2][2]) % MODN;
			}
		std::cout << ans * 4LL % MODN << std::endl;
	}

	return 0;
}
