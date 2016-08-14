#include <bits/stdc++.h>

const int N = 22;
int a[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (int curT = 1; curT <= T; ++ curT) {
		int n; std::cin >> n;
		int tot = 0;
		for (int i = 0; i < n; ++ i) {
			std::cin >> a[i];
			tot += a[i];
		}

		bool half = false;
		int tmp = 0;
		for (int i = 0; i < n; ++ i) {
			if (a[i] * 2 > tot) {
				half = true;
				tmp = (tot - a[i]) * 2 + 1;
			}
		}
		if (!half) tmp = tot;

		std::cout << "Case #" << curT << ": " << std::min(tmp, tot / 2) << std::endl;
	}

	return 0;
}
