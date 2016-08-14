#include <bits/stdc++.h>

char buf[11111111];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (int T = 1; std::cin >> buf; ++ T) {
		int m1 = 0, m2 = 0;
		int len = strlen(buf);
		for (int i = 0; i < len; ++ i) {
			m1 = (m1 * 10 + buf[i] - '0') % 73;
			m2 = (m2 * 10 + buf[i] - '0') % 137;
		}
		std::cout << "Case #" << T << ": ";
		if (m1 == 0 && m2 == 0) std::cout << "YES" << std::endl;
		else std::cout << "NO" << std::endl;
	}

	return 0;
}
