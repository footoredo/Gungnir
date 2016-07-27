#include <bits/stdc++.h>
using namespace std;

const int N = 55;

typedef long double DB;
const DB eps = 1e-10, PI = acos(DB(-1));

__inline int sign(DB x) {
	return x < -eps ? -1 : (x > eps ? 1 : 0);
}

__inline DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

__inline DB sqr(DB x) {
	return x * x;
}

struct Point {
	DB x, y;
	Point(): x(0), y(0) {}
	Point(DB _x, DB _y): x(_x), y(_y) {}
	DB len2() const {
		return x * x + y * y;
	}
	DB len() const {
		return msqrt(len2());
	}
	Point operator+(Point rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(Point rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	Point operator*(DB k) const {
		return Point(x * k, y * k);
	}
	Point operator/(DB k) const {
		assert(sign(k));
		return Point(x / k, y / k);
	}
	Point rotate(const DB ang) const {
		return Point(cos(ang) * x - sin(ang) * y, cos(ang) * y + sin(ang) * x);
	}
	DB ang() const {
		return atan2(y, x);
	}
	void read() {
		cin >> x >> y;
	}
} p[4];

DB det(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

DB dot(Point a, Point b) {
	return a.x * b.x + a.y * b.y;
}

struct Circle {
	Point o; DB r;
	Circle() {}
	Circle(Point a, Point b) {
		o = (a + b) / 2.0;
		r = (b - o).len();
	}
	DB area() {
		return r * r * PI;
	}
};

struct Event {
	Point p;
	DB ang;
	int delta;
	Event(Point p = Point(0, 0), double ang = 0, double delta = 0): p(p), ang(ang), delta(delta) {}
};
bool operator<(const Event& a, const Event& b) {
	return a.ang < b.ang;
}
void addEvent(const Circle& a, const Circle& b, vector<Event> &evt, int &cnt) {
	DB d2 = (a.o - b.o).len2(),
		dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2,
		pRatio = msqrt(-(d2 - sqr(a.r - b.r)) * (d2 - sqr(a.r + b.r)) / (d2 * d2 * 4));
	Point d = b.o - a.o, p = d.rotate(PI / 2),
		q0 = a.o + d * dRatio + p * pRatio,
		q1 = a.o + d * dRatio - p * pRatio;
	DB ang0 = (q0 - a.o).ang(),
		ang1 = (q1 - a.o).ang();
	evt.push_back(Event(q1, ang1, 1));
	evt.push_back(Event(q0, ang0, -1));
	cnt += ang1 > ang0;
}
bool issame(const Circle &a, const Circle& b) {
	return sign((a.o - b.o).len()) == 0 && sign(a.r - b.r) == 0;
}
bool overlap(const Circle& a, const Circle& b) {
	return sign(a.r - b.r - (a.o - b.o).len()) >= 0;
}
bool intersect(const Circle& a, const Circle& b) {
	return sign((a.o - b.o).len() - a.r - b.r) < 0;
}
int C;
Circle c[N];
DB area[N];
void solve() {
	memset(area, 0, sizeof(DB) * (C+1));
	for (int i = 0; i < C; i++) {
		int cnt = 1;
		vector<Event> evt;
		for (int j = 0; j < i; ++j) if (issame(c[i], c[j])) ++cnt;
		for (int j = 0; j < C; ++j) {
			if (j != i && !issame(c[i], c[j]) && overlap(c[j], c[i])) {
				++cnt;
			}
		}
		for (int j = 0; j < C; ++j) {
			if (j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j])) {
				addEvent(c[i], c[j], evt, cnt);
			}
		}
		if (evt.size() == 0) {
			area[cnt] += PI * c[i].r * c[i].r;
		}
		else {
			sort(evt.begin(), evt.end());
			evt.push_back(evt.front());
			for (int j = 0; j + 1 < (int)evt.size(); ++j) {
				cnt += evt[j].delta;
				area[cnt] += det(evt[j].p, evt[j + 1].p) / 2;
				DB ang = evt[j + 1].ang - evt[j].ang;
				if (ang < 0) {
					ang += PI * 2;
				}
				area[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2;
			}
		}
	}
}

Point isLL(const Point& a, const Point& b, const Point& c, const Point& d) {
	DB s1 = det(d - c, a - c), s2 = -det(d - c, b - c);
	return (a * s2 + b * s1) / (s1 + s2);
}

bool onSeg(const Point& a, const Point& b, const Point& p) {
	return sign(det(p - a, b - a)) == 0 && sign(dot(p - a, p - b)) <= 0;
}

bool cross(const Point& a, const Point& b, const Point& c, const Point& d) {
	if (!sign(det(b - a, d - c))) return 0;
	Point e = isLL(a, b, c, d);
	return onSeg(a, b, e) && onSeg(c, d, e);
}

int main() {
	int x1, y1, x2, y2, x3, y3, x4, y4;
	for (int T = 1; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4, x1 || y1 || x2 || y2 || x3 || y3 || x4 || y4; T++) {
		p[0] = Point(x1, y1); p[1] = Point(x2, y2); p[2] = Point(x3, y3); p[3] = Point(x4, y4);
		c[0] = Circle(p[0], p[2]); c[1] = Circle(p[0], p[3]); c[2] = Circle(p[1], p[2]); c[3] = Circle(p[1], p[3]);
		C = 4; solve();
		//printf("%.3f\n", (double)(c[0].area()+ c[1].area()+ c[2].area()+ c[3].area()));
		//printf("%.3f %.3f %.3f %.3f\n", (double)area[1], (double)area[2], (double)area[3], (double)area[4]);
		DB ans = area[1];
		if (!cross(p[0], p[1], p[2], p[3])) {
			/*c[0] = Circle(p[0], p[2]); c[1] = Circle(p[0], p[3]); C = 2; solve(); ans -= area[2];
			printf("%.3f %.3f\n", (double)area[1], (double)area[2]);
			//printf("%.3f\n", (double)area[2]);
			c[0] = Circle(p[1], p[2]); c[1] = Circle(p[1], p[3]); C = 2; solve(); ans -= area[2];
			printf("%.3f %.3f\n", (double)area[1], (double)area[2]);
			//printf("%.3f\n", (double)area[2]);*/
			ans -= area[4];
		}
		printf("Case %d: %.3f\n\n", T, (double)ans);
	}
}
