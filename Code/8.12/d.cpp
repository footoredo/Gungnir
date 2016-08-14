#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 2222;
int n;

struct point {
	int x, y;
	point() {};
	point(int _x, int _y): x(_x), y(_y) {};
	inline friend point operator + (const point &p, const point &q) {
		return point(p.x + q.x, p.y + q.y);
	}
	inline friend point operator - (const point &p, const point &q) {
		return point(p.x - q.x, p.y - q.y);
	}
} P[MAXN], p[MAXN * 2];

inline LL dot(const point &p, const point &q) {
	return (LL)p.x * q.x + (LL)p.y * q.y;
}

inline LL cross(const point &p, const point &q) {
	return (LL)p.x * q.y - (LL)p.y * q.x;
}

inline bool operator < (const point &p, const point &q) {
	if (p.y >= 0 && q.y < 0) return true;
	if (p.y < 0 && q.y >= 0) return false;
	if (!p.y && !q.y) return p.x > q.x;
	return cross(p, q) > 0;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", &P[i].x, &P[i].y);
		LL ans = (LL)n * (n - 1) * (n - 2) / 6;
		LL temp = 0;
		for (int i = 1; i <= n; ++i) {
			int cnt = 0;
			for (int j = 1; j <= n; ++j)
				if (i != j) p[++cnt] = P[j] - P[i];
			sort(p + 1, p + cnt + 1);
			for (int j = 1; j <= cnt + 1; ++j) p[cnt + j] = p[j];
			int l = 1, r = 1;
			for (int j = 1; j <= cnt; ++j) {
				if (l < j) l = r = j;
				while (l + 1 < j + cnt && cross(p[j], p[l + 1]) >= 0 && dot(p[j], p[l + 1]) > 0) ++l;
				if (l + 1 == j + cnt || cross(p[j], p[l + 1]) <= 0 || dot(p[j], p[l + 1]) > 0) continue;
				r = max(r, l + 1);
				while (r + 1 < j + cnt && cross(p[j], p[r + 1]) > 0 && dot(p[j], p[r + 1]) <= 0) ++r;
				if (dot(p[j], p[r]) <= 0 || cross(p[j], p[r]) > 0) {
					ans -= r - l;
				}
			}
			int h = 1, t = 1;
			while (h <= cnt) {
				for (t = h; t < cnt && !cross(p[t + 1], p[h]) && dot(p[t + 1], p[h]) > 0; ++t);
				temp += LL(t - h + 1) * (t - h) / 2;
				h = t + 1;
			}
		}
		cout << ans - temp / 2 << endl;
	}
}
