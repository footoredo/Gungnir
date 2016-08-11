#include <bits/stdc++.h>
typedef long double DB;
const DB eps = 1e-9;
const DB PI = acos(DB(-1));
const DB LIM = 10000;

__inline int sign(DB x) {
	return x < -eps ? -1 : (x > eps ? 1 : 0);
}

__inline DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

const int N = 22;
struct Point {
	DB x, y;
	__inline Point(): x(0), y(0) {}
	__inline Point(DB x, DB y): x(x), y(y) {}
	__inline Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	__inline Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	__inline Point operator*(DB k) const {
		return Point(x * k, y * k);
	}
	__inline Point operator/(DB k) const {
		return Point(x / k, y / k);
	}
	__inline DB len2() const {
		return x * x + y * y;
	}
	__inline DB len() const {
		return msqrt(x * x + y * y);
	}
	__inline void read() {
		std::cin >> x >> y;
	}
	__inline void print() {
		std::cout << x << " " << y;
	}
	__inline bool operator<(const Point& rhs) const {
		return len2() < rhs.len2();
	}
} ball[N];

__inline DB dot(const Point& a, const Point& b) {
	return a.x * b.x + a.y * b.y;
}

__inline DB det(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}

struct Line {
	Point a, b;
	__inline Line() {}
	__inline Line(const Point& a, const Point& b): a(a), b(b) {}
} left, right, up, down;

struct Circle {
	Point o; DB r;
	__inline Circle(const Point& o, DB r): o(o), r(r) {}
};

__inline bool _isLL(const Line& l1, const Line& l2, Point &p) {
	if (!sign(det(l2.b - l2.a, l1.b - l1.a))) return false;
	DB s1 = det(l2.b - l2.a, l1.a - l2.a),
	   s2 = -det(l2.b - l2.a, l1.b - l2.a);
	p = (l1.a * s2 + l1.b * s1) / (s1 + s2);
	return true;
}

__inline bool _isCL(const Circle& a, const Line& l, Point& p1, Point& p2) {
	DB x = dot(l.a - a.o, l.b - l.a),
	   y = (l.b - l.a).len2(),
	   d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if (sign(d) < 0) return false;
	Point p = l.a - ((l.b - l.a) * (x / y)), delta = (l.b - l.a) * (msqrt(d) / y);
	p1 = p + delta, p2 = p - delta;
	return true;
}

__inline bool isLL(const Point& O, const Point& vec, const Line L, Point& x) {
	if (!_isLL(Line(O, O + vec), L, x)) return false;
	if (sign(dot(x - O, vec)) < 0) return false;
	return true;
}

__inline bool isCL(const Point& O, const Point& vec, const Point& A, DB r, Point& p) {
	Point p1, p2;
	if (!_isCL(Circle(A, r * 2), Line(O, O + vec), p1, p2)) return false;
	bool found = false;
	if (sign(dot(p1 - O, vec)) >= 0) {
		found = true;
		p = p1;
	}
	if (sign(dot(p2 - O, vec)) >= 0) {
		if (!found || found && dot(p1 - p2, vec) > 0) {
			found = true;
			p = p2;
		}
	}
	return found;
}

std::vector<std::pair<DB, int> > event;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(3);

	int n;
	for (; std::cin >> n, n; ) {
		DB w, h, r; Point vec;
		std::cin >> w >> h >> r;
		left = Line(Point(r, 0), Point(r, h));
		right = Line(Point(w - r, 0), Point(w - r, h));
		up = Line(Point(0, h - r), Point(w, h - r));
		down = Line(Point(0, r), Point(w, r));
		vec.read();
		for (int i = 0; i < n; ++ i)
			ball[i].read();
		DB dis = 0;
		Point cur = ball[0];
		bool hit = false;
		int hitball;
		int last = -100;
		for (; sign(dis - LIM) < 0; ) {
//			cur.print(); std::cout << " -> "; vec.print(); std::cout << std::endl;
			Point X;
			event.clear();
			if (isLL(cur, vec, left, X) && sign(vec.x) < 0) 
				event.push_back(std::make_pair(dot(X - cur, vec), 0));
			if (isLL(cur, vec, down, X) && sign(vec.y) < 0) 
				event.push_back(std::make_pair(dot(X - cur, vec), -1));
			if (isLL(cur, vec, right, X) && sign(vec.x) > 0)
				event.push_back(std::make_pair(dot(X - cur, vec), -2));
			if (isLL(cur, vec, up, X) && sign(vec.y) > 0) 
				event.push_back(std::make_pair(dot(X - cur, vec), -3));
			for (int i = 1; i < n; ++ i)
				if (isCL(cur, vec, ball[i], r, X))
					event.push_back(std::make_pair(dot(X - cur, vec), i));
			std::sort(event.begin(), event.end());
//			std::cout << event[0].first << " " << event[0].second << std::endl;
			DB movement = event[0].first / vec.len();
			if (event[0].second > 0) {
				if (sign(dis + movement - LIM) <= 0) {
					hit = true; hitball = event[0].second + 1;
					break;
				}
				else break;
			}
			else {
				if (sign(dis + movement - LIM) <= 0) {
					dis += movement;
					cur = cur + vec / vec.len() * movement;
					int t = event[0].second;
					last = t;
					if (t == 0 || t == -2) vec.x = -vec.x;
					else if (t == -1 || t == -3) vec.y = - vec.y;
				}
				else break;
			}
		}

		if (hit) std::cout << hitball << std::endl;
		else std::cout << -1 << std::endl; 
	}

	return 0;
}
