#include <bits/stdc++.h>
using namespace std;

const int MAXH = 2222;
const int MAXN = 500;
const int inf = 1e9;
int c[MAXH][MAXH], board[MAXN][MAXN], mp[MAXN][MAXN], link[MAXN], vis[MAXN], n, m, H, W, T, x, y;
char ch[MAXH];

int calc(int tx, int ty, int x, int y) {
	return c[tx][ty] - c[tx][ty - y] - c[tx - x][ty] + c[tx - x][ty - y];
}

bool find(int u) {
	for (int i = 1; i <= mp[u][0]; ++i) {
		int v = mp[u][i];
		if (!vis[v]) {
			vis[v] = 1;
			if (!link[v] || find(link[v])) {
				link[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main() {
	while (scanf("%d%d%d%d%d", &H, &W, &n, &m, &T) != EOF) {
		for (int i = 1; i <= H; ++i) {
			scanf("%s", ch + 1);
			for (int j = 1; j <= W; ++j) c[i][j] = (ch[j] - '0') ^ 1;
		}
		for (int i = 1; i <= H; ++i)
			for (int j = 1; j <= W; ++j)
				c[i][j] = c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1] + c[i][j];
		
		int ans = inf;
		for (x = 1; x <= H; ++x) {
			y = (H - n * x) / (n + 1);
			if (x < y || y <= 0 || n * x + (n + 1) * y != H || m * x + (m + 1) * y != W) continue;
			int nowans = 0;
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m; ++j) {
					int tx = i * (x + y), ty = j * (x + y);
					if (calc(tx, ty, x, x)) nowans++;
					board[i * 2][j * 2] = 1;
				}
			for (int i = 1; i <= n + 1; ++i)
				for (int j = 1; j <= m; ++j) {
					int tx = (i - 1) * x + i * y, ty = j * (x + y);
					board[i * 2 - 1][j * 2] = (calc(tx, ty, y, x) == x * y);
				}
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m + 1; ++j) {
					int tx = i * x + i * y, ty = (j - 1) * x + j * y;
					board[i * 2][j * 2 - 1] = (calc(tx, ty, x, y) == x * y);
				}
			for (int i = 1; i <= n + 1; ++i)
				for (int j = 1; j <= m + 1; ++j) {
					int tx = (i - 1) * x + i * y, ty = (j - 1) * x + j * y;
					board[i * 2 - 1][j * 2 - 1] = (calc(tx, ty, y, y) == y * y);
				}
/*for (int i = 1; i <= n * 2 + 1; ++i) {
	for (int j = 1; j <= m * 2 + 1; ++j)
		cout << board[i][j] << " ";
	cout << endl;
}
cout << nowans << endl;*/
			for (int i = 1; i <= n + 1; ++i)
				for (int j = 1; j <= m; ++j) {
					if (board[i * 2 - 1][j * 2]) continue;
					nowans++;
					for (int k = 1; k <= m * 2 + 1; ++k) board[i * 2 - 1][k] = 1;
				}
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m + 1; ++j) {
					if (board[i * 2][j * 2 - 1]) continue;
					nowans++;
					for (int k = 1; k <= n * 2 + 1; ++k) board[k][j * 2 - 1] = 1;
				}
				
			/*int sum_row = 0, sum_col = 0;
			for (int i = 1; i <= n * 2 + 1; ++i) {
				bool flag = true;
				for (int j = 1; j <= m * 2 + 1; ++j)
					if (!board[i][j]) {
						flag = false;
						break;
					}
				if (!flag) sum_row++;
			}
			for (int j = 1; j <= m * 2 + 1; ++j) {
				bool flag = true;
				for (int i = 1; i <= n * 2 + 1; ++i)
					if (!board[i][j]) {
						flag = false;
						break;
					}
				if (!flag) sum_col++;
			}
			ans = min(ans, nowans + min(sum_col, sum_row));*/
			int N = n * 2 + 1, M = m * 2 + 1;
			memset(link, 0, sizeof(link));
			memset(mp, 0, sizeof(mp));
			for (int i = 1; i <= N; ++i)
				for (int j = 1; j <= M; ++j)
					if (!board[i][j]) mp[i][++mp[i][0]] = j;
			for (int i = 1; i <= N; ++i) {
				memset(vis, 0, sizeof(vis));
				if (find(i)) nowans++;
			}
			ans = min(ans, nowans);
		}
		if (ans != inf) printf("%d\n", ans * T);
		else puts("-1");
	}
}
