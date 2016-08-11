#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <algorithm>

const int N = 222;
int n;
int T[N], D[N];
int seq[N], cc;

bool solved[N][N];
int f[N][N], term[N][N], dis[N][N];
__inline int solve(int l, int r) {
	if (solved[l][r]) return f[l][r];
	solved[l][r] = true;
	if (l == r) return f[l][r] = 0;
	int d = r > l ? 1 : -1;
	int cur = 1e9, pos = D[l], curt = 0;
	f[l][r] = -1;
	for (int i = l; i != r; i += d) {
		if (cur <= dis[i][pos]) break;
		curt += dis[i][pos];
		cur -= dis[i][pos]; pos = i;
		cur = std::min(cur, T[i]);
		int tmp = solve(r, i + d);
		if (!~tmp) continue;
		if (cur > tmp + dis[r][pos]) {
			if (!~f[l][r] || f[l][r] > tmp + dis[r][pos] + curt) {
				f[l][r] = tmp + dis[r][pos] + curt;
				term[l][r] = i;
			}
		}
	}
	return f[l][r];
}

__inline void get_ans(int l, int r) {
	assert(~f[l][r]);
	if (l == r) seq[cc ++] = l;
	else {
//		std::cout << l << " " << r << " " << term[l][r] << std::endl;
		int d = r > l ? 1 : -1;
		for (int i = l; i != term[l][r] + d; i += d) {
			seq[cc ++] = i;
		}
		get_ans(r, term[l][r] + d);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	for (; std::cin >> n; ) {
		for (int i = 0; i < n; ++ i) std::cin >> T[i];
		for (int i = 0; i < n; ++ i) std::cin >> D[i];

		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j) {
				dis[i][j] = std::abs(D[i] - D[j]);
				solved[i][j] = false;
			}
		cc = 0; 
		if (~solve(0, n - 1)) {
			get_ans(0, n - 1);
			for (int i = 0; i < n; ++ i) {
				std::cout << seq[i] + 1;
				if (i == n - 1) std::cout << std::endl;
				else std::cout << " ";
			}
		}
		else if (~solve(n - 1, 0)) {
			get_ans(n - 1, 0);
			for (int i = 0; i < n; ++ i){
				std::cout << seq[i] + 1;
				if (i == n - 1) std::cout << std::endl;
				else std::cout << " ";
			}
		}
		else std::cout << "Mission Impossible" << std::endl;
	}

	return 0;
}
