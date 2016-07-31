#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int tot = 11;
const char M[tot][5][4] = {
	{"***",
	 ".*.",
	 ".*.",
	 ".*.",
	 "..."},
	{"**.",
	 ".**",
	 ".*.",
	 ".*.",
	 "..."},
	{"**.",
	 ".*.",
	 ".**",
	 ".*.",
	 "..."},
	{"**.",
	 ".*.",
	 ".*.",
	 ".**",
	 "..."},
	{".*.",
	 "***",
	 ".*.",
	 ".*.",
	 "..."},
	{".*.",
	 "**.",
	 ".**",
	 ".*.",
	 "..."},
	{"**.",
	 ".*.",
	 ".**",
	 "..*",
	 "..."},
	{".*.",
	 "**.",
	 ".**",
	 "..*",
	 "..."},
	{".*.",
	 ".*.",
	 "***",
	 "..*",
	 "..."},
	{"*..",
	 "*..",
	 "**.",
	 ".*.",
	 ".*."},
	{"*..",
	 "**.",
	 ".**",
	 "..*",
	 "..."},
};
const int table[tot][6][4] = {
	{{0, 4, 7, 3}, {1, 5, 8, 4}, {2, 6, 9, 5}, {8, 9, 10, 7}, {10, 6, 11, 3}, {11, 2, 1, 0}},
	{{0, 3, 5, 2}, {1, 4, 6, 3}, {6, 7, 9, 5}, {4, 8, 11, 7}, {9, 11, 10, 2}, {10, 8, 1, 0}}, 
	{{0, 3, 5, 2}, {1, 4, 6, 3}, {6, 7, 8, 5}, {8, 11, 9, 2}, {7, 4, 10, 11}, {9, 10, 1, 0}},
	{{0, 3, 5, 2}, {1, 4, 6, 3}, {6, 10, 7, 5}, {7, 11, 8, 2}, {8, 9, 1, 0}, {11, 10, 4, 9}},
	{{0, 2, 3, 1}, {1, 4, 8, 10}, {3, 5, 6, 4}, {2, 11, 9, 5}, {6, 9, 7, 8}, {7, 11, 0, 10}},
	{{0, 2, 3, 1}, {1, 4, 6, 11}, {3, 5, 7, 4}, {7, 9, 8, 6}, {5, 2, 10, 9}, {8, 10, 0, 11}},
	{{0, 3, 5, 2}, {1, 4, 6, 3}, {6, 10, 7, 5}, {7, 8, 11, 2}, {10, 4, 9, 8}, {9, 1, 0, 11}},
	{{0, 2, 3, 1}, {1, 4, 6, 11}, {3, 5, 7, 4}, {7, 8, 10, 6}, {5, 2, 9, 8}, {9, 0, 11, 10}},
	{{0, 2, 3, 1}, {3, 10, 4, 9}, {9, 5, 11, 1}, {4, 6, 8, 5}, {10, 2, 7, 6}, {7, 0, 11, 8}},
	{{0, 2, 3, 1}, {3, 9, 4, 8}, {4, 5, 10, 11}, {9, 2, 6, 5}, {6, 0, 7, 10}, {7, 1, 8, 11}},
	{{0, 2, 3, 1}, {3, 5, 4, 11}, {2, 10, 6, 5}, {6, 7, 9, 4}, {10, 0, 8, 7}, {8, 1, 11, 9}}
};
const int link[6][2] = {{0, 2}, {1, 3}, {0, 3}, {0, 1}, {1, 2}, {2, 3}};
const int ro[6] = {1, 0, 3, 4, 5, 2};
const int re[6] = {0, 1, 3, 2, 5, 4};
const int re_2[6] = {0, 1, 5, 4, 3, 2};
const int maxn = 30;
const int base = 401;
int num[maxn][maxn], tn[maxn][maxn], a[maxn][maxn], ta[maxn][maxn], totjoin[maxn], T, n, m;

struct unionset {
	int node, size;
} fa[maxn];

struct point {
	int x, y;
} f[maxn];

void rot(int &n, int &m) {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			ta[j][n - i + 1] = a[i][j];
			tn[j][n - i + 1] = num[i][j];
		}
	swap(n, m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			a[i][j] = ro[ta[i][j]];
			num[i][j] = tn[i][j];
		}
}

void rev(int n, int m) {
	for (int i = 1; i <= n; ++i) {
		reverse(a[i] + 1, a[i] + m + 1);
		reverse(num[i] + 1, num[i] + m + 1);
		for (int j = 1; j <= m; ++j) a[i][j] = re[a[i][j]];
	}
}

void rev_2(int n, int m) {
	for (int j = 1; j <= m; ++j)
		for (int i = 1; i <= n / 2; ++i) {
			swap(a[i][j], a[n - i + 1][j]);
			swap(num[i][j], num[n - i + 1][j]);
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = re_2[a[i][j]];
}

int getfa(int k) {
	if (fa[k].node == k) return k;
	return fa[k].node = getfa(fa[k].node);
}

void join(int x, int y) {
	totjoin[x]++; totjoin[y]++;
	int fx = getfa(x), fy = getfa(y);
	if (fx != fy) {
		fa[fx].node = fy;
		fa[fy].size += fa[fx].size;
	}
}

void solve(int n, int m, set<LL> &ans) {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) 
			for (int k = 0; k < tot; ++k) {
				int ind = 0;
				bool flag = true;
				for (int p = 0; p < 5; ++p)
					for (int q = 0; q < 3; ++q)
						if (i + p <= n && j + q <= m && M[k][p][q] == '*') {
							f[ind].x = i + p;
							f[ind].y = j + q;
							++ind;
						}
				if (ind < 6) continue;
				for (int p = 0; p < 12; ++p) {
					fa[p].node = p; fa[p].size = 1; totjoin[p] = 0;
				}
				for (int p = 0; p < ind; ++p) {
					int tmp = a[f[p].x][f[p].y];
					join(table[k][p][link[tmp][0]], table[k][p][link[tmp][1]]);
				}
				int s = 0;
				for (int p = 0; p < 12; ++p) {
					if (totjoin[p] != 0 && totjoin[p] != 2 || fa[getfa(p)].size != 6 && fa[getfa(p)].size != 1) {
						flag = false;
						break;
					}
					if (fa[getfa(p)].size == 1) s++;
				}
				if (s != 6) continue;
				if (!flag) continue;
				assert(s == 6);
				vector<int> allnum;
				allnum.clear();
				for (int p = 0; p < ind; ++p) allnum.push_back(num[f[p].x][f[p].y]);
				sort(allnum.begin(), allnum.end());
				LL x = 0;
				for (vector<int>::iterator it = allnum.begin(); it != allnum.end(); ++it) x = x * base + *it;
				if (ans.find(x) == ans.end()) ans.insert(x);
			}
}

int main() {
	scanf("%d", &T);
	for (int cs = 1; cs <= T; ++cs) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
				num[i][j] = (i - 1) * m + j;
			}
				
		set<LL> ans;
		ans.clear();
		for (int i = 0; i < 4; ++i) {
			rot(n, m);
			for (int j = 0; j < 2; ++j) {
				rev(n, m);
				solve(n, m, ans);
			}
		}
		printf("Case %d: %d\n", cs, ans.size());
	}
	return 0;
}
