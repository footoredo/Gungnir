#include <bits/stdc++.h>
typedef double DB;

const DB eps = 1e-9;
__inline int sign(DB x) {
	if (x > eps) return 1;
	else if (x < -eps) return -1;
	else return 0;
}

const int N = 111;
int n, s, t, inf = 1e9;
DB eq[N][N];
bool q[N];
int adj[N][N], d[N][N];
bool valid[N];

bool solve(int s, DB& ans) {
	for (int i = 1; i <= n; ++ i) if (d[i][t]!=inf) {
		int k = i;
		for (int j = i; j <= n; ++ j) if (d[j][t]!=inf)
			if (abs(eq[j][i]) > abs(eq[k][i])) {
				k = j; 
			}
		for (int j = i; j <= n + 1; ++ j)
			std::swap(eq[i][j], eq[k][j]);
		if (!sign(eq[i][i])) continue;
		for (int j = i + 1; j <= n; ++ j) if (d[j][t]!=inf) {
			DB kk = eq[j][i] / eq[i][i];
			for (int k = i; k <= n + 1; ++ k)
				eq[j][k] = eq[j][k] - eq[i][k] * kk;
		}
	}
	for (int i = n; i >= 1; -- i) if (d[i][t]!=inf) {
		for (int j = i + 1; j <= n; ++ j) 
			if (sign(eq[i][j])) {
				eq[i][n + 1] -= eq[i][j] * eq[j][n + 1];
			}
		eq[i][n + 1] /= eq[i][i];
	}
	ans = eq[s][n + 1];
	return true;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(15);

	for (; std::cin >> n >> s >> t, n || s || t; ) {
		for (int i = 1; i <= n; ++ i) std::cin >> q[i];
		memset(eq, 0, sizeof eq);
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				std::cin >> adj[i][j];
				d[i][j] = adj[i][j];
				if (!adj[i][j]) d[i][j] = inf;
				if (i == j) d[i][i] = 0;
			}
		}
		for (int k = 1; k <= n; ++ k)
			for (int i = 1; i <= n; ++ i)
				for (int j = 1; j <= n; ++ j)
					d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
//		for (int i = 1; i <= n; ++ i)
//			std::cout << i << " " << d[i][t] << std::endl;
		if (d[s][t] == inf) {
			std::cout << "impossible" << std::endl;
			continue;
		}
		for (int i = 1; i <= n; ++ i) if (d[i][t] != inf) {
			if (i == t) {
				eq[i][i] = 1; eq[i][n + 1] = 0;
				continue;
			}
			eq[i][i] = 1;
			if (q[i]) {
				int all = 0;
				for (int j = 1; j <= n; ++ j)
					if (adj[i][j] && adj[i][j] == d[i][t] - d[j][t])
						++ all;
				if (!all) {
					eq[i][i] = 0; eq[i][n + 1] = 1;
					continue;
				}
				for (int j = 1; j <= n; ++ j)
					if (adj[i][j] && adj[i][j] == d[i][t] - d[j][t]) {
//						std::cout << i << " " << j << std::endl;
						eq[i][j] -= 1. / all;
						eq[i][n + 1] += adj[i][j] * 1. / all;
					}
			}
			else {
				int all = 0;
				for (int j = 1; j <= n; ++ j)
					if (adj[i][j])
						++ all;
				if (!all) {
					eq[i][i] = 0; eq[i][n + 1] = 1;
					continue;
				}
				for (int j = 1; j <= n; ++ j)
					if (adj[i][j]) {
						eq[i][j] -= 1. / all;
						eq[i][n + 1] += adj[i][j] * 1. / all;
					}
			}
		}
		DB ans;
		solve(s, ans); 
		std::cout << ans << std::endl;
	}

	return 0;
}
