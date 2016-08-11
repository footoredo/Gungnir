#include <bits/stdc++.h>

int rr[15], p[15];

int main() {
	for (int i = 1; i <= 10; ++ i) {
		p[i - 1] = 11 - i;
		rr[i - 1] = 20 * 20 * i * i;
	} p[10] = 0;
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	int T; std::cin >> T;
	for (; T--; ) {
		int n; std::cin >> n;
		int ans = 0;
		for (int i = 0; i < n; ++ i) {
			int x, y; std::cin >> x >> y;
			ans += p[std::lower_bound(rr, rr + 10, x * x + y * y) - rr];
		}
		std::cout << ans << std::endl;
	}

	return 0;
}
