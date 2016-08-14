#include <bits/stdc++.h>
typedef double DB;

const int N = 1111;
DB x[N], y[N], t[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(15);

	int T; std::cin >> T;
	for (; T--; ) {
		int n; std::cin >> n;
		DB ans = 0;
		for (int i = 0; i < n; ++ i) {
			std::cin >> t[i] >> x[i] >> y[i];
			if (i) {
				DB tmp = sqrt(1. * (x[i] - x[i-1]) * (x[i] - x[i-1]) + 1. * (y[i] - y[i - 1]) * (y[i] - y[i - 1])) / (t[i] - t[i - 1]);
				ans = std::max(ans, tmp);
			}
		}
		std::cout << ans << std::endl;
	}

	return 0;
}
