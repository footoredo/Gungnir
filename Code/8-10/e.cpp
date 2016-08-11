#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int alphabet = 26;
//const int alphabet = 3;
const int MAXS = 11;
const int INF = 1e9;
int dp[alphabet][MAXS][MAXS], mp[MAXN][MAXN], board[MAXN][MAXN], n, m;
bool vis[alphabet][MAXS][MAXS];
char ch[111111];
pair<int, int> fa[MAXN][MAXN], pos[MAXN][MAXN];
vector<pair<int, int> > jewel[alphabet][2];

int dfs(int c, int i, int j) {
	if (vis[c][i][j]) return dp[c][i][j];
	vis[c][i][j] = true;
	pair<int, int> u = jewel[c][0][i], v = jewel[c][1][j];
	if (u.first > v.first || u.second > v.second || fa[u.first][u.second] != fa[v.first][v.second]) return -INF;
	int x1 = u.first, y1 = u.second, x2 = v.first, y2 = v.second;
	for (int x = x1; x <= x2; ++x)
		for (int y = y1; y <= y2; ++y) {
			int cc = pos[x][y].first, id = pos[x][y].second;
			if (cc < 0) continue;
			for (int k = 0; k < jewel[cc][0].size(); ++k) {
				pair<int, int> tmp = jewel[cc][0][k];
				if (tmp.first <= x2 && tmp.first >= x1 && tmp.second <= y2 && tmp.second >= y1) dfs(cc, k, id);
			}
		}
	for (int x = x1; x <= x2; ++x)
		for (int y = y1; y <= y2; ++y)
			board[x][y] = -INF;
	board[x1][y1] = 0;
	for (int x = x1; x <= x2; ++x)
		for (int y = y1; y <= y2; ++y) {
			if (mp[x][y] < 0) {
				board[x][y] = -INF;
				continue;
			}
			if (x > x1 && mp[x - 1][y] > -1) board[x][y] = max(board[x][y], board[x - 1][y]);
			if (y > y1 && mp[x][y - 1] > -1) board[x][y] = max(board[x][y], board[x][y - 1]);
			int cc = pos[x][y].first, id = pos[x][y].second;
			if (cc < 0) continue;
			for (int k = 0; k < jewel[cc][0].size(); ++k) {
				pair<int, int> tmp = jewel[cc][0][k];
				if (cc == c && (k == i || id == j)) continue;
				if (tmp.first <= x2 && tmp.first >= x1 && tmp.second <= y2 && tmp.second >= y1)
					board[x][y] = max(board[x][y], board[tmp.first][tmp.second] + dp[cc][k][id]);
			}
		}
/*if (c == 3 && i == 1 && j == 1) {
cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
for (int x = x1; x <= x2; ++x) {
	for (int y = y1; y <= y2; ++y) cout << board[x][y] << " ";
	cout << endl;
}
}*/
	dp[c][i][j] = board[x2][y2] + 1;
	if (dp[c][i][j] < 0) dp[c][i][j] = -INF;
	//cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	//cout << c << " " << i << " " << j << " " << dp[c][i][j] << endl;
	return dp[c][i][j];
}

inline pair<int, int> getfa(pair<int, int> u) {
	if (fa[u.first][u.second] == u) return u;
	return fa[u.first][u.second] = getfa(fa[u.first][u.second]);
}

int main() {
	while (scanf("%d%d", &n, &m), n) {
		for (int i = 0; i < alphabet; ++i)
			for (int j = 0; j < 2; ++j)
				jewel[i][j].clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", ch + 1);
			for (int j = 1; j <= m; ++j) {
				pos[i][j] = make_pair(-1, -1);
				if (ch[j] == '#') {
					mp[i][j] = -1;
					continue;
				}
				mp[i][j] = 0;
				if (ch[j] == '.') continue;
				if (ch[j] >= 'A' && ch[j] <= 'Z') {
					jewel[ch[j] - 'A'][1].push_back(make_pair(i, j));
					pos[i][j] = make_pair(ch[j] - 'A', jewel[ch[j] - 'A'][1].size() - 1);
				} else jewel[ch[j] - 'a'][0].push_back(make_pair(i, j));
			}
		}
	//	continue;
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				fa[i][j] = make_pair(i, j);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				pair<int, int> u, v;
				if (i > 1 && mp[i][j] > -1 && mp[i - 1][j] > -1) {
					u = getfa(make_pair(i, j));
					v = getfa(make_pair(i - 1, j));
					fa[u.first][u.second] = v;
				}
				if (j > 1 && mp[i][j] > -1 && mp[i][j - 1] > -1) {
					u = getfa(make_pair(i, j));
					v = getfa(make_pair(i, j - 1));
					fa[u.first][u.second] = v;
				}
			}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				fa[i][j] = getfa(make_pair(i, j));
			}
		
		for (int i = 0; i < alphabet; ++i)
			for (int j = 0; j < jewel[i][0].size(); ++j)
				for (int k = 0; k < jewel[i][1].size(); ++k)
					dp[i][j][k] = -INF, vis[i][j][k] = false;
		for (int i = 0; i < alphabet; ++i)
			for (int j = 0; j < jewel[i][0].size(); ++j)
				for (int k = 0; k < jewel[i][1].size(); ++k)
					dp[i][j][k] = dfs(i, j, k);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				board[i][j] = -INF;
		board[1][1] = 0;
		for (int x = 1; x <= n; ++x)
			for (int y = 1; y <= m; ++y) {
				if (mp[x][y] < 0) {
					board[x][y] = -INF;
					continue;
				}
				if (x > 1 && mp[x - 1][y] > -1) board[x][y] = max(board[x][y], board[x - 1][y]);
				if (y > 1 && mp[x][y - 1] > -1) board[x][y] = max(board[x][y], board[x][y - 1]);
				int cc = pos[x][y].first, id = pos[x][y].second;
				if (cc < 0) continue;
				for (int k = 0; k < jewel[cc][0].size(); ++k) {
					pair<int, int> tmp = jewel[cc][0][k];
					board[x][y] = max(board[x][y], board[tmp.first][tmp.second] + dp[cc][k][id]);
				}
			}
		int ans = (board[n][m] < 0) ? -1 : board[n][m];
		printf("%d\n", ans);
	}
}
