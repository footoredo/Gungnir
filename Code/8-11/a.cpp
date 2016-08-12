#include <bits/stdc++.h>
typedef double DB;

const int N = 22;
int rem[N];
DB f[1 << 11];
long long C[N * 4][N * 4];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(15);

	for (int i = 0; i <= 48; ++ i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++ j)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}

	int T; std::cin >> T;
	for (; T --; ) {
		int n, m; std::cin >> n >> m;
		for (int i = 1; i <= n; ++ i)
			rem[i] = 4;
		for (int i = 0; i < m; ++ i) {
			int x; std::cin >> x;
			-- rem[x]; 
		}
		memset(f, 0, sizeof(*f) * (1 << n - 1));
		if (!rem[1]) {
			int state = 0;
			for (int i = 2; i <= n; ++ i)
				if (!rem[i]) state |= 1 << i - 2;
			f[state] = 1;
		}
		else {
			for (int state = (1 << n - 1) - 1; state >= 0; -- state) {
				int lbound = 0, rem_all = 0;
				for (int i = 2; i <= n; ++ i)
					if (state >> (i - 2) & 1)
						lbound += rem[i];
					else rem_all += rem[i];
//				std::cout << "S " << state << ": " << std::endl;
//				std::cout << "lbound " << lbound << " rem_all " << rem_all << std::endl;
				for (int i = rem[1] - 1 + lbound; 
						i <= n * 4 - m  - 1; ++ i) {
					DB p0 = DB(rem[1]) / (n * 4 - m - i);
					int d = lbound + rem[1] - 1;
					long long base = C[n * 4 - m][i];
					long long up = C[rem_all][i - d];
					f[state] += p0 * DB(1) * up / base;
				}

				for (int j = state & (state - 1); j != state; 
						j = (j - 1) & state) {
					f[j] -= f[state];
				}
			}
		}

		for (int state = 0; state < 1 << n - 1; ++ state)
			std::cout << f[state] << std::endl;
	}

	return 0;
}
