#include <bits/stdc++.h>
#define index INDEX

const int N = 20;
int n;
int owe[N][N], _owe[N][N];
std::vector<int> oss;
bool os[N];
int index[(1 << N) + 5], cnt[(1 << N) + 5];

__inline bool neg(int x, int mask) {
	int tot = 0;
	for (int m = mask; m; m ^= m & -m)
		tot += owe[index[m & -m]][x];
	return tot < 0;
}

void clear(int x) {
	for (int i = 0; i < n; ++ i)
		owe[x][i] = owe[i][x] = 0;
}

bool solved[(1<<N) + 5];
int f[(1<<N) + 5];

inline int solve(int mask) {
	if (solved[mask]) return f[mask];
	solved[mask] = true;
	f[mask] = 0;
	if (cnt[mask] == 1)
		f[mask] = mask;
	else {
		for (int m = mask; m; m ^= (m & -m))
			if (neg(index[m & -m], mask))
				f[mask] |= solve(mask ^ (m & -m));
	}
	return f[mask];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T;
	std::cin >> T;

	for (int i = 0; i < 20; ++ i) index[1 << i] = i;
	for (int i = 1; i < 1 << 20; ++ i)
		cnt[i] = cnt[i ^ (i & -i)] + 1;
	//std::cout << cnt[(1 << 20) - 1] << std::endl;
	for (; T --; ) {
		std::cin >> n;
		oss.clear();
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
				std::cin >> owe[i][j];

		if (n == 1) {
			std::cout << 1 << std::endl;
			continue;
		}

		memset(solved, 0, sizeof(*solved) << n);
		int s = solve((1 << n) - 1);
		
		for (int i = 0; i < n; ++ i)
			if (s >> i & 1)
				oss.push_back(i + 1);

		if (!oss.size()) std::cout << 0 << std::endl;
		else {
			std::sort(oss.begin(), oss.end());
			for (int i = 0; i < (int)oss.size(); ++ i) {
				std::cout << oss[i];
				if (i == (int)oss.size() - 1) std::cout << std::endl;
				else std::cout << ' ';
			}
		}
	}

	return 0;
}
