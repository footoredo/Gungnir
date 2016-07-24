#include <bits/stdc++.h>
using namespace std;
typedef double DB;

const DB eps = 1e-8;
const int N = 55555;
int n;

__inline int dcmp(DB x) {
	return x < -eps ? -1 : (x > eps ? 1 : 0);
}

struct Point {
	DB x, y;
	__inline Point(): x(0), y(0) {}
	__inline Point(DB x, DB y): x(x), y(y) {}
	__inline Point operator+(const Point& p) const {
		return Point(x + p.x, y + p.y);
	}
	__inline Point operator-(const Point& p) const {
		return Point(x - p.x, y - p.y);
	}
	__inline int read() {
		return scanf("%lf%lf", &x, &y);
	}
	__inline Point operator*(DB k) const {
		return Point(x * k, y * k);
	}
	__inline Point operator/(DB k) const {
		return Point(x / k, y / k);
	}
} P[N], C[N];

__inline DB det(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}

__inline DB dot(const Point& a, const Point& b) {
	return a.x * b.x + a.y * b.y;
}

__inline bool Pair_Comp(const Point& a, const Point& b) {
	if (dcmp(a.x - b.x) < 0) return true;
	if (dcmp(a.x - b.x) > 0) return false;
	return dcmp(a.y - b.y) < 0;
}

int Convex_Hull(int n, Point *P, Point *C) {
	sort(P, P + n, Pair_Comp);
	int top = 0;
	for (int i = 0; i < n; i++) {
		while (top >= 2 && dcmp(det(C[top - 1] - C[top - 2], P[i] - C[top - 2])) <= 0) top--;
		C[top++] = P[i];
	}
	int lasttop = top;
	for (int i = n - 1; i >= 0; i--) {
		while (top > lasttop && dcmp(det(C[top - 1] - C[top - 2], P[i] - C[top - 2])) <= 0) top--;
		C[top++] = P[i];
	}
	return --top;
}

int main() {
	int T; scanf("%d", &T);
	for (; T--; ) {
		scanf("%d", &n);
		Point center, g_center;
		for (int i = 0; i < n; i++) P[i].read(), center = center + P[i];
		center = center / n;
		DB S = 0;
		for (int i = 0; i < n; i++) {
			Point t_center = center + P[i] + P[(i+1) % n];
			t_center = t_center / 3;
			DB tS = det(P[i] - center, P[(i+1) % n] - center);
			g_center = g_center + t_center * tS;
			S += tS;
		}
		g_center = g_center / S;
		int cc = Convex_Hull(n, P, C), ans = 0;
		//printf("%.3f %.3f\n", g_center.x, g_center.y);
		for (int i = 0; i < cc; i++) {
			//printf("%.3f %.3f\n", C[i].x, C[i].y);
			int j = (i + 1) % cc;
			if (dcmp(dot(g_center - C[j], C[i] - C[j])) * dcmp(dot(g_center - C[i], C[i] - C[j])) < 0) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}