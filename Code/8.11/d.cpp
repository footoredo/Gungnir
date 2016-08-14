#include <bits/stdc++.h>
typedef double DB;

const int N = 55555;
int A[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(15);

	int T; std::cin >> T;
	for (; T --; ) {
		int n, k; std::cin >> n >> k;
		for (int i = 0; i < n; ++ i)
			std::cin >> A[i];
		std::sort(A, A + n);

		k = n - k;
		if (k == 0) {
			std::cout << 0. << std::endl;
			continue;
		}
		DB d2s = 0, ds = 0;
		for (int i = 0; i < k; ++ i) {
			d2s += (DB) A[i] * A[i];
			ds += A[i];
		}

		DB ans = d2s - ds * ds / k;
		for (int i = k; i < n; ++ i) {
			d2s -= (DB) A[i - k] * A[i - k];
			ds -= A[i - k];
			d2s += (DB) A[i] * A[i];
			ds += A[i];
			
			DB tmp = d2s - ds * ds / k;
			ans = std::min(ans, tmp);
		}

		std::cout << ans << std::endl;
	}

	return 0;
}
