#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const DB eps = 1e-12, lbound = 0, rbound = 1000;

__inline int sign(DB x) {
	return x < -eps ? -1 : ( x > eps ? 1 : 0 );
}

__inline DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

pair<DB, DB> solve(int A, int B, DB C) {
	if (A == 0) {
		if (B == 0) return sign(C) <= 0 ? make_pair(lbound - eps, rbound + eps) : make_pair(lbound+1., lbound);
		else if (B > 0) return make_pair(lbound - eps, -C / B + eps);
		else return make_pair(-C / B - eps, rbound + eps);
	}
	else {
		DB delta = DB(B) * B - 4 * A * C;
		if (sign(delta) < 0) return make_pair(lbound+1., lbound);
		DB sd = msqrt(delta);
		DB x1 = (-B - sd) / (2*A), x2 = (-B + sd) / (2*A);
		return make_pair(x1 - eps, x2 + eps);
	}
}

const int N = 11111;
int n, a[N], b[N], c[N];

bool check(DB level) {
	pair<DB, DB> iv(lbound - eps, rbound + eps);
	for (int i = 0; i < n; i++) {
		pair<DB, DB> tv = solve(a[i], b[i], c[i] - level);
		iv.first = max(iv.first, tv.first);
		iv.second = min(iv.second, tv.second);
		if (sign(iv.second - iv.first) < 0) return 0;
	}
	return sign(iv.second - iv.first) > 0;
}

int main() {
	int T; scanf("%d", &T);
	for (; T--; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
		DB l = -2e8, r = 2e8;
		for (int i = 0; i < 70; i++) {
			DB m = (l + r) / 2.0;
			if (check(m)) r = m; else l = m;
		}
		printf("%.4f\n", (double)(r + eps));
	}
	
	return 0;
}
