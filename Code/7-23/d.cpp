#include <bits/stdc++.h>
using namespace std;

const int maxn = 15;
const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[] = {1, 0, -1, -1, -1, 0, 1, 1};
int step, n, ansx, ansy, x, y, c, tot, S, boo[maxn][maxn], mp[maxn][maxn], s[3], mx[10], X[maxn * maxn], Y[maxn * maxn];

bool check(int x, int y, int c) {
	for (int dir = 0; dir < 8; ++dir) {
		mx[dir] = 1;
		int tx = x, ty = y;
		for (int i = 1; i <= 4; ++i) {
			tx += dx[dir], ty += dy[dir];
			if (tx >= 0 && ty >= 0 && tx < maxn && ty < maxn && boo[tx][ty] == c) mx[dir]++;
			else break;
		}
	}
	for (int i = 0; i < 4; ++i)
		if (mx[i] + mx[i + 4] - 1 >= 5) return true;
	return false;
}

int solve(int dep, int c) {
	if (dep > 3) return 2;
	int ret = -1;
	for (int i = 1; i <= tot; ++i) {
		int x = X[i], y = Y[i];
		if (boo[x][y] || mp[x][y] == -1) continue;
		boo[x][y] = c;
		if (check(x, y, c)) {
			boo[x][y] = 0;
			if (dep == 1) {
				ansx = x, ansy = y;
				step = 1;
				return 1;
			} else return 1;
		}
		/*if (dep == 3 && x == 2 && y == 5) {
			cout << "ASdsafdfsadfas " << check(x, y, c) << endl;
			return 0;
		}*/
		int tmp = solve(dep + 1, 3 - c);
		//if (dep == 1) cout << "adfs" << tmp << endl;
		if (tmp == 0) {
			boo[x][y] = 0;
			if (dep == 1) {
				ansx = x; ansy = y;
			}
			return 1;
		}
		if (tmp == 2) ret = 2;
		boo[x][y] = 0;
	}
	if (ret == 2) return 2; else return 0;
}

bool checkin(int x, int y) {
	return x >= 0 && y >= 0 && x < maxn && y < maxn;
}

int main() {
	while (1) {
		scanf("%d", &n);
		if (n == 0) return 0;
		memset(boo, 0, sizeof(boo));
		s[0] = s[1] = s[2] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", &x, &y, &c);
			s[++c]++;
			boo[x][y] = c;
		}
		for (int i = 0; i < maxn; ++i)
			for (int j = 0; j < maxn; ++j) {
				if (boo[i][j]) {
					mp[i][j] = -1;
					continue;
				}
				bool flag = false;
				for (int dir = 0; dir < 8; ++dir) {
					int tx = i + dx[dir], ty = j + dy[dir];
					int tx1 = tx + dx[dir], ty1 = ty + dy[dir];
					if (checkin(tx, ty) && checkin(tx1, ty1) && boo[tx][ty] + boo[tx1][ty1] > 0) {
						flag = true;
						break;
					}
				}
				if (flag) mp[i][j] = 1; else mp[i][j] = -1;
			}
/*for (int i = 0; i < maxn; ++i) {
	for (int j = 0; j < maxn; ++j) cout << boo[i][j];
	cout << endl;
}*/
		if (s[1] == s[2]) S = 2; else {
			if (s[1] == s[2] - 1) S = 1;
			else {
				printf("Invalid.\n");
				continue;
			}
		}
		tot = 0;
		for (int i = 0; i < maxn; ++i)
			for (int j = 0; j < maxn; ++j)
				if (!boo[i][j]) {
					++tot; X[tot] = i; Y[tot] = j;
				}
		
		step = 3;
		bool flag = false;
		for (int i = 1; i <= tot; ++i) {
			boo[X[i]][Y[i]] = S;
			if (check(X[i], Y[i], S)) {
				ansx = X[i]; ansy = Y[i];
				step = 1;
				break;
			}
			boo[X[i]][Y[i]] = 0;
		}
		if (step == 1) {
			if (S == 1) printf("Place white at (%d,%d) to win in %d move.\n", ansx, ansy, step);
			else printf("Place black at (%d,%d) to win in %d move.\n", ansx, ansy, step);
			continue;
		}
		int ans = solve(1, S);
		
		if (ans == 1) {
			if (S == 1) printf("Place white at (%d,%d) to win in %d move", ansx, ansy, step);
			else printf("Place black at (%d,%d) to win in %d move", ansx, ansy, step);
			if (step == 3) cout << "s";
			cout << "." << endl;
		} else {
			if (ans == 2) printf("Cannot win in 3 moves.\n");
			else printf("Lose in 2 moves.\n");
		}
	}
}