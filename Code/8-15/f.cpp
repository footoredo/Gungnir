#include <bits/stdc++.h>

const int LEN = 20, N = 111111;
long long contrib[LEN][2][LEN][2];
int X, A[N], n;
long long opt_sum;

void search(int pos, int tmp, long long sum) {
//	std::cout << tmp << " " << sum << std::endl;
	if (pos < 0) {
		if (sum < opt_sum) {
			opt_sum = sum; X = tmp;
		}
	}
	else {
		long long sum0 = sum, sum1 = sum;
		for (int i = LEN - 1; i >= pos; -- i)
			sum0 += contrib[i][tmp >> i & 1][pos][0];
		search(pos - 1, tmp, sum0);
		tmp ^= 1 << pos;
		for (int i = LEN - 1; i >= pos; -- i)
			sum1 += contrib[i][tmp >> i & 1][pos][1];
		search(pos - 1, tmp, sum1);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T --; ) {
		memset(contrib, 0, sizeof contrib);
		std::cin >> n;
		for (int i = 0; i < n; ++ i) std::cin >> A[i];
		for (int i = 1; i < n; ++ i) if (A[i] != A[i - 1]) {
			int branch = 31 - __builtin_clz(A[i] ^ A[i - 1]);
			int k = (A[i] >> branch & 1) - (A[i - 1] >> branch & 1);
			for (int j = branch; j >= 0; -- j) {
				int diff = k * ((A[i] & 1 << j) - (A[i - 1] & 1 << j));
//				std::cout << i << " " << branch << " " << j << " " << diff << std::endl;
				contrib[branch][0][j][0] += diff;
				contrib[branch][0][j][1] -= diff;
				contrib[branch][1][j][0] -= diff;
				contrib[branch][1][j][1] += diff;
			}
		}

		opt_sum = 1e15;
		search(LEN - 1, 0, 0);
		std::cout << X << " " << opt_sum << std::endl;
	}

	return 0;
}
