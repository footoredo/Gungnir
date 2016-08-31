#include <bits/stdc++.h>
using namespace std;

const int N = 4;
const double INF = 100000000;
const double eps = 1e-8;
double a[30][30], ans[30], fans[30], c[30][30], total, maxtotal;
int f[30], exist[30], num[30];
char str[11111];

void get_equation() {
	memset(a, 0, sizeof(a));
	memset(exist, 0, sizeof(exist));
	int l = strlen(str + 1), nowc = 1, i = 1;
	double nownumber = 0;
	while (i <= l) {
		if (str[i] == '+' || str[i] == '-') {
			if (str[i++] == '+') nowc = 1; else nowc = -1;
			nownumber = 0;
			continue;
		}
		if (isdigit(str[i])) {
			double db = 1.0;
			bool flag = false;
			while (i <= l && (isdigit(str[i]) || str[i] == '.')) {
				if (str[i] == '.') {
					flag = true;
					++i;
					continue;
				}
				if (flag) {
					db /= 10.0;
					nownumber += (str[i++] - '0') * db;
				} else {
					nownumber = nownumber * 10 + double(str[i++] - '0');
				}
			}
		}
		if (fabs(nownumber) < eps) nownumber = 1.0;
		nownumber *= nowc;
		if (i > l || str[i] == '+' || str[i] == '-') a[0][0] += nownumber;
		else {
			int x = str[i++] - 'a' + 1, y = 0;
			if (i <= l && str[i] != '+' && str[i] != '-') {
				if (str[i] == '^') {
					++i;
					if (str[i++] == '2') y = x;
				} else y = str[i++] - 'a' + 1;
			}
				a[x][y] += nownumber;
			if (x != y) a[y][x] += nownumber;
			exist[x] = exist[y] = 1;
		}
	}
}

inline void getans() {
	int cnt = 0;
	for (int i = 1; i <= N; ++i) {
		if (!exist[i] || f[i] > -1) continue;
		++cnt;
		for (int j = 1; j <= N; ++j) c[cnt][j] = 0;
		c[cnt][0] = -a[i][0];
		c[cnt][i] = a[i][i] * 2;
		for (int j = 1; j <= N; ++j) {
			if (i == j || fabs(a[i][j]) < eps) continue;
			if (f[j] == -1) c[cnt][j] = a[i][j];
			else c[cnt][0] -= a[i][j] * f[j];
		}
	}
	int ind = 0;
	for (int i = 1; i <= N; ++i) {
		int k = -1;
		double mx = 0.0;
		for (int j = ind + 1; j <= cnt; ++j) {
			if (fabs(c[j][i]) > mx) mx = fabs(c[j][i]), k = j;
		}
		if (k == -1) continue; else num[++ind] = i;
		for (int j = 0; j <= N; ++j) swap(c[k][j], c[ind][j]);
		for (int j = ind + 1; j <= cnt; ++j) {
			double tmp = c[j][i] / c[ind][i];
			if (fabs(tmp) < eps) continue;
			for (k = 0; k <= N; ++k) c[j][k] -= c[ind][k] * tmp;
		}
	}
	for (int i = 1; i <= N; ++i) ans[i] = f[i];
	for (int i = ind; i; --i) {
		if (fabs(c[i][num[i]]) < eps) return;
		ans[num[i]] = c[i][0] / c[i][num[i]];
		for (int j = 1; j < i; ++j) {
			if (fabs(c[j][num[i]]) < eps) continue;
			double tmp = c[j][num[i]] / c[i][num[i]];
			for (int k = 0; k <= N; ++k) c[j][k] -= c[i][k] * tmp;
		}
	}
	for (int i = 1; i <= N; ++i)
		if (exist[i] && (ans[i] < -eps || ans[i] > 1.0 + eps)) return;
	ans[0] = 1;
	double total = 0.0;
	for (int i = 0; i <= N; ++i)
		for (int j = 0; j <= i; ++j)
			total += a[i][j] * ans[i] * ans[j];
	if (total > maxtotal) {
		maxtotal = total;
		for (int i = 1; i <= N; ++i) fans[i] = ans[i];
	}
}

inline void dfs(int dep) {
	if (dep > N) getans();
	else {
		for (int i = -1; i < 2; ++i) {
			if (!exist[dep] && i > -1) continue;
			f[dep] = i;
			dfs(dep + 1);
		}
	}
}

int main() {
	scanf("%s", str + 1);
	get_equation();
	maxtotal = -INF;
	dfs(1);
	printf("%.10f\n", maxtotal);
	for (int i = 1; i <= N; i++)
		if (fans[i] < eps) fans[i] = 1e-15;
		else
			if (fans[i] > 1 - eps) fans[i] = 1.0 - 1e-15;
	for (int i = 1; i <= N; ++i)
		if (exist[i]) printf("%c=%.10f\n", char(i - 1 + 'a'), fans[i]);
}
